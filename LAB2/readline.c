#include "readline.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int read_line(char *str){
	char tmp;
	int i = 0;
	int result = 1;
	while(1){
		tmp = getchar();
		if(tmp == '\n' || tmp == EOF)
			break;
		if(!isdigit(tmp))
			result = 0;
		str[i] = tmp;
		i++;
	}
	str[i] = '\0';
	return result;
}
