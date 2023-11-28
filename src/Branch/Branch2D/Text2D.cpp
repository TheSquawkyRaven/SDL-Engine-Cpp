#include "pch.h"

#include "Text2D.h"

#include "../../Squawk/Log.h"

using namespace std;
using namespace Perch;

void Text2D::SetText(std::string text)
{
	this->text = text;
	UpdateTexture();
}

void Text2D::SetFont(shared_ptr<Font> font)
{
	this->font = font;
	UpdateTexture();
}

void Text2D::UpdateTexture()
{
	shared_ptr<Texture> texture = Texture::Create(engine, font, text, GetColor());
	SetTexture(texture);
}

void Text2D::Ready()
{
	SetColor(Color::Black());
}

void Text2D::OnDestroy()
{
	font = nullptr;
}
