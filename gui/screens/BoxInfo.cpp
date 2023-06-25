/*
** EPITECH PROJECT, 2022
** B-YEP-400-MAR-4-1-zappy-thibaut.tran
** File description:
** BoxInfo.cpp
*/

#include "BoxInfo.hpp"

BoxInfo::BoxInfo()
{
    _box = LoadTexture("gui/assets/boxInfo.png");
    _font = LoadFont("gui/assets/fonts/font1.ttf");
}

BoxInfo::~BoxInfo()
{
}

void BoxInfo::setItems(std::vector<AItem *> items)
{
    _items = items;
}

void BoxInfo::draw()
{
    Vector2 position = (Vector2) {-100, 1080 - 250};
    DrawTextureEx(_box, position, 0.0f, 1.0f, WHITE);
    std::vector<std::string> names;
    std::vector<size_t> positions;
    std::vector<size_t> counters;
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
        Vector2 position = (Vector2) {(float) (i * 100), (float) (1080 - 200)};
        DrawTextureEx(_items.at(positions.at(i))->getTexture(), position, 0.0f, 2.5f, WHITE);
        Vector2 positionText = (Vector2) {(float) (i * 100 + 70), (float) (1080 - 185)};
        DrawTextEx(_font, std::to_string(counters.at(i)).c_str(), positionText, 20, 20, BROWN);
    }
}