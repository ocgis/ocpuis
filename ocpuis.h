#ifndef _OCPUIS_H_
#define _OCPUIS_H_

typedef unsigned char CPUbyte;
typedef unsigned short CPUword;
typedef unsigned long CPUlong;

typedef CPUlong CPUaddr;

typedef struct sCPU {

  /* Initialisation */

  CPUaddr init_pc;      /* Program counter
			 * Execution will start here
			 * upon CPUrun().
			 */

  CPUword init_sr;      /* Status register */

  /* Note: the thing commonly known as SP is
   *       really Areg[7]
   */

  CPUaddr init_msp;     /* Master SP */
  CPUaddr init_usp;     /* User SP */
  CPUaddr init_isp;     /* Interrupt SP */

  CPUlong init_dreg[8]; /* Data registers */
  CPUlong init_areg[8]; /* Address registers */
  
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
  void (*handle_event) (unsigned long cyclecnt);

} CPU;

/* Regular functions */

/* 
 * CPUtemplate:
 * 
 * Creates an empty (zeroed) entry
 * of the struct above and returns it.
 */

CPU *CPUtemplate(void);

/* 
 * CPUsimple_template:
 * 
 * Similar to CPUtemplate() but also
 * sets PC, SP (A7) and SR before
 * returning the struct.
 */

CPU *CPUsimple_template(CPUaddr pc, CPUaddr sp, CPUword sr);

/*
 * CPUinit:
 *
 * Initialises the CPU core, in a very non-reentrant manner.
 * Fills the internal structures with the values specified
 * in the CPU struct.
 */

int CPUinit(CPU *data);

/*
 * CPUrun:
 *
 * Begin execution.
 */

int CPUrun(void);

/*
 * CPUsubroutine
 *
 * Execute subroutine.
 */

int CPUsubroutine(CPUaddr new_pc);

/*
 * CPUexception
 *
 * Perform an exception by
 * jumping to an vector nr,
 * without going to the user-
 * level exception handler.
 */

int CPUexception(int nr);

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
