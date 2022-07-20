#!/bin/bash
gcc main.c -lfcgi -o main
spawn-fcgi -p 8080 ./main
nginx -g "daemon off;"
service nginx start
/bin/bash
