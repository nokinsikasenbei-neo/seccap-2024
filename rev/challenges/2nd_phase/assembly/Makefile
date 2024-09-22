# TARGET = file/encrypter

# ASM_SRC = src/main.asm

# OBJ = file/encrypter.o

# NASM = nasm
# NASMFLAGS = -f elf32

# LD = ld
# LDFLAGS = -m elf_i386

# all: $(TARGET)

# $(OBJ): $(ASM_SRC)
# 	$(NASM) $(NASMFLAGS) -o $(OBJ) $(ASM_SRC)

# $(TARGET): $(OBJ)
# 	$(LD) $(LDFLAGS) -o $(TARGET) $(OBJ)

TARGET32 = file/encrypter32
TARGET64 = file/encrypter64

ASM_SRC_32 = src/main32.asm
ASM_SRC_64 = src/main64.asm

OBJ32 = file/encrypter32.o
OBJ64 = file/encrypter64.o

NASM = nasm

# 32bit用フラグ
NASMFLAGS32 = -f elf32
LDFLAGS32 = -m elf_i386

# 64bit用フラグ
NASMFLAGS64 = -f elf64
LDFLAGS64 = -m elf_x86_64

# 両方のバイナリをビルド
all: $(TARGET32) $(TARGET64)

# 32bitオブジェクトファイルの生成
$(OBJ32): $(ASM_SRC_32)
	$(NASM) $(NASMFLAGS32) -o $(OBJ32) $(ASM_SRC_32)

# 64bitオブジェクトファイルの生成
$(OBJ64): $(ASM_SRC_64)
	$(NASM) $(NASMFLAGS64) -o $(OBJ64) $(ASM_SRC_64)

# 32bitターゲットのビルド
$(TARGET32): $(OBJ32)
	$(LD) $(LDFLAGS32) -o $(TARGET32) $(OBJ32)

# 64bitターゲットのビルド
$(TARGET64): $(OBJ64)
	$(LD) $(LDFLAGS64) -o $(TARGET64) $(OBJ64)