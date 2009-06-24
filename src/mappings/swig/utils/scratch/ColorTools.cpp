//
// File: ColorTools.cpp
// Created by: Julien Dutheil
// Created on: Thu Mar 16 2006
//

/*
Copyright or © or Copr. CNRS, (November 17, 2004)

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

#include "ColorTools.h"

using namespace bpp;

const RGBColor ColorTools::RED    = RGBColor(255,0,0);
const RGBColor ColorTools::GREEN  = RGBColor(0,255,0);
const RGBColor ColorTools::BLUE   = RGBColor(0,0,255);
const RGBColor ColorTools::BLACK  = RGBColor(0,0,0);
const RGBColor ColorTools::WHITE  = RGBColor(255,255,255);
const RGBColor ColorTools::YELLOW = RGBColor(255,255,0);
const RGBColor ColorTools::CYAN   = RGBColor(0,255,255);
const RGBColor ColorTools::MAGENTA = RGBColor(255,0,255);
const RGBColor ColorTools::ORANGE = RGBColor(255,127,0);
     
vector<RGBColor> ColorTools::gradient(unsigned int n, const RGBColor & low, const RGBColor & high) 
{
  vector<RGBColor> colors(n);
  for(unsigned int i = 0; i < n-1; i++)
  {
    colors[i][0] = low[0] + (int)floor((double)i*(double)((int)high[0] - (int)low[0])/(double)(n-1));
    colors[i][1] = low[1] + (int)floor((double)i*(double)((int)high[1] - (int)low[1])/(double)(n-1));
    colors[i][2] = low[2] + (int)floor((double)i*(double)((int)high[2] - (int)low[2])/(double)(n-1));
  }
  colors[n-1] = high;
  return colors;
}

vector<RGBColor> ColorTools::gradient(unsigned int n, const RGBColor & low, const RGBColor & mid, const RGBColor & high)
{
  unsigned int lower = n/2;
  unsigned int upper = n - lower;
  vector<RGBColor> colors1 = gradient(lower, low, mid);
  vector<RGBColor> colors2 = gradient(upper+1, mid, high);
  for(unsigned int i = 1; i < colors2.size(); i++)
  {
    colors1.push_back(colors2[i]);
  }
  return colors1;
}

