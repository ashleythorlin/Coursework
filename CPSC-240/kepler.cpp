//================================================================================================================================
//
//	Ashley Thorlin
//	CPSC 240-01
//	ashleythorlin@csu.fullerton.edu
//	Electricity Program
//
//================================================================================================================================

#include <stdio.h>
#include <stdint.h>

extern "C" char* copernicus();

int main(int argc, char* argv[]){
	
	char* title;
	
	printf("%s","Welcome to High Voltage System Programming brought to you by Ashley Thorlin.\n");
	title = copernicus();
	printf("%s%s%s", "Goodbye ", title, ". Have a nice research party.\n");
	printf("%s", "Zero will be returned to the operating system.\n");

	return 0; 
}