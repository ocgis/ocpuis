#
# Makefile.in for UAE
#

OBJS = readcpu.o newcpu.o missing.o support.o fpp.o cpudefs.o cpustbl.o custom.o
LIBS = -lm
CORESRCS = cpuemu1.c cpuemu2.c cpuemu3.c cpuemu4.c cpuemu5.c cpuemu6.c cpuemu7.c cpuemu8.c
COREOBJS = cpuemu1.o cpuemu2.o cpuemu3.o cpuemu4.o cpuemu5.o cpuemu6.o cpuemu7.o cpuemu8.o

CFLAGS=-g


all: main

clean:
	-rm -f $(OBJS) *~ *.o main build68k gencpu 
	-rm -f $(CORESRCS) cpustbl.c cputbl.h cpudefs.c

build68k: build68k.o
	$(CC) $(LDFLAGS) -o build68k build68k.o
gencpu: gencpu.o readcpu.o cpudefs.o missing.o
	$(CC) $(LDFLAGS) -o gencpu gencpu.o readcpu.o missing.o cpudefs.o

cpudefs.c: build68k table68k
	./build68k < table68k >cpudefs.c

$(CORESRCS): gencpu
	./gencpu

# gencpu also creates cpustbl.c and cputbl.h
cpustbl.c: $(CORESRCS)
cputbl.h: $(CORESRCS)

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
main: main.o $(OBJS) $(COREOBJS)
	$(CC) $(CFLAGS) -o $@ main.o $(OBJS) $(COREOBJS) $(LIBS)

