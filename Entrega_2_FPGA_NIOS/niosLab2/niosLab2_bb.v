
module niosLab2 (
	clk_clk,
	leds_export,
	motor_export,
	reset_reset_n,
	switch_export);	

	input		clk_clk;
	output	[5:0]	leds_export;
	output	[3:0]	motor_export;
	input		reset_reset_n;
	input	[3:0]	switch_export;
endmodule
