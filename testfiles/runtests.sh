#!/bin/bash

source testcases.sh

testsSmall=("arithop_test_1")

failCount=0

cd ..

for test in ${tests[@]}; do
  echo -n "./secc testfiles/$test"
  output=$(./secc testfiles/$test 2>&1)  # Capture the output in both stdout and stderr

  echo "$output"  # Print the output

  if echo "$output" | grep -q "on line"; then
    echo "error found, skipping make and out"
    echo "$output" > curr_output
  else
    echo "make out"
    make --no-print-directory out
    echo "./out > curr_output"
    ./out > curr_output
    cat curr_output
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

