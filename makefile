# SPITBOL makefile using nasm

ws?=64

debug?=0

os?=unix

OS=$(os)
WS=$(ws)
DEBUG=$(debug)

CC=gcc
ELF=elf$(WS)


ifeq	($(DEBUG),0)
CFLAGS= -D m64 -m64 -static 
else
CFLAGS= -D m64 -g -m64
endif

# Assembler info 
# Assembler
ASM=nasm
ifeq	($(DEBUG),0)
ASMFLAGS = -f $(ELF) -d m64
else
ASMFLAGS = -g -f $(ELF) -d m64
endif

# Tools for processing Minimal source file.
BASEBOL =   ./bin/sbl
# Objects for SPITBOL's LOAD function.  AIX 4 has dlxxx function library.
#LOBJS=  load.o
#LOBJS=  dlfcn.o load.o
LOBJS=

spitbol: sbl csbl


#	rm sbl sbl.lex sbl.s sbl.err err.asm
sbl:	err.o int.o sbl.o
#stop:
	$(CC) $(CFLAGS) -c osint/*.c
	$(CC) $(CFLAGS) *.o -osbl -lm
	
# link spitbol with dynamic linking


sbl.lex:	sbl.min
	$(BASEBOL) lex.sbl 

sbl.asm:	sbl.lex
	$(BASEBOL) -x asm.sbl
	
err.asm:	err.sbl sbl.asm
	$(BASEBOL) -x -1=sbl.err -2=err.asm err.sbl

err.o:	err.asm
	$(ASM) $(ASMFLAGS) err.asm

int.o:	int.asm
	$(ASM) $(ASMFLAGS) int.asm

sbl.o:	sbl.asm
	$(ASM) $(ASMFLAGS) sbl.asm







csbl:	sbl osint/gen_code_c.h
	$(BASEBOL) -x cgen.sbl
	
	cd cosint; \
	  pwd; \
	  $(CC) $(CFLAGS) -DGEN_C_CODE=1 -c ../osint/*.c
	
	$(CC) $(CFLAGS) -o csbl -Iosint cosint/*.o  -lm

cosint/cerr.c:	err.asm

osint/gen_code_c.h:  osint/gen_c_code_head_fragment.h osint/gen_c_code_tail_fragment.h cosint/csbl.c
	$(BASEBOL) cs_c_to_gen_c_code.sbl <cosint/csbl.c >tempad
	cat >osint/gen_code_c.h  osint/gen_c_code_head_fragment.h  tempad osint/gen_c_code_tail_fragment.h
	rm  tempad
			

spitbol-dynamic: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -osbl -lm 

sbl.go:	sbl.lex go.sbl
	$(BASEBOL) -x -u i32 go.sbl


# install binaries from ./bin as the system spitbol compilers
install:
	sudo cp ./bin/sbl /usr/local/bin
clean:
	rm -f  *.o *.lst *.map *.err err.lex sbl.lex sbl.err sbl.asm err.asm ./sbl  

z:
	nm -n sbl.o >s.nm
	sbl map-$(WS).sbl <s.nm >s.dic
	sbl z.sbl <ad >ae

sclean:
# clean up after sanity-check
	make clean
	rm tbol*
