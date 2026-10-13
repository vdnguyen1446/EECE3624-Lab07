/***************************************************************************
 * Lab07.c (barebones starter code version)
 *
 *   Created: 10/13/2026
 *    Author:
 * Processor: ATmega128A (on a ReadyAVR)
 *
 * Your comments go here...
 *
 **************************************************************************/

/* your #include file declaration(s) go here */
#include "UARTLibrary.h"
#include <string.h>

/* your #define declarations go here */
#define BaudRate 9600
#define DataBits 8
#define StopBits 1
#define NoParity 0

// prototype subroutine definitions
void initializeArray(unsigned char *cp);
void displayArray(unsigned char *cp);
void updateArray(unsigned char *cp);

int main(void)
{
	// create a 61-char array
	unsigned char Cells[61];
	initializeArray(Cells);

	// Initialize the UART
	// ProfNote:  Understand the UARTLibary.h before blindly running the next line!
	uart_init(BaudRate, DataBits, StopBits, NoParity);
	
	// ProfNote:  Initial Testing Only!  Comment out after UART confirmed working!
	/*while (1) {
		uart_tx('H');uart_tx('e');uart_tx('l');uart_tx('l');uart_tx('o');uart_tx('\r');uart_tx('\n');
		uart_tx('W');uart_tx('o');uart_tx('r');uart_tx('l');uart_tx('d');uart_tx('!');uart_tx('\r');uart_tx('\n');
	}*/
	
    /* your code goes here */
	for(int i = 0; i < 122; i++){
		displayArray(Cells);
		updateArray(Cells);
	}
	
}

/* your subroutines go here */
void initializeArray(unsigned char *cp){
	unsigned char initial[61] = "                              *                              ";
	memcpy(cp, initial, 61);
}
void displayArray(unsigned char *cp){
	// ProfNote:  Look through your line using "uart_tx(<char>)" to print one character at a time.
	// At the end of the line, use "uart_tx('\r'); uart_tx('\n');" to print a new line to keep your
	// output aligned properly.
	int i = 0;
	int j = 0;
	
	while(*cp){
		uart_tx(cp[j]);
		if(i == 7){
			uart_tx('\r'); uart_tx('\n');
		}
		i++;
		j++;
		cp++;
		
	}
	
}
void updateArray(unsigned char *cp){
	unsigned char next[61];
	next[0] = ' ';
	next[61] = ' ';
	
	for(int i = 1; i < 61; i++){
		unsigned char left = cp[i-1];
		unsigned char center = cp[i];
		unsigned char right	= cp[i+1];
		
		// Rule 26 Logic
		next[i] = ' ';
		// Black and Neighbors Black = white
		if(center == '*' && left == '*' && right == '*' ){
			next[i] = ' ';
		}
		// Black, Left Black, Right White = white
		else if(center == '*' && left == '*' && right == ' ' ){
			next[i] = ' ';
		}
		// White and Neighbors Black = White
		else if(center == ' ' && left == '*' && right == '*' ){
			next[i] = ' ';
		}
		// White, Left Black, Right White = Black
		else if(center == ' ' && left == '*' && right == ' '){
			next[i] = '*';
		}
		// Black, Left White, Right Black = Black
		else if(center == '*' && left == ' ' && right == ' ' ){
			next[i] = '*';
		}
		// Black and Neighbors White = White
		else if(center == '*' && left == ' ' && right == ' ' ){
			next[i] = ' ';
		}
		// White, Left White, Right Black = Black
		else if(center == ' ' && left == ' ' && right == ' '){
			next[i] = '*';
		}
		// White and Neighbors White = White
		else if(center == ' ' && left == ' ' && right == ' '){
			next[i] = ' ';
		}
		
		memcpy(cp, next, 61);
	}
}
