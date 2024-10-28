# CMake generated Testfile for 
# Source directory: /home/fx/projects/otus-cpp/otus-cpp
# Build directory: /home/fx/projects/otus-cpp/otus-cpp/build
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(ipfilter_cli "sh" "-c" "cat /home/fx/projects/otus-cpp/otus-cpp/build/ip_filter.tsv | /home/fx/projects/otus-cpp/otus-cpp/build/ipfilter_cli | md5sum | grep -q '24e7a7b2270daee89c64d3ca5fb3da1a'")
set_tests_properties(ipfilter_cli PROPERTIES  _BACKTRACE_TRIPLES "/home/fx/projects/otus-cpp/otus-cpp/CMakeLists.txt;56;add_test;/home/fx/projects/otus-cpp/otus-cpp/CMakeLists.txt;0;")
