include_HEADERS = \
	libvsapm.h

pkginclude_HEADERS = \
	libvsapm/codepage.h \
	libvsapm/definitions.h \
	libvsapm/error.h \
	libvsapm/extern.h \
	libvsapm/features.h \
	libvsapm/types.h

EXTRA_DIST = \
	libvsapm.h.in \
	libvsapm/definitions.h.in \
	libvsapm/features.h.in \
	libvsapm/types.h.in

MAINTAINERCLEANFILES = \
	Makefile.in

distclean: clean
	-rm -f libvsapm.h
	-rm -f libvsapm/definitions.h
	-rm -f libvsapm/features.h
	-rm -f libvsapm/types.h
	-rm -f Makefile

