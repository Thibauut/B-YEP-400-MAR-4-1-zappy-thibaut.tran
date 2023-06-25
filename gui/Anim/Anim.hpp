/*
** EPITECH PROJECT, 2022
** B-YEP-400-MAR-4-1-zappy-thibaut.tran
** File description:
** Anim.hpp
*/

#pragma once
#include "../Utils/Global.hpp"

class Anim {
    public:
        Anim();
        Anim(Rectangle frameRec, int speed, Vector2 position, int maxFrames, float scale);
        ~Anim();

        void draw(Texture2D texture);
        void update();

        void setPosition(Vector2 position);

    private:
        Vector2 _position;
        Rectangle _frameRec;
        Rectangle _settings;
        int _currentFrame;
        int _framesCounter;
        int _framesSpeed;
        int _maxFrames;
    };