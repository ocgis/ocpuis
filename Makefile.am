lib_LTLIBRARIES = libocpuis.la

CORESRCS = cpuemu1.c cpuemu2.c cpuemu3.c cpuemu4.c cpuemu5.c cpuemu6.c cpuemu7.c cpuemu8.c

libocpuis_la_SOURCES = $(CORESRCS) readcpu.c newcpu.c missing.c support.c \
	fpp.c cpudefs.c cpustbl.c custom.c init.c memory.c

include_HEADERS = ocpuis.h

noinst_PROGRAMS = build68k gencpu sampleprog

build68k_SOURCES = build68k.c

gencpu_SOURCES = gencpu.c readcpu.c cpudefs.c missing.c

sampleprog_SOURCES = sampleprog.c

sampleprog_LDADD = ./libocpuis.la

cpudefs.c: build68k table68k
	./build68k < table68k >cpudefs.c

$(CORESRCS) cpustbl.c cpustbl.h: gencpu
	./gencpu

# gencpu also creates cpustbl.c and cputbl.h
cpustbl.c: $(CORESRCS)
cputbl.h: $(CORESRCS)

