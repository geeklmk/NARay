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

	struct SpriteSheetData
	{
		Texture2D sheetTexture;
		Rectangle source;
		Vector2 pivot;
		Vector2 spriteSize;
	};


	class SpriteSheet
	{
	public:
		virtual SpriteSheetData* GetSpriteData(int frameNumber)
		{
			return NULL;
		};

		virtual void Destroy()
		{
		};

		int Count()
		{
			return frameCount;
		}

	protected:
		int frameCount;
	};

	class GridSpriteSheet : public SpriteSheet
	{
	public:
		GridSpriteSheet(Texture2D sheetTexture, int gridSizeX, int gridSizeY, int top=0, int bottom=0, int left=0, int right=0)
		{
			int cols = sheetTexture.width / gridSizeX;
			int rows = sheetTexture.height / gridSizeY;
			frameCount = rows * cols;
			spriteData = new SpriteSheetData*[cols * rows];
			int frame = 0;
			for (int c = 0; c < cols; c++)
			{
				for (int r = 0; r < rows; r++)
				{
					spriteData[frame] = new SpriteSheetData();
					spriteData[frame]->sheetTexture = sheetTexture;
					spriteData[frame]->source = { (float)gridSizeX * (frame % cols)+left, (float)gridSizeY * (frame / cols)+top, (float)gridSizeX - left - right, (float)gridSizeY - top - bottom };
					spriteData[frame]->pivot = { 0.5f, 1.0f };
					spriteData[frame]->spriteSize = { (float)gridSizeX - left - right, (float)gridSizeY - top - bottom };
					frame++;
				}
			}
		}

		SpriteSheetData* GetSpriteData(int frameNumber)
		{
			return spriteData[frameNumber];
		}

		void Destroy()
		{
			for (int frame = 0; frame < frameCount; frame++)
			{
				delete spriteData[frame];
			}
			delete[] spriteData;
		}
	private:
		SpriteSheetData** spriteData;
	};


	class Sprite 
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
			SpriteSheetData* currentSprite = this->sheet->GetSpriteData(frame);

			Rectangle destination = { x, y, currentSprite->spriteSize.x*this->scale, currentSprite->spriteSize.y *this->scale };
			origin.x = (currentSprite->spriteSize.x * currentSprite->pivot.x * this->scale);
			origin.y = (currentSprite->spriteSize.y * currentSprite->pivot.y * this->scale);
			DrawTexturePro( currentSprite->sheetTexture, currentSprite->source, destination, this->origin, this->rotation, WHITE);
		}

	private:
		SpriteSheet* sheet;
		Vector2 origin;
		SpriteAnim currentAnim;
		int currentFrame;
		float scale;
		float rotation;
		float timer;
		std::map<int, SpriteAnim> animations;
	};
}