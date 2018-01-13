/*
 * Filename: 1_ebpcorruption.c
 * Author: @charlieMKR, https://makemyday.io
 *
 * The goal of this code is to ilustrate how %ebp can be overwritten through buffer overflow.
 *
 * Compile with: gcc -O0 -m32 -fno-stack-protector -ggdb -o ebpcorruption.o 1_ebpcorruption.c
 *
 * This code is part of the Memory Attacks repository at https://github.com/charlieMKR/memory-attacks
 */

#include <stdio.h>
#include <string.h>

void corruptableFunc(char *charArray) {
	char overflowable[10]; // buffer that will be overflowed
	strcpy(overflowable, charArray); // %ebp corruption
	printf("Stored value: %s\n", overflowable);
	// return and CRASH!
}

int main(){
	char *corruptorArray = "AAAAAAAAAAAAAAAAAAroc"; // will overwrite %ebp with 0x00636f72 (cor)
	// printf("Enter a string: "); // uncomment these for interactive mode
	// gets(corruptorArray);
	corruptableFunc(corruptorArray);
	printf("Exiting!");
	return 0;
}

