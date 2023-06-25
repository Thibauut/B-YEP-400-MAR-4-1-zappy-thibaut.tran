/*
** EPITECH PROJECT, 2022
** B-YEP-400-MAR-4-1-zappy-thibaut.tran
** File description:
** Tile.hpp
*/

#pragma once

#include "../items/AItem.hpp"
#include "../screens/BoxInfo.hpp"
#include <mutex>

class Tile {
    public:
        Tile();
        Tile(Vector2 position, std::vector<AItem*> items, int currentTile);
        ~Tile();

        void drawTile(int startX, int startY, int spriteSpacingX, int spriteSpacingY, int renderIndex);
        void drawTiles(int renderIndex);

        // Setters
        void setTilePosition(Vector2 position);
        void setTileItems(std::vector<AItem*> items);
        bool CheckTileHover(BoxInfo& boxInfo, BoxPlayer& boxPlayer, Camera2D camera);

        // Getters
        Vector2 getTilePosition() const;
        std::vector<AItem*> getTileItems();
        void setTexture(Texture2D &texture);

        void removeItem(int item);

    private:
        Vector2 _position;
        Texture2D _texture;
        bool _isHovered;
        Rectangle _rec;
        std::vector<AItem*> _items;
        int _currentTile;
};