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

Anim::Anim(Rectangle frameRec, int speed, Vector2 position, int maxFrames, float scale)
{
    _frameRec = frameRec;
    _framesSpeed = speed;
    _framesCounter = 0;
    _currentFrame = 0;
    _position = position;
    _maxFrames = maxFrames;
    _settings = {position.x, position.y, scale, scale};
}

Anim::~Anim()
{
}

void Anim::draw(Texture2D texture)
{
    DrawTexturePro(texture, _frameRec, _settings, Vector2{0, 0}, 0, WHITE);
}

void Anim::setPosition(Vector2 position)
{
    _position = position;
    _settings.x = _position.x;
    _settings.y = _position.y;
}

void Anim::update()
{
    _framesCounter++;
    if (_framesCounter >= (GetFrameTime()/_framesSpeed)) {
        _framesCounter = 0;
        _currentFrame++;
        if (_currentFrame >= _maxFrames) _currentFrame = 0;
        _frameRec.x = _frameRec.x + _frameRec.width;
    }
}