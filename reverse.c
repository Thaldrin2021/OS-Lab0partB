#include <stdio.h>
#include <stdlib.h>
#define FILE_ERROR "--> ERROR: File couldn't be opened"

int getNumLines(char *);

int main(int argc, char *argv[]) {
	int numLines = getNumLines(argv[1]);
	printf( "Number of Lines = %d\n", numLines );
	return EXIT_SUCCESS;
}

int getNumLines(char *fileName) {
	FILE *file = fopen(fileName, "r");
	if (file == NULL) {
		printf( "%s\n", FILE_ERROR );
		exit(1);
	} else {
		char *line = NULL;
		size_t lineSize = 0;
		ssize_t length;
		int count = 0;
		length = getline(&line, &lineSize, file);
		while (length >= 0) {
			length = getline(&line, &lineSize, file);
			count++;
		} fclose(file);
		return count;
	}
}
