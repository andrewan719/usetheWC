#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define FILENAME_LENGTH 260

//INTENDED BEHAVIOR WITH TEST.TXT: 71 lines, 2269 bytes, 430 words, 2127 characters
int main(int argc, char **argv) {
	//intialize file and filename array
	FILE *fp;
	char filename[FILENAME_LENGTH];
	int lines = 0;
	int words = 0;
	long int characters = 0;
	long int bytes = 0;
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
		if(flags[0]) {
			//seek to end of file, and get position in bytes
			fseek(fp, 0L, SEEK_END);
			bytes = ftell(fp);
			//display and reset position
			printf("%ld      ", bytes);
			fseek(fp, 0L, SEEK_SET);
		}
		//main loop: used for words, lines, characters
		if(flags[1] || flags[2] || flags[3]) {
			//get first character in file
			char c = fgetc(fp);
			while(c != EOF) {
				if(c == '\n') 
					lines++;
				//get next character in file
				c = fgetc(fp);	
			}
		}
		if(flags[1]) {
			//ERROR: Lines read outputs as zero. After looking at the compiler logs, seems like
			//buffer[i] is an int, for whatever reason.
			//UPDATE: thought I'd fixed it, but I just caused an infinite loop. Ouch. Fix ASAP.
			printf("%d      ", lines);
		}
		printf("%s\n", filename);
		fclose(fp);
	}
	return 0;
}
