#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define FILENAME_LENGTH 260

int main(int argc, char **argv) {
	//intialize file and filename array
	FILE *fp;
	char filename[FILENAME_LENGTH];
	char prev;
	int lines = 0;
	int words = 0;
	long int characters = 0;
	long int bytes = 0;
	//initialize array of bools for flags
	bool flags[4] = {false};
	if(argc == 1) {
		flags[0] = true;
		flags[1] = true;
		flags[2] = true;		
		//open file, return error message if not possible
		fp = stdin;
	}	
	else if(argc == 2) {
		//Set flags to be -c, -l, -w, set filename to argv[1]
		flags[0] = true;
		flags[1] = true;
		flags[2] = true;
		strcpy(filename, argv[1]);
		//open file, return error message if not possible
		fp = fopen(filename, "r");
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
					case 'h':
						printf("usetheWC: Windows word counter. Usage: usetheWC [FILENAME]. Command flags include -c for byte counting, -l for line counting, -w for word counting, -m for character counting, and -h to repeat this message.");
						return 0;
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

		//open file, return error message if not possible
		fp = fopen(filename, "r");
	}
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
				if(c == ' ' && prev != ' ')
					words++;
				characters++;
				//get next character in file
				prev = c;
				c = fgetc(fp);	
			}
		}
		if(flags[1]) {
			printf("%d      ", lines);
		}
		if(flags[2]) {
			printf("%d      ", words);
		}
		if(flags[3]) {
			printf("%ld      ", characters);
		}
		printf("%s\n", filename);
		fclose(fp);
	}
	return 0;
}
