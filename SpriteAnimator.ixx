/*
 * Project:    NARay
 * File:       SpriteAnimator.ixx
 * Author:     Luca 'aXon' Marchetti
 *
 * Description:
 *   Sprite animations utilities
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

export namespace NARay
{

	struct SpriteAnim
	{
		SpriteAnim()
		{

		}

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

	class SpriteSheet 
	{
	public:
		SpriteSheet(Texture2D &sheet, int gridSizeX, int gridSizeY)
		{ 
			this->gridSizeX = gridSizeX;
			this->gridSizeY = gridSizeY;
			this->cols = sheet.width / gridSizeX;
			this->rows = sheet.height / gridSizeY;
			this->sheet = sheet;
			this->origin = { 0, 0 };
			this->pivot = { 0.5f, 0.5f };
			timer = 0;
		}

		void RegisterAnimation(int reference, SpriteAnim& animation)
		{
			this->animations[reference] = animation;
		}

		SpriteSheet* SetAnim(int reference)
		{
			this->currentAnim = animations[reference];
			this->timer = 0;
			this->currentFrame = 0;	
			this->scale = 1;
			this->rotation = 0;
			return this;
		}

		SpriteSheet* SetScale(float scaleFactor)
		{
			this->scale = scaleFactor;
			return this;
		}

		SpriteSheet* SetRotation(float angle)
		{
			this->rotation = angle;
			return this;
		}

		void Update(float deltaTime)
		{
			this->timer += deltaTime;
			if (this->timer >= this->currentAnim.animSpeed)
			{
				this->timer -= this->currentAnim.animSpeed;
				this->currentFrame = (this->currentFrame+1)%this->currentAnim.frameData.size();
			}
		}

		void Draw(int x, int y)
		{		
			int frame = this->currentAnim.frameData[this->currentFrame];
			Rectangle source = { this->gridSizeX * (frame % this->cols), this->gridSizeY * (frame / this->cols), this->gridSizeX, this->gridSizeY };
			Rectangle destination = { x, y, this->gridSizeX*this->scale, this->gridSizeY*this->scale };
			origin.x = (this->gridSizeX * this->pivot.x * this->scale);
			origin.y = (this->gridSizeY * this->pivot.y * this->scale);
			DrawTexturePro(this->sheet, source, destination, this->origin, this->rotation, WHITE);
		}

	private:
		Texture2D sheet;
		Vector2 origin;
		Vector2 pivot;
		int gridSizeX;
		int gridSizeY;
		int rows;
		int cols;
		SpriteAnim currentAnim;
		int currentFrame;
		float scale;
		float rotation;
		float timer;
		std::map<int, SpriteAnim> animations;
	};
}