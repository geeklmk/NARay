/*
 * Project:    NARay
 * File:       SpriteAnimator.GridSpriteSheet.ixx
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

export module SpriteAnimator:GridSpriteSheet;

import :SpriteSheet;

namespace NARay
{
	export class GridSpriteSheet : public SpriteSheet
	{
	public:
		GridSpriteSheet()
		{

		}

		GridSpriteSheet& SetPivot(Vector2 pivot)
		{
			this->defaultPivot = pivot;

			for (int i=0; i < this->frameCount; i++)
				spriteData[i]->pivot = pivot;
			
			return *this;
		}
		
		GridSpriteSheet& SetHandle(Vector2 handle)
		{
			this->defaultHandle = handle;

			for (int i=0; i < this->frameCount; i++)
				spriteData[i]->handle = handle;

			return *this;
		}

		GridSpriteSheet& ProcessSpriteSheet(Texture2D sheetTexture, int gridSizeX, int gridSizeY, int top = 0, int bottom = 0, int left = 0, int right = 0)
		{
			int cols = sheetTexture.width / gridSizeX;
			int rows = sheetTexture.height / gridSizeY;
			frameCount = rows * cols;
			spriteData = new SpriteSheetFrameData * [cols * rows];
			int frame = 0;
			for (int c = 0; c < cols; c++)
			{
				for (int r = 0; r < rows; r++)
				{
					spriteData[frame] = new SpriteSheetFrameData();
					spriteData[frame]->sheetTexture = sheetTexture;
					spriteData[frame]->source = { (float)gridSizeX * (frame % cols) + left, (float)gridSizeY * (frame / cols) + top, (float)gridSizeX - left - right, (float)gridSizeY - top - bottom };
					spriteData[frame]->pivot = defaultPivot;
					spriteData[frame]->handle = defaultHandle;
					spriteData[frame]->spriteSize = { (float)gridSizeX - left - right, (float)gridSizeY - top - bottom };
					frame++;
				}
			}

			return *this;
		}

		SpriteSheetFrameData* GetFrameData(int frameNumber)
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
		SpriteSheetFrameData** spriteData;
		Vector2 defaultPivot = { 0.5f, 0.5f };
		Vector2 defaultHandle = { 0.0f,0.0f };
	};
}