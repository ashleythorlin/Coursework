//===============================================================================================================================
//
//	Name: Ashley Thorlin
//	Class/Section: CPSC 240-01
//	Email: ashleythorlin@csu.fullerton.edu
//	Program Name: Heron's Area
//
//===============================================================================================================================

#include <stdio.h>

// Declaration of area function in assembly.
double area();
void output_area(double);
void output_error();

int main()
{
	double result = -999.999;
	printf("\n%s","Welcome to Heron's Area by Ashley Thorlin\n\n");
	
	result = area();
	if(result == 0.0){
		output_error();
	}
	
	else{
		output_area(result);
	}
	
	printf("\nThe main program received this number %lf and will keep it.", result);
	
	printf("\nI hope you enjoyed this triangle program. A zero will be sent to the OS. Bye.\n\n");
	return 0;
}