#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include "ocpuis.h"

#define DEBUG fprintf(stderr, "Got to line: %d\n", __LINE__)

#define MEMSIZE 1000000
#define DATAOFFSET 100000

typedef struct {
  int size;
  int dataoffset;
  int memsize;
  unsigned char *data;
  unsigned char *memstart;
} afile;

afile *prg;

afile *load_file(char *name)
{
  static afile f;
  struct stat st;
  int fd;

  stat(name, &st);
  
  f.size = st.st_size;
  f.dataoffset = DATAOFFSET;
  f.memsize = MEMSIZE;
  f.memstart = (unsigned char *) malloc(f.memsize);
  f.data = f.memstart + f.dataoffset;

  fd = open(name, O_RDONLY);

  read(fd, f.data, f.size);

  close(fd);
  
  return &f;
}

CPUbyte my_get_byte(CPUaddr addr)
{
  return *((CPUbyte *)(addr + prg->memstart));
}

CPUword my_get_word(CPUaddr addr)
{
  return *((CPUword *)(addr + prg->memstart));
}

CPUlong my_get_long(CPUaddr addr)
{
  return *((CPUlong *)(addr + prg->memstart));
}

void my_put_byte(CPUaddr addr, CPUbyte value)
{
  *((CPUbyte *)(addr + prg->memstart)) = value;
}

void my_put_word(CPUaddr addr, CPUword value)
{
  *((CPUword *)(addr + prg->memstart)) = value;
}

void my_put_long(CPUaddr addr, CPUlong value)
{
  *((CPUlong *)(addr + prg->memstart)) = value;
}

void *my_real_addr(CPUaddr addr)
{
  return (void *)(addr + prg->memstart);
}

int my_valid_addr(CPUaddr addr, CPUlong size)
{
  if((addr < 0) || (addr+size > prg->memsize))
    return 0;
  else
    return 1;
}

void my_handle_exception(int nr, CPUaddr oldpc)
{
  fprintf(stderr, "An exception %d occured\n", nr);
  exit(-1);
}

void fill_template(CPU *cpu)
{
  cpu->get_byte = my_get_byte;
  cpu->get_word = my_get_word;
  cpu->get_long = my_get_long;
  cpu->put_byte = my_put_byte;
  cpu->put_word = my_put_word;
  cpu->put_long = my_put_long;
  cpu->real_addr = my_real_addr;
  cpu->valid_addr = my_valid_addr;
  cpu->handle_exception = my_handle_exception;
}

int main(int argc, char *argv[])
{
  CPU *cpu;

  prg = load_file(argv[1]);

  cpu = CPUsimple_template((CPUaddr) (prg->data - prg->memstart),
			   (CPUaddr) (prg->memstart + prg->memsize - 60000),
			   0);

  fill_template(cpu);

  CPUinit(cpu);
  CPUrun();

  return 0;
}


