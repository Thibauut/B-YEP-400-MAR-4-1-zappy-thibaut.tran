/*
** EPITECH PROJECT, 2022
** B-YEP-400-MAR-4-1-zappy-thibaut.tran
** File description:
** BoxInfo.hpp
*/

#pragma once
#include "../Utils/Global.hpp"
#include "../items/AItem.hpp"

class BoxInfo {
    public:
        BoxInfo();
        ~BoxInfo();

        void setItems(std::vector<AItem *> items);
        void draw();

    private:
        Texture2D _box;
        std::vector<AItem *> _items;
};