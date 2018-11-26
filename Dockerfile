FROM ubuntu:latest
MAINTAINER Joao Carvalho <jpldcarvalho@gmail.com>

WORKDIR /home/openp2p

RUN apt update && apt install libconfig9

COPY bin/ bin/
COPY config/ config/

CMD ["bin/main", "config/overlay/overlay.cfg"]
