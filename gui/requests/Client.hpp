/*
** EPITECH PROJECT, 2022
** B-YEP-400-MAR-4-1-zappy-thibaut.tran
** File description:
** Request.cpp
*/

#pragma once

#include <iostream>
#include <string>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>
// #include "../../dependencies/json.hpp"

// using json = nlohmann::json;

class Client {
    public:
        Client();
        Client(const std::string& ip, int port);
        ~Client();

        // bool sendRequestExec();
        void sendRequest(const std::string& commande);
        void sendRequestId(const std::string& commande, std::string value);
        // bool catchResponseExec();
        std::string catchResponse();
    private:
        int socketId;
        struct sockaddr_in serverAddress;
};