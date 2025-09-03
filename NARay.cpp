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

using namespace NARay;
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
    GridSpriteSheet spriteSheet(tex, 64, 64, 6, 20, 18, 18);

    Sprite sprite_1(&spriteSheet);
    Sprite sprite_2(&spriteSheet);

    int anim1[3] = { 0,1,2 };
    int anim2[4] = { 3, 4, 5, 6 };
    SpriteAnim anim_a(anim1, 4);
    SpriteAnim anim_b(anim2, 5);

    sprite_1.RegisterAnimation(0, anim_a);
    sprite_2.RegisterAnimation(0, anim_b);
    
    sprite_1.SetAnim(0).SetScale(4);
    
    sprite_2.SetAnim(0).SetScale(2);

    float timer = 0;
    int frame = 0;
    float ang = 0;

    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        float delta = GetFrameTime();
        tween.step(delta / 3.0f);
        
        sprite_1.Update(delta);
        sprite_2.Update(delta);


        //sprite.SetRotation(ang);
        ang += 1;


        BeginDrawing();
        
        sprite_1.Draw(200, 400);
        sprite_2.Draw(400, 400);

        ClearBackground(RAYWHITE);
        DrawLine(0, 400, 600, 400, BLACK);

        DrawText("ciao", xPos, 200, 20, LIGHTGRAY);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    spriteSheet.Destroy();
    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}