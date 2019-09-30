#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "readline.h"
#include "factorial.h"

int main (){
	char str[51];
	while(1){
		if (read_line(str))
			if (strlen(str) > 0)
				printf("%s\n",factorial(atoi(str)));
            else
                break;
		else
			puts("-1");
	}
	return 0;
}
