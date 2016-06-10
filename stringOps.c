/* Library Description: These functions perform operations on strings.
 * Programmer Name: Tara Eicher
 * Programmer WSU ID: z847x563
 * Professor Name: Prof. Joseph Lesniak
 * Date Last Modified: 8/31/14
 */

#include <stdlib.h>			//contains malloc()	
#include <string.h>			//contains strlen()
#include "stringOps.h"		//header file

//This function reverses the characters in a string, leaving the null character intact.

void reverseString(char* string)
{
	char* copy=(char*)malloc(sizeof(char)*strlen(string));
	unsigned short i=1;
	strcpy(copy,string);	//Copy the string string in order to copy it back in reverse.

	//Copy the string back in reverse.
	do
	{
		*string=*(copy+strlen(copy)-i);
		string++;
		i++;
	}
	while(i<=strlen(copy));

	//Free memory.

	free(copy);
}