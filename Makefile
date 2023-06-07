##
## EPITECH PROJECT, 2022
## Zappy
## File description:
## Makefile
##

SRC_GUI		=	gui/SFML/SFML.cpp			\
				gui/gui.cpp					\
				gui/requests/Client.cpp	\

SRC_AI 		=	AI/ai.py

SRC_SERVER	=	server/zappy_server

NAME_GUI	=	zappy_gui

NAME_AI		=	zappy_ai

NAME_SERVER	=	zappy_server

all: GUI ai SERVER

clean:
		rm -f *.o

fclean: clean
		rm -f $(NAME_GUI)
		rm -f $(NAME_AI)
		rm -f $(NAME_SERVER)

ai:
	cp -r $(SRC_AI) $(NAME_AI)
	chmod 777 $(NAME_AI)

SERVER:
	cp -r $(SRC_SERVER) $(NAME_SERVER)
	chmod 777 $(NAME_SERVER)

GUI:
	g++ -o $(NAME_GUI) $(SRC_GUI) -std=c++11 -Wall -lGL -lGLU -lglut -lGLEW -lglfw -lX11 -lXxf86vm -lXrandr -lpthread -lXi -ldl -lXinerama -lXcursor -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system

re: fclean all