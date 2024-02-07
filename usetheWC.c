#include <stdio.h>
#include <stdbool.h>
#include <string.h>

int main(int argc, char **argv) {
	//intialize file and filename array
	FILE *fp;
	//NOTE: find some way to improve this rather than fixed size of 100.
	//Perhaps initialize it when the argv is found?
	char filename[100];
	//initialize array of bools for flags
	bool flags[4] = {false};
	if(argc == 1) {
		//Allow for standard input later, for now just return 0
		printf("Invalid syntax.\n");
		printf("Correct syntax: usetheWC [flags] [filename].");
		return 1;
	}	
	if(argc == 2) {
		//Set flags to be -c, -l, -w, set filename to argv[1]
		flags[0] = true;
		flags[1] = true;
		flags[2] = true;
		strcpy(filename, argv[1]);
	}
	else {
		for(int i=1; i<argc; i++) { 
			if(argv[i][0] == '-') {
				//turn flags into boolean values, and display error message if unidentified
				switch(argv[i][1]) {
					case 'c':
						flags[0] = true;
						break;
					case 'l':
						flags[1] = true;
						break;
					case 'w':
						flags[2] = true;
						break;
					case 'm':
						flags[3] = true;
						break;
					default:
						printf("The flag -%c is unidentified.\n", argv[i][1]);
						break;
				}
			}
			else {
				//set filename to the flag used
				strcpy(filename, argv[i]);
			}
		}
	}
	//open file, return error message if not possible
	fp = fopen(filename, "r");
	if(fp == NULL) {
		printf("usetheWC: cannot open %s\n", filename);
		return 2;
	}
	else {
		//flag 1: get byte count of file.
		if(flags[0] == true){
			//seek to end of file, and get position in bytes
			//ERROR: bytes displays as blank number when used. No compiler errors,
			//and the spaces and filename display work fine. Remedy ASAP.
			fseek(fp, 0, SEEK_END);
			long int bytes = ftell(fp);
			//display and reset position
			printf("%l      ", bytes);
			fseek(fp, 0, SEEK_SET);
		}
		printf("%s\n", filename);
		fclose(fp);
	}
	return 0;
}
