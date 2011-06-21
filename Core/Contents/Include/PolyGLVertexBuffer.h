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


#pragma once

#ifdef _WINDOWS
#include <windows.h>
#endif
#include "PolyString.h"
#include "PolyGlobals.h"
#include "PolyMesh.h"
#include "PolyGLRenderer.h"

#include "PolyGLHeaders.h"

namespace Polycode {
	
	class _PolyExport OpenGLVertexBuffer : public VertexBuffer {
	public:
		
		OpenGLVertexBuffer(Mesh *mesh);
		virtual ~OpenGLVertexBuffer();
		
		GLuint getVertexBufferID();		
		GLuint getTextCoordBufferID();	
		GLuint getNormalBufferID();
		GLuint getColorBufferID();
		
	private:
		
		GLuint vertexBufferID;
		GLuint texCoordBufferID;
		GLuint normalBufferID;
		GLuint colorBufferID;		
	};
	
}