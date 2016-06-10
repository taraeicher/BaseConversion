/* Library Description: These functions perform conversion operations between decimal and non-decimal bases.
 * Programmer Name: Tara Eicher
 * Programmer WSU ID: z847x563
 * Professor Name: Prof. Joseph Lesniak
 * Date Last Modified: 8/31/14
 */
 
#include <limits.h>				//contains LONG_MAX		
#include <ctype.h>				//contains isdigit() and isupper()
#include "conversionOps.h"		//header file
#include "stringOps.h"			//string handling header file

//Convert the input from the input base to a decimal number.

long convertBaseToDecimal(char* input,unsigned short base)
{
	long decimal=0;

	//Keep processing until null string is reached. This prevents processing of out-of-bounds data.

	while(*input!='\0')
	{
		//Multiply previous decimal value by the base and add the new digit. Handle alphabetical characters separately.
		//Note: 48 and 65 are the ASCII values of '0' and 'A' respectively.

		decimal*=base;
		if(isdigit(*input))
			decimal+=*input-48;
		else
		{
			//Handle characters by ASCII value. If a character is passed that is not alphanumeric (or is lower-case alphabetical) return an error status.

			if(isupper(*input))
				decimal+=(*input)-(65-10);
			else
				return -1;
		}
		input++;
	}
	return decimal;
}

//Get the maximum number of digits to allocate for the input base.

void getMaxNum(unsigned short base, char* maximum)
{
	//Convert the maximum number to its value in the provided base and determine the length of the value.
	
	convertDecimalToBase(LONG_MAX,base,maximum);
}

//Convert any number from a given base to a decimal number.

void convertDecimalToBase(long decimalNumber, unsigned short base,char* convertedNumber)
{
	unsigned short remainder;
	char* start=convertedNumber;
	
	//Use iterative base conversion. Place each digit in the output. Handle zero in a special case.
	//Note: 48 and 65 are the ASCII values of '0' and 'A', respectively.

	if(decimalNumber==0)
	{
		*convertedNumber='0';
		convertedNumber++;
	}
	else
	{
		for(;decimalNumber!=0;convertedNumber++)
		{
			remainder=decimalNumber%base;
			if(remainder<10)
				*convertedNumber=remainder+48;
			else
				*convertedNumber=remainder+65-10;
			decimalNumber=decimalNumber/base;
		}
	}
	*convertedNumber='\0';	//Place the null character at the end to avoid out-of-bounds scanning.
	
	reverseString(start);	//Reverse the string to obtain the correct number.
}


