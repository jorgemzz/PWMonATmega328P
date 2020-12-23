/*
 * PwmTest.c
 *
 * Created: 12/23/2020 11:36:15 AM
 * Author : Jorge Miranda
 */ 
#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>

void init_pwm_timer1();
void set_servo_angle(float angle);

int main(void)
{
    DDRB|= 1 << PIND5;
	init_pwm_timer1();
	set_servo_angle(180);
    while (1) 
    {
		PINB |= 1<< PIND5;
		_delay_ms(100);
    }
}


void init_pwm_timer1(){
	TCCR1A |= (1 << COM1A1) | (1 << WGM11);
	TCCR1B |= (1 << WGM13) | (1<<  WGM12) | (1 << CS11) | (1 <<  CS10);
	DDRB |=  1 << PIND1;
	ICR1 = 4999;
}

#define TIME_ON_000_DEG 388U	//time on in us for 0 degree position of servo
#define TIME_ON_180_DEG 2140U	//time on in us for 180 degree position of servo
void set_servo_angle(float angle){
	if(angle < 0){
		angle = 0.0;
	}else if(angle > 180){
		angle = 180.0;
	}
	float time_on = (((TIME_ON_180_DEG - TIME_ON_000_DEG)*angle)/180.0 + TIME_ON_000_DEG);
	OCR1A = (unsigned int)(time_on/4);		//Find register value considering 4us base time after pre scaler
}