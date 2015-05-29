CC = clang
XX = clang++
CFLAGS = -Wall -g -std=c++11
INCLUDE = -I./include/

LIBS = -lm
OBJS = main.o data.o extract.o train.o user_mannual.o
NAME = KeywordExtractor

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@	
%.o: %.cc
	$(XX) $(CFLAGS) $(INCLUDE) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS)
	$(XX) -o $(NAME) $(OBJS) $(LIBS)

clean:
	rm -f *.o
	rm -f KeywordExtractor 
