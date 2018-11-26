FROM alpine:latest
MAINTAINER Joao Carvalho <jpldcarvalho@gmail.com>

RUN ["mkdir", "/home/openp2p"]
WORKDIR /home/openp2p

RUN ["mkdir", "bin"]
RUN ["mkdir", "config"]
COPY bin/ bin/
COPY config/ config/

RUN ["ls", "bin/"]
RUN ["ls", "config/overlay"]

CMD ["./bin/main ./config/overlay/overlay.cfg"]

EXPOSE $OPENP2P_PORT
