#ifndef PARSER_H
#define PARSER_H 

#include "structures.h"

/**
* With a given line in the input profile file, and the length of the
* string, and a result parameter profile, parses the line and update 
* the profile accordingly. The function exits on error while printing 
* the appropriate error message to stdin. 
* @return 0 on success, otherwise, return -1.
*/
int parse_line(const char *line, Profile *profile);

/**
* Verifies that the profile is valid. This function
* returns if and only if it is valid, otherwise prints an error message
* and exits.
*/
void verify(Profile *profile);


/**
* Used to parse a string representation of either a percentage,
* fraction, or integer given a default denominator into a float.
* Note that the output must be a float between 0 and 1 inclusive,
* otherwise -1 is returned.
* @param s can be of the following form: percentage (e.g. 10%), 
*          fraction (e.g. 6/7), or an integer (e.g. 6). If an integer x
*          is input, then it is parsed as x/default_denom. 
* @param default_denom the default denominator used when an integer is passed 
*                      as the first argument to this function.
* @return a float representing the input string, or -1 if the input is invalid.
*/
float parse_float(const char *s, float default_denom);

#endif