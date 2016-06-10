/* Library Description: These functions handle digit entry errors for a base conversion application.
 * Programmer Name: Tara Eicher
 * Programmer WSU ID: z847x563
 * Professor Name: Prof. Joseph Lesniak
 * Date Last Modified: 8/23/14
 */

 #include <stdio.h>		//contains getc() and printf()
 #include "errors.h"	//header file
 
//When the user enters an erroneous number, prompt for next action.

NumberValidationStatus handleDigitError()
{
	char entry,discard;	//Get user entry, including characters to discard.
	NumberValidationStatus retVal;
	
	printf("Press '0' to enter a new number or '1' to exit: ");
	entry=getc(stdin);
	
	//Discard remainder of entry.
				
	discard=getc(stdin);
	while(discard!='\0'&&discard!='\n')
		discard=getc(stdin);

	switch(entry)
	{
		case '0': retVal=REDO_NUMBER;break;
		case '1': retVal=EXIT;break;
		default:retVal=handleDigitError();break;
	}
	
	return retVal;
}