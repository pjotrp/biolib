//
// File: DvipsColorSet.cpp
// Created by: Julien Dutheil
// Created on: Mon Apr 14 2008
//

/*
Copyright or © or Copr. CNRS, (November 17, 2008)

This software is a computer program whose purpose is to provide utilitary
classes. This file belongs to the Bio++ Project.

This software is governed by the CeCILL  license under French law and
abiding by the rules of distribution of free software.  You can  use, 
modify and/ or redistribute the software under the terms of the CeCILL
license as circulated by CEA, CNRS and INRIA at the following URL
"http://www.cecill.info". 

As a counterpart to the access to the source code and  rights to copy,
modify and redistribute granted by the license, users are provided only
with a limited warranty  and the software's author,  the holder of the
economic rights,  and the successive licensors  have only  limited
liability. 

In this respect, the user's attention is drawn to the risks associated
with loading,  using,  modifying and/or developing or reproducing the
software by the user in light of its specific status of free software,
that may mean  that it is complicated to manipulate,  and  that  also
therefore means  that it is reserved for developers  and  experienced
professionals having in-depth computer knowledge. Users are therefore
encouraged to load and test the software's suitability as regards their
requirements in conditions enabling the security of their systems and/or 
data to be ensured and,  more generally, to use and operate it in the 
same conditions as regards security. 

The fact that you are presently reading this means that you have had
knowledge of the CeCILL license and that you accept its terms.
*/

#include "DvipsColorSet.h"

using namespace bpp;

DvipsColorSet::DvipsColorSet()
{
  _colors["GreenYellow"] = RGBColor(217, 255, 79);
  _colors["Yellow"] = RGBColor(255, 255, 0);
  _colors["Goldenrod"] = RGBColor(255, 230, 41);
  _colors["Dandelion"] = RGBColor(255, 181, 41);
  _colors["Apricot"] = RGBColor(255, 173, 122);
  _colors["Peach"] = RGBColor(255, 128, 77);
  _colors["Melon"] = RGBColor(255, 138, 128);
  _colors["YellowOrange"] = RGBColor(255, 148, 0);
  _colors["Orange"] = RGBColor(255, 99, 33);
  _colors["BurntOrange"] = RGBColor(255, 125, 0);
  _colors["Bittersweet"] = RGBColor(194, 48, 0);
  _colors["RedOrange"] = RGBColor(255, 59, 33);
  _colors["Mahogany"] = RGBColor(166, 25, 22);
  _colors["Maroon"] = RGBColor(173, 23, 55);
  _colors["BrickRed"] = RGBColor(184, 20, 11);
  _colors["Red"] = RGBColor(255, 0, 0);
  _colors["OrangeRed"] = RGBColor(255, 0, 128);
  _colors["RubineRed"] = RGBColor(255, 0, 222);
  _colors["WildStrawberry"] = RGBColor(255, 10, 156);
  _colors["Salmon"] = RGBColor(255, 120, 158);
  _colors["CarnationPink"] = RGBColor(255, 94, 255);
  _colors["Magenta"] = RGBColor(255, 0, 255);
  _colors["VioletRed"] = RGBColor(255, 48, 255);
  _colors["Rhodamine"] = RGBColor(255, 46, 255);
  _colors["Mulberry"] = RGBColor(165, 25, 250);
  _colors["RedViolet"] = RGBColor(157, 17, 168);
  _colors["Fuchsia"] = RGBColor(124, 21, 235);
  _colors["Lavender"] = RGBColor(255, 133, 255);
  _colors["Thistle"] = RGBColor(224, 105, 255);
  _colors["Orchid"] = RGBColor(173, 92, 255);
  _colors["DarkOrchid"] = RGBColor(153, 51, 204);
  _colors["Purple"] = RGBColor(140, 36, 255);
  _colors["Plum"] = RGBColor(128, 0, 255);
  _colors["Violet"] = RGBColor(54, 31, 255);
  _colors["RoyalPurple"] = RGBColor(64, 25, 255);
  _colors["BlueViolet"] = RGBColor(34, 22, 245);
  _colors["Periwinkle"] = RGBColor(110, 115, 255);
  _colors["CadetBlue"] = RGBColor(97, 110, 196);
  _colors["CornflowerBlue"] = RGBColor(89, 222, 255);
  _colors["MidnightBlue"] = RGBColor(3, 126, 145);
  _colors["NavyBlue"] = RGBColor(15, 117, 255);
  _colors["RoyalBlue"] = RGBColor(0, 128, 255);
  _colors["Blue"] = RGBColor(0, 0, 255);
  _colors["Cerulean"] = RGBColor(15, 227, 255);
  _colors["Cyan"] = RGBColor(0, 255, 255);
  _colors["ProcessBlue"] = RGBColor(10, 255, 255);
  _colors["SkyBlue"] = RGBColor(97, 255, 224);
  _colors["Turquoise"] = RGBColor(38, 255, 204);
  _colors["TealBlue"] = RGBColor(35, 250, 165);
  _colors["Aquamarine"] = RGBColor(46, 255, 178);
  _colors["BlueGreen"] = RGBColor(38, 255, 171);
  _colors["Emerald"] = RGBColor(0, 255, 128);
  _colors["JungleGreen"] = RGBColor(3, 255, 122);
  _colors["SeaGreen"] = RGBColor(79, 255, 128);
  _colors["Green"] = RGBColor(0, 255, 0);
  _colors["ForestGreen"] = RGBColor(20, 224, 27);
  _colors["PineGreen"] = RGBColor(15, 191, 78);
  _colors["LimeGreen"] = RGBColor(128, 255, 0);
  _colors["YellowGreen"] = RGBColor(143, 255, 66);
  _colors["SpringGreen"] = RGBColor(189, 255, 61);
  _colors["OliveGreen"] = RGBColor(55, 153, 8);
  _colors["RawSienna"] = RGBColor(140, 39, 0);
  _colors["Sepia"] = RGBColor(77, 13, 0);
  _colors["Brown"] = RGBColor(102, 19, 0);
  _colors["Tan"] = RGBColor(219, 148, 112);
  _colors["Gray"] = RGBColor(128, 128, 128);
  _colors["Black"] = RGBColor(0, 0, 0);
  _colors["White"] = RGBColor(255, 255, 255);
}

