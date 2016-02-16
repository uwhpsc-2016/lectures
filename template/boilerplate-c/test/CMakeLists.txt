set (test_list
  run.c)

foreach (test ${test_list})
  string (REPLACE ".c" "" test ${test})
  add_executable (${test} ${PROJECT_SOURCE_DIR}/test/${test}.c)
  target_link_libraries (${test} lecture)
  add_test (${test} ${test})
endforeach (test)
