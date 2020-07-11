/**
 * @file File.h
 * @author Raptor (Aditya Aravind) (raptor.inc2018@gmail.com)
 * @brief File management class
 * @version 0.1
 * @date 12-06-2020
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#ifndef FILE_H
#define FILE_H

#include <fstream>
#include <string>

namespace rg
{
	class File
	{
		typedef std::ios_base::openmode Fmode;

	public:

		static const Fmode READ = std::fstream::in;
		static const Fmode WRITE = std::fstream::out;
		static const Fmode READ_WRITE = (std::fstream::in | std::fstream::out);
		static const Fmode BINARY = std::fstream::binary;
		
	private:
	
		std::fstream _file;
		bool _is_open = false;
		Fmode _rwMode;
		bool _is_binary;

	public:
		
		/**
		 * @brief Open a file
		 * 
		 * @param file_path path to file.
		 * @param rwmode read write mode, default write.
		 * @param fmode file mode, default text.
		 * @param binary is binary file ?
		 * @return true if successful.
		 * @return false 
		 */
		bool open(const std::string &file_path, Fmode rwmode = WRITE, bool binary = false);
		
		/**
		 * @brief Close opened file.
		 * 
		 */
		void close();

		/**
		 * @brief Is file opened or not.
		 * 
		 * @return true if opened.
		 * @return false 
		 */
		bool isOpen() { return _is_open;}

		/**
		 * @brief Get Read/write mode
		 * 
		 * @return RWMode 
		 */
		Fmode getRWMode() { return _rwMode;}


		/**
		 * @brief Add data at the end. Only available in Text mode.
		 * 
		 * @param data 
		 * @return true if successful.
		 * @return false 
		 */
		bool append(const std::string &data, bool newline = true);
		
		/**
		 * @brief Add binary data at the end. Only available in Binary mode.
		 * 
		 * @param data 
		 * @param size of binary.
		 * @return true if successful.
		 * @return false 
		 */
		bool appendBinary(const void *data, int size);

		
		template<typename T>
		bool appendBinary(const T &t)
		{
			if (!_is_open || !_is_binary)
				return false;

			_file.seekp(std::fstream::end);
			_file.write((char *)t, sizeof(t));

			return !_file.bad();
		}

		/**
		 * @brief Get size of file in bytes.
		 * 
		 * @return int 
		 */
		int size();

		bool putAt();

		std::string getLine

		~File();
	};
}

#endif
