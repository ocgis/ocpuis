#include "sysconfig.h"
#include "sysdeps.h"

#include "ocpuis.h"
#include "memory.h"

struct sMem memory;

void CPUset_func_get_byte(CPUbyte (*func)(CPUaddr))
{
  memory.getb = func;
}

void CPUset_func_get_word(CPUword (*func)(CPUaddr))
{
  memory.getw = func;
}

void CPUset_func_get_long(CPUlong (*func)(CPUaddr))
{
  memory.getl = func;
}

void CPUset_func_put_byte(void (*func)(CPUaddr, CPUbyte))
{
  memory.putb = func;
}

void CPUset_func_put_word(void (*func)(CPUaddr, CPUword))
{
  memory.putw = func;
}

void CPUset_func_put_long(void (*func)(CPUaddr, CPUlong))
{
  memory.putl = func;
}

void CPUset_func_real_addr(void *(*func)(CPUaddr))
{
  memory.real_addr = func;
}

void CPUset_func_valid_addr(int (*func)(CPUaddr, CPUlong))
{
  memory.valid_addr = func;
}
