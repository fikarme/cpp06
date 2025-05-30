NAME    	= convert
CPP     	= c++
CPPFLAGS	= -std=c++98 -Wall -Wextra -Werror
RM			= rm -rf
SRCS    	= $(wildcard *.cpp)

all: $(NAME)

$(NAME): $(SRCS)
	@$(CPP) $(CPPFLAGS) $(SRCS) -o $(NAME)

clean:
	@echo "no o files to clean"

fclean: 
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re