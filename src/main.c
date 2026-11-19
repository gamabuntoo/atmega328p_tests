/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gule-bat <gule-bat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/17 22:34:14 by gule-bat          #+#    #+#             */
/*   Updated: 2026/11/19 23:53:52 by gule-bat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "atmegatest.h"

void	flip_bit(uint8_t bit,  volatile uint8_t *Por)
{
	uint8_t v = 1;
	uint8_t b = 0;
	b = v << bit;

	if (b != 0 && ((b) & (b-1)) == 0)
	{
		if ((*Por & b) != 0)
			*Por &= ~b;
		else
			*Por |= b;
	}
	return ;
}

bool	stat_bit(uint8_t bit,  volatile uint8_t *Por)
{
	uint8_t v = 1;
	uint8_t b = 0;
	b = v << bit;

	if (b != 0 && ((b) & (b-1)) == 0)
	{
		if ((*Por & b) != 0)
			return (true);
		else
			return (false);
	}
	return (false);
}

void	flip_state_segment(uint8_t segment, bool stat)
{
	int i = 2;
	char c = 'a';

	if (segment > 'z' || segment < 'a')
		return;
	while (i < 9)
	{
		if (segment == c)
		{			
			if (segment == 'g' && i == 8)
			{
				if ((!(PORTB & (1 << PB0)) && (stat == 1)) || ((PORTB & (1 << PB0)) && stat == 0))
					return;
				return (flip_bit(0, &PORTB));
			}
			if (((!(PORTD & (1 << i)) && stat == 1) || ((PORTD & (1 << i)) && stat == 0)) && i < 8)
				return;
			return flip_bit(i, &PORTD);
		}
		c++;
		i++;
	}

}

void	flip_state_digit(uint8_t dig)
{
	uint8_t i = 0;
	
	if (dig >= 4 && dig < 0)
		return ;
	while (i < 4)
	{
		if (i == dig)
			flip_bit(i+1, &PORTB);
		i++;
	}
}

void	set_state_digit(uint8_t dig, bool stat)
{
	uint8_t i = 0;
	
	if (dig >= 4 && dig < 0)
		return ;
	while (i < 4)
	{
		if (i == dig)
		{
			if (stat_bit(i+1, &PORTB) == true && stat == 0)
				flip_bit(i+1, &PORTB);
			else if (stat_bit(i+i, &PORTB) == false && stat == 1)
				flip_bit(i+1, &PORTB);
		}
		i++;
	}
}

int which_side(uint16_t val)
{
	uint16_t x = 0;
	uint16_t res = 0;

	// 1 pour A | 4 pour B
	uint16_t tabA[] = digitA;
	uint16_t tabB[] = digitB;
	if (val > 10 && val < 0)
		return 0;
	while (x < digitAs)
	{
		if (val == tabA[x])
		{
			res = 1;
			if (x > 1)
			{
				res += 1; // 2
				return res;
			}
			return (res);
		}
		x++;
	}
	x = 0;
	while (x < digitBs)
	{
		if (val == tabB[x])
		{
			res = 4;
			return (res);
		}
		x++;
	}
	return (0);
}

void	display_number(uint8_t val) // SWITCHCASE NECESSAIRE
{
	int i = 0;
	uint16_t side = 0;

	if (val > 9)
		return ;
	while (i < 7)
	{
		flip_state_segment('a' + i, 1);
		i++;
	}

	i = 0;
	if (val == 8)
		return ;/*(_delay_ms(175))*/
	if (val == 0)
	{
		// _delay_ms(175);
		flip_state_segment('g', 0);

		return ;
	}
	side = which_side(val);
	if (!side)
		return ;
	else if (side >= 1 && side <= 2)
	{
		// uint8_t	tab[] = digitA;
		if ((val == 9 || val == 7) || (val >= 1 && val <= 3))
		{
			// _delay_ms(77);
			flip_state_segment('e', 0);
		}
		if ((val >= 1 && val <= 3) || val == 7)
		{
			flip_state_segment('f', 0);
			// _delay_ms(55);
		}	
		if (val == 2)
		{
			flip_state_segment('c', 0);
			flip_state_segment('e', 1);
			// _delay_ms(15);
		}
		if (val == 7 || val == 1)
		{
			flip_state_segment('g', 0);
			flip_state_segment('d', 0);
			// _delay_ms(10);
		}
		if (val == 1)
		{
			flip_state_segment('a', 0);
			// _delay_ms(5);
		}
	}
	else
	{
		if  (val >= 4 && val <= 6)
		{
			flip_state_segment('b', 0); // 6
			// _delay_ms(77);
		}
		if  (val >= 4 && val <= 5)
		{
			flip_state_segment('e', 0); // 5
			// _delay_ms(27);
		}
		if (val == 4)
		{
			flip_state_segment('b', 1); 
			flip_state_segment('a', 0); 
			// _delay_ms(55);
			flip_state_segment('d', 0); // 4
		}
	}

}

void	display_flicker(uint8_t digit, uint16_t value)
{
	// for (int x = 0; x < 4 && p_switch() == false; x++)
		// _delay_ms(20);
	if (p_switch() == false)
	{
		display_number(value);
		_delay_us(20);	
		flip_state_digit(digit);
	}
}


void	display_val(uint16_t value)
{
	uint8_t x = 0;
	int8_t id = 3;
	uint16_t tmp = value;

	while (id >= 0 && p_switch() == false)
	{
		if (id >= 0 && tmp == 0)
			return ;
		x = tmp % 10;
		tmp = tmp / 10;
		display_flicker(id, x);
		set_state_digit(id, 1);
		set_state_digit(id, 0);
		id--;
	}
	return ;
}


int main()
{  
	uint16_t ct = 0;
	
	// WATCH DOG MENTIONNE
	MCUCR &= ~(1 << WDRF);
	wdt_disable();
	flip_bit(5, &P_DDRB);
	
	DDRD |= 252; // 11111100					both for lights and ports, light only on pb5 
	DDRB |= 31;	 // 00011111	activate ports
	DDRC &= ~(1 << PC0); // button1
	DDRC &= ~(1 << PC1); // button2


	PORTD |= 252; // set port
	PORTB = (PORTB & ~31) | 31;

	PORTC |= (1 << PC0); // init buttons pins
	PORTC |= (1 << PC1);


	while (!p_switch())
	{
	}// start

	// init_uart();
	// _delay_ms(200);
	// print_port_stat_uart(&PORTB, "PORTB");
	// print_port_stat_uart(&PORTC, "PORTC");
	// print_port_stat_uart(&PORTD, "PORTD"); // debug ports at start
	// _delay_ms(200);

	set_state_digit(3, 0);
	set_state_digit(2, 0);
	set_state_digit(1, 0);
	set_state_digit(0, 0);
	while (1)
	{
		if (ct > 9999)
			ct = 0;

		display_val(ct);
		if (!((PINC & (1 << PC1)))) // if button2 pushed, value inscreases
		{
			ct++;
			_delay_ms(100);
		}

		_delay_us(20); // 				probleme qd PB5 parfois, décalage suspicieux (flipstatedigit?)
		// for (int x = 0; x < 8 && p_switch() == false; x++)
			// _delay_ms(20);
										// display_string_uart("debug loop\r\n");
		while (p_switch() != false)
		{}
		PORTB &= 0b11011111;
	}
}