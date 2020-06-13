/**
 * @file DirMan.h
 * @author Raptor (Aditya Aravind) (raptor.inc2018@gmail.com)
 * @brief Directory management
 * @version 0.1
 * @date 2020-06-11
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#ifndef DIRMAN_H
#define DIRMAN_H

#include <string>
#include <map>

namespace rg
{
	class DirMan
	{
	private:

		inline static std::map<std::string, std::string> _registered_paths;

	public:

		DirMan() {}

		/**
		 * @brief Get the Actual Path.
		 * 
		 * @param path 
		 * @return std::string path
		 */
		std::string getActualPath(const std::string &path);

		/**
		 * @brief Check if file exists or not.
		 * 
		 * @param path to file
		 * @return true if exits
		 * @return false if not
		 */
		bool fileExists(const std::string &path);


		bool dirExists(const std::string &path);

		void registerPath(const std::string &name, const std::string &path);

	};


}

#endif
