#!/bin/bash

echo "This script is used to test the process sandbox"

# Clean up old outputs
rm -f output_expected.txt output_actual.txt diff_file

# ANSI escape codes for colors
RED='\033[0;31m'
GREEN='\033[0;32m'
NC='\033[0m' # No Color

# Function to compare expected and actual output
check_diff() {
    diff "$1" "$2" > diff_file
    if [ -s "diff_file" ]; then
        echo -e "${RED}Test Failed${NC}"
        cat "diff_file"
    else
        echo -e "${GREEN}Test Passed${NC}"
    fi
}

# Function to compare return values
check_return() {
    if [ "$1" -eq "$2" ]; then
        echo -e "${GREEN}Return value is correct${NC}"
    else
        echo -e "${RED}Return value is incorrect (Expected: $2, Got: $1)${NC}"
    fi
}

# Compile the sandbox with test cases
gcc -Wall -Wextra -Werror sandbox.c test_cases.c -o sandbox_tester

if [ ! -f sandbox_tester ]; then
    echo -e "${RED}Compilation failed!${NC}"
    exit 1
fi

# Run test cases
echo "Running test cases..."
./sandbox_tester > output_actual.txt

# Define expected output
cat > output_expected.txt <<EOF
Nice function!
Bad function: exited with code 42
Bad function: Segmentation fault
Bad function: timed out after 2 seconds
EOF

# Check output
check_diff output_actual.txt output_expected.txt
