#include<16f877.h>
//------ADC VALUE------
#device ADC=10
#use delay(clock=4000000)
#fuses HS, NOWDT, NOPUT, NOLVP, NOCPD, NOPROTECT, NODEBUG, NOBROWNOUT, NOWRT
//------LCD SETUP------
#define use_portb_lcd TRUE
#include<lcd.c>

//------I/O PORT SETUP------
#use fast_io(a)
#use fast_io(b)
#use fast_io(c)

//------VARIABLES------
unsigned long int value;
float voltage,heat;

void main(){

lcd_init();

//------DISABLED PROPERTIES------
setup_psp(PSP_DISABLED);
setup_timer_1(T1_DISABLED);
setup_ccp2(CCP_OFF);

//------PWM SETUP------
setup_timer_2(T2_DIV_BY_4,255,1);
setup_ccp1(ccp_pwm);
set_pwm1_duty(0);

//------PORT SETUP------
set_tris_a(0x01);
set_tris_b(0x00);
set_tris_c(0x00);

//------ADC SETUP------
setup_adc(adc_clock_div_32);
setup_adc_ports(AN0);
set_adc_channel(0);
delay_us(20);

output_a(0x00);
output_b(0x00);
output_c(0x00);
lcd_gotoxy(3,1);
printf(lcd_putc,"Temperature:");


while(true){

//------ADC READ------
value=read_adc();
voltage=value*4.88739;
heat=(voltage/10);

//------LCD PRINT------
lcd_gotoxy(5,2);
printf(lcd_putc,"%f C",heat);
delay_ms(100);

//------DC MOTOR CONTROL------
if(heat<=25){
set_pwm1_duty(0); 
output_high(pin_c0);
output_high(pin_c1);
}

if(heat>25 && heat<30){
set_pwm1_duty(342);
output_high(pin_c0);
output_low(pin_c1);
}

if(heat>=30 && heat<35){
set_pwm1_duty(648);
output_high(pin_c0);
output_low(pin_c1);
}

if(heat>=35){
set_pwm1_duty(1023);
output_high(pin_c0);
output_low(pin_c1);
}

}
}
