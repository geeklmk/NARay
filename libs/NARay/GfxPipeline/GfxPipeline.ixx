/*
 * Project:    NARay
 * File:       GfxPipeline.ixx
 * Author:     Luca 'aXon' Marchetti
 *
 * Description:
 *   Very basic drawing pipeline
 *
 * License: LGPL 2.1
 *
 */
#include<iostream>
#include <vector>
#include<map>
#include<unordered_map>

export module GfxPipeline;

namespace NARay
{
	export class Drawable
	{
	public:
		virtual void Draw()
		{ 
		}

		virtual void UpdateTimers(float delta)
		{

		}

		virtual void SetOrder(int order)
		{
			this->order = order;
		}

		int GetOrder()
		{
			return order;
		}

	protected:
		int order = 0;
	};



	export class GfxPipeline
	{
	public:
		const static int MIN_LAYER = 0;
		const static int MAX_LAYER = 10000;
		inline static float frameDeltaTime = 0.0f;

		static void Draw(float deltaTime, int drawStart=MIN_LAYER, int drawEnd=MAX_LAYER)
		{
			auto it = layers.lower_bound(drawStart);
			int i = 0;
			while (it != layers.end() && it->first < drawEnd)
			{
				int currentLayer = it->first;
				const std::vector<Drawable*>& objectsInLayer = it->second;
				for (Drawable* drawable : objectsInLayer)
				{
					drawable->UpdateTimers(GfxPipeline::frameDeltaTime);
					drawable->Draw();
					++i;
				}
				++it;
			}
		}

		static void RegisterDrawable(Drawable* drawableToRegister)
		{
			GfxPipeline::layers[drawableToRegister->GetOrder()].push_back(drawableToRegister);
			GfxPipeline::drawableTracker[drawableToRegister] = drawableToRegister->GetOrder();		
		}

		static void MoveDrawable(Drawable* drawableToMove)
		{
			// check if it exists
			if (GfxPipeline::drawableTracker.find(drawableToMove) == GfxPipeline::drawableTracker.end())
			{
				GfxPipeline::RegisterDrawable(drawableToMove);
				return;
			}
			int newLayer = drawableToMove->GetOrder();
			int oldLayer = GfxPipeline::drawableTracker[drawableToMove];
			
			// why did you call me?
			if (newLayer == oldLayer)
				return;

			GfxPipeline::UnRegisterDrawable(drawableToMove);
			GfxPipeline::RegisterDrawable(drawableToMove);
		}

		static void UnRegisterDrawable(Drawable* drawableToUnRegister)
		{
			// check if it exists
			if (GfxPipeline::drawableTracker.find(drawableToUnRegister) == GfxPipeline::drawableTracker.end())
				return;
			std::vector<Drawable*>& oldLayerVector = GfxPipeline::layers[GfxPipeline::drawableTracker[drawableToUnRegister]];
			std::erase(oldLayerVector, drawableToUnRegister);
		}

	private:
		inline static std::map<int, std::vector<Drawable*>> layers;
		inline static std::unordered_map<Drawable*, int> drawableTracker;
	};

	export class PipelineDrawable : public Drawable
	{
	public:
		PipelineDrawable()
		{
			GfxPipeline::RegisterDrawable(this);
		}

		void SetOrder(int order)
		{
			this->order = order;
			GfxPipeline::MoveDrawable(this);
		}
	};

}
