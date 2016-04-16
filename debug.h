/*
 * debug.h
 *
 *  Created on: Apr 16, 2016
 *      Author: vincent
 */

#ifndef DEBUG_H_
#define DEBUG_H_


#ifdef DEBUG_
#define DEBUG_PORT Serial


#define DEBUG_BEGIN(baud) DEBUG_PORT.begin(baud)
#define DEBUG_WRITE(...) DEBUG_PORT.write(__VA_ARGS__)
#define DEBUG_PRINT(...) DEBUG_PORT.print(__VA_ARGS__)
#define DEBUG_PRINTLN(...) DEBUG_PORT.println(__VA_ARGS__)

#else
#define DEBUG_BEGIN(baud)
#define DEBUG_WRITE(...)
#define DEBUG_PRINT(...)
#define DEBUG_PRINTLN(...)
#endif // DEBUG_


#endif /* DEBUG_H_ */
