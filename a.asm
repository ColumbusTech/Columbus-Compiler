org 0

BEGIN:
	clrf PORTB
	clrf TRISB

LOOP:
	bsf PORTB, 4
	goto LOOP

end.