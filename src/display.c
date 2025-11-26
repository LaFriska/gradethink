#include "display.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>

/**
* Customises the terminal using ANSI escape codes.
* @param mode things like bold, underline etc.
* @param colour the colour of the text.
*/
void customise(char *mode, char*colour){
    printf("\x1b[%s;%sm", mode, colour);
}

/**
* Cutomises the terminal using ANSI escape codes, except
* it also sets the background colour.
* @param mode bold, underline etc.
* @param fg the colour of the text.
* @param bg the colour of the background.
*/
void customise_bg(char *mode, char *fg, char *bg){
    printf("\x1b[%s;%s;%sm", mode, fg, bg);
}

/**
* Customises the terminal using ANSI escape codes, using
* RGB. This does not work with bolded texts.
*/
void customise_rgn(char *rgb, char *bg){
    printf("\x1b[38;5;%sm\x1b[48;5;%sm", rgb, bg);
}

/**
* Resets the terminal customisation.
*/
void reset(){
    printf("%s", RESET);
}

/***
* Centers a text, and place it in a result buffer.
* It is src must be a pointer to an array of size+1 in length.
* @return -1 on fail, 0 on success.
*/
int centered_text(char *dst, char *src, size_t size){
    size_t len = strlen(src);
    if(len > size){
        return -1;
    }
    size_t rem = size - len;
    size_t left;
    size_t right;
    if(rem % 2 == 1){
        left = (rem-1)/2 + 1;
        right = (rem-1)/2;
    }
    left = rem/2;
    right = rem/2;
    memset(dst, ' ', left);
    strncpy(dst+left, src, len);
    memset(dst+left+len, ' ', right);
    dst[size] = '\0';
    return 0;
}

/**
* Associates a grade band of the result to a specific
* colour.
* @return result of a component between 0 and 1 inclusive, or -1
*         for a N/A grade.
*/
char *colour_from_grades(float res){
    
    if(res < 0){ //N/A
        return NA;
    }
    
    if(res >= 0.9){     //High HD
        return HIGH_HD;
    }else if(res >= 0.8){ //HD
        return HD;
    }else if(res >= 0.7){ //D
        return D;
    }else if(res >= 0.6){ //C
        return C;
    }else if(res >= 0.5){ //P
        return P;
    }else{                //F
        return F;
    }
}

void print_fixed_len(const char*str, size_t len, size_t actual_len){
    
    if(actual_len < len){
        actual_len = len;
    }
    
    char buf[actual_len+1];
    strncpy(buf, str, len);
    char *rest = &buf[len];
    memset(rest, ' ', actual_len - len);
    buf[actual_len] = '\0';
    printf("%s", buf);
}

/**
* Rounds a float to 2 decimal places.
*/
float round_2d(float f){
    return roundf(f * 100)/100;
}

void render_component(const Component *component){
    char *colour = colour_from_grades(component->result);
    customise_rgn(colour, GRAY_RGB);
    
    print_fixed_len(component->name, strlen(component->name), NAME_WIDTH);
    float mult_weight = round_2d(component->weight * 100);
    char buf[16];
    snprintf(buf, 12, "%.2f", mult_weight);
    size_t len = strlen(buf);
    buf[len] = '%';
    buf[len+1] = '\0';
    print_fixed_len(buf, strlen(buf), WEIGHT_WIDTH);
    
    if(component->result < 0){
        print_fixed_len(NA_STRING, strlen(NA_STRING), RESULT_WIDTH);
    }else{
        float mult_result = round_2d(component->result * 100);
        snprintf(buf, 12, "%.2f", mult_result);
        len = strlen(buf);
        buf[len] = '%';
        buf[len+1] = '\0';
        print_fixed_len(buf, strlen(buf), RESULT_WIDTH);
    }
    
    reset();
    printf("\n");
}

void render_categories(){
    customise_rgn(WHITE_RGB, GRAY_RGB);
    print_fixed_len(NAME_STR, strlen(NAME_STR), NAME_WIDTH);
    print_fixed_len(WEIGHT_STR, strlen(WEIGHT_STR), WEIGHT_WIDTH);
    print_fixed_len(RESULT_STR, strlen(RESULT_STR), RESULT_WIDTH);
    reset();
    printf("\n");
}

void render_course_name(char *name){
    char centered[TOTAL_WIDTH + 1];
    centered_text(centered, name, TOTAL_WIDTH);
    customise_bg(BOLD, WHITE, BLACK_BG);
    printf("%s", centered);
    reset();
    printf("\n");
}

void render(Profile *profile){
    CourseList *curr = profile->head;
    while(curr){
        char *name = curr->course.name;
        render_course_name(name);
        render_categories();
        ComponentList *comp = curr->course.head;
        while(comp){
            render_component(&comp->component);
            comp = comp->next;
        }
        printf("\n");
        curr = curr->next;
    }
}