library IEEE;
use IEEE.std_logic_1164.all;

entity LAB2_FPGA_NIOS is
    port (
        -- Gloabals
        fpga_clk_50        : in  std_logic;             -- clock.clk

        -- I/Os
        stepmotor_en  : in  std_logic;
        stepmotor_dir : in  std_logic;
		  stepmotor_vel : in  std_logic_vector(1 downto 0);
        stepmotor_pio : out std_logic_vector(3 downto 0);
		  fpga_led      : out std_logic_vector(3 downto 0)
		  
  );
end entity LAB2_FPGA_NIOS;

architecture rtl of LAB2_FPGA_NIOS is

    component niosLab2 is
        port (
            clk_clk       : in  std_logic                    := 'X';             -- clk
            reset_reset_n : in  std_logic                    := 'X';             -- reset_n
            switch_export : in  std_logic_vector(3 downto 0) := (others => 'X');  -- export
				motor_export  : out std_logic_vector(3 downto 0);
            leds_name : out std_logic_vector(3 downto 0)        -- leds        
				);
    end component niosLab2;

begin

u0 : component niosLab2 port map (
  clk_clk       => fpga_clk_50,    --  clk.clk
  reset_reset_n => '1',            --  reset.reset_n999999999999999
  switch_export(0) => stepmotor_en,  -- switch.export
  switch_export(1) => stepmotor_dir,
  switch_export(3 downto 2) => stepmotor_vel,
  motor_export  => stepmotor_pio,   --  motor.export
  leds_name     => fpga_led      --  leds.name
);

end rtl;
