#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#define PROCESSES 3

int countDivisible (char a[100][79], int n, int num){
    int result = 0;
    for(int i=0; i<n; i++){
        if (num == 5)
            if (a[i][strlen(a[i])-2] == '5' || a[i][strlen(a[i])-2] == '0')
                result++;
        
        if (num == 2)
            if (a[i][strlen(a[i])-2] == '0' || a[i][strlen(a[i])-2] == '2' || a[i][strlen(a[i])-2] == '4' || a[i][strlen(a[i])-2] == '6' || a[i][strlen(a[i])-2] == '8')
                result++;
        
        if (num == 3){
            int sumOfDigit = 0;
            for (int j=0; j< strlen(a[i]); j++)
                sumOfDigit += a[i][j] + '0';
            if (sumOfDigit % 3 == 0)
                result++;
        }
    }
    return result;
}

int main() {
    char data[100][79];
    int divisibleBy[3] = {2,3,5};
    char str[79] ;
    FILE *fp;
    char* filename = "number.txt";
    fp = fopen(filename, "r");
    int line = 0;
    while (fgets(str, 79, fp) != NULL){
        for(int i=0; i<79; i++)
            data[line][i] = str[i];
        line++;
    }
    fclose(fp);
    
    pid_t pid;
    for (int i = 0; i < 3; i++){
        pid = fork();
        if (pid < 0){
            printf("[!] Error\n");
            exit(1);
        }
        else if (pid == 0) {
            printf("%d\n", countDivisible(data, line, divisibleBy[i]));
            exit(0);
        }
    }
    
    for (int j = 0; j < 3; j++)
        wait(0);
    return 0;
}

