
module niosLab2 (
	clk_clk,
	reset_reset_n,
	switches_export,
	leds_name);	

	input		clk_clk;
	input		reset_reset_n;
	input	[5:0]	switches_export;
	output	[3:0]	leds_name;
endmodule
