#!/bin/bash



if [[ $1 == "build" ]]; then
	docker build -t td ./
fi

docker images
docker ps -a
docker run -d -p 6667:6667 --name tcpdump td
docker exec -it tcpdump bash
