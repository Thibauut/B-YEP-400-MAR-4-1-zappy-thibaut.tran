/*
** EPITECH PROJECT, 2022
** B-YEP-400-MAR-4-1-zappy-thibaut.tran
** File description:
** LoadingScreen.hpp
*/

#pragma once

#include "../Utils/Global.hpp"
#include "../Utils/ThreadTool.hpp"

class LoadingScreen
 {
    public:
        LoadingScreen();
        ~LoadingScreen();

        void draw(LoadingState state);
};