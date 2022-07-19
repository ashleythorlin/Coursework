#include <iostream>
#include <string>
#include <vector>
#include <bitset>
#include <cassert>
#include <unordered_map>
#include <fstream>
#include <iomanip>
#include <array>
#include <functional>
#include <cstddef>
#include <unordered_set>
#include <sstream>


std::vector<std::byte> hex_str_to_bytes(std::string const& hex) {
	std::vector<std::byte> bytes;
	for (size_t i = 0; i < hex.size(); i += 2) {
		std::istringstream iss(hex.substr(i, 2));
		unsigned long b;
		iss >> std::hex >> b;
		bytes.push_back((std::byte) b);
	}
	return bytes;
}

// transform bytes into string with printed hex numbers
std::string bytes_to_hex_str(std::vector<std::byte> const& in) {
	std::stringstream result;
	for (auto const& elem : in)
		result << std::hex << std::setfill('0') << std::setw(2) << (int)elem;
	return result.str();
}

std::vector<std::byte> as_bytes(std::string const& in) {
	std::vector<std::byte> result;
	result.reserve(in.size());
	for (auto const& elem : in)
		result.push_back((std::byte) elem);
	return result;
}

std::string as_str(std::vector<std::byte> const& in) {
	std::string result;
	result.reserve(in.size());
	for (auto const& byte : in)
		result += (char)byte;
	return result;
}

// TASK 1 #######################################################################

const std::string base64_chars =
"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
"abcdefghijklmnopqrstuvwxyz"
"0123456789+/";

// parser-like approach to base64 encoding
std::string base64_encode(std::vector<std::byte> bytes) {
	std::stringstream buffer;
	int hexCounter = 0, octCounter = 0;
	size_t iter = 0;
	std::string hexBuffer;
	hexBuffer.resize(6);
	std::string result;

	while (true) {
		if (hexCounter == 0 && iter >= bytes.size()) {
			while (octCounter % 8 != 0) {
				octCounter += 6;
				result += '=';
			}
			break;
		}
		if (hexCounter < 6) {
			if (iter >= bytes.size()) { // last real char
				if (hexCounter != 0) {  // some data, pad with zeros
					int fpad = 6 - hexCounter;
					for (int i = 0; i < fpad; ++i) buffer << '0';
					hexCounter += fpad;
					octCounter += fpad;
				}
			}
			else {
				buffer << std::bitset<8>((unsigned char)bytes[iter]).to_string();
				hexCounter += 8;
				octCounter += 8;
				++iter;
			}
		}
		buffer.read(&hexBuffer[0], 6);
		result += base64_chars[std::stoi(hexBuffer, nullptr, 2)];
		hexCounter -= 6;
	}
	return result;
}

char base64_to_index(char in) {
	// TODO resolve integral promotions warnings
	if (in >= 65 && in <= 90)       // from A to Z
		return in - 65;             // map to 0-25
	else if (in >= 97 && in <= 122) // from a to z
		return in - 97 + 26;        // map to 26-51
	else if (in >= 48 && in <= 57)  // from 0 to 9
		return in - 48 + 52;        // map to 52-61
	else if (in == 43)                    // for +
		return 62;
	else if (in == 47)                    // for /
		return 63;
	else throw std::runtime_error("unexpected base64 character");
}

std::vector<std::byte> base64_decode(std::string in) {
	std::stringstream buffer;
	int octCounter = 0;
	std::string octBuffer;
	octBuffer.resize(8);
	std::vector<std::byte> result;
	int iter = 0;
	bool must_end = false;

	while (true) {
		if (iter >= in.size() || in.at(iter) == '=') {
			break;
		}
		while (octCounter < 8) {
			if (iter >= in.size() || in.at(iter) == '=') {
				must_end = true;
			}
			buffer << std::bitset<6>((unsigned char)base64_to_index(in.at(iter)));
			++iter;
			octCounter += 6;
		}
		if (must_end) break;
		buffer.read(&octBuffer[0], 8);
		result.push_back(static_cast<std::byte>(std::stoi(octBuffer, nullptr, 2)));
		octCounter -= 8;
	}
	return result;
}

