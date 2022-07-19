#include <string>
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <string>
#include <map>
#include <cmath>
#include <vector>
#include <cassert>
#include <numeric>

#include <fstream>


#include "utils.h"

void separator(char c, int width, int lines) {
  std::cout << "\n\n//";
  while (lines-- > 0) { 
    while (width-- > 0) { std::cout << c; }
  }
  std::cout << "\n\n";
}
void dash_separator(int width, int lines) { separator('-', width, lines); }
void plus_separator(int width, int lines) { separator('+', width, lines); }

std::string read_file(const std::string& filename) {
    std::ifstream ifs(filename);
    if (!ifs.is_open()) { 
        std::cerr << "Could not open file: '" << filename << "'\n";  
        exit(-1); 
    }

    std::string line, result;
    while (ifs >> line) { result += line; }
    ifs.close();

    return result;
}


// returns a single bit from position n (from the right)
//     of an unsigned int x
// e.g., for number 1110 010 1001 0101, getbit(x, 0) == 1, getbit(x, 1) == 0
int getbit(unsigned x, unsigned n) { return (x >> n) & 1; }


// returns an unsigned long as a std::string of 0's and 1's
//    to_binary4 returns a string of length 4 with only the rightmost 4 bits shown
//    to_binary8 returns    "     "     "   8    "    "       "       8   "    "
// e.g., for x = 0000 1110, tobinary_4 returns      "1110"
//                          tobinary_8 returns "0000 1110", ...
std::string tobinary(unsigned long x, int bits) { 
  static char buf[BUFSIZ];
  memset(buf, 0, sizeof(char));

  char* p = buf;
  for (int i = bits - 1; i >= 0; --i) { 
    *p++ = (getbit((int)x, i) == 1 ? '1' : '0');
    if (i % 8 == 0) { *p++ = ' ';  }
  }
  if (*(p - 1) == ' ') { --p; }
  *p = '\0';

  return std::string(buf);
}
std::string tobinary_4( unsigned long x) { return tobinary(x, 4); }
std::string tobinary_8( unsigned long x) { return tobinary(x, 8); }
std::string tobinary_16(unsigned long x) { return tobinary(x, 16); }
std::string tobinary_24(unsigned long x) { return tobinary(x, 24); }
std::string tobinary_32(unsigned long x) { return tobinary(x, 32); }


unsigned int count_one_bits(unsigned x, unsigned n) {
  unsigned int bits = 0;
  for (int i = 0; i < n; ++i) { bits += getbit(x, i); }

  return bits;
}
void test_count_one_bits() { 
  for (int x = 0; x < 128; ++x) {
    unsigned int n = count_one_bits(x, 8);
    std::cout << tobinary_8(x) << " (1 bits): " << n << "\n";
    if (x % 10 == 9) { std::cout << "\n"; }
  }
}


// Converts a single base64 character to its ASCII value, 
//    e.g, 0 in base64 --> 'A', 1 --> 'B', ...
//    only A-Z, a-z, and / are converted
//    all other characters are returned as =
unsigned char toascii(unsigned char base64_char) {  
  unsigned char& c = base64_char;    // alias for base64_char

  if (c < 26) { return c + 65; 
  } else if (c >= 26 && c < 52) { return c + 71; 
  } else if (c >= 52 && c <= 61) { return c - 4; 
  } else if (c == 62) { return 43; 
  } else if (c == 63) { return 47; 
  } else { throw new std::invalid_argument("Invalid base64 value\n"); }
}
void test_toascii() { 
  for (unsigned char base64_char = 0; base64_char < 64; ++base64_char) { 
    std::cout << std::setw(2) << (int)base64_char << " in base 64 is: " << toascii(base64_char) << "\n";
    if (base64_char % 10 == 9) { std::cout << "\n"; }
  }
}

unsigned char tobase64(unsigned char ascii_char) { 
  unsigned char& c = ascii_char;    // mask off highest-2 bits

  if (c == 43) {          // '+' --> 62
    return 62;                        
  } else if (c == 47) {   // '/' --> 63
    return 63; 
  } else if (c == 61) {   // '=' -->  0   (padding char)
    return 0;
  }

  if (!isalnum(c)) { 
    throw new std::invalid_argument("invalid ascii_char for base64"); 
  }
  if (c >= 48 && c < 58) { return c - '0' + 52; }  // '0' --> 52
  if (c >= 65 && c < 91) { return c - 'A'; }       // 'A' --> 0
  if (c >= 97 && c <= 122) { return c - 'a' + 26;   // 'a' --> 26
  } else { throw new std::invalid_argument("Invalid base64 encoding\n"); }  
}

