#include "Header.h"

#define MAX_LINE_LENGTH 100
#define CONFIG_FILE_ARGS 2

extern int interrupted;

void usage_error(int argc, char* argv[]){
    fprintf(stderr, "Usage: %s [-t <minutes>]\n", argv[0]);
    exit(EXIT_FAILURE);
}

int readConfig(const char *fileName, char** source, char** destination, char** user, char** ip){
    FILE * configFile = fopen(fileName, "r");

    if(configFile == NULL){
        perror("Error: Path to the file may be wrong, or file doesn't exist.");
        return 1;
    }

    char line[MAX_LINE_LENGTH];
    // OPEN THE FILE AND READ DATA LINE BY LINE.
    while(fgets(line, sizeof(line), configFile) != NULL){
        if(line[0] == '#' || line[0] == '\n'){
            //printf("Detected comment or clrf\n");
            continue;
        }

        char arg[MAX_LINE_LENGTH], value[MAX_LINE_LENGTH];
        //printf("%d", sscanf(line, "%99[^=]=%99s", arg, value));
        /*
            The args from config file are formatted this way:
            ARG=VALUE
        */
        if(sscanf(line, "%99[^=]=%99s", arg, value) == CONFIG_FILE_ARGS){
            /* 
                ARGS
            */
            if(strcmp(arg, "USER") == 0){
                //printf("%s \n", value);
                *user = createArray(strlen(value));
                strncpy(*user, value, strlen(value));
            }
            if(strcmp(arg, "IP") == 0){
                //printf("%s \n", value);
                *ip = createArray(strlen(value));
                strncpy(*ip, value, strlen(value));
            }
            if(strcmp(arg, "SOURCE") == 0){
                //printf("%s \n", value);
                *source = createArray(strlen(value));
                strncpy(*source, value, strlen(value));
            }
            if(strcmp(arg, "DESTINATION") == 0){
                //printf("%s \n", value);
                *destination = createArray(strlen(value));
                strncpy(*destination, value, strlen(value));
            }
        }

    }
    return 0;
}

char* createArray(int __size){
    return (char*) malloc(__size * sizeof(char));
}

void handle_interrupt(int signo){
    if(signo == SIGINT){
        printf("CTRL + C\n");
        interrupted = 1;
    }
}