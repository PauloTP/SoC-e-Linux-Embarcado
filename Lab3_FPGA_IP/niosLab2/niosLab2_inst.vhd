	component niosLab2 is
		port (
			clk_clk         : in  std_logic                    := 'X';             -- clk
			reset_reset_n   : in  std_logic                    := 'X';             -- reset_n
			switches_export : in  std_logic_vector(5 downto 0) := (others => 'X'); -- export
			leds_name       : out std_logic_vector(3 downto 0)                     -- name
		);
	end component niosLab2;

	u0 : component niosLab2
		port map (
			clk_clk         => CONNECTED_TO_clk_clk,         --      clk.clk
			reset_reset_n   => CONNECTED_TO_reset_reset_n,   --    reset.reset_n
			switches_export => CONNECTED_TO_switches_export, -- switches.export
			leds_name       => CONNECTED_TO_leds_name        --     leds.name
		);

