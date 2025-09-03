/*
 * Project:    NARay
 * File:       SpriteAnimator.ixx
 * Author:     Luca 'aXon' Marchetti
 *
 * Description:
 *   Sprite animations utilities.
 *   Uses NARay DrawTexturePro to draw the sprite, handling fixed-time frame animation
 *   and position/rotation/ with pivot point
 *
 * License: LGPL 2.1
 *
 */
extern "C" {
#include "raylib.h"
}

#include <span>
#include <vector>
#include <array>
#include <map>


export module SpriteAnimator;

export import :SpriteSheet;
export import :GridSpriteSheet;
export import :Sprite;