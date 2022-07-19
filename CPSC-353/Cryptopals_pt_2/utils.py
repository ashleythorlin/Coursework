from binascii import hexlify
from base64 import b64decode
from itertools import combinations
from Crypto.Cipher import AES
from Crypto.Cipher.AES import block_size
from random import randint
from os import urandom




CHARACTER_FREQ = {
    'a': 0.0651738, 'b': 0.0124248, 'c': 0.0217339, 'd': 0.0349835, 'e': 0.1041442, 'f': 0.0197881, 'g': 0.0158610,
    'h': 0.0492888, 'i': 0.0558094, 'j': 0.0009033, 'k': 0.0050529, 'l': 0.0331490, 'm': 0.0202124, 'n': 0.0564513,
    'o': 0.0596302, 'p': 0.0137645, 'q': 0.0008606, 'r': 0.0497563, 's': 0.0515760, 't': 0.0729357, 'u': 0.0225134,
    'v': 0.0082903, 'w': 0.0171272, 'x': 0.0013692, 'y': 0.0145984, 'z': 0.0007836, ' ': 0.1918182
}


def get_english_score(input_bytes):
    score = 0

    for byte in input_bytes:
        score += CHARACTER_FREQ.get(chr(byte).lower(), 0)

    return score


def singlechar_xor(input_bytes, key_value):
    output = b''

    for char in input_bytes:
        output += bytes([char ^ key_value])

    return output


def singlechar_xor_brute_force(ciphertext):
    candidates = []

    for key_candidate in range(256):
        plaintext_candidate = singlechar_xor(ciphertext, key_candidate)
        candidate_score = get_english_score(plaintext_candidate)

        result = {
            'key': key_candidate,
            'score': candidate_score,
            'plaintext': plaintext_candidate
        }
        candidates.append(result)
    return sorted(candidates, key=lambda c: c['score'], reverse=True)[0]


#challenge 5

def repeating_key_xor(plaintext, key):
    ciphertext = b''
    i = 0

    for byte in plaintext:
        ciphertext += bytes([byte ^ key[i]])
        i = i + 1 if i < len(key) - 1 else 0

    return ciphertext 


#challenge 6

def hamming_distance(binary_seq_1, binary_seq_2): #computes hamming between two strings
    assert len(binary_seq_1) == len(binary_seq_2)
    dist = 0

    for bit1, bit2 in zip(binary_seq_1, binary_seq_2):
        diff = bit1 ^ bit2
        dist += sum([1 for bit in bin(diff) if bit == '1'])

    return dist


def break_repeating_key_xor(binary_data):
    normalized_distances = {}

    for key_size in range(2, 41):
        chunks = [binary_data[i:i + key_size] for i in range(0, len(binary_data), key_size)][:4]
        distance = 0
        pairs = combinations(chunks, 2)

        for (x, y) in pairs:
            distance += hamming_distance(x, y)

        distance /= 6
        normalized_distance = distance / key_size
        normalized_distances[key_size] = normalized_distance

    possible_key_sizes = sorted(normalized_distances, key=normalized_distances.get)[:3]
    possible_plaintexts = []

    for d in possible_key_sizes:
        key = b''

        for i in range(d):
            block = b''

            for j in range(i, len(binary_data), d):
                block += bytes([binary_data[j]])

            key += bytes([singlechar_xor_brute_force(block)['key']])
        possible_plaintexts.append((repeating_key_xor(binary_data, key), key))
    return max(possible_plaintexts, key=lambda k: get_english_score(k[0]))


#challenge 7

def aes_ecb_decrypt(data, key): #decrypts the given AES-ECB encrypted data with the given key
    cipher = AES.new(key, AES.MODE_ECB)
    return pkcs7_unpad(cipher.decrypt(data))


#challenge 8

def count_aes_ecb_repetitions(ciphertext): #counts the number of repeated chunks of the ciphertext
    chunks = [ciphertext[i:i + block_size] for i in range(0, len(ciphertext), block_size)]
    number_of_duplicates = len(chunks) - len(set(chunks))
    return number_of_duplicates


def detect_ecb_encrypted_ciphertext(ciphertexts): #determines ciphertext most likely encrypted with AES-ECB
    best = (-1, 0)     # index of best candidate, repetitions of best candidate

    # For each ciphertext
    for i in range(len(ciphertexts)):

        # count the block repetitions
        repetitions = count_aes_ecb_repetitions(ciphertexts[i])

        # keep ciphertext with most repetitions
        best = max(best, (i, repetitions), key=lambda t: t[1])

    return best


