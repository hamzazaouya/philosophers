NAME = philo
HEADER = philosophers.h
SOURCES = philosophers.c aid_funct1.c main.c routine.c aid_funct2.c
SRC_PATH = src
OBJ_PATH  = objs
OBJ_PATH_B = objs_b

CC = cc
CFLAGS = -Wall -Wextra -Werror

SRCS = $(addprefix $(SRC_PATH)/,$(SOURCES))
OBJS = $(addprefix $(OBJ_PATH)/,$(SOURCES:.c=.o))

OBJS_B = $(addprefix $(OBJ_PATH_B)/,$(SOURCES_B:.c=.o))
.PHONY:	all clean fclean re

all : $(OBJ_PATH) $(NAME)


$(NAME) : $(OBJS)
	$(CC) $(CFLAGS)  $(OBJS) $(LIB) -o $(NAME)

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c includes/$(HEADER)
	@$(CC) $(CFLAGS)  -c -o $@ $<

$(OBJ_PATH):
	@mkdir objs

clean:
	rm -f $(OBJS) $(OBJS_B)

fclean: clean
	rm -f $(NAME)
	rm -fr $(OBJ_PATH)
re : fclean all