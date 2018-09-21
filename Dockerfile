FROM ubuntu:18.04

RUN apt -y update
RUN apt -y install sudo openssh-server git curl bison libcurl4-openssl-dev libssl-dev libhiredis-dev \
                   libmarkdown2-dev libcap-dev libcgroup-dev make libpcre3 libpcre3-dev libmysqlclient-dev gcc

ENV NGINX_VERSION 1.15.3
RUN wget http://nginx.org/download/nginx-$NGINX_VERSION.tar.gz &&\
    tar zxf nginx-$NGINX_VERSION.tar.gz

ENV NGX_CONFIG_OPT --with-http_stub_status_module \
                   --with-http_ssl_module \
                   --prefix=/usr/local/nginx \
                   --with-http_realip_module \
                   --with-http_addition_module \
                   --with-http_sub_module \
                   --with-http_gunzip_module \
                   --with-http_gzip_static_module \
                   --with-http_random_index_module \
                   --with-http_secure_link_module \
                   --add-module=/nginx-ssh-module

WORKDIR /nginx-$NGINX_VERSION
EXPOSE 8022
