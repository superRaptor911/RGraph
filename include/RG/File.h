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
		
	private:
	
		std::fstream m_file;
		bool m_is_open = false;
		bool m_is_binary = false;
		char m_open_mode = 'r';

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
		bool open(const std::string &file_path, char open_mode = 'r',
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
		bool isOpen() { return m_is_open;}

		/**
		 * @brief Get Read/write mode
		 * 
		 * @return RWMode 
		 */
		char getOpenMode() { return m_open_mode;}


		/**
		 * @brief Add data at the end. Only available in Text mode.
		 * 
		 * @param data 
		 * @return true if successful.
		 * @return false 
		 */
		bool appendText(const std::string &data, bool newline = true);
		
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
			if (!m_is_open || !m_is_binary)
				return false;

			m_file.write((char *)&t, sizeof(t));

			return !m_file.bad();
		}

		/**
		 * @brief Get size of file in bytes.
		 * 
		 * @return long int 
		 */
		long int size();

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
			if (!m_is_open || !m_is_binary)
				return false;

			m_file.read((char *)&t, sizeof(t));

			return !m_file.bad();
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
		bool eof() { return m_file.eof();}

		~File();
	};
}

#endif
