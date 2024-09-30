#include "include/raylib.h"

int main()
{
    //SetTraceLogLevel(LOG_ERROR);
    InitWindow(1920, 1080, "Pong");
    InitAudioDevice();
    SetTargetFPS(60);

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

        // Input
        
        if (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP)) playerPos -= speed;

        if (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN)) playerPos += speed;


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
            DrawRectangle(390, playerPos + 140, 20, 200, WHITE);
            DrawCircle(ballPosX + 360, ballPosY + 140, 15, WHITE);
            DrawRectangle(1150 + 360, enemyPos + 140, 20, 200, WHITE);

            for (int i = 0; i < 20; i++)
            {
                DrawRectangle(590 + 360, i * 40 + 140, 10, 20, WHITE);
            }

            DrawText(TextFormat("%i", playerPoints), 300 + 360, 50 + 140, 200, WHITE);
            DrawText(TextFormat("%i", enemyPoints), 800 + 360, 50 + 140, 200, WHITE);

        EndDrawing();
    }

    UnloadSound(hit);
    UnloadSound(win);
    UnloadSound(loss);
    
    CloseAudioDevice();

    CloseWindow();

    return 0;
}
