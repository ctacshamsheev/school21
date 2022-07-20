#!/bin/bash

# echo ___________________________4_________________________
# sudo docker build -t myserver:current ./server/
# sudo docker run -it -p 80:81 --name testserver -v /home/student/DO5_SimpleDocker-0/src/server/nginx/:/etc/nginx -d myserver:current bash
# echo __________________________result_____________________
# curl localhost:80
# echo _____________________________________________________
# sudo docker stop testserver
# echo ___________________________dockle____________________
# sudo dockle myserver:current
# sudo docker rm $(sudo docker ps -a -f status=exited -q)
# sudo docker rmi myserver:current
echo ___________________________5_________________________
sudo docker build -t myserver:current ./server5/
sudo docker images
sudo docker run -it -p 80:81 --name testserver -v /home/student/DO5_SimpleDocker-0/src/server5/nginx/:/etc/nginx -d myserver:current bash
sudo docker ps
echo _____________________________________________________
#sudo dockle myserver:current
#echo ___________________________dockle____________________
#sudo dockle -i CIS-DI-0005 -i CIS-DI-0008  myserver:current
sleep 30
echo __________________________result_____________________
curl localhost:80
curl localhost:80/status
echo _____________________________________________________
sudo docker stop testserver
sudo docker rm $(sudo docker ps -a -f status=exited -q)
sudo docker rmi myserver:current
echo ___________________________6_______)_________________
sudo docker-compose build
sudo docker-compose up