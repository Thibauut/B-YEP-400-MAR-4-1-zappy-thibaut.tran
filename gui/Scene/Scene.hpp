/*
** EPITECH PROJECT, 2022
** B-YEP-400-MAR-4-1-zappy-thibaut.tran
** File description:
** Scene.hpp
*/

#pragma once
#include "../Player/Egg.hpp"
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
        void removePlayer(int pos);
        void drawPlayers(Texture2D model, Texture2D incantation);
        void setPositionPlayer(std::string id, Vector2 position);
        std::vector<AItem *> getInventoryPlayer(std::string id);
        void setInventoryPlayer(std::string id, std::vector<AItem *> inventory);
        void setOrientationPlayer(std::string id, int orientation);
        void setLevelPlayer(std::string id, int level);
        void isIncantingPlayer(std::string id, bool isIncanting);
        std::string isPlayerAtPosition(Vector2 position);
        int getPlayerById(std::string id);
        std::string getPlayerName(size_t pos);

        std::vector<Egg> getEggs();
        void setEggs(std::vector<Egg> eggs);
        void addEgg(Egg &egg);
        void removeEgg(int eggPos);
        void drawEggs(Texture2D model);
        void setPositionEgg(std::string id, Vector2 position);
        int getEggById(std::string id);

        void setBase(Texture2D base);
        Texture2D getBase() const;
        void drawBase() const;


    private:
        std::vector<Player> _players;
        std::vector<Egg> _eggs;
        std::mutex _mutexPlayer;
        std::mutex _mutexEgg;
        Texture _base;

};