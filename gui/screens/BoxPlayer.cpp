/*
** EPITECH PROJECT, 2022
** B-YEP-400-MAR-4-1-zappy-thibaut.tran
** File description:
** BoxPlayer.cpp
*/

#include "BoxPlayer.hpp"

BoxPlayer::BoxPlayer()
{
    _show = false;
}

BoxPlayer::~BoxPlayer()
{
}

void BoxPlayer::init()
{
    _box = LoadTexture("gui/assets/boxInfo.png");
    _font = LoadFont("gui/assets/fonts/font1.ttf");
}

void BoxPlayer::setItems(std::vector<AItem *> items)
{
    _items = items;
}

void BoxPlayer::draw(Player& player, Texture2D texturePlayer)
{
    std::unique_lock<std::mutex> lock(_mutex);
    if (!_show)
        return;
    Vector2 position = (Vector2) {1500, 1080 - 250};
    DrawTextureEx(_box, position, 0.0f, 1.0f, WHITE);
    std::vector<std::string> names;
    std::vector<int> positions;
    std::vector<int> counters;
    bool add = true;
    for (size_t i = 0; i < _items.size(); i++) {
        for (size_t j = 0; j < names.size(); j++) {
            if (names.at(j) == _items.at(i)->getName())
                add = false;
        }
        if (add == true) {
            names.push_back(_items.at(i)->getName());
            positions.push_back(i);
        }
        add = true;
    }
    for (size_t i = 0; i < names.size(); i++) {
        counters.push_back(0);
        for (size_t j = 0; j < _items.size(); j++) {
            if (names.at(i) == _items.at(j)->getName())
                counters.at(i)++;
            }
    }
    for (size_t i = 0; i < names.size(); i++) {
        Vector2 position = (Vector2) {(float) (i * 100 + 1600), (float) (1080 - 200)};
        DrawTextureEx(_items.at(positions.at(i))->getTexture(), position, 0.0f, 2.5f, WHITE);
        Vector2 positionText = (Vector2) {(float) (i * 100 + 1670), (float) (1080 - 185)};
        DrawTextEx(_font, std::to_string(counters.at(i)).c_str(), positionText, 20, 20, BROWN);
    }
    player.drawAtPosition(texturePlayer);
}

void BoxPlayer::setIdPlayer(std::string idPlayer)
{
    _idPlayer = idPlayer;
}

std::string BoxPlayer::getIdPlayer() const
{
    return _idPlayer;
}

bool BoxPlayer::isShowing()
{
    std::unique_lock<std::mutex> lock(_mutex);
    return _show;
}

void BoxPlayer::show()
{
    std::unique_lock<std::mutex> lock(_mutex);
    _show = true;
}

void BoxPlayer::hide()
{
    std::unique_lock<std::mutex> lock(_mutex);
    _show = false;
}