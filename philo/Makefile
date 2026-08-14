# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ncruz-ne <ncruz-ne@student.42lisboa.com>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/06/13 17:22:31 by ncruz-ne          #+#    #+#              #
#    Updated: 2026/08/14 09:34:36 by ncruz-ne         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= philo
NAME_DB		= philo_db

SRC_DIR 	= src
OBJ_DIR 	= obj
OBJ_DIR_DB 	= obj_db

UTILS_SRC	= $(addprefix $(SRC_DIR)/utils/, ft_ato_.c ft_calloc.c ft_is_.c \
				time.c write.c)
SRC			= $(addprefix $(SRC_DIR)/, philo.c init.c run_sim.c exit.c) $(UTILS_SRC)
OBJ 		= $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC))
OBJ_DB 		= $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR_DB)/%.o,$(SRC))

HEADERS 	= $(addprefix include/, philo.h flair.h)

CC			= cc
CPPFLAGS	= -Iinclude
CFLAGS		= -Wall -Werror -Wextra -pthread
DB_FLAGS	= -g

RM 			= rm -f

N_PHILO			= 4
T_DIE			= 310
T_EAT			= 200
T_SLEEP			= 100
N_EATS_X_PHILO	= 0
ARGS			= $(N_PHILO) $(T_DIE) $(T_EAT) $(T_SLEEP) $(N_EATS_X_PHILO)

TEST_DIR		= test_logs
SIM_LOG			= sim_log
VALG_LOG		= valg_out
HELG_LOG		= helg_out

ESC             := $(shell printf '\033')
COLOR_RESET     := $(ESC)[0m
VIOLET			:= $(ESC)[38;2;180;140;230m
# DARK_VIOLET     := $(ESC)[38;2;148;0;211m
GREEN           := $(ESC)[32m
# RED             := $(ESC)[31m
# BRIGHT_GREEN    := $(ESC)[92m
# LIGHT_GREEN     := $(ESC)[38;2;144;238;144m
# SPRING_GREEN    := $(ESC)[38;2;0;255;127m
# SOFT_LIME       := $(ESC)[38;2;180;255;180m

SUCCESS         := $(ESC)[38;2;144;238;144m
SUCCESS_BOLD    := $(ESC)[38;2;0;255;127m
INFO            := $(ESC)[38;2;173;216;230m
PATH_COLOR      := $(ESC)[38;2;221;160;221m
# WARNING         := $(ESC)[38;2;255;215;0m
# ERROR_COLOR     := $(ESC)[38;2;255;127;127m
# MUTED           := $(ESC)[38;2;190;190;190m


all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(OBJ) -o $@
	@printf "%b compiled.\n" "$(GREEN)$@$(COLOR_RESET)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADERS)
	@mkdir -p $(dir $@)
	@$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@
	@printf "%b created.\n" "$(SUCCESS)$@$(COLOR_RESET)"

clean:
	@$(RM) $(OBJ)
	@$(RM) -r $(OBJ_DIR)
	@printf "$(INFO)All object files removed.$(COLOR_RESET)\n"

fclean: clean
	@$(RM) $(NAME)
	@printf "$(INFO)Executable removed.$(COLOR_RESET)\n"

re: fclean all

run: re $(NAME)
	@printf "Running $(VIOLET)./$(NAME) $(ARGS)$(COLOR_RESET)\n\n"
	@./$(NAME) $(ARGS)

print: re $(NAME)
	@printf "Running $(VIOLET)./$(NAME) $(ARGS)$(COLOR_RESET)\n\n"
	@./$(NAME) $(ARGS) > $(TEST_DIR)/$(SIM_LOG).txt
	@printf "See simulation logs in $(PATH_COLOR)$(TEST_DIR)/$(SIM_LOG).txt$(COLOR_RESET).\n"

norm:
	@curl -L -o "../en.norm.pdf" \
	"https://raw.githubusercontent.com/neusamcn/philo/main/en.norm.pdf"


#################################### RULES FOR TESTING ####################################
$(NAME_DB): $(OBJ_DB)
	@$(CC) $(OBJ_DB) -o $@
	@printf "%b for debugging compiled.\n" "$(GREEN)$@$(COLOR_RESET)"

$(OBJ_DIR_DB)/%.o: $(SRC_DIR)/%.c $(HEADERS)
	@mkdir -p $(dir $@)
	@$(CC) $(CPPFLAGS) $(CFLAGS) $(DB_FLAGS) -c $< -o $@
	@printf "%b created.\n" "$(SUCCESS)$@$(COLOR_RESET)"

$(TEST_DIR):
	@mkdir -p $@
	@printf "%b created.\n" "$(SUCCESS)/$@$(COLOR_RESET)"

db:
	@gdbtui --args ./$(NAME_DB) $(ARGS)

valg: $(NAME_DB) $(TEST_DIR)
	@valgrind --track-fds=yes --leak-check=full --show-leak-kinds=all -s \
	--log-file=$(TEST_DIR)/$(VALG_LOG).log ./$(NAME_DB) $(ARGS)
	@printf "Valgrind run concluded. \
	See output in $(PATH_COLOR)$(TEST_DIR)/$(VALG_LOG).log$(COLOR_RESET).\n"

hel: $(NAME_DB) $(TEST_DIR)
	@valgrind --tool=helgrind --track-destroy=all -s --log-file=$(TEST_DIR)/$(HELG_LOG).log \
	./$(NAME_DB) $(ARGS)
	@printf "Helgrind run concluded. \
	See output in $(PATH_COLOR)$(TEST_DIR)/$(HELG_LOG).log$(COLOR_RESET).\n"

# TODO: make rule to check stderr?

test: tclean valg hel db

tclean:
	@$(RM) -r $(TEST_DIR)
	@printf "%b for debugging removed.\n" "$(PATH_COLOR)/$(TEST_DIR)$(COLOR_RESET)"
	@$(RM) -r $(OBJ_DIR_DB)
	@$(RM) $(NAME_DB)
	@printf "$(INFO)Debugging executable and object files removed.$(COLOR_RESET)\n"


.PHONY: all clean fclean re run print norm db valg hel test tclean