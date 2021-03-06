#pragma once

#include "utility/fonts.h"

#include <vector>

using namespace utility;

const Font Normal200 = Font(Font::Typeface::Cabin, Font::Emphasis::Normal, 200);
const Font Normal55 = Font(Font::Typeface::Cabin, Font::Emphasis::Normal, 55);
const Font Bold55 = Font(Font::Typeface::Cabin, Font::Emphasis::Bold, 55);
const Font Normal45 = Font(Font::Typeface::Cabin, Font::Emphasis::Normal, 45);
const Font Bold45 = Font(Font::Typeface::Cabin, Font::Emphasis::Bold, 45);
const Font Normal35 = Font(Font::Typeface::Cabin, Font::Emphasis::Normal, 35);
const Font Bold35 = Font(Font::Typeface::Cabin, Font::Emphasis::Bold, 35);
const Font Bold30 = Font(Font::Typeface::Cabin, Font::Emphasis::Normal, 30);
const Font Normal25 = Font(Font::Typeface::Cabin, Font::Emphasis::Normal, 25);
const Font Bold25 = Font(Font::Typeface::Cabin, Font::Emphasis::Bold, 25);
const Font Normal15 = Font(Font::Typeface::Cabin, Font::Emphasis::Normal, 15);
const Font ObelixPro18 = Font(Font::Typeface::ObelixPro, Font::Emphasis::Normal, 18);
const Font ObelixPro35 = Font(Font::Typeface::ObelixPro, Font::Emphasis::Normal, 35);
const Font ObelixPro40 = Font(Font::Typeface::ObelixPro, Font::Emphasis::Normal, 40);
const Font ObelixPro50 = Font(Font::Typeface::ObelixPro, Font::Emphasis::Normal, 50);


const std::vector<Font> kFontsToPreload = {
  Normal200,
  Normal55,
  Bold55,
  Normal45,
  Bold45,
  Normal35,
  Bold35,
  Bold30,
  Normal25,
  Bold25,
  Normal15,
  ObelixPro18,
  ObelixPro35,
  ObelixPro40,
  ObelixPro50
};
