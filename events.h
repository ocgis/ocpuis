extern unsigned long cycles;

static __inline__ do_cycles(unsigned long cycles_to_add)
{
  cycles+=cycles_to_add;
  if(cycles > 8012800) /* FIXME */
    cycles -= 8012800;
  memory.handle_event(cycles);
}

