NAME        = PRAG
CFLAGS      = -Wall -Wextra -Werror
SRCS        = main.c utils.c
OBJS        = $(addprefix $(BUILD), $(SRCS:.c=.o))
RM          = rm -rf
BUILD       = build/

all: $(BUILD) $(NAME)

install: all
	cp $(NAME) /usr/local/bin/

$(BUILD):
	@mkdir -p $(BUILD)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

$(BUILD)%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(BUILD)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re