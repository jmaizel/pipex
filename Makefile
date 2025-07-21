NAME = pipex

CC = gcc
CFLAGS = -Wall -Wextra -Werror

LIBFT_DIR = ./libft
LIBFT_INCLUDES = $(LIBFT_DIR)/includes

SRC_DIR = ./srcs

# Fichiers sources pour la version normale
SRC_FILES = main.c \
			utils.c \
			path.c \
			utils2.c \
			cmd1.c \
			cmd2.c

# Création des listes d'objets
SRC = $(addprefix $(SRC_DIR)/, $(SRC_FILES))
OBJ = $(SRC:.c=.o)

LIBFT = $(LIBFT_DIR)/libft.a

INCLUDES = -I$(LIBFT_INCLUDES) -I$(SRC_DIR) -I.

# Règles principales
all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME)

# Compilation des objets
$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Compilation de la libft
$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

# Nettoyage
clean:
	rm -f $(OBJ)
	@$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re