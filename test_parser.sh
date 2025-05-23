#!/bin/bash

MINISHELL=./minishell
OUTPUT=test_output.txt
EXPECTED=test_expected.txt

# Helper function to run a test
run_test() {
    input="$2"

    echo "$input" | $MINISHELL >> $OUTPUT 2>&1
    echo " " >> $OUTPUT
}

# Test cases

rm -f $OUTPUT

run_test "// Invalid Variable" "\$PAT"

run_test "" "\$USER\$PATH"

run_test "" "\$?\$USER  \"Test\$?\""

run_test "// Basic Command Parsing" "echo hello"

run_test "// Pipes" "ls -l | grep main"

run_test "// Multiple Pipes with Quotes" 'cat "some file" | grep "hello $PATH" | wc -l'

run_test "// Single Quotes — No Expansion" "echo '\$HOME is cool'"

run_test "// Double Quotes — With Expansion" "echo \"\$HOME is cool\""

run_test "// Mixed Quotes" "echo 'user:' \"\$USER\""

run_test "// Variables Alone" "echo \$PATH"

run_test "// Syntax Error (unclosed quote)" 'echo "hello'

run_test "// Empty Pipe at Start" "| ls"

run_test "// Empty Pipe at End" "ls |"

run_test "// Double Pipe" "ls || echo hi"

run_test "// Pipe followed by another pipe" "ls | | grep"

run_test "// Pipe starts input" "| echo hello"

run_test "// Double pipe in middle" "echo hello || wc"

run_test "// Valid pipe" "echo hello | wc"

run_test "// Pipe in quotes (should be literal)" 'echo "hello | world" | wc'

run_test "// Literal pipe in single quotes" "echo '|'"

run_test "// Here-doc with pipe" "cat << EOF | wc"

run_test "// Quotes with pipe inside" 'echo "this | is not a pipe"'

run_test "// Double quoted word" '"hello"'

run_test "// Single quoted word" "'world'"

run_test "// Empty input" "\"\""

run_test "// Invalid characters in quotes" "\"'\';\""

run_test "// Invalid characters outside quotes" "\"test\";"

run_test "// Invalid characters outside quotes" "\"test\" \ "

#diff test_expected.txt test_output.txt