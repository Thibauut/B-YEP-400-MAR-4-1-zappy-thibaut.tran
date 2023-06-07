/*
** EPITECH PROJECT, 2022
** B-YEP-400-MAR-4-1-zappy-thibaut.tran
** File description:
** Client.cpp
*/

#include "Client.hpp"

Client::Client(const std::string& ip, int port) {
    // Création du socket
    socketId = socket(AF_INET, SOCK_STREAM, 0);
    if (socketId == -1) {
        std::cerr << "Erreur lors de la création du socket." << std::endl;
        exit(1);
    }

    // Configuration de l'adresse du serveur
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(port);
    if (inet_pton(AF_INET, ip.c_str(), &(serverAddress.sin_addr)) <= 0) {
        std::cerr << "Adresse IP invalide ou non prise en charge." << std::endl;
        exit(1);
    }

    // Connexion au serveur
    if (connect(socketId, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) < 0) {
        std::cerr << "Erreur lors de la connexion au serveur." << std::endl;
        exit(1);
    }
}

Client::~Client() {
    // Fermeture du socket
    close(socketId);
}

void Client::sendRequest(const std::string& commande) {
    // Envoi de la commande au serveur
    if (send(socketId, commande.c_str(), commande.size(), 0) < 0) {
        std::cerr << "Erreur lors de l'envoi de la commande." << std::endl;
        exit(1);
    }
}

std::string Client::catchResponse() {
    // Réception de la réponse du serveur
    char buffer[1024] = {0};
    if (recv(socketId, buffer, sizeof(buffer), 0) < 0) {
        std::cerr << "Erreur lors de la réception de la réponse." << std::endl;
        exit(1);
    }

    return std::string(buffer);
}
