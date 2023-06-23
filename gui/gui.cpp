/*
** EPITECH PROJECT, 2022
** Zappy
** File description:
** gui.cpp
*/

#include <iostream>
#include <string.h>
#include <raylib.h>
#include "Map/Map.hpp"
#include "screens/LoadingScreen.hpp"
#include "screens/BoxInfo.hpp"
#include "Scene/Scene.hpp"
#include <condition_variable>
#include <mutex>
#include "Anim/AnimRaylib.hpp"
#include "Bar/BarTime.hpp"

#include <atomic>

using namespace std;

atomic<bool> dataLoaded = false;
void LoadDataThread();
atomic<int> dataProgress = 0;

Map myMap;
Scene scene;
bool verifLoad = false;
TimeBar timeBar;

// Camera camera = { 0 };

using json = nlohmann::json;

Tile parseResponse(json parsedData, int x, int y, int count)
{

    Vector2 position = {(float)x, (float)y};
    std::vector<AItem*> items;
    for (int i = 0; i < (int)parsedData["food"]; i++)
            items.push_back(new Food(position));
    for (int i = 0; i < (int)parsedData["linemate"]; i++)
            items.push_back(new Linemate(position));
    for (int i = 0; i < (int)parsedData["deraumere"]; i++)
            items.push_back(new Deraumere(position));
    for (int i = 0; i < (int)parsedData["sibur"]; i++)
            items.push_back(new Sibur(position));
    for (int i = 0; i < (int)parsedData["mendiane"]; i++)
            items.push_back(new Mendiane(position));
    for (int i = 0; i < (int)parsedData["phiras"]; i++)
            items.push_back(new Phiras(position));
    for (int i = 0; i < (int)parsedData["thystame"]; i++)
            items.push_back(new Thystame(position));
    return Tile(position, items, count);
}

void checkOnServer(PlayerState &state)
{
    Client client(ip, port);
    std::string response;
    while (1) {
        response = client.catchResponse();
        std::cout << "checkOnServer: " << response << std::endl;
        if (response.find("pnw") != std::string::npos) {
            json parsedData = json::parse(response);
            state.id = parsedData["id"];

            std::cout << "New Player - id=" << state.id << std::endl;
            Player player(state.id);
            float x = parsedData["x"];
            float y = parsedData["y"];
            int orientation = parsedData["o"];
            int level = parsedData["level"];
            player.setOrientation(orientation);
            player.setLevel(level);
            player.setPosition(Vector2{x, y});
            scene.addPlayer(player);
            std::cout << "Player created !!!" << std::endl;
        }
        if (response.find("pgt") != std::string::npos) {
            json parsedData = json::parse(response);
            std::string id = parsedData["id"];
            int player = scene.getPlayerById(id);
            int x = scene.getPlayers()[player].getPosition().x;
            int y = scene.getPlayers()[player].getPosition().y;
            int i = 0;
            for (; y > 0; y--) {
                for (int r = x; r > 0; r--) {
                    i += 1;
                }
            }
            // myMap._map[i].;
        }
        // if (response.find("pdr") != std::string::npos) {
        //     std::cout << response << std::endl;
        //     json parsedData = json::parse(response);

        //     // scene.getPlayerById(parsedData["id"]).dropResource(parsedData["res"]);
        // }
    }
}

void resfreshInfo()
{
    Client client(ip, port);
    std::string response;
    while (1) {
        std::vector<Player> players(scene.getPlayers());
        std::cout << "size:" << players.size() << std::endl;
        for (size_t i = 0; i < players.size(); i++) {
            std::cout << "ppo " << players[i].getName() << std::endl;
            client.sendRequestId("ppo", players[i].getName());
            response = client.catchResponse();
            std::cout << response << "END" << std::endl;
            if (response != "ko\n" || response != "ko") {
                json parsedData = json::parse(response);
                float x = parsedData["x"];
                float y = parsedData["y"];
                int orientation = parsedData["o"];
                players[i].setPosition(Vector2{x, y});
                players[i].setOrientation(orientation);
            }
            // std::this_thread::sleep_for(std::chrono::seconds(3));
            // std::cout << "plv " << players[i].getName() << std::endl;
            // client.sendRequestId("plv", players[i].getName());
            // response = client.catchResponse();
            // std::cout << response << std::endl;
            // if (response != "ko\n" || response != "ko") {
            //     json parsedData2 = json::parse(response);
            //     // int level = parsedData["level"];
            //     // players[i].setLevel(level);
            // }
        }
        scene.setPlayers(players);
        // std::cout << "sgt" << std::endl;
        // client.sendRequest("sgt\n");
        // response = client.catchResponse();
        // std::cout << response << std::endl;
        // if (response != "ko\n" || response != "ko") {
        //     json parsedData = json::parse(response);
        //     int time = parsedData["sgt"];
        //     // scene.setTime(time);
        // }
        if (timeBar._tmpTime != timeBar._time) {
            timeBar._tmpTime = timeBar._time;
            std::string message = "sst " + std::to_string(timeBar._time) + "\n";
            client.sendRequest(message);
            response = client.catchResponse();
            std::cout << response << std::endl;
        }
        std::this_thread::sleep_for(std::chrono::seconds(2));
    }
}

