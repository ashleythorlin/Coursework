// run_length_encode(S):
//     C = ""
//     if S is empty:
//         return C
//     run_char = S[0]
//     run_length = 1
//     for each character c in S after the first:
//            if c == run_char:
//                run_length++
//            else:
//                append_run(C, run_char, run_length)
//                run_char = c
//                run_length = 1
//     append_run(C, run_char, run_length)
//     return C

// append_run(C, run_char, run_length):
//     if run_length > 1:
//         C.append(convert_to_string(run_length))
//     C.append(run_char)

#include <iostream>
#include <string>

std::string run_length_encode(const std::string& uncompressed) {

    std::string C = "";
    if (uncompressed == "" || uncompressed.empty()){
        return C;
    }
    char run_char = uncompressed[0];

    int run_length = 1;
    for(int i = 1; i < uncompressed.length(); i++) {
        if(isupper(run_char) || ispunct(run_char) || isdigit(run_char)){
          throw std::invalid_argument("Invalid characters");
        }
        if(uncompressed[i] == run_char){
            run_length++;
        } else {
          if(run_length > 1){
              C += std::to_string(run_length);
          }
          C.push_back(run_char);
            run_char = uncompressed[i];
            run_length = 1;
        }
    }
    if(isupper(run_char) || ispunct(run_char) || isdigit(run_char)){
      throw std::invalid_argument("Invalid characters");
    }
    if(run_length > 1){
        C += std::to_string(run_length);
    }
    C.push_back(run_char);
    std::cout << C;
    return C;
  }



int main(){
    std::string input[3] = {"aaa", "heloooooooo there", "footloose and fancy free"};
    for(int i = 0; i < 3; i++){
        std::cout << "Input: " << input[i] << "\n";
        std::cout << "Output: " << run_length_encode(input[i]) << "\n";
    }
    return 0;
}