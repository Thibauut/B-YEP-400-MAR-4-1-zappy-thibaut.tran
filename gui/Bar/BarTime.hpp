/*
** EPITECH PROJECT, 2022
** B-YEP-400-MAR-4-1-zappy-thibaut.tran
** File description:
** BarTime.hpp
*/

#pragma once

#include "../Utils/Global.hpp"

class Bar {
    public:
        Bar();
        ~Bar();

        void init(Vector2 position);
        void draw();
        void setValue(int time);
        void checkMouseClick();
        bool isEnabled();
        void show();
        void hide();

        int _tmpTime;
        int _value;
    private:
        Vector2 _backgroundPosition;
        Texture2D _background;

        Vector2 _cadrePosition;
        Texture2D _cadre;

        int _startX;
        Vector2 _pointerPosition;
        Texture2D _pointer;
        bool _enabled;

        Vector2 _fillPosition;
        Texture2D _fill;
        Rectangle _fillRec;
        bool _show;

        Font _textValue;
};