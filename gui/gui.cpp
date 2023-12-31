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
#include "Map/Cursor.hpp"
#include "Anim/Dropdown.hpp"

#include <atomic>

using namespace std;

atomic<bool> dataLoaded = false;
void LoadDataThread();
atomic<int> dataProgress = 0;

BoxPlayer boxPlayer;
Map myMap;
Scene scene;
bool verifLoad = false;
Bar timeBar;
Client client;

Camera2D camera = { 0 };

using json = nlohmann::json;

std::vector<AItem *> parseItems(json parsedData, Vector2 position)
{
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
    return items;
}

Tile parseResponse(json parsedData, int x, int y, int count)
{
    std::vector<AItem *> items;
    Vector2 position = {(float)x, (float)y};
    items = parseItems(parsedData, position);
    return Tile(position, items, count);
}

void parseAction(json data)
{
    std::string cmd = data["cmd"];
    if (cmd == "pin") {
        std::string id = data["id"];
        scene.setInventoryPlayer(id, parseItems(data, (Vector2) {0, 0}));
    }
    if (cmd == "pgt") {
        std::string id = data["id"];
        int player = scene.getPlayerById(id);
        int x = scene.getPlayers().at(player).getPosition().x;
        int y = scene.getPlayers().at(player).getPosition().y;
        int pos = (y * width_map) + x;
        int item = data["resource"];
        myMap._map.at(pos).removeItem(item);
    }
    if (cmd == "pdr") {
        std::string id = data["id"];
        // int player = scene.getPlayerById(id);
        // int x = scene.getPlayers().at(player).getPosition().x;
        // int y = scene.getPlayers().at(player).getPosition().y;
        // myMap._map.at(i);
    }
    if (cmd == "pic") {
        std::string leader = data["l"];
        int pos = scene.getPlayerById(leader);
        for (size_t i= 0; i < scene.getPlayers().size(); i++) {
            if (scene.getPlayers().at(i).getPosition().x == scene.getPlayers().at(pos).getPosition().x &&
                scene.getPlayers().at(i).getPosition().y == scene.getPlayers().at(pos).getPosition().y) {
                scene.isIncantingPlayer(scene.getPlayers().at(i).getName(), true);
            }
        }
    }
    if (cmd == "pie") {
        int x = data["x"];
        int y = data["y"];
        for (size_t i = 0; i < scene.getPlayers().size(); i++) {
            if (scene.getPlayers().at(i).getPosition().x == x &&
                scene.getPlayers().at(i).getPosition().y == y) {
                scene.isIncantingPlayer(scene.getPlayers().at(i).getName(), false);
            }
        }
    }
    if (cmd == "plv") {
        std::string id = data["id"];
        int level = data["level"];
        scene.setLevelPlayer(id, level);
    }
    if (cmd == "pdi") {
        std::string id = data["id"];
        if (id == boxPlayer.getIdPlayer())
            boxPlayer.hide();
        int player = scene.getPlayerById(id);
        scene.removePlayer(player);
    }
    if (cmd == "ppo") {
        float x = data["x"];
        float y = data["y"];
        int orientation = data["o"];
        std::string id = data["id"];
        scene.setPositionPlayer(id, Vector2{x, y});
        scene.setOrientationPlayer(id, orientation);
    }
    if (cmd == "bct") {
        int x = int(data["x"]);
        int y = int(data["y"]);
        int count = (y * width_map) + x;
        Tile tile = parseResponse(data, x, y, count);
        myMap.push(tile);
    }
    if (cmd == "enw") {
        std::string id = data["player_id"];
        std::string eggId = data["egg_id"];
        float x = data["x"];
        float y = data["y"];
        Egg egg(eggId);
        egg.setPosition(Vector2{x, y});
        scene.addEgg(egg);
    }
    if (cmd == "edi") {
        std::string eggId = data["id"];
        int eggPos = scene.getEggById(eggId);
        scene.removeEgg(eggPos);
    }
    if (cmd == "ebo") {
        std::string eggId = data["id"];
        // int eggPos = scene.getEggById(eggId);
        // scene.removeEgg(eggPos);
    }
    if (cmd == "pnw") {
        std::string id = data["id"];
        float x = data["x"];
        float y = data["y"];
        int orientation = data["o"];
        int level = data["level"];
        Player player(id);
        player.setOrientation(orientation);
        player.setLevel(level);
        player.setPosition(Vector2{x, y});
        scene.addPlayer(player);
    }
}

void makeAction()
{
    std::string command;
    std::string cmd;
    while (1) {
        if (!client._actionQueue.isEmpty()) {
            command = client._actionQueue.pop();
            if (command != "ko\n" && command != "ko" && command.c_str()[0] != 'k' && command.c_str()[1] != 'o') {
                std::cout << "PARSER: " << command << "ENDPARSER" << std::endl;
                parseAction(json::parse(command));
            } else {
                // std::cout << "ERROR: " << command << "END" << std::endl;
            }
        }
    }
}

void refreshInfo()
{
    std::chrono::time_point<std::chrono::system_clock> start, end;
    std::string response;
    while (1) {
        response = client.catchResponse();
        // std::this_thread::sleep_for(std::chrono::milliseconds(200));
        for (size_t i = 0; i < scene.getPlayers().size(); i++) {
            std::string name = scene.getPlayerName(i);
            if (name != "") {
                client.sendRequestId("ppo", name);
                response = client.catchResponse();
                client.sendRequestId("plv", name);
                response = client.catchResponse();
                // client.sendRequestId("pin", name);
                // response = client.catchResponse();
            }
        }
        if (timeBar._tmpTime != timeBar._value) {
            timeBar._tmpTime = timeBar._value;
            std::string message = "sst " + std::to_string(timeBar._value) + "\n";
            client.sendRequest(message);
        }
    }
}

