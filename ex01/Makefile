NAME := RPN
FLAGS := -Wall -Wextra -Werror -std=c++98 -g
FILES := main.cpp RPN.cpp
OBJ := $(FILES:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJ)
	c++ $(FLAGS) $(OBJ) -o $@

%.o: %.cpp
	c++ $(FLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all