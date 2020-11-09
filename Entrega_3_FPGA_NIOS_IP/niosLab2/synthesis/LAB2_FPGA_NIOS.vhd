library IEEE;
use IEEE.std_logic_1164.all;

entity LAB2_FPGA_NIOS is
    port (
        -- Gloabals
        fpga_clk_50        : in  std_logic;             -- clock.clk

        -- I/Os
        fpga_led_pio       : out std_logic_vector(3 downto 0);
		  fpga_switches_pio  : in std_logic_vector(5 downto 0);
		  fpga_motor_phases  : out std_logic_vector(3 downto 0)
		  
  );
end entity LAB2_FPGA_NIOS;

architecture rtl of LAB2_FPGA_NIOS is
 SIGNAL to_leds : std_logic_vector(3 downto 0);

component niosLab2 is
        port (
            clk_clk         : in  std_logic                    := 'X';             -- clk
            leds_name     : out std_logic_vector(3 downto 0);                    -- export
            reset_reset_n   : in  std_logic                    := 'X';             -- reset_n
				fases_phases  : out std_logic_vector(3 downto 0)    -- phases
        );
    end component niosLab2;

	 
begin

	fpga_led_pio <= to_leds;
	
 u0 : component niosLab2
        port map (
           clk_clk       => fpga_clk_50,    --  clk.clk
			  reset_reset_n => '1',            --  reset.reset_n
			  leds_name   => to_leds,    --  leds.export
			  fases_phases  => fpga_motor_phases   -- fases.phases
        );

end rtl;