void test_tobase64() { 
  for (unsigned char ascii_char = 'A'; ascii_char <= 'z'; ++ascii_char) {
    unsigned char& c = ascii_char;
    if (!isalpha(c) && c != '+' && c != '/') { continue; } 
    std::cout << c << " in ascii is: " << (int)tobase64(c) << "\n";
    if (c % 10 == 9) { std::cout << "\n"; }
  }
  std::cout << "\n";

  for (unsigned char ascii_char = '0'; ascii_char <= '9'; ++ascii_char) {
    unsigned char& c = ascii_char;
    std::cout << c << " in ascii is: " << (int)tobase64(c) << "\n";
  }

  std::cout << '+' << " in ascii is: " << (int)tobase64('+') << "\n";
  std::cout << '/' << " in ascii is: " << (int)tobase64('/') << "\n";
}

// converts 4 ascii base64-encoded chars (6 bits each) to 3 ascii chars
void to_ascii_from_word(const char* src, std::string& dst) {
  unsigned long combined
      = (tobase64(src[0]) << 18) | (tobase64(src[1]) << 12) 
      | (tobase64(src[2]) << 6)  | (tobase64(src[3]));
	
  unsigned mask = 255;   // modified from 127

  // std::cout << "combined is: " << tobinary_24(combined) << "\n\n";

  for (int i = 16, j = 0; i >= 0; i -= 8, ++j) {
    unsigned char c = (combined >> i) & mask;
    dst.push_back(c);
  }
}


void test_to_ascii_from_word() { 
  std::cout << "\n//=========================================================\n";
  std::cout << "// ...IN TEST_TO_ASCII_FROM_WORD()...\n";
  std::cout << "//=========================================================\n\n";
  std::string src("TWFu");
  std::string dst;

  for (unsigned char c : src) { std::cout << c; }  std::cout << "\n"; 
  to_ascii_from_word(src.c_str(), dst);
  for (unsigned char c : dst) { std::cout << c; }  std::cout << "\n"; 

  assert(dst == std::string("Man"));
  std::cout << "//=========================================================\n";
  std::cout << "//to_ascii_from_word assertion passed...\n";
  std::cout << "//=========================================================\n\n";
}

// converts a string of base-64 encoded ascii characters to a string of ascii characters
void to_ascii_from_string(const std::string& src, std::string& dst) {
  const char* psrc = src.c_str();
  int n = (int)src.length();
  for (int i = 0; i < n; i += 4) {
    to_ascii_from_word(psrc + i, dst);
  }
}
void test_to_ascii_from_string() { 
  std::cout << "\n//=========================================================\n";
  std::cout << "// ... IN TEST_TO_ASCII_FROM_STRING()...\n";
  std::cout << "//=========================================================\n\n";
  std::string src("TWFueSBoYW5kcyBtYWtlIGxpZ2h0IHdvcmsu");

  std::string dst;

  for (unsigned char c : src) { std::cout << c; }  std::cout << "\n"; 
  to_ascii_from_string(src.c_str(), dst);
  std::string hex;
  hex_encode(dst, hex);
  for (unsigned char c : hex) { std::cout << c; }  std::cout << "\n"; 

  assert(dst == std::string("Many hands make light work."));
  std::cout << "//=========================================================\n";
  std::cout << "// to_ascii_from_string assertion passed...\n";
  std::cout << "//=========================================================\n\n";
}

 // converts 3 ascii chars (8 bits each) to 4 base64-encoded ascii chars,
  //     by shifting the first left by 16 bits, 
  //                 the second left by 8 bits, 
  //     and ORing them all together to get a 24 bit unsigned long, then...
  //     breaking them into 4 six-bit base64 encoded chars, and
  //     translating them back into ascii
  //
