/*
** EPITECH PROJECT, 2022
** B-YEP-400-MAR-4-1-zappy-thibaut.tran
** File description:
** IItem.hpp
*/

#pragma once

#include "../Utils/Global.hpp"
#include "../Anim/Anim.hpp"

class IItem {
    public:
        virtual ~IItem() = default;

        virtual void drawItem() = 0;
        virtual void setItemPosition(Vector2 position) = 0;
        virtual Vector2 getItemPosition() const = 0;
        virtual std::string getName() const = 0;
        virtual Texture2D getTexture() const = 0;
        virtual int getId() const = 0;
};