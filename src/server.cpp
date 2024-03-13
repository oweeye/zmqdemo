 
#include <zmq.hpp>
#include <iostream>
#include <string>
#include <thread>

int main() {
    zmq::context_t context(1);
    zmq::socket_t socket(context, ZMQ_REP);
    socket.bind("tcp://*:5555");

    while (true) {
        zmq::message_t request;

        // Wait for the next request from the client
        socket.recv(&request);
        std::string message(static_cast<char*>(request.data()), request.size());
        std::cout << "Received message: " << message << std::endl;

        // Simulate doing some work
        std::this_thread::sleep_for(std::chrono::milliseconds(500));

        // Send reply back to the client
        std::string replyMessage = "Message received";
        zmq::message_t reply(replyMessage.size());
        memcpy(reply.data(), replyMessage.c_str(), replyMessage.size());
        socket.send(reply);
    }
    return 0;
}
