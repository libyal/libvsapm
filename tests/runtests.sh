#!/bin/sh
# Script to run tests
#
# Version: 20260714

if [ -f "${PWD}/libvsapm/.libs/libvsapm.1.dylib" ] && [ -f ./pyvsapm/.libs/pyvsapm.so ]
then
    install_name_tool -change /usr/local/lib/libvsapm.1.dylib "${PWD}/libvsapm/.libs/libvsapm.1.dylib" ./pyvsapm/.libs/pyvsapm.so
fi

make check-build > /dev/null

# shellcheck disable=SC2068
make check $@
RESULT=$?

if [ ${RESULT} -ne 0 ]
then
    find . -name \*.log -path \*.dir/\*/\*.log -print -exec cat {} \;
fi
exit ${RESULT}

