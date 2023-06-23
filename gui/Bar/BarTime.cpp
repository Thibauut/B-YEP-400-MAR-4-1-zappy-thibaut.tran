/*
** EPITECH PROJECT, 2022
** B-YEP-400-MAR-4-1-zappy-thibaut.tran
** File description:
** BarTime.cpp
*/

#include "BarTime.hpp"

TimeBar::TimeBar()
{
    _enabled = false;
}

TimeBar::~TimeBar()
{
    UnloadTexture(_background);
    UnloadTexture(_pointer);
}

void TimeBar::init()
{
    _cadrePosition = {1600, 50};
    _backgroundPosition = {1608, 58};
    _fillPosition = {1608, 55};
    _background = LoadTexture("gui/assets/slider/background.png");
    _cadre = LoadTexture("gui/assets/slider/cadre.png");
    _startX = 1600;
    _pointerPosition = {(float) _startX, 52};
    _pointer = LoadTexture("gui/assets/slider/pointer.png");
    _tmpTime = 2;
    _time = 2;
    _fill = LoadTexture("gui/assets/slider/fill.png");
    _fillRec = (Rectangle) { 0.0f, 100.0f, 0.0f, 33.0f };
}

void TimeBar::draw()
{
    DrawTextureEx(_background, _backgroundPosition, 0, 0.15f, WHITE);
    DrawTextureRec(_fill, _fillRec, _fillPosition, WHITE);
    DrawTextureEx(_cadre, _cadrePosition, 0, 0.15f, WHITE);
    DrawTextureEx(_pointer, _pointerPosition, 0, 0.15f, WHITE);
}

void TimeBar::setTime(int time)
{
    _time = time;
}

void TimeBar::checkMouseClick()
{
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        _enabled = true;
    if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
        _enabled = false;

    float posMouse = GetMousePosition().x - ((262 * 0.15f) / 2);

    if (_enabled == true) {
        if (posMouse >= (_startX + 4) && posMouse <= _startX + 200) {
            _fillRec.width = (posMouse - _startX) + ((262 * 0.15f) / 2);
            _pointerPosition.x = posMouse;
            _time = ((posMouse - _startX) / 2);
        }
    }
}