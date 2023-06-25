/*
** EPITECH PROJECT, 2022
** B-YEP-400-MAR-4-1-zappy-thibaut.tran
** File description:
** fork.c
*/

#include "../../include/my.h"

inventory_t *init_inventory_egg(egg_t *egg)
{
    egg->inventory = malloc(sizeof(inventory_t));
    egg->inventory->food = 10;
    egg->inventory->linemate = 0;
    egg->inventory->deraumere = 0;
    egg->inventory->sibur = 0;
    egg->inventory->mendiane = 0;
    egg->inventory->phiras = 0;
    egg->inventory->thystame = 0;
    return (egg->inventory);
}

char *my_strdup(char const *str)
{
    int i = 0;
    for (; str[i]; i += 1);
    char *temp = malloc(sizeof(char) * i + 1);
    for (int i = 0; str[i]; i += 1)
        temp[i] = str[i];
    temp[i] = '\0';
    return temp;
}

egg_t *create_egg(this_t *this, player_t *player)
{
    egg_t *egg = malloc(sizeof(egg_t));
    egg->socket = -1;
    egg->id = get_unique_uuid();
    egg->x = player->x;
    egg->y = player->y;
    egg->o = rand() % 4;
    egg->team = player->team;
    egg->in_team = true;
    egg->is_gui = false;
    egg->level = 1;
    egg->incantation = false;
    egg->life = 126;
    egg->inventory = init_inventory_egg(egg);
    egg->uuid_creator = my_strdup(player->id);
    return (egg);
}

void fork_egg(this_t *this, player_t *player, int exec)
{
    if (exec == 0) {
        cmd_ai_t *action = create_action_ai(this, player, "Fork", NULL, 42);
        this->actions = add_element_ai(this->actions, action, list_len_ai(this->actions));
        send_pfk_to_gui(this, player->id);
        return;
    }
    egg_t *egg = create_egg(this, player);
    this->eggs = add_element_egg(this->eggs, egg, list_len_egg(this->eggs));
    dprintf(player->socket, "ok\n");
    send_enw_to_gui(this, player, egg);
    this->nb_clients = this->nb_clients + 1;
    this->nb_clients_egg += 1;
    for (list_teams_t *tmp = this->teams; tmp; tmp = tmp->next) {
        if (strcmp(tmp->team->name, player->team->name) == 0) {
            printf("Add players slot\n");
            tmp->team->max_players += 1;
        }
    }
}