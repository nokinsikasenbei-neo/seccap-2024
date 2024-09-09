TARGET = file/encrypter

ASM_SRC = src/main.asm

OBJ = file/encrypter.o

NASM = nasm
NASMFLAGS = -f elf32

LD = ld
LDFLAGS = -m elf_i386

all: $(TARGET)

$(OBJ): $(ASM_SRC)
	$(NASM) $(NASMFLAGS) -o $(OBJ) $(ASM_SRC)

$(TARGET): $(OBJ)
	$(LD) $(LDFLAGS) -o $(TARGET) $(OBJ)
