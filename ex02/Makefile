NAME    	= lain
CPP     	= c++
CPPFLAGS	= -std=c++98 -Wall -Wextra -Werror
RM			= rm -rf
OBJDIR		= Obj
OBJ			= $(addprefix $(OBJDIR)/, $(SRCS:.cpp=.o))
OBJS		= $(SRCS:.cpp=.o)
SRCS    	= main.cpp

all: $(NAME)

$(NAME): $(OBJ)
    @$(CPP) $(CPPFLAGS) $(OBJ) -o $(NAME)

$(OBJDIR)/%.o: %.cpp
    @mkdir -p $(OBJDIR)
    @$(CPP) $(CPPFLAGS) -c $< -o $@

clean:
    @$(RM) $(OBJ)

fclean: clean
    @$(RM) $(NAME)

re: fclean all

e: fclean all
    @./$(NAME)

.PHONY: all clean fclean re e