AM_CPPFLAGS = \
	-I$(top_srcdir)/include \
	-I$(top_srcdir)/common \
	@LIBCERROR_CPPFLAGS@ \
	@LIBCDATA_CPPFLAGS@ \
	@LIBCLOCALE_CPPFLAGS@ \
	@LIBCNOTIFY_CPPFLAGS@ \
	@LIBCSPLIT_CPPFLAGS@ \
	@LIBUNA_CPPFLAGS@ \
	@LIBCFILE_CPPFLAGS@ \
	@LIBCPATH_CPPFLAGS@ \
	@LIBBFIO_CPPFLAGS@ \
	@LIBVSAPM_DLL_IMPORT@

AM_LDFLAGS = @STATIC_LDFLAGS@

bin_PROGRAMS = \
	vsapminfo

vsapminfo_SOURCES = \
	info_handle.c info_handle.h \
	vsapmtools_getopt.c vsapmtools_getopt.h \
	vsapmtools_i18n.h \
	vsapminfo.c \
	vsapmtools_libbfio.h \
	vsapmtools_libcerror.h \
	vsapmtools_libclocale.h \
	vsapmtools_libcnotify.h \
	vsapmtools_libuna.h \
	vsapmtools_libvsapm.h \
	vsapmtools_output.c vsapmtools_output.h \
	vsapmtools_signal.c vsapmtools_signal.h \
	vsapmtools_unused.h

vsapminfo_LDADD = \
	@LIBUNA_LIBADD@ \
	../libvsapm/libvsapm.la \
	@LIBCNOTIFY_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	@LIBCERROR_LIBADD@ \
	@LIBINTL@

MAINTAINERCLEANFILES = \
	Makefile.in

distclean: clean
	-rm -f Makefile

splint-local:
	@echo "Running splint on vsapminfo ..."
	-splint -preproc -redef $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(vsapminfo_SOURCES)

