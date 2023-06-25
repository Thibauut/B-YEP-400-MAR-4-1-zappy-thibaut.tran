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
#include <pthread.h>

typedef struct sockaddr_in SOCKADDR_IN;
typedef struct sockaddr SOCKADDR;
typedef struct in_addr IN_ADDR;
#define ADD_TO_QUEUE 0
#define EXECUTE 1

enum orientation_e {
    NORTH,
    EAST,
    SOUTH,
    WEST
};

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

//INVENTORY
typedef struct inventory_s {
    int food;
    int linemate;
    int deraumere;
    int sibur;
    int mendiane;
    int phiras;
    int thystame;
} inventory_t;


//EGG
typedef struct	egg_s
{
    bool in_team;
    bool is_gui;
    int socket;
    team_t *team;

    inventory_t *inventory;
    char *id;
    int level;
    int x;
    int y;
    enum orientation_e o;
    int life;
    bool incantation;
    char *uuid_creator;
} egg_t;

typedef struct list_eggs_s {
    egg_t *egg;
    struct list_eggs_s *next;
} list_eggs_t;

typedef struct vector2d_s {
    int x;
    int y;
} vector2d_t;

typedef struct list_vector2d_s {
    vector2d_t *vector;
    struct list_vector2d_s *next;
} list_vector2d_t;

typedef struct player_s {
    bool in_team;
    bool is_gui;
    int socket;
    team_t *team;

    //INFO
    inventory_t *inventory;
    char *id;
    int level;
    int x;
    int y;
    enum orientation_e o;
    int life;
    bool incantation;
} player_t;

typedef struct list_players_s {
    player_t *player;
    struct list_players_s *next;
} list_players_t;

//COMMAND AI
typedef struct cmd_ai_s {
    char *uuid;
    char **cmd;
    int duration;
} cmd_ai_t;

typedef struct list_cmd_ai_s {
    cmd_ai_t *action;
    struct list_cmd_ai_s *next;
} list_cmd_ai_t;


