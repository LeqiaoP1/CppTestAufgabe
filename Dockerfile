FROM ubuntu:20.04

ARG DEBIAN_FRONTEND=noninteractive
ENV TZ=Europe/Berlin

RUN apt-get update && \
	apt-get install -y build-essential git cmake clang-format

USER root

WORKDIR "/workspace"

CMD ["/bin/bash"]
