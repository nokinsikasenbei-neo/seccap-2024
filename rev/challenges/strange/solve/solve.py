enc = [0x4e, 0x54, 0x49, 0x4f, 0x83, 0x3d, 0x3f, 0x3b, 0x7a, 0x3c, 0x76, 0x6f, 0x3b, 0x67, 0x7f, 0x39, 0x3f, 0x70, 0x38, 0x7d, 0x3f, 0x67, 0x3d, 0x81, 0x75, 0x6a, 0x38, 0x74, 0x3d, 0x85]

print("".join(chr(e - 0x8) for e in enc))