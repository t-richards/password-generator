FROM debian:stable

RUN set -ex; \
 apt-get update; \
 apt-get install -y --no-install-recommends curl ca-certificates git gcc linux-libc-dev make; \
 rm -rf /var/lib/apt/lists/*; \
 rm -rf /usr/share/man/*; \
 rm -rf /usr/share/doc/*
