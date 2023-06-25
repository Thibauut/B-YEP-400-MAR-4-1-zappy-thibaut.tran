/*
** EPITECH PROJECT, 2022
** B-YEP-400-MAR-4-1-zappy-thibaut.tran
** File description:
** BarTime.cpp
*/

#include "BarTime.hpp"

Bar::Bar()
{
    _enabled = false;
}

Bar::~Bar()
{
    UnloadTexture(_background);
    UnloadTexture(_pointer);
}

// 1600 50
void Bar::init(Vector2 position)
{
    _cadrePosition = {position.x, position.y};
    _backgroundPosition = {position.x + 8, position.y + 8};
    _fillPosition = {position.x + 8, position.y + 5};
    _background = LoadTexture("gui/assets/slider/background.png");
    _cadre = LoadTexture("gui/assets/slider/cadre.png");
    _startX = position.x;
    _pointerPosition = {(float) _startX, position.y + 2};
    _pointer = LoadTexture("gui/assets/slider/pointer.png");
    _tmpTime = 2;
    _value = 2;
    _fill = LoadTexture("gui/assets/slider/fill.png");
    _fillRec = (Rectangle) { 0.0f, 100.0f, 0.0f, 33.0f };
    _textValue = LoadFont("gui/assets/fonts/font1.ttf");
}

void Bar::draw()
{
    if (_show) {
        DrawTextureEx(_background, _backgroundPosition, 0, 0.15f, WHITE);
        DrawTextureRec(_fill, _fillRec, _fillPosition, WHITE);
        DrawTextureEx(_cadre, _cadrePosition, 0, 0.15f, WHITE);
        DrawTextureEx(_pointer, _pointerPosition, 0, 0.15f, WHITE);
        Vector2 tmpPos = _pointerPosition;
        tmpPos.x += 8;
        tmpPos.y += 15;
        DrawTextEx(_textValue, TextFormat("%d", _value), tmpPos, 20, 10, WHITE);
    }
}

void Bar::setValue(int value)
{
    _value = value;
}

bool Bar::isEnabled()
{
    return _enabled;
}

void Bar::checkMouseClick()
{
    if (_show) {
        float posMouse = GetMousePosition().x - ((262 * 0.15f) / 2);
        float yMouse = GetMousePosition().y - ((262 * 0.15f) / 2);
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            if (posMouse >= (_startX + 4) && posMouse <= _startX + 200 && yMouse >= (_pointerPosition.y) && yMouse <= (_pointerPosition.y + (262 * 0.15f))) {
                _enabled = true;
            }
        }
        if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
            _enabled = false;
        }

        if (_enabled == true) {
            if (posMouse >= (_startX + 4) && posMouse <= _startX + 200) {
                _fillRec.width = (posMouse - _startX) + ((262 * 0.15f) / 2);
                _pointerPosition.x = posMouse;
                _value = ((posMouse - _startX) / 2);
            }
        }
    }
}

void Bar::show()
{
    _show = true;
}

void Bar::hide()
{
    _show = false;
}