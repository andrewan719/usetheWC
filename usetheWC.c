#include <stdio.h>
#include <stdbool.h>

int main(int argc, char** argv){
	int i;
	//set array of bools for flags
	bool flags[4] = false;
	for(i=0; i<argc; i++){
		//set file to char * filename for access
		//4 flags: -c (bytes), -w (words), -l (lines), -m (characters)
		//put flags in a data structure for usage
		//Edge case: 0 flags, set -c, -l, -w	
	}
	fp = fopen(filename);
	if(flags[0] == true){
		cout << sizeof(filename);
	}
	cout << filename << endl;
	fclose(fp);
	return 0;
}
