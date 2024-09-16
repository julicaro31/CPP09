NAME = btc
OBJ_DIR	= obj
SRCS = main.cpp BitcoinExchange.cpp
OBJS = ${SRCS:%.cpp=$(OBJ_DIR)/%.o}
HEADER = BitcoinExchange.hpp
CC = c++
FLAGS = -Wall -Wextra -Werror -std=c++11

$(OBJ_DIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CC) $(FLAGS) -c -o $@ $^

all: $(NAME)

$(NAME): $(OBJS) $(HEADER)
	$(CC) $(FLAGS) $(OBJS) -o $(NAME)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re