#include <string>
#include <iostream>
#include <cstdlib>
#include <string>


int getbit(unsigned x, unsigned n) { return (x >> n) & 1; }

char* tobinary(unsigned long x, int bits) { 
  static char buf[BUFSIZ];
  memset(buf, 0, sizeof(char));

  char* p = buf;
  for (int i = bits - 1; i >= 0; --i) { 
    *p++ = (getbit(x, i) == 1 ? '1' : '0');
    if (i % 8 == 0) { *p++ = ' ';  }
  }
  if (*(p - 1) == ' ') { --p; }
  *p = '\0';
  return buf;
}

char* tobinary_4( unsigned long x) { return tobinary(x, 4); }
char* tobinary_8( unsigned long x) { return tobinary(x, 8); }
char* tobinary_16(unsigned long x) { return tobinary(x, 16); }
char* tobinary_24(unsigned long x) { return tobinary(x, 24); }
char* tobinary_32(unsigned long x) { return tobinary(x, 32); }

char tobase64(char c) { 
  if (c < 26) { return c + 65; 
  } else if (c < 52) { return c + 71; 
  } else if (c <= 61) { return c - 4; 
  } else if (c == 62) { return 43; 
  } else { return 47; }
}

void base64(const char* src, char* dst) {

  unsigned long combined = (src[0] << 16) | (src[1] << 8) | src[2];
  unsigned mask = 63;   // mask really was 63 to get only 6 bits at a time

  for (int i = 18, j = 0; i >= 0; i -= 6, ++j) {
    dst[j] = tobase64((combined >> i) & mask);
  }
}

void convert_to_base64(const char* src, char* dst, int n) {
  for (int i = 0, j = 0; i < n; i += 3, j += 4) {
    base64(src + i, dst + j);
  }
  // dst[n + 1] = '\0';
}

char hex_char(char value) {
  if (value > 15) { throw new std::invalid_argument("dec is not a valid hex value"); }
  if (value < 10) { return '0' + value; }
  else { return 'A' + value - 10; }
}

char dec_value(char hex) {   // e.g., converts, 'A' --> 10
  if (!isxdigit(hex)) { throw new std::invalid_argument("c is not a valid hex character\n"); }

  char value = 0;
  hex = toupper(hex);
  if ('A' <= hex && hex <= 'F') { value = hex - 'A' + 10; }
  else { value = hex - '0'; }

  return value;
}

char toascii_frombinary(const char* s) {
  int n = strlen(s);
  const char* p = s + n - 1;
  char c = 0;
  unsigned power = 1;
  while (*p != '\0' && p >= s) { 
    if (*p != '0' && *p != '1') { throw new std::invalid_argument("invalid binary number"); }
    if (*p-- == '1') { 
      c += power;
    }
    power <<= 1;
  }
  return c;
}

void hex_decoded(const char* src, char* dst, int n) {
    for (int i = 0, j = 0; i < n; i += 2, ++j) { 
      dst[j] = dec_value(src[i]) << 4 | dec_value(src[i + 1]); 
    }
    std::cout << "\nOriginal data...\n";
    for (int i = 0; i < n; ++i) { 
      std::cout << src[i];  
      if (i % 6 == 5) { 
        std::cout << " "; 
      } 
    }  

    std::cout << "\n\nHex conversion... (hexbuf[0] << 4 | hexbuf[1]  hexbuf[2] << 4 | hexbuf[3])...)\n";
    for (int i = 0; i < n/2; ++i) { 
      std::cout << tobinary_8(dst[i]) << " "; 
    }  
    std::cout << "\n";
}

void block_xor(const char* src1, const char* src2, char* dst, int n) {
  for (int i = 0; i < n; ++i) { 
    dst[i] = (char)((unsigned)src1[i] ^ (unsigned)src2[i]);
  }
}



std::string BinaryToHex(std::string Binary) {    // e.g., 1101 --> D
  static char buf[16];
  unsigned c = toascii_frombinary(Binary.c_str());
  snprintf(buf, sizeof(buf), "%x", c);
  return std::string(buf);
}

std::string HexToBinary(std::string Hex) {      // e.g., D --> 1101
  unsigned x = strtol(Hex.c_str(), NULL, 16);
  return std::string(tobinary_4(x));
}

std::string AsciiToBinary(std::string Ascii) {   // e.g., 'A' --> 01000001
  char c = Ascii.c_str()[0];
  const char* s = tobinary_8(c);
  return std::string(s);
}

