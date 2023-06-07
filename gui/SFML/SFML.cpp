/*
** EPITECH PROJECT, 2022
** Zappy
** File description:
** SFML.cpp
*/

#include "SFML.hpp"

SFML::SFML()
{}

SFML::~SFML()
{}

void SFML::createWindow()
{
    _window = new sf::RenderWindow(sf::VideoMode(800, 600), "Zappy");
}

void SFML::drawWindow()
{
    _window->display();
}

void SFML::destroyWindow()
{
    _window->close();
}

void SFML::runWindow()
{
    while (_window->isOpen()) {
        sf::Event event;
        while (_window->pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                _window->close();
        }
        glClear(GL_COLOR_BUFFER_BIT);
    }
}

void SFML::setWindow(sf::RenderWindow *window)
{
    _window = window;
}

sf::RenderWindow *SFML::getWindow()
{
    return _window;
}