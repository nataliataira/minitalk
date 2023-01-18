NAME = minitalk
SERVER = server
CLIENT = client

PATH_SRCS = ./sources/
PATH_INCL = ./includes/
PATH_OBJS = ./objects/
PATH_LIBFT = ./libft/

SRCS_S = $(PATH_SRCS)server.c
SRCS_C = $(PATH_SRCS)client.c

OBJS_S = $(PATH_OBJS)server.o
OBJS_C = $(PATH_OBJS)client.o

CFLAGS = -Wall -Wextra -Werror -g
IFLAGS = -I $(PATH_INCL)
LIBFT = $(PATH_LIBFT)libft.a

all: $(NAME)

$(NAME): $(SERVER) $(CLIENT)

$(SERVER): $(OBJS_S) $(LIBFT)
	cc $(CFLAGS) $(IFLAGS) -o $@ $< $(LIBFT)

$(OBJS_S): $(SRCS_S)
	@mkdir -p $(PATH_OBJS)
	cc $(CFLAGS) $(IFLAGS) -c $< -o $@

$(CLIENT): $(OBJS_C) $(LIBFT)
	cc $(CFLAGS) $(IFLAGS) -o $@ $< $(LIBFT)

$(OBJS_C): $(SRCS_C)
	@mkdir -p $(PATH_OBJS)
	cc $(CFLAGS) $(IFLAGS) -c $< -o $@

$(LIBFT):
	@make -C $(PATH_LIBFT)

clean:
	@make clean -C $(PATH_LIBFT)
	rm -rf $(PATH_OBJS)

fclean: clean
	@make fclean -C $(PATH_LIBFT)
	rm $(SERVER) $(CLIENT)

re: fclean all

.PHONY: all clean fclean re



