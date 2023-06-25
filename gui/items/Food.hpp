/*
** EPITECH PROJECT, 2022
** B-YEP-400-MAR-4-1-zappy-thibaut.tran
** File description:
** Food.hpp
*/

#pragma once

#include "AItem.hpp"

class Food : public AItem {
    public:
        Food() {
            _name = "food";
            _texture = LoadTexture("gui/assets/ore/food.png");
        };
        Food(Vector2 position) {
            _name = "food";
            _texture = LoadTexture("gui/assets/ore/food.png");
            _position = position;
        };
        ~Food() = default;

        void drawItem() override {
            _position.x = _position.x + 15;
            _position.y = _position.y + 3;
            DrawTextureEx(_texture, _position, 0, 1.0f, WHITE);
            // _anim.draw(_texture);
        };
        void setItemPosition(Vector2 position) {
            _position = position;
        };
        Vector2 getItemPosition() const {
            return _position;
        };
        std::string getName() const {
            return "food";
        };

        Texture2D getTexture() const {
            return _texture;
        };

        int getId() const {
            return 0;
        }

    private:
        std::string _name;
        Vector2 _position;
        Texture2D _texture;
};