extern unsigned long cycles;

static __inline__ void do_cycles(unsigned long cycles_to_add)
{
  cycles+=cycles_to_add;
  memory.handle_event(cycles);
  if(cycles > 8012800) /* FIXME */
    cycles -= 8012800;
}