void checkArguments(int argc, char** argv) {
    if (argc != 3) {
        std::cerr << "Usage: ./zappy_gui [ip] [port]" << std::endl;
        exit(84);
    }
    ip = argv[1];
    port = atoi(argv[2]);
}

int main(int argc, char **argv) {
    checkArguments(argc, argv);
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    client.init(ip, port);
    sleep(0.1);
    std::string response;
    // response = client.catchResponse();
    client.sendRequest("msz\n");
    std::cout << "Send msz command to server..." << std::endl;
    response = client.catchResponse();
    json parsedData = json::parse(response);
    width_map = parsedData["x"];
    height_map = parsedData["y"];
    std::cout << "Response: " << response << std::endl;
    std::cout << "x: " << width_map << ", y: " << height_map << std::endl;
    InitWindow(screenWidth, screenHeight, "Zappy");
    timeBar.init((Vector2) {1650, 100});
    Bar zoomBar;
    zoomBar.init((Vector2) {1600, 100});

    PlayerState playerState;
    playerState.client = &client;

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
    std::cout << "width_MAP: " << width_map << ", height_MAP: " << height_map << std::endl;
    sleep(0.1);
    std::string request = "bct ";
    std::string finalRequest;
    int count = 0;
    for (int j = 0; j < height_map; j++) {
        for (int i = 0; i < width_map; i++) {
            finalRequest = request + std::to_string(i) + " " + std::to_string(j) + "\n";
            client.sendRequest(finalRequest);
            std::cout << "Send " << finalRequest << " command to server..." << std::endl;
            response = client.catchResponseAnexe();
            json parsedData = json::parse(response);
            int x = int(parsedData["x"]);
            int y = int(parsedData["y"]);
            // int count = (y * width_map) + x;
            Tile tile(parseResponse(parsedData, x, y, count));
            count++;
            myMap.push(tile);
        }
        sleep(0.1);
    }
    sleep(3);
    Texture2D basePlayer = LoadTexture("gui/assets/player/players.png");
    Texture2D baseIncantation = LoadTexture("gui/assets/player/incantation.png");
    Texture2D baseEgg = LoadTexture("gui/assets/player/egg.png");
    Texture2D dropDown = LoadTexture("gui/assets/ui/dropdownButton.png");

    Cursor cursor;
    DropdownMenu dropdownMenu({ 1600, 50 }, { 320, 1750 }, BROWN);

    std::thread checkingThread(makeAction);
    std::thread refreshThread(refreshInfo);

    SetTargetFPS(60);
    BoxInfo boxInfo;
    boxPlayer.init();
    // AnimRaylib anim;
    // anim.run();

    Texture2D backgroundImg = LoadTexture("gui/models/loadingScreen.png");
    Texture2D baseTexture = LoadTexture("gui/assets/background.png");

    camera.offset = (Vector2){ 0, 0 };
    camera.rotation = 0;
    camera.zoom = 1.0f;
    camera.target = (Vector2){ 0, 0};

    Rectangle backgroundRect;
    backgroundRect.x = 0;
    backgroundRect.y = 0;
    backgroundRect.width = screenWidth;
    backgroundRect.height = screenHeight;

    scene.setBase(baseTexture);
    // Texture2D testPlayer = LoadTexture("gui/assets/player/players.png");

    while (!WindowShouldClose()) {
        switch (state) {
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
                std::string id = "";
                std::string tmp = "";
                bool check = false;
                for (auto &tile: myMap._map) {
                    check = tile.CheckTileHover(boxInfo, boxPlayer, camera);
                    if (check == true) {
                        tmp = scene.isPlayerAtPosition(tile.getTilePosition());
                        if (tmp != "" && id == "") {
                            id = tmp;
                        }
                    }
                }
                if (id != "") {
                    boxPlayer.setItems(scene.getInventoryPlayer(id));
                    boxPlayer.setIdPlayer(id);
                    boxPlayer.show();
                } else {
                    boxPlayer.hide();
                }
                timeBar.checkMouseClick();
                cursor.update(timeBar, zoomBar);
                // camera.zoom = zoomBar._value * 0.1f;
                int scroll = GetMouseWheelMove();
                if (scroll != 0) {
                    if (scroll > 0)
                        camera.zoom += 0.1f;
                    else
                        camera.zoom -= 0.1f;
                }
                bool check2 = dropdownMenu.update();
                if (check2 == true)
                    timeBar.show();
                else
                    timeBar.hide();
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
                // loadScreen.draw(loadingState);
            } break;
            case STATE_FINISHED:
            {
                DrawTexture(scene.getBase(), 0, 0, WHITE);
                BeginMode2D(camera);
                    HideCursor();
                    myMap.drawMap();
                    scene.drawEggs(baseEgg);
                    scene.drawPlayers(basePlayer, baseIncantation);
                EndMode2D();
                if (isDrawingBox) {
                    boxInfo.draw();
                    if (boxPlayer.isShowing()) {
                        Player player;
                        int posPlayer = scene.getPlayerById(boxPlayer.getIdPlayer());
                        boxPlayer.draw(scene.getPlayers().at(posPlayer), basePlayer);
                    }
                }
                for (size_t i = 0; i < scene.getPlayers().size(); i++) {
                    DrawText(scene.getPlayers().at(i).getName().c_str(), 10, 10 + 20 * i, 20, GREEN);
                }
                dropdownMenu.draw(dropDown);
                timeBar.draw();
                cursor.draw(&camera);
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