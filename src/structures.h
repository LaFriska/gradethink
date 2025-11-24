#ifndef STRUCTURES_H
#define STRUCTURES_H

/*
* A component is a single assessment within a course. It has a 
* name, weighting, and percentage value result associated with 
* how well the student did in this component. 
*/
struct Component{
    char name[72]; //A name, at-most 72 characters, checks should be 64 as a safeguard.
    float weight; //Total weighting, must be in [0, 1].
    float result; //Result, must be [0, 1] ∪ {-1}. It is -1 if the result is not yet ready (displayed as N/A)
};

/**
* A linked list of components.
*/
struct ComponentList{
    struct Component component;
    struct ComponentList *next;
};

/**
* A course is a ComponentList with a name.
*/
struct Course{
    char name[72];
    struct ComponentList headComponent;
}; 

/**
* A linked list of courses.
*/
struct CourseList{
    struct Course course;
    struct CourseList *next;
};

typedef struct Component Component;
typedef struct ComponentList ComponentList;
typedef struct Course Course;
typedef struct CourseList CourseList;

#endif