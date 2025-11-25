#include "display.h"
#include <stdio.h>
#include <stdbool.h>

/**
* Customises the terminal using ANSI escape codes.
* @param mode things like bold, underline etc.
* @param colour the colour of the text.
*/
void customise(char *mode, char*colour){
    printf("\x1b[%s;%sm", mode, colour);
}

/**
* Resets the terminal customisation.
*/
void reset(){
    printf("%s", RESET);
}

void render_course_name(char *name){
    customise(BOLD, BLUE);
    printf("%s\n", name);
    reset();
}

void render(Profile *profile){
    CourseList *curr = profile->head;
    while(curr){
        char *name = curr->course.name;
        render_course_name(name);
        curr = curr->next;
        //TODO components.
    }
}