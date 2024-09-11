NAME	= philo

SRC		= main.c exit_and_error.c init.c start_simulation.c get_fork.c stages.c utils.c 
OBJ		= $(SRC:.c=.o)
HEADER	= philo.h

CFLAGS	= -g -Wall -Wextra -Werror 

CC	= cc
RM	= rm -f

PURPLE:="\033[1;35m"
RED:="\033[1;91m"
GREEN:="\033[1;32m"
BLUE:="\033[1;36m"
EOC:="\033[0;0m"

all:		$(NAME)
			@echo $(PURPLE)"✨The program is ready✨" $(EOC)

$(NAME):	$(OBJ) $(HEADER)
	@echo $(BLUE) "*Compiling philosophers*" $(EOC)
	$(CC) $(SRC) $(CFLAGS) -o $(NAME)

clean:
	@echo $(PURPLE) "🧹️🧹️🧹️" $(EOC)
	$(RM) $(OBJ)
	@echo $(PURPLE) "✨Clean✨" $(EOC)

fclean:		clean
	@echo $(PURPLE) "🪄" $(EOC)
	$(RM) $(NAME)
	@echo $(PURPLE) "✨FClean✨" $(EOC)

re:	fclean all

.PHONY:	check	all clean fclean re