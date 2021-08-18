/*
 * Test2021_2.c
 *
 * Created: 08/11/21 15:44:36
 * Author : German
 */ 

#include <avr/io.h>
#include <avr/iom2560.h>
#define F_CPU	16000000L
#include <util/delay.h>
#include <avr/interrupt.h>

//Typedef
typedef union {
	struct{
		uint8_t b0: 1;
		uint8_t b1: 1;
		uint8_t b2: 1;
		uint8_t b3: 1;
		uint8_t b4: 1;
		uint8_t b5: 1;
		uint8_t b6: 1;
		uint8_t b7: 1;
	}bit;
	uint8_t byte;	
}_sFlag;
//..

//Defines
#define IS10MS		flag1.bit.b0
#define IS250MS		flag1.bit.b1
//..


//Prototipos
void initPorts();
void initTimers();
//..

//Globals Variables
volatile _sFlag flag1;

volatile uint8_t timeOut250msAprox;
//.

//Interruptions
ISR(TIMER0_OVF_vect){
	timeOut250msAprox--;
	if(!timeOut250msAprox){
		timeOut250msAprox = 25;
		IS250MS = 1;
	}
}
//.


void initPort(){
	//Configuro PIN del LED como salida (PB5 Arduino UNO, PB7 Arduino 2560)
	DDRB = (1 << DDB7); //0b10000000
	//	DDRB |= (1 << DDB5); // DDRB = DDRB | 0b00100000
	
	PORTB |= (1 << PB7);
}

//'U' 'N' 'E' 'R' 'BYTES' : nDATOS CKS
//
//'U' 'N' 'E' 'R' => HEADER
//: => TOKEN
//BYTES => es la suma de nDATOS + CKS
//CKS => es byte que es la suma de todo lo enviado

void initTimers(){
	TCCR0A = 0x00;
	TIFR0 = TIFR0;
	TIMSK0 = (1 << TOIE0); //0b00000001 
	TCCR0B = 0x05; 
}

int main(void)
{
	flag1.byte = 0;
	
	timeOut250msAprox = 15;
	
	initPort();	
	
	initTimers();	
	
	sei(); //Estoy poniendo en 1 el bit 7 del status

    /* Replace with your application code */
    while (1) 
    {
		if (IS250MS)
		{
			IS250MS = 0;
			if(PORTB & (1<<PB7)) //(1<<PB7) = 0x80
				PORTB &= ~(1 << PB7);
			else
				PORTB |= (1 << PB7);
		}
				
    }
}

