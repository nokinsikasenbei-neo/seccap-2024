def rol(n):
    return ((n << 1) & 255) | (n >> 7)

with open("../file/encrypted_flag.txt", "rb") as f:
    read_data = bytearray(f.read())

print("".join(chr(rol(b) - 3) for b in read_data))