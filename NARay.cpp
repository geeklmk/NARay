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
#include "raylib.h"
#include <iostream>
#include "tweeny/tweeny.h"

int xPos = 0;

bool stepped(int x)
{

    xPos = x;
    return false;
}


int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop

    auto tween = tweeny::from(0).to(400).during(3).onStep(stepped);

    Texture2D tex = LoadTexture("resources/ninja.png");

    NARay::SpriteSheet spriteSheet(tex, 64, 64);
    int anim1[3] = { 0,1,2 };
    NARay::SpriteAnim anim(anim1, 4);
    spriteSheet.RegisterAnimation(0, anim);
    spriteSheet.SetAnim(0)->SetScale(6);

    float timer = 0;
    int frame = 0;
    float ang = 0;

    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        float delta = GetFrameTime();
        tween.step(delta / 3.0f);
        spriteSheet.Update(delta);
        spriteSheet.SetRotation(ang);
        ang += 1;


        BeginDrawing();
        spriteSheet.Draw(100, 100);
        ClearBackground(RAYWHITE);

        DrawText("ciao", xPos, 200, 20, LIGHTGRAY);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}