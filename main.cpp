/*
	Group 11 Coding Convention(s):

	-The use of camel case for all function signatures, variable names, etc

	-All class names will start with a capital letter, and then proceed with lower case letters

	-In each class, public members/methods will be listed first and then protected/private members/methods

	-To divide each section, the following must be adhered to:

		Each major section of a listing should be separated by a dividing comment line. e.g. 
	//-------------------------------------

	And then proceeded with a title: i.e.) Revision History, List of #includes, etc.

	-In terms of version information, the following conventions will be followed [Oldest first]:
		i) Reversion history will start at 1.0 and proceed to 2.0, 3.0, etc.
		ii) Each version history will be followed by:
			a) day-month-year [Date]
			b) a name of the individual who had done the modification ex) Modified by Tanvir

	-In a block that is separated by --- (dashes), there will be a paragraph explaining what the header file / module contains and its purpose [will come after the history/version section]
		-All #include statements must be listed after the “explanation block” mentioned above
		-In terms of the explanation paragraph, mention what is being hidden/abstracted, and why particular procedures and attributes are “placed” together in the same header/module; in other words, explain cohesion

	- In terms of indentation, blocks of code will be “captured” and/or “boxed in” by a set of curly brackets (  {  )
		-Use "Visual Studio" style as C_Cpp: Clang_format_style, for example:
				if () //next line
                {
					//some code [use 1 “tab” ]
				}
		-In terms of spacing for “=”, there must be one space to the left and to the right of the “=”; at the end of each line when the “ ; “  must be entered, there must be no space to the left of it

	-In terms of how comments for functions should be listed [in the header files], adhere to the following:

		i)all function prototypes must be proceeded by a horizontal line ( ----- )
		ii)All comments related to a function prototype must be placed after the function signature and before any other statement
		iii)all function parameters must be listed on separate lines [must include its type and direction (either in or out) [In meaning what gets inputted and out means what gets outputted and/or sent out to other functions, etc]; Also, all function parameters must have their name listed

	-All function signatures must also include the following:
		i) what the function does [as in, what it can do for programmers that call it]
		ii) any possible exceptions
*/

#include "database.h"
#include "print.h"
#include "control.h"
#include "ui.h"
#include <iostream>
#include <string>
using namespace std;

int main()
{
    openDatabase();
    bool exit;
    do
    {
        exit = mainMenu();
    } while (exit == false);
    closeDatabase();
    return 0;
}