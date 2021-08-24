//some good intrinsic CPU instructions
//https://www.keil.com/pack/doc/cmsis/Core/html/group__intrinsic__CPU__gr.html
//https://www.keil.com/pack/doc/cmsis/Core/html/group__compiler__conntrol__gr.html
//https://www.keil.com/pack/doc/cmsis/Core/html/group__Core__Register__gr.html

void 	__NOP (void)
 	No Operation. More...
 
void 	__WFI (void)
 	Wait For Interrupt. More...
 
void 	__WFE (void)
 	Wait For Event. More...
 
void 	__SEV (void)
 	Send Event. More...
 
void 	__BKPT (uint8_t value)
 	Set Breakpoint. More...
 
void 	__ISB (void)
 	Instruction Synchronization Barrier. More...
 
void 	__DSB (void)
 	Data Synchronization Barrier. More...
 
void 	__DMB (void)
 	Data Memory Barrier. More...
 
uint32_t 	__REV (uint32_t value)
 	Reverse byte order (32 bit) More...
 
uint32_t 	__REV16 (uint32_t value)
 	Reverse byte order (16 bit) More...
 
int16_t 	__REVSH (int16_t value)
 	Reverse byte order (16 bit) More...
 
uint32_t 	__RBIT (uint32_t value)
 	Reverse bit order of value. More...
 
uint32_t 	__ROR (uint32_t value, uint32_t shift)
 	Rotate a value right by a number of bits. More...

uint8_t 	__CLZ (uint32_t value)
 	Count leading zeros. More...
//////////////////////////////////////////////////////
*   keil do not switch to handler mode- control bit not change
*   how to exit from bkpt instruction
//////////////////////////////////////////////////////
stack depth calculation way:
if	(0)
{
  uint32_t	*x;
  x=	(uint32_t	*)	0x20000200;           //stack_start_adr
  while	(	x	<(uint32_t	*)	0x20001000)   //stack_stop_adr
    *x++=0xf1f2f3f4;                      //fill stack with a fixed pattern
}
//////////////////////////////////////////////////////
set breakpoint and an intruction after that. change PC to the next instruction for exit.
__BKPT	(1);
__NOP	  ();
//////////////////////////////////////////////////////
enter ascii in windows
0x0d  \r  '\r'  carriage return
0x0a  \n  '\n'  line feed

visual studio
@end of send strings: send 0x0a 
//////////////////////////////////////////////////////
