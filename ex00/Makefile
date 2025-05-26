NAME    	= lain
CPP     	= c++
CPPFLAGS	= -std=c++98 -Wall -Wextra -Werror
RM			= rm -rf
OBJDIR		= Obj
SRCS    	= $(wildcard *.cpp)
OBJ			= $(addprefix $(OBJDIR)/, $(SRCS:.cpp=.o))

$(OBJDIR)/%.o: %.cpp
	@mkdir -p $(OBJDIR)
	@$(CPP) $(CPPFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJ)
	@$(CPP) $(CPPFLAGS) $(OBJ) -o $(NAME)

clean:
	@$(RM) $(OBJDIR)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

e: fclean $(NAME)
	@./$(NAME)
	@$(RM) $(OBJDIR)
	@$(RM) $(NAME)

.PHONY: all clean fclean re e