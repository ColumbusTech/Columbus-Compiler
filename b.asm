org 0

BEGIN:
clrf PORTA
clrf PORTB
bsf STATUS, 5
clrf TRISA
clrf TRISB
bcf STATUS, 5
LOOP:
bsf PORTB, 4
goto LOOP

end
