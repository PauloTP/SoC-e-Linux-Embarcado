	component niosLab2 is
		port (
			clk_clk       : in  std_logic                    := 'X'; -- clk
			leds_name     : out std_logic_vector(3 downto 0);        -- name
			reset_reset_n : in  std_logic                    := 'X'; -- reset_n
			fases_phases  : out std_logic_vector(3 downto 0)         -- phases
		);
	end component niosLab2;

	u0 : component niosLab2
		port map (
			clk_clk       => CONNECTED_TO_clk_clk,       --   clk.clk
			leds_name     => CONNECTED_TO_leds_name,     --  leds.name
			reset_reset_n => CONNECTED_TO_reset_reset_n, -- reset.reset_n
			fases_phases  => CONNECTED_TO_fases_phases   -- fases.phases
		);