//SERVER
typedef struct this_s {
    //PARAMS
    int port;
    int width;
    int height;
    int nb_clients;
    int nb_clients_egg;
    int freq;
    char **teams_name;
    struct timeval *timeout;
    int refill_map_timer;
    bool is_start;

    //PLAYERS & TEAMS & EGGS
    list_players_t *players;
    list_teams_t *teams;
    list_vector2d_t *tiles_pos;
    list_vector2d_t *players_pos;
    list_eggs_t *eggs;

    //SERVER
    int control_socket;
    int new_socket;
    int maxfd;
    SOCKADDR_IN control_addr;
    SOCKADDR_IN client_addr;
    char **cmd;

    //SELECT
    list_cmd_ai_t *actions;
    list_cmd_ai_t *first_actions;
    fd_set readfds;
    fd_set tmpfds;
    fd_set writefds;

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
struct timeval float_to_timeval(float seconds);
cmd_ai_t *get_action_by_id(this_t *this, char *uuid);
cmd_ai_t *create_action_ai(this_t *this, player_t *player, char *cmd, char *arg, int duration);
player_t *get_player_by_uuid(this_t *this, char *uuid);
char *rm_extra_spaces(char *str);
void update_pos(this_t *this, int *x, int *y);

list_players_t *create_cell(player_t *player);
list_players_t *add_element(list_players_t *list, player_t *player, int pos);
list_players_t *free_element_at(list_players_t *list, int pos);
int list_len(list_players_t *list);

list_teams_t *create_cell_team(team_t *team);
list_teams_t *add_element_team(list_teams_t *list, team_t *team, int pos);
list_teams_t *free_element_at_team(list_teams_t *list, int pos);
int list_len_team(list_teams_t *list);

list_cmd_ai_t *create_cell_ai(cmd_ai_t *cmd);
list_cmd_ai_t *add_element_ai(list_cmd_ai_t *list, cmd_ai_t *cmd, int pos);
list_cmd_ai_t *free_first_element_ai(list_cmd_ai_t *list);
list_cmd_ai_t *free_element_at_ai(list_cmd_ai_t *list, int pos);
int list_len_ai(list_cmd_ai_t *list);

list_vector2d_t *create_cell_vector(vector2d_t *vector);
list_vector2d_t *add_element_vector(list_vector2d_t *list, vector2d_t *vector, int pos);
list_vector2d_t *free_first_element_vector(list_vector2d_t *list);
list_vector2d_t *free_element_at_vector(list_vector2d_t *list, int pos);
int list_len_vector(list_vector2d_t *list);

list_eggs_t *create_cell_egg(egg_t *egg);
list_eggs_t *add_element_egg(list_eggs_t *list, egg_t *egg, int pos);
list_eggs_t *free_first_element_egg(list_eggs_t *list);
list_eggs_t *free_element_at_egg(list_eggs_t *list, int pos);
int list_len_egg(list_eggs_t *list);
egg_t *get_element_egg(list_eggs_t *list, int pos);

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
void update_map(this_t *this);
void handle_borders(this_t *this, player_t *player);

//SERVER
void init_socket(this_t *this);
void init_fdset(this_t *this);
void init_zappy_teams(this_t *this);
void init_server(this_t *this);
void run_server(this_t *this);
void data_from_player(this_t *this);
void server_timer(this_t *this);
int add_player_to_team(this_t *this, player_t *player);
void add_player_to_set(this_t *this);
void handle_new_connection(this_t *this);
void delete_player(this_t *this, player_t *player);

//ERRORS
void socket_error(int control_socket);
void htons_error(this_t *this);
void bind_error(int _bind);
void listen_error(int _listen);
void select_error(this_t *this, int _activity);

//COMMANDS (SERVER)
void commands(this_t *this, player_t *player);
int get_ai_commands(this_t *this, player_t *player);
int exec_ai_commands(this_t *this, player_t *player, int exec);
int exec_gui_commands(this_t *this, player_t *player);
int object_commands(this_t *this, player_t *player, int exec);
int move_commands(this_t *this, player_t *player, int exec);
int action_commands(this_t *this, player_t *player, int exec);
int player_commands(this_t *this, player_t *player, int exec);
void exec_actions(this_t *this);

//COMMANDS (GUI)
int map_info_gui_commands(this_t *this, player_t *player);
int player_info_gui_commands(this_t *this, player_t *player);
int time_info_gui_commands(this_t *this, player_t *player);
void msz(this_t *this, player_t *player);
void bct(this_t *this, player_t *player);
void mct(this_t *this, player_t *player);
void tna(this_t *this, player_t *player);
void ppo(this_t *this, player_t *player);
void plv(this_t *this, player_t *player);
void pin(this_t *this, player_t *player);
void pnw(this_t *this, player_t *player);
void sgt(this_t *this, player_t *player);
void sst(this_t *this, player_t *player);
void send_pdr_to_gui(this_t *this, char *drop_id, int resource);

// EVENTS (GUI)
void pdi(this_t *this, player_t *player, char *dead_id);
void send_pdi_to_gui(this_t *this, char *uuid);
void pdr(this_t *this, player_t *player, char *drop_id, int resource);
void send_pdr_to_gui(this_t *this, char *drop_id, int resource);
void pgt(this_t *this, player_t *player, char *take_id, int resource);
void send_pgt_to_gui(this_t *this, char *take_id, int resource);
void pic(this_t *this, player_t *player, int x, int y, char *id, list_players_t *list);
void send_pic_to_gui(this_t *this, int x, int y, char *id, list_players_t *list);
void pie(this_t *this, player_t *player, int x, int y, char *r);
void send_pie_to_gui(this_t *this, int x, int y, char *r);
void pex(this_t *this, player_t *player, char *player_id);
void send_pex_to_gui(this_t *this, char *uuid);
void pfk(this_t *this, player_t *player, char *uuid);
void send_pfk_to_gui(this_t *this, char *uuid);
void enw(this_t *this, player_t *player, egg_t *egg);
void send_enw_to_gui(this_t *this, player_t *player, egg_t *egg);
void ebo(this_t *this, player_t *player, char *uuid);
void send_ebo_to_gui(this_t *this, char *uuid);
void pbc(this_t *this, player_t *player, char *uuid, char *msg);
void send_pbc_to_gui(this_t *this, char *uuid, char *msg);
void edi(this_t *this, player_t *player, char *uuid);
void send_edi_to_gui(this_t *this, char *uuid);


//COMMANDS (AI)
void inventory(this_t *this, player_t *player, int exec);
void look(this_t *this, player_t *player, int exec);
void connect_nbr(this_t *this, player_t *player);
void broadcast(this_t *this, player_t *player, int exec);
void right(this_t *this, player_t *player, int exec);
void left(this_t *this, player_t *player, int exec);
void forward(this_t *this, player_t *player, int exec);
void take_object(this_t *this, player_t *player, int exec);
void set_object(this_t *this, player_t *player, int exec);
void incantation(this_t *this, player_t *player, int exec);
void eject(this_t *this, player_t *player, int exec);
void fork_egg(this_t *this, player_t *player, int exec);