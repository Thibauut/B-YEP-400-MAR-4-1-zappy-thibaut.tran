/*
** EPITECH PROJECT, 2022
** B-YEP-400-MAR-4-1-zappy-thibaut.tran
** File description:
** Egg.hpp
*/

#pragma once
#include <raylib.h>
#include "Player.hpp"

class Egg {
    public:
        Egg();
        Egg(std::string id);
        ~Egg();

        void draw(Texture2D texture);

        void setPosition(Vector2 position);
        Vector2 getPosition() const;

        void setId(std::string id);
        std::string getId() const;

    private:
        Vector2 _position;
        std::string _id;
};