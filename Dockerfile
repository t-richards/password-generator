# Build
FROM alpine:latest AS builder
RUN apk add --update --no-cache git openssh-client binutils gcc make musl-dev libc-dev check-dev
WORKDIR /src
COPY . /src
RUN make dist

# Run
FROM alpine:latest AS runner
COPY --from=builder /src/password-generator /password-generator
ENTRYPOINT ["/password-generator"]
