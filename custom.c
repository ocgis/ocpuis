#include "sysconfig.h"
#include "sysdeps.h"

uae_u16 intena,intreq;
unsigned long cycles;

int intlev (void)
{
    uae_u16 imask = intreq & intena;
    if (imask && (intena & 0x4000)){
        if (imask & 0x2000) return 6;
        if (imask & 0x1800) return 5;
        if (imask & 0x0780) return 4;
        if (imask & 0x0070) return 3;
        if (imask & 0x0008) return 2;
        if (imask & 0x0007) return 1;
    }
    return -1;
}