void to_base64_from_word(const char* src, std::string& dst) {
  unsigned long combined = (src[0] << 16) | (src[1] << 8) | src[2];
  unsigned mask = 63;   // mask really was 63 to get only 6 bits at a time

  for (int i = 18, j = 0; i >= 0; i -= 6, ++j) {
    dst.push_back(toascii((unsigned char)((combined >> i) & mask)));
  }
}
void test_to_base64_from_word() { 
  std::cout << "\n//=========================================================\n";
  std::cout << "// ...IN TEST_TO_BASE64_FROM_WORD()...\n";
  std::cout << "//=========================================================\n\n";
  std::string src("Man");
  std::string dst;

  for (unsigned char c : src) { std::cout << c; }  std::cout << "\n"; 
  to_base64_from_word(src.c_str(), dst);
  for (unsigned char c : dst) { std::cout << c; }  std::cout << "\n"; 

  assert(dst == std::string("TWFu"));
  std::cout << "//=========================================================\n";
  std::cout << "//to_base64_from_word assertion passed...\n";
  std::cout << "//=========================================================\n\n";
}
// converts a string of ascii characters to a string of base64 ascii characters
//    by taking 3 characters at a time, calling on tobase_64 to convert
//    3 ascii characters to 4 base64 characters, 
//    and doing this again and again for the whole string
//
void to_base64_from_string(const std::string& src, std::string& dst) {
  const char* psrc = src.c_str();
  int n = src.length();
  for (int i = 0; i < n; i += 3) {
    to_base64_from_word(psrc + i, dst);
  }
}
void test_to_base64_from_string() { 
  std::cout << "\n//=========================================================\n";
  std::cout << "// ... IN TEST_TO_BASE64_FROM_STRING()...\n";
  std::cout << "//=========================================================\n\n";
  std::string src("Many hands make light work.");
  std::string dst;

  for (unsigned char c : src) { std::cout << c; }  std::cout << "\n"; 
  to_base64_from_string(src.c_str(), dst);
  for (unsigned char c : dst) { std::cout << c; }  std::cout << "\n"; 

  assert(dst == std::string("TWFueSBoYW5kcyBtYWtlIGxpZ2h0IHdvcmsu"));
  std::cout << "//=========================================================\n";
  std::cout << "// to_base64_from_string assertion passed...\n";
  std::cout << "//=========================================================\n\n";
}

unsigned char to_hex(unsigned char dec) {
  if (dec > 15) { throw new std::invalid_argument("dec is not a valid hex value"); }
  if (dec < 10) { return '0' + dec; }
  else { return 'a' + dec - 10; }
}
unsigned char to_dec(unsigned char hex) {   // e.g., converts, 'A' --> 10
  if (!isxdigit(hex)) { throw new std::invalid_argument("c is not a valid hex character\n"); }

  char value = 0;
  hex = toupper(hex);
  if ('A' <= hex && hex <= 'F') { value = hex - 'A' + 10; }
  else { value = hex - '0'; }

  return value;
}

// takes an ascii-encoded string of numbers and letters from a-f, 
//    and encodes each two 8-bit bytes into one 8-bit byte
//     "7a..." would be encoded into 0111 1010...  
//     Since 0111 1010 is 0x64 + 1x32 + 1x16 + 1x8 + 0x4 + 1x2 + 0x1 
//     = 32 + 16 + 8 + 2    =   58     =     ':',   "7a..." ---> ": ..."
// Due to compression, the length of the dst string will be half the length of the src string
//     Dependency:  dec_value() to convert each ascii-encoded value
void hex_decode(const std::string& src, std::string& dst) {
    int n = src.length();
    for (int i = 0; i < n; i += 2) { 
      dst.push_back(to_dec(src[i]) << 4 | to_dec(src[i + 1])); 
      // std::cout << tobinary_8(dst.back()) << "\n";
    }
}
void test_hex_decode() { 
  char hexbuf[] = "49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d";
  std::string src(hexbuf);
  std::string dst(src.length(), 0);   // same size as src, filled with '\0'
  hex_decode(src, dst);
}

