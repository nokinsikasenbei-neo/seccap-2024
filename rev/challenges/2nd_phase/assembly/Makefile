TARGET = file/encrypter
ASM_SRC_64 = src/main64.asm
OBJ64 = file/encrypter64.o
NASM = nasm

# 64bit用フラグ
NASMFLAGS64 = -f elf64
LDFLAGS64 = -m elf_x86_64

# 両方のバイナリをビルド
all: $(TARGET)

# 64bitオブジェクトファイルの生成
$(OBJ64): $(ASM_SRC_64)
	$(NASM) $(NASMFLAGS64) -o $(OBJ64) $(ASM_SRC_64)

# 64bitターゲットのビルド
$(TARGET): $(OBJ64)
	$(LD) $(LDFLAGS64) -o $(TARGET) $(OBJ64)

clean:
	rm -f $(OBJ64)