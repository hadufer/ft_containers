SRCS_TEST    =  test.cpp
SRCS_TIME    =  test_time.cpp
OSRCS_TEST   =  ${SRCS_TEST:.cpp=.o}
OSRCS_TIME   =  ${SRCS_TIME:.cpp=.o}
NAME_TEST_FT =  test_ft
NAME_TEST_STD = test_std
NAME_TIME =     test_time

all : ${NAME_TIME} ${NAME_TEST_FT} ${NAME_TEST_STD} 

%.o: %.cpp 
	c++ -Wall -Werror -Wextra -std=c++98 -I./include -fsanitize=address -c $< -o ${<:.cpp=.o} -g

${NAME_TEST_FT} :
	c++ -Wall -Werror -Wextra -std=c++98 -I./include -D NAMESPACE=ft ${SRCS_TEST} -o ${NAME_TEST_FT} 

${NAME_TEST_STD} :
	c++ -Wall -Werror -Wextra -std=c++98 -I./include -D NAMESPACE=std ${SRCS_TEST} -o ${NAME_TEST_STD} 

${NAME_TIME} :  ${OSRCS_TIME}
	c++ -Wall -Werror -Wextra -std=c++98 -fsanitize=address  ${OSRCS_TIME} -o ${NAME_TIME} -g

clean :
	rm -f ${OSRCS_TEST} ${OSRCS_TIME}

fclean : clean
	rm -f ${NAME_TEST_FT} ${NAME_TEST_STD} ${NAME_TIME}

re : fclean all

.PHONY: all clean fclean re
