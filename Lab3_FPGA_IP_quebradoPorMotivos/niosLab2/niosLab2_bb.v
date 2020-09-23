
module niosLab2 (
	clk_clk,
	leds_writeresponsevalid_n,
	motor_export,
	reset_reset_n,
	switch_export);	

	input		clk_clk;
	output	[3:0]	leds_writeresponsevalid_n;
	output	[3:0]	motor_export;
	input		reset_reset_n;
	input	[3:0]	switch_export;
endmodule
