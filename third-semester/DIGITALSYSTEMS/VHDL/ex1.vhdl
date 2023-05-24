library ieee;
use ieee.std_logic_1164.all;

entity ex1 is
    port(
        a, b, c: in std_logic;
        s : out std_logic
    );
end ex1;

architecture arc of ex1 is
    signal aux1, aux2: std_logic;
    begin
        aux1 <= a AND b;
        aux2 <= b OR c;
        s <= aux1 NAND aux2;
end arc;
