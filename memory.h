 /*
  * UAE - The Un*x Amiga Emulator
  *
  * memory management
  *
  * Copyright 1995 Bernd Schmidt
  */

#include "ocpuis.h"
#include "maccess.h"

extern struct sMem {

  CPUbyte (*getb) (CPUaddr addr);
  CPUword (*getw) (CPUaddr addr);
  CPUlong (*getl) (CPUaddr addr);

  void (*putb) (CPUaddr addr, CPUbyte value);
  void (*putw) (CPUaddr addr, CPUword value);
  void (*putl) (CPUaddr addr, CPUlong value);

  void *(*real_addr) (CPUaddr addr);
  int (*valid_addr) (CPUaddr addr, CPUlong size);
  void (*handle_exception) (int, CPUaddr);

} memory;

static __inline__ uae_u32 get_long(uaecptr addr)
{
    return (uae_u32) memory.getl((CPUaddr) addr);
}
static __inline__ uae_u32 get_word(uaecptr addr)
{
    return (uae_u32) memory.getw((CPUaddr) addr);
}
static __inline__ uae_u32 get_byte(uaecptr addr)
{
    return (uae_u32) memory.getb((CPUaddr) addr);
}
static __inline__ void put_long(uaecptr addr, uae_u32 l)
{
    memory.putl((CPUaddr) addr, (CPUlong) l);
    return;
}
static __inline__ void put_word(uaecptr addr, uae_u32 w)
{
    memory.putw((CPUaddr) addr, (CPUword) w);
    return;
}
static __inline__ void put_byte(uaecptr addr, uae_u32 b)
{
    memory.putb((CPUaddr) addr, (CPUbyte) b);
    return;
}

static __inline__ uae_u8 *get_real_address(uaecptr addr)
{
    return (uae_u8 *) memory.real_addr(addr);
}

static __inline__ int valid_address(uaecptr addr, uae_u32 size)
{
    return memory.valid_addr(addr, size);
}

static __inline__ void handle_exception(int nr, CPUaddr oldpc)
{
    memory.handle_exception(nr, oldpc);
}

void CPUset_func_get_byte(CPUbyte (*)(CPUaddr));
void CPUset_func_get_word(CPUword (*)(CPUaddr));
void CPUset_func_get_long(CPUlong (*)(CPUaddr));
void CPUset_func_put_byte(void (*)(CPUaddr, CPUbyte));
void CPUset_func_put_word(void (*)(CPUaddr, CPUword));
void CPUset_func_put_long(void (*)(CPUaddr, CPUlong));
void CPUset_func_real_addr(void *(*)(CPUaddr));
void CPUset_func_valid_addr(int (*)(CPUaddr, CPUlong));
void CPUset_func_handle_exception(void (*)(int, CPUaddr));
