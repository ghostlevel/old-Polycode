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

#include "PolyCore.h"
#if defined(_WINDOWS) || defined(_MINGW)
#include <windows.h>

#endif

namespace Polycode {
	
	Core::Core(int xRes, int yRes, bool fullScreen, int aaLevel, int frameRate) : EventDispatcher() {
		services = CoreServices::getInstance();
		input = new CoreInput();
		services->setCore(this);
		fps = 0;
		running = true;
		frames = 0;
		lastFrameTicks=0;
		lastFPSTicks=0;
		elapsed = 0;
		this->xRes = xRes;
		this->yRes = yRes;
		mouseEnabled = true;
		lastSleepFrameTicks = 0;
		
		refreshInterval = 1000 / frameRate;
	}
	
	void Core::enableMouse(bool newval) {
		mouseEnabled = newval;
	}
	
	int Core::getNumVideoModes() {
		return numVideoModes;
	}
	
	Number Core::getXRes() {
		return xRes;
	}

	Number Core::getYRes() {
		return yRes;
	}
	
	CoreInput *Core::getInput() {
		return input;
	}	
	
	Core::~Core() {
		printf("Shutting down core");
		delete services;
	}
	
	void Core::Shutdown() {	
		running = false;
	}
	
	Number Core::getElapsed() {
		return ((Number)elapsed)/1000.0f;
	}
	
	Number Core::getTicksFloat() {
		return ((Number)getTicks())/1000.0f;		
	}
	
	void Core::setVideoModeIndex(int index, bool fullScreen, int aaLevel) {
		vector<Rectangle> resList = getVideoModes();
		if(index >= resList.size())
			return;
		
		setVideoMode(resList[index].w, resList[index].h, fullScreen, aaLevel);
	}
	
	void Core::updateCore() {
		frames++;
		frameTicks = getTicks();
		elapsed = frameTicks - lastFrameTicks;
		
		if(elapsed > 1000)
			elapsed = 1000;
		services->Update(elapsed);

		if(frameTicks-lastFPSTicks >= 1000) {
			fps = frames;
			frames = 0;
			lastFPSTicks = frameTicks;
		}
		lastFrameTicks = frameTicks;
		
	}
	
	void Core::doSleep() {
		unsigned int ticks = getTicks();
		unsigned int ticksSinceLastFrame = ticks - lastSleepFrameTicks;
		if(ticksSinceLastFrame <= refreshInterval)
#if defined(_WINDOWS) || defined(_MINGW)
		Sleep((refreshInterval - ticksSinceLastFrame));
#else
			usleep((refreshInterval - ticksSinceLastFrame) * 1000);
#endif
		lastSleepFrameTicks = ticks;
	}
	
	
	Number Core::getFPS() {
		return fps;
	}
	
	CoreServices *Core::getServices() {
		return services;
	}
	
}
