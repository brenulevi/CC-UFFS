library ieee;
use ieee.std_logic_1164.all;

entity dmux1 is
    port(
        a, k : in std_logic;
        s1, s2 : out std_logic
    );
end dmux1;

architecture arc of dmux1 is
    begin
        process(a, k)
        begin
            if k = '1' then
                s1 <= '0';
                s2 <= a;
            else
                s1 <= a;
                s2 <= '0';
            end if;
        end process;
end arc;