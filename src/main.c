#include <stdlib.h>
#include <stdio.h>

/**
* Reads the content of the file line by line, each line. Each 
* line will be parsed separately by the parser.
*/ 
void parse_file(char *file_path){
    
    FILE *file = fopen(file_path, "r");
    if(file == NULL){
        printf("Error: Cannot read file.\n");
        exit(EXIT_FAILURE);
    }
    
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    while((read = getline(&line, &len, file)) != -1){
        printf("%s", line);
    }
    free(line);
    return;
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
    parse_file(file_path);
    
    return 0;
}