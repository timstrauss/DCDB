#!/bin/bash

rm -rf coverage.info
rm -rf real_coverage.info
rm -rf zero_coverage.info
lcov --capture --directory . --output-file real_coverage.info
lcov --capture --initial --directory . --output-file zero_coverage.info
lcov --add-tracefile real_coverage.info --add-tracefile zero_coverage.info --output-file coverage.info
rm -rf real_coverage.info
rm -rf zero_coverage.info
lcov --remove coverage.info '/usr/*' --output-file coverage.info
conanHome=$(conan config home)
conanFilter="${conanHome}/*"
currentDir=$(pwd)
testFilter="${currentDir}/tests/*"
lcov --remove coverage.info "$conanFilter" --output-file coverage.info
lcov --remove coverage.info "$testFilter" --output-file coverage.info
lcov --list coverage.info
genhtml coverage.info --output-directory out