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

bool File::open(const std::string &file_path, char open_mode, bool binary, bool truncate)
{
	if (m_is_open)
	{
		m_file.close();
		R_CPRINT("Closing previous file and opening new");
	}

	m_is_binary = binary;
	m_open_mode = open_mode;
	std::ios_base::openmode file_flags;


	
	if (m_open_mode == 'a')
		file_flags = std::fstream::app;
	else if (m_open_mode == 'b')
		file_flags = std::fstream::in | std::fstream::out;
	else if (m_open_mode == 'r')
		file_flags = std::fstream::in;
	else if (m_open_mode == 'w')
		file_flags = std::fstream::out;
	else
	{
		R_CPRINT("Error : wrong file open flag provided");
		return false;
	}

	// Binary Mode flag
	if (m_is_binary)
		file_flags = file_flags | std::fstream::binary;
	// Truncate flag
	if (truncate)
		file_flags = file_flags | std::fstream::trunc;

	// Open file with rwmode with file flags
	m_file.open(file_path, file_flags);

	// Set variables
	m_is_open = m_file.good();
	
	if (!m_is_open)
		R_CPRINT_ERR(("Unable to open file " + file_path).c_str());
	
	return m_is_open;
}


void File::close()
{
	if (m_is_open)
		m_file.close();
	else
		R_CPRINT_WARN("File already closed");
	
}


bool File::appendText(const std::string &data, bool newline)
{
	if (!m_is_open || m_is_binary)
		return false;
	
	if (newline)
		m_file << data << "\n";
	else
		m_file << data;
	
	return !m_file.bad();
}

bool File::appendBinary(const void *data, int size)
{
	if (!m_is_open || !m_is_binary)
		return false;
	
	m_file.write((char *)data, size);

	return !m_file.bad();
}

/**
 * @brief Get size of file.
 * 
 * @return Size of file.
 */
long int File::size()
{
	if (!m_is_open)
		return -1;
	
	int old_pos = m_file.tellg();
	m_file.seekg(std::fstream::end);
	
	int sz = m_file.tellg();
	m_file.seekg(old_pos, std::fstream::beg);
	return sz;
}


std::string File::getFileContent()
{
	// Check file open or not
	if (!m_is_open || !(m_open_mode == 'r' || m_open_mode == 'b'))
		return "";
	
	std::stringstream buffer;
	
	m_file.seekg(std::fstream::beg);
	buffer << m_file.rdbuf();
	
	return buffer.str();	
}

std::string File::getLine()
{
	std::string rtn_val;
	std::getline(m_file, rtn_val);
	return rtn_val;
}

File::~File()
{
	if (m_is_open)
		m_file.close();
}

