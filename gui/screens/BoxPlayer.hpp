/*
** EPITECH PROJECT, 2022
** B-YEP-400-MAR-4-1-zappy-thibaut.tran
** File description:
** BoxPlayer.hpp
*/

#pragma once
#include "../Utils/Global.hpp"
#include "../items/AItem.hpp"
#include "../Player/Player.hpp"
#include <mutex>

class BoxPlayer {
    public:
        BoxPlayer();
        ~BoxPlayer();

        void init();

        void setItems(std::vector<AItem *> items);
        void draw(Player &player, Texture2D texturePlayer);
        std::string getIdPlayer() const;
        void setIdPlayer(std::string idPlayer);

        bool isShowing();
        void show();
        void hide();

    private:
        Texture2D _box;
        Vector2 _position;
        std::vector<AItem *> _items;
        Font _font;
        bool _show;
        std::string _idPlayer;
        std::mutex _mutex;
};