void hex_encode(const std::string& src, std::string& dst) {
    int mask = 15;                                      // only want 4 bits at a time
    int n = src.length();
    const char* psrc = src.c_str();
    for (int i = 0; i < n; ++i) { 
        // std::cout << tobinary_8(xor_dst[i]) << "\n";
        dst.push_back(to_hex((psrc[i] >> 4) & mask));     // convert to hex
        dst.push_back(to_hex(psrc[i] & mask));
    }
}
void test_hex_encode() { 
  char hexbuf[] = "49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d";
  std::string src(hexbuf), decoded, encoded;
  hex_decode(src, decoded);
  hex_encode(decoded, encoded);

  assert(src == encoded);
  std::cout << "passed test_hex_decode()\n";
}

void block_xor(const std::string& src1, const std::string& src2, std::string& dst) {
  int n = src1.length();
  if (n != src2.length()) { throw new std::invalid_argument("src lengths not equal\n"); }

  for (int i = 0; i < n; ++i) {  dst.push_back(src1[i] ^ src2[i]); }
}

void single_char_xor(const std::string& src, std::string& dst, unsigned char c) {
  int n = src.length();
  for (int i = 0; i < n; ++i) { dst.push_back(src[i] ^ c); }
}

bool is_vowel(char c) { return (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'i'); }

std::string find_single_char_xor(const std::string& src, unsigned char& maxkey,
                          int& maxscore) {
  // static int count = 1;   // to track down problem key extractions

  std::string nohexsrc, key_xor, message;
  nohexsrc = src;
  // hex_decode(src, nohexsrc);    // 1.4 --> needs hex_decode, 1.3 doesn't, 1.6 doesn't

  int score = 0;
  for (unsigned char key = ' '; key <= 'z'; ++key) { 
      key_xor.clear();
      score = 0;

      single_char_xor(nohexsrc, key_xor, key);
      // single_char_xor(src, key_xor, key);

      // std::cout << "CHAR " << key << "    ";
      int i = 0;
      for (char c : key_xor) {
          if (isalpha(c) || isspace(c)) { ++score; }
          if (islower(c) && (is_vowel(c))) { ++score; }
          if (!isalpha(c) && !isspace(c)) { --score; }
          if (score >= maxscore) {  
            maxscore = score;  
            maxkey = key; 
            message = key_xor; 
          }
          // std::cout << c; 
      }   
      // std::cout << ", score: " << score << "\n";
  }
  // std::cout << "................ count is now: " << count++ << "\n";
  return message;
}


std::string find_string_single_char_xor(const std::vector<std::string>& sources, int& index,
                                        unsigned char& maxkey, int& maxscore) {

  int score = 0;     
  unsigned char key = '0';  
  std::string message, poss_message;
  int idx = 0;   
  for (const std::string& src : sources) { 
    score = 0;
    std::cout << "Testing " << std::setw(3) << idx << "    " << src << "\n";
    if (idx % 10 == 9) { std::cout << "\n"; }

    std::string hex_decoded;
    hex_decode(src, hex_decoded);
    poss_message = find_single_char_xor(hex_decoded, key, score);
    if (score > maxscore) {  maxscore = score;  index = idx;  maxkey = key;  message = poss_message; }
    ++idx;
  } 
  std::cout << "index: " << index << ", maxkey: " << maxkey << ", message = " << message << "\n";

  return message;
}
 
void repeating_key_xor(const std::string& src, const std::string& key, std::string& dst) {
  std::string x_or;
  int srclen = src.length();
  int keylen = key.length();

  for (int i = 0, j = 0; i < srclen; ++i, ++j) { 
    j %= keylen;                    // e.g., j is 3 but keylen is 3 --> j = 0
    x_or.push_back(src[i] ^ key[j]);
  }
  hex_encode(x_or, dst);
}

unsigned int hamming_distance(const std::string& s, const std::string& t) {
  const std::string& first = (s.length() > t.length() ? s : t);
  const std::string& second = (s.length() > t.length() ? t : s);
  // std::cout << "first is: " << first << "\n";
  // std::cout << "second is: " << second << "\n";

  unsigned int total = 0;
  for (int i = 0; i < first.length(); ++i) {
    unsigned char c = first[i];
    unsigned char d = (i < second.length() ? second[i] : (char)0);
    unsigned char x_or = c ^ d;

    unsigned int bits = count_one_bits(x_or, 8);
    total += bits;
    // std::cout << "total << " << total << " byte " << i << " : " << bits << "\n";
  }

  // std::cout << "hamming distance between: " << "'" << s << "' and '" << t << " is: " << total << "\n";

  return total;
}

