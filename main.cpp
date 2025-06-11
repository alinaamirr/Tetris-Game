#include <raylib.h>
#include "game.h"
#include "colors.h"
#include <iostream>

double lastUpdateTime = 0;

bool EventTriggered(double interval)
{
    double currentTime = GetTime();
    if (currentTime - lastUpdateTime >= interval)
    {
        lastUpdateTime = currentTime;
        return true;
    }
    return false;
}

int main()
{
    InitWindow(500, 620, "Tetris");
    SetTargetFPS(60);

    Font font = LoadFontEx("Font/monogram.ttf", 64, 0, 0);

    Game game = Game();
    bool gameOverHandled = false;

    while (!WindowShouldClose())
    {
        UpdateMusicStream(game.music);
        game.HandleInput();
        if (EventTriggered(0.2))
        {
            game.MoveBlockDown();
        }

        BeginDrawing();
        ClearBackground(darkBlue);
        DrawTextEx(font, "Score", {365, 15}, 38, 2, WHITE);
        DrawTextEx(font, "Next", {370, 145}, 38, 2, WHITE);
        DrawTextEx(font, "Highestscore", {315,400}, 30, 2, WHITE);
        DrawRectangleRounded({320, 55, 170, 60}, 0.3, 6, lightBlue);//score
        DrawRectangleRounded({320, 435, 170, 180}, 0.3, 6, lightBlue);//highest score

        char highestscore[10];
        sprintf(highestscore, "%d", game.highestScore);
        Vector2 texts = MeasureTextEx(font, highestscore, 38, 2);
        DrawTextEx(font, highestscore, {320 + (170 - texts.x) / 2, 500}, 38, 2, WHITE);

        char scoreText[10];
        sprintf(scoreText, "%d", game.score);
        Vector2 textSize = MeasureTextEx(font, scoreText, 38, 2);

        DrawTextEx(font, scoreText, {320 + (170 - textSize.x) / 2, 65}, 38, 2, WHITE);
        DrawRectangleRounded({320, 200, 170, 180}, 0.3, 6, lightBlue);//Next
        game.Draw();
        
        EndDrawing();
        
        if (game.gameOver && !gameOverHandled)
        {
            game.Storingfile();
            gameOverHandled = true;
        }
        
        if (gameOverHandled)
        {
            if (IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_ESCAPE) || IsKeyPressed(KEY_SPACE))
            {
                break;
            }
        }
        sprintf(highestscore, "%d", game.highestScore);
        DrawTextEx(font, highestscore, {320 + (170 - texts.x) / 2, 500}, 38, 2, WHITE);
    }
    
    CloseWindow();
    return 0;
}


