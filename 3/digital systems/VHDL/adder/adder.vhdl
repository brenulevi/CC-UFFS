--------------------------------------------------------------------
-- 8 BIT ADDER

library ieee;
use ieee.std_logic_1164.all;

entity eight_bit_adder is
  port(
    a: in std_logic_vector(7 downto 0);
    b: in std_logic_vector(7 downto 0);
    carry: out std_logic;
    sum: out std_logic_vector(7 downto 0)
  );
end eight_bit_adder;

architecture behav_eight_adder of eight_bit_adder is

  component four_bit_adder is
    port(
      a, b: in std_logic_vector(3 downto 0);
      k: in std_logic;
      carry: out std_logic;
      sum: out std_logic_vector(3 downto 0)
    );
  end component four_bit_adder;

  signal carry0: std_logic;

begin

  foura0: four_bit_adder
          PORT MAP(
            a(0) => a(0),
            a(1) => a(1),
            a(2) => a(2),
            a(3) => a(3),
            b(0) => b(0),
            b(1) => b(1),
            b(2) => b(2),
            b(3) => b(3),
            k => '0',
            carry => carry0,
            sum(0) => sum(0),
            sum(1) => sum(1),
            sum(2) => sum(2),
            sum(3) => sum(3)
          );
  
  foura1: four_bit_adder
          PORT MAP(
            a(0) => a(4),
            a(1) => a(5),
            a(2) => a(6),
            a(3) => a(7),
            b(0) => b(4),
            b(1) => b(5),
            b(2) => b(6),
            b(3) => b(7),
            k => carry0,
            carry => carry,
            sum(0) => sum(4),
            sum(1) => sum(5),
            sum(2) => sum(6),
            sum(3) => sum(7)
          );

end behav_eight_adder ; -- behav_eight_adder
--------------------------------------------------------------------
-- 4 BIT ADDER

library ieee;
use ieee.std_logic_1164.all;

entity four_bit_adder is
  port(
      a: in std_logic_vector(3 downto 0);
      b: in std_logic_vector(3 downto 0);
      k: in std_logic;
      carry: out std_logic;
      sum: out std_logic_vector(3 downto 0)
  );
end four_bit_adder;

architecture behav_four_adder of four_bit_adder is

  component full_adder is
      port(
          a, b, carry_in: in std_logic;
          carry_out, sum: out std_logic
      );
  end component full_adder;

  signal carry1, carry2, carry3: std_logic;

begin

  fa0: full_adder
          PORT MAP(
            a => a(0),
            b => b(0),
            carry_in => k,
            carry_out => carry1,
            sum => sum(0)
          );

  fa1: full_adder
          PORT MAP(
            a => a(1),
            b => b(1),
            carry_in => carry1,
            carry_out => carry2,
            sum => sum(1)
          );
        
  fa2: full_adder
          PORT MAP(
            a => a(2),
            b => b(2),
            carry_in => carry2,
            carry_out => carry3,
            sum => sum(2)
          );

  fa3: full_adder
          PORT MAP(
            a=> a(3),
            b => b(3),
            carry_in => carry3,
            carry_out => carry,
            sum => sum(3)
          );

end behav_four_adder ; -- behav_adder

--------------------------------------------------------------------
-- FULL ADDER

library ieee;
use ieee.std_logic_1164.all;

entity full_adder is
  port (
    a, b, carry_in: in std_logic;
    carry_out, sum: out std_logic
  ) ;
end full_adder;

architecture behav_full of full_adder is

  component half_adder is
      port(
          a, b: in std_logic;
          carry, sum: out std_logic
      );
  end component half_adder;

  signal x, y, z: std_logic;
  
begin

  ha1: half_adder
          PORT MAP(
              a => a,
              b => b,
              sum => x,
              carry => y
          );
  
  ha2: half_adder
          PORT MAP(
              a => carry_in,
              b => x,
              sum => sum,
              carry => z
          );

  carry_out <= z OR y;

end behav_full ; -- behav_full

--------------------------------------------------------------------
-- HALF ADDER

library ieee;
use ieee.std_logic_1164.all;

entity half_adder is
  port (
    a, b: in std_logic;
    carry, sum: out std_logic
  ) ;
end half_adder;

architecture behav_half of half_adder is
begin
    sum <= a XOR b;
    carry <= a AND b;
end behav_half ; -- behav_half

--------------------------------------------------------------------