void test_hamming_distance() {
  std::cout << "\n//=========================================================\n";
  std::cout << "// ... IN TEST_HAMMING_DISTANCE()...\n";
  std::cout << "//=========================================================\n\n";
  std::string s("seven"), t("seven");

  int hamming = hamming_distance(std::string("seven"), std::string("six"));
  hamming = hamming_distance(std::string("six"), std::string("seven"));
  hamming = hamming_distance(std::string("seven"), std::string("seven"));
  int hammingWokka = hamming_distance(std::string("this is a test"), 
                                      std::string("wokka wokka!!!"));

  assert(hammingWokka == 37);
  std::cout << "//=========================================================\n";
  std::cout << "// hamming_distance assertion passed...\n";
  std::cout << "//=========================================================\n\n";
}

double hamming_distance_for_keysize(const std::string& src, unsigned int keysize) {

  std::vector<unsigned int> blocks;
  unsigned int& n = keysize;  // alias

  for (unsigned int i = 0; i < src.length() - 2 * n; i += 2 * n) { 
    const std::string& first = src.substr(i, n);
    const std::string& second = src.substr(i + n, n);
    unsigned int hamming = hamming_distance(first, second);
    blocks.push_back(hamming);
  }
  std::sort(blocks.begin(), blocks.end());
  double average = std::reduce(blocks.begin(), blocks.end()) / blocks.size();
  return average / n;

  // bool average = true;

  // if (2 * n > src.length()) { throw new std::invalid_argument("src too short for keysize\n"); }
  // blocks.push_back(src.substr(i, n));
  // blocks.push_back(src.substr(i + n, n));
  // unsigned int distance = hamming_distance(blocks[0], blocks[1]);
  // double avg_distance = distance;    // covers case when only two blocks


  // if (src.length() < 4 * n) { average = false; }
  // else {
  //   blocks.push_back(src.substr(i + 2 * n, n));
  //   blocks.push_back(src.substr(i + 3 * n, n));
  //   unsigned int distance2 = hamming_distance(blocks[2], blocks[3]);
  //   avg_distance = (distance + distance2) / 2.0;   // covers case when 4 blocks
  // }

  return average / keysize;   // normalized keysize
}

std::vector<hamming_dist_key> best_keysize_hamming_distance(const std::string& src) {
  double min_distance = 100000;
  unsigned int min_keysize = UINT32_MAX;

  std::vector<hamming_dist_key> best_keys;
  unsigned max_key = std::min((unsigned int)(src.length() / 2), 40U);
  std::cout << "max_key is: " << max_key << "\n";
  std::cout << "src.length() is: " << src.length() << "\n";

  for (unsigned int keysize = 2; keysize < max_key; ++keysize) {
    double dist = hamming_distance_for_keysize(src, keysize);
    best_keys.push_back(hamming_dist_key(keysize, dist));

    if (dist < min_distance) { min_distance = dist; min_keysize = keysize; }
  }

      // sort by distance, based on hamming_distance_key.operator<
  std::sort(best_keys.begin(), best_keys.end());   
  return best_keys;
}
void test_best_keysize_hamming_distance() {
  std::cout << "\n//=========================================================\n";
  std::cout << "// ... IN TEST_BEST_KEYSIZE_HAMMING_DISTANCE()...\n";
  std::cout << "//=========================================================\n\n";

  std::string src = "threeRingsForTheElvenKingsUnderTheStarrySkySevenForTheDwarfLordsInTheirHallsOfStoneNineForMortalMenDoomedToDieOneForTheDarkLordOnHisDarkThroneInTheLandOfMordorWhereTheShadowsLie";
  std::cout << "src len is: " << src.length() << ", and src is: " << src << "\n";
  std::vector<hamming_dist_key> best_keys = best_keysize_hamming_distance(src);
  
  std::cout << "\nBEST five keys...\n";
  for (int i = 0; i < 5; ++i) { 
    std::cout << best_keys[i] << "\n";   
  }

  hamming_dist_key best = best_keys[0];
  assert(best.distance = 2 && best.keysize == 3);
  std::cout << "//=========================================================\n";
  std::cout << "// best_keysize_hamming_distance assertion passed...\n";
  std::cout << "//=========================================================\n\n";

}

