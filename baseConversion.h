/* Program Description: This program converts a given number from a given input base to a given output base. All input is collected from the user through stdin and
 *		and undergoes character-by-character validation. The number is first converted to decimal, then to the output base. After conversion, the number is
 *		printed for the user through stdin. In the case of a user error, the user is prompted to choose between entering a new number and entering new bases.
 * Programmer Name: Tara Eicher
 * Programmer WSU ID: z847x563
 * Professor Name: Prof. Joseph Lesniak
 * Date Last Modified: 8/31/14
 */
 
 //Prevent redefinition.
 
#ifndef BASE_CONVERSION_H
#define BASE_CONVERSION_H

#include "errors.h"
 
//Collect base values from user via stdin.

void getBases(unsigned short* base1, unsigned short* base2);
	
//Collect the number to be converted from the user via stdin. Check the validity of each digit.

NumberValidationStatus determineNumberValidity(char* input, unsigned short base, char* maximum);

#endif
