/*
** EPITECH PROJECT, 2022
** B-YEP-400-MAR-4-1-zappy-thibaut.tran
** File description:
** Linemate.hpp
*/

#pragma once

#include "AItem.hpp"

class Linemate : public AItem {
    public:
        Linemate()
        {
            _name = "linemate";
            _texture = LoadTexture("gui/assets/ore/Icon1.png");
        };

        Linemate(Vector2 position) {
            _name = "linemate";
            _texture = LoadTexture("gui/assets/ore/Icon1.png");
            _position = position;
        };

        ~Linemate() = default;

        void drawItem() override {
            _position.x = _position.x + 10;
            _position.y = _position.y + 10;
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
            return "linemate";
        };

        Texture2D getTexture() const {
            return _texture;
        };

    private:
        std::string _name;
        Vector2 _position;
        Texture2D _texture;
        Anim _anim;
};