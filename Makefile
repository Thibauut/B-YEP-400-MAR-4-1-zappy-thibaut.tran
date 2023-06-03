##
## EPITECH PROJECT, 2022
## Zappy
## File description:
## Makefile
##

SRC_GUI		=	gui/SFML/SFML.cpp\
				gui/gui.cpp

SRC_AI 		=	ai/ai.py

NAME_GUI	=	zappy_gui

NAME_AI		=	zappy_ai

all: gui ai

clean:
	rm -f .o

fclean: clean
	rm -f $(NAME_GUI)
	rm -f $(NAME_AI)

re: fclean all

ai:
	cp -r $(SRC_AI) $(NAME_AI)
	chmod 777 $(NAME_AI)

gui:
	g++ -o $(NAME_GUI) $(SRC_GUI) -lsfml-graphics	-lsfml-audio -lsfml-window -lsfml-system -g3

.PHONY: all fclean re