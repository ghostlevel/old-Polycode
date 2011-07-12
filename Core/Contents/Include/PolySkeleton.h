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
#include "PolyBone.h"
#include <string>
#include <vector>
#include "PolyBezierCurve.h"
#include "PolyTween.h"

using std::string;
using std::vector;

namespace Polycode {
	
	class QuaternionTween;
	class BezierPathTween;
	
	class _PolyExport BoneTrack {
		public:
			BoneTrack(Bone *bone, Number length);
			~BoneTrack();
			void Play();
			void Stop();
			void Update();
		
			void setSpeed(Number speed);
			
			BezierCurve *scaleX;
			BezierCurve *scaleY;
			BezierCurve *scaleZ;
			BezierCurve *QuatW;
			BezierCurve *QuatX;
			BezierCurve *QuatY;
			BezierCurve *QuatZ;
			BezierCurve *LocX;			
			BezierCurve *LocY;
			BezierCurve *LocZ;
			
			Vector3 LocXVec;
			Vector3 LocYVec;
			Vector3 LocZVec;						

			Vector3 ScaleXVec;
			Vector3 ScaleYVec;
			Vector3 ScaleZVec;						
		
		
			Quaternion boneQuat;
			QuaternionTween *quatTween;
			
			Vector3 QuatWVec;
			Vector3 QuatXVec;
			Vector3 QuatYVec;			
			Vector3 QuatZVec;		
		
			
		protected:
		
			Number length;
		
			bool initialized;
		
			Bone *targetBone;
			vector <BezierPathTween*> pathTweens;
		
	};

	/**
	* Skeleton animation.
	*/ 
	class _PolyExport SkeletonAnimation {
		public:
		
			SkeletonAnimation(String name, Number duration);
			~SkeletonAnimation();		
			
			/**
			* Adds a new bone track
			* @param boneTrack New bone track to add.
			*/
			void addBoneTrack(BoneTrack *boneTrack);
			
			/**
			* Returns the animation name.
			*/
			String getName();
			
			/**
			* Plays the animation.
			*/
			void Play();			
			/**
			* Stops the animation.
			*/			
			void Stop();
			void Update();

			/**
			* Sets the animation multiplier speed.
			* @param speed Number to multiply the animation speed by.
			*/					
			void setSpeed(Number speed);
			
		protected:
			
			String name;
			Number duration;
			vector<BoneTrack*> boneTracks;
	};

	/**
	* 3D skeleton. Skeletons are applied to scene meshes and can be animated with loaded animations.
	*/
	class _PolyExport Skeleton : public SceneEntity {
		public:
		
			/**
			* Construct skeleton from a skeleton file.
			* @param fileName Skeleton file to load.
			*/
			Skeleton(String fileName);
			Skeleton();
			
			/**
			* Loads a new skeleton from file.
			* @param fileName Skeleton file to load.
			*/ 
			void loadSkeleton(String fileName);
			
			~Skeleton();
		
			/**
			* Play back a loaded animation.
			* @param animName Name of animation to play.
			*/
			void playAnimation(String animName);
						
			void playAnimationByIndex(int index);		
			
			/**
			* Loads in a new animation from a file and adds it to the skeleton.
			* @param name Name of the new animation.
			* @param fileName File to load animation from.
			*/			
			void addAnimation(String name, String fileName);
			
			/**
			* Returns a SkeletonAnimation by its name.
			* @param Name of animation to return.
			*/
			SkeletonAnimation *getAnimation(String name);
			void Update();
			
			/**
			* Get bone instance by its name
			* @param name Name of the bone.
			*/
			Bone *getBoneByName(String name);
			
			/**
			* Toggles bone visibility on and off.
			* @param val If true, bones will be rendered, if false, they will not.
			*/
			void bonesVisible(bool val);
			
			/**
			* Enables labels with bone names to be rendered. See SceneLabel for details on the parameters.
			* @param labelFont Font to use
			* @param size Size of font.
			* @param scale Scale of font.
			* @param labelColor Color of the label.
			*/
			void enableBoneLabels(String labelFont, Number size, Number scale, Color labelColor);
					
			/**
			* Returns the number of bones in the skeleton
			*/
			int getNumBones();
			
			/**
			* Returns a bone at the specified index.
			* @param index Bone index.
			*/
			Bone *getBone(int index);
		
			/**
			* Returns the current animation.
			*/
			SkeletonAnimation *getCurrentAnimation() { return currentAnimation; }
		
		protected:
		
			SceneEntity *bonesEntity;
		
			SkeletonAnimation *currentAnimation;
			vector<Bone*> bones;
			vector<SkeletonAnimation*> animations;
	};

}