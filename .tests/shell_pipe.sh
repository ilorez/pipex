#!/bin/bash

echo "=== Testing Various Pipe Errors ==="

# Test 1: Too many pipes in a single command
echo -e "\n1. Testing too many pipes (EMFILE/ENFILE error):"
(
  cmd="cat /dev/zero"
  for i in {1..1000}; do
    cmd+=" | cat"
  done
  eval $cmd
) 2>&1

# Test 2: Pipe to a non-existent command
echo -e "\n2. Testing pipe to non-existent command:"
ls | nonexistentcommand 2>&1

# Test 3: Writing to a closed pipe (SIGPIPE)
echo -e "\n3. Testing write to closed pipe (SIGPIPE):"
mkfifo testpipe
(cat testpipe) & # Start reader
sleep 1
rm testpipe # Remove the pipe while it's in use
wait        # Wait for background process

# Test 4: Broken pipe with large data
echo -e "\n4. Testing broken pipe with large data:"
yes | head -n1 2>&1

# Test 5: Pipe with permission issues
echo -e "\n5. Testing pipe with permission issues:"
mkfifo testpipe2
chmod 000 testpipe2
cat testpipe2 2>&1
rm -f testpipe2

# Test 6: Pipe buffer overflow
echo -e "\n6. Testing pipe buffer overflow:"
(yes "test" | sleep 2) 2>&1

# Test 7: Command substitution with failed pipe
echo -e "\n7. Testing command substitution with failed pipe:"
result=$(cat /dev/zero | head -c1 | nonexistentcommand) 2>&1
echo "Result: $?"

# Cleanup any remaining test files
rm -f testpipe testpipe2 2>/dev/null

echo -e "\nTests completed."
