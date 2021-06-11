# Note that we cannot use: AUTOMAKE_OPTIONS = subdir-objects
# subdir-objects will compile the source files to a single version of Python.
# Since subdir-objects is being deprecated we copy the source files instead.
am__installdirs = "$(DESTDIR)$(pyexecdir3)"
pyexecdir = $(pyexecdir3)

if HAVE_PYTHON3
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

am_pyvsapm_la_rpath = -rpath $(pyexecdir3)

BUILT_SOURCES = \
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

pyexec_LTLIBRARIES = pyvsapm.la

nodist_pyvsapm_la_SOURCES = $(BUILT_SOURCES)

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

pyvsapm_la_CPPFLAGS = $(PYTHON3_CPPFLAGS)
pyvsapm_la_LDFLAGS  = -module -avoid-version $(PYTHON3_LDFLAGS)

$(BUILT_SOURCES):
	/bin/cp -f $(top_srcdir)/pyvsapm/$@ $@

endif

MAINTAINERCLEANFILES = \
	Makefile.in

clean-local:
	/bin/rm -f pyvsapm*.[ch]

distclean: clean
	/bin/rm -f Makefile

