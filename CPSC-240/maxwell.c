//================================================================================================================================
//																																*
//  Author information																											*
//  Author name: Ashley Thorlin																									*
//  Author email: ashleythorlin@csu.fullerton.edu																				*
//																																*
//===============================================================================================================================*
//																																*
//Program information																											*
//  Program name: Triangle Program																								*
//  Programming languages: Main function in C++; "Triangle" function in X86-64													*
//  Files in the program: pythagoras.c, triangle.asm, r.sh																		*
//																																*
//===============================================================================================================================*
//																																*
//Copyright (C) 2021 Ashley Thorlin                                                                    				            *
//	This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License   *
//	version 3 as published by the Free Software Foundation.                                                                     *
//	This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied          *
//	warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.      *
//	A copy of the GNU General Public License v3 is available here:  <https://www.gnu.org/licenses/>.  							*
//																																*
//===============================================================================================================================*
//																																*
//Purpose																														*
//  The intent of this program is to allow the user to input the lengths of two sides of a right triangle and the program will	*
//	output the triangle's area and the length of the hypotenuse.																*
//																																*
//==============================================================================================================================*

#include <stdio.h>

double triangle();

int main(int arc, char* argv[]){
	
	double hertz = 0.0;
	
	printf("Welcome to the Hertz program written by Ashley Thorlin.\n");
	printf("If errors are discovered, report to Ashley Thorlin at ashleythorlin@csu.fullerton.edu.\n");
	hertz = calc_hertz();
	printf("The main function received the number %.5lf and plans to keep it.", hertz);
	printf("An integer zero will be returned to the OS. Goodbye!");
	return 0;
}


