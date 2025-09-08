/*
 * Project:    NARay
 * File:       SpriteAnimator.Sprite.ixx
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
#include <unordered_map>


export module SpriteAnimator:Sprite;

import :SpriteSheet;
import :GridSpriteSheet;
import GfxPipeline;

namespace NARay
{
	/// <summary>
	///  Structure holding simple animation data: animation frames and animation rate in frames per second
	/// </summary>
	export struct SpriteAnim
	{
		SpriteAnim()
		{

		}
		/// <summary>
		/// Standard constructur
		/// </summary>
		/// <param name="frames">array of frames</param>
		/// <param name="fps">animation rate in frames per second</param>
		SpriteAnim(std::span<const int> frames, int fps)
		{
			this->frameData = frames;
			this->fps = fps;
			animSpeed = 1.0f / (float)fps;
		}

		int fps;
		float animSpeed;
		std::span<const int> frameData;
	};


	/// <summary>
	/// Basic sprite handling class
	/// </summary>
	export class Sprite : public PipelineDrawable
	{
	public:
		Sprite(SpriteSheet* spriteSheet)
		{
			this->sheet = spriteSheet;
			this->origin = { 0, 0 };
			timer = 0;
		}

		void RegisterAnimation(int reference, SpriteAnim& animation)
		{
			this->animations[reference] = animation;
		}

		Sprite& SetAnim(int reference)
		{
			this->currentAnim = animations[reference];
			this->timer = 0;
			this->currentFrame = 0;
			this->scale = 1;
			this->rotation = 0;
			return *this;
		}

		Sprite& SetScale(float scaleFactor)
		{
			this->scale = scaleFactor;
			return *this;
		}

		Sprite& SetRotation(float angle)
		{
			this->rotation = angle;
			return *this;
		}

		Sprite& SetPosition(int x, int y)
		{
			this->position = { (float)x, (float)y };
			return *this;
		}
		
		void UpdateTimers(float delta)
		{
			this->timer += delta;
			if (this->timer >= this->currentAnim.animSpeed)
			{
				this->timer -= this->currentAnim.animSpeed;
				this->currentFrame = (this->currentFrame + 1) % this->currentAnim.frameData.size();
			}
		}

		void Draw()
		{
			int frame = this->currentAnim.frameData[this->currentFrame];
			SpriteSheetFrameData* currentSprite = this->sheet->GetFrameData(frame);

			origin.x = (currentSprite->spriteSize.x * currentSprite->pivot.x * this->scale);
			origin.y = (currentSprite->spriteSize.y * currentSprite->pivot.y * this->scale);
			Vector2 displacement = {
				this->origin.x - (currentSprite->spriteSize.x * currentSprite->handle.x * this->scale),
				this->origin.y - (currentSprite->spriteSize.y * currentSprite->handle.y * this->scale)
			};

			Rectangle destination = { position.x +displacement.x, position.y+displacement.y, currentSprite->spriteSize.x * this->scale, currentSprite->spriteSize.y * this->scale};

			DrawTexturePro(currentSprite->sheetTexture, currentSprite->source, destination, this->origin, this->rotation, WHITE);
		}

	private:
		SpriteSheet* sheet;
		Vector2 origin;
		Vector2 position;
		SpriteAnim currentAnim;
		int currentFrame;
		float scale;
		float rotation;
		float timer;
		std::unordered_map<int, SpriteAnim> animations;
	};
}