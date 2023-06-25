/*
** EPITECH PROJECT, 2022
** B-YEP-400-MAR-4-1-zappy-thibaut.tran
** File description:
** ActionQueue.cpp
*/

#include "ActionQueue.hpp"

ActionQueue::ActionQueue()
{
}

ActionQueue::~ActionQueue()
{
}

void ActionQueue::push(std::string action)
{
    std::unique_lock<std::mutex> lock(_mutex);
    std::cout << "PUSH: " << action << "END" << std::endl;
    _queue.push_back(action);
}

std::string ActionQueue::pop()
{
    std::unique_lock<std::mutex> lock(_mutex);
    std::string action = _queue.at(0);
    _queue.erase(_queue.begin());
    return action;
}

bool ActionQueue::isEmpty()
{
    std::unique_lock<std::mutex> lock(_mutex);
    return _queue.empty();
}

std::vector<std::string> ActionQueue::getQueue()
{
    std::unique_lock<std::mutex> lock(_mutex);
    return _queue;
}