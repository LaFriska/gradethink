#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "parser.h"
#include "display.h"

/**
* Reads the content of the file line by line, each line. Each 
* line will be parsed separately by the parser.
*/ 
Profile *parse_file(char *file_path){
    
    FILE *file = fopen(file_path, "r");
    if(file == NULL){
        printf("Error: Cannot read file.\n");
        exit(EXIT_FAILURE);
    }
    
    Profile *profile = malloc(sizeof(Profile));
    profile->head = NULL;
    profile->tail = NULL;
    
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    while((read = getline(&line, &len, file)) != -1){
        parse_line(line, profile);
    }
    free(line);
    return profile;
}

/**
* Main routine.
*/
int main(int argc, char *argv[]){
    
    if(argc < 2){
        printf("Error: Too few arguments.\n");
        exit(EXIT_FAILURE);
    }
    
    char *file_path = argv[1];
    Profile *profile = parse_file(file_path);
    
    float aim = 0.8F;
    
    //parses the syntax ./gradethink [file] -a [percentage]
    if(argc > 2){
        if(strcmp(argv[2], "-a") == 0){
            
            if(argc < 4){
                DASH_A_ERROR:
                    printf("-a flag must be followed by a number, percentage, or fraction.\n");
                    exit(EXIT_FAILURE);
            }
            
            float newaim = parse_float(argv[3], 100);
            if(newaim < 0) goto DASH_A_ERROR;
            
            aim = newaim;
        }
    }
    
    verify(profile);
    render(profile, aim);
    
    free_profile(profile);
    return 0;
}