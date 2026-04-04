#include "structures.h"
#include <stdlib.h>
#include <stdio.h>

void free_profile(Profile *profile){
    free_course_list(profile->head);
    free(profile);
}

void free_course_list(CourseList *courselist){
    CourseList *curr = courselist;
    CourseList *next;
    while(curr){
        free(curr->course.name);
        free_component_list(curr->course.head);
        next = curr->next;
        free(curr);
        curr = next;
    }
}

void free_component_list(ComponentList *components){
    ComponentList *curr = components;
    ComponentList *next;
    while(curr){
        free(curr->component.name);
        next = curr->next;
        free(curr);
        curr = next; 
    }
}

CourseList *new_course_list(){
    CourseList *res = malloc(sizeof(CourseList));
    if(res == NULL){
        printf("Error: Cannot allocate memory\n");
        exit(1);
    }
    res->course.head = NULL;
    res->course.name = NULL;
    res->course.tail = NULL;
    res->next = NULL;
    return res;
}

ComponentList *new_component_list(){
    ComponentList *res = malloc(sizeof(ComponentList));
    res->component.name = NULL;
    res->next = NULL;
    return res;
}