EXEC	:= App

files	:= main.c

CFLAGS	:= `sdl2-config --libs --cflags` -ggdb3 -O0 --std=c99 -Wall -lm

OBJS	:= $(files:.c=.o)

all	: $(OBJS)
	cc $(CFLAGS) $(OBJS) -lSDL2 -o $(EXEC) 

$(EXEC)	: all

clean	:
	rm -rf $(OBJS)

fclean	: clean
	rm -rf $(EXEC)
       
re	: fclean $(EXEC)
