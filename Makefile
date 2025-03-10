# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: svidot <svidot@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/04 06:54:46 by svidot            #+#    #+#              #
#    Updated: 2023/12/04 06:54:46 by svidot           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LIBFT_DIR = ft_printf/libft
FT_PRINTF_DIR = ft_printf
GNL_DIR = gnl
SRC_DIR = sources
HEADERS_DIR = include
MLX = mlx_linux
BONUS_DIR = bonus
SRC_BONUS_DIR = $(BONUS_DIR)/sources

CC = cc
CFLAGS = -I$(LIBFT_DIR) -I$(GNL_DIR) -I$(FT_PRINTF_DIR) -I$(HEADERS_DIR) -I$(MLX) -O3 -Wall -Wextra -Werror
LDFLAGS = -L$(MLX) -lmlx_Linux -lXext -lX11 -lm -lz
#CFLAGS_BONUS =

SOURCES = $(SRC_DIR)/main.c $(SRC_DIR)/setup.c $(GNL_DIR)/get_next_line.c $(GNL_DIR)/get_next_line_utils.c \
$(SRC_DIR)/draw_line.c $(SRC_DIR)/event.c $(SRC_DIR)/loop.c $(SRC_DIR)/matrix.c $(SRC_DIR)/pixels.c \
$(SRC_DIR)/points.c $(SRC_DIR)/set_matrix.c $(SRC_DIR)/utils.c

SOURCES_BONUS = $(SRC_BONUS_DIR)/main.c $(SRC_BONUS_DIR)/setup.c $(GNL_DIR)/get_next_line.c $(GNL_DIR)/get_next_line_utils.c \
$(SRC_BONUS_DIR)/draw_line.c $(SRC_BONUS_DIR)/event.c $(SRC_BONUS_DIR)/loop.c $(SRC_BONUS_DIR)/matrix.c $(SRC_BONUS_DIR)/pixels.c \
$(SRC_BONUS_DIR)/points.c $(SRC_BONUS_DIR)/set_matrix.c $(SRC_BONUS_DIR)/utils.c

OBJECTS = $(SOURCES:.c=.o)
OBJECTS_BONUS = $(SOURCES_BONUS:.c=_bonus.o)

LIBFTPRINTF = $(FT_PRINTF_DIR)/libftprintf.a
NAME = fdf
NAME_BONUS = $(BONUS_DIR)/$(NAME)

HEADERS = $(GNL_DIR)/get_next_line.h $(HEADERS_DIR)/main.h $(HEADERS_DIR)/loop.h $(HEADERS_DIR)/pixels.h $(HEADERS_DIR)/setup.h
#HEADERS_BONUS = 

.PHONY: all ft_printf bonus clean fclean re intro l newline backline emoticon

$(SRC_DIR)/%.o : $(SRC_DIR)/%.c $(LIBFTPRINTF) $(HEADERS)
	@echo "\033[0;32m compiling $(NAME) object $<...\033[0m" 🚀
	@$(CC) $(CFLAGS) $< -c -o $@

$(GNL_DIR)/%.o : $(GNL_DIR)/%.c $(HEADERS)
	@echo "\033[0;32m compiling $(NAME) object $<...\033[0m" 🚀
	@$(CC) $(CFLAGS) $< -c -o $@

$(BONUS_DIR)/%_bonus.o : $(BONUS_DIR)/%.c $(LIBFTPRINTF) $(HEADERS) 
	@echo "\033[0;32m compiling $(NAME) object bonus $<...\033[0m" 🚀
	@$(CC) $(CFLAGS) $(CFLAGS_BONUS) $< -c -o $@

$(GNL_DIR)/%_bonus.o : $(GNL_DIR)/%.c $(HEADERS)
	@echo "\033[0;32m compiling $(NAME) object bonus $<...\033[0m" 🚀
	@$(CC) $(CFLAGS) $< -c -o $@

all: intro ft_printf $(NAME) emoticon		

l: ft_printf $(NAME)
	
ft_printf: emoticon
#	@$(MAKE) -s -C $(LIBFT_DIR) bonus 
	@$(MAKE) -s -C $(FT_PRINTF_DIR) 

$(NAME) : $(OBJECTS) 
	@echo "\n\033[0;32m linking $(NAME) objects with $(LIBFTPRINTF)...\033[0m 🚀\n\n 💗 💎 💎 💗\n"
	@$(CC) $(OBJECTS) $(LDFLAGS) $(LIBFTPRINTF) -o $@

bonus: ft_printf $(NAME_BONUS)
	@echo " 💎 🧯 🔥 😵\n"

$(NAME_BONUS) : $(OBJECTS_BONUS)
	@echo "\n\033[0;32m linking $(NAME) objects and objects bonus with $(LIBFTPRINTF) to $(NAME_BONUS) \033[0m 🚀\n"
	@$(CC) $(OBJECTS_BONUS) $(LDFLAGS) $(LIBFTPRINTF) -o $@

emoticon:
	@echo "\n 💗 😀 😃 😍\n"

newline: 
	@echo ""

backline: 
	@echo "\033[A\033[A"

intro:
	clear
	@sleep 1
	@echo -n " Wake"
	@sleep .4
	@echo " up...\n"
	@sleep .1
	@echo -n " "
	@letters="The Makefile has you..."; \
	echo "\033[1;92m$$letters\033[0m" | awk '{split($$0, chars, ""); \
	for (i = 1; i <= length($$0); i++) \
	{printf "%s", chars[i]; system("sleep 0.2");}} \
	system("sleep 1");' 
	@words="\n\n\tFollow \n\t\tthe \t\b\b\033[0;96mColored! \
	\n\n\t\t\b\b\b\b\b\b\033[1;95mUnicorne!\033[0m...🦄\n\n"; \
	for j in $${words}; do \
		echo -n "$$j"; \
		sleep .4; \
	done
	@sleep .4
	@cat mfile_design	

clean:
	@echo "\n cleanning $(NAME) objects 🧻"
	@rm -f $(OBJECTS) $(OBJECTS_BONUS);
	@$(MAKE) -C $(FT_PRINTF_DIR) clean -s
	@echo ""

fclean: 
	@echo "\n cleanning $(NAME) objects 🧻"
	@rm -f $(OBJECTS) $(OBJECTS_BONUS);
	@echo " cleanning $(NAME) 🚽" 
	@rm -f $(NAME) $(NAME_BONUS)
	@$(MAKE) -C $(FT_PRINTF_DIR) fclean -s
	@echo ""

re: fclean backline l
