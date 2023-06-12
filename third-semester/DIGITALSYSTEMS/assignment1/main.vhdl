library ieee;
use ieee.std_logic_1164.all;

-- type temperatureArray is array (1 downto 0) of integer range -20 to 50;

entity smart_house is
  port (
    -- INPUTS:

    -- open(1) or closed(0) flag for all 4 windows
    status_window: in std_logic_vector(2 downto 0);
    -- open(1) or closed(0) and locked (1) or unlocked(0) flags for door
    status_door: in std_logic_vector(1 downto 0);
    -- open(1) or closed(0) flag for secure mode
    secure_mode: in std_logic;
    -- night(1) or day(0) flag for daylight sensor
    daylight_sensor: in std_logic;
    -- raining(1) or not raining(0) flag for weather sensor
    weather_sensor: in std_logic;
    -- temperature sensors (-20ºC to 50ªC)
    -- temperature_sensor: in temperatureArray;
    -- water level sensor for A water tank
    -- water_level_A: in integer;
    -- max(1) or not max(0)
    max_tankB: in std_logic;

    -- OUTPUTS:

    -- problem(1) or safe(0): 
    -- (1): secure_mode(1) && status_window(has 1)
    -- (1): status_door(1,1);
    security_alert: out std_logic;
    -- problem(1) or safe(0)
    -- (1): secure_mode(1) && status_door(any,1) && status_window(has 1)
    window_open_alert: out std_logic_vector(2 downto 0);
    -- problem(1) or safe(0)
    -- (1): weather_sensor(1) && status_window(has 1) !! status_door(1, any);
    wdopen_rain_alert: out std_logic;
    -- problem(1) or safe(0)
    -- (1): daylight_sensor(1) && status_window(has 1)
    wopen_night_alert: out std_logic;
    -- problem(1) or safe(0)
    -- (1): temperature_sensor(media < 15ºC) && status_window(has 1)
    wopen_lowtemp_alert: out std_logic;
    -- on(1) or off(0)
    -- (1): water_level_A > 20
    -- (0): max_tankB == 100
    water_pump: out std_logic;
    -- active(1) or disabled(0)
    -- (1): water_level_A < 15
    eletrovalve: out std_logic

  ) ;
end smart_house;

architecture arch_smart_house of smart_house is
begin
    process(secure_mode, status_window, status_door)
    begin
        if (secure_mode = '1') and ((status_window(0) = '1') or (status_window(1) = '1') or (status_window(2) = '1')) then
            security_alert <= '1';
        elsif (status_door(0) = '1') and (status_door(1) = '1') then
            security_alert <= '1';
        end if;
    end process;
        

end arch_smart_house ; -- arch_smart_house

-- -- ===========================================================================================

-- entity security is
--   port (
--     clock
--   ) ;
-- end security;

-- -- ===========================================================================================

-- entity crepuscular_sensor is
--   port (
--     clock
--   ) ;
-- end crepuscular_sensor;

-- -- ===========================================================================================

-- entity water_system is
--   port (
--     clock
--   ) ;
-- end water_system;

-- -- INPUTS:

-- -- open(1) or closed(0) flag for all 4 windows
-- status_window: in std_logic_vector(2 downto 0);
-- -- open(1) or closed(0) and locked (1) or unlocked(0) flags for door
-- status_door: in std_logic_vector(1 downto 0);
-- -- open(1) or closed(0) flag for secure mode
-- secure_mode: in std_logic;
-- -- night(1) or day(0) flag for daylight sensor
-- daylight_sensor: in std_logic;
-- -- raining(1) or not raining(0) flag for weather sensor
-- weather_sensor: in std_logic;
-- -- temperature sensors (-20ºC to 50ªC)
-- temperature_sensor_: in std_logic;
-- -- water level sensor for A water tank
-- water_level_A: in integer;
-- -- max(1) or not max(0)
-- max_tankB: in std_logic;

-- -- OUTPUTS:

-- -- problem(1) or safe(0): 
--   -- (1): secure_mode(1) && status_window(has 1)
--   -- (1): status_door(1,1)
-- security_alert: out std_logic;
-- -- problem(1) or safe(0)
--   -- (1): secure_mode(1) && status_door(any,1) && status_window(has 1)
-- window_open_alert: out std_logic_vector(2 downto 0);
-- -- problem(1) or safe(0)
--   -- (1): weather_sensor(1) && status_window(has 1) !! status_door(1, any);
-- wdopen_rain_alert: out std_logic;
-- -- problem(1) or safe(0)
--   -- (1): daylight_sensor(1) && status_window(has 1)
-- wopen_night_alert: out std_logic;
-- -- problem(1) or safe(0)
--   -- (1): temperature_sensor(media < 15ºC) && status_window(has 1)
-- wopen_lowtemp_alert: out std_logic;
-- -- on(1) or off(0)
--   -- (1): water_level_A > 20
--   -- (0): max_tankB == 100
-- water_pump: out std_logic;
-- -- active(1) or disabled(0)
--   -- (1): water_level_A < 15
-- eletrovalve: out std_logic