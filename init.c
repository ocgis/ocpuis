#include "sysconfig.h"
#include "sysdeps.h"

#include "ocpuis.h"
#include "custom.h"
#include "readcpu.h"
#include "options.h"
#include "memory.h"
#include "newcpu.h"

CPU *CPUtemplate(void)
{
  CPU *tpl;

  tpl = (CPU *)calloc(sizeof(CPU),1);
  
  return tpl;
}

CPU *CPUsimple_template(CPUaddr pc, CPUaddr sp, CPUword sr)
{
  CPU *tpl;
  
  tpl = CPUtemplate();

  if(!tpl)
    return NULL;

  tpl->init_areg[7] = sp;
  tpl->init_pc = pc;
  tpl->init_sr = sr;
  
  return tpl;
}

int CPUinit(CPU *data)
{
  int r;

  init_m68k();

  if(!data)
    return -42;

  for(r=0;r<8;r++) {
    m68k_dreg(regs, r) = data->init_dreg[r];
    m68k_areg(regs, r) = data->init_areg[r];
  }

  if(!data->get_byte) {
    free(data);
    return -1;
  }
  CPUset_func_get_byte(data->get_byte);

  if(!data->get_byte) {
    free(data);
    return -2;
  }
  CPUset_func_get_word(data->get_word);

  if(!data->get_byte) {
    free(data);
    return -3;
  }
  CPUset_func_get_long(data->get_long);

  if(!data->get_byte) {
    free(data);
    return -4;
  }
  CPUset_func_put_byte(data->put_byte);

  if(!data->get_byte) {
    free(data);
    return -5;
  }
  CPUset_func_put_word(data->put_word);

  if(!data->get_byte) {
    free(data);
    return -6;
  }
  CPUset_func_put_long(data->put_long);

  if(!data->get_byte) {
    free(data);
    return -7;
  }
  CPUset_func_real_addr(data->real_addr);

  if(!data->get_byte) {
    free(data);
    return -8;
  }
  CPUset_func_valid_addr(data->valid_addr);
  
  CPUset_pc(data->init_pc);
  CPUset_msp(data->init_msp);
  CPUset_isp(data->init_isp);
  CPUset_usp(data->init_usp);
  CPUset_sr(data->init_sr);

  free(data);

  return 0;
}

int CPUrun(void)
{
  m68k_go(0);
}

void CPUset_pc(CPUaddr pc)
{
  m68k_setpc(pc);
}

CPUaddr CPUget_pc(void)
{
  return m68k_getpc();
}

void CPUset_sr(CPUword sr)
{
  regs.sr = sr;
  MakeFromSR();
}

CPUword CPUget_sr(void)
{
  return regs.sr;
}

void CPUset_usp(CPUaddr usp)
{
  regs.usp = usp;
}

CPUaddr CPUget_usp(void)
{
  return regs.usp;
}

void CPUset_isp(CPUaddr isp)
{
  regs.isp = isp;
}

CPUaddr CPUget_isp(void)
{
  return regs.isp;
}

void CPUset_msp(CPUaddr msp)
{
  regs.msp = msp;
}

CPUaddr CPUget_msp(void)
{
  return regs.msp;
}

void CPUset_dreg(int r, CPUlong value)
{
  m68k_dreg(regs, r) = value;
}

CPUlong CPUget_dreg(int r)
{
  return m68k_dreg(regs, r);
}

void CPUset_areg(int r, CPUlong value)
{
  m68k_areg(regs, r) = value;
}

CPUlong CPUget_areg(int r)
{
  return m68k_areg(regs, r);
}

