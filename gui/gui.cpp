/*
** EPITECH PROJECT, 2022
** Zappy
** File description:
** gui.cpp
*/

#include <iostream>
#include <GLFW/glfw3.h>
#include <GL/glut.h>
#include "requests/Client.hpp"
#include "Utils/Global.hpp"
#include "../dependencies/json.hpp"

using json = nlohmann::json;

float cameraX = 0.0f;  // Position de la caméra sur l'axe X
float cameraY = 3.0f;  // Position de la caméra sur l'axe Y
float cameraZ = 0.0f;  // Position de la caméra sur l'axe Z

void renderScene()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(cameraX, cameraY, cameraZ,  // Position de la caméra
              cameraX, cameraY, cameraZ - 1.0,  // Point de regard de la caméra
              0.0, 1.0, 0.0);  // Vecteur d'orientation de la caméra

    glColor3f(1.0, 1.0, 1.0);  // Couleur des lignes

    glTranslatef((((width_map * 10) / 2) * (-1)), 0.0, (((height_map * 10) / 2) * (-1)));  // Déplacer le quadrillage au centre
    // Dessiner les lignes horizontales du quadrillage
    for (int i = 0; i <= width_map * 10; i += 10) {
        glBegin(GL_LINES);
        glVertex3f(0, 0, i);
        glVertex3f(width_map * 10, 0, i);
        glEnd();
    }

    // Dessiner les lignes verticales du quadrillage
    for (int i = 0; i <= height_map * 10; i += 10) {
        glBegin(GL_LINES);
        glVertex3f(i, 0, 0);
        glVertex3f(i, 0, height_map * 10);
        glEnd();
    }

    glutSwapBuffers();
}

void specialKeyPressed(int key, int x, int y) {
    const float cameraSpeed = 1.0f;  // Vitesse de déplacement de la caméra
    switch (key) {
        case GLUT_KEY_UP:
            cameraY += cameraSpeed;  // Déplacer la caméra vers l'avant
            break;
        case GLUT_KEY_DOWN:
            if (cameraY < 1) cameraY = 1;
            cameraY -= cameraSpeed;  // Déplacer la caméra vers l'arrière
            break;
        case GLUT_KEY_LEFT:
            cameraX -= cameraSpeed;  // Déplacer la caméra vers la gauche
            break;
        case GLUT_KEY_RIGHT:
            cameraX += cameraSpeed;  // Déplacer la caméra vers la droite
            break;
        case GLUT_KEY_PAGE_UP:
            cameraZ -= cameraSpeed;  // Déplacer la caméra vers la gauche
            break;
        case GLUT_KEY_PAGE_DOWN:
            cameraZ += cameraSpeed;  // Déplacer la caméra vers la droite
            break;
    }

    glutPostRedisplay();  // Redessiner la scène
}

void checkArguments(int argc, char** argv) {
    if (argc != 3) {
        std::cerr << "Usage: ./zappy_gui [ip] [port]" << std::endl;
        exit(84);
    }
    ip = argv[1];
    port = atoi(argv[2]);
}

int main(int argc, char** argv) {
    // init
    checkArguments(argc, argv);
    Client client(ip, port);
    std::string response = client.catchResponse();
    std::cout << "response: " << response << std::endl;
    client.sendRequest("GUI\n");
    client.sendRequest("msz\n");
    std::cout << "Send msz command to server..." << std::endl;
    response = client.catchResponse();
    json parsedData = json::parse(response);
    width_map = parsedData["x"];
    height_map = parsedData["y"];
    std::cout << "x: " << width_map << ", y: " << height_map << std::endl;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 800);
    glutCreateWindow("Zappy GUI");

    glEnable(GL_DEPTH_TEST);  // Activer le test de profondeur

    glClearColor(0.0, 0.0, 0.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, 1.0, 0.1, 1000.0);  // Paramètres de la projection

    glutDisplayFunc(renderScene);
    glutSpecialFunc(specialKeyPressed);  // Gérer les touches spéciales

    glutMainLoop();

    return (0);
}
