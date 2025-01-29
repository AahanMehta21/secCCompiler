#!/bin/bash

tests=(
  "arithop_test_1" "arithop_test_2" "arithop_test_3" "arithop_test_4"
  "err_arithop_test_1" "err_arithop_test_2" "err_arithop_test_3"
  "comparision_test_1" "comparision_test_2"
  "if_test_1" "if_test_2"
  "if_else_test_1" "if_else_test_2"
  "nested_if_test_1"
  "nested_while_test_1"
  "while_test_1"
  "print_arithop_test_1" "print_arithop_test_2"
  "var_test_1" "var_test_2"
  "for_test_1" "for_test_2" "nested_loop_test_1" "nested_loop_test_2"
)

cd ..

failCount=0

for test in ${tests[@]}; do
  echo "running test $test:"
  output=$(./secc testfiles/$test 2>&1)  # Capture the output in both stdout and stderr

  if echo "$output" | grep -q "on line"; then
    echo "$output" > curr_output
  else
    make --no-print-directory out
    ./out > curr_output
  fi
  sleep 1

  if diff -c curr_output "testfiles/expected/expected_$test"; then
    echo '### SUCCESS: Files Are Identical! ###'
  else
    echo '### WARNING: Files Are Different! ###'
    ((failCount++))  # Increment failCount when files differ
  fi

  printf "\n"
done

if [ $failCount -eq 0 ]; then
  printf "\n\n### All test cases passed! ###\n"
else
  printf "\n\n### Failed ${failCount} testcases! ###\n"
fi
