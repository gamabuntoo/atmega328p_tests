// void idle_increment()
// {
// 	static int i = 0;
// 	static int dig = 0;
// 	if (i > 9)
// 		i = 0;
// 	if (dig > 3)
// 		dig = 0;

// 	if (p_switch() == false)
// 	{
// 		display_number(i++);
// 		for (int x = 0; x < 16 && p_switch() == false; x++)
// 			_delay_ms(20);
// 		// flip_state_digit(dig);
// 	}
// 	if (!((PINC & (1 << PC1)))) // if button2 pushed, b bits get flipped
// 	{
// 		flip_state_digit(dig);
// 		dig++;
// 	}
// 	return ;
// }

// void idle_2()
// {
// 	static int i = 0;
// 	static char c = 'a';
// 	static bool stat = 1;
// 	char t[4];
// 	if (c >= 'g' || i >= 7)
// 	{
// 		i = 0;
// 		c = 'a';
// 		stat = !stat;
// 	}
// 	while (i < 7 && p_switch() == false)
// 	{
// 		if (!((PINC & (1 << PC1))) && ((i != 5 && i != 7 && i != 0) || (i > 0 && i < 4))) // if button2 pushed, b bits get flipped
// 			flip_state_digit(i);
// 		flip_state_segment(c, stat);

// 		//debug

// 		display_string_uart(itoa(i, t, 10));			display_string_uart(" index\r\n");
// 		print_port_stat_uart(&PORTD, "PORTD");
// 		print_port_stat_uart(&PORTB, "PORTB");
	
// 		for (int x = 0; x < 8 && p_switch() == false; x++)
// 			_delay_ms(20);
// 		i++;
// 		c++;
// 	}

// }