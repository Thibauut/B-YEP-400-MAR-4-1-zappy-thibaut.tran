/*
** EPITECH PROJECT, 2022
** B-YEP-400-MAR-4-1-zappy-thibaut.tran
** File description:
** Item.hpp
*/

#pragma once

#include "IItem.hpp"

class AItem : public IItem {
    public:
        AItem();
        AItem(Vector2 position);
        virtual ~AItem();

        virtual void drawItem();
        virtual void setItemPosition(Vector2 position);
        virtual Vector2 getItemPosition() const;
        virtual std::string getName() const;
        virtual Texture2D getTexture() const;
        virtual int getId() const;

    private:
        std::string _name;
        Vector2 _position;
        Texture2D _texture;
};