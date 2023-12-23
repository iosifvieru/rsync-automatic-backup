#include "Header.h"

extern int optind;
extern char* optarg;

int interrupted = 0;

int main(int argc, char* argv[]){
    int opt, time, err;
    char* ip, *user, *source, *destination;

    // signal handler
    signal(SIGINT, handle_interrupt);

    while((opt = getopt(argc, argv, "t:")) != -1){
        switch(opt){
            case 't':
                time = atoi(optarg);
                //printf("TIME: %d\n", time);
                break;
            default:
                usage_error(argc, argv);
        }
    }

    if(optind == 1){
        usage_error(argc, argv);
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