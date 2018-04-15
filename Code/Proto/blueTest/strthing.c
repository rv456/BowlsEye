#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>


int main(int argc, char** argv){

	char str[10] = "888,100,51";

	char *token = strtok(str, ",");

	while(token != NULL){

		printf("%i\n", atoi(token));
		token = strtok(NULL, ",");

	}

	

}
