/*
** EPITECH PROJECT, 2022
** B-YEP-400-MAR-4-1-zappy-thibaut.tran
** File description:
** Dragon.hpp
*/

#pragma once
#include <raylib.h>

class Dragon {
    public:
        Dragon();
        ~Dragon();

        void update();
        void draw();

    private:
        Vector2 _position;
        Model _model;
        Texture2D _texture;
        ModelAnimation *_animation;
        int _frameCounter;
        unsigned int _nbAnim;
};