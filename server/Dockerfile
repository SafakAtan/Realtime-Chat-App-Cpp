# server/Dockerfile
FROM gcc:latest
WORKDIR /app
COPY . .
RUN g++ -o server server.cpp
CMD ["./server"]
