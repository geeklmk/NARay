/*
 * Project:    NARay
 * File:       NARay.cpp
 * Author:     Luca 'aXon' Marchetti
 *
 * Description:
 *   Main test file for NARay functions
 *
 * License: LGPL 2.1
 * 
 */

import SpriteAnimator;
import SGui;

#include "raylib.h"
#include <iostream>
#include "tweeny/tweeny.h"

using namespace NARay;

int main(void)
{
    const int screenWidth = 928;
    const int screenHeight = 793;

    // Windows init, must be done before loading textures
    InitWindow(screenWidth, screenHeight, "NARay, library test");
    SetTargetFPS(60);

    // Background loading
    
    Texture2D bgLayer11 = LoadTexture("resources/forest/Layer_0011_0.png");
    Texture2D bgLayer10 = LoadTexture("resources/forest/Layer_0010_1.png");
    Texture2D bgLayer09 = LoadTexture("resources/forest/Layer_0009_2.png");
    Texture2D bgLayer08 = LoadTexture("resources/forest/Layer_0008_3.png");
    Texture2D bgLayer07 = LoadTexture("resources/forest/Layer_0007_Lights.png");
    Texture2D bgLayer06 = LoadTexture("resources/forest/Layer_0006_4.png");
    Texture2D bgLayer05 = LoadTexture("resources/forest/Layer_0005_5.png");
    Texture2D bgLayer04 = LoadTexture("resources/forest/Layer_0004_Lights.png");
    Texture2D bgLayer03 = LoadTexture("resources/forest/Layer_0003_6.png");
    Texture2D bgLayer02 = LoadTexture("resources/forest/Layer_0002_7.png");
    Texture2D bgLayer01 = LoadTexture("resources/forest/Layer_0001_8.png");
    Texture2D bgLayer00 = LoadTexture("resources/forest/Layer_0000_9.png");


    Texture2D tex = LoadTexture("resources/ninja.png");
    GridSpriteSheet spriteSheet;
    spriteSheet
        .ProcessSpriteSheet(tex, 64, 64, 6, 20, 18, 18)
        .SetHandle({ 0.5f, 1.0f })
        .SetPivot({ 0.5f, 0.5f });

    Sprite* sprite_1 = SpriteManager::CreateSprite(&spriteSheet);
    Sprite* sprite_2 = SpriteManager::CreateSprite(&spriteSheet);

    int anim1[3] = { 0, 1, 2 };
    int anim2[4] = { 3, 4, 5, 6 };
    SpriteAnim anim_a(anim1, 4);
    SpriteAnim anim_b(anim2, 5);

    sprite_1->RegisterAnimation(0, anim_a);
    sprite_2->RegisterAnimation(0, anim_b);
    
    sprite_1->SetAnim(0).SetScale(4);
    
    sprite_2->SetAnim(0).SetScale(2);

    Texture2D panel = LoadTexture("resources/nineslice.png");
    NineSlice slice(panel, 48, 48, 48, 48);
    NSPanel uiPanel(slice);
    uiPanel.SetPosition(16, 16);
    uiPanel.SetSize(screenWidth - 32, 164);



    float timer = 0;
    int frame = 0;
    float ang = 0;

    int jump;
    auto tween = tweeny::from(0)
        .to(200).via(tweeny::easing::cubicInOut).during(1000)
        .to(0).via(tweeny::easing::cubicInOut).during(1000);

    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        float delta = GetFrameTime();
        int deltaMillis = (int)(delta * 1000);

        jump = tween.step(delta);
        if (tween.progress() >= 1)
            tween.seek(0);

        DrawTexture(bgLayer11, 0, 0, WHITE);
        DrawTexture(bgLayer10, 0, 0, WHITE);
        DrawTexture(bgLayer09, 0, 0, WHITE);
        DrawTexture(bgLayer08, 0, 0, WHITE);
        DrawTexture(bgLayer07, 0, 0, WHITE);
        DrawTexture(bgLayer06, 0, 0, WHITE);
        DrawTexture(bgLayer05, 0, 0, WHITE);
        DrawTexture(bgLayer04, 0, 0, WHITE);
        DrawTexture(bgLayer03, 0, 0, WHITE);
        DrawTexture(bgLayer02, 0, 0, WHITE);
        DrawTexture(bgLayer01, 0, 0, WHITE);
        DrawTexture(bgLayer00, 0, 0, WHITE);


        //sprite_1->SetRotation(ang);
        //ang += 1;
        sprite_1->SetPosition(200, 729-jump);
        sprite_2->SetPosition(400, 729);

        BeginDrawing();
  
        ClearBackground(RAYWHITE);

        uiPanel.Draw();

        SpriteManager::DrawSprites(delta);

        DrawLine(0, 400, 600, 400, BLACK);


        EndDrawing();
    }

    // Teardown
    SpriteManager::UnregisterAll();
    spriteSheet.Destroy();

    UnloadTexture(tex);
    UnloadTexture(panel);
    UnloadTexture(bgLayer00);
    UnloadTexture(bgLayer01);
    UnloadTexture(bgLayer02);
    UnloadTexture(bgLayer03);
    UnloadTexture(bgLayer04);
    UnloadTexture(bgLayer05);
    UnloadTexture(bgLayer06);
    UnloadTexture(bgLayer07);
    UnloadTexture(bgLayer08);
    UnloadTexture(bgLayer09);
    UnloadTexture(bgLayer10);
    UnloadTexture(bgLayer11);
    CloseWindow();

    return 0;
}