#include "atmegatest.h"

bool	check_button_PB5()
{
	if (!(PINC & (1 << PC0)))
	{
		PORTB |= (1 << PORTB5);		// output via pb5 builtin led
		// flag |= 1;
		return (true);
	}
	else
		PORTB &= ~(1 << PORTB5); // led off
	return (false);
}

int	p_switch()
{
	static bool st = 0;
	static bool last = 0;
	bool pressed = !(PINC & (1 << PC0));
	// (check_button_PB5() == 1)
	if (pressed && !last)
	{
		_delay_ms(10);
		if (check_button_PB5())
			st = !st;
	}
	last = pressed;
	return st;
}