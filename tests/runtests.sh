#!/bin/sh
# Script to run tests
#
# Version: 20260609

if test -f ${PWD}/libvsapm/.libs/libvsapm.1.dylib && test -f ./pyvsapm/.libs/pyvsapm.so
then
	install_name_tool -change /usr/local/lib/libvsapm.1.dylib ${PWD}/libvsapm/.libs/libvsapm.1.dylib ./pyvsapm/.libs/pyvsapm.so
fi

make check-build > /dev/null

make check $@
RESULT=$?

if test ${RESULT} -ne 0
then
	find . -name \*.log -path \*.dir/\*/\*.log -print -exec cat {} \;
fi
exit ${RESULT}

