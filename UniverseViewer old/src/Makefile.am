## Process this file with automake to produce Makefile.in

INCLUDES = \
	-DPACKAGE_DATA_DIR=\""$(datadir)"\" \
	-DPACKAGE_LOCALE_DIR=\""$(prefix)/$(DATADIRNAME)/locale"\" \
	@PACKAGE_CFLAGS@

bin_PROGRAMS = uv-2

uv_2_SOURCES = \
	main.c \
	support.c support.h \
	interface.c interface.h \
	callbacks.c callbacks.h \
	vector.c struct.h vector.h \
	distance.c struct.h distance.h space.h \
	quasar.c struct.h  vector.h distance.h quasar.h projection.h \
	projection.c struct.h vector.h projection.h \
	space.c struct.h space.h vector.h distance.h \
	isotrop.c struct.h

uv_2_LDADD = @PACKAGE_LIBS@

