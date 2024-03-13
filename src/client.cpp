#include <zmq.hpp>
#include <string>
#include <iostream>
#include <thread>

int main() {
    zmq::context_t context(1);
    zmq::socket_t socket(context, ZMQ_REQ);

    std::cout << "Connecting to server..." << std::endl;
    socket.connect("tcp://localhost:5555");

    for (int i = 0; i < 10; i++) {
        std::string messageToSend = "Hello server " + std::to_string(i);
        zmq::message_t request(messageToSend.size());
        memcpy(request.data(), messageToSend.c_str(), messageToSend.size());
        std::cout << "Sending message: " << messageToSend << std::endl;
        
        socket.send(request);

        // Wait for the server reply
        zmq::message_t reply;
        socket.recv(&reply);
        std::string replyMessage(static_cast<char*>(reply.data()), reply.size());
        std::cout << "Received reply: " << replyMessage << std::endl;

        // Simulate doing some work
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
    return 0;
}
