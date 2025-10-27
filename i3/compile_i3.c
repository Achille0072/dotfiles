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
    FILE* f = fopen(argv[1], "r");
    if(f == NULL)
    {
        fprintf(stderr, "Could not open config_seed file \n");
        exit(1);
    }

    char* home = getenv("HOME");
    char* config_path = malloc((strlen(home) + 1) * sizeof(char));
    config_path = strcpy(config_path, home);
    config_path = realloc(config_path, (strlen(config_path) + strlen("/.config/i3/") + 1) * sizeof(char));
    config_path = strcat(config_path, "/.config/i3/");

    FILE* config = fopen(strcat(config_path, "config"), "w");
    if(config == NULL)
    {
        fprintf(stderr, "Could not create config file \n");
        exit(1);
    }
    config_path[strlen(config_path) - strlen("config")] = '\0';

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

                config_path = realloc(config_path, (strlen(config_path) + strlen(path) + 1) * sizeof(char));
                FILE* included = fopen(strcat(config_path, path), "r");
                if(included == NULL)
                {
                    fprintf(stderr, "Could not open included file %s\n", config_path);
                    exit(1);
                }
                config_path[strlen(config_path) - strlen(path)] = '\0';
                while(getline(&buffer, &bufsize, included) != -1) fprintf(config, "%s", buffer);
                fclose(included);
            }
        } else fprintf(config, "%s", buffer);
    }

free(buffer);
free(config_path);
fclose(config);
fclose(f);
return 0;
}
