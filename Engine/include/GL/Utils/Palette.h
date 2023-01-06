#pragma once

#ifndef OOGL_PALETTE_HPP
#define OOGL_PALETTE_HPP

/*
	Not forget active
	glEnable(GL_COLOR_TABLE);
*/

//#include <Platform/PlatformDefined.hpp>
#ifndef _PLATFORM_PSP
#include <GL/Texture.h>
#endif
#include <GL/Extensions.h>
#include <string>

namespace GL
{
	namespace PaletteData
	{
		enum format_t
		{
			RGB = GL_RGB,
			RGBA = GL_RGBA,
		};
		enum type_t
		{
			UnsignedByte = GL_UNSIGNED_BYTE,
			UnsignedByte332 = GL_UNSIGNED_BYTE_3_3_2,
			UnsignedByte233Rev = GL_UNSIGNED_BYTE_2_3_3_REV,
			UnsignedShort565 = GL_UNSIGNED_SHORT_5_6_5,
			UnsignedShort565Rev = GL_UNSIGNED_SHORT_5_6_5,
			UnsignedShort4444 = GL_UNSIGNED_SHORT_4_4_4_4,
			UnsignedShort4444Rev = GL_UNSIGNED_SHORT_4_4_4_4_REV,
			UnsignedShort5551 = GL_UNSIGNED_SHORT_5_5_5_1,
			UnsignedShort1555Rev = GL_UNSIGNED_SHORT_1_5_5_5_REV,
			UnsignedInt8888 = GL_UNSIGNED_INT_8_8_8_8,
			UnsignedInt8888Rev = GL_UNSIGNED_INT_8_8_8_8_REV,
			UnsignedInt101010102 = GL_UNSIGNED_INT_10_10_10_2
		};
	}
	
#ifdef _PLATFORM_PSP
	class Palette
	{
#else
	class Palette : public Texture
	{
#endif
	public:
		Palette();
		Palette( GLubyte* palette, GLushort size, PaletteData::format_t format = PaletteData::RGB, bool staticMem=false );
		~Palette();
		
#ifndef _PLATFORM_PSP
		operator GLuint() const;
		//const Palette& operator=( const Palette& other );
#endif
		void Active();
		
		GLushort GetSize() const;
		GLubyte* GetData() const;
	private:
		GLubyte* data;
		GLushort size;
		bool isStatic;
		PaletteData::format_t format;
		PaletteData::type_t type;
#ifndef _PLATFORM_PSP
		GLuint obj;
#endif
	};
}

#endif