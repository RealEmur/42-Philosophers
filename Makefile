NAME = philo

SOURCES = philosophers.c utils/functions.c helpers/philosophers.c
HEADER = philosophers.h

CC = cc 
CFLAGS = 

all: $(NAME)

$(NAME): $(SOURCES) $(HEADER)
	$(CC) $(CFLAGS) $(SOURCES) -o $(NAME)	

clean: 
	echo "Nothing to clean"

fclean: 
	$(RM) $(NAME)

re: fclean all