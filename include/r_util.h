
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

#ifdef ENABLE_LOGGING
/**
 * @brief Print console error
 * 
 */
#define R_CPRINT_ERR(msg) printf("Error in file %s:%d \n----------> %s\n",  __FILE__, __LINE__, msg);

#define R_CPRINT(msg) printf("%s.\n",msg);

#define R_CPRINT_WARN(msg) printf("Warning : %s.\n", msg);


#else

#define R_CPRINT_ERR(msg) ;

#define R_CPRINT(msg) ;

#define R_CPRINT_WARN(msg) ;

#endif

#endif