void createMap(LoadingState &state)
{
    Client client(ip, port);
    // LoadingState *state = (LoadingState *) arg;
    state.progress = 0;
    state.loaded = false;
    std::string response = client.catchResponse();
    // for (int i = 1; i < width_map; i++) {
    //     for (int j = 1; j < height_map; j++) {
    //         std::string request = "bct ";
    //         request = request + std::to_string(i) + " " + std::to_string(j) + "\n";
    //         client.sendRequest(request);
    //         std::cout << "Send " << request << " command to server..." << std::endl;
    //         response = client.catchResponse();
    //         std::cout << response << std::endl;
    //         json parsedData = json::parse(response);
    //         std::cout << "x: " << parsedData["x"] << ", y: " << parsedData["y"] << std::endl;

    //         int x = int(parsedData["x"]);
    //         int y = int(parsedData["y"]);
    //         Tile tile = parseResponse(parsedData, x, y);

    //         myMap.push(tile);
    //         count += 1;
    //         state.progress = ((width_map - 1) * (height_map - 1));
    //         state.progress = count / state.progress * 100;
    //     }
    // }
    // myMap.setMap(map._map);
    state.loaded = true;
    dataLoaded = true;
    pthread_exit(NULL);
}

// float cameraX = 0.0f;  // Position de la caméra sur l'axe X
// float cameraY = 3.0f;  // Position de la caméra sur l'axe Y
// float cameraZ = 0.0f;  // Position de la caméra sur l'axe Z

void checkArguments(int argc, char** argv) {
    if (argc != 3) {
        std::cerr << "Usage: ./zappy_gui [ip] [port]" << std::endl;
        exit(84);
    }
    ip = argv[1];
    port = atoi(argv[2]);
}

