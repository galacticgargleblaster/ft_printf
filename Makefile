# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: student <student@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/10/01 10:18:11 by nkirkby           #+#    #+#              #
#    Updated: 2019/04/06 21:18:37 by student          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

SOURCE_DIR = .
SOURCES = $(wildcard $(SOURCE_DIR)/*.c)
SOURCE_BASENAMES = $(notdir $(SOURCES))

LIBFT_DIR = ./lib/libft
LIBLIST_DIR = ./lib/liblist
INCLUDES = .
CC = clang
CPP = clang -E
CFLAGS = -Wall -Werror -Wextra -I$(INCLUDES)
LINKER_FLAGS = -lft -L$(LIBFT_DIR) -llist -L$(LIBLIST_DIR)

# ------------------------------------------------------------------------------#
# This method of directory creation is adapted from:
# https://gist.github.com/maxtruxa/4b3929e118914ccef057f8a05c614b0f

# intermediate directory for generated object files
OBJECT_DIR := .o

# object files, auto generated from source files
OBJECTS := $(patsubst %,$(OBJECT_DIR)/%.o,$(basename $(SOURCE_BASENAMES)))
# ------------------------------------------------------------------------------#

.SUFFIXES: # remove the default suffix rules, because the GNU Make manual states:
# Suffix rules are the old-fashioned way of defining implicit rules for make.
# Suffix rules are obsolete because pattern rules are more general and clearer.
# They are supported in GNU make for compatibility with old makefiles.
all: $(NAME)

$(NAME): $(OBJECTS)
	ar -r $@ $^ $(LIBFT_DIR)/.o/*.o $(LIBLIST_DIR)/.o/*.o

# https://stackoverflow.com/questions/38110010/pattern-rule-with-files-in-different-directories
$(OBJECT_DIR)/%.o: $(SOURCE_DIR)/%.c $(INCLUDES)
	make -C $(LIBFT_DIR)
	make -C $(LIBLIST_DIR)
	$(shell mkdir -p $(dir $(OBJECTS)) >/dev/null)
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	make -C $(LIBFT_DIR) clean
	make -C $(LIBLIST_DIR) clean

fclean: clean
	/bin/rm -f $(NAME)
	/bin/rm -rf $(NAME).dSYM
	make -C $(LIBFT_DIR) fclean
	make -C $(LIBLIST_DIR) fclean

re: clean all

test: fclean
	$(MAKE) CFLAGS+='-g' all
	$(CC) $(CFLAGS) -g $(LINKER_FLAGS) -lftprintf -L. .test.c -o test
	
# To make debug