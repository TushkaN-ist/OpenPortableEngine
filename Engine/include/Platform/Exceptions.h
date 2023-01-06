#pragma once

#include <string>
#include <exception>

namespace GL{
	
	/*
		Exceptions
	*/
	class FileException : public std::exception
	{
		virtual const char* what() const throw()
		{
			return "File could not be opened!";
		}
	};
	class FormatException : public std::exception
	{
		virtual const char* what() const throw()
		{
			return "Image file format not supported!";
		}
	};
	
	// Shaders
	class CompileException : public std::exception 
	{
	public:
		CompileException( const std::string& str ) throw() : infoLog( str ) {}
		~CompileException() throw() {}

		virtual const char* what() const throw()
		{
			return infoLog.c_str();
		}

	private:
		std::string infoLog;
	};
	
	class LinkException : public std::exception 
	{
	public:
		LinkException( const std::string& str ) throw() : infoLog( str ) {}
		~LinkException() throw() {}

		virtual const char* what() const throw()
		{
			return infoLog.c_str();
		}

	private:
		std::string infoLog;
	};

}