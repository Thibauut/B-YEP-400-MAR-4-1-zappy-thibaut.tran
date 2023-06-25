/*
** EPITECH PROJECT, 2022
** B-YEP-400-MAR-4-1-zappy-thibaut.tran
** File description:
** Tile.cpp
*/

#include "Tile.hpp"
#include <iostream>

Tile::Tile()
{
}

Tile::Tile(Vector2 position, std::vector<AItem*> items, int currentTile)
{
    _position = position;
    _items = items;
    int rand = std::rand() % 3 + 1;
    std::string path = "gui/assets/ground/grass" + std::to_string(rand) + ".png";
    _texture = LoadTexture(path.c_str());
    _isHovered = false;
    _currentTile = currentTile;
    _rec.x = (screenWidth / 2) + (_currentTile % (width_map)) * (60 / 2) - (_currentTile / (width_map)) * (60 / 2);
    _rec.y = (_currentTile % (height_map)) * (50 / 2) + (_currentTile / (height_map)) * (50 / 2);
    _rec.width = 130 / 2;
    _rec.height = 130 / 2;
}

Tile::~Tile()
{}

void Tile::drawTile(int startX, int startY, int spriteSpacingX, int spriteSpacingY, int renderIndex)
{
    float posX = startX + (renderIndex % (width_map)) * spriteSpacingX - (renderIndex / (width_map)) * spriteSpacingX;
    float posY = startY + (renderIndex % (height_map)) * spriteSpacingY + (renderIndex / (height_map)) * spriteSpacingY;
    Vector2 pos = {posX, posY};
    if (_isHovered) {
        pos.y -= 10;
        DrawTextureEx(_texture, pos, 0.0f, 0.5f, GREEN);
    } else {
        DrawTextureEx(_texture, pos, 0.0f, 0.5f, WHITE);
    }
    // drawTiles(renderIndex);
}

void Tile::CheckTileHover(BoxInfo &boxInfo, Camera2D camera)
{
    Vector2 mouse = GetMousePosition();
    mouse.x /= camera.zoom;
    mouse.y /= camera.zoom;
    mouse.x -= camera.offset.x;
    mouse.y -= camera.offset.y;
    if (CheckCollisionPointRec(mouse, _rec) && canHover == true) {
        _isHovered = true;
        canHover = false;
    } else if (!CheckCollisionPointRec(mouse, _rec) && _isHovered == true) {
        _isHovered = false;
        canHover = true;
    }

    if (_isHovered) {
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            if (_items.size() == 0) {
                isDrawingBox = false;
                return;
            }
            isDrawingBox = true;
            boxInfo.setItems(_items);
        }
    }
}

void Tile::drawTiles(int renderIndex)
{
    for (auto &item : _items) {
        Vector2 pos;
        pos.x = (screenWidth / 2) + (renderIndex % (width_map)) * (60 / 2) - (renderIndex / (width_map)) * (60 / 2);
        pos.y = (renderIndex % (height_map)) * (50 / 2) + (renderIndex / (height_map)) * (50 / 2);
        if (_isHovered) {
            pos.y -= 10;
        }
        item->setItemPosition(pos);
        item->drawItem();
    }
}

void Tile::removeItem(int item)
{
    for (size_t i = 0; i < _items.size(); i++) {
        if (_items.at(i)->getId() == item) {
            _items.erase(_items.begin() + i);
            return;
        }
    }
}

void Tile::setTexture(Texture &texture)
{
    _texture = texture;
}

void Tile::setTilePosition(Vector2 position)
{
    _position = position;
}

void Tile::setTileItems(std::vector<AItem *> items)
{
    _items = items;
}

Vector2 Tile::getTilePosition() const
{
    return _position;
}

std::vector<AItem *> Tile::getTileItems() const
{
    return _items;
}