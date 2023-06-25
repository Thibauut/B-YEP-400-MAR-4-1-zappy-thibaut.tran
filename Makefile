##
## EPITECH PROJECT, 2022
## Zappy
## File description:
## Makefile
##

SRC_GUI		=	gui/requests/Client.cpp				\
				gui/items/AItem.cpp					\
				gui/tile/Tile.cpp					\
				gui/Utils/Global.cpp				\
				gui/Map/Map.cpp						\
				gui/screens/LoadingScreen.cpp		\
				gui/Player/Player.cpp				\
				gui/Player/Egg.cpp					\
				gui/Scene/Scene.cpp					\
				gui/Anim/AnimRaylib.cpp				\
				gui/Anim/Anim.cpp					\
				gui/screens/BoxInfo.cpp				\
				gui/Map/Cursor.cpp					\
				gui/Bar/BarTime.cpp					\
				gui/requests/ActionQueue.cpp		\

SRC_AI 		=	ai/ai.py

SRC_SERVER	=	server/utils/utils.c									\
				server/utils/player_list_utils.c						\
				server/utils/team_list_utils.c							\
				server/utils/ai_cmd_list_utils.c						\
				server/utils/eggs_list_utils.c							\
				server/utils/look_list_utils.c							\
				server/utils/display_help.c								\
				server/server/get_params/get_params.c					\
				server/server/socket_error/error.c						\
				server/server/server.c									\
				server/server/server_read.c								\
				server/server/server_init.c								\
				server/server/server_timer.c							\
				server/server/teams_init.c								\
				server/server/get_params/get_ai_commands.c				\
				server/server/get_params/get_gui_commands.c				\
				server/server/handle_server/handle_gui_commands.c		\
				server/server/handle_server/handle_commands.c			\
				server/server/handle_server/handle_player.c				\
				server/server/handle_server/handle_connection.c			\
				server/server/handle_server/handle_ai_commands.c		\
				server/server/build_map/map.c							\
				server/server/commands_gui/msz.c						\
				server/server/commands_gui/bct.c						\
				server/server/commands_gui/mct.c						\
				server/server/commands_gui/tna.c						\
				server/server/commands_gui/ppo.c						\
				server/server/commands_gui/plv.c						\
				server/server/commands_gui/sgt.c						\
				server/server/commands_gui/sst.c						\
				server/server/commands_gui/pin.c						\
				server/server/commands_gui/events/pbc.c					\
				server/server/commands_gui/events/pic.c					\
				server/server/commands_gui/events/pex.c					\
				server/server/commands_gui/events/pie.c					\
				server/server/commands_gui/events/pnw.c					\
				server/server/commands_gui/events/pdi.c					\
				server/server/commands_gui/events/pdr.c					\
				server/server/commands_gui/events/pgt.c					\
				server/server/commands_gui/events/pfk.c					\
				server/server/commands_gui/events/enw.c					\
				server/server/commands_gui/events/ebo.c					\
				server/server/commands_ai/inventory.c					\
				server/server/commands_ai/broadcast.c					\
				server/server/commands_ai/look.c						\
				server/server/commands_ai/connect_nbr.c					\
				server/server/commands_ai/forward.c						\
				server/server/commands_ai/right.c						\
				server/server/commands_ai/left.c						\
				server/server/commands_ai/take_object.c					\
				server/server/commands_ai/set_object.c					\
				server/server/commands_ai/eject.c						\
				server/server/commands_ai/fork.c						\
				server/server/commands_ai/incantation.c					\
				server/server/commands_gui/events/edi.c					\
				server/main.c

NAME_GUI	=	zappy_gui

NAME_AI		=	zappy_ai

NAME_SERVER	=	zappy_server

all: gui_ ai_ server_

clean:
	@rm -f *.o

fclean: clean
	@rm -f $(NAME_GUI)
	@rm -f $(NAME_AI)
	@rm -f $(NAME_SERVER)

ai_:
	@cp -r $(SRC_AI) $(NAME_AI)
	@chmod 777 $(NAME_AI)

server_:
	@gcc	-o $(NAME_SERVER) $(SRC_SERVER) -g3 -std=gnu17	-luuid

gui_:
	@g++ -pthread -o $(NAME_GUI) gui/gui.cpp $(SRC_GUI) -Wall -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system -lassimp

re: fclean all