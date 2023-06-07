/*
** EPITECH PROJECT, 2022
** Zappy
** File description:
** Map.hpp
*/

#pragma once

#include "SFML.hpp"

class Map {
    public:
        Map();
        ~Map();
        void createMap();
        void drawMap();
        void destroyMap();
        void runMap();
        void setMap(sf::RenderWindow *window);
        sf::RenderWindow *getMap();
    private:
        sf::RenderWindow *_window;
};