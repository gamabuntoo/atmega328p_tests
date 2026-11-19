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

//buttons
bool	check_button_PB5();
int		p_switch();


//bits etcc
void	flip_bit(uint8_t bit,  volatile uint8_t *Por);
bool	stat_bit(uint8_t bit,  volatile uint8_t *Por);
void	flip_state_segment(uint8_t segment, bool stat);
int 	which_side(uint16_t val);
void	set_state_digit(uint8_t dig, bool stat);
void	flip_state_digit(uint8_t dig);
void	display_number(uint8_t val); // modification necessaire pcq degeu et animation useless pcq flicker
void	display_val(uint16_t value);



#endif