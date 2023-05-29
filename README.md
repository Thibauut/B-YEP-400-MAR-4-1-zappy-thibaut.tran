# Zappy
Zappy is an autonomous game powered by AI. It's the end-of-second-year project at Epitech. The goal of this project is to create a network game where several teams confront on a tiles map containing resources.
The winning team is the first one where at least 6 players who reach the maximum elevation.

## Requirements

- gui (C++)
- server (C)
- ai (free)


## Project
### Server
The server is the key of the game, which contains the state of the game and the state of the players. It also send and receive messages from the clients.

### GUI
The gui is a client of the server. He asks the server about information of the game to display it.
The world is in 3D for a better experience.

### AI
We choose C++ for AI langage;
They have different levels.

## Build

```
make gui
make ai
make server

make
make re

make clean
make fclean
```

## Usage
```bash
USAGE:
    ./zappy_gui -p port -h machine
        port is the port number
        machine is the name of the machine; localhost by default

    ./zappy_server -p port -x width -y height -n name1 name2 ... -c clientsNb -f freq
        port is the port number
        width is the width of the world
        height is the height of the world
        nameX is the name of the team X
        clientsNb is the number of authorized clients per team
        freq is the reciprocal of time unit for execution of actions

    ./zappy_ai -p port -n name -h machine
        port is the port number
        name is the name of the team
        machine is the name of the machine; localhost by default

```

## Documentation
In progress...

## Contributors

- [Maori Dino](https://github.com/MaoKoro)
- [Thibaut Tran](https://github.com/Thibauut)
- [Noah Yekken](https://github.com/)
- [Alexandre Vassal](https://github.com/)
- [Zyad Othman](https://github.com/)