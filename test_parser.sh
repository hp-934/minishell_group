#!/bin/bash

MINISHELL=./minishell
OUTPUT=test_output.txt
EXPECTED=test_expected.txt

# make

# Helper function to run a test
run_test() {
    input="$1"
    echo "$input" | /bin/bash -s >> "$EXPECTED" 2>&1
    echo "$input" | "$MINISHELL" >> $OUTPUT 2>&1
}

# Test cases

> "$OUTPUT"
> "$EXPECTED"

run_test "\$PAT"
run_test ""
run_test " "
run_test "\"\""
run_test "\" \""
run_test "echo hi"

sed -i '/^>/d' "$OUTPUT"

#diff test_expected.txt test_output.txt