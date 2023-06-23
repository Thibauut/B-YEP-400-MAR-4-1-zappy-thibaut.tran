/*
** EPITECH PROJECT, 2022
** B-YEP-400-MAR-4-1-zappy-thibaut.tran
** File description:
** Phiras.hpp
*/

#pragma once

#include "AItem.hpp"

class Phiras : public AItem {
    public:
        Phiras() {
            _name = "phiras";
            _texture = LoadTexture("gui/assets/ore/Icon5.png");
        };

        Phiras(Vector2 position) {
            _name = "phiras";
            _texture = LoadTexture("gui/assets/ore/Icon5.png");
            _position = position;
        };

        ~Phiras() = default;

        void drawItem() override {
            _position.x = _position.x + 15;
            _position.y = _position.y + 15;
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
            return "phiras";
        };

        Texture2D getTexture() const {
            return _texture;
        };

    private:
        std::string _name;
        Vector2 _position;
        Texture2D _texture;
};