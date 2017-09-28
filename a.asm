LIST p = 16f628, R = DEC

#include <p16f628.inc>

__config  _INTRC_OSC_NOCLKOUT & _LVP_OFF & _WDT_OFF & _PWRTE_ON & _BODEN_ON

org 0

BEGIN:
	clrf PORTB
	clrf TRISB

LOOP:
	bsf PORTB, 4
	goto LOOP

end.