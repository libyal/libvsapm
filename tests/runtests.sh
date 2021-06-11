#!/bin/sh
# Script to run tests
#
# Version: 20201121

if test -f ${PWD}/libvsapm/.libs/libvsapm.1.dylib && test -f ./pyvsapm/.libs/pyvsapm.so;
then
	install_name_tool -change /usr/local/lib/libvsapm.1.dylib ${PWD}/libvsapm/.libs/libvsapm.1.dylib ./pyvsapm/.libs/pyvsapm.so;
fi

make check CHECK_WITH_STDERR=1;
RESULT=$?;

if test ${RESULT} -ne 0 && test -f tests/test-suite.log;
then
	cat tests/test-suite.log;
fi
exit ${RESULT};

