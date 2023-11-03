AUTOMAKE_OPTIONS = subdir-objects

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
	@LIBVSAPM_DLL_IMPORT@

if HAVE_PYTHON_TESTS
TESTS_PYVSAPM = \
	test_python_module.sh
endif

TESTS = \
	test_library.sh \
	test_tools.sh \
	test_vsapminfo.sh \
	$(TESTS_PYVSAPM)

check_SCRIPTS = \
	pyvsapm_test_partition.py \
	pyvsapm_test_support.py \
	pyvsapm_test_volume.py \
	test_library.sh \
	test_manpage.sh \
	test_python_module.sh \
	test_runner.sh \
	test_tools.sh \
	test_vsapminfo.sh

EXTRA_DIST = \
	$(check_SCRIPTS)

check_PROGRAMS = \
	vsapm_test_error \
	vsapm_test_io_handle \
	vsapm_test_notify \
	vsapm_test_partition \
	vsapm_test_partition_map_entry \
	vsapm_test_sector_data \
	vsapm_test_support \
	vsapm_test_tools_info_handle \
	vsapm_test_tools_output \
	vsapm_test_tools_signal \
	vsapm_test_volume

vsapm_test_error_SOURCES = \
	vsapm_test_error.c \
	vsapm_test_libvsapm.h \
	vsapm_test_macros.h \
	vsapm_test_unused.h

vsapm_test_error_LDADD = \
	../libvsapm/libvsapm.la

vsapm_test_io_handle_SOURCES = \
	vsapm_test_io_handle.c \
	vsapm_test_libcerror.h \
	vsapm_test_libvsapm.h \
	vsapm_test_macros.h \
	vsapm_test_memory.c vsapm_test_memory.h \
	vsapm_test_unused.h

vsapm_test_io_handle_LDADD = \
	../libvsapm/libvsapm.la \
	@LIBCERROR_LIBADD@

vsapm_test_notify_SOURCES = \
	vsapm_test_libcerror.h \
	vsapm_test_libvsapm.h \
	vsapm_test_macros.h \
	vsapm_test_notify.c \
	vsapm_test_unused.h

vsapm_test_notify_LDADD = \
	../libvsapm/libvsapm.la \
	@LIBCERROR_LIBADD@

vsapm_test_partition_SOURCES = \
	vsapm_test_functions.c vsapm_test_functions.h \
	vsapm_test_getopt.c vsapm_test_getopt.h \
	vsapm_test_libbfio.h \
	vsapm_test_libvsapm.h \
	vsapm_test_libvsapm.h \
	vsapm_test_macros.h \
	vsapm_test_memory.c vsapm_test_memory.h \
	vsapm_test_partition.c \
	vsapm_test_rwlock.c vsapm_test_rwlock.h

vsapm_test_partition_LDADD = \
	@LIBBFIO_LIBADD@ \
	@LIBCPATH_LIBADD@ \
	@LIBCFILE_LIBADD@ \
	@LIBUNA_LIBADD@ \
	@LIBCSPLIT_LIBADD@ \
	@LIBCNOTIFY_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	@LIBCDATA_LIBADD@ \
	../libvsapm/libvsapm.la \
	@LIBCTHREADS_LIBADD@ \
	@LIBCERROR_LIBADD@ \
	@PTHREAD_LIBADD@

vsapm_test_partition_map_entry_SOURCES = \
	vsapm_test_functions.c vsapm_test_functions.h \
	vsapm_test_libbfio.h \
	vsapm_test_libcerror.h \
	vsapm_test_libvsapm.h \
	vsapm_test_macros.h \
	vsapm_test_memory.c vsapm_test_memory.h \
	vsapm_test_partition_map_entry.c \
	vsapm_test_unused.h

vsapm_test_partition_map_entry_LDADD = \
	@LIBBFIO_LIBADD@ \
	@LIBCPATH_LIBADD@ \
	@LIBCFILE_LIBADD@ \
	@LIBUNA_LIBADD@ \
	@LIBCSPLIT_LIBADD@ \
	@LIBCNOTIFY_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	@LIBCDATA_LIBADD@ \
	../libvsapm/libvsapm.la \
	@LIBCERROR_LIBADD@

vsapm_test_sector_data_SOURCES = \
	vsapm_test_functions.c vsapm_test_functions.h \
	vsapm_test_libbfio.h \
	vsapm_test_libcerror.h \
	vsapm_test_libvsapm.h \
	vsapm_test_macros.h \
	vsapm_test_memory.c vsapm_test_memory.h \
	vsapm_test_sector_data.c \
	vsapm_test_unused.h

