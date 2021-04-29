rm input.txt
nasm -f elf CS19B074_A7.asm
ld -m elf_i386 -s CS19B074_A7.o io.o -o CS19B074
sudo ./CS19B074