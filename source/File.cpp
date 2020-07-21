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
#include <RG/File.h>
#include <RG/r_util.h>
#include <sstream>

using namespace rg;

bool File::open(const std::string &file_path, Fmode rwmode, bool binary, bool truncate)
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

	auto file_flags = rwmode;

	// Binary Mode flag
	if (_is_binary)
		file_flags = file_flags | BINARY;
	// Truncate flag
	if (truncate)
		file_flags = file_flags | std::fstream::trunc;
	else
		file_flags = file_flags | std::fstream::app;

	// Open file with rwmode with file flags
	_file.open(_file_path, file_flags);

	// Set variables
	_is_open = _file.good();
	_is_binary = binary;
	
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
	
	if (newline)
		_file << data << "\n";
	else
		_file << data;
	
	return !_file.bad();
}

bool File::appendBinary(const void *data, int size)
{
	if (!_is_open || !_is_binary)
		return false;
	
	_file.write((char *)data, size);

	return !_file.bad();
}

/**
 * @brief Get size of file.
 * 
 * @return Size of file.
 */
long int File::size()
{
	if (!_is_open)
		return -1;
	
	int old_pos = _file.tellg();
	_file.seekg(std::fstream::end);
	
	int sz = _file.tellg();
	_file.seekg(old_pos, std::fstream::beg);
	return sz;
}


std::string File::getFileContent()
{
	if (!_is_open || _rwMode == READ)
		return "";
	
	std::stringstream buffer;
	
	_file.seekg(std::fstream::beg);
	buffer << _file.rdbuf();
	
	return buffer.str();	
}

std::string File::getLine()
{
	std::string rtn_val;
	std::getline(_file,rtn_val);
	return rtn_val;
}

File::~File()
{
	if (_is_open)
		_file.close();
}

