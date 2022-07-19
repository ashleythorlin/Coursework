#include <stdio.h>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <string>
#include <cassert>
#include <map>

#include "utils.h"


int challenge_1_1() {
    std::cout << "\n//=========================================================\n";
    std::cout << "// CHALLENGE 1_1 ..................\n";
    std::cout << "//=========================================================\n\n";

    char hexbuf[] = "49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d";
    std::string hex_encoded(hexbuf);

    std::string hex_decoded;
    std::string base64_encoded_ascii;

    hex_decode(hex_encoded, hex_decoded);
    to_base64_from_string(hex_decoded, base64_encoded_ascii);

    for (unsigned char c : base64_encoded_ascii) { std::cout << c; }  std::cout << "\n"; 

    assert(base64_encoded_ascii == std::string("SSdtIGtpbGxpbmcgeW91ciBicmFpbiBsaWtlIGEgcG9pc29ub3VzIG11c2hyb29t"));
    std::cout << "//=========================================================\n";
    std::cout << "// challenge 1_1 assertion passed...\n";
    std::cout << "//=========================================================\n\n";

    return 0;
}

int challenge_1_2() { 
    std::cout << "\n//=========================================================\n";
    std::cout << "// CHALLENGE 1_2 ..................\n";
    std::cout << "//=========================================================\n\n";

    std::cout << "\nCHALLENGE 2 ..................\n";
    std::string src1("1c0111001f010100061a024b53535009181c");
    std::string src2("686974207468652062756c6c277320657965");

    std::string hexsrc1, hexsrc2, xor_dst, result;

    hex_decode(src1, hexsrc1);
    hex_decode(src2, hexsrc2);
    block_xor(hexsrc1, hexsrc2, xor_dst);

    hex_encode(xor_dst, result);

    std::cout << "\nAfter block_xor...\n";
    std::cout << result << "\n\n";

    assert(result == std::string("746865206b696420646f6e277420706c6179"));
    std::cout << "//=========================================================\n";
    std::cout << "// challenge 1_2 assertion passed...\n";
    std::cout << "//=========================================================\n\n";

 
    return 0;
}

int challenge_1_3() {
    std::cout << "\n//=========================================================\n";
    std::cout << "// CHALLENGE 1_3 ..................\n";
    std::cout << "//=========================================================\n\n";

    char srcbuf[] = "1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736";
    // // char srcbuf[] = "01424d5d1a322a0d381717130e181d07240c2c19ecee750b1a37085d014c";
    // char srcbuf[] = "7b5a4215415d544115415d5015455447414c155c46155f4058455c5b523f";
    int maxscore = 0;
    unsigned char maxkey = '0';
    std::string message = find_single_char_xor(std::string(srcbuf), maxkey, maxscore);    
    
    std::cout << "\n\nSecret message at key: " << maxkey << ", message is: "
                << message << "\n\n";

    assert(message == std::string("Cooking MC's like a pound of bacon"));
    std::cout << "//=========================================================\n";
    std::cout << "// challenge 1_3 assertion passed...\n";
    std::cout << "//=========================================================\n\n";

    return 0;
}
 

#define FILE_ERROR 1

int challenge_1_4() {
    std::cout << "\n//=========================================================\n";
    std::cout << "// CHALLENGE 1_4 ..................\n";
    std::cout << "//=========================================================\n\n";

    std::string filename("encoded_4_170.txt");
    std::ifstream ifs(filename);
    std::vector<std::string> sources;
    if (!ifs.is_open()) { 
        std::cerr << "Could not open file: '" << filename << "'\n"; 
        exit(FILE_ERROR); 
    }

    std::string line;
    char buf[BUFSIZ];
    memset(buf, 0, BUFSIZ);
    while (ifs >> line) { 
        sources.push_back(line);
        // std::cout << "adding " << line << "\n";
    }
    ifs.close();

    unsigned char maxkey = '0';
    int index = 0, maxscore = 0;
    std::string message 
        = find_string_single_char_xor(sources, index, maxkey, maxscore);

    std::cout 
            << "\n\nSecret message at key: " << maxkey 
            << ", score is: " << maxscore 
            << ", index is: " << index 
            << ", message is: " << message << "\n\n";

    assert(message == std::string("Now that the party is jumping\n"));
    std::cout << "//=========================================================\n";
    std::cout << "// challenge 1_4 assertion passed...\n";
    std::cout << "//=========================================================\n\n";

    return 0;
}


int challenge_1_5() {
    std::cout << "\n//=========================================================\n";
    std::cout << "// CHALLENGE 1_5 ..................\n";
    std::cout << "//=========================================================\n\n";

    std::string src("Burning 'em, if you ain't quick and nimble\nI go crazy when I hear a cymbal");
    std::string repeating_key("ICE"), dst;


    std::string secret("Mr. and Mrs. Dursley, who lived at Number 4 Privet Drive, were proud to say "
                       "that they were perfectly normal, thank you very much. "
                       "They were the last people you would expect to find involved "
                       "in anything strange or mysterious, because they just didn't hold "
                       "with such nonsense.");
    std::string repeat("Ashurbanipal");
    std::string cipher;
    repeating_key_xor(secret, repeat, cipher);
    std::cout << "\nCIPHER TEXT: ";
    for (unsigned char c : cipher) { std::cout << c; }   std::cout << "\n";


    repeating_key_xor(src, repeating_key, dst);
    std::cout << "\nencrypted exercise: ";
    for (unsigned char c : dst) { std::cout << c; }   std::cout << "\n\n";

    assert(dst == std::string("0b3637272a2b2e63622c2e69692a23693a2a3c6324202d623d63343c2a26226324272765272a282b2f20430a652e2c652a3124333a653e2b2027630c692b20283165286326302e27282f"));
    std::cout << "//=========================================================\n";
    std::cout << "// challenge 1_5 assertion passed...\n";
    std::cout << "//=========================================================\n\n";
    
    return 0;
}


int challenge_1_6() {  
    std::string filename("encoded_1_6.txt");
    std::ifstream ifs(filename);
    std::string source;

    if (!ifs.is_open()) { 
        std::cerr << "Could not open file: '" << filename << "'\n"; 
        exit(FILE_ERROR); 
    }

    std::string line;
    while (ifs >> line) { 
        source += line;
        // std::cout << "adding " << line << "\n";
    }
    ifs.close();

    // std::cout << "ALL SOURCE is...\n" << source << "\n\n\n";
    
    test_get_repeating_key_xor(source);


    return 0; 
}

int challenge_1_7() {  return 0; }

int challenge_1_8() {  return 0;  }
