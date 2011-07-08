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

#include "PolyFont.h"

using namespace Polycode;

Font::Font(String fileName) : buffer(NULL), valid(false) {
	FT_Library FTLibrary;
	FT_Init_FreeType(&FTLibrary);
	
	OSFILE *file = OSBasics::open(fileName, "rb");
	long progsize = 0;
	
	if (file) {
		OSBasics::seek(file, 0, SEEK_END);	
		progsize = OSBasics::tell(file);
		OSBasics::seek(file, 0, SEEK_SET);
		buffer = (unsigned char*)malloc(progsize);
		memset(buffer, 0, progsize);
		OSBasics::read(buffer, progsize, 1, file);
		OSBasics::close(file);
		valid = true;
	} else {
		Logger::log("File not found loading font %s\n", fileName.c_str());
	}

	if(valid && FT_New_Memory_Face(FTLibrary, buffer, progsize, 0, &ftFace) != 0) {
		Logger::log("Error loading font %s\n", fileName.c_str());
		valid = false;
	}
	
	if (valid)
		FT_Select_Charmap(ftFace, FT_ENCODING_UNICODE);	
	//FT_New_Face(FTLibrary, fileName.c_str(), 0, &ftFace);	
//	free(buffer);
}

bool Font::isValid() {
	return valid;
}

Font::~Font() {
	free(buffer);
}

FT_Face Font::getFace() {
	return ftFace;
}