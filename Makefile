compile:
	g++ Snake.cpp -lSDL2 -lSDL2_ttf -lSDL2_image
	./a.out
debug:
	g++ Snake.cpp -lSDL2 -lSDL2_ttf -lSDL2_image
	gdb ./a.out
