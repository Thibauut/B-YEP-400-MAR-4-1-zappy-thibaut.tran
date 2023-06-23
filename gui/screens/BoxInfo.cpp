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
    for (size_t i = 0; i < _items.size(); i++) {
        Vector2 position = (Vector2) {(float) (i * 70), (float) (1080 - 200)};
        DrawTextureEx(_items[i]->getTexture(), position, 0.0f, 2.5f, WHITE);
    }
}