from utils import *

def chal6():
    print("\n\n - - - CHALLENGE 6 - - -\n")

    with open("chal6.txt") as input_file:
        data = b64decode(input_file.read())

    result = break_repeating_key_xor(data)
    print("Key =", result[1].decode())
    print("---------------------------------------")
    print(result[0].decode().rstrip())

def chal7():
    print("\n\n - - - CHALLENGE 7 - - -\n")
    with open("chal7.txt") as input_file:
        binary_data = b64decode(input_file.read())

    print(aes_ecb_decrypt(binary_data, b'YELLOW SUBMARINE').decode().rstrip())

def chal8():
    print("\n\n - - - CHALLENGE 8 - - -\n")
    ciphertexts = [bytes.fromhex(line.strip()) for line in open("chal8.txt")]
    result = detect_ecb_encrypted_ciphertext(ciphertexts)

    print(ciphertexts[result[0]])

def chal9():
    print("\n\n - - - CHALLENGE 9 - - -\n")
    example = b"YELLOW SUBMARINE"
    ans = b"YELLOW SUBMARINE\x04\x04\x04\x04"

    result = pad(example, 20)
    print(f"Result: {result}")

    result = unpad(result, 20)
    print(f"Result: {result}")

def chal10():
    print("\n\n - - - CHALLENGE 10 - - -\n")
    key = b'YELLOW SUBMARINE'
    four = b'\x00' * 16
    cipher = AES.new(key, AES.MODE_CBC, four)

    ct = parse_input('chal10.txt')
    pt = unpad(cipher.decrypt(ct), AES.block_size)

    print(pt.decode())

def chal11():
    print("\n\n - - - CHALLENGE 11 - - -\n")
    oracle = encryptionOracle11()
    detections = []

    for _ in range(10):
        detections.append(ECB_CBC_detector(oracle))

    print(f"Actual: {oracle.history}\nExpected: {detections}")

def chal12():
    print("\n\n - - - CHALLENGE 12 - - -\n")
    oracle = encryptionOracle12()
    secret_size = len(oracle.encrypt(b''))
    secret = recover_secret(oracle, secret_size)

    print(secret.decode())
