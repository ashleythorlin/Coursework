#include <string.h>
#include <iostream>
#include <stdio.h>
#include <limits>
#include <string>
#include <sstream>

int getbit(unsigned x, unsigned n) { return (x >> n) & 1; }

char* tobinary(unsigned long x, int bits) 
{ 
    static char buf[BUFSIZ];
    memset(buf, 0, sizeof(char));

    char* p = buf;

    for (int i = bits - 1; i >= 0; --i)
    { 
        *p++ = (getbit(x, i) == 1 ? '1' : '0');
    }

    if (*(p - 1) == ' ') { --p; }
    *p = '\0';
    
    return buf;
}

char* tobinary4(unsigned long x) { return tobinary(x, 32); }
char* tobinary8( unsigned long x) { return tobinary(x, 8); }


std::string HexToBinary(std::string Hex) 
{      
    unsigned long x = strtoll(Hex.c_str(), NULL, 16);
    return std::string(tobinary4(x));
}

char binarytoascii(const char* s) {
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

std::string BinaryToHex(std::string Binary) {
  static char buf[16];
  unsigned c = binarytoascii(Binary.c_str());
  snprintf(buf, sizeof(buf), "%x", c);
  return std::string(buf);
}

std::string AsciiToBinary(std::string Ascii) {
  char c = Ascii.c_str()[0];
  const char* s = tobinary8(c);
  return std::string(s);
}


std::string decodeHex(std::string hex)
{
    std::string binary = "";
    std::string tempascii = "";
    std::string ascii = "";

    int group = hex.length() % 8;
    if (group == 0) {group = 8;}

    hex.insert(0, "000000000", 0, 8 - group);

    for (int i = 0; i < hex.length()/8; i++)
    {
        binary.append(HexToBinary(hex.substr(i*8,8)));
    }

    binary = binary.erase(0,4*(8-group));

    for (int k = 0; k < binary.length()/8; k++)
    {
      std::string temp = binary.substr(k*8,8);
      tempascii = binarytoascii(temp.c_str());
      ascii.append(tempascii);
    }

    return ascii;
}

std::string encodeHex(std::string text)
{
    std::string hex = "";
    std::string binary = "";

    for (int i = 0; i < text.length(); i++)
    {
        binary.append(AsciiToBinary(text.substr(i*1,1)));
    }

    for (int i = 0; i < binary.length()/4; i++)
    {
        hex.append(BinaryToHex(binary.substr(i*4,4)));
    }

    return hex;
}

int main()
{
    std::cout << ("Encoding the Text String: \n") << encodeHex("Currently trying our best. Considering how long this method of communication takes, you might want to get comfortable.") << "\n";
    std::cout << ("Decoding the Hex String: \n") << decodeHex("43757272656e746c7920747279696e67206f757220626573742e20436f6e7369646572696e6720686f77206c6f6e672074686973206d6574686f64206f6620636f6d6d756e69636174696f6e2074616b65732c20796f75206d696768742077616e7420746f2067657420636f6d666f727461626c652e") << "\n\n";
}