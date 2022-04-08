# CMake generated Testfile for 
# Source directory: /home/elizabeth/Documents/newProject4/p4_starter_code/p4_starter_code
# Build directory: /home/elizabeth/Documents/newProject4/p4_starter_code/p4_starter_code
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(student-tests "student-tests")
set_tests_properties(student-tests PROPERTIES  _BACKTRACE_TRIPLES "/home/elizabeth/Documents/newProject4/p4_starter_code/p4_starter_code/CMakeLists.txt;36;add_test;/home/elizabeth/Documents/newProject4/p4_starter_code/p4_starter_code/CMakeLists.txt;0;")
add_test(test00 "pathfinder" "/home/elizabeth/Documents/newProject4/p4_starter_code/p4_starter_code/tests/maze00.png" "output00.png")
set_tests_properties(test00 PROPERTIES  _BACKTRACE_TRIPLES "/home/elizabeth/Documents/newProject4/p4_starter_code/p4_starter_code/CMakeLists.txt;37;add_test;/home/elizabeth/Documents/newProject4/p4_starter_code/p4_starter_code/CMakeLists.txt;0;")
add_test(test00-compare "compare" "/home/elizabeth/Documents/newProject4/p4_starter_code/p4_starter_code/tests/output00.png" "output00.png")
set_tests_properties(test00-compare PROPERTIES  _BACKTRACE_TRIPLES "/home/elizabeth/Documents/newProject4/p4_starter_code/p4_starter_code/CMakeLists.txt;38;add_test;/home/elizabeth/Documents/newProject4/p4_starter_code/p4_starter_code/CMakeLists.txt;0;")
add_test(test01 "pathfinder" "/home/elizabeth/Documents/newProject4/p4_starter_code/p4_starter_code/tests/maze01.png" "output01.png")
set_tests_properties(test01 PROPERTIES  _BACKTRACE_TRIPLES "/home/elizabeth/Documents/newProject4/p4_starter_code/p4_starter_code/CMakeLists.txt;39;add_test;/home/elizabeth/Documents/newProject4/p4_starter_code/p4_starter_code/CMakeLists.txt;0;")
add_test(test01-compare "compare" "/home/elizabeth/Documents/newProject4/p4_starter_code/p4_starter_code/tests/output01.png" "output01.png")
set_tests_properties(test01-compare PROPERTIES  _BACKTRACE_TRIPLES "/home/elizabeth/Documents/newProject4/p4_starter_code/p4_starter_code/CMakeLists.txt;40;add_test;/home/elizabeth/Documents/newProject4/p4_starter_code/p4_starter_code/CMakeLists.txt;0;")
add_test(test02 "pathfinder" "/home/elizabeth/Documents/newProject4/p4_starter_code/p4_starter_code/tests/maze02.png" "output02.png")
set_tests_properties(test02 PROPERTIES  _BACKTRACE_TRIPLES "/home/elizabeth/Documents/newProject4/p4_starter_code/p4_starter_code/CMakeLists.txt;41;add_test;/home/elizabeth/Documents/newProject4/p4_starter_code/p4_starter_code/CMakeLists.txt;0;")
add_test(test02-compare "compare" "/home/elizabeth/Documents/newProject4/p4_starter_code/p4_starter_code/tests/output02.png" "output02.png")
set_tests_properties(test02-compare PROPERTIES  _BACKTRACE_TRIPLES "/home/elizabeth/Documents/newProject4/p4_starter_code/p4_starter_code/CMakeLists.txt;42;add_test;/home/elizabeth/Documents/newProject4/p4_starter_code/p4_starter_code/CMakeLists.txt;0;")
subdirs("lib")
