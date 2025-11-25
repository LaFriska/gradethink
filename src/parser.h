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

#endif