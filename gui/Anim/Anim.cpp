/*
** EPITECH PROJECT, 2022
** B-YEP-400-MAR-4-1-zappy-thibaut.tran
** File description:
** Anim.cpp
*/

#include "Anim.hpp"

Anim::Anim()
{
}

Anim::Anim(Rectangle frameRec, int speed, Vector2 position)
{
    _frameRec = frameRec;
    _framesSpeed = speed;
    _framesCounter = 0;
    _currentFrame = 0;
    _position = position;
}

Anim::~Anim()
{
}

void Anim::draw(Texture2D texture)
{
    DrawTextureRec(texture, _frameRec, _position, WHITE);
}

void Anim::update()
{
    _framesCounter++;
    if (_framesCounter >= (GetFrameTime()/_framesSpeed))
    {
        _framesCounter = 0;
        _currentFrame++;
        // if (_currentFrame > 7) _currentFrame = 0;
        // _frameRec.x = (float)_currentFrame*(float)scarfy.width/6;
    }
}