//===============================================================================================================================
//
//	Name: Ashley Thorlin
//	Class/Section: CPSC 240-01 (took final with 240-05)
//	Email: ashleythorlin@csu.fullerton.edu
//	Program Name: SSE Benchmarking Program
//
//===============================================================================================================================


#include <stdio.h>

// Declaration of area function in assembly.
double benchmark();

int main()
{
	double result = -999.999;
	printf("\n%s","This is Final Exam by Ashley Thorlin\n\n");
	
	result = benchmark();
	
	printf("\nThe main program received %lf and will keep it.", result);
	
	printf("\nHave a nice day.\n\n");
	return 0;
}