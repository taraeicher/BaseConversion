/* Program Description: This program converts a given number from a given input base to a given output base. All input is collected from the user through stdin and
 *		and undergoes character-by-character validation. The number is first converted to decimal, then to the output base. After conversion, the number is
 *		printed for the user through stdin. In the case of a user error, the user is prompted to choose between entering a new number and entering new bases.
 * Programmer Name: Tara Eicher
 * Programmer WSU ID: z847x563
 * Professor Name: Prof. Joseph Lesniak
 * Date Last Modified: 8/31/14
 */

#include <stdio.h>				//contains getc() and printf()
#include <stdlib.h>				//contains malloc()
#include <ctype.h>				//contains isdigit()
#include <string.h>				//contains strlen() and strcmp()
#include "baseConversion.h"		//header file
#include "conversionOps.h"		//contains base conversion functions
//#include "errors.h"				//contains error-handling function

//Main program

int main()
{
	
	NumberValidationStatus status=REDO_NUMBER;			//Determines next step after validation
	long decimalValue=-1;								//Decimal value of number entered
	unsigned short baseIn=0;							//Input base
	unsigned short baseOut=0;							//Output base
	char* digits;										//References input digits
	char* outputDigits;									//References output digits
	char* maxNumInput=(char*)malloc(sizeof(char)*32);;		//References maximum number for given input base. 31 is highest number of digits for a binary long.
	char* maxNumOutput=(char*)malloc(sizeof(char)*32);;		//References maximum number for given output base. 31 is highest number of digits for a binary long.

	//Print main prompt.

	printf("Welcome to Base Conversion! This program converts a number of any base between 2 and 20 to a given base between 2 and 20.\n");

	//Get base numbers for input and output. Obtain the maximum number possible for this number.

	getBases(&baseIn,&baseOut);
	getMaxNum(baseIn,maxNumInput);
	getMaxNum(baseOut,maxNumOutput);
	digits=(char*)malloc(sizeof(char)*(strlen(maxNumInput)+1));			//+1 is needed for null character.
	outputDigits=(char*)malloc(sizeof(char)*(strlen(maxNumOutput)+1));	//+1 is needed for null character.

	//Get and validate number. Repeat number and base entry as needed.

	while(status!=CONTINUE)
	{
		//If user wants to re-enter the number, call the function that collects and validates the number.
		//If the user wants to re-enter the bases, reset the bases, and call the functions that collect and validate the bases and the number.
	
		if(status==REDO_NUMBER)
			status=determineNumberValidity(digits,baseIn,maxNumInput);
		else if(status==EXIT)
		{
			//Free memory.

			free(digits);
			free(outputDigits);
			free(maxNumInput);
			free(maxNumOutput);
		
			return(0);
		}
	}

		//Convert input to decimal value. Quit if there was an error. Otherwise, convert the decimal value to the output base and print the number.

	printf("\nConverting the number...\n");
	decimalValue=convertBaseToDecimal(digits,baseIn);
	if(decimalValue<0)
	{
		printf("\nThere was an error converting this number. Base Conversion will now terminate.\n");
	}
	else
	{
		convertDecimalToBase(decimalValue,baseOut,outputDigits);
		printf("\nConversion complete.\n");
		printf("The base %d number %s converts to %s in base %d.\n",baseIn,digits,outputDigits,baseOut);
		printf("Thank you for using Base Conversion.\n");

		//Close and exit the program.
		
	}
	
	//Free memory.

	free(digits);
	free(outputDigits);
	free(maxNumInput);
	free(maxNumOutput);
		
	return(0);
		
}

//Collect base values from user via stdin.

