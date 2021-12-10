# CMake generated Testfile for 
# Source directory: /home/corentin/Documents/sepc/tp_threads
# Build directory: /home/corentin/Documents/sepc/tp_threads/build
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(CommonPthreadError "perl" "/home/corentin/Documents/sepc/tp_threads/tests/pthcocci.pl")
set_tests_properties(CommonPthreadError PROPERTIES  _BACKTRACE_TRIPLES "/home/corentin/Documents/sepc/tp_threads/CMakeLists.txt;54;add_test;/home/corentin/Documents/sepc/tp_threads/CMakeLists.txt;0;")
