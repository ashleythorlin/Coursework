#include <stdio.h>
#include <stdlib.h>
#include <string.h>


char* hextobase64(char *hex, int size)
{
    int sizeb64 = 64;
    char* base64 = calloc(sizeb64+1, 1);
    unsigned mask = 63;

    for (int i = size-1; i>= 0; i-=3, sizeb64 -= 2) {
        base64[sizeb64] |= hex[i];

        if (i > 1) {
            base64[sizeb64 - 1] |= ((hex[i - 2] << 2));
        }

        if (i > 0) {
            base64[sizeb64] |= ((hex[i - 1] << 4) & mask);
            base64[sizeb64 - 1] |= (hex[i - 1] >> 2);
        }

        
    }
    return base64;
}

char offset(char c){
    if (c < 26) {
            return c + 65;
        }
        else if (c < 52) {
            return c + 71;
        }
        else if (c < 62) {
            return c - 4;
        }
        else if (c == 62) {
            return 43;
		}
        else {
            return 47;
        }
}

char* strtoarr(char *str, int length){

    int size = length;
    char* arr = calloc(size+1, 1);

    memset(arr, 0, sizeof(char));

    for(int i = 0; i < strlen(str); i++){
        arr[i] = str[i];
    }

    return arr;
}


int main(int argc, char **argv)
{
    char str[] = "49276D206B696C6C696E6720796F757220627261696E206C696B65206120706F69736F6E6F7573206D757368726F6F6D";

    char src[97];
    char dst[65];
    char output[65];

    memset(src, '\0', sizeof(src));

    strcpy(src, str);

    dst = hextobase64(src, sizeof(src));

    int i = 0;

    for (i = 64; i >= 0; i--) {
        output[i] = offset(dst[i]);
    }
    
    output++;   //remove leading zero/A
    printf("%s\n", output);
    return 0;

    return 0;
}