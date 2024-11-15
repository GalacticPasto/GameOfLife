echo "Building"
gcc src/GameOfLife.c -o build/GameOfLife -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -g 
