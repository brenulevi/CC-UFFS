# Activity DBII

To run everything correctly, first execute the code below in cmd and after run script.sql in psql

1 - `cd /`\
2 - `sudo mkdir mypgtbs && cd mypgtbs`\
3 - `sudo mkdir mytb01 && cd mytb01`\
4 - `cd /`\
5 - `sudo chown postgres.postgres mypgtbs/`\
6 - `sudo chown postgres.postgres mypgtbs/mytb01/`\
7 - `cd /mypgtbs`\
8 - `sudo mkdir mytb02 && cd mytb02`\
9 - `cd /`\
10 - `sudo chown postgres.postgres mypgtbs/`\
11 - `sudo chown postgres.postgres mypgtbs/mytb02/`\
12 - `psql -h localhost -U postgres -d postgres`