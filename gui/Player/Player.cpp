/*
** EPITECH PROJECT, 2022
** B-YEP-400-MAR-4-1-zappy-thibaut.tran
** File description:
** Player.cpp
*/

#include "Player.hpp"
#include <iostream>

Player::Player() : _incantation((Rectangle) {0, 0, 140, 50}, 1, (Vector2) {0, 0}, 7, 50)
{
    _id = "";
    _player = LoadTexture("gui/assets/player/players.png");
    _anim = (Rectangle) {16 * 3, 22 * 10, 16, 22};
    _settings = (Rectangle) {_pos.x, _pos.y, (float)_player.width, (float)_player.height};
    _isIncanting = false;
}

Player::Player(std::string id) : _incantation((Rectangle) {0, 0, 140, 50}, 1, (Vector2) {0, 0}, 7, 50)
{
    _id = id;
    _anim = (Rectangle) {16 * 3, 22 * 10, 16, 22};
    _settings = (Rectangle) {_pos.x, _pos.y, 16 * 2, 22 * 2};
    _player = LoadTexture("gui/assets/player/players.png");
    _isIncanting = false;
}

Player::~Player()
{
    // UnloadTexture(_player);
}

void Player::setName(std::string id)
{
    _id = id;
}

std::string Player::getName() const
{
    return _id;
}

void Player::setInventory(std::vector<AItem *> inventory)
{
    _inventory = inventory;
}

std::vector<AItem *> Player::getInventory() const
{
    return _inventory;
}

void Player::setPosition(Vector2 pos)
{
    _pos = pos;
    int renderIndex = (_pos.y * (width_map)) + _pos.x;
    _settings.x = (screenWidth / 2) + (renderIndex % (width_map)) * (30) - (renderIndex / (width_map)) * 30;
    _settings.y = (renderIndex % (height_map)) * 25 + (renderIndex / (height_map)) * 25;
    _settings.y -= 10;
    _settings.x += 20;
    _incantation.setPosition((Vector2) {_settings.x - 10, _settings.y - 10});
}

Vector2 Player::getPosition() const
{
    return _pos;
}

void Player::setOrientation(int orientation)
{
    _orientation = orientation;
}

int Player::getOrientation() const
{
    return _orientation;
}

void Player::setLevel(int level)
{
    _anim.y = 660 - (((level - 1) * 22) * 4);
    _level = level;
}

void Player::isIncanting(bool isIncanting)
{
    _isIncanting = isIncanting;
}

int Player::getLevel() const
{
    return _level;
}

Rectangle Player::getSettings() const
{
    return _settings;
}

Rectangle Player::getAnim() const
{
    return _anim;
}

void Player::draw(Texture2D texture, Texture2D incantation)
{
    if (_orientation == 0) {
        _anim.x = (16 * 5);
    }
    if (_orientation == 1) {
        _anim.x = (16 * 3);
    }
    if (_orientation == 2) {
        _anim.x = 16;
    }
    if (_orientation == 3) {
        _anim.x = (16 * 7);
    }

    if (_isIncanting == true) {
        _incantation.update();
        _incantation.draw(incantation);
    }
    // std::cout << "settings.y " << _settings.y;
    // std::cout << " settings.x " << _settings.x << std::endl;
    DrawTexturePro(texture, _anim, _settings, (Vector2) {0, 0}, 0, WHITE);
}

void Player::drawAtPosition(Texture2D texture)
{
    if (_orientation == 0) {
        _anim.x = (16 * 5);
    }
    if (_orientation == 1) {
        _anim.x = (16 * 3);
    }
    if (_orientation == 2) {
        _anim.x = 16;
    }
    if (_orientation == 3) {
        _anim.x = (16 * 7);
    }
    // if (_isIncanting == true) {
    //     _incantation.update();
    //     _incantation.draw(incantation);
    // }
    // std::cout << "settings.y " << _settings.y;
    // std::cout << " settings.x " << _settings.x << std::endl;
    Rectangle tmpSettings = _settings;
    tmpSettings.x = 1520;
    tmpSettings.y = 900;
    tmpSettings.width *= 2;
    tmpSettings.height *= 2;
    DrawTexturePro(texture, _anim, tmpSettings, (Vector2) {0, 0}, 0, WHITE);
}