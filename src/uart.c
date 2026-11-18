#include "atmegatest.h"

void	disp_bit_uart(char c)
{
	while (!(UCSR0A & (1 << UDRE0)))
	{
	}
	UDR0 = c; // copy value to the uart read write variable
}

void	display_uint_uart(uint8_t v)
{
	int8_t i = 7;
	while (i >= 0)
	{
		if ((v & (1 << i)))
			disp_bit_uart('1');
		else
			disp_bit_uart('0');
		i--;
	}
	disp_bit_uart('\r');
	disp_bit_uart('\n');
}

void	display_string_uart(const char *str)
{
	uint8_t i = 0;
	while (str[i] != '\0')
	{
		disp_bit_uart(str[i]);
		i++;
	}
}

void	print_port_stat_uart(volatile uint8_t *port, const char *name)
{
	char t[4];
	if (!port)
		return ;
	display_string_uart("-Stat "); 	display_string_uart(name);
	// display_string_uart(itoa(s, t, 10));			display_string_uart(" index\r\n");
	display_string_uart("-\r\nb10:\t");			display_string_uart(itoa(*port, t, 10)); // PORT VALUE DISPLAY
	display_string_uart("\r\nbin:\t");			display_uint_uart(*port);					disp_bit_uart('\n');
}

void init_uart()
{
	UBRR0H = 0;
	UBRR0L = 103; // speed calcul de con

	UCSR0A = 0;	 //normal mode U2X0 / gives state 
	UCSR0B = (1 << TXEN0) | (1 << RXEN0); // fonctions
	UCSR0C = (1 << UCSZ01) | (1 << UCSZ00); //format trame
}
