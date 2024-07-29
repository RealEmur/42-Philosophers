NAME = philo

SOURCES = philosophers.c utils/functions.c helpers/philosophers.c utils/philosophers.c
HEADER = philosophers.h

DATARACE = -fsanitize=thread

CC = cc 
CFLAGS = -pthread
 
all: $(NAME)

$(NAME): $(SOURCES) $(HEADER)
	$(CC) $(CFLAGS) $(SOURCES) -o $(NAME)	

clean: 
	echo "Nothing to clean"

fclean: 
	$(RM) $(NAME)

re: fclean all