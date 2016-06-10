/* Library Description: These functions perform conversion operations between decimal and non-decimal bases.
 * Programmer Name: Tara Eicher
 * Programmer WSU ID: z847x563
 * Professor Name: Prof. Joseph Lesniak
 * Date Last Modified: 8/31/14
 */
 
//Prevent redefinition.
 
#ifndef CONVERSION_OPS_H
#define CONVERSION_OPS_H


//Get the maximum number of digits to allocate for a given base.
 
void getMaxNum(unsigned short base, char* maximum);		

//Convert a decimal number to a number of a given base.

void convertDecimalToBase(long decimalNumber,unsigned short base,char* convertedNumber);		

//Convert a number of a given input base to a decimal number.

long convertBaseToDecimal(char* input,unsigned short base);	


#endif
