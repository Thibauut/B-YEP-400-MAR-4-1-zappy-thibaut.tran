/*
** EPITECH PROJECT, 2022
** B-YEP-400-MAR-4-1-zappy-thibaut.tran
** File description:
** BarTime.hpp
*/

#pragma once

#include "../Utils/Global.hpp"

class TimeBar {
    public:
        TimeBar();
        ~TimeBar();

        void init();
        void draw();
        void setTime(int time);
        void checkMouseClick();

        int _tmpTime;
        int _time;
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
};