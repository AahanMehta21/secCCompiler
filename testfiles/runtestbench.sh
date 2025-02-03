#!/bin/bash

source testcases.sh

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
