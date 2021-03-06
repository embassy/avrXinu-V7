/*
 *  clkint.c
 *  Avr_Xinu
 *
 *  Created by Michael Minor on 8/23/10.
 *  Copyright 2010. All rights reserved.
 *
 */

/*
 *
 *	Version for 256rfr2XplainPro
 *
 */

#include <conf.h>
#include <kernel.h>
#include <sleep.h>
#include <avr/io.h>
#include <avr/interrupt.h>

#define LED PING2

extern void wakeup(void);
extern int resched(void);

static int prescaler = 10;

//static int rtcScaler = 10;


/**
 *--------------------------------------------------------------------------
 * Clock interrupt routine -- system clock driven TIMER3 in CTC mode
 * clkint() -- premptive scheduling and time-of-day clock routine
 *--------------------------------------------------------------------------
 */

ISR(TIMER3_COMPA_vect)		/* Timer3 Compare Match A vector */
{
    /* executing the ISR automatically clears the OCF3A Flag */
    /* 100 Hz clock 16000000/256/(1+624) */
	/* OCR3A set to 624 for CTC mode */

	ctr100++;				/* Version 8 timer/counter */
	
	if (--prescaler > 0)
		return;
	prescaler = 10;

//	if (--rtcScaler == 0)	{
//		clktime++;
//		rtcScaler = 10;
//		PORTB ^= (1<<LED);
//	}
	
    if (defclk)	{
		clkdiff++;
		return;
	}
    if ( slnempty && (--*sltop <= 0) )	{
		wakeup();
	}
    if (--preempt <= 0)	{
		resched();
	}
}

/**
 *--------------------------------------------------------------------------
 * RTC interrupt routine -- watch crystal 32.768kHz driven TIMER2 overflow
 * time-of-day clock routine
 *--------------------------------------------------------------------------
 */


ISR(TIMER2_OVF_vect)		/* overflow interrupt vector */
{
    /* the timer overflow interrupt automatically clears the TOV2 Flag */
    /* 1 Hz clock (32768/128)/256	(256 is 8-bit clock overflow; 128 prescale) */
	
	clktime++;               /*update time of day*/
	PORTG ^= (1<<LED);
}