std::string hex_str_to_base64(std::string const& in) {
	return base64_encode(hex_str_to_bytes(in));
}

std::string base64_to_hex_str(std::string const& in) {
	return bytes_to_hex_str(base64_decode(in));
}

// TASK 2 #######################################################################

std::string fixed_length_xor(std::string const& hexA, std::string const& hexB) {
	std::stringstream result;
	std::vector<std::byte> a = hex_str_to_bytes(hexA), b = hex_str_to_bytes(hexB);
	for (int i = 0; i < a.size(); ++i) {
		result << std::hex << static_cast<int>(a[i] ^ b[i]);
	}
	return result.str();
}

// TASK 3 #######################################################################

std::vector<std::byte> single_byte_xor_decode(std::vector<std::byte> const& bytes, std::byte const key) {
	std::vector<std::byte> result;
	result.reserve(bytes.size());
	for (auto const& elem : bytes) result.push_back(elem ^ key);
	return result;
}

std::vector<std::byte> single_byte_xor_decode_hex(std::vector<std::byte> const& hex, std::byte const key) {
	return single_byte_xor_decode(hex_str_to_bytes(as_str(hex)), key);
}


// TASK 4 #######################################################################

// data is taken from http://www.data-compression.com/english.html
const std::unordered_map<char, double> english_letter_frequencies{
		{'a', 0.0651738},
		{'b', 0.0124248},
		{'c', 0.0217339},
		{'d', 0.0349835},
		{'e', 0.1041442},
		{'f', 0.0197881},
		{'g', 0.0158610},
		{'h', 0.0492888},
		{'i', 0.0558094},
		{'j', 0.0009033},
		{'k', 0.0050529},
		{'l', 0.0331490},
		{'m', 0.0202124},
		{'n', 0.0564513},
		{'o', 0.0596302},
		{'p', 0.0596302},
		{'q', 0.0008606},
		{'r', 0.0497563},
		{'s', 0.0515760},
		{'t', 0.0729357},
		{'u', 0.0225134},
		{'v', 0.0082903},
		{'w', 0.0171272},
		{'x', 0.0013692},
		{'y', 0.0145984},
		{'z', 0.0007836},
		{' ', 0.1918182}
};

// rate string based on english letter frequencies, better rating is greater
double rate_english_frequency(std::string const& in) {
	double result = 0;
	for (auto const& elem : in)
		if (english_letter_frequencies.find(std::tolower(elem)) != english_letter_frequencies.end())
			result += english_letter_frequencies.at(std::tolower(elem));
	return result;
}

std::byte brute_single_byte_xor(std::vector<std::byte> const& in,
	std::function<std::vector<std::byte>(std::vector<std::byte>,
		std::byte)> const& decode = single_byte_xor_decode) {
	std::string curr_guess;
	double max_rating = 0, curr_rating;
	unsigned char best_key = 0;
	for (unsigned k = 0; k <= 255; k += 1) {
		curr_guess = as_str(decode(in, (std::byte) k));
		curr_rating = rate_english_frequency(curr_guess);
		if (curr_rating > max_rating) {
			max_rating = curr_rating;
			best_key = k;
		}
	}
	return (std::byte) best_key;
}

std::byte brute_single_byte_xor_hex(std::vector<std::byte> const& in) {
	return brute_single_byte_xor(in, single_byte_xor_decode_hex);
}

void task_4() {
	std::string line;
	std::fstream infile("set_1_src/task4.txt", std::ios::in);

	std::string best_guess, curr_guess;
	double max_rating = 0, curr_rating;

	while (getline(infile, line)) {
		std::byte key = brute_single_byte_xor_hex(as_bytes(line));
		curr_guess = as_str(single_byte_xor_decode_hex(as_bytes(line), key));
		curr_rating = rate_english_frequency(curr_guess);
		if (curr_rating > max_rating) {
			max_rating = curr_rating;
			best_guess = curr_guess;
		}
	}
	std::cout << "Task 4 (best guess): " << best_guess << std::endl;
}

int main(int argc, const char* argv[]) {

    task_4();

    return 0;

}