#ifndef ATMEGATEST_H
# define ATMEGATEST_H

#include <avr/io.h>
#include <avr/wdt.h> // WATCH DOGS
#include <stdint.h>
#include <stdlib.h>
#include <util/delay.h>
#include <stdbool.h>

#define         PORT_B  *((volatile uint8_t*)0x25) // PORT B, byte needs to be set to the value of wanted b side port (0-7)
#define         P_DDRB  *((volatile uint8_t*)0x24) // DDRB, tells whats the pin is doing (I/O)


#define 		digitA {9, 3, 7, 2, 1}
#define 		digitAs 5
#define			digitB {6, 5, 4}
#define 		digitBs 3

// INIT UART
void	disp_bit_uart(char c);
void	display_uint_uart(uint8_t v);
void	display_string_uart(const char *str);
void	print_port_stat_uart(volatile uint8_t *port, const char *name);
void 	init_uart();


bool	check_button_PB5();
int		p_switch();

#endif