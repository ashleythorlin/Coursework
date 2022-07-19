#ifndef __UTILS_H__
#define __UTILS_H__

#include <iostream>
#include <string>
#include <vector>


void separator(char c='=', int width=100, int lines=1);
void dash_separator(int width=80, int lines=1);
void plus_separator(int width=80, int lines=1);


int getbit(unsigned x, unsigned n);
unsigned int count_one_bits(unsigned x, unsigned n);
void test_count_one_bits();

std::string tobinary(unsigned long x, int bits);
std::string tobinary_4(unsigned long x);
std::string tobinary_8(unsigned long x);
std::string tobinary_16(unsigned long x);
std::string tobinary_24(unsigned long x);
std::string tobinary_32(unsigned long x);

unsigned char to_hex(unsigned char decimal);
unsigned char to_decimal(unsigned char hex);

void hex_decode(const std::string& src, std::string& dst);
void test_hex_decode();

void hex_encode(const std::string& src, std::string& dst);
void test_hex_encode();

unsigned char toascii(unsigned char base64_char);
void test_toascii();

void to_base64_from_word(const char* src, std::string& dst);
void test_to_base64_from_word();

void to_base64_from_string(const std::string& src, std::string& dst);
void test_to_base64_from_string();


unsigned char tobase64(unsigned char ascii_char);
void test_tobase64();
void to_ascii_from_word(const char* src, std::string& dst);
void test_to_ascii_from_word();
void to_ascii_from_string(const std::string& src, std::string& dst);
void test_to_ascii_from_string(); 
     
void block_xor(const std::string& src1, const std::string& src2, std::string& dst);
void single_char_xor(const std::string& src, std::string& dst, unsigned char c);
std::string find_single_char_xor(const std::string& src, unsigned char& maxkey,
                                 int& maxscore);

std::string find_string_single_char_xor(const std::vector<std::string>& sources, int& index,
                                        unsigned char& maxkey, int& maxscore);


void repeating_key_xor(const std::string& src, const std::string& key, std::string& dst);

unsigned int hamming_distance(const std::string& s, const std::string& t);
void test_hamming_distance();

struct hamming_dist_key {
    unsigned int keysize;
    double distance;

    hamming_dist_key(unsigned int keysize_, double distance_) 
    : keysize(keysize_), distance(distance_) { }

    friend bool operator<(const hamming_dist_key& a, const hamming_dist_key& b) { 
      return a.distance < b.distance;
    }
    friend std::ostream& operator<<(std::ostream& os, const hamming_dist_key& hdk) { 
      return os << "keysize: " << std::setw(2) << hdk.keysize << " has hamming dist: " 
                << std::fixed << std::setprecision(3) << hdk.distance;
    }
};

double hamming_distance_for_keysize(const std::string& src, unsigned int keysize);

std::vector<hamming_dist_key> best_keysize_hamming_distance(const std::string& src);
void test_best_keysize_hamming_distance();

void transpose_blocks(const std::string& src, unsigned int keysize, std::string& dst);
void test_transpose_blocks();

std::string get_repeating_key_xor(const std::string& src, unsigned int keysize);
void test_get_repeating_key_xor(const std::string& src);

#endif