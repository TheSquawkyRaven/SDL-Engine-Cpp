#pragma once

#ifdef PERCHENGINECPP_EXPORTS
#define PERCH_API __declspec(dllexport)
#else
#define PERCH_API __declspec(dllimport)
#endif


#include "Branch2D.h"

#include "../../Structs/Rect2.h"
#include "../../Structs/Vector2.h"

#include <SDL.h>

namespace Perch
{

	/// <summary>
	/// 
	/// </summary>
	class Rectangle2D : public Branch2D
	{

		// # Variables + Getters/Setters
	private:

		Rect2 rect = Rect2();
		Color color = Color();

	public:

		PERCH_API inline Rect2 GetRect2() const { return rect; }
		PERCH_API inline void SetRect2(Rect2 rect) { this->rect = rect; }
		PERCH_API inline Color GetColor() const { return color; }
		PERCH_API inline void SetColor(Color color) { this->color = color; }

		// ###

		// # Functions

	private:
		
	public:

		PERCH_API Rectangle2D(Engine* engine) : Branch2D(engine) {};

		PERCH_API virtual void Draw(SDL_Renderer* renderer) override;

		PERCH_API Vector2 GetRectSize();
		PERCH_API Vector2 GetRectGlobalSize();

		PERCH_API Vector2 GetRectGlobalPosition();

		// ###

	};


}
