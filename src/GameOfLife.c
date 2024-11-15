#include <math.h>
#include <raylib.h>
#include <stdio.h>

#define SIZE 5

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
        DrawLineV(startPos, endPos, MAGENTA);
    }

    // col
    for (int i = 0; i < WIDTH; i += SIZE)
    {
        Vector2 startPos = {i, 0};
        Vector2 endPos = {i, HEIGHT};
        DrawLineV(startPos, endPos, MAGENTA);
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

    int xDir[8] = {1, 0, -1, 0, -1, 1, 1, -1};
    int yDir[8] = {0, 1, 0, -1, -1, 1, -1, 1};

    Vector2 selectPos = {SIZE, SIZE};
    Vector2 selectSize = {SIZE, SIZE};

    Color selectColor = BLUE;

    bool canRun = false;
    bool reset = false;
    bool isPressed = false;

    // Main game loop
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        int key = GetKeyPressed();

        Vector2 mousePos = GetMousePosition();

        selectPos.x = (floor(mousePos.x / SIZE));
        selectPos.y = (floor(mousePos.y / SIZE));

        isPressed = IsMouseButtonDown(MOUSE_BUTTON_LEFT);

        reset = IsKeyPressed(KEY_R);
        if (IsKeyPressed(KEY_P))
        {
            canRun = true;
        }

        if (reset)
        {
            canRun = false;
            for (int i = 0; i < GRIDHEIGHT; i++)
            {
                for (int j = 0; j < GRIDWIDTH; j++)
                {
                    grid[i][j] = 0;
                }
            }
        }

        int backGrid[GRIDHEIGHT][GRIDWIDTH] = {0};

        for (int i = 0; i < GRIDHEIGHT; i++)
        {
            for (int j = 0; j < GRIDWIDTH; j++)
            {
                backGrid[i][j] = grid[i][j];
            }
        }

        if (canRun)
        {
            for (int i = 1; i < GRIDHEIGHT - 1; i++)
            {
                for (int j = 1; j < GRIDWIDTH - 1; j++)
                {
                    int alive = 0;
                    for (int k = 0; k < 8; k++)
                    {
                        int dy = i + yDir[k];
                        int dx = j + xDir[k];

                        if (backGrid[dy][dx])
                        {
                            alive++;
                        }
                    }
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
        }

        BeginDrawing();
        ClearBackground(BLACK);

        if (canRun == false)
        {
            Vector2 pos;
            pos.x = selectPos.x * SIZE;
            pos.y = selectPos.y * SIZE;
            DrawRectangleV(pos, selectSize, selectColor);
            if (isPressed)
            {
                grid[(int)selectPos.y][(int)selectPos.x] = 1;
            }
        }
        for (int i = 0; i < GRIDHEIGHT; i++)
        {
            for (int j = 0; j < GRIDWIDTH; j++)
            {
                if (grid[i][j] == true)
                {
                    Vector2 pos = {j * SIZE, i * SIZE};
                    Vector2 size = {SIZE, SIZE};
                    DrawRectangleV(pos, size, WHITE);
                }
            }
        }
        EndDrawing();
    }

    CloseWindow();

    return 0;
}
