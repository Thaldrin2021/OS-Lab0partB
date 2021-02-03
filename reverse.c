// Programmer:			Zachary William Preston
// Date:			2021 February 2
// Course:			Into to Operating Systems
// Description:			program will enter in the lines of a file backwards, then
//				will either print to terminal screen or will write to a
//				output file and save onto the terminal

// Preprocessor Directives
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define FILE_ERROR "--> ERROR: File couldn't be opened"
#define CMD_ERROR "--> ERROR: Too few arguments ./reverse <input> <output>"
#define SAME_ERROR "--> ERROR: Input and Output cannot be the same"
#define MAX_ERROR "--> ERROR: Too many arguments ./reverse <input> <output>"
#define TEST_IN "test.txt"
#define TEST_OUT "test2.txt"

// Function Prototypes
int getNumLines(char *);
int getMaxLineSize(char *);
void oneArgument(char *);
void twoArguments(char *, char *);

// main() - If there is only one argument, CMD error, and then exit
//	    If there are two arguments, then print to screen in reverse
//	    If there are 3 arguments, check if in and out are the same
//		If they are the same, print error and exit program
//		If they are different, write reverse to the out file
//	    If there are more than 3 arguments, print error and exit program
int main(int argc, char *argv[]) {
	if (argc == 1) {
		printf( "%s\n", CMD_ERROR );
	} else if (argc == 2) {
		oneArgument(argv[1]);
	} else if (argc == 3) {
		if (strcmp(argv[1], argv[2]) == 0) {
			printf( "%s\n", SAME_ERROR );
			exit(1);
		} else {
			twoArguments(argv[1], argv[2]);
		}
	} else {
		printf( "%s\n", MAX_ERROR );
		exit(1);
	}
	return EXIT_SUCCESS;
}

// getNumLines - This function will get the number of lines that are in
//		 the file, it gets each line and then increments by 1,
//		 finally closing the file and returning the number as an
//		 integer value
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

// getMaxLineSize() - this function will get the size of the longest line, and will
//		      be used to allocate the right amount of space, without reallocating.
//		      This uses a counter, i and every time a new line is entered, the counter
//		      will continue until the end of the line is discovered, if that is
//		      the max line, then max will be given that value, and will remain that
//		      value until a new max is found or until the end of the file '\0' is encountered
int getMaxLineSize(char *fileName) {
	FILE *file = fopen(fileName, "r" );
	if (file == NULL) {
		printf( "%s\n", FILE_ERROR );
		exit(1);
	} else {
		char *line = NULL;
		size_t lineSize = 0;
		ssize_t length;
		int max = 0;
		int i = 0;
		length = getline(&line, &lineSize, file);
		while (line[i] != '\0')
			i++;
		max = i;
		while (length >= 0) {
			length = getline(&line, &lineSize, file);
			i = 0;
			while (line[i] != '\0')
				i++;
			if (i > max)
				max = i;
		} fclose(file);
		return max;
	}
}

// oneArgument() - If one file, "the input file", is input on the terminal, then it will print
//		   the file contents backwards to the terminal menu. It uses the getNumLines() and
//		   the getMaxLineSize() functions to allocate the right amount of memory, when
//		   initializing the array. Finally, once all the content is gathered, uses a for loop
//		   with a decrement to print the array backwards to the screen, hence "reverse"
void oneArgument(char *fileName) {
	int numLines = getNumLines(fileName);
	int maxLine = getMaxLineSize(fileName);
	char fileLines[numLines][maxLine + 1];
	FILE *file = fopen(fileName, "r");
	if (file == NULL) {
		printf( "%s\n", FILE_ERROR );
		exit(1);
	} else {
		char *line = NULL;
		size_t lineSize = 0;
		ssize_t length;
		int current = 0;
		length = getline(&line, &lineSize, file);
		strcpy(fileLines[current], line);
		current++;
		while (length >= 0) {
			length = getline(&line, &lineSize, file);
			strcpy(fileLines[current], line);
			current++;
		} fclose(file);
		for (int i = numLines - 1; i >= 0; i--)
			printf( "%s", fileLines[i] );
	}
}

// twoArguments() - if the user enters in two arguments into the terminal, an input file,
// 		    and an output file, then will do the same as the oneArgument() function,
//		    however this time will write to a file instead of printing to terminal,
//		    using the same procedure as the previous function.
void twoArguments(char *input, char *output) {
	int numLines = getNumLines(input);
	int maxLine = getMaxLineSize(input);
	char fileLines[numLines][maxLine + 1];
	FILE *file = fopen(input, "r");
	if (file == NULL) {
		printf( "%s\n", FILE_ERROR );
		exit(1);
	} else {
		char *line = NULL;
		size_t lineSize = 0;
		ssize_t length;
		int current = 0;
		length = getline(&line, &lineSize, file);
		strcpy(fileLines[current], line);
		current++;
		while (length >= 0) {
			length = getline(&line, &lineSize, file);
			strcpy(fileLines[current], line);
			current++;
		} fclose(file);
	} file = fopen(output, "w");
	if (file == NULL) {
		printf( "%s\n", FILE_ERROR );
		exit(1);
	} else {
		for (int i = numLines - 1; i >= 0; i--)
			fprintf(file, "%s", fileLines[i]);
		fclose(file);
	}
}
