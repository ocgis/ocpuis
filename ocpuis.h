#ifndef _OCPUIS_H_
#define _OCPUIS_H_

typedef unsigned char CPUbyte;
typedef unsigned short CPUword;
typedef unsigned long CPUlong;

typedef CPUlong CPUaddr;

typedef struct sCPU {

  /* Initialisation */

  CPUaddr init_pc;
  CPUaddr init_msp, init_usp, init_isp;
  CPUword init_sr;

  CPUlong init_dreg[8];
  CPUlong init_areg[8];
  
  /* Memory handling */

  CPUbyte (*get_byte) (CPUaddr addr);
  CPUword (*get_word) (CPUaddr addr);
  CPUlong (*get_long) (CPUaddr addr);

  void (*put_byte) (CPUaddr addr, CPUbyte value);
  void (*put_word) (CPUaddr addr, CPUword value);
  void (*put_long) (CPUaddr addr, CPUlong value);

  void *(*real_addr) (CPUaddr addr);
  int (*valid_addr) (CPUaddr addr, CPUlong size);

  /* Exception handling */

  void (*handle_exception) (int nr, CPUaddr oldpc);

} CPU;

/* Regular functions */

CPU *CPUtemplate(void);
CPU *CPUsimple_template(CPUaddr pc, CPUaddr sp, CPUword sr);
int CPUinit(CPU *data);
int CPUrun(void);

/* Retrieving and setting special data */

CPUaddr CPUget_pc(void);
void CPUset_pc(CPUaddr);

CPUaddr CPUget_msp(void);
void CPUset_msp(CPUaddr);
CPUaddr CPUget_usp(void);
void CPUset_usp(CPUaddr);
CPUaddr CPUget_isp(void);
void CPUset_isp(CPUaddr);

CPUword CPUget_sr(void);
void CPUset_sr(CPUword);

CPUlong CPUget_dreg(int);
void CPUset_dreg(int, CPUlong);

CPUlong CPUget_areg(int);
void CPUset_areg(int, CPUlong);

#endif /* _OCPUIS_H_ */
