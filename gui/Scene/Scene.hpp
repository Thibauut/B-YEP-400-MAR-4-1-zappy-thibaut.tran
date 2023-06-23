/*
** EPITECH PROJECT, 2022
** B-YEP-400-MAR-4-1-zappy-thibaut.tran
** File description:
** Scene.hpp
*/

#pragma once
#include "../Player/Player.hpp"
#include <vector>
#include <mutex>
#include "../Utils/Global.hpp"

class Scene {
    public:
        Scene();
        ~Scene();

        std::vector <Player> getPlayers();
        void setPlayers(std::vector<Player> players);
        void addPlayer(Player &player);
        void removePlayer(Player &player);
        void drawPlayers(Texture2D model);

        void setBase(Texture2D base);
        Texture2D getBase() const;
        void drawBase() const;

        int getPlayerById(std::string id) const;

    private:
        std::vector<Player> _players;
        std::mutex _mutex;
        Texture _base;

};