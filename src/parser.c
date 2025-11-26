#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include "parser.h"
#include <assert.h>
#include "structures.h"

/**
* Adds a course into the profile. 
*/
void add_course(char *name, Profile *profile){
    
    CourseList *newlist = new_course_list();
    newlist->course.name = name;
    
    //NULL case:
    if(profile->tail == NULL){
        profile->head = newlist;
        profile->tail = newlist;
        return;
    }
    
    //Usual Case 
    profile->tail->next = newlist;
    profile->tail = newlist;
}

/**
* Given a string, removes surrounding whitespaces.
* @return whether the string contains atleast 1 non-whitespace character. This
*         function returns 0 if and only if the resulting string is set to the empty string. 
*/
int strip(char *s){
    int i = 0, j = 0;
    
    //Check for empty string
    if(s[0] == '\0') return 0;
    
    while (isspace(s[i])){
        i++;
        if(s[i] == '\0'){ //Blank string detected
            s[0] = '\0';
            return 0;
        }
    }
    while ((s[j++] = s[i++]));
    j -= 2;
  	while(s[j] == ' ') j--;
  	j++;
  	s[j] = '\0';
    return 1;
}

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
float parse_float(const char *s, float default_denom){ //TODO add rounding for precision errors.
    size_t len = strlen(s);
    char buf[len+1];
    strncpy(buf, s, len);
    buf[len] = '\0';
    char *endptr;
    float val;
    
    if(buf[len-1] == '%'){
        buf[len-1] = '\0';
        val = strtof(buf, &endptr);
        if(*endptr != '\0'){
            return -1;
        }
        float res = val / 100;
        if(res < 0 || res > 1){
            return -1;
        }
        return res;
    }
    
    //Try to parse as a single long
    val = strtof(buf, &endptr);
    
    if(*endptr == '\0'){ //Succeeds
        float res = val / default_denom;
        if(res < 0 || res > 1){
            return -1;
        }
        return res;
    }
    
    //Fraction
    if(*endptr == '/'){
        int i = 0;
        while(buf[i] != '/') i++;
        buf[i] = '\0';
        char *denom_str = &buf[i+1];
        val = strtof(buf, &endptr);
        if(*endptr != '\0'){
            return -1;      //Invalid numerator
        }
        float denom = strtof(denom_str, &endptr);
        if(*endptr != '\0'){    
            return -1;      //Invalid denominator
        }
        if(denom == 0){
            return -1;      //Division by 0
        }
        float res = val / denom;
        if(res < 0 || res > 1){
            return -1;      //out of bounds
        }
        return res;
    }
    
    return -1; //Invalid format
    
}

/**
* Parses a single string representing a component of a course. 
* @param component the string representing the component.
* @param clen the length of the component string excluding the null byte.
* @param profile current profile under construction.
* @return -1 on failure or 0 on success.
*/
int parse_component(char *component, int len, Profile *profile){
    char *saveptr = component;
    char sep[4] = ",";
    
    //Component name parsing
    char *token = strtok_r(saveptr, sep, &saveptr);
    
    if(token == NULL){
        printf("Error: Cannot parse the following component: \"%s\". Component name not found.\n", component);
        exit(1);
    }
    
    if(!strip(token)){
        printf("Error: Cannot parse the following component: \"%s\". Component name is blank.\n", component);
        exit(1);
    }
    
    ComponentList *node = new_component_list();
    const size_t namelen = strlen(token);
    char *name = malloc(namelen + 1);
    strncpy(name, token, namelen);
    name[namelen] = '\0';
    node->component.name = name;
    
    token = strtok_r(saveptr, sep, &saveptr); // Next argument, total weighting. 
    
    if(token == NULL){
        printf("Error: Cannot parse the following component: \"%s\". Component weighting not found.\n", component);
        exit(1);
    }
    
    if(!strip(token)){
        printf("Error: Cannot parse the following component: \"%s\". Component weighting is blank.\n", component);
        exit(1);
    }
    
    float weighting = parse_float(token, 100);
    if(weighting < 0){
        printf("Error: Cannot parse the following component: \"%s\". Weighting \"%s\" cannot be parsed into float.\n", component, token);
        exit(1);
    }
    
    node->component.weight = weighting;
    
    token = strtok_r(saveptr, sep, &saveptr); // Next argument, current result
    
    if(token == NULL){ //no results available
        node->component.result = -1;
    }else if(!strip(token)){
        printf("Error: Cannot parse the following component: \"%s\". Component result is blank.\n", component);
        exit(1);
    }else{
        float result = parse_float(token, weighting * 100);
        if(result < 0){
            printf("Error: Cannot parse the following component: \"%s\". Result \"%s\" cannot be parsed into float.\n", component, token);
            exit(1);
        }
        node->component.result = result;
    }
    
    Course *course = &profile->tail->course;
    
    if(course->tail == NULL){
        course->head = node;
        course->tail = node;
    }else{
        course->tail->next = node;
        course->tail = node;
    }
    return 0;
}


int parse_line(const char *line, Profile *profile){
    int len = (int) strlen(line);
    int i = 0;
    int j = len-1;
    
    while(isspace(*(line+i))){
        if(i == len-1){
            //All whitespace, do nothing.
            return 0;
        }
        i++;
    }
    
    while(isspace(*(line+j)) && j >= 0){
        j--;
    }
    
    assert(j >= i);
    
    //Ends with a colon, add course
    if(*(line+j) == ':'){
        //Copies the name
        int namelen = j-i;
        char *name = malloc((unsigned) namelen+1);
        if(name == NULL){
            printf("Error: Cannot allocate memory\n");
            exit(1);
        }
        memcpy(name, line+i, (unsigned) namelen);
        *(name+namelen) = '\0';
        add_course(name, profile);
        return 0;
    }
    
    //At this point, we safely assume the string represents a component. 
    int clen = j+1-i;
    char component[clen+1];
    memcpy(component, line+i, (unsigned) clen);
    component[clen] = '\0';
    
    return parse_component(component, clen, profile);
    
}

void verify(Profile *profile){
    CourseList *csl = profile->head;
    while(csl){
        ComponentList *cpl = csl->course.head;
        float weightCumulative = 0;
        while(cpl){
            weightCumulative += cpl->component.weight;
            cpl = cpl->next;
        }
        
        if(weightCumulative != 1){
            printf("Error: Weights of components under \"%s\" does not add up to 100%%.\n", csl->course.name);
            exit(1);
        }
        csl = csl->next;
    }
}