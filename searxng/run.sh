#docker run --name searxng -d -p 8888:8080 -v "./config/:/etc/searxng/" -v "./data/:/var/cache/searxng/" docker.io/searxng/searxng:latest

docker-compose -f ~/.config/searxng/compose.yaml up -d searxng
