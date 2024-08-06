NAME = philo

SOURCES = philosophers.c utils/functions.c helpers/philosophers.c helpers/checker.c utils/philosophers.c utils/table.c
HEADER = philosophers.h
MAKEFILE = Makefile

DATARACE = -fsanitize=thread 

CC = cc 
CFLAGS = -Wall -Wextra -Werror -pthread 

all: $(NAME)

$(NAME): $(SOURCES) $(HEADER) $(MAKEFILE)
	$(CC) $(CFLAGS) $(SOURCES) -o $(NAME)	

clean: 
	echo "Nothing to clean"

fclean: 
	$(RM) $(NAME)

test: 
	echo $(SOURCES:.c=.o)

re: fclean all