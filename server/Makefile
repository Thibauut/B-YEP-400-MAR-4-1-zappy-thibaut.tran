##
## EPITECH PROJECT, 2022
## B-YEP-400-MAR-4-1-zappy-thibaut.tran
## File description:
## Makefile
##

SRC	=	utils/utils.c				\
		utils/player_list_utils.c	\
		utils/team_list_utils.c		\
		server/display_help.c		\
		server/get_params.c			\
		server/error.c				\
		server/server.c				\
		server/commands_ai.c		\
		server/commands_gui.c		\
		server/handle_cmd.c			\
		server/handle_player.c		\
		server/map.c				\
		server/commands_gui/msz.c	\
		server/commands_gui/bct.c	\
		server/commands_gui/mct.c	\
		server/commands_gui/tna.c	\
		main.c

OBJ	=	$(SRC:.c=.o)

NAME	= zappy_server

all	:	$(NAME)	$(SRC)

$(NAME)	:
	@printf "\x1B[1;34m\r[Compiling]               %$(SPACES)c\x1B[1;0m" ' '
	@sleep 0.5
	@gcc	-o $(NAME) $(SRC) -g3 -std=gnu17	-luuid
	@printf "\x1B[1;32m\r[Compilation terminated]%$(SPACES)c\n\x1B[1;0m" ' '
	@sleep 0.5

clean :
	@rm	-f	$(OBJ)

fclean :
	@printf "\x1B[1;31m\r[Cleaning]                %$(SPACES)c\x1B[1;0m" ' '
	@sleep 0.5
	@rm	-f	$(NAME)
	@printf "\x1B[1;32m\r[Clean terminated]%$(SPACES)c\n\x1B[1;0m" ' '
	@sleep 0.5

re :	fclean	clean
	@printf "\x1B[1;33m\r[Recompiling]             %$(SPACES)c\x1B[1;0m" ' '
	@sleep 0.5
	@gcc	-o $(NAME) $(SRC) -g3 -std=gnu17	-luuid
	@printf "\x1B[1;32m\r[Recompilation terminated]%$(SPACES)c\n\x1B[1;0m" ' '
	@sleep 0.5
