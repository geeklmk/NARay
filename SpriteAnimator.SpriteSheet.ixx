/*
 * Project:    NARay
 * File:       SpriteAnimator.SpriteSheet.ixx
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

export module SpriteAnimator:SpriteSheet;

namespace NARay
{

	/// <summary>
	/// Structure holding the single sprite frame data
	/// </summary>
	export struct SpriteSheetFrameData
	{
		Texture2D sheetTexture;
		Rectangle source;
		/// <summary>
		/// pivot point for rotations
		/// </summary>
		Vector2 pivot;
		/// <summary>
		/// handle point coordinates are relative to
		/// </summary>
		Vector2 handle;
		Vector2 spriteSize;
	};

	/// <summary>
	/// Base class for spritesheets
	/// </summary>
	export class SpriteSheet
	{
	public:
		/// <summary>
		/// Returns data for the selected frame
		/// </summary>
		/// <param name="frameNumber">frame to get the data from</param>
		/// <returns></returns>
		virtual SpriteSheetFrameData* GetFrameData(int frameNumber)
		{
			return NULL;
		};

		virtual void Destroy()
		{
		};

		/// <summary>
		/// Returns the number of frames of this specific SpriteSheet
		/// </summary>
		/// <returns></returns>
		int Count()
		{
			return frameCount;
		}

	protected:
		int frameCount;
	};
}