#ifndef __FONTS_H
#define __FONTS_H

#include "Element.h"

#pragma once

namespace gui
{
	HFONT CreateFontFromFile(const char* filename, const char* fontfilename /*= THE FONT FACE AS IT APPEARS IN THE FONT FILE*/,
		int cHeight, int cWidth, int cEscapement, int cOrientation, int cWeight, bool bItalic,
		bool bUnderline, bool bStrikeOut, int iCharSet, int iOutPrecision, int iClipPrecision,
		int iQuality, int iPitchAndFamily);

	void DestroyFontMadeFromFile(HFONT font, const char* filename);
}

#define FONT_ARIAL                     "Arial"
#define FONT_TIMES_NEW_ROMAN           "Times New Roman"
#define FONT_COURIER_NEW               "Courier New"
#define FONT_VERDANA                   "Verdana"
#define FONT_TAHOMA                    "Tahoma"
#define FONT_GEORGIA                   "Georgia"

//ew
#define FONT_COMIC_SANS_MS             "Comic Sans MS"

#define FONT_SEGOE_UI                  "Segoe UI"
#define FONT_TREBUCHET_MS              "Trebuchet MS"
#define FONT_ARIAL_BLACK               "Arial Black"
#define FONT_IMPACT                    "Impact"
#define FONT_LUCIDA_CONSOLE            "Lucida Console"
#define FONT_SYMBOL                    "Symbol"
#define FONT_CALIBRI                   "Calibri"
#define FONT_CONSOLAS                  "Consolas"
#define FONT_DROID_SANS                "Droid Sans"
#define FONT_OPEN_SANS                 "Open Sans"
#define FONT_ROBOTO                    "Roboto"
#define FONT_MERRIWEATHER              "Merriweather"
#define FONT_PALATINO                   "Palatino Linotype"
#define FONT_GEORGIA_BOLD              "Georgia Bold"
#define FONT_HELVETICA                 "Helvetica"
#define FONT_CANDARA                   "Candara"
#define FONT_BASKERVILLE               "Baskerville"
#define FONT_MSN_SANS_SERIF            "MSN Sans Serif"
#define FONT_FUTURA                    "Futura"
#define FONT_GARAMOND                  "Garamond"
#define FONT_ARVO                      "Arvo"
#define FONT_NUNITO                   "Nunito"
#define FONT_RALEWAY                   "Raleway"
#define FONT_BEBAS_NEUE                "Bebas Neue"
#define FONT_ALEGREYA                 "Alegreya"
#define FONT_FREIGHT_TEXT              "Freight Text"
#define FONT_COURIER                   "Courier"

#endif
