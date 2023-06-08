##
## EPITECH PROJECT, 2022
## Zappy
## File description:
## Makefile
##

SRC_GUI		=	gui/SFML/SFML.cpp			\
				gui/gui.cpp					\
				gui/requests/Client.cpp	\

SRC_AI 		=	ai/ai.py

SRC_SERVER	=	server/utils/utils.c				\
				server/utils/player_list_utils.c	\
				server/utils/team_list_utils.c		\
				server/server/display_help.c		\
				server/server/get_params.c			\
				server/server/error.c				\
				server/server/server.c				\
				server/server/commands_ai.c			\
				server/server/commands_gui.c		\
				server/server/handle_cmd.c			\
				server/server/handle_player.c		\
				server/server/map.c					\
				server/server/commands_gui/msz.c	\
				server/server/commands_gui/bct.c	\
				server/server/commands_gui/mct.c	\
				server/server/commands_gui/tna.c	\
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
	@g++	-o $(NAME_GUI) $(SRC_GUI) -std=c++11 -Wall -lGL -lGLU -lglut -lGLEW -lglfw -lX11 -lXxf86vm -lXrandr -lpthread -lXi -ldl -lXinerama -lXcursor -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system

re: fclean all