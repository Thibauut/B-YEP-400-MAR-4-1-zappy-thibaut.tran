##
## EPITECH PROJECT, 2022
## Zappy
## File description:
## Makefile
##

SRC_GUI		=	GUI/SFML/SFML.cpp\
				GUI/gui.cpp

SRC_AI 		=	AI/ai.py

NAME_GUI	=	zappy_gui

NAME_AI		=	zappy_ai

all: gui ai

clean:
		rm -f *.o

fclean: clean
		rm -f $(NAME_GUI)
		rm -f $(NAME_AI)

ai:
	cp -r $(SRC_AI) $(NAME_AI)
	chmod 777 $(NAME_AI)

gui:
	g++ -o $(NAME_GUI) $(SRC_GUI) -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system -g3

re: fclean all