LIBRARY IEEE;
USE ieee.std_logic_1164.ALL;

ENTITY smart_house IS
  PORT (
    -- INPUTS:

    -- open(1) or closed(0) flag for all 4 windows
    status_window : IN STD_LOGIC_VECTOR(2 DOWNTO 0);
    -- open(1) or closed(0) and locked (0) or unlocked(1) flags for door
    status_door : IN STD_LOGIC_VECTOR(1 DOWNTO 0);
    -- open(1) or closed(0) flag for secure mode
    secure_mode : IN STD_LOGIC;
    -- night(1) or day(0) flag for daylight sensor
    daylight_sensor : IN STD_LOGIC;
    -- raining(1) or not raining(0) flag for weather sensor
    weather_sensor : IN STD_LOGIC;
    -- temperature sensors (-20ºC to 50ªC)
    temperature_sensor_1 : IN STD_LOGIC_VECTOR(7 DOWNTO 0);
    temperature_sensor_2 : IN STD_LOGIC_VECTOR(7 DOWNTO 0);
    -- water level sensor for A water tank -
    level_tankA : IN STD_LOGIC_VECTOR(3 DOWNTO 0);
    -- max(1) or not max(0)
    max_tankB : IN STD_LOGIC;

    -- OUTPUTS:

    -- problem(1) or safe(0): 
    -- (1): secure_mode(1) && status_window(has 1)
    -- (1): status_door(1,1);
    security_alert : OUT STD_LOGIC;
    -- problem(1) or safe(0)
    -- (1): secure_mode(1) && status_door(any,1) && status_window(has 1)
    wdopen_alert : OUT STD_LOGIC_VECTOR(2 DOWNTO 0);
    -- problem(1) or safe(0)
    -- (1): weather_sensor(1) && status_window(has 1) !! status_door(1, any);
    wdopen_rain_alert : OUT STD_LOGIC;
    -- problem(1) or safe(0)
    -- (1): daylight_sensor(1) && status_window(has 1)
    wopen_night_alert : OUT STD_LOGIC;
    -- problem(1) or safe(0)
    -- (1): temperature_sensor(media < 15ºC) && status_window(has 1)
    wopen_lowtemp_alert : OUT STD_LOGIC;
    -- on(1) or off(0)
    -- (1): water_level_A > 20
    -- (0): max_tankB == 100
    water_pump : OUT STD_LOGIC;
    -- active(1) or disabled(0)
    -- (1): water_level_A < 15
    eletrovalve : OUT STD_LOGIC

  );
END smart_house;

ARCHITECTURE arch_smart_house OF smart_house IS

  -- COMPONENT security IS
  --   PORT (
  --     status_window : IN STD_LOGIC_VECTOR(2 DOWNTO 0);
  --     status_door : IN STD_LOGIC_VECTOR(1 DOWNTO 0);
  --     secure_mode : IN STD_LOGIC;
  --     security_alert : OUT STD_LOGIC;
  --     wdopen_alert : OUT STD_LOGIC_VECTOR(2 DOWNTO 0)
  --   );
  -- END COMPONENT security;

BEGIN

  -- security_comp : security PORT MAP(
  --   status_window(0) => status_window(0),
  --   status_window(1) => status_window(1),
  --   status_window(2) => status_window(2),
  --   status_door(0) => status_door(0),
  --   status_door(1) => status_door(1),
  --   secure_mode => secure_mode,
  --   security_alert => security_alert,
  --   wdopen_alert(0) => wdopen_alert(0),
  --   wdopen_alert(1) => wdopen_alert(1)
  -- );

  -- Security Alert Process
  PROCESS (secure_mode, status_window, status_door)
  BEGIN
    IF (secure_mode = '1') AND ((status_window(0) = '1') OR (status_window(1) = '1') OR (status_window(2) = '1')) THEN
      security_alert <= '1';
    ELSIF (status_door(1) = '0') AND (status_door(0) = '1') THEN
      security_alert <= '1';
    ELSE
      security_alert <= '0';
    END IF;
    -- FOR i IN 0 TO 2 LOOP
    --   IF (status_window(i) = '1') THEN
    --     security_alert <= '1';
    --   END IF;
    -- END LOOP;
  END PROCESS;

END arch_smart_house; -- arch_smart_house

-- -- -- ===========================================================================================

-- LIBRARY IEEE;
-- USE ieee.std_logic_1164.ALL;

