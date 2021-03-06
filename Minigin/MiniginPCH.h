#pragma once

#include "targetver.h"

#include <stdio.h>
#include <iostream> // std::cout
#include <sstream> // stringstream
#include <tchar.h>
#include <memory> // smart pointers
#include <vector>
//#pragma  warning(push)
//#pragma warning( disable: 4201)
//#include <glm/glm.hpp>
//#pragma warning (pop)


#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include "Log.h" // Various logging functions

struct GameContext
{
	float deltaT;
	//could have more information 
	//that needs to be shared in all update methods
	//but not needed at this time
};

struct Pos
{
	float x, y, z;
};

struct Scale
{
	float w, h;
};

struct Rect
{
	Rect();
	Rect(const Pos& pos, const Scale& scale)
		:x{ pos.x }
		,y{ pos.y }
		,w{ scale.w }
		,h{ scale.h }
	{}
		
	float x, y, w, h;
};