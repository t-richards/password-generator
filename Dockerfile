# Build
FROM alpine:latest AS builder
# Workaround for https://gitlab.com/qemu-project/qemu/-/issues/2825
RUN apk upgrade --no-cache --scripts=no apk-tools
RUN apk add --update --no-cache git openssh-client binutils gcc make musl-dev libc-dev check-dev
ENV CFLAGS="-static -no-pie -O2 -pipe -fstack-protector-strong -fno-plt"
ENV CPPFLAGS="-D_FORTIFY_SOURCE=2"
ENV LDFLAGS="-Wl,-O1,--sort-common,--as-needed,-z,relro"
WORKDIR /src
COPY . /src
RUN make dist

# Run
FROM scratch AS runner
COPY --from=builder /src/password-generator /password-generator
ENTRYPOINT ["/password-generator"]
