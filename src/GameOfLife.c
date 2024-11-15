#include "../include/raylib.h"
#include <math.h>
#include <stdio.h>
#include <string.h>

#define SIZE 10

#define WIDTH 1200
#define HEIGHT 720

#define GRIDWIDTH WIDTH / SIZE
#define GRIDHEIGHT HEIGHT / SIZE

void drawGrid()
{
    // row
    for (int i = 0; i < HEIGHT; i += SIZE)
    {
        Vector2 startPos = {0, i};
        Vector2 endPos = {WIDTH, i};
        DrawLineV(startPos, endPos, LIGHTGRAY);
    }

    // col
    for (int i = 0; i < WIDTH; i += SIZE)
    {
        Vector2 startPos = {i, 0};
        Vector2 endPos = {i, HEIGHT};
        DrawLineV(startPos, endPos, LIGHTGRAY);
    }
}

int main()
{

    InitWindow(WIDTH, HEIGHT, "GameOfLife");

    SetTargetFPS(60); // Set our game to run at 60 frames-per-second

    int fps = 60;
    int tick = 0;
    int tickRate = 5;

    int grid[GRIDHEIGHT][GRIDWIDTH] = {0};

    int xDir[4] = {1, 0, -1, 0};
    int yDir[4] = {0, 1, 0, -1};

    Vector2 selectPos = {SIZE, SIZE};
    Vector2 selectSize = {SIZE, SIZE};

    Color selectColor = BLUE;

    bool canRun = false;

    // Main game loop
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        int key = GetKeyPressed();

        Vector2 mousePos = GetMousePosition();

        selectPos.x = floorf(mousePos.x / SIZE);
        selectPos.y = floorf(mousePos.y / SIZE);

        bool isPressed = IsMouseButtonDown(MOUSE_BUTTON_LEFT);

        if (IsKeyPressed(KEY_P))
        {
            canRun = true;
        }

        if ((tick == fps / tickRate) && canRun)
        {
            int backGrid[GRIDHEIGHT][GRIDWIDTH] = {0};

            memcpy(backGrid, grid, sizeof(int) * GRIDHEIGHT * GRIDWIDTH);

            for (int i = 1; i < GRIDHEIGHT; i++)
            {
                for (int j = 1; j < GRIDWIDTH - 1; j++)
                {
                    int alive = 0;
                    for (int k = 0; k < 4; k++)
                    {
                        int dy = i + yDir[k];
                        int dx = j + xDir[k];

                        if (backGrid[dy][dx])
                        {
                            alive++;
                        }
                    }
                    if (backGrid[i - 1][j - 1])
                        alive++;
                    if (backGrid[i - 1][j + 1])
                        alive++;
                    if (backGrid[i + 1][j - 1])
                        alive++;
                    if (backGrid[i + 1][j + 1])
                        alive++;
                    if (backGrid[i][j])
                    {
                        if (alive > 3 || alive < 2)
                        {
                            grid[i][j] = 0;
                        }
                    }
                    else
                    {
                        if (alive == 3)
                        {
                            grid[i][j] = 1;
                        }
                    }
                }
            }
            tick = 0;
        }

        BeginDrawing();
        ClearBackground(BLACK);
        Vector2 pos;
        if (!canRun)
        {
            pos.x = selectPos.x * SIZE;
            pos.y = selectPos.y * SIZE;
            DrawRectangleV(pos, selectSize, selectColor);
            if (isPressed)
            {
                grid[(int)pos.y][(int)pos.x] = 1;
            }
        }

        char posx[64];
        sprintf(posx, "%f", selectPos.x);
        char posy[64];
        sprintf(posy, "%f", selectPos.y);

        DrawText(posx, 0, 0, 20, GREEN);
        DrawText(posx, 0, 20, 20, GREEN);

        // draw
        for (int i = 0; i < GRIDHEIGHT; i++)
        {
            for (int j = 0; j < GRIDWIDTH; j++)
            {
                if (grid[i][j])
                {
                    Vector2 pos = {j * SIZE, i * SIZE};
                    Vector2 size = {SIZE, SIZE};
                    DrawRectangleV(pos, size, WHITE);
                }
            }
        }
        tick++;
        if (tick >= fps)
            tick = 0;
        EndDrawing();
    }

    CloseWindow();

    return 0;
}
