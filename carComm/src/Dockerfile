FROM alpine:3.7 as builder
MAINTAINER Team11 DIT168 gusisakal@student.gu.se
RUN apk update && \
    apk --no-cache add \
        ca-certificates \
        cmake \
        g++ \
        make && \
    apk add libcluon --no-cache --repository https://chrberger.github.io/libcluon/alpine/v3.7 --allow-untrusted
ADD . /opt/sources
WORKDIR /opt/sources
RUN cd /opt/sources && \
    mkdir communicationBuild && \
    cd communicationBuild && \
    cmake -D CMAKE_BUILD_TYPE=Release .. && \
    make && make test && cp communication.messageFetch /tmp && cp communication.messageSend /tmp

# Deploy.
FROM alpine:3.7
MAINTAINER Team11 DIT168 gusisakal@student.gu.se
RUN apk update && \
    apk add libcluon --no-cache --repository https://chrberger.github.io/libcluon/alpine/v3.7 --allow-untrusted && \
    mkdir /opt
WORKDIR /opt
COPY --from=builder /tmp/communication.messageFetch .
COPY --from=builder /tmp/communication.messageSend .
