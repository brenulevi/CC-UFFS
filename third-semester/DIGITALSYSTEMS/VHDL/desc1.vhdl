library ieee;
use ieee.std_logic_1164.all;

entity desc is
  port (
    A,B,C: in std_logic;
    D,E,F: out std_logic
  );
end desc;

architecture arc_desc of desc is

    signal op1, op2, op3: std_logic;

begin

    op1 <= A NOR (NOT B);
    op2 <= (NOT B) NAND (NOT C);
    op3 <= (NOT B) AND (NOT C);

    D <= op1 XOR (NOT op2);
    E <= op2 OR (NOT B);
    F <= op2 XOR op3;

end arc_desc ;