void getBases(unsigned short* base1, unsigned short* base2)
{
	char output[3]; //Hold the output for validation. The array can hold two digits and a null/newline character.
	char input[3];  //Hold the input for validation. The array can hold two digits and a null/newline character.

	//Prompt the user for a valid input base. Repeat as needed.

	do
	{
		char temp;		//used for character input
		char* i;		//iterator

		//Get the input base.

		printf("\nPlease enter the input base. You must enter a whole number between 2 and 20.\n");
		temp=getc(stdin);

		//Repeat as long as input is not a null or newline character.

		for(i=input;temp!='\n'&&temp!='\0';i++)
		{
			*i=temp;
			temp=getc(stdin);
		}
		*i='\0';

		//If the first char is a digit and the second char is either a digit (and the third char is a newline) or a newline, set the input base value. Else, loop again.

		if(isdigit(input[0])&&((input[1]=='\0'&&input[0]>(48+1))||(input[2]=='\0'&&isdigit(input[1])&&(input[0]<(48+2)||(input[0]==(48+2)&&input[1]==(48+0))))))
		{

			//Set the base input value for the 1-digit or 2-digit number.
			//Note: 48 is the ASCII value of '0'.

			if(input[1]=='\0')
				*base1=((unsigned short)input[0])-48;
			else
				*base1=(((unsigned short)input[0])-48)*10+(((unsigned short)input[1])-48);
		}
		else
			printf("\nInvalid entry.\n");
	}
	while(!(2<=*base1&&*base1<=20));


	//Prompt the user for a valid output base. Repeat as needed.

	do
	{
		char temp;		//used for character input
		char* i;		//iterator

		//Get the input base.

		printf("\nPlease enter the output base. You must enter a whole number between 2 and 20, and it cannot be the same as the input base.\n");
		temp=getc(stdin);
		for(i=output;temp!='\n';i++)
		{
			*i=temp;
			temp=getc(stdin);
		}
		*i='\0';

		//If the first char is a digit and the second char is either a digit (and the third char is a newline) or a newline, set the input base value. Else, loop again.

		if(isdigit(output[0])&&((output[1]=='\0'&&output[0]>(48+1))||(output[2]=='\0'&&isdigit(output[1])&&(output[0]<(48+2)||(output[0]==(48+2)&&output[1]==(48+0))))))
		{

			//Set the base output value for the 1-digit or 2-digit number.
			//Print error message if output base has the same value as input base.
			//Note: 48 is the ASCII value of '0'
			
			if(output[0]!=input[0]||output[1]!=input[1])
			{
				if(output[1]=='\0')
					*base2=((unsigned short)output[0])-48;
				else
					*base2=(((unsigned short)output[0])-48)*10+(((unsigned short)output[1])-48);
			}
			else printf("\nInvalid entry.\n");
		}
		else
			printf("\nInvalid entry.\n");
	}
	while((!(2<=*base2&&*base2<=20))||(output[0]==input[0]&&output[1]==input[1]));
}

//Collect the number to be converted from the user via stdin. Check the validity of each digit.

NumberValidationStatus determineNumberValidity(char* input, unsigned short base, char* maximum)
{
	char keystroke,discard;
	char* startAddress=input;
	
	printf("\nPlease enter the base %d number you wish to convert: ",base);	//Prompt user for entry.
	keystroke=getc(stdin);			//Get the first character.

	//Iterate through until max number is reached or until the newline character is entered.

	while(input<=(startAddress+strlen(maximum))&&(keystroke!='\0'&&keystroke!='\n'))
	{
		//Validate that each character is an acceptable digit or alphanumeric character.
		//For bases less than ten, check that the character is an acceptable digit.
		//For bases greater than or equal to ten, check that the character is a digit or an acceptable alphabetical character.
		//Note: 48, 65, and 97 are the ASCII values of '0', 'A', and 'a', respectively.

		if(base<=10)
		{
			if(isdigit(keystroke)&&keystroke<(48+base))
				*input=keystroke;
				
			//If the number is invalid, perform error handling.
				
			else
			{
				printf("\nThat number contains a digit that is not base %d.\n",base);
				
				//Discard remainder of entry.
				
				discard=getc(stdin);
				while(discard!='\0'&&discard!='\n')
					discard=getc(stdin);
					
				return handleDigitError();
			}
		}
		else
		{
			//If it is a digit, copy it to the input string.
		
			if(isdigit(keystroke))
				*input=keystroke;
			
			//If it is a letter, convert it to upper-case and copy it to the input string.
			
			else if((keystroke>=65&&keystroke<(65+base-10))||(keystroke>=97&&keystroke<(97+base-10)))
			{
				keystroke=toupper(keystroke);
				*input=keystroke;
			}
			
			//If the number is invalid, perform error handling.
				
			else
			{
				printf("\nThat number contains a digit that is not base %d.\n",base);
				
				//Discard remainder of entry.
				
				discard=getc(stdin);
				while(discard!='\0'&&discard!='\n')
					discard=getc(stdin);
					
				return handleDigitError();
			}
		}
		
		//If there are leading zeros, ignore them, unless zero is the only digit.
		
		if(*startAddress=='0')
		{		
			keystroke=getc(stdin);
			if(keystroke!='\n'&&keystroke!='\0')
				input--;
			ungetc(keystroke,stdin);
		}
		
		//Iterate and get next character.

		input++;
		keystroke=getc(stdin);
	}
	
	*input='\0';		//The null string prevents out-of-bounds scanning.

	//If the number is too large, perform error handling. Else, notify that the number was converted as expected.

	if((input>(startAddress+strlen(maximum)))||(input==(startAddress+strlen(maximum))&&strcmp(startAddress,maximum)>0))
	{
		printf("\nThat number is too large. The maximum number for base %d is %s.\n",base,maximum);	
		
		//Discard remainder of entry.
		
		discard=getc(stdin);
		while(discard!='\0'&&discard!='\n')
			discard=getc(stdin);
			
		return handleDigitError();
	}
	else
	{
		return CONTINUE;
	}
}
