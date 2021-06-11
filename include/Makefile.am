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
	/bin/rm -f libvsapm.h
	/bin/rm -f libvsapm/definitions.h
	/bin/rm -f libvsapm/features.h
	/bin/rm -f libvsapm/types.h
	/bin/rm -f Makefile