int main(int argc, char** argv) {
    checkArguments(argc, argv);
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    Client client(ip, port);
    std::string response;
    // response = client.catchResponse();
    client.sendRequest("msz\n");
    std::cout << "Send msz command to server..." << std::endl;
    response = client.catchResponse();
    if (response == "") {
        std::cout << "Retry..." << std::endl;
        client.sendRequest("msz\n");
        response = client.catchResponse();
    }
    json parsedData = json::parse(response);
    width_map = parsedData["x"];
    height_map = parsedData["y"];
    std::cout << "Response: " << response << std::endl;
    std::cout << "x: " << width_map << ", y: " << height_map << std::endl;
    InitWindow(screenWidth, screenHeight, "Zappy");
    timeBar.init();
    LoadingState loadingState = { 0, false, &client, myMap };
    std::thread loadingThread(createMap, std::ref(loadingState));

    PlayerState playerState;
    playerState.client = &client;
    std::thread checkingThread(checkOnServer, std::ref(playerState));

    std::thread refreshThread(resfreshInfo);

    Texture2D basePlayer = LoadTexture("gui/assets/player/players.png");

    LoadingScreen loadScreen;
    // camera.position = (Vector2){ 50.0f, 10.0f, 10.0f };
    // camera.target = (Vector2){ 0.0f, 10.0f, 0.0f };
    // camera.up = (Vector2){ 0.0f, 1.0f, 0.0f };
    // camera.fovy = 45.0f;
    // camera.projection = CAMERA_PERSPECTIVE;

    // unsigned int animsCount = 1;
    // unsigned int animIndex = 0;
    // unsigned int animCurrentFrame = 0;

    // Model title = LoadModel("gui/models/title.glb");
    // Vector2 rotation = { 100.0f, 0.0f, 0.0f };
    // Vector2 scale = { 1.0f, 1.0f, 1.0f };
    // Vector2 titlePos = { 0.0f, 130.0f, 0.0f };

    // DisableCursor();
    // float modelRotation = 90.0f;
    // float rotationSpeed = 20.0f;

    Vector2 tmpMousePos = GetMousePosition();

    enum { STATE_WAITING, STATE_LOADING, STATE_FINISHED } state = STATE_WAITING;

    // loadingState.client = &client;
    // loadingState.map = myMap;
    // pthread_t loadingThread;
    int count = 0;
    std::cout << "width_MAP: " << width_map << ", height_MAP: " << height_map << std::endl;

    for (int j = 1; j < height_map; j++) {
        for (int i = 1; i < width_map; i++) {
            std::string request = "bct ";
            request = request + std::to_string(i) + " " + std::to_string(j) + "\n";
            client.sendRequest(request);
            std::cout << "Send " << request << " command to server..." << std::endl;
            response = client.catchResponse();
            std::cout << response << std::endl;
            json parsedData = json::parse(response);
            std::cout << "x: " << parsedData["x"] << ", y: " << parsedData["y"] << std::endl;

            int x = int(parsedData["x"]);
            int y = int(parsedData["y"]);
            Tile tile = parseResponse(parsedData, x, y, count);
            count += 1;
            myMap.push(tile);
        }
        std::cout << "count: " << count << std::endl;
    }

    loadingState.loaded = false;
    SetTargetFPS(60);
    BoxInfo boxInfo;
    // AnimRaylerun();
    // UpdateCamera(&camera, CAMERA_CUSTOM);

    Texture2D backgroundImg = LoadTexture("gui/models/loadingScreen.png");
    Texture2D baseTexture = LoadTexture("gui/assets/background.png");

    Rectangle backgroundRect;
    backgroundRect.x = 0;
    backgroundRect.y = 0;
    backgroundRect.width = screenWidth;
    backgroundRect.height = screenHeight;

    scene.setBase(baseTexture);
    // Texture2D testPlayer = LoadTexture("gui/assets/player/players.png");

    while (!WindowShouldClose()) {
        switch (state)
        {
            case STATE_WAITING:
            {
                if (IsKeyPressed(KEY_ENTER))
                {
                    state = STATE_LOADING;
                }
            } break;
            case STATE_LOADING:
            {
                state = STATE_FINISHED;
                break;
                Vector2 mousePos = GetMousePosition();
                if (mousePos.x != tmpMousePos.x) {
                    // modelRotation += (mousePos.x - tmpMousePos.x) * 0.5f;
                    tmpMousePos = mousePos;
                } else {
                    // modelRotation += rotationSpeed * GetFrameTime();
                }
                if (dataLoaded)
                {
                    state = STATE_FINISHED;
                    // loadingThread.join();
                }
            } break;
            case STATE_FINISHED:
            {
                for (auto &tile: myMap._map) {
                    tile.CheckTileHover(boxInfo);
                }
                timeBar.checkMouseClick();
            } break;
            default: break;
        }

        // if(IsKeyDown(KEY_SPACE)) {
        //     // UpdateModelAnimation(model, anims[0], animCurrentFrame);
        //     UpdateModelAnimation(testPlayer, animPlayer[0], animCurrentFrame);
        //     animCurrentFrame = (animCurrentFrame + 1);
        //     // if (animCurrentFrame > animPlayer[0].frameCount) animCurrentFrame = 0;
        // }
        // UpdateCamera(&camera, CAMERA_THIRD_PERSON);
        // if (IsKeyPressed(KEY_UP)) animIndex = (animIndex + 1)%animsCount;
        // else if (IsKeyPressed(KEY_DOWN)) animIndex = (animIndex + animsCount - 1)%animsCount;
        BeginDrawing();
            ClearBackground(RAYWHITE);

            switch (state) {
            case STATE_WAITING:
            {
                DrawText("PRESS ENTER to START LOADING DATA", 150, 170, 20, DARKGRAY);
            } break;
            case STATE_LOADING:
            {
                DrawTexture(backgroundImg, backgroundRect.x, backgroundRect.y, WHITE);
                // BeginMode3D(camera);
                //     camera.position = (Vector2){ 0.0f, 10.0f, 10.0f };
                //     camera.target = (Vector2){ 0.0f, 70.0f, 0.0f };
                //     DrawModelEx(title, titlePos, rotation, modelRotation,  scale, DARKBLUE);
                // EndMode3D();
                loadScreen.draw(loadingState);
            } break;
            case STATE_FINISHED:
            {
                // DrawGrid(width_map, 20.0f);
                DrawTexture(scene.getBase(), 0, 0, WHITE);
                myMap.drawMap();
                scene.drawPlayers(basePlayer);
                if (isDrawingBox) {
                    boxInfo.draw();
                }
                for (size_t i = 0; i < scene.getPlayers().size(); i++) {
                    DrawText(scene.getPlayers()[i].getName().c_str(), 10, 10 + 20 * i, 20, GREEN);
                }
                timeBar.draw();
            } break;
            default: break;
        }
        EndDrawing();
    }

    CloseWindow();
    // loadingThread.join();
    checkingThread.join();
    refreshThread.join();
    return (0);
}