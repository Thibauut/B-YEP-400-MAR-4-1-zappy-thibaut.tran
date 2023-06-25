/*
** EPITECH PROJECT, 2022
** B-YEP-400-MAR-4-1-zappy-thibaut.tran
** File description:
** Player.hpp
*/

#pragma once
#include <string>
#include <raylib.h>
#include "../Utils/Global.hpp"
#include "../Anim/Anim.hpp"

class Player {
    public:
        Player();
        Player(std::string id);
        ~Player();

        void setName(std::string id);
        std::string getName() const;

        void setPosition(Vector2 pos);
        Vector2 getPosition() const;

        void setOrientation(int orientation);
        int getOrientation() const;

        void setLevel(int level);
        int getLevel() const;


        void isIncanting(bool isIncanting);

        Rectangle getSettings() const;

        Rectangle getAnim() const;

        // void setInventory(std::vector<AItem>);
        // std::vector<AItem> getInventory() const;

        void draw(Texture texture, Texture2D incantation);

    private:
        std::string _id;
        Vector2 _pos;
        int _orientation;
        int _level;
        Rectangle _anim;
        Rectangle _settings;
        Texture2D _player;

        bool _isIncanting;
        Anim _incantation;
        // std::vector<AItem> _inventory;
};