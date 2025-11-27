#ifndef DISPLAY_H
#define DISPLAY_H

#include "structures.h"

#define BLACK "30"
#define RED "31"
#define GREEN "32"
#define YELLOW "33"
#define BLUE "34"
#define MAGENTA "35"
#define CYAN "36"
#define WHITE "37"
#define DEFAULT "39" 

#define BLACK_BG "40"
#define RED_BG "41"
#define GREEN_BG "42"
#define YELLOW_BG "43"
#define BLUE_BG "44"
#define MAGENTA_BG "45"
#define CYAN_BG "46"
#define WHITE_BG "47"
#define DEFAULT_BG "49" 

#define RESET "\x1B[0m"

#define BOLD "1"
#define NOBOLD "0"
#define UNDERLINE "4"

#define NAME_WIDTH 32
#define WEIGHT_WIDTH 16
#define RESULT_WIDTH 16
#define TOTAL_WIDTH 64

#define HIGH_HD "201"
#define HD "46"
#define D "51"
#define C "21"
#define P "208"
#define F "196"
#define NA "247"
#define BLACK_RGB "16"
#define GRAY_RGB "233"
#define WHITE_RGB "255"

#define NA_STRING "N/A"

#define NAME_STR "NAME"
#define WEIGHT_STR "WEIGHTING"
#define RESULT_STR "RESULT"

/**
* Given a profile, renders it onto the screen.
* @param profile the profile to render.
* @param aim the gradeband to aim for.
*/
void render(Profile *profile, float aim);

#endif
