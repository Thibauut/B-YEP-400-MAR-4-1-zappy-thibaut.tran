/*
** EPITECH PROJECT, 2022
** B-YEP-400-MAR-4-1-zappy-thibaut.tran
** File description:
** my.h
*/

#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <unistd.h>
#include <netdb.h>
#include <ctype.h>
#include <pwd.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/select.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <uuid/uuid.h>
#include <dlfcn.h>
#include <time.h>
#include "map.h"

typedef struct sockaddr_in SOCKADDR_IN;
typedef struct sockaddr SOCKADDR;
typedef struct in_addr IN_ADDR;

//TEAM
typedef struct team_s {
    char *name;
    int max_players;
    int nb_players;
    char **players_id;
} team_t;

typedef struct list_teams_s {
    team_t *team;
    struct list_teams_s *next;
} list_teams_t;

//PLAYER
typedef struct player_s {
    bool in_team;
    bool is_gui;
    int socket;
    team_t *team;

    //INFO
    char *id;
    int level;
    bool incentation;
} player_t;

typedef struct list_players_s {
    player_t *player;
    struct list_players_s *next;
} list_players_t;


//SERVER
typedef struct this_s {
    //PARAMS
    int port;
    int width;
    int height;
    int nb_clients;
    int freq;
    char **teams_name;

    list_players_t *players;
    list_teams_t *teams;

    //SERVER
    int control_socket;
    int new_socket;
    int maxfd;
    SOCKADDR_IN control_addr;
    SOCKADDR_IN client_addr;
    char **cmd;

    fd_set readfds;
    fd_set tmpfds;
    fd_set writefds;

    struct timeval timeout;
    time_t start_time;

    //MAP
    map_t *map;

} this_t;

//UTILS
int my_is_number(char *str);
char *my_strlowcase(char *str);
int my_strcasecmp(char *s1, char *s2);
int my_strlen(char *str);
char **strtok_wordtab(char *str, char *tok);
char *my_strcat(char *dest, char *src);
int my_strcmp(char *s1, char *s2);
char **word_to_tab(char *str, char c, int i);
char *my_itoa(int nb);
void display_help(void);
char *get_unique_uuid(void);

list_players_t *create_cell(player_t *player);
list_players_t *add_element(list_players_t *list, player_t *player, int pos);
list_players_t *free_element_at(list_players_t *list, int pos);

list_teams_t *create_cell_team(team_t *team);
list_teams_t *add_element_team(list_teams_t *list, team_t *team, int pos);
list_teams_t *free_element_at_team(list_teams_t *list, int pos);
int list_len_team(list_teams_t *list);

//PARAMS
void init_params(this_t *this);
void error_params(char**av, int i, int max_args, char *option, bool enable_max_args);
void get_port(this_t *this, char *port);
void get_width(this_t *this, char *width);
void get_height(this_t *this, char *height);
void get_nb_clients(this_t *this, char *nb_clients);
void get_freq(this_t *this, char *freq);
void get_params(this_t *this, int ac, char **av);

//MAP
void init_zappy_map(this_t *this);
void refill_map(this_t *this);

//SERVER
void init_server(this_t *this);
void run_server(this_t *this);
int add_player_to_team(this_t *this, player_t *player);

//ERRORS
void socket_error(int control_socket);
void htons_error(this_t *this);
void bind_error(int _bind);
void listen_error(int _listen);
void select_error(int _activity);

//COMMANDS (SERVER)
void commands(this_t *this, player_t *player);
int exec_ai_commands(this_t *this, player_t *player);
int exec_gui_commands(this_t *this, player_t *player);
int move_commands(this_t *this, player_t *player);
int action_commands(this_t *this, player_t *player);
int player_commands(this_t *this, player_t *player);

//COMMANDS (GUI)
int map_info_gui_commands(this_t *this, player_t *player);
int player_info_gui_commands(this_t *this, player_t *player);
int time_info_gui_commands(this_t *this, player_t *player);

void msz(this_t *this, player_t *player);