vsapm_test_sector_data_LDADD = \
	@LIBBFIO_LIBADD@ \
	@LIBCPATH_LIBADD@ \
	@LIBCFILE_LIBADD@ \
	@LIBUNA_LIBADD@ \
	@LIBCSPLIT_LIBADD@ \
	@LIBCNOTIFY_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	@LIBCDATA_LIBADD@ \
	../libvsapm/libvsapm.la \
	@LIBCERROR_LIBADD@

vsapm_test_support_SOURCES = \
	vsapm_test_functions.c vsapm_test_functions.h \
	vsapm_test_getopt.c vsapm_test_getopt.h \
	vsapm_test_libbfio.h \
	vsapm_test_libcerror.h \
	vsapm_test_libclocale.h \
	vsapm_test_libcnotify.h \
	vsapm_test_libuna.h \
	vsapm_test_libvsapm.h \
	vsapm_test_macros.h \
	vsapm_test_memory.c vsapm_test_memory.h \
	vsapm_test_support.c \
	vsapm_test_unused.h

vsapm_test_support_LDADD = \
	@LIBBFIO_LIBADD@ \
	@LIBCPATH_LIBADD@ \
	@LIBCFILE_LIBADD@ \
	@LIBUNA_LIBADD@ \
	@LIBCSPLIT_LIBADD@ \
	@LIBCNOTIFY_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	@LIBCDATA_LIBADD@ \
	../libvsapm/libvsapm.la \
	@LIBCERROR_LIBADD@

vsapm_test_tools_info_handle_SOURCES = \
	../vsapmtools/info_handle.c ../vsapmtools/info_handle.h \
	vsapm_test_libcerror.h \
	vsapm_test_macros.h \
	vsapm_test_memory.c vsapm_test_memory.h \
	vsapm_test_tools_info_handle.c \
	vsapm_test_unused.h

vsapm_test_tools_info_handle_LDADD = \
	@LIBCLOCALE_LIBADD@ \
	../libvsapm/libvsapm.la \
	@LIBCERROR_LIBADD@

vsapm_test_tools_output_SOURCES = \
	../vsapmtools/vsapmtools_output.c ../vsapmtools/vsapmtools_output.h \
	vsapm_test_libcerror.h \
	vsapm_test_macros.h \
	vsapm_test_tools_output.c \
	vsapm_test_unused.h

vsapm_test_tools_output_LDADD = \
	../libvsapm/libvsapm.la \
	@LIBCERROR_LIBADD@

vsapm_test_tools_signal_SOURCES = \
	../vsapmtools/vsapmtools_signal.c ../vsapmtools/vsapmtools_signal.h \
	vsapm_test_libcerror.h \
	vsapm_test_macros.h \
	vsapm_test_tools_signal.c \
	vsapm_test_unused.h

vsapm_test_tools_signal_LDADD = \
	../libvsapm/libvsapm.la \
	@LIBCERROR_LIBADD@

vsapm_test_volume_SOURCES = \
	vsapm_test_functions.c vsapm_test_functions.h \
	vsapm_test_getopt.c vsapm_test_getopt.h \
	vsapm_test_libbfio.h \
	vsapm_test_libcerror.h \
	vsapm_test_libclocale.h \
	vsapm_test_libcnotify.h \
	vsapm_test_libuna.h \
	vsapm_test_libvsapm.h \
	vsapm_test_macros.h \
	vsapm_test_memory.c vsapm_test_memory.h \
	vsapm_test_rwlock.c vsapm_test_rwlock.h \
	vsapm_test_unused.h \
	vsapm_test_volume.c

vsapm_test_volume_LDADD = \
	@LIBBFIO_LIBADD@ \
	@LIBCPATH_LIBADD@ \
	@LIBCFILE_LIBADD@ \
	@LIBUNA_LIBADD@ \
	@LIBCSPLIT_LIBADD@ \
	@LIBCNOTIFY_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	@LIBCDATA_LIBADD@ \
	../libvsapm/libvsapm.la \
	@LIBCTHREADS_LIBADD@ \
	@LIBCERROR_LIBADD@ \
	@PTHREAD_LIBADD@

MAINTAINERCLEANFILES = \
	Makefile.in

distclean: clean
	-rm -f Makefile

