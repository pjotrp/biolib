//
// File: MolscriptColorSet.cpp
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

#include "MolscriptColorSet.h"

using namespace bpp;

MolscriptColorSet::MolscriptColorSet()
{
  _colors["aliceblue"] = RGBColor(240, 248, 255);
  _colors["antiquewhite"] = RGBColor(250, 235, 215);
  _colors["aquamarine"] = RGBColor(127, 255, 212);
  _colors["azure"] = RGBColor(240, 255, 255);
  _colors["beige"] = RGBColor(245, 245, 220);
  _colors["bisque"] = RGBColor(255, 228, 196);
  _colors["black"] = RGBColor(0, 0, 0);
  _colors["blanchedalmond"] = RGBColor(255, 235, 205);
  _colors["blue"] = RGBColor(0, 0, 255);
  _colors["blueviolet"] = RGBColor(138, 43, 226);
  _colors["brown"] = RGBColor(165, 42, 42);
  _colors["burlywood"] = RGBColor(222, 184, 135);
  _colors["cadetblue"] = RGBColor(95, 158, 160);
  _colors["chartreuse"] = RGBColor(127, 255, 0);
  _colors["chocolate"] = RGBColor(210, 105, 30);
  _colors["coral"] = RGBColor(255, 127, 80);
  _colors["cornflowerblue"] = RGBColor(100, 149, 237);
  _colors["cornsilk"] = RGBColor(255, 248, 220);
  _colors["crimson"] = RGBColor(220, 20, 60);
  _colors["cyan"] = RGBColor(0, 255, 255);
  _colors["darkblue"] = RGBColor(0, 0, 139);
  _colors["darkcyan"] = RGBColor(0, 139, 139);
  _colors["darkgoldenrod"] = RGBColor(184, 134, 11);
  _colors["darkgray"] = RGBColor(169, 169, 169);
  _colors["darkgreen"] = RGBColor(0, 100, 0);
  _colors["darkgrey"] = RGBColor(169, 169, 169);
  _colors["darkkhaki"] = RGBColor(189, 183, 107);
  _colors["darkmagenta"] = RGBColor(139, 0, 139);
  _colors["darkolivegreen"] = RGBColor(85, 107, 47);
  _colors["darkorange"] = RGBColor(255, 140, 0);
  _colors["darkorchid"] = RGBColor(153, 50, 204);
  _colors["darkred"] = RGBColor(139, 0, 0);
  _colors["darksalmon"] = RGBColor(233, 150, 122);
  _colors["darkseagreen"] = RGBColor(143, 188, 143);
  _colors["darkslateblue"] = RGBColor(72, 61, 139);
  _colors["darkslategray"] = RGBColor(47, 79, 79);
  _colors["darkslategrey"] = RGBColor(47, 79, 79);
  _colors["darkturquoise"] = RGBColor(0, 206, 209);
  _colors["darkviolet"] = RGBColor(148, 0, 211);
  _colors["deeppink"] = RGBColor(255, 20, 147);
  _colors["deepskyblue"] = RGBColor(0, 191, 255);
  _colors["dimgray"] = RGBColor(105, 105, 105);
  _colors["dimgrey"] = RGBColor(105, 105, 105);
  _colors["dodgerblue"] = RGBColor(30, 144, 255);
  _colors["firebrick"] = RGBColor(178, 34, 34);
  _colors["floralwhite"] = RGBColor(255, 250, 240);
  _colors["forestgreen"] = RGBColor(34, 139, 34);
  _colors["gainsboro"] = RGBColor(220, 220, 220);
  _colors["ghostwhite"] = RGBColor(248, 248, 255);
  _colors["gold"] = RGBColor(255, 215, 0);
  _colors["goldenrod"] = RGBColor(218, 165, 32);
  _colors["gray"] = RGBColor(190, 190, 190);
  _colors["green"] = RGBColor(0, 255, 0);
  _colors["greenyellow"] = RGBColor(173, 255, 47);
  _colors["grey"] = RGBColor(190, 190, 190);
  _colors["honeydew"] = RGBColor(240, 255, 240);
  _colors["hotpink"] = RGBColor(255, 105, 180);
  _colors["indianred"] = RGBColor(205, 92, 92);
  _colors["indigo"] = RGBColor(75, 0, 130);
  _colors["ivory"] = RGBColor(255, 255, 240);
  _colors["khaki"] = RGBColor(240, 230, 140);
  _colors["lavender"] = RGBColor(230, 230, 250);
  _colors["lavenderblush"] = RGBColor(255, 240, 245);
  _colors["lawngreen"] = RGBColor(124, 252, 0);
  _colors["lemonchiffon"] = RGBColor(255, 250, 205);
  _colors["lightblue"] = RGBColor(173, 216, 230);
  _colors["lightcoral"] = RGBColor(240, 128, 128);
  _colors["lightcyan"] = RGBColor(224, 255, 255);
  _colors["lightgoldenrod"] = RGBColor(238, 221, 130);
  _colors["lightgoldenrodyellow"] = RGBColor(250, 250, 210);
  _colors["lightgray"] = RGBColor(211, 211, 211);
  _colors["lightgreen"] = RGBColor(144, 238, 144);
  _colors["lightgrey"] = RGBColor(211, 211, 211);
  _colors["lightpink"] = RGBColor(255, 182, 193);
  _colors["lightsalmon"] = RGBColor(255, 160, 122);
  _colors["lightseagreen"] = RGBColor(32, 178, 170);
  _colors["lightskyblue"] = RGBColor(135, 206, 250);
  _colors["lightslateblue"] = RGBColor(132, 112, 255);
  _colors["lightslategray"] = RGBColor(119, 136, 153);
  _colors["lightslategrey"] = RGBColor(119, 136, 153);
  _colors["lightsteelblue"] = RGBColor(176, 196, 222);
  _colors["lightyellow"] = RGBColor(255, 255, 224);
  _colors["limegreen"] = RGBColor(50, 205, 50);
  _colors["linen"] = RGBColor(250, 240, 230);
  _colors["magenta"] = RGBColor(255, 0, 255);
  _colors["maroon"] = RGBColor(176, 48, 96);
  _colors["mediumaquamarine"] = RGBColor(102, 205, 170);
  _colors["mediumblue"] = RGBColor(0, 0, 205);
  _colors["mediumorchid"] = RGBColor(186, 85, 211);
  _colors["mediumpurple"] = RGBColor(147, 112, 219);
  _colors["mediumseagreen"] = RGBColor(60, 179, 113);
  _colors["mediumslateblue"] = RGBColor(123, 104, 238);
  _colors["mediumspringgreen"] = RGBColor(0, 250, 154);
  _colors["mediumturquoise"] = RGBColor(72, 209, 204);
  _colors["mediumvioletred"] = RGBColor(199, 21, 133);
  _colors["midnightblue"] = RGBColor(25, 25, 112);
  _colors["mintcream"] = RGBColor(245, 255, 250);
  _colors["mistyrose"] = RGBColor(255, 228, 225);
  _colors["moccasin"] = RGBColor(255, 228, 181);
  _colors["navajowhite"] = RGBColor(255, 222, 173);
  _colors["navy"] = RGBColor(0, 0, 128);
  _colors["navyblue"] = RGBColor(0, 0, 128);
  _colors["oldlace"] = RGBColor(253, 245, 230);
  _colors["olivedrab"] = RGBColor(107, 142, 35);
  _colors["orange"] = RGBColor(255, 165, 0);
  _colors["orangered"] = RGBColor(255, 69, 0);
  _colors["orchid"] = RGBColor(218, 112, 214);
  _colors["palegoldenrod"] = RGBColor(238, 232, 170);
  _colors["palegreen"] = RGBColor(152, 251, 152);
  _colors["paleturquoise"] = RGBColor(175, 238, 238);
  _colors["palevioletred"] = RGBColor(219, 112, 147);
  _colors["papayawhip"] = RGBColor(255, 239, 213);
  _colors["peachpuff"] = RGBColor(255, 218, 185);
  _colors["peru"] = RGBColor(205, 133, 63);
  _colors["pink"] = RGBColor(255, 192, 203);
  _colors["plum"] = RGBColor(221, 160, 221);
  _colors["powderblue"] = RGBColor(176, 224, 230);
  _colors["purple"] = RGBColor(160, 32, 240);
  _colors["red"] = RGBColor(255, 0, 0);
  _colors["rosybrown"] = RGBColor(188, 143, 143);
  _colors["royalblue"] = RGBColor(65, 105, 225);
  _colors["saddlebrown"] = RGBColor(139, 69, 19);
  _colors["salmon"] = RGBColor(250, 128, 114);
  _colors["sandybrown"] = RGBColor(244, 164, 96);
  _colors["seagreen"] = RGBColor(46, 139, 87);
  _colors["seashell"] = RGBColor(255, 245, 238);
  _colors["sgibeet"] = RGBColor(142, 56, 142);
  _colors["sgibrightgray"] = RGBColor(197, 193, 170);
  _colors["sgibrightgrey"] = RGBColor(197, 193, 170);
  _colors["sgichartreuse"] = RGBColor(113, 198, 113);
  _colors["sgidarkgray"] = RGBColor(85, 85, 85);
  _colors["sgidarkgrey"] = RGBColor(85, 85, 85);
  _colors["sgilightblue"] = RGBColor(125, 158, 192);
  _colors["sgilightgray"] = RGBColor(170, 170, 170);
  _colors["sgilightgrey"] = RGBColor(170, 170, 170);
  _colors["sgimediumgray"] = RGBColor(132, 132, 132);
  _colors["sgimediumgrey"] = RGBColor(132, 132, 132);
  _colors["sgiolivedrab"] = RGBColor(142, 142, 56);
  _colors["sgisalmon"] = RGBColor(198, 113, 113);
  _colors["sgislateblue"] = RGBColor(113, 113, 198);
  _colors["sgiteal"] = RGBColor(56, 142, 142);
  _colors["sgiverydarkgray"] = RGBColor(40, 40, 40);
  _colors["sgiverydarkgrey"] = RGBColor(40, 40, 40);
  _colors["sgiverylightgray"] = RGBColor(214, 214, 214);
  _colors["sgiverylightgrey"] = RGBColor(214, 214, 214);
  _colors["sienna"] = RGBColor(160, 82, 45);
  _colors["skyblue"] = RGBColor(135, 206, 235);
  _colors["slateblue"] = RGBColor(106, 90, 205);
  _colors["slategray"] = RGBColor(112, 128, 144);
  _colors["slategrey"] = RGBColor(112, 128, 144);
  _colors["snow"] = RGBColor(255, 250, 250);
  _colors["springgreen"] = RGBColor(0, 255, 127);
  _colors["steelblue"] = RGBColor(70, 130, 180);
  _colors["tan"] = RGBColor(210, 180, 140);
  _colors["thistle"] = RGBColor(216, 191, 216);
  _colors["tomato"] = RGBColor(255, 99, 71);
  _colors["turquoise"] = RGBColor(64, 224, 208);
  _colors["violet"] = RGBColor(238, 130, 238);
  _colors["violetred"] = RGBColor(208, 32, 144);
  _colors["wheat"] = RGBColor(245, 222, 179);
  _colors["white"] = RGBColor(255, 255, 255);
  _colors["whitesmoke"] = RGBColor(245, 245, 245);
  _colors["yellow"] = RGBColor(255, 255, 0);
  _colors["yellowgreen"] = RGBColor(154, 205, 50);
}
