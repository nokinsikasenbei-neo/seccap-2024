enc = "{tgkkWWHWSHSOdWTuJDTidhPuIHDbZdUt"
key = "vigenere"
table = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz{}_"

TABLE_SIZE = len(table)

def get_index(c):
    for i in range(TABLE_SIZE):
        if table[i] == c:
            return i
    return -1

def decrypt(enc, key):
    enc = list(enc)
    enc_len = len(enc)
    key_len = len(key)
    dec = [0] * enc_len
    
    for i, e in enumerate(enc):
        shift = table.find(e)
        index_flag = (shift - table.find(key[i % key_len])) % TABLE_SIZE
        dec[i] = table[index_flag]

    return ''.join(dec)

print(decrypt(enc, key))