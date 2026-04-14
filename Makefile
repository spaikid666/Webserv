NAME 					= webserv

C++						= c++ -std=c++98

STD_FLAGS 				= -Wall -Wextra -Werror

SRCS					= src/main.cpp\
						  src/Location.cpp\
                          src/Server.cpp\
						  src/Socket.cpp\
						  utils/FileCheck.cpp\
						  utils/Parse.cpp\
						  utils/SocketConfig.cpp\
						  

OBJS					= ${SRCS:.cpp=.o}

REMOVE					= rm -f ${OBJS}

all:					${NAME}

${NAME}:
						${C++} ${SRCS} ${STD_FLAGS} -o ${NAME}

clean:					
						${REMOVE}

fclean:					clean
						rm -f webserv
						
re:						fclean all

.PHONY:					all clean fclean re