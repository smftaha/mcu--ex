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
#define CoreDebug_BASE      (0xE000EDF0UL)
#define CoreDebug           ((CoreDebug_Type *)     CoreDebug_BASE)   /*!< Core Debug configuration struct */

/**
  \brief  Structure type to access the Core Debug Register (CoreDebug).
 */
typedef struct
{
  __IOM uint32_t DHCSR;                  /*!< Offset: 0x000 (R/W)  Debug Halting Control and Status Register */
  __OM  uint32_t DCRSR;                  /*!< Offset: 0x004 ( /W)  Debug Core Register Selector Register */
  __IOM uint32_t DCRDR;                  /*!< Offset: 0x008 (R/W)  Debug Core Register Data Register */
  __IOM uint32_t DEMCR;                  /*!< Offset: 0x00C (R/W)  Debug Exception and Monitor Control Register */
} CoreDebug_Type;

//this doesnt work on CM0, it is claimed works on CM3,4
if (CoreDebug->DHCSR & CoreDebug_DHCSR_C_DEBUGEN_Msk)
{
	__BKPT(0);
}
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
https://stackoverflow.com/questions/27510198/how-to-delay-an-arm-cortex-m0-for-n-cycles-without-a-timer
delay in assembly
   movs  r0, #NUM    ;1 cycle
1: subs  r0, r0, #1  ;1 cycle
   bne   1b          ;2 if taken, 1 otherwise
//////////////////////////////////////////////////////
enter ascii in windows
0x0d  \r  '\r'  carriage return
0x0a  \n  '\n'  line feed

visual studio
@end of send strings: send 0x0a 
//////////////////////////////////////////////////////

	SysTick->CTRL=	SysTick_CTRL_ENABLE_Msk	|	SysTick_CTRL_TICKINT_Msk;//	|SysTick_CTRL_CLKSOURCE_Msk;
 SysTick->LOAD=	(FCPU/1000)-1;
	DBGMCU->CR=	DBGMCU_CR_DBG_STANDBY;
	DBGMCU->APB1FZ=		DBGMCU_APB1_FZ_DBG_IWDG_STOP;

while(1)
if	(	SysTick-> CTRL	&	SysTick_CTRL_COUNTFLAG_Msk)
{}
//////////////////////////////////////////////////////
#if defined	(DBG_MODE_1) || defined(DBG_MODE_2)

#define VREFINT_CAL			((uint16_t*) 0x1FFFF7BA)
#define UID				      	((uint16_t*) 0x1FFFF7AC)
x=		((uint32_t)(((*VREFINT_CAL)	&0x0fff)	*330))/Adc_Rslt;
//////////////////////////////////////////////////////
