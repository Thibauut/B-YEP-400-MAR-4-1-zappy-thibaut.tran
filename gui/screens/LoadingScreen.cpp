/*
** EPITECH PROJECT, 2022
** B-YEP-400-MAR-4-1-zappy-thibaut.tran
** File description:
** LoadingScreen.cpp
*/

#include "LoadingScreen.hpp"

LoadingScreen::LoadingScreen()
{
}

LoadingScreen::~LoadingScreen()
{
}

void LoadingScreen::draw(LoadingState state)
{
    DrawText("Loading models...", 200 - MeasureText("Loading models...", 30) / 2, screenHeight - 100 - 50, 30, WHITE);
    DrawRectangle(screenWidth / 2 - 100, screenHeight / 2 - 25, 200, 50, LIGHTGRAY);
    DrawRectangle(screenWidth / 2 - 100, screenHeight / 2 - 25, state.progress * 2, 50, SKYBLUE);
    std::string progress = std::to_string(state.progress);
    progress = progress + "%";
    const char *text = progress.c_str();
    DrawText(text, screenWidth / 2 - 15, screenHeight / 2 - 10, 20, DARKBLUE);
}