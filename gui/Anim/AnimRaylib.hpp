/*
** EPITECH PROJECT, 2022
** B-YEP-400-MAR-4-1-zappy-thibaut.tran
** File description:
** Anim.hpp
*/

#pragma once

#include "../Utils/Global.hpp"

class AnimRaylib {
    public:
        AnimRaylib();
        ~AnimRaylib();

        void run();
        void update();
        void draw();

    private:
        int logoPositionX = screenWidth/2 - 128;
        int logoPositionY = screenHeight/2 - 128;

        int framesCounter = 0;
        int lettersCount = 0;

        int topSideRecWidth = 16;
        int leftSideRecHeight = 16;

        int bottomSideRecWidth = 16;
        int rightSideRecHeight = 16;

        int state = 0;                  // Tracking animation states (State Machine)
        float alpha = 1.0f;             // Useful for fading
};