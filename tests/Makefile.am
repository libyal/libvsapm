AUTOMAKE_OPTIONS = subdir-objects

AM_CPPFLAGS = \
	-I../include -I$(top_srcdir)/include \
	-I../common -I$(top_srcdir)/common \
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

BUILT_SOURCES = package.m4

check_AUTOTESTS = \
	test_library \
	test_manpages \
	test_tools

if HAVE_PYTHON_TESTS
check_AUTOTESTS += test_python_module
endif

check_SCRIPTS = \
	pyvsapm_test_partition.py \
	pyvsapm_test_support.py \
	pyvsapm_test_volume.py

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
	vsapm_test_extern.h \
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
	@LIBCERROR_LIBADD@ \
	@LIBINTL@

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
	vsapm_test_extern.h \
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

AUTOM4TE = autom4te
AUTOTEST = $(AUTOM4TE) --language=autotest

SUFFIXES = .at

.at:
	$(AM_V_GEN)rm -f $@ $@.tmp; \
	$(AUTOTEST) -I '$(srcdir)' -o $@.tmp $< && \
	mv $@.tmp $@

atconfig: $(top_builddir)/config.status
	cd $(top_builddir) && $(SHELL) ./config.status tests/$@

check-build: $(check_PROGRAMS)

check-local: $(check_AUTOTESTS)
	@fail=0; \
	for test_suite in $(check_AUTOTESTS); do \
		$(AM_TESTS_ENVIRONMENT) $(SHELL) "./$$test_suite" $(TESTSUITEFLAGS) || fail=1; \
		echo ""; \
	done; \
	exit $$fail

clean-local:
	for test_suite in $(check_AUTOTESTS); do \
		test ! -f "$$test_suite" || $(SHELL) "./$$test_suite" --clean; \
	done

package.m4: $(top_srcdir)/configure.ac
	$(AM_V_GEN):; \
	{ \
	  echo 'm4_define([AT_PACKAGE_NAME], [$(PACKAGE_NAME)])' ; \
	  echo 'm4_define([AT_PACKAGE_TARNAME], [$(PACKAGE_TARNAME)])' ; \
	  echo 'm4_define([AT_PACKAGE_VERSION], [$(PACKAGE_VERSION)])' ; \
	  echo 'm4_define([AT_PACKAGE_STRING], [$(PACKAGE_STRING)])' ; \
	  echo 'm4_define([AT_PACKAGE_BUGREPORT], [$(PACKAGE_BUGREPORT)])' ; \
	} > $@

test_inputs_libvsapm.at: generate_test_inputs.sh
	$(SHELL) $(srcdir)/generate_test_inputs.sh $(PACKAGE_NAME) libvsapm

test_inputs_pyvsapm.at: generate_test_inputs.sh
	$(SHELL) $(srcdir)/generate_test_inputs.sh $(PACKAGE_NAME) pyvsapm

test_inputs_vsapminfo.at: generate_test_inputs.sh
	$(SHELL) $(srcdir)/generate_test_inputs.sh $(PACKAGE_NAME) vsapminfo

test_library: \
	package.m4 \
	test_inputs_libvsapm.at \
	test_library.at \
	test_macros.at

test_manpages: \
	package.m4 \
	test_manpages.at

test_python_module: \
	package.m4 \
	test_inputs_pyvsapm.at \
	test_macros.at \
	test_python_module.at

test_tools: \
	package.m4 \
	test_inputs_vsapminfo.at \
	test_macros.at \
	test_tools.at

EXTRA_DIST = \
	$(check_AUTOTESTS:=.at) \
	$(check_SCRIPTS) \
	generate_test_inputs.sh \
	package.m4 \
	test_macros.at

CLEANFILES = \
	$(check_AUTOTESTS) \
	*.exe \
	*.tmp \
	notify_stream.log \
	test_inputs_*.at

DISTCLEANFILES = \
	*.log \
	atconfig \
	Makefile \
	Makefile.in

