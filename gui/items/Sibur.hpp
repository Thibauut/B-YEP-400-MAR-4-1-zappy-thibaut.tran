/*
** EPITECH PROJECT, 2022
** B-YEP-400-MAR-4-1-zappy-thibaut.tran
** File description:
** Sibur.hpp
*/

#pragma once

#include "AItem.hpp"

class Sibur : public AItem {
    public:
        Sibur() {
            _name = "sibur";
            _texture = LoadTexture("gui/assets/ore/Icon3.png");
        };

        Sibur(Vector2 position) {
            _name = "sibur";
            _texture = LoadTexture("gui/assets/ore/Icon3.png");
            _position = position;
        };

        ~Sibur() = default;

        void drawItem() override {
            _position.x = _position.x + 13;
            _position.y = _position.y + 13;
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
            return "sibur";
        };

        Texture2D getTexture() const {
            return _texture;
        };

        int getId() const {
            return 3;
        }

    private:
        std::string _name;
        Vector2 _position;
        Model _model;
        Texture2D _texture;
};