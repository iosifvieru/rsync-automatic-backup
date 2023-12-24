#include "Header.h"

extern int optind;
extern char* optarg;

int interrupted = 0;

int main(int argc, char* argv[]){
    int opt, time = 10, err;
    char* ip, *user, *source, *destination;

    // signal handler
    signal(SIGINT, handle_interrupt);

    while((opt = getopt(argc, argv, "s:t:")) != -1){
        switch(opt){
            case 't':
                time = atoi(optarg);
                break;
            case 's':
                source = createArray(strlen(optarg));
                strncpy(source, optarg, strlen(optarg));
                break;
            default:
                usage_error(argc, argv);
                break;
        }
    }

    if(optind == 1){
        usage_error(argc, argv);
        //time = 1;
    }

    err = readConfig("config", &source, &destination, &user, &ip);
    if(err != 0){
        fprintf(stderr, "Config file error.\n");
        exit(EXIT_FAILURE);
    }

    //printf("%s, %s, %s, %s", user, ip, source, destination);

    // rsync command
    char rsyncCommand[100*2];
    snprintf(rsyncCommand, sizeof(rsyncCommand), "rsync -avz -e ssh %s/ %s@%s:%s", source, user, ip, destination);

    printf("%s\n", rsyncCommand);
    while(!interrupted){
        err = system(rsyncCommand);

        sleep(time*60);
    }


    free(source);
    free(destination);
    free(user);
    free(ip);
    return 0;
}       