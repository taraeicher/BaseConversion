/* Library Description: These functions handle digit entry errors for a base conversion application.
 * Programmer Name: Tara Eicher
 * Programmer WSU ID: z847x563
 * Professor Name: Prof. Joseph Lesniak
 * Date Last Modified: 8/31/14
 */

 //Prevent redefinition.
 
#ifndef ERRORS_H
#define ERRORS_H

 
//Returns the status of the number validation.

typedef enum{CONTINUE,REDO_NUMBER,EXIT}NumberValidationStatus;

//When the user enters an erroneous number, prompt for next action.

NumberValidationStatus handleDigitError();	

#endif
