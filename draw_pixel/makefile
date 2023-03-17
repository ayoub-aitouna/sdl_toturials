EXEC	:= App

files	:= main.c parsing/get_map.c

third_party := get_next_line/get_next_line.c get_next_line/get_next_line_utils.c

# CFLAGS	:= `sdl2-config --libs --cflags` -ggdb3 -O0 --std=c99

OBJS	:= $(files:.c=.o)
third_party_OBJS	:= $(third_party:.c=.o)

ubuntu	: $(OBJS) $(third_party_OBJS)
	cc $(CFLAGS) $(OBJS) $(third_party_OBJS) -L/Users/aaitouna/homebrew/opt/sdl2/lib -I/Users/aaitouna/homebrew/opt/sdl2/include  -lSDL2 -o $(EXEC) 

macos	: $(third_party_OBJS)
	gcc $(files) $(third_party_OBJS) -fsanitize=address -o APP -I/Users/aaitouna/homebrew/opt/sdl2/include -L/Users/aaitouna/homebrew/opt/sdl2/lib -lSDL2

$(EXEC)	: all

clean	:
	rm -rf $(OBJS) $(third_party_OBJS)

fclean	: clean
	rm -rf $(EXEC)
       
re	: fclean $(EXEC)
