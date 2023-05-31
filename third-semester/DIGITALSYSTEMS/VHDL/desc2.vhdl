library ieee;
use ieee.std_logic_1164.all;

entity desc is
  port (
    A,B,C: in std_logic;
    D,E: out std_logic
  );
end desc;

architecture arc_desc of desc is

    signal op1, op2, op3, op4: std_logic;

begin

    op1 <= (NOT A) AND B;
    op2 <= (NOT A) AND C;
    op3 <= B AND C;
    op4 <= A XOR B;

    D <= op1 OR op2 OR op3;
    E <= op4 XOR C;

end arc_desc ;