#include "pch.h"

#include "Viewport2D.h"

#include "../../Squawk/Log.h"

using namespace std;
using namespace Perch;
using namespace Squawk;

void Viewport2D::Update()
{
	engine->SimulateUseViewport(viewport.get());
}

void Viewport2D::UpdateOut()
{
	engine->SimulateUnuseViewport(viewport.get());
}

void Viewport2D::Draw(SDL_Renderer* renderer)
{
	engine->UseViewport(renderer, viewport.get());
}

void Viewport2D::DrawOut(SDL_Renderer* renderer)
{
	engine->UnuseViewport(renderer, viewport.get());
}

