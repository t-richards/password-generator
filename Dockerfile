FROM alpine:edge

RUN apk add --update --no-cache git openssh-client binutils gcc make musl-dev libc-dev
