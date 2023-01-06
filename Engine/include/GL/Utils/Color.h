
#pragma once

#ifndef OOGL_COLOR_HPP
#define OOGL_COLOR_HPP

//#include <Platform/PlatformRender.hpp>

namespace GL
{
	/*
		Color
	*/
	struct Color
	{
	public:
		Color( float r = 0, float g = 0, float b = 0, float a = 255 ) : R( r ), G( g ), B( b ), A( a ) {}

		float R, G, B, A;
	};
	struct Color32
	{
	public:
		Color32( unsigned char r = 0, unsigned char g = 0, unsigned char b = 0, unsigned char a = 255 ) : R( r ), G( g ), B( b ), A( a ) {}

		unsigned char R, G, B, A;
	};
}

#endif