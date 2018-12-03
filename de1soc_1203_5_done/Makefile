rle8: rle8_yhp.o cnt.o
	gcc -o rle8 rle8_yhp.o cnt.o
rle8_yhp.o: cnt.h ./RLE/rle8_yhp.c
	gcc -c -ggdb ./RLE/rle8_yhp.c
rle16: rle16_yhp.o cnt.o
	gcc -o rle16 rle16_yhp.o cnt.o
rle16_yhp.o: cnt.h ./RLE/rle16_yhp.c
	gcc -c -ggdb ./RLE/rle16_yhp.c
rle32: rle32_yhp.o cnt.o
	gcc -o rle32 rle32_yhp.o cnt.o
rle32_yhp.o: cnt.h ./RLE/rle32_yhp.c
	gcc -c -ggdb ./RLE/rle32_yhp.c

rld8: rld8_yhp.o cnt.o
	gcc -o rld8 rld8_yhp.o cnt.o
rld8_yhp.o: cnt.h ./RLD/rld8_yhp.c
	gcc -c -ggdb ./RLD/rld8_yhp.c
rld16: rld16_yhp.o cnt.o
	gcc -o rld16 rld16_yhp.o cnt.o
rld16_yhp.o: cnt.h ./RLD/rld16_yhp.c
	gcc -c -ggdb ./RLD/rld16_yhp.c
rld32: rld32_yhp.o cnt.o
	gcc -o rld32 rld32_yhp.o cnt.o
rld32_yhp.o: cnt.h ./RLD/rld32_yhp.c
	gcc -c -ggdb ./RLD/rld32_yhp.c

cnt.o: cnt.h cnt.c
	gcc -c -ggdb cnt.c

all:rle8 rle16 rle32 rld8 rld16 rld32
clean:
	rm -f *.o rle8 rle16 rle32 rld8 rld16 rld32
