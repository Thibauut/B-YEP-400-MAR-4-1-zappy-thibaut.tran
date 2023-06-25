/*
** EPITECH PROJECT, 2022
** B-YEP-400-MAR-4-1-zappy-thibaut.tran
** File description:
** Cursor.cpp
*/

#include "Cursor.hpp"

Cursor::Cursor()
{
    _textureDisabled = LoadTexture("gui/assets/cursor/1.png");
    _textureEnabled = LoadTexture("gui/assets/cursor/2.png");
    _enabled = false;
    _position = {0, 0};
}

Cursor::~Cursor()
{
    UnloadTexture(_textureEnabled);
    UnloadTexture(_textureDisabled);
}

void Cursor::update(Bar &one, Bar &two)
{
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && one.isEnabled() == false && two.isEnabled() == false) {
        _enabled = true;
        _enabledPos = GetMousePosition();
        _enabledPos.x -= 15;
        _enabledPos.y -= 15;
    }
    if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
        _enabled = false;
    }
}

void Cursor::draw(Camera2D *camera)
{
    _position = GetMousePosition();
    _position.x -= 15;
    _position.y -= 15;
    if (_enabled)
        DrawTextureEx(_textureEnabled, _position, 0, 1.0f, WHITE);
    else
        DrawTextureEx(_textureDisabled, _position, 0, 1.0f, WHITE);
    if (_enabled) {
        camera->offset.x += (_position.x - _enabledPos.x) * 0.1f;
        camera->offset.y += (_position.y - _enabledPos.y) * 0.1f;
    }
}

