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
void customise_rgn(char *rgb){
    printf("\x1b[38;5;%sm", rgb);
}

/**
* Resets the terminal customisation.
*/
void reset(){
    printf("%s", RESET);
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
    customise_rgn(colour);
    
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
    
    printf("\n");
    reset();
}

void render_course_name(char *name){
    customise(BOLD, DEFAULT);
    printf("%s", name);
    reset();
    printf("\n");
}

void render(Profile *profile){
    CourseList *curr = profile->head;
    while(curr){
        char *name = curr->course.name;
        render_course_name(name);
        ComponentList *comp = curr->course.head;
        while(comp){
            render_component(&comp->component);
            comp = comp->next;
        }
        printf("\n");
        curr = curr->next;
    }
}