#challenge 9

def pkcs7_pad(message, block_size): #pads the input with the PKCS 7 padding format for block_size

    # if input length is already equal to block_size, no need to pad
    if len(message) == block_size:
        return message

    # compute the padding byte and return the padded message
    ch = block_size - len(message) % block_size
    return message + bytes([ch] * ch)


def is_pkcs7_padded(binary_data):   #determines if the data is PKCS 7 padded
    

    padding = binary_data[-binary_data[-1]:]

    return all(padding[b] == len(padding) for b in range(0, len(padding)))


def pkcs7_unpad(data): #unpads the given data from its PKCS 7 padding
    if len(data) == 0:
        raise Exception("The input data must contain at least one byte")

    if not is_pkcs7_padded(data):
        return data

    padding_len = data[len(data) - 1]
    return data[:-padding_len]

def pad(plaintext: bytes, block_size: int) -> bytes: #pads input
    padding = block_size - (len(plaintext) % block_size)
    return plaintext + bytes([padding]) * padding

def unpad(padded: bytes, block_size: int) -> bytes: #unpads input
    length = len(padded)
    if length % block_size:
        raise ValueError("Input data is not padded")
    if not _is_valid_padding(padded):
        raise ValueError("Not valid padding")
    return padded[:-padded[-1]]

def _is_valid_padding(padded: bytes) -> bool: #verifies padding
    pad = padded[-1]
    return padded[-pad:] == bytes([pad]) * pad


#challenge 10

def parse_input(filename):
    with open(filename) as f:
        data = f.read().replace('\n', '')

    return b64decode(data)


#challenge 11

class EncryptionOracleInterface:
    def encrypt(self, data: bytes) -> bytes:
        pass

class encryptionOracle11(EncryptionOracleInterface):
    def __init__(self):
        self.history = []
        self.key = urandom(16)

    def encrypt(self, data: bytes) -> bytes:
        pt = urandom(randint(5 ,10)) + data + urandom(randint(5 ,10))

        if randint(0 ,1):
            self.history.append('CBC')
            cipher = AES.new(self.key, AES.MODE_CBC)
        else:
            self.history.append('ECB')
            cipher = AES.new(self.key, AES.MODE_ECB)

        return cipher.encrypt(pad(pt, AES.block_size))

def ECB_CBC_detector(oracle: type[EncryptionOracleInterface]) -> str:
    data = b'A' * 48
    ct = oracle.encrypt(data)

    blocks = [ct[i: i +AES.block_size] for i in range(0, len(ct), AES.block_size)]

    return 'ECB' if len(blocks) != len(set(blocks)) else 'CBC'


#challenge 12

class encryptionOracle12(EncryptionOracleInterface):
    def __init__(self):
        self.key = urandom(16)
        self.cipher = AES.new(self.key, AES.MODE_ECB)
        self.secret = b64decode(
            'Um9sbGluJyBpbiBteSA1LjAKV2l0aCBteSByYWctdG9wIGRvd24gc28gbXkgaGFpciBjYW4gYmxvdwpUaGUgZ2lybGllcyBvbiBzdGFuZGJ5IHdhdmluZyBqdXN0IHRvIHNheSBoaQpEaWQgeW91IHN0b3A/IE5vLCBJIGp1c3QgZHJvdmUgYnkK')

    def encrypt(self, data: bytes) -> bytes:
        pt = data + self.secret

        return self.cipher.encrypt(pad(pt, AES.block_size))

def get_block_size(oracle: type[EncryptionOracleInterface]) -> int:
    test = b''
    base_len = len(oracle.encrypt(test))
    new_len = base_len

    while new_len == base_len:
        test += b'A'
        new_len = len(oracle.encrypt(test))

    return new_len - base_len

def recover_secret(oracle: type[EncryptionOracleInterface], secret_size: int) -> bytes:
    assert (ECB_CBC_detector(oracle) == 'ECB')

    feed = b'A' * secret_size
    recovered = b''
    for i in range(secret_size):
        pt = feed[:-i]
        ct = oracle.encrypt(pt)
        to_match = ct[:secret_size]
        for b in range(256):
            test = pt + recovered + bytes([b])
            if oracle.encrypt(test)[:secret_size] == to_match:
                recovered += bytes([b])
                break

    return recovered