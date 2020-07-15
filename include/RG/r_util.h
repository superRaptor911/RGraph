
/**
 * @file r_util.h
 * @author Raptor (Aditya Aravind) (raptor.inc2018@gmail.com)
 * @brief Utility
 * @version 0.1
 * @date 12-06-2020
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#ifndef R_UTIL_H
#define R_UTIL_H

#include <string>
#include <vector>

// Macros
#define R_CPRINT_ERR(msg) printf("Error in file %s:%d \n----------> %s\n",  __FILE__, __LINE__, msg);
#define R_CPRINT(msg) printf("%s.\n",msg);
#define R_CPRINT_WARN(msg) printf("Warning : %s.\n", msg);

namespace rg
{
namespace util 
{
	//String
	inline std::vector<std::string> splitStr(const std::string &str, const std::string &delimiter);

	/////////////////////////////Function Definition //////////////////////////////

	std::vector<std::string> splitStr(const std::string &str, const std::string &delimiter)
	{
		std::vector<std::string> rtn_val;

		// Handle delimiter = ""
		if (delimiter.size() == 0)
		{
			rtn_val.push_back(str);
			return rtn_val;
		}

		// Reserve vector size for performance
		rtn_val.reserve(std::min(str.size() / delimiter.size() + 1, 100000UL));
		
		// Allocate memory
		char *token = new char[str.size() + 1];
		
		// Length of delimiter
		int del_len = delimiter.size();
		
		// For delimiter
		int i = 0;

		// For token
		int j = 0;

		// Iterate input string
		for (auto &it : str)
		{
			// Char clean so, add to token
			if (it != delimiter[i])
			{
				i = 0;
				token[j] = it;
				j++;
			}
			// Char may not be clean
			else
			{
				// goto next delimiter char 
				i++;

				// chars were dirty, finalize token and push to vector
				if (i == del_len)
				{
					// Position till where token is clean
					int p = j - del_len + 1;
					token[p] = '\0';
					
					// prevent "" from inserting
					if (p != 0)
						rtn_val.push_back(token);
					
					j = 0;
					i = 0;
				}
				// Char maybe dirty but still add it to token
				else
				{
					token[j] = it;
					j++;
				}
			}
		}

		// Insert last token
		if (j != 0)
		{
			token[j] = '\0';
			rtn_val.push_back(token);
		}

		// De-allocate memory
		delete[] token;
		return rtn_val;
	}
}
}
#endif