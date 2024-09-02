NAME = philo_bonus

SOURCES = philosophers_bonus.c utils/functions_bonus.c helpers/philosophers_bonus.c utils/philosophers_bonus.c utils/table_bonus.c \
helpers/checker_bonus.c utils/semaphores_bonus.c
HEADER = philosophers_bonus.h

DATARACE = -fsanitize=thread

CC = cc 
CFLAGS =  -pthread -lpthread $(DATARACE)
 
all: $(NAME)

$(NAME): $(SOURCES) $(HEADER)
	$(CC) $(CFLAGS) $(SOURCES) -o $(NAME)	

clean: 
	echo "Nothing to clean"

fclean: 
	$(RM) $(NAME)

re: fclean all