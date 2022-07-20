FROM nginx

ARG USERNAME=nginx

USER root

COPY ./main.c /home/$USERNAME/main.c
COPY ./start.sh /home/$USERNAME/start.sh
COPY ./nginx/nginx.conf /etc/nginx/nginx.conf

EXPOSE 81/tcp

RUN apt-get update ; \
    apt-get install -y gcc spawn-fcgi libfcgi-dev ; \
    apt-get clean ; \
    rm -rf /var/lib/apt/lists/* ; 

WORKDIR /home/$USERNAME

RUN usermod -aG adm,nginx $USERNAME; \
    chown -R $USERNAME:$USERNAME /var/cache/nginx/ ; \
    chown -R $USERNAME:$USERNAME /var/run/ ; \
    chown -R $USERNAME:$USERNAME /home/$USERNAME/ ; \
    chmod +x /home/$USERNAME/start.sh

USER $USERNAME

HEALTHCHECK --interval=10s --timeout=30s --start-period=5s --retries=3 CMD curl -sS 127.0.0.1 || exit 1

ENTRYPOINT ["sh", "./start.sh"]