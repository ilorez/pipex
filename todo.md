here_doc should work like real heredoc
you have leaks in child
perror message should be like origna;
if command not found should show command not found not 
not such file or directory

you should close all fds on errors even in child process

try heredoc with diffrent commands like ls and cat
check diffrent test when infile doesn't have required permissions or outfile or both with correct and uncoreect commands 

handle 0 1 126 127

