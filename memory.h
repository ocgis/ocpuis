 /*
  * UAE - The Un*x Amiga Emulator
  *
  * memory management
  *
  * Copyright 1995 Bernd Schmidt
  */

#include "maccess.h"

static __inline__ uae_u32 get_long(uaecptr addr)
{
    return 0;
}
static __inline__ uae_u32 get_word(uaecptr addr)
{
    return 0;
}
static __inline__ uae_u32 get_byte(uaecptr addr)
{
    return 0;
}
static __inline__ void put_long(uaecptr addr, uae_u32 l)
{
    return;
}
static __inline__ void put_word(uaecptr addr, uae_u32 w)
{
    return;
}
static __inline__ void put_byte(uaecptr addr, uae_u32 b)
{
    return;
}

static __inline__ uae_u8 *get_real_address(uaecptr addr)
{
    return NULL;
}

static __inline__ int valid_address(uaecptr addr, uae_u32 size)
{
    return 0;
}
