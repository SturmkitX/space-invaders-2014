Original implementation of the project:

C++90
SDL2 (+audio, net, image, ttf)
Multiplayer support over TCP (UDP is unstable)
Database access through external script written in Java and JDBC connector

Written for Windows, compiled with MinGW compiler tools

Recompiled for Linux, gcc 8

Memory results are found in:
-- massif.out.XXXXX file (cpu usage data, can be visualized as a graph using massif-visualizer)
-- memcheck.out (memory leaks, tested single player, music change, multiplayer; there are definitely some memory leaks)

Small portions of code have been modified in order to be compatible with Linux (such as removing windows.h references)
Logic is exactly the same

Modifications, up until now:
[X] Database connection through MariaDB/C Connector
    -- in some cases it may fail with Segmentation fault, in that case run this in terminal:
    ln -s /var/run/mysqld/mysqld.sock /tmp/mysql.sock

