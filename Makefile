#
# Makefile.in for UAE
#

OBJS = readcpu.o newcpu.o missing.o support.o fpp.o cpudefs.o cpustbl.o custom.o
LIBS = -lm

CFLAGS=-g


all: main

clean:
	-rm -f $(OBJS) *~ *.o main build68k gencpu 
	-rm -f cpuemu.c cpustbl.c cputbl.h cpudefs.c

build68k: build68k.o
	$(CC) $(LDFLAGS) -o build68k build68k.o
gencpu: gencpu.o readcpu.o cpudefs.o missing.o
	$(CC) $(LDFLAGS) -o gencpu gencpu.o readcpu.o missing.o cpudefs.o

cpudefs.c: build68k table68k
	./build68k < table68k >cpudefs.c

cpuemu.c: gencpu
	./gencpu

# gencpu also creates cpustbl.c and cputbl.h
cpustbl.c: cpuemu.c
cputbl.h: cpuemu.c

.c.o:
	$(CC) $(INCLUDES) -c $(INCDIRS) $(CFLAGS) $(X_CFLAGS) $(DEBUGFLAGS) $< -o $@
.c.s:
	$(CC) $(INCLUDES) -S $(INCDIRS) $(CFLAGS) $(X_CFLAGS) $(DEBUGFLAGS) $< -o $@
.c.i:
	$(CC) $(INCLUDES) -E $(INCDIRS) $(CFLAGS) $(X_CFLAGS) $(DEBUGFLAGS) $< > $@
.S.o:
	$(CC) $(INCLUDES) -c $(INCDIRS) $(CFLAGS) $(X_CFLAGS) $(DEBUGFLAGS) $< -o $@
.s.o:
	$(CC) $(INCLUDES) -c $(INCDIRS) $(CFLAGS) $(X_CFLAGS) $(DEBUGFLAGS) $< -o $@

build68k.o: readcpu.h
readcpu.o: readcpu.h
newcpu.o: config.h events.h
support.o: m68k.h
main: main.o $(OBJS)
	$(CC) $(CFLAGS) -o $@ main.o $(OBJS) $(LIBS)

