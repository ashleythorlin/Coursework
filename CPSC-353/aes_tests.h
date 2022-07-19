#ifndef __aes_tests_h__
#define __aes_tests_h__

#include <iostream>
#include <vector>
#include <cassert>
#include <fstream>

#include "aes.h"
#include "utils.h"


const unsigned int BLOCK_BYTES_LENGTH = 16 * sizeof(unsigned char);

void test_encrypt_ecb_keylength_128();
	
void test_encrypt_ecb_keylength_192();

void test_encrypt_ecb_keylength_256();

void test_encrypt_decrypt_one_block();

void test_encrypt_decrypt_vector_one_block();

void test_one_block_encrypt();

void test_one_block_encrypt_vector();

void test_ecb_one_block_without_byte_encrypt();

void test_ecb_one_block_plus_one_byte_encrypt();

void test_ecb_two_blocks_encrypt();

void test_ecb_one_block_decrypt();

void test_ecb_one_block_decrypt_vector();

void test_ecb_two_blocks_decrypt();

void test_cbc_encrypt_decrypt();

void test_cbc_encrypt_decrypt_vector();

void test_cbc_two_blocks_encrypt();

void test_cbc_two_blocks_encrypt_vector();

void test_cbc_two_blocks_decrypt();

void test_cbc_two_blocks_decrypt_vector();

void test_cfb_encrypt_decrypt();

void test_cfb_encrypt_decrypt_vector();

void test_cfb_encrypt_twoblocks();

void test_cfb_encrypt_twoblocks_vector();

void test_cfb_decrypt_twoblocks();

void test_cfb_decrypt_twoblocks_vector();

void test_ecb_256_longdata_encrypt_decrypt_one_kb();

void test_ecb_256_longdata_encrypt_decrypt_vector_one_kb();

void run_aes_tests();

enum CRYPTO { ENCRYPT, DECRYPT };

std::vector<unsigned char> test_ecb_128_crypto_vector(const std::vector<unsigned char>& cipher,
                                 const std::vector<unsigned char>& key, CRYPTO action);

std::vector<unsigned char> test_ecb_128_crypto_string(const std::string& cipher, 
                                                       const std::string& key,
                                                       CRYPTO action);
																											 
std::vector<unsigned char> test_ecb_128_crypto(const std::string& input, const std::string& key, CRYPTO action);

std::string pad_pkcs7_if_needed(const std::string& msg, unsigned int block_size, CRYPTO action);

std::vector<unsigned char> test_cbc_128_crypto_vector(
        const std::vector<unsigned char>& cipher,
        const std::vector<unsigned char>& key, 
        const std::vector<unsigned char>& prev, CRYPTO action);

std::vector<unsigned char> test_cbc_128_crypto(const std::string& input, const std::string& key, CRYPTO action);

bool ecb_mode_detected(const std::string& cipher, unsigned int block_size);


#endif
