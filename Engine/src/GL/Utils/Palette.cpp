
//#include "Image.hpp" // only for Exceptions (._.')
#include <GL/Utils/Palette.h>
//#include "ByteBuffer.h"
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <Platform/Exceptions.h>
#include <GL/gl.h>

namespace GL{
	
#ifdef _PLATFORM_PSP
	Palette::Palette(){
		format = PaletteData::RGB;
		type = PaletteData::UnsignedByte;
		data = new GLubyte[0];
	}
	Palette::Palette( GLubyte* palette, GLushort Size,PaletteData::format_t _format, bool staticMem ){
		size = Size<256?Size:256;
		format = _format;
		type = PaletteData::UnsignedByte;
		isStatic = staticMem;
		if (!isStatic){
			GLushort tsize = format==PaletteData::RGB?size*3:size*4;
			data = new GLubyte[tsize];
			std::memcpy( data, palette, tsize );
		}else{
			data = palette;
		}
	}
	Palette::~Palette(){
		if ( !isStatic && data ) delete[] data;
	}
	void Palette::Active(){
		glColorTable(GL_TEXTURE_2D, format, size, format, type, data);
	}
#else

#define PUSHSTATE() GLint restoreId; glGetIntegerv( GL_TEXTURE_BINDING_2D, &restoreId );
#define POPSTATE() glBindTexture( GL_TEXTURE_2D, restoreId );
	Palette::Palette():Texture(GL_TEXTURE_2D)
	{
		gc.Create( obj, glGenTextures, glDeleteTextures );
		format = PaletteData::RGB;
		type = PaletteData::UnsignedByte;
		data = new GLubyte[0];
	}
	Palette::Palette( GLubyte* palette, GLushort Size,PaletteData::format_t _format, bool staticMem ):Texture(GL_TEXTURE_2D){
		PUSHSTATE()
		
		gc.Create( obj, glGenTextures, glDeleteTextures );
		size = Size<256?Size:256;
		format = _format;
		type = PaletteData::UnsignedByte;
		isStatic = staticMem;
		if (!isStatic){
			GLushort tsize = format==PaletteData::RGB?size*3:size*4;
			data = new GLubyte[tsize];
			std::memcpy( data, palette, tsize );
		}else{
			data = palette;
		}
		
		glBindTexture( textureD, obj );
		glTexImage2D( textureD, 0, format, Size, 1, 0, format, type, data );
		
		Filter::filter_t filter = Filter::Nearest;
		
		glTexParameteri(textureD, GL_TEXTURE_MAG_FILTER, filter);
		glTexParameteri(textureD, GL_TEXTURE_MIN_FILTER, filter);
		
		glTexParameteri( textureD, GL_TEXTURE_WRAP_S, GL::Wrapping::ClampEdge );
		
		POPSTATE()
	}
	Palette::~Palette(){
		if ( !isStatic && data ) delete[] data;
	}
	
	Palette::operator GLuint() const
	{
		return obj;
	}
#endif
	
	GLushort Palette::GetSize() const{
		return size;
	}
	GLubyte* Palette::GetData() const{
		return data;
	}
	
}




	/*void Palette::Load( const std::string& filename, PaletteData::format_t Format,uchar multiply){
		
		// Load data from file
		std::ifstream file( filename.c_str(), std::ios::binary | std::ios::ate );
		if ( !file.is_open() ) throw FileException();

		uint fileSize = (uint)file.tellg();
		file.seekg( 0, std::ios::beg );

		ByteReader data( fileSize, true );
		file.read( (char*)data.Data(), fileSize );
		
		file.close();
		Load( data.Data(), format==PaletteData::RGB?data.Length()/3:data.Length()/4, Format, multiply);
		
	}*/