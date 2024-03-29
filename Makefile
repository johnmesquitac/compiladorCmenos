all: tokenizer parser build bin cod

tokenizer:
	flex cminus.l

parser:
	bison -d cminus.y

build:
	gcc -c *.c -fno-builtin-exp -Wno-implicit-function-declaration
	gcc *.o -lfl -o cminus -fno-builtin-exp

clean:
	rm -f cminus
	rm -f lex.yy.c
	rm -f *.o
	rm -f cminus.tab.*

bin:
	gcc binario.c -o binario

cod:
	./cminus Testes/teste11.c
	./binario Testes/teste11.tm > Testes/teste11.txt