void transpose_blocks(const std::string& src, unsigned int keysize, std::string& dst) {
  unsigned int& key = keysize;  // alias for keysize
  unsigned int n = src.length();

  for (int i = 0; i < n; i += key * key) {   
    for (int j = 0; j < key; ++j) {  
      for (int k = 0; k < key; ++k) {          
                 // i=0 .............................................................  i=1
                 // j=0 .............................................................  |                                                               
                 //  j=1 ............................................................  |
                 //   j=2 ...........................................................  |
                 // k=0   k=1   k=2   k=3   k=4 .....................................  |
                 // ABCDE ABCDE ABCDE ABCDE ABCDE --> AAAAA BBBBB CCCCC DDDDD EEEEE ...FGHIJ FGHIJ FGHIJ FGHIJ FGHIJ ... 
        dst.push_back(src[i + j + key * k]);   
        // std::cout << std::setw(4) << i + j + key * k;
      }
      std::cout << "   ";
    }
    std::cout << "\n";
  }
}
void test_transpose_blocks() { 
  std::cout << "\n//=========================================================\n";
  std::cout << "// ... IN TEST_TRANSPOSE_BLOCKS()...\n";
  std::cout << "//=========================================================\n";
  
  std::string src("ABC DEF GHI JKL MNO PQRSTUVWXYZa"), 
              dst;
  transpose_blocks(src, 3, dst);
  
  std::cout << "src is: " << src << "\n";
  std::cout << "dst is: " << dst << "\n";

  assert(dst == std::string("ADG BEH CFI JMP KNQ LORSVYTWZUXa"));
  std::cout << "//=========================================================\n";
  std::cout << "// transpose_blocks assertion passed...\n";
  std::cout << "//=========================================================\n\n";
}



std::string get_repeating_key_xor(const std::string& src, unsigned int keysize) {
  std::string key;

  for (unsigned int i = 0; i < keysize; ++i) {     // for all of the blocks that make up the repeating key (say 5)
    std::string block;
    int index = 0;
    unsigned char maxkey = 0;
    int maxscore = 0;
    for (int j = 0; j < keysize; ++j) {      // build the block
      block.push_back(src[i * keysize + j]);   
    }
    find_single_char_xor(block, maxkey, maxscore);   // for each block -- find the single char XOR key
    key.push_back(maxkey);                           //   and add it to the key
  }
  std::cout << "repeating key XOR is: " << key << "\n";
  return key;
}


void test_get_repeating_key_xor(const std::string& src) { 
  // std::string src("HUIfTQsPAh9PE048GmllH0kcDk4TAQsHThsBFkU2AB4BSWQgVB0dQzNTTmVS"), 
    std::string not_base64, hexdst, transposed;
    unsigned int keysize = 0;

    to_ascii_from_string(src, not_base64);   // from base64 encoding to ASCII (from 6bit to 8bit)

        // try keysizes from 2 to 40, return vector of keysize, hamming_distance in ascending order
    std::vector<hamming_dist_key> best_keys = best_keysize_hamming_distance(not_base64);

    for (const hamming_dist_key& hdk : best_keys) {    // list them
      std::cout << hdk << "\n";
    }
    // ----------------------------------------------- chop up text into best block size
    keysize = best_keys[0].keysize;
    transpose_blocks(not_base64, keysize, transposed);     // find repeating key xor (e.g., ICE)  

    std::string hex_encoded_src;
    // hex_encode(transposed, hex_encoded_src);

    // std::cout << "hex_encoded_string is: " << hex_encoded_src << "\n\n";


    std::string key = get_repeating_key_xor(transposed, keysize);
    std::cout << "REPEATING KEY was: " << key << "\n\n";


    key = std::string("Terminator X: Bring the noise");  // temporarily overwrite the key
    std::string x_or, plaintext;                 // XOR the repeating key to decode the text
    repeating_key_xor(not_base64, key, plaintext);

    // std::cout << "cipher text is: " << src << "\n\n";
    std::cout << "============================================\nPLAIN TEXT is\n";
    // std::cout << "plaintext is: " << plaintext << "\n\n";

    std::string hex_decoded;
    hex_decode(plaintext, hex_decoded);
    std::cout << "\n\n" << hex_decoded << "\n\n";
}

