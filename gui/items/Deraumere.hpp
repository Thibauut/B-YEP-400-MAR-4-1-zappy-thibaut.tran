/*
** EPITECH PROJECT, 2022
** B-YEP-400-MAR-4-1-zappy-thibaut.tran
** File description:
** Deraumere.hpp
*/

#pragma once

#include "AItem.hpp"

class Deraumere : public AItem {
    public:
        Deraumere() {
            _name = "deraumere";
            _texture = LoadTexture("gui/assets/ore/Icon2.png");
        };

        Deraumere(Vector2 position) {
            _name = "deraumere";
            _texture = LoadTexture("gui/assets/ore/Icon2.png");
            _position = position;
        };

        ~Deraumere() = default;

        void drawItem() override {
            _position.x = _position.x + 8;
            _position.y = _position.y + 8;
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
            return "deraumere";
        };

        Texture2D getTexture() const {
            return _texture;
        };

        int getId() const {
            return 2;
        }

    private:
        std::string _name;
        Vector2 _position;
        Texture2D _texture;
        int _id;
};