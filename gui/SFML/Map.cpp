/*
** EPITECH PROJECT, 2022
** B-YEP-400-MAR-4-1-zappy-thibaut.tran
** File description:
** Map.cpp
*/

#define STB_IMAGE_IMPLEMENTATION
#include <../../dependencies/stb_image.h>

int width, height, channels;
unsigned char* image = stbi_load(".png", &width, &height, &channels, 0);
