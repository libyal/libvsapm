if HAVE_PYTHON
AM_CFLAGS = \
	-I$(top_srcdir)/include \
	-I$(top_srcdir)/common \
	@LIBCERROR_CPPFLAGS@ \
	@LIBCDATA_CPPFLAGS@ \
	@LIBCLOCALE_CPPFLAGS@ \
	@LIBCSPLIT_CPPFLAGS@ \
	@LIBUNA_CPPFLAGS@ \
	@LIBCFILE_CPPFLAGS@ \
	@LIBCPATH_CPPFLAGS@ \
	@LIBBFIO_CPPFLAGS@ \
	@LIBVSAPM_DLL_IMPORT@

pyexec_LTLIBRARIES = pyvsapm.la

pyvsapm_la_SOURCES = \
	pyvsapm.c pyvsapm.h \
	pyvsapm_error.c pyvsapm_error.h \
	pyvsapm_file_object_io_handle.c pyvsapm_file_object_io_handle.h \
	pyvsapm_integer.c pyvsapm_integer.h \
	pyvsapm_libbfio.h \
	pyvsapm_libcerror.h \
	pyvsapm_libclocale.h \
	pyvsapm_libvsapm.h \
	pyvsapm_partition.c pyvsapm_partition.h \
	pyvsapm_partitions.c pyvsapm_partitions.h \
	pyvsapm_python.h \
	pyvsapm_unused.h \
	pyvsapm_volume.c pyvsapm_volume.h

pyvsapm_la_LIBADD = \
	@LIBCERROR_LIBADD@ \
	../libvsapm/libvsapm.la \
	@LIBCDATA_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	@LIBCSPLIT_LIBADD@ \
	@LIBUNA_LIBADD@ \
	@LIBCFILE_LIBADD@ \
	@LIBCPATH_LIBADD@ \
	@LIBBFIO_LIBADD@

pyvsapm_la_CPPFLAGS = $(PYTHON_CPPFLAGS)
pyvsapm_la_LDFLAGS  = -module -avoid-version $(PYTHON_LDFLAGS)

endif

MAINTAINERCLEANFILES = \
	Makefile.in

distclean: clean
	-rm -f Makefile

