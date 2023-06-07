/*
** EPITECH PROJECT, 2022
** Zappy
** File description:
** SFML.hpp
*/

#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/OpenGL.hpp>

class SFML {
    public:
        SFML();
        ~SFML();
        void createWindow();
        void drawWindow();
        void destroyWindow();
        void runWindow();
        void setWindow(sf::RenderWindow *window);
        sf::RenderWindow *getWindow();
    private:
        sf::RenderWindow *_window;
        GLuint _textureID;
};