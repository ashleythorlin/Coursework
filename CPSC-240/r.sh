#===============================================================================================================================
#
#	Name: Ashley Thorlin
#	Class/Section: CPSC 240-01
#	Email: ashleythorlin@csu.fullerton.edu
#	Program Name: Heron's Area
#
#===============================================================================================================================
#!/bin/bash

rm *.o
rm *.out

echo "The script file for Heron's Area has begun"

#echo "Assemble huron.asm"
nasm -f elf64 -l huron.lis -o huron.o huron.asm

#echo "Compile triangle.c"
gcc -c -Wall -m64 -no-pie -o triangle.o triangle.c -std=c17

#echo "Compile output_area.c"
gcc -c -Wall -m64 -no-pie -o output_area.o output_area.c -std=c17

#echo "Compile output_error_message.c"
gcc -c -Wall -m64 -no-pie -o output_error_message.o output_error_message.c -std=c17

#echo "Compile isfloat.cpp"
g++ -c -m64 -Wall -fno-pie -no-pie -o isfloat.o isfloat.cpp -std=c++17

#echo "Link the object files"
gcc -m64 -no-pie -o a.out -std=c11 huron.o triangle.o output_area.o output_error_message.o isfloat.o

echo "----- Run the program -----"
./a.out

echo "----- End Program -----"