-- ENTITY security IS
--   PORT (
--     status_window : IN STD_LOGIC_VECTOR(2 DOWNTO 0);
--     status_door : IN STD_LOGIC_VECTOR(1 DOWNTO 0);
--     secure_mode : IN STD_LOGIC;
--     security_alert : OUT STD_LOGIC;
--     wdopen_alert : OUT STD_LOGIC_VECTOR(2 DOWNTO 0)
--   );
-- END security;

-- ARCHITECTURE arch_security OF security IS

-- BEGIN
--   -- Security Alert Process
--   PROCESS (secure_mode, status_window, status_door)
--   BEGIN
--     IF (secure_mode = '1') AND ((status_window(0) = '1') OR (status_window(1) = '1') OR (status_window(2) = '1')) THEN
--       security_alert <= '1';
--     ELSIF (status_door(1) = '0') AND (status_door(0) = '1') THEN
--       security_alert <= '1';
--     END IF;
--     FOR i IN 0 TO 2 LOOP
--       IF (status_window(i) = '1') THEN
--         security_alert <= '1';
--       END IF;
--     END LOOP;
--   END PROCESS;

--   -- Open window alert
--   PROCESS (secure_mode, status_window, status_door)
--   BEGIN
--     FOR janela IN 0 TO 3 LOOP
--       IF (secure_mode = '1') AND ((status_door(0) = '1') OR (status_window(janela) = '1')) THEN
--         wdopen_alert <= '1';
--       END IF;
--     END LOOP;
--   END PROCESS;

-- END arch_security; -- arch_security

-- -- -- ===========================================================================================

-- LIBRARY IEEE;
-- USE ieee.std_logic_1164.ALL;

-- ENTITY crepuscular_system IS
--   PORT (
--     status_window : IN STD_LOGIC_VECTOR(2 DOWNTO 0);
--     daylight_sensor : IN STD_LOGIC;
--     wopen_night_alert : OUT STD_LOGIC
--   );
-- END crepuscular_system;

-- ARCHITECTURE arch_crepuscular_system OF crepuscular_system IS

-- BEGIN

--   -- Window open at night alert
--   PROCESS (daylight_sensor, status_window)
--   BEGIN
--     FOR janela IN 0 TO 3 LOOP
--       IF (daylight_sensor = '1') AND (status_window(janela) = '1') THEN
--         wopen_night_alert <= '1';
--       END IF;
--     END LOOP;
--   END PROCESS;

-- END arch_crepuscular_system; -- arch_crepuscular_system

-- -- -- ===========================================================================================

-- LIBRARY IEEE;
-- USE ieee.std_logic_1164.ALL;

-- ENTITY weather_system IS
--   PORT (
--     weather_sensor : IN STD_LOGIC;
--     status_window : IN STD_LOGIC_VECTOR(2 DOWNTO 0);
--     status_door : IN STD_LOGIC_VECTOR(1 DOWNTO 0);
--     wdopen_rain_alert : OUT STD_LOGIC
--   );
-- END weather_system;

-- ARCHITECTURE arch_weather_system OF weather_system IS

-- BEGIN

--   -- Window with rain alert
--   PROCESS (weather_sensor, status_window, status_door)
--   BEGIN
--     FOR janela IN 0 TO 3 LOOP
--       IF (weather_sensor = '1') AND (status_door(1) = '1') AND (status_window(janela) = '1') THEN
--         wdopen_rain_alert <= '1';
--       END IF;
--     END LOOP;
--   END PROCESS;

--   -- -- Window open low temperature alert
--   -- PROCESS ()
--   -- BEGIN

--   -- END PROCESS;

-- END arch_weather_system; -- arch_weather_system

-- -- -- ===========================================================================================
-- LIBRARY IEEE;
-- USE ieee.std_logic_1164.ALL;

-- ENTITY water_system IS
--   PORT (
--     level_tankA : IN STD_LOGIC_VECTOR(3 DOWNTO 0);
--     max_tankB : IN STD_LOGIC;
--     water_pump : IN STD_LOGIC;
--     electrovalve : OUT STD_LOGIC
--   );
-- END water_system;

-- ARCHITECTURE arch_water_system OF water_system IS

-- BEGIN

--   -- Water pump activation
--   PROCESS (level_tankA, max_tankB)
--   BEGIN
--     IF (level_tankA(3) = '1') AND (max_tankB = '0') THEN
--       water_pump <= '1';
--     END IF;
--   END PROCESS;

--   -- Electrovalve activation
--   PROCESS (level_tank_A)
--   BEGIN
--     IF (level_tankA(3) = '0') THEN
--       eletrovalve <= '1';
--     END IF;
--   END PROCESS;
-- END arch_water_system;