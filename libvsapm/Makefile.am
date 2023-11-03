AM_CPPFLAGS = \
	-I$(top_srcdir)/include \
	-I$(top_srcdir)/common \
	@LIBCERROR_CPPFLAGS@ \
	@LIBCTHREADS_CPPFLAGS@ \
	@LIBCDATA_CPPFLAGS@ \
	@LIBCLOCALE_CPPFLAGS@ \
	@LIBCNOTIFY_CPPFLAGS@ \
	@LIBCSPLIT_CPPFLAGS@ \
	@LIBUNA_CPPFLAGS@ \
	@LIBCFILE_CPPFLAGS@ \
	@LIBCPATH_CPPFLAGS@ \
	@LIBBFIO_CPPFLAGS@ \
	@LIBFCACHE_CPPFLAGS@ \
	@LIBFDATA_CPPFLAGS@ \
	@PTHREAD_CPPFLAGS@ \
	@LIBVSAPM_DLL_EXPORT@

lib_LTLIBRARIES = libvsapm.la

libvsapm_la_SOURCES = \
	libvsapm.c \
	libvsapm_debug.c libvsapm_debug.h \
	libvsapm_definitions.h \
	libvsapm_error.c libvsapm_error.h \
	libvsapm_extern.h \
	libvsapm_io_handle.c libvsapm_io_handle.h \
	libvsapm_libbfio.h \
	libvsapm_libcdata.h \
	libvsapm_libcerror.h \
	libvsapm_libclocale.h \
	libvsapm_libcnotify.h \
	libvsapm_libcthreads.h \
	libvsapm_libfcache.h \
	libvsapm_libfdata.h \
	libvsapm_notify.c libvsapm_notify.h \
	libvsapm_partition.c libvsapm_partition.h \
	libvsapm_partition_map_entry.c libvsapm_partition_map_entry.h \
	libvsapm_sector_data.c libvsapm_sector_data.h \
	libvsapm_support.c libvsapm_support.h \
	libvsapm_types.h \
	libvsapm_unused.h \
	libvsapm_volume.c libvsapm_volume.h \
	vsapm_partition_map_entry.h

libvsapm_la_LIBADD = \
	@LIBCERROR_LIBADD@ \
	@LIBCTHREADS_LIBADD@ \
	@LIBCDATA_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	@LIBCNOTIFY_LIBADD@ \
	@LIBCSPLIT_LIBADD@ \
	@LIBUNA_LIBADD@ \
	@LIBCFILE_LIBADD@ \
	@LIBCPATH_LIBADD@ \
	@LIBBFIO_LIBADD@ \
	@LIBFCACHE_LIBADD@ \
	@LIBFDATA_LIBADD@ \
	@PTHREAD_LIBADD@

libvsapm_la_LDFLAGS = -no-undefined -version-info 1:0:0

EXTRA_DIST = \
	libvsapm_definitions.h.in \
	libvsapm.rc \
	libvsapm.rc.in

MAINTAINERCLEANFILES = \
	Makefile.in

distclean: clean
	-rm -f libvsapm_definitions.h
	-rm -f libvsapm.rc
	-rm -f Makefile

sources-local: $(BUILT_SOURCES)

splint-local:
	@echo "Running splint on libvsapm ..."
	-splint -preproc -redef $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(libvsapm_la_SOURCES)

