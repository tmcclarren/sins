SINS
-----------
Packet analyser for Everquest, ala ShowEQ

DESCRIPTION
-----------
SINS sits passively and waits for Everquest packets to pass by
on the ethernet card. It rebuilds the data stream and displays
useful information about the data being sent between client and
server.

Please read the CHANGES and BUGS files for more information.

INSTALLATION
------------
See the file 'INSTALL' for installation and configuration information.

RUNNING
-------
SINS needs to have root access to be able to receive the packets,
so make sure you run it as root.

Usage:
  ./sins --help

shows current command line arguments.  Also look at the 
conf/sins.conf.dist file for configuration file options and defaults.
