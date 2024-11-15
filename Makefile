GameOfLife:
	clang -framework CoreVideo -framework IOKit -framework Cocoa -framework GLUT -framework OpenGL ../lib/libraylib.a GameOfLife.c -o GameOfLife 

