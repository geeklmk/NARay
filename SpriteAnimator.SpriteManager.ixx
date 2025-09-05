/*
 * Project:    NARay
 * File:       SpriteAnimator.SpriteManager.ixx
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
#include <vector>

export module SpriteAnimator:SpriteManager;

import :Sprite;

namespace NARay
{
	export class SpriteManager
	{
	public:
		inline static float frameDeltaTime = 0.0f;

		static void DrawSprites(float frameDeltaTime)
		{
			SpriteManager::frameDeltaTime = frameDeltaTime;
			for (Sprite* sprite : SpriteManager::sprites)
			{
				sprite->UpdateTimers(SpriteManager::frameDeltaTime);
				sprite->Draw();
			}
		}

		static void RegisterSprite(Sprite* spriteToRegister)
		{
			SpriteManager::sprites.push_back(spriteToRegister);
		}

		static void UnRegisterSprite(Sprite* spriteToRegister)
		{
			std::erase(SpriteManager::sprites, spriteToRegister);
		}

		static Sprite* CreateSprite(SpriteSheet* spriteSheet)
		{
			Sprite* newSprite = new Sprite(spriteSheet);
			SpriteManager::RegisterSprite(newSprite);
			return newSprite;
		}

	private:
		inline static std::vector<Sprite*> sprites;
	};
}