This MIPS Simulator has the ability to interrupt a running simulation in either the text-mode or GUI-mode version of the program by moving the simulator execution into a separate thread. The program  attempts to parse the file into the data representing the virtual machine. If the input file cannot be parsed the program should print an error message and return EXIT_FAILURE. If the input file can be parsed then the program will enter a read-eval-print loop using standard output and standard input for communication with the user. The loop will print the prompt simmips> and wait for one of the following command strings to be entered:

step - execute the current instruction and print the new program counter, or if an error has occurred the error message
run - start execution of the current program (repeated step)
break - stop execution of the current program (stop at end of current step). Does nothing if the simualtion is not running.
status - print the error status as a message, print nothing if no error has been encountered
quit - quit the program, return EXIT_SUCCESS
print $r - print the register contents, either a register number, alias, or one of pc, hi, or lo in hex format
print &a - print the byte at memory address a, in hex format

If the program is invoked with a command line option --gui before or after the filename, then the graphical version of the program will be used. Otherwise the text mode above will be used.

$ simmips.exe --gui myprog.asm

If the file cannot be opened and parsed an appropriate error message will be displayed in the status widget. Unless there was an error loading and parsing the file the status widget will display “Ok”. The contents of the virtual machine registers and memory will be displayed and the registers will be laid out with the $pc first, followed by $hi, $lo, and $0-$31