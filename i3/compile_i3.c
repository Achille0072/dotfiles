#include <stdlib.h>
#include <stdio.h>
#include <string.h>


int compare (char* string, char* find, int start, int end)
{
    if(end == -1) end = strlen(find);

    for(int i = start; i < end; i++)
    {
        if(string[i] != find[i-start]) return 1;
    }
    return 0;
}

int main (int argc, char* argv[])
{
    FILE* f = fopen("config_seed", "r");
    if(f == NULL)
    {
        fprintf(stderr, "Could not open config file \n");
        exit(1);
    }

    FILE* temp = fopen("temp", "w");
    if(temp == NULL)
    {
        fprintf(stderr, "Could not create temp file \n");
        exit(1);
    }

    size_t bufsize = 1;
    char* buffer = malloc(bufsize * sizeof(char));

    while(getline(&buffer, &bufsize, f) != -1)
    {
        if(buffer[0] == '@')
        {
            if(compare(buffer, "include", 1, -1) == 0)
            {
                char* path = malloc(sizeof(char));
                int ignored = strlen("@include \"");
                for(int i = ignored; ; i++)
                {
                    path[i-ignored] = buffer[i];
                    if(buffer[i] == '"')
                    {   
                        path[i-ignored] = '\0';
                        break;
                    }
                    path = realloc(path, (i + 1 - ignored) * sizeof(char));
                }
                FILE* included = fopen(path, "r");
                if(included == NULL)
                {
                    fprintf(stderr, "Could not open included file %s\n", path);
                    exit(1);
                }
                while(getline(&buffer, &bufsize, included) != -1) fprintf(temp, "%s", buffer);
                fclose(included);
            }
        } else fprintf(temp, "%s", buffer);
    }

    fclose(f);
    fclose(temp);
    f = fopen("config", "w");
    temp = fopen("temp", "r");
    while(getline(&buffer, &bufsize, temp) != EOF)
        fprintf(f, "%s", buffer);


free(buffer);
fclose(temp);
remove("temp");
fclose(f);
return 0;
}
