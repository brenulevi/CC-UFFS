library ieee;
use ieee.std_logic_1164.all;

entity finalproject is
	port(
		SW : in std_logic_vector(9 downto 0);
		KEY : in std_logic_vector(3 downto 0);
		
		LEDR : out std_logic_vector(9 downto 0);
		LEDG : out std_logic_vector(7 downto 0);
		HEX0 : out std_logic_vector(6 downto 0);
		HEX1 : out std_logic_vector(6 downto 0);
		HEX2 : out std_logic_vector(6 downto 0);
		HEX3 : out std_logic_vector(6 downto 0)
	);
end finalproject;

architecture finalproject_behav of finalproject is
begin

	LEDR <= SW;

end finalproject_behav;