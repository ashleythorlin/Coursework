#include <stdio.h>
#include <string.h>
​
int getbit(unsigned x, unsigned n) { return (x >> n) & 1; }
​
char* tobinary(unsigned long x) { 
  static char buf[BUFSIZ];
  memset(buf, 0, sizeof(char));
​
  char* p = buf;
  for (int i = 31; i >= 0; --i) { 
    *p++ = (getbit(x, i) == 1 ? '1' : '0');
    if (i % 8 == 0) { *p++ = ' ';  }
  }
  *p = '\0';
  return buf;
}
​
void print_binary_dec(const char* msg, unsigned x) { 
  printf("%s is %s --- %u\n", msg, tobinary(x), x);
}
​
void print_binary(const char* msg, unsigned x) { 
  printf("%s is %s\n", msg, tobinary(x));
}
​
char tobase(char c) { 
  if (c < 26) { return c + 65; 
  } else if (c < 52) { return c + 71; 
  } else if (c < 61) { return c - 4; 
  } else if (c == 62) { return 43; 
  } else { return 47; }
}
​
void base64(char* src, char* dst) {
  printf("putting them together to form 24 bits...\n");
  unsigned long combined = (src[0] << 16) | (src[1] << 8) | src[2];
​
  print_binary_dec("src[0]", src[0] << 16);
  print_binary_dec("src[1]", src[1] << 8);
  print_binary_dec("src[2]", src[2]);
  print_binary_dec("comb  ", combined);
  printf("\n");
​
  printf("pulling them apart 6 bits at a time...\n");
  unsigned mask = 63;   // mask really was 63 to get only 6 bits at a time
​
  unsigned one   = (combined >> 18) & mask;
  unsigned two   = (combined >> 12) & mask;
  unsigned three = (combined >> 6) & mask;
  unsigned four  = combined & mask;
​
  print_binary_dec("one  ", one);
  print_binary_dec("two  ", two);
  print_binary_dec("three", three);
  print_binary_dec("four ", four);
  printf("\n");
​
  dst[0] = tobase(one);
  dst[1] = tobase(two);
  dst[2] = tobase(three);
  dst[3] = tobase(four);
  dst[4] = '\0';
}
​
int main(int argc, const char* argv[]) { 
  printf("Challenge1\n\n");
​
  char src[80];
  char dst[80];
​
  memset(src, 0, sizeof(char));
  memset(dst, 0, sizeof(char));
  strncpy(src, "Man", 3);
​
  printf("source is: '%s'\n", src);
  base64(src, dst);
​
  printf("src is: '%s', result is: '%s'\n\n", src, dst);
​
  return 0;
}