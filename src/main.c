#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include <dirent.h>
#include <errno.h>

#define MAXDIRLEN 256

/**
 * Initialises the directories,
 * @return a pointer to a string representing the path of the newly created directory, or NULL on fail.
 */
char *init_directories(){
    char *home = getenv("HOME");
    char *path = malloc(MAXDIRLEN);
    strncpy(path, home, MAXDIRLEN);
    strlcat(path, "/.config", MAXDIRLEN);

    DIR *config = opendir(path);
    if(config == NULL){
        if(errno == ENOENT){
            printf("%s\n", "Error: Directory .config does not exist in your home directory. Please create this directory first.");
        }else{
            printf("%s\n", "Error: Failed to open .config directory, make sure your permission bits are properly set.");
        }
        free(path);
        return NULL;
    }
    closedir(config);

    strlcat(path, "/gradethink", MAXDIRLEN);

    int mkdirres = mkdir(path, 0700);
    if(mkdirres == -1){
        if(errno != EEXIST){
            printf("%s\n", "Failed to initialise subdirectory for gradethink in ~/.config. Make sure the permission bits are properly set.");
            free(path);
            return NULL;
        }
    }else{
        printf("%s\n", "Creating subdirectory for gradethink in ~/.config.");
    }

    return path;
}


int main(int argc, char **argv) {


    if(argc < 3) {
        printf("%s\n", "Error: Too few arguments.");
        return 1;
    }

    char *path = init_directories();

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

    free(path);
    return 0;

}