#include <stdio.h>
#include <string.h>


char base64(int c) {
    if (c < 26) { 
        return c + 65; 
    } else if (c < 52) { 
        return c + 71; 
    } else if (c <= 61) { 
        return c - 4; 
    } else if (c == 62) { 
        return 43; 
    } else { 
        return 47; 
    }
}

int main(int argc, char *argv[])
{
    char input[] = "\x49\x27\x6d\x20\x6b\x69\x6c\x6c\x69\x6e\x67\x20\x79\x6f\x75\x72\x20\x62\x72\x61\x69\x6e\x20\x6c\x69\x6b\x65\x20\x61\x20\x70\x6f\x69\x73\x6f\x6e\x6f\x75\x73\x20\x6d\x75\x73\x68\x72\x6f\x6f\x6d";

    int i = 0;

    for (int i = 0; i * 6 < strlen(input) * 8; ++i) {
        const char* p = input + (i * 6)/8;
        char val = 0;

        switch(i % 4) {
            case 0:
                val += (*p & 0xFC) >> 2;
                break;
            case 1:
                val += (*p & 0x03) << 4;
                val += *(p+1) >> 4;
                break;
            case 2:
                val += (*p & 0x0F) << 2;
                val += *(p+1) >> 6;
                break;
            case 3:
                val += (*p & 0x3f);
                val += *(p+1) >> 8;
                break;
        }
        printf("%c", base64(val));
    }
    printf("\n");

    return 0;
}