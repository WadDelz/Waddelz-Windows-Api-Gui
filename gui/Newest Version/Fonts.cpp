#include "Fonts.h"

std::vector<const char*> szAddedFileFonts = {};

HFONT gui::CreateFontFromFile(const char* filename, const char* fontfilename, int cHeight, int cWidth, int cEscapement, int cOrientation, int cWeight, bool bItalic, bool bUnderline, bool bStrikeOut, int iCharSet, int iOutPrecision, int iClipPrecision, int iQuality, int iPitchAndFamily)
{
	bool bFound = false;
	for (unsigned int i = 0; i < szAddedFileFonts.size(); i++)
	{
		if (!strcmp(szAddedFileFonts.at(i), filename))
			bFound = true;
	}

	if (!bFound)
	{
		if (!AddFontResourceEx(filename, FR_PRIVATE, 0))
			return nullptr;
	}

	szAddedFileFonts.push_back(_strdup(filename));

    return CreateFont(
        cHeight,
        cWidth,
        cEscapement,
        cOrientation,
        cWeight,
        bItalic ? TRUE : FALSE,
        bUnderline ? TRUE : FALSE,
        bStrikeOut ? TRUE : FALSE,
        iCharSet,
        iOutPrecision,
        iClipPrecision,
        iQuality,
        iPitchAndFamily,
        fontfilename
    );
}

void gui::DestroyFontMadeFromFile(HFONT font, const char* filename)
{
    for (unsigned int i = 0; i < szAddedFileFonts.size(); i++)
    {
        if (!strcmp(filename, szAddedFileFonts.at(i)))
        {
            free((char*)szAddedFileFonts.at(i));
            szAddedFileFonts.erase(szAddedFileFonts.begin() + i);
            RemoveFontResourceEx(filename, FR_PRIVATE, 0);
            break;
        }
    }

    if (font)
        DeleteObject(font);
}
