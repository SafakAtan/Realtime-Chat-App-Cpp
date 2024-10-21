# Real-Time Chat Application in C++

## Overview
This project is a real-time chat application developed in C++ using TCP sockets. It allows multiple clients to connect to a single server and send messages to each other. The application is designed to function similarly to a Twitch chat, where all connected clients can see messages from others and send messages in real time.

## Features
- Multiple clients can connect to the server.
- Clients can send and receive messages to and from all other connected clients.
- Continuous listening for incoming messages, allowing for a real-time chat experience.
- Implemented using C++ and Docker for containerization.

## Technologies Used
- C++
- TCP Sockets
- Docker
- Threading (for concurrent message receiving)

## Getting Started

### Prerequisites
- Docker installed on your machine
- Basic understanding of C++ and Docker

### Installation
1. Clone the repository:
   ```bash
   git clone https://github.com/yourusername/Realtime-Chat-App-Cpp.git
   cd Realtime-Chat-App-Cpp
