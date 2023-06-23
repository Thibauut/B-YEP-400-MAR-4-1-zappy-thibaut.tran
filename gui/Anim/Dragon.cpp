/*
** EPITECH PROJECT, 2022
** B-YEP-400-MAR-4-1-zappy-thibaut.tran
** File description:
** Dragon.cpp
*/

#include "Dragon.hpp"

Dragon::Dragon()
{
    _nbAnim = 1;
    _frameCounter = 0;
    _position = {0.0f, 100.0f, 120.0f};
    _model = LoadModel("gui/models/decoration/TMP2.glb");
    // _animation = LoadModelAnimations("gui/models/decoration/low_poly_flying_dragon.glb", &_nbAnim);
}

Dragon::~Dragon()
{
    UnloadModel(_model);
}

void Dragon::draw()
{
    DrawModel(_model, _position, 3.0f, WHITE);
}

void Dragon::update()
{
    // _position.x += 0.1f;
    // _position.y += 0.1f;
    // _position.z += 0.1f;
    // UpdateModelAnimation(_model, _animation[0], _frameCounter);
    // _frameCounter = (_frameCounter + 1);
    // if (_frameCounter >= _animation[0].frameCount)
    //     _frameCounter = 0;
}