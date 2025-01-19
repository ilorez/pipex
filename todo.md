
you should close all fds on errors even in child process
you have leaks in child
here_doc should work like real heredoc
perror message should be like origna;
if command not found should show command not found not no such file or directory


try heredoc with diffrent commands like ls and cat
check diffrent test when infile doesn't have required permissions or outfile or both with correct and uncoreect commands 

handle 0 1 126 127

