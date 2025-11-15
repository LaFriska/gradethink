#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>

int init_directories(){
    char *home = getenv("HOME");
    char path[128];
    strncpy(path, home, 128);
    strlcat(path, "/.config", 128);
    if(mkdir(path, 0700) != -1){
        printf("%s\n", "Creating .config subdirectory.");
    }
}


int main(int argc, char **argv) {


    if(argc < 3) {
        printf("%s\n", "Error: Too few arguments.");
        return 1;
    }

    char *command = argv[1];

    //Add a course
    if(strcmp(command, "add") == 0){
        //TODO
    }

    //Remove a course 
    else if(strcmp(command, "delete") == 0){
        //TODO
    }

    //Displays the status
    else if(strcmp(command, "status") == 0){

    }

    return 0;

}