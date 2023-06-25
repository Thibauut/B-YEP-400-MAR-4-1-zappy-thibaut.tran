/*
** EPITECH PROJECT, 2022
** B-YEP-400-MAR-4-1-zappy-thibaut.tran
** File description:
** Cursor.hpp
*/

#pragma once
#include <raylib.h>
#include "../Bar/BarTime.hpp"

class Cursor {
    public:
        Cursor();
        ~Cursor();

        void draw(Camera2D *camera);
        void update(Bar &one, Bar &two);
        void checkMouseClick();

    private:
        Vector2 _position;
        Vector2 _enabledPos;
        Texture2D _textureEnabled;
        Texture2D _textureDisabled;
        bool _enabled;
};