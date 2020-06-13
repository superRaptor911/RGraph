/**
 * @file File.cpp
 * @author Raptor (Aditya Aravind) (raptor.inc2018@gmail.com)
 * @brief File management class definition
 * @version 0.1
 * @date 12-06-2020
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#include <File.h>
#include <r_util.h>

#define ENABLE_DIRMAN

#ifdef ENABLE_DIRMAN
#include <DirMan.h>
#endif

using namespace rg;

bool File::open(const std::string &file_path, Fmode rwmode, bool binary)
{
	if (_is_open)
	{
		_file.close();
		R_CPRINT("Closing previous file and opening new");
	}

	std::string _file_path;
	
	#ifdef ENABLE_DIRMAN
		static DirMan dirman;
		_file_path = dirman.getActualPath(file_path);
	#else
		_file_path = file_path;
	#endif

	_is_binary = binary;

	if (_is_binary)
		_file.open(_file_path, rwmode | BINARY);
	else
		_file.open(_file_path, rwmode);

	_is_open = _file.good();
	
	if (!_is_open)
		R_CPRINT_ERR(("Unable to open file " + _file_path).c_str());
	
	return _is_open;
}


void File::close()
{
	if (_is_open)
		_file.close();
	else
		R_CPRINT_WARN("File already closed");
	
}


bool File::append(const std::string &data, bool newline)
{
	if (!_is_open || _is_binary)
		return false;
	
	_file.seekp(std::fstream::end);
	
	if (newline)
		_file <<"\n" << data;
	else
		_file << data;
	
	return !_file.bad();
}

bool File::appendBinary(const void *data, int size)
{
	if (!_is_open || !_is_binary)
		return false;

	_file.seekp(std::fstream::end);
	_file.write((char *)data, size);

	return !_file.bad();
}

/**
 * @brief Get size of file.
 * 
 * @return Size of file.
 */
int File::size()
{
	if (!_is_open)
		return -1;

	_file.seekg(std::fstream::end);
	return _file.tellg();
}

