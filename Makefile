##
## EPITECH PROJECT, 2022
## Zappy
## File description:
## Makefile
##

NAME_GUI	=	zappy_gui

SRC_GUI	=	gui/SFML/SFML.cpp	\
			gui/gui.cpp

all: gui

clean:
	rm -f .o

fclean: clean
	rm -f $(NAME_GUI)

gui:
	g++ -o $(NAME_GUI) $(SRC_GUI) -lsfml-graphics	-lsfml-audio -lsfml-window -lsfml-system -g3

re: fclean all

.PHONY: all fclean re