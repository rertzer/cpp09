CXX = c++

CXXFLAGS = -Wall -Wextra -Werror -std=c++98 -g3

NAME = PmergeMe 

SRC_DIR = ./

OBJ_DIR = obj/

INC_DIR = ./

SOURCES = main.cpp PmergeMe.cpp PmergeMeL.cpp Number.cpp NbVector.cpp NbList.cpp

OBJ = $(SOURCES:.cpp=.o)

OBJS = $(addprefix $(OBJ_DIR), $(OBJ))
DEPS = $(OBJS:.o=.d)

all: $(NAME) 

$(OBJ_DIR)%.o: $(SRC_DIR)%.cpp
	$(CXX) $(CXXFLAGS) -c -MMD $< -o $@ -I $(INC_DIR)


$(NAME): $(OBJ_DIR) $(OBJS)
	$(CXX) $(CXXFLAGS) -o  $@ $(OBJS)

$(OBJ_DIR):
	mkdir  $(OBJ_DIR)

clean:
	rm -f $(OBJS)
	rm -f $(DEPS)
	rm -fd $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean
	make all

-include $(DEPS)

.PHONY: all clean fclean re