std::string BinaryToText(std::string Binary) {
  static char buf[16];
  char c = toascii_frombinary(Binary.c_str());
  if (c == 127) { return std::string("DELETE"); }
  if (c > 127) { return std::string(); }

  snprintf(buf, sizeof(buf), "%c", c);
  return std::string(buf);
}

std::string BinaryToBase64(std::string Binary) {
  static char buf[16];
  memset(buf, 0, sizeof(buf));
  char c = toascii_frombinary(Binary.c_str());
  char cbase64 = tobase64(c);
  snprintf(buf, sizeof(buf), "%c", cbase64);
  return std::string(buf);
}


//==================================================================================
// TESTS 
//==================================================================================

void test_one_hex_char(int dec) {
  std::cout << dec << " is " << hex_char(dec) << "\n";
}
void test_hex_char() {
  for (int i = 0; i < 16; ++i) { test_one_hex_char(i); }
}

void test_one_dec_value(char hex) {
  std::cout << hex << " is " << (int)dec_value(hex) << "\n";
}

void test_dec_value() {
  for (char c = '0'; c <= '9'; ++c) {
    test_one_dec_value(c);
  }
  for (char c = 'a'; c <= 'f'; ++c) {
    test_one_dec_value(c);
  }
}

void one_test_base64(const char* s) {
  char src[4];
  char dst[4];
  memset(src, 0, sizeof(src));
  memset(dst, 0, sizeof(dst));
  strncpy(src, s, sizeof(src));

  base64(src, dst);
  std::cout << dst;  //  << " " << std::flush;
}

void test_base64() {
  char src[] = "Many hands make light work.";
  char dst[BUFSIZ];
  memset(dst, 0, sizeof(dst));
  convert_to_base64(src, dst, strlen(src));
  std::cout << "\n\n\tTest base64 conversion...\n";
  std::cout << src << "\n";
  std::cout << dst << "\n";

  std::cout << "\n\n";
}

void test_hexdecoded() { 
  char hexbuf[] = "49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d";
    char decbuf[BUFSIZ];
    char base64_buf[BUFSIZ];

    memset(decbuf, 0, sizeof(decbuf));
    memset(base64_buf, 0, sizeof(base64_buf));
    int n = strlen(hexbuf);
    hex_decoded(hexbuf, decbuf, n);
}

void test_BinaryToText() { 
  for (unsigned int x = 33; x < 200; ++x) { 
    const char* s = tobinary_8(x);
    std::string binary(s);
    std::string text = BinaryToText(binary);
    std::cout << s << " is " << text << "\n";
  }
}

void test_tobinary_8() { 
  printf("TESTING test_tobinary8()............................\n");
  printf("A is: %s\n", tobinary_8('A'));
  printf("B is: %s\n", tobinary_8('B'));
  printf("C is: %s\n", tobinary_8('C'));
  printf("D is: %s\n", tobinary_8('D'));
  printf("E is: %s\n", tobinary_8('E'));
  printf("F is: %s\n", tobinary_8('F'));

  printf("end testing test_tobinary8()............................\n");
}

void test_toascii_frombinary() { 
  // std::initializer_list<std::string> li = { "00110000", "00110001", "00110010", "00110011", "00110100" };
  // for (const std::string el : li) { 
  //   std::cout << el << " is " << toascii_frombinary(el.c_str()) << "\n";
  // }

  for (unsigned int x = 48; x < 122; ++x) { 
    char* s = tobinary_8(x);
    std::cout << "'" << s << "' is " << toascii_frombinary(s) << "\n";
  }
}

void test_HexToBinary() { 
  char buf[10];

  for (unsigned x = 0; x < 16; ++x) { 
    snprintf(buf, sizeof(buf), "%x", x);  
    std::string hex(buf);
    std::cout << buf << " is " << HexToBinary(hex) << "\n";
  }
}

void test_BinaryToHex() { 
  std::cout << "TESTING BinaryToHex()======================\n";
  for (unsigned x = 0; x < 16; ++x) { 
    const char* s = tobinary_4(x);
    std::string binary(s);
    std::cout << s << " is " << BinaryToHex(binary) << "\n";
  }
}

void test_AsciiToBinary() { 
  char buf[16];
  memset(buf, 0, sizeof(buf));

  for (int x = 48; x < 125; ++x) { 
    snprintf(buf, sizeof(buf), "%c", x);
    std::string s(buf);
    std::cout << s << " is " << AsciiToBinary(s) << "\n";
  }
}
 
void test_BinaryToBase64() {
  for (unsigned x = 0; x < 64; ++x) { 
    const char* binary = tobinary_8(x);
    std::string base64 = BinaryToBase64(binary);
    std::cout << binary << " is " << base64 << "\n";
  } 
 }

