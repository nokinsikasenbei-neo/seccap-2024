enc = [0xa4, 0x48,0x71,0x28,0x57,0x76,0x2b,0x82,0x5c,0x42,0xa6,0x40,0x60]

with open("../file/bin", "rb") as f:
    i = 0
    data = f.read(2)
    while data:
        if data[0] == 0x00:
            enc[i] -= data[1]
        elif data[0] == 0x01:
            enc[i] += data[1]
        elif data[0] == 0x02:
            enc[i] ^= data[1]
        data = f.read(2)
        i += 1

print("".join([chr(i) for i in enc]))
