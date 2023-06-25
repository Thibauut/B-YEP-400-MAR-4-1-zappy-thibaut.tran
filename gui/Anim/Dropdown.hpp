/*
** EPITECH PROJECT, 2022
** B-YEP-400-MAR-4-1-zappy-thibaut.tran
** File description:
** Dropdown.hpp
*/

#pragma once

#include <raylib.h>

class DropdownMenu {
    public:
        DropdownMenu(const Vector2& position, const Vector2& size, const Color& color)
            : position(position), size(size), color(color), isOpen(false), animationSpeed(5.0f)
        {
            dropdownRect = { position.x, position.y, 0, size.y };
            targetWidth = size.x;
        }

        inline float Clamp(float value, float min, float max) {
            if (value < min) {
                return min;
            } else if (value > max) {
                return max;
            }
            return value;
        }


        bool update() {
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && !isOpen && CheckCollisionPointRec(GetMousePosition(), { position.x, position.y, 32, 32}) == true)
            {
                isOpen = true;
            }
            else if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && isOpen && CheckCollisionPointRec(GetMousePosition(), { position.x, position.y, size.x, size.y}) == false)
            {
                isOpen = false;
            }

            float speed = targetWidth * GetFrameTime() * animationSpeed;
            dropdownRect.width = isOpen ? (dropdownRect.width + speed) : (dropdownRect.width - speed);
            dropdownRect.width = Clamp(dropdownRect.width, 0, targetWidth);
            if (dropdownRect.width == targetWidth)
                return true;
            return false;
        }

        void draw(Texture2D texture)
        {
            DrawTextureEx(texture, position, 0.0f, 2.0f, WHITE);
            DrawRectangleRec(dropdownRect, color);
        }

    private:
        Vector2 position;
        Vector2 size;
        Color color;
        Rectangle dropdownRect;
        bool isOpen;
        float animationSpeed;
        float targetWidth;
};
