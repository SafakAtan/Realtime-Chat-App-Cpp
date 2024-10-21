FROM gcc:latest
WORKDIR /app
COPY . .
RUN g++ -o client client.cpp
CMD ["./client"]
