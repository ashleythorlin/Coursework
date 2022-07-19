#include <cstdlib>
#include <iostream>
#include <iomanip>

#include "challenges_1.h"
#include "utils.h"




void run_conversion_tests() { 
  // test_hex_decode();
  // test_hex_encode();

  // test_toascii();
  // test_to_base64_from_word();   
  // test_to_base64_from_string(); 
  
  // test_tobase64();
  // test_to_ascii_from_word();
  // test_to_ascii_from_string();

  // test_count_one_bits();

  // test_hamming_distance();

  // test_best_keysize_hamming_distance();
  // test_transpose_blocks();

  // test_get_repeating_key_xor();


  // challenge_1_1();
  // challenge_1_2();
  // challenge_1_3();
  // challenge_1_4();
  // challenge_1_5(); 

    challenge_1_6();

  exit(-1);
}

 
int main(int argc, const char* argv[]) {

   run_conversion_tests();


   if (argc != 2) {
     std::cerr << "Usage: ./main <1-5>\n";
     exit(-1);
   }
   int choice = atoi(argv[1]);

   switch(choice) {
     case 1:  challenge_1_1();  break;
     case 2:  challenge_1_2();  break;
     case 3:  challenge_1_3();  break;
     case 4:  challenge_1_4();  break;
     case 5:  challenge_1_5();  break;

     case 6:  challenge_1_6();  break; 
    //  case 7:  challenge_1_7();  break;
    //  case 8:  challenge_1_8();  break;


     default: std::cerr << "Error -- choice " << choice << "not recognized\n";  break;
   }


  return 0;
}
