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
#include "PolyString.h"
#include "PolyGlobals.h"
#include "PolyCore.h"
#include "PolyString.h"
#include "PolyRectangle.h"
#include <vector>
#include "PolyGLHeaders.h"
#include "PolyGLRenderer.h"
#include <mach/mach_time.h>
#include <unistd.h>

#include "PolyGLSLShaderModule.h"
#import <Cocoa/Cocoa.h>

using std::vector;

@class PolycodeView;

namespace Polycode {
	
	class _PolyExport PosixMutex : public CoreMutex {
	public:
		pthread_mutex_t pMutex;
	};
	
	class CocoaEvent {
	public:
		int eventGroup;
		int eventCode;
		
		int mouseX;
		int mouseY;
		
		PolyKEY keyCode;
		wchar_t unicodeChar;
		
		char mouseButton;
		
		static const int INPUT_EVENT = 0;
	};
	
	class _PolyExport CocoaCore : public Core {		
	public:
		
		CocoaCore(PolycodeView *view, int xRes, int yRes, bool fullScreen, int aaLevel, int frameRate);
		virtual ~CocoaCore();
		
		void enableMouse(bool newval);
		unsigned int getTicks();		
		bool Update();		
		void setVideoMode(int xRes, int yRes, bool fullScreen, int aaLevel);		
		void resizeTo(int xRes, int yRes);
		void createThread(Threaded *target);		
		
		void createFolder(String folderPath);
		void copyDiskItem(String itemPath, String destItemPath);
		void moveDiskItem(String itemPath, String destItemPath);		
		void removeDiskItem(String itemPath);		
		String openFolderPicker();
		vector<string> openFilePicker(vector<CoreFileExtension> extensions, bool allowMultiple);
		
		void setCursor(int cursorType);
		
		void copyStringToClipboard(String str);
		String getClipboardString();		
		
//		static pascal OSStatus coreEventHandler (EventHandlerCallRef next, EventRef event, void *data);	
		
		void lockMutex(CoreMutex *mutex);
		void unlockMutex(CoreMutex *mutex);
		CoreMutex *createMutex();		
		
		void checkEvents();
		
		vector<Rectangle> getVideoModes();
		
		int lastMouseY;
		int lastMouseX;		
		
		CoreMutex *eventMutex;
		
		vector<CocoaEvent> cocoaEvents;
		
		NSOpenGLContext *context;
		
	protected:	
		PolycodeView *glView;
		
		uint64_t initTime;		
				
	};
}