NAME = philosophers
HEADER = philosophers.h
SOURCES = philosophers.c ft_lstadd_back_bonus.c
SRC_PATH = src
OBJ_PATH  = objs
OBJ_PATH_B = objs_b
LIB_PATH = includes/libft
LIB = $(LIB_PATH)/libft.a

CC = cc
CFLAGS = -Wall -Wextra -Werror 

SRCS = $(addprefix $(SRC_PATH)/,$(SOURCES))
OBJS = $(addprefix $(OBJ_PATH)/,$(SOURCES:.c=.o))

OBJS_B = $(addprefix $(OBJ_PATH_B)/,$(SOURCES_B:.c=.o))
.PHONY:	all clean fclean re

all : $(OBJ_PATH) $(NAME)

$(LIB):
	@cd $(LIB_PATH) && make && make clean


$(NAME) : $(OBJS) $(LIB)
	$(CC)  $(OBJS) $(LIB) -o $(NAME)

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c includes/$(HEADER)
	@$(CC)  -c -o $@ $<

$(OBJ_PATH):
	@mkdir objs

clean:
	rm -f $(OBJS) $(OBJS_B)

fclean: clean
	rm -f $(NAME)
	@cd $(LIB_PATH) && make fclean
	rm -fr $(OBJ_PATH)
re : fclean all