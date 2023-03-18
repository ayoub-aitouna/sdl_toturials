EXEC	:= window

files	:= main.c

CFLAGS	:= -fsanitize=address -o $(EXEC) -I/Users/aaitouna/homebrew/opt/sdl2/include -L/Users/aaitouna/homebrew/opt/sdl2/lib -lSDL2 -pthread -lm

OBJS	:= $(files:.c=.o)

all	:
	gcc $(files) $(CFLAGS)

race:
	gcc race.c get_map.c  get_next_line/get_next_line.c get_next_line/get_next_line_utils.c $(CFLAGS)

$(EXEC)	: all

clean	:
	rm -rf $(OBJS) 

fclean	: clean
	rm -rf $(EXEC)
       
re	: fclean $(EXEC)
