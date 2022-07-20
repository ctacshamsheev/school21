FROM nginx

COPY ./main.c /home/main.c
COPY ./start.sh /home/start.sh
COPY ./nginx/nginx.conf /etc/nginx/nginx.conf

EXPOSE 81/tcp

USER root

RUN apt-get update ; \
    apt-get install -y gcc spawn-fcgi libfcgi-dev ; \
    apt-get clean ; \
    rm -rf /var/lib/apt/lists/*

WORKDIR /home/

HEALTHCHECK --interval=10s --timeout=30s --start-period=5s --retries=3 CMD curl -sS 127.0.0.1 || exit 1

ENTRYPOINT ["sh", "./start.sh"]