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
#define size 61
int Rule;
char c;

// prototype subroutine definitions
void initializeArray(unsigned char *cp);
void displayArray(unsigned char *cp);
void updateArray(unsigned char *cp);
void WelcomeArray();

int main(void)
{
	// create a 61-char array
	unsigned char Cells[size];
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
	while(1){
		initializeArray(Cells);
		WelcomeArray();
		c = NULL;
		while(c == NULL){
			c = uart_rx();
		}
		
		if(c == 'A' || c == 'a')
			Rule = 26;
		else if(c == 'B' || c == 'b')
			Rule = 105;
		else if(c == 'C' || c == 'c')
			Rule = 45;
		else
			Rule = 0;
		if(Rule != 0){
			for(int i = 0; i < 122; i++){
				displayArray(Cells);
				updateArray(Cells);
			}
		}
	}
}

/* your subroutines go here */
void initializeArray(unsigned char *cp){
	unsigned char initial[61] = "                              *                              ";
	memcpy(cp, initial, size);
}
void displayArray(unsigned char *cp){
	// ProfNote:  Look through your line using "uart_tx(<char>)" to print one character at a time.
	// At the end of the line, use "uart_tx('\r'); uart_tx('\n');" to print a new line to keep your
	// output aligned properly.

	
	while(*cp){
		uart_tx(*cp);
		cp++;
		
	}
	uart_tx('\r');
	uart_tx('\n');
	
	
}


void WelcomeArray(){
	unsigned char line[61];
	for(int i = 0; i < 10; i++){
		if(i == 1 || i == 9){
			memcpy(line, "------------------------------------------------------------",61 );
			displayArray(line);
		}
		if(i == 3){
			memcpy(line, "Pick A Rule Set:                              ",61 );
			displayArray(line);
			memcpy(line, "          A = 26          B = 105         C = 45         ",61);
			displayArray(line);
		}
		if(i == 5){
			memcpy(line, "   A = Rule 26     ",61);
			displayArray(line);
			memcpy(line, "   ***|**_|*_*|**_|_**|_*_|__*|___",61);
			displayArray(line);
			memcpy(line,"                                                             ",61);
			displayArray(line);
			memcpy(line, "    _ | _ | * | _ | * | * | _ | * ",61);
			displayArray(line);
		}
		if(i == 6){
			memcpy(line, "   B = Rule 105     ",61);
			displayArray(line);
			memcpy(line, "   ***|**_|*_*|**_|_**|_*_|__*|___",61);
			displayArray(line);
			memcpy(line,"                                                             ",61);
			displayArray(line);
			memcpy(line, "    _ | * | * | _ | * | _ | _ | * ",61);
			displayArray(line);
		}
		if(i == 7){
			memcpy(line, "   C = Rule 45     ",61);
			displayArray(line);
			memcpy(line, "   ***|**_|*_*|**_|_**|_*_|__*|___",61);
			displayArray(line);
			memcpy(line,"                                                             ",61);
			displayArray(line);
			memcpy(line, "    _ | _ | * | _ | * | * | _ | * ",61);
			displayArray(line);
		}
		else{
			memcpy(line,"                                                             ",61);
			displayArray(line);
		}
	}
}


void updateArray(unsigned char *cp){
	unsigned char next[size];
	next[0] = ' ';
	next[size] = ' ';

	
	for(int i = 1; i < 61; i++){
		unsigned char left = cp[i-1];
		unsigned char center = cp[i];
		unsigned char right	= cp[i+1];
		// Rule 26 Logic
		if(Rule == 26){
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
			else if(center == '*' && left == ' ' && right == '*' ){
				next[i] = '*';
			}
			// Black and Neighbors White = White
			else if(center == '*' && left == ' ' && right == ' ' ){
				next[i] = ' ';
			}
			// White, Left White, Right Black = Black
			else if(center == ' ' && left == ' ' && right == '*'){
				next[i] = '*';
			}
			// White and Neighbors White = White
			else if(center == ' ' && left == ' ' && right == ' '){
				next[i] = ' ';
			}
		}
		if(Rule == 105){
			next[i] = ' ';
			// Black and Neighbors Black = white
			if(center == '*' && left == '*' && right == '*' ){
				next[i] = ' ';
			}
			// Black, Left Black, Right White = black
			else if(center == '*' && left == '*' && right == ' ' ){
				next[i] = '*';
			}
			// White and Neighbors Black = black
			else if(center == ' ' && left == '*' && right == '*' ){
				next[i] = '*';
			}
			// White, Left Black, Right White = white
			else if(center == ' ' && left == '*' && right == ' '){
				next[i] = ' ';
			}
			// Black, Left White, Right Black = Black
			else if(center == '*' && left == ' ' && right == '*' ){
				next[i] = '*';
			}
			// Black and Neighbors White = White
			else if(center == '*' && left == ' ' && right == ' ' ){
				next[i] = ' ';
			}
			// White, Left White, Right Black = white
			else if(center == ' ' && left == ' ' && right == '*'){
				next[i] = ' ';
			}
			// White and Neighbors White = black
			else if(center == ' ' && left == ' ' && right == ' '){
				next[i] = '*';
			}
		}
		if(Rule == 45){
			next[i] = ' ';
			if(center == '*' && left == '*' && right == '*' ){
				next[i] = ' ';
			}

			else if(center == '*' && left == '*' && right == ' ' ){
				next[i] = ' ';
			}

			else if(center == ' ' && left == '*' && right == '*' ){
				next[i] = '*';
			}

			else if(center == ' ' && left == '*' && right == ' '){
				next[i] = ' ';
			}

			else if(center == '*' && left == ' ' && right == '*' ){
				next[i] = '*';
			}

			else if(center == '*' && left == ' ' && right == ' ' ){
				next[i] = '*';
			}

			else if(center == ' ' && left == ' ' && right == '*'){
				next[i] = ' ';
			}

			else if(center == ' ' && left == ' ' && right == ' '){
				next[i] = '*';
			}
		}
		
		
		
	}
	memcpy(cp, next, 61);
}
