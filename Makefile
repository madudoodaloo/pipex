NAME = pipex

CC = cc 
RM = rm -rf 
CFLAGS = -Wall -Wextra -Werror -g #-fsanitize=address

SRC = pipex.c \
utils/ft_split.c \
utils/paths.c \
utils/utils.c

OBJS = $(SRC:.c=.o)

$(NAME):	$(OBJS)
		$(CC) $(CFLAGS) $(OBJS) -o $(NAME) 

all:	$(NAME)

clean:
		$(RM) $(OBJS)

fclean: clean
		$(RM) $(NAME)

re: fclean all