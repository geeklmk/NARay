/*
 * Project:    NARay
 * File:       SGui.Text.ixx
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

#include<string>
#include<iostream>

import GfxPipeline;
export module SGui:Text;

namespace NARay
{

	export typedef enum {
		LEFT,
		RIGHT,
		MIDDLE
	} HAlign;

	export typedef enum {		
		TOP,
		BOTTOM,
		CENTER
	} VAlign;

	export class Text : public PipelineDrawable
	{
	public:

		Text( Font fontToUse, int fontSize, Color fontColor)
		{
			this->textFont = fontToUse;
			this->fontSize = fontSize;
			this->fontColor = fontColor;
			this->rotation = 0;
			this->spacing = 8;
			SetOrder(500);
			hAlign = HAlign::LEFT;
			vAlign = VAlign::CENTER;
		}

		void Draw()
		{
			Vector2 measure = MeasureTextEx(this->textFont, this->text.c_str(), this->fontSize, this->spacing);
			Vector2 newPos = { position.x, position.y };
			switch (hAlign)
			{
			case HAlign::LEFT: break;
			case HAlign::RIGHT:
				newPos = {
					position.x + size.x - measure.x,
					newPos.y
				};
				break;
			case HAlign::MIDDLE:
				newPos = {
					position.x + size.x / 2 - measure.x / 2,
					newPos.y
				}; 
				break;
			}
			
			switch (vAlign)
			{
			case VAlign::TOP: break;
			case VAlign::BOTTOM:
				newPos = {
					newPos.x,
					position.y + size.y - measure.y,
				};
				break;
			case HAlign::MIDDLE:
				newPos = {
					newPos.x,
					position.y + size.y / 2 - measure.y / 2,
				};
				break;
			}

			DrawTextPro(this->textFont, this->text.c_str(), newPos, {0, 0}, this->rotation, this->fontSize, this->spacing, this->fontColor);
		}

		Text& SetText(std::string text)
		{
			this->text = text;
			return *this;
		}

		Text& SetPosition(int x, int y)
		{
			this->position = { (float)x, (float)y };
			return *this;
		}

		Text& SetSize(int w, int h)
		{
			this->size = { (float)w, (float)h };
			return *this;
		}

		Text& SetAlign(HAlign horizontal, VAlign vertical)
		{
			this->hAlign = horizontal;
			this->vAlign = vertical;
			return *this;
		}

	private:
		Vector2 position;
		Vector2 size;
		std::string text;
		Font textFont;
		int fontSize;
		int rotation;
		int spacing;
		Color fontColor;
		HAlign hAlign;
		VAlign vAlign;
	};

}
