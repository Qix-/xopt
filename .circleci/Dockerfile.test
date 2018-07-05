FROM alpine:3.7 AS base
WORKDIR /src
RUN apk --update add alpine-sdk cmake bash
COPY . ./
WORKDIR /src/build

# Debug
FROM base
RUN cmake .. -DCMAKE_BUILD_TYPE=Debug -DBUILD_TESTING=On
RUN cmake --build .
RUN ctest -VV

# Release
FROM base
RUN cmake .. -DCMAKE_BUILD_TYPE=Release -DBUILD_TESTING=On
RUN cmake --build .
RUN ctest -VV
