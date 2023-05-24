library ieee;
use ieee.std_logic_1164.all;

entity mux1 is
    port(
        a, b, k: in std_logic;
        s: out std_logic
    );
end mux1;

architecture arc of mux1 is
    begin
        process(a, b, k)
        begin
            if k = '1' then
                s <= b;
            else
                s <= a;
            end if;
        end process;
end arc;