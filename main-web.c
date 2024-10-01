#include "include/raylib.h"
#include <stdlib.h>

int main()
{
    SetTraceLogLevel(LOG_ERROR);
    InitWindow(1920, 1080, "Pong");
    InitAudioDevice();
    SetTargetFPS(60);

    int room = 0;

    int buttons[3][5] = {{400, 250, 400, 50, 0}, {400, 350, 400, 50, 0}};
    char button_text[3][10] = {"Play", "About"};

    Sound hit = LoadSound("sounds/hit.wav");
    Sound win = LoadSound("sounds/win.wav");
    Sound loss = LoadSound("sounds/loss.wav");

    int playerPos = 300;
    int playerPoints = 0;
    int speed = 5;

    int ballPosX = 400;
    int ballPosY = 380;
    int ballDir = -1;
    int ballSpeed = 10;
    int ballUpVel = 0;

    int enemyPos = 300;
    int enemyPoints = 0;

    while (!WindowShouldClose())
    {

        if (room == 0)
        {

            Vector2 mousePos = { -100.0f, -100.0f };
            mousePos = GetMousePosition();

            for (int i = 0; i < sizeof(buttons) / sizeof(buttons[0]); i++)
            {
                if (mousePos.x > buttons[i][0] + 360 && mousePos.x < buttons[i][0] + 360 + buttons[i][2] && mousePos.y > buttons[i][1] + 70 - 30 && mousePos.y < buttons[i][1] + 70 - 30 + buttons[i][3])
                {
                    buttons[i][4] = 1;

                    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
                    {
                        room = i + 1;
                    }

                } else
                {
                    buttons[i][4] = 0;
                }
            }


            BeginDrawing();
                ClearBackground(BLACK);
                for (int i = 0; i < sizeof(buttons) / sizeof(buttons[0]); i++)
                {
                    if (buttons[i][4] == 0)
                    {
                        DrawRectangle(buttons[i][0] + 360, buttons[i][1] + 70, buttons[i][2], buttons[i][3], BLUE);
                    } else
                    {
                        DrawRectangle(buttons[i][0] + 360, buttons[i][1] + 70, buttons[i][2], buttons[i][3], SKYBLUE);
                    }
                    DrawText(button_text[i], buttons[i][0] + 100 + 360, buttons[i][1] + 70, 50, WHITE);
                }
            EndDrawing();
        } else if (room == 1)
        {
            // Input
            
            if (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP)) playerPos -= speed;

            if (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN)) playerPos += speed;

            if (IsKeyDown(KEY_P)) room = 0;


            // Update
                    
            if (playerPos > 600) playerPos = 600;
            if (playerPos < 0) playerPos = 0;

            ballPosX += ballSpeed * ballDir;
            ballPosY += ballUpVel;


            if (ballPosX == 50 && ballPosY > playerPos && ballPosY < playerPos + 200)
            {
                PlaySound(hit);
                ballDir = 1;
                float offset = ((float)(ballPosY - (playerPos + 100)) / 200) * -3.0;
                ballUpVel += offset * 5;
            }

            if (ballPosX == 1150 && ballPosY > enemyPos && ballPosY < enemyPos + 200)
            {
                PlaySound(hit);
                ballDir = -1;
                float offset = ((float)(ballPosY - (enemyPos + 100)) / 200) * 3.0;
                ballUpVel += offset * 5;
            }

            if (ballPosY > enemyPos + 100) enemyPos += speed;
            if (ballPosY < enemyPos + 100) enemyPos -= speed;

            if (enemyPos > 600) enemyPos = 600;
            if (enemyPos < 0) enemyPos = 0;


            if (ballPosY >= 800 || ballPosY <= 0)
            {
                ballUpVel *= -1;
                PlaySound(hit);
            }


            if (ballPosX > 1200 || ballPosX < 0)
            {

                if (ballPosX > 1200)
                {
                    playerPoints += 1;
                    PlaySound(win);
                }
                else
                {
                    enemyPoints += 1;
                    PlaySound(loss);
                }

                playerPos = 300;

                ballPosX = 400;
                ballPosY = 380;
                ballUpVel = 0;
                ballDir = -1;

                enemyPos = 300;
            }


            // Render

            BeginDrawing();

                ClearBackground(BLACK);

                DrawRectangle(30 + 360, playerPos + 70, 20, 200, WHITE);
                DrawCircle(ballPosX + 360, ballPosY + 70, 15, WHITE);
                DrawRectangle(1150 + 360, enemyPos + 70, 20, 200, WHITE);

                for (int i = 0; i < 20; i++)
                {
                    DrawRectangle(590 + 360, i * 40 + 70, 10, 20, WHITE);
                }

                DrawText(TextFormat("%i", playerPoints), 300 + 360, 50 + 70, 200, WHITE);
                DrawText(TextFormat("%i", enemyPoints), 800 + 360, 50 + 70, 200, WHITE);

            EndDrawing();
        } else if (room == 2)
        { 

            int hover = 0;

            Vector2 mousePos = { -100.0f, -100.0f };
            mousePos = GetMousePosition();

            for (int i = 0; i < sizeof(buttons) / sizeof(buttons[0]); i++)
            {
                if (mousePos.x > 300 + 360 && mousePos.x < 300 + 360 + 400 && mousePos.y > 500 + 70 - 30 && mousePos.y < 500 + 70 -30 + 50)
                {
                    hover = 1;

                    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
                    {
                        room = 0;
                    }

                } else
                {
                    hover = 0;
                }
            }


            BeginDrawing();
                ClearBackground(BLACK);
                DrawText("About", 300 + 360, 50 + 70, 200, WHITE);
                DrawText("This is a pong game", 320 + 360, 300 + 70, 50, WHITE);

                if (hover == 0)
                {
                    DrawRectangle(300 + 360, 500 + 70, 400, 50, BLUE);
                } else
                {
                    DrawRectangle(300 + 360, 500 + 70, 400, 50, SKYBLUE);
                }
                DrawText("Back", 300 + 100 + 360, 500 + 70, 50, WHITE);
            EndDrawing();

        }
    }

    UnloadSound(hit);
    UnloadSound(win);
    UnloadSound(loss);
    
    CloseAudioDevice();

    CloseWindow();

    return 0;
}
