#ifndef STRUCTURES_H
#define STRUCTURES_H

/*
* A component is a single assessment within a course. It has a 
* name, weighting, and percentage value result associated with 
* how well the student did in this component. 
*/
struct Component{
    char *name;
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
    char *name;
    struct ComponentList *head;
    struct ComponentList *tail;
}; 

/**
* A linked list of courses.
*/
struct CourseList{
    struct Course course;
    struct CourseList *next;
};

/**
* A profile is simply contains a pointer to the start and end of
* a course list.
*/
struct Profile{
    struct CourseList *head;
    struct CourseList *tail;
};

typedef struct Component Component;
typedef struct ComponentList ComponentList;
typedef struct Course Course;
typedef struct CourseList CourseList;
typedef struct Profile Profile;

/***
* Frees the profile. Wrapper around free_course_list.
*/
void free_profile(Profile *profile);

/**
* Frees the course list. Wrapper around free_component_list.
*/
void free_course_list(CourseList *courselist);

/**
* Frees the allocated memory for a ComponentList.
*/
void free_component_list(ComponentList *components);

/** 
* Instantiates a new CourseList node.
*/
CourseList *new_course_list();

/**
* Instantiates a new ComponentList node.
*/
ComponentList *new_component_list();

#endif