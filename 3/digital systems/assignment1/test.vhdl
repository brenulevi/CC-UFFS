library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity ent is
	port( 
        in1: in std_logic_vector(3 downto 0);
        in2: in std_logic_vector(3 downto 0);
	    out1 : out std_logic_vector(3 downto 0)
        ); 
end ent;

architecture behav of ent is

    signal int1, int2: integer;
    signal sum_int: integer;

    begin
        int1 <= to_integer(unsigned(in1));
        int2 <= to_integer(unsigned(in2));
        
        sum_int <= int1 + int2;

        out1 <= std_logic_vector(to_unsigned(sum_int, 4));
	
end behav; 

-- Ela me disse "eu te amo", mas o breno me disse "não pense que tens imperfeições, pois até o sol e a lua tomam 
-- turnos pra presenciar sua beleza".