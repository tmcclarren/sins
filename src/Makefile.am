INCLUDES = \
$(QT_INCLUDES)\
$(X_INCLUDES)\
-I/usr/include/pcap\
-DCONFDIR=\"$(pkgdatadir)/\"

bin_PROGRAMS = sins

sins_SOURCES = \
main.cpp\
spawn.cpp\
util.cpp\
baselistview.cpp\
m_baselistview.cpp\
basewindow.cpp\
m_basewindow.cpp\
bigtextwindow.cpp\
m_bigtextwindow.cpp\
category.cpp\
m_category.cpp\
compass.cpp\
m_compass.cpp\
dropwindow.cpp\
m_dropwindow.cpp\
experience.cpp\
m_experience.cpp\
filter.cpp\
m_filter.cpp\
finder.cpp\
m_finder.cpp\
interface.cpp\
m_interface.cpp\
itemmgr.cpp\
m_itemmgr.cpp\
log.cpp\
m_log.cpp\
map.cpp\
m_map.cpp\
packet.cpp\
m_packet.cpp\
player.cpp\
preferences.cpp\
m_preferences.cpp\
m_player.cpp\
skilllist.cpp\
m_skilllist.cpp\
spawnlist.cpp\
m_spawnlist.cpp\
spawnmonitor.cpp\
m_spawnmonitor.cpp\
spawnpointlist.cpp\
m_spawnpointlist.cpp\
spells.cpp\
m_spells.cpp\
spelllist.cpp\
m_spelllist.cpp\
statlist.cpp\
m_statlist.cpp\
vpacket.cpp

sins_LDADD = $(QT_LDFLAGS) -lqt-mt	
# The following will achieve a static build (comment out the above)
#sins_LDADD=-L/usr/X11R6/lib $(QT_LDFLAGS) -lqt-mt -lX11 -lXext -lSM -lICE
#sins_LDFLAGS=-Xlinker -Bstatic

EXTRA_DIST = \
main.h\
spawn.h\
util.h\
baselistview.h\
basewindow.h\
bigtextwindow.h\
category.h\
compass.h\
dropwindow.h\
everquest.h\
experience.h\
filter.h\
finder.h\
interface.h\
itemmgr.h\
listviewwrapper.h\
log.h\
main.h\
map.h\
msgdlg.h\
opcodes.h\
packet.h\
player.h\
preferences.h\
skilllist.h\
spawn.h\
spawnlist.h\
spawnmonitor.h\
spawnpointlist.h\
spelldat.h\
spelllist.h\
spells.h\
spelltimes.h\
statlist.h\
util.h\
vpacket.h\
clear.xpm\
cross.xpm

BUILT_SOURCES = \
m_baselistview.cpp\
m_basewindow.cpp\
m_bigtextwindow.cpp\
m_category.cpp\
m_dropwindow.cpp\
m_experience.cpp\
m_filter.cpp\
m_finder.cpp\
m_interface.cpp\
m_itemmgr.cpp\
m_log.cpp\
m_map.cpp\
m_packet.cpp\
m_player.cpp\
m_preferences.cpp\
m_spawnlist.cpp\
m_spawnmonitor.cpp\
m_spawnpointlist.cpp\
m_spells.cpp\
m_spelllist.cpp\
m_compass.cpp

CLEANFILES = $(BUILT_SOURCES)

MAINTAINERCLEANFILES = Makefile.in

m_%.cpp: %.h %.cpp
	$(MOC) $< -o $@

