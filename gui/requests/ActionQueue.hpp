/*
** EPITECH PROJECT, 2022
** B-YEP-400-MAR-4-1-zappy-thibaut.tran
** File description:
** ActionQueue.hpp
*/

#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <mutex>

class ActionQueue {
    public:
        ActionQueue();
        ~ActionQueue();

        void push(std::string action);
        std::string pop();
        bool isEmpty();
        std::vector<std::string> getQueue();

    private:
        std::vector<std::string> _queue;
        std::mutex _mutex;
};
