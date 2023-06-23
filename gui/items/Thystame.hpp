/*
** EPITECH PROJECT, 2022
** B-YEP-400-MAR-4-1-zappy-thibaut.tran
** File description:
** Thystame.hpp
*/

#pragma once

#include "AItem.hpp"

class Thystame : public AItem {
    public:
        Thystame() {
            _name = "thystame";
            _texture = LoadTexture("gui/assets/ore/Icon6.png");
        };

        Thystame(Vector2 position) {
            _name = "thystame";
            _texture = LoadTexture("gui/assets/ore/Icon6.png");
            _position = position;
        };

        ~Thystame() = default;

        void drawItem() override {
            _position.x = _position.x + 3;
            _position.y = _position.y + 3;
            DrawTextureEx(_texture, _position, 0, 0.5f, WHITE);
            // _anim.draw(_texture);
        };

        void setItemPosition(Vector2 position) {
            _position = position;
        };

        Vector2 getItemPosition() const {
            return _position;
        };

        std::string getName() const {
            return "thystame";
        };

        Texture2D getTexture() const {
            return _texture;
        };

    private:
        std::string _name;
        Vector2 _position;
        Texture2D _texture;
};