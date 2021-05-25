CFLAGS = -O3 `sdl2-config --cflags`
LDFLAGS = `sdl2-config --libs` -lSDL2 -lSDL2_ttf -lm

INC = sdl2-light.h definition.h graphique.h logique.h sdl2-ttf-light.h transition.h menu.h
SRC = main.c sdl2-light.c logique.c graphique.c sdl2-ttf-light.c transition.c menu.c
OBJ = $(SRC:%.c=%.o)

PROG = spacecorridor

%.o: %.c $(INC)
	gcc $(CFLAGS) -c $<

spacecorridor: $(OBJ)
	gcc $(CFLAGS) $(OBJ) $(LDFLAGS) -o $@

doc: $(PROG)
	doxygen ./$(PROG)
	make -C latex

clean:
	rm -f *~ *.o $(PROG)
	rm -rf latex html

