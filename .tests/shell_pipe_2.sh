#!/bin/sh

echo "=== Testing Pipe Errors in Shell ==="

# Test 1: Broken pipe with yes command
echo "\n1. Testing broken pipe:"
yes | head -n1 2>&1

# Test 2: Pipe to non-existent command
echo "\n2. Testing pipe to missing command:"
ls | nonexistentcommand 2>&1

# Test 3: FIFO pipe errors
echo "\n3. Testing FIFO pipe errors:"
mkfifo testpipe
(cat testpipe) &
sleep 1
rm testpipe
wait

# Test 4: Multiple pipes to trigger resource limits
echo "\n4. Testing many pipes:"
cmd="cat /dev/zero"
i=1
while [ $i -le 1000 ]; do
  cmd="$cmd | cat"
  i=$((i + 1))
done
eval $cmd 2>&1

# Test 5: Permission denied pipe
echo "\n5. Testing permission denied:"
mkfifo testpipe2
chmod 000 testpipe2
cat testpipe2 2>&1
rm -f testpipe2

# Cleanup
rm -f testpipe testpipe2 2>/dev/null

echo "\nTests completed."
