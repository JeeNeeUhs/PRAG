NAME        = prag
CC         ?= cc
CFLAGS     ?= -Wall -Wextra -O2
PREFIX     ?= /usr/local
BINDIR      = $(PREFIX)/bin
SRCS        = main.c utils.c
BUILD       = build
OBJS        = $(addprefix $(BUILD)/, $(SRCS:.c=.o))
RM          = rm -rf

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $(NAME) $(OBJS)

$(BUILD)/%.o: %.c | $(BUILD)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD):
	@mkdir -p $(BUILD)

install: all
	install -d $(DESTDIR)$(BINDIR)
	install -m 755 $(NAME) $(DESTDIR)$(BINDIR)/$(NAME)

clean:
	$(RM) $(BUILD)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all install clean fclean rem