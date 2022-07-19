#include <stdio.h>
#include <string.h>

//returns the value of a bit within a number
int getbit(unsigned x, unsigned n) { 	//unsigned = neither + or -
    return (x >> n) & 1;  	//shifts
}

char* tobinary(unsigned long x) { 
	//create a buffer to hold the ascii when converting to binary
	static char buf[BUFSIZ];		//note that buf is an array

	//memset copies "0" to the <sizeof(char)> characters of buf
	memset(buf, 0, sizeof(char));		

	//pointer to buf
	char* p = buf;		//pointing to the first element of buf

	//loop converts long to binary by checking each bit
	for (int i = 31; i >= 0; --i) { 	//for loop runs BACKWARDS (i--) because digits are lowest at the end ...16^4, 16^3, 16^2, 16^1	
		*p++ = (getbit(x, i) == 1 ? '1' : '0');		//if (?) bit at index i == 1, then set element at p to 1, otherwise 0
		
		//separates groups of 8 bits
		if (i % 8 == 0) { 		
			*p++ = ' ';
		}
	}
	*p = '\0';		//add null terminator at the end of the buffer
	return buf;
}

//prints conversion to binary and binary to decimal 
void print_binary_dec(const char* msg, unsigned x) { 
  	printf("%s is %s --- %u\n", msg, tobinary(x), x);		// %u is unsigned integer
}

//prints conversion to binary --- not used?
void print_binary(const char* msg, unsigned x) { 
  	printf("%s is %s\n", msg, tobinary(x));		
}

//compensates for the offset of ascii table, converts from base64 to ascii table
char tobase(char c) { 
	if (c < 26) { 
		return c + 65; 

	} else if (c < 52) { 
		return c + 71; 

	} else if (c < 61) { 
		return c - 4; 

	} else if (c == 62) { 
		return 43; 

	} else { 
		return 47; }
}

//prints out converted string in base64
void base64(char* src, char* dst) {
	printf("putting them together to form 24 bits...\n");

	//combines all characters from src into one string of chars 
	unsigned long combined = (src[0] << 16) | (src[1] << 8) | src[2];

	//prints out binary of each char from src, one char per group (except for combined)
	print_binary_dec("src[0]", src[0] << 16);
	print_binary_dec("src[1]", src[1] << 8);
	print_binary_dec("src[2]", src[2]);
	print_binary_dec("comb  ", combined);
	printf("\n");

	printf("pulling them apart 6 bits at a time...\n");
	unsigned mask = 63;   // mask really was 63 to get only 6 bits at a time

	//right shift certain number of bits for first, second, third, and fourth group of 6 bits
	//assigns each grouping to one/two/three/four
	//shifts 18/12/6 bits in order to get a six bit binary string
	unsigned one   = (combined >> 18) & mask;		//00000000 01001101 00000000 00000000 --> 00000000 00000000 00000000 00010011
	unsigned two   = (combined >> 12) & mask;		//00000000 00000000 01100001 00000000  --> 00000000 00000000 00000000 00010110
	unsigned three = (combined >> 6) & mask;		//00000000 00000000 00000000 01101110  --> 00000000 00000000 00000000 00000101
	unsigned four  = combined & mask;				//00000000 01001101 01100001 01101110 -->  00000000 00000000 00000000 00101110

	//prints out new grouping
	print_binary_dec("one  ", one);
	print_binary_dec("two  ", two);
	print_binary_dec("three", three);
	print_binary_dec("four ", four);
	printf("\n");

	//converts new grouping to base64, assigns to dst
	dst[0] = tobase(one);
	dst[1] = tobase(two);
	dst[2] = tobase(three);
	dst[3] = tobase(four);
	dst[4] = '\0';
}

int main(int argc, const char* argv[]) { 
	printf("Challenge1\n\n");

	//define src/dst
	char src[80];
	char dst[80];

	//fill src and dst with zeroes
	memset(src, 0, sizeof(char));
	memset(dst, 0, sizeof(char));
	
	//sets src to "Man"
	strncpy(src, "Man", 3);

	printf("source is: '%s'\n", src);
	base64(src, dst);

	printf("src is: '%s', result is: '%s'\n\n", src, dst);

	return 0;
}


/*
NOTES:
Bitwise Operators:
1 = set
bitwise functions or used because they are fast
	/, * run in O(n^2) time
	% runs in O(n^3) time
	bitwise runs in O(n)

& AND:
both bits must be set
a	b
0 & 0 -> 0
0 & 1 -> 0
1 & 0 -> 0
1 & 1 -> 1

EX:
a = 5
b = 7
a + b = 101 + 111 = 101 = 5


| OR:
one bit must be set
a	b
0 | 0 -> 0
0 | 1 -> 1
1 | 0 -> 1
1 | 1 -> 1
like a+b (1 + 1 = 1 in binary)

^ XOR:
bits must be different
a	b
0 ^ 0 -> 0
0 ^ 1 -> 1
1 ^ 0 -> 1
1 ^ 1 -> 0

<< LEFT SHIFT OP:
deletes n bits from the front of the string, adds n zeroes to the end

5 << 1 = 00000101 -> 00001010; 5 becomes 10 (delete first bit, add 1 zero to the end)
similar to 5 * 2^(1) = 10

5 << 2 = 00000101 -> 00010100; 5 becomes 20 (delete first 2 bits, add 2 zeroes to the end)
similar to 5 * 2^(2) = 20

a << n -> a * 2^(n)

>> RIGHT SHIFT OP:
deletes n bits from the end of the string, adds n zeroes to the front
5 >> 1 = 00000101 -> 00000010; 5 becomes 2 (delete last bit, add one zero to the beginning )

a >> n -> a * 2^-(n)

~ NOT/COMPLEMENT:
flips all the bits, including sign (0 -> 1, 1 -> 0)

*/