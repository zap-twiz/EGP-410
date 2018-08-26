#include "Font.h"

Font::Font(const std::string& filename, int size)
	:mpFont(NULL)
	,mSize(size)
{
	mpFont = TTF_OpenFont(filename.c_str(), size);
}

Font::~Font()
{
	TTF_CloseFont(mpFont);
}

