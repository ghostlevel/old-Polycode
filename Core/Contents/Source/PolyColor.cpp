/*
 Copyright (C) 2011 by Ivan Safrin
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
*/

#include "PolyColor.h"

using namespace Polycode;

Color::Color() : r(1),g(1),b(1),a(1){

}

Color::Color(Number r,Number g, Number b, Number a) {
	setColor(r,g,b,a);
}

Color::Color(Color *color) {
	setColor(color->r, color->g, color->b, color->a);
}

Color::Color(int r,int g, int b, int a) {
	setColorRGBA(r,g,b,a);
}

Color::Color(unsigned int hex) {
	setColorHex(hex);
}

void Color::setColorHexRGB(unsigned int hex) {

	int tr = (hex >> 24) & 0xFF;
	int tb = (hex >> 16) & 0xFF;
	int tg = (hex >> 8) & 0xFF;
//	int ta = (hex ) & 0xFF;
	
	r = ((Number)tr)/255.0f;
	g = ((Number)tg)/255.0f;
	b = ((Number)tb)/255.0f;
//	a = ((Number)ta)/255.0f;	
	
}

void Color::setColorHex(unsigned int hex) {
	int tr = (hex >> 24) & 0xFF;
	int tg = (hex >> 16) & 0xFF;
	int tb = (hex >> 8) & 0xFF;
	int ta = (hex ) & 0xFF;
	
	r = ((Number)tr)/255.0f;
	g = ((Number)tg)/255.0f;
	b = ((Number)tb)/255.0f;
	a = ((Number)ta)/255.0f;	
}

Number Color::getBrightness() {
	return (r+g+b) / 3.0f;
}

void Color::setColorHSV(Number H, Number S, Number V) {
	Number r,g,b;
    
	if (S == 0) {
        r = g = b = V;
    } else {
        int i = (int)(H/60.0f);
        Number f = (H/60.0f) - (Number)i;
        Number p = V*(1.0f-S);
        Number q = V*(1.0f-S*f);
        Number t = V*(1.0f-(1.0f-f)*S);
        switch (i) {
            case 0: r = V;   g = t;  b = p;  break;
            case 1: r = q;  g = V;   b = p;  break;
            case 2: r = p;  g = V;   b = t;  break;
            case 3: r = p;  g = q;  b = V;   break;
            case 4: r = t;  g = p;  b = V;   break;
            case 5: r = V;   g = p;  b = q;  break;
        }
    }

	setColor(r, g, b, a);
}

void Color::Random() {
	setColor((Number)rand()/RAND_MAX, (Number)rand()/RAND_MAX, (Number)rand()/RAND_MAX, 1.0f);
}

void Color::setColorRGB(int r, int g, int b) {
	this->r = ((Number)r)/255.0f;
	this->g = ((Number)g)/255.0f;
	this->b = ((Number)b)/255.0f;
}
	
void Color::setColorRGBA(int r, int g, int b, int a) {
	this->r = ((Number)r)/255.0f;
	this->g = ((Number)g)/255.0f;
	this->b = ((Number)b)/255.0f;
	this->a = ((Number)a)/255.0f;
}

void Color::setColor(Color *color) {
	this->r = color->r;
	this->g = color->g;
	this->b = color->b;
	this->a = color->a;
}


void Color::setColor(Number r, Number g, Number b, Number a) {
	this->r = r;
	this->g = g;
	this->b = b;
	this->a = a;
}

unsigned int Color::getUint() {
	
	unsigned int ir = 255.0f*r;
	unsigned int ig = 255.0f*g;
	unsigned int ib = 255.0f*b;
	unsigned int ia = 255.0f*a;
		
	unsigned int val = ((ia & 0xFF) << 24) | ((ib & 0xFF) << 16) | ((ig & 0xFF) << 8) | (ir & 0xFF);
	return val;
}

Color::~Color() {

}