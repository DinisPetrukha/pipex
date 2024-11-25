NAME = pipex

SRC = src/pipex.c src/pipex_utils.c src/main.c

OBJ = $(SRC:.c=.o)

CC = cc

CFLAGS = -Wall -Werror -Wextra

INCLUDES = -Ilibft/

LIBFT = libft/libft.a

GREEN = \033[0;32m
CYAN = \033[0;36m
RED = \033[0;31m
NC = \033[0;33m

all: $(LIBFT) $(OBJ) $(NAME)

$(LIBFT):
	@echo "$(CYAN) \n-Compiling Libft...\n$(NC)"
	@$(MAKE) -C libft

	@echo "$(CYAN) \n-Compiling $(NAME)...\n$(NC)"
	@echo "cc $(CFLAGS) -g $(INCLUDES) -c *.c -o *.o"

$(OBJ): %.o: %.c
	@echo "$(CYAN) Compiling $@...$(NC)"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(NAME): $(OBJ)
	@echo "$(CYAN)\n-Linking $(NAME) with libft...\n$(NC)"
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJ) $(LIBFT) -o $(NAME)
	@make clean
	@echo "$(GREEN)\n--------------------------------$(NC)"
	@echo "$(GREEN) $(NAME) is ready!$(NC)"
	@echo "$(GREEN) Usage1: $(NAME) [infile] [cmd1] [cmd2] ... [outfile]$(NC)"
	@echo "$(GREEN) Usage2: $(NAME) here_doc [delimiter] [cmd1] [cmd2] ... [outfile]$(NC)"
	@echo "$(GREEN)--------------------------------$(NC)"

clean:
	@echo "$(CYAN)\n-Cleaning Libft...\n$(NC)"
	$(MAKE) -C libft clean
	@echo "$(CYAN)\n-Cleaning object files...\n$(NC)"
	rm -f $(OBJ)
	@echo "$(GREEN)\n--------------------------------$(NC)"
	@echo "$(GREEN) $(NAME) object files cleaned!$(NC)"
	@echo "$(GREEN)--------------------------------$(NC)"

fclean: clean
	@echo "$(CYAN)\n-Cleaning $(NAME) and libft...\n$(NC)"
	rm -f $(NAME)
	$(MAKE) -C libft fclean
	@echo "$(GREEN)\n--------------------------------$(NC)"
	@echo "$(GREEN) $(NAME) object files cleaned!$(NC)"
	@echo "$(GREEN)--------------------------------$(NC)"

re: fclean all

run: all
	./pipex infile cat "grep a" outfile

.PHONY: all clean fclean re