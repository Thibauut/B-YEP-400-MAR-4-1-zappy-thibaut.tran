/*
** EPITECH PROJECT, 2022
** B-YEP-400-MAR-4-1-zappy-thibaut.tran
** File description:
** Client.cpp
*/

#include "Client.hpp"

Client::Client() {}

Client::Client(const std::string& ip, int port)
{
    socketId = socket(AF_INET, SOCK_STREAM, 0);
    if (socketId == -1) {
        std::cerr << "Erreur lors de la création du socket." << std::endl;
        exit(1);
    }
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(port);
    if (inet_pton(AF_INET, ip.c_str(), &(serverAddress.sin_addr)) <= 0) {
        std::cerr << "Adresse IP invalide ou non prise en charge." << std::endl;
        exit(1);
    }
    if (connect(socketId, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) < 0) {
        std::cerr << "Erreur lors de la connexion au serveur." << std::endl;
        exit(1);
    }
    int flags = fcntl(socketId, F_GETFL, 0);
    fcntl(socketId, F_SETFL, flags | O_NONBLOCK);
    std::string response = catchResponse();
    std::cout << "response: " << response << std::endl;
    sendRequest("GUI\n");
    catchResponse();
}

Client::~Client()
{
    close(socketId);
}

void Client::sendRequest(const std::string& commande)
{
    if (send(socketId, commande.c_str(), commande.size(), 0) < 0) {
        std::cerr << "Erreur lors de l'envoi de la commande." << std::endl;
        exit(1);
    }
}

void Client::sendRequestId(const std::string& commande, std::string value)
{
    std::string command = commande + " " + value + "\n";
    if (send(socketId, command.c_str(), command.size(), 0) < 0) {
        std::cerr << "Erreur lors de l'envoi de la commande." << std::endl;
        exit(1);
    }
}

std::string Client::catchResponse()
{
    fd_set readSet;
    FD_ZERO(&readSet);
    FD_SET(socketId, &readSet);

    struct timeval timeout;
    timeout.tv_sec = 5;
    timeout.tv_usec = 0;

    if (select(socketId + 1, &readSet, NULL, NULL, &timeout) < 0) {
        std::cerr << "Erreur lors de l'attente de la réponse." << std::endl;
        exit(1);
    }

    if (FD_ISSET(socketId, &readSet)) {
        char buffer[1024] = {0};
        if (recv(socketId, buffer, sizeof(buffer), 0) < 0) {
            std::cerr << "Erreur lors de la réception de la réponse." << std::endl;
            exit(1);
        }

        return std::string(buffer);
    } else {
        return "";
    }
}
