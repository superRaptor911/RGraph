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

		static const Fmode BINARY = std::fstream::binary;

	public:

		static const Fmode READ = std::fstream::in;
		static const Fmode WRITE = std::fstream::out;
		static const Fmode READ_WRITE = (std::fstream::in | std::fstream::out);
		
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
		 * @param truncate erase file
		 * @return true if successful.
		 * @return false 
		 */
		bool open(const std::string &file_path, Fmode rwmode = WRITE, 
					bool binary = false, bool truncate = false);
		
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

		/**
		 * @brief Append Object
		 * 
		 * @tparam Any object 
		 * @param t 
		 * @return true 
		 * @return false 
		 */
		template<typename T>
		bool appendBinary(T &t)
		{
			if (!_is_open || !_is_binary)
				return false;

			_file.write((char *)&t, sizeof(t));

			return !_file.bad();
		}

		/**
		 * @brief Get size of file in bytes.
		 * 
		 * @return long int 
		 */
		long int size();

		bool putAt();

		/**
		 * @brief Get the File Content
		 * 
		 * @return std::string 
		 */
		std::string getFileContent();

		/**
		 * @brief Read from file
		 * 
		 * @param data 
		 * @param size 
		 * @return true 
		 * @return false 
		 */
		bool readBinary(const void *data, int size);

		template<typename T>
		bool readBinary(T &t)
		{
			if (!_is_open || !_is_binary)
				return false;

			_file.read((char *)&t, sizeof(t));

			return !_file.bad();
		}


		/**
		 * @brief Get Line
		 * 
		 * @return std::string 
		 */
		std::string getLine();

		/**
		 * @brief check if reached end of file
		 * 
		 * @return true 
		 * @return false 
		 */
		bool eof() { return _file.eof();}

		~File();
	};
}

#endif
