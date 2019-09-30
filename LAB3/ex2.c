pp#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void function(char* argv, char* c){
    strcpy(argv,c);
    int i = 0;
    while(1)
        i++;
}

void error(){
    printf("Error");
    exit(1);
}

int main(int argc, char** argv){
    pid_t pid = fork();
    if (pid < 0)
        error();
    else if (pid == 0){ //inside B
        pid_t pid2 = fork();
        if (pid2 < 0)
            error();
        else if (pid2 == 0) // inside E
            function(argv[0],"E");
        else {  // inside B
            pid_t pid3 = fork();
            if (pid3 < 0)
                error();
            else if (pid3 == 0)
                function(argv[0],"F");
            else
                function(argv[0],"B");
        }
    }
    else { // inside A
        pid_t pid2 = fork();
        if (pid2 < 0)
            error();
        else if (pid2 == 0) { // inside C
            pid_t pid3 = fork();
            if (pid3 < 0)
                error();
            else if (pid3 == 0) { // inside G
                pid_t pid4 = fork();
                if (pid4 < 0)
                    error();
                else if (pid4 == 0) // inside I
                    function(argv[0],"I");
                else
                    function(argv[0],"G");
            }
            else
                function(argv[0],"C");
        }
        else {
            pid_t pid4 = fork();
            if (pid4 < 0)
                error();
            else if (pid4 == 0) // inside D
                function(argv[0],"D");
            else
                function(argv[0],"A");
        }
    }
}



