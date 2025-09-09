/*
 * Project:    NARay
 * File:       SGui.NSPanel.ixx
 * Author:     Luca 'aXon' Marchetti
 *
 * Description:
 *   Very simple UI, 9-slice based
 *
 * License: LGPL 2.1
 *
 */
extern "C" {
#include "raylib.h"
}

import GfxPipeline;
export module SGui:NSPanel;

namespace NARay
{
	export class NineSlice
	{
	public:

		int top, bottom, left, right;
		Texture2D texture;

		NineSlice(Texture2D& texture, int top, int bottom, int left, int right)
		{
			this->top = top;
			this->bottom = bottom;
			this->left = left;
			this->right = right;
			this->texture = texture;
		}
	};


	export class NSPanel : public PipelineDrawable
	{
	public:

		NSPanel(NineSlice& nineSlice)
		{
			this->nineSlice = &nineSlice;
			SetOrder(500);
		}

		NSPanel& SetPosition(int x, int y)
		{
			position = { (float)x, (float)y };
			return *this;
		}

		NSPanel& SetSize(int w, int h)
		{
			size = { (float)w, (float)h };
			return *this;
		}

		void Draw()
		{
			Rectangle dest = { position.x, position.y,  size.x,  size.y };
			float texW = nineSlice->texture.width;
			float texH = nineSlice->texture.height;

			// Define the source rectangles for all 9 slices
			Rectangle source[9];
			source[0] = { 0, 0, (float)nineSlice->left, (float)nineSlice->top }; // Top-Left
			source[1] = { (float)nineSlice->left, 0, texW - nineSlice->left - nineSlice->right, (float)nineSlice->top }; // Top-Mid
			source[2] = { texW - nineSlice->right, 0, (float)nineSlice->right, (float)nineSlice->top }; // Top-Right

			source[3] = { 0, (float)nineSlice->top, (float)nineSlice->left, texH - nineSlice->top - nineSlice->bottom }; // Mid-Left
			source[4] = { (float)nineSlice->left, (float)nineSlice->top, texW - nineSlice->left - nineSlice->right, texH - nineSlice->top - nineSlice->bottom }; // Mid-Mid
			source[5] = { texW - nineSlice->right, (float)nineSlice->top, (float)nineSlice->right, texH - nineSlice->top - nineSlice->bottom }; // Mid-Right

			source[6] = { 0, texH - nineSlice->bottom, (float)nineSlice->left, (float)nineSlice->bottom }; // Bot-Left
			source[7] = { (float)nineSlice->left, texH - nineSlice->bottom, texW - nineSlice->left - nineSlice->right, (float)nineSlice->bottom }; // Bot-Mid
			source[8] = { texW - nineSlice->right, texH - nineSlice->bottom, (float)nineSlice->right, (float)nineSlice->bottom }; // Bot-Right

			// Define the destination rectangles for all 9 slices
			Rectangle dests[9];
			dests[0] = { dest.x, dest.y, (float)nineSlice->left, (float)nineSlice->top }; // Top-Left
			dests[1] = { dest.x + nineSlice->left, dest.y, dest.width - nineSlice->left - nineSlice->right, (float)nineSlice->top }; // Top-Mid
			dests[2] = { dest.x + dest.width - nineSlice->right, dest.y, (float)nineSlice->right, (float)nineSlice->top }; // Top-Right

			dests[3] = { dest.x, dest.y + nineSlice->top, (float)nineSlice->left, dest.height - nineSlice->top - nineSlice->bottom }; // Mid-Left
			dests[4] = { dest.x + nineSlice->left, dest.y + nineSlice->top, dest.width - nineSlice->left - nineSlice->right, dest.height - nineSlice->top - nineSlice->bottom }; // Mid-Mid
			dests[5] = { dest.x + dest.width - nineSlice->right, dest.y + nineSlice->top, (float)nineSlice->right, dest.height - nineSlice->top - nineSlice->bottom }; // Mid-Right

			dests[6] = { dest.x, dest.y + dest.height - nineSlice->bottom, (float)nineSlice->left, (float)nineSlice->bottom }; // Bot-Left
			dests[7] = { dest.x + nineSlice->left, dest.y + dest.height - nineSlice->bottom, dest.width - nineSlice->left - nineSlice->right, (float)nineSlice->bottom }; // Bot-Mid
			dests[8] = { dest.x + dest.width - nineSlice->right, dest.y + dest.height - nineSlice->bottom, (float)nineSlice->right, (float)nineSlice->bottom }; // Bot-Right

			// Draw all 9 slices
			for (int i = 0; i < 9; ++i)
			{
				// Only draw slices that have a positive width and height
				if (source[i].width > 0 && source[i].height > 0 && dests[i].width > 0 && dests[i].height > 0)
				{
					DrawTexturePro(nineSlice->texture, source[i], dests[i], { 0, 0 }, 0.0f, WHITE);
				}
			}
		}
	private:
		NineSlice* nineSlice;
		Vector2 position;
		Vector2 size;
	};
}