NAME		=	containers
OBJS_DIR	=	./objs
SRCS_DIR	=	.
HPP_DIR		=	./include

HEADERS		=	main.hpp	


SRC_FILES	=	main.cpp			


SRCS = $(addprefix $(SRCS_DIR)/, $(SRC_FILES))
OBJS = $(patsubst $(SRCS_DIR)/%.cpp,$(OBJS_DIR)/%.o, $(SRCS))
DEPS = $(OBJS:.o=.d)

CXXFLAGS		= -Wall -Wextra -Werror -Iinclude -std=c++98
CXXFLAGS_H		= -MMD -MP
RM				= rm -f
CXX				= clang++

all:		$(NAME)

-include $(DEPS)
$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.cpp $(HEADERS) | $(OBJS_DIR)
	${CXX} $(CXXFLAGS) $(CXXFLAGS_H) -c $< -o $@

$(OBJS_DIR):
	@mkdir -p $(OBJS_DIR)

${NAME}: 	${OBJS}
	${CXX} $(CXXFLAGS) $(CXXFLAGS_H) -o ${NAME} ${OBJS}

clean:
				$(RM) $(OBJS) $(DEPS)
				rm -rf $(OBJS_DIR)

fclean:			clean
				$(RM) $(NAME)

re:				fclean $(NAME)

.PHONY:			all clean fclean re
