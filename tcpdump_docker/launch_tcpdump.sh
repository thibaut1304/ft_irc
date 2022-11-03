#!/bin/bash




IMAGE_NAME="tcpdump_irc"
CONTAINER_NAME=$IMAGE_NAME

if [[ $1 == "build" ]]; then
  docker build ./ -t $IMAGE_NAME
fi


docker images
docker ps -a
docker run -d -p 6667:6667 --name $CONTAINER_NAME $IMAGE_NAME
docker exec -it $CONTAINER_NAME tcpdump -Aqq port 6667
