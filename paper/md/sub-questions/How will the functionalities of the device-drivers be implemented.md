<!-- # Research -->

## How will the functionality of the device-drivers be implemented

### How will the functionality of device-driver0 be implemented

As specified in the Requirements the functionality of device-driver0 will be to continuously read from stdin.   
As the application that will be build in this paper will be build with C, for reading the stdin the basic commands are:

- Name ; Explanation ; Input arguments ; Return value
- getchar ; Reads the next available character from stdin and returns it as an integer ; None ; Read character
- gets ; Reads the next line from stdin and places this into the provided Read line parameter ; Read line ; Status
- scanf ; Reads the input from the standard input stream stdin and scans that input according to the format provided ; Format, List of Format variables , Value to put the read value into ; Status

Using the above commands the behavior of the first device-driver can be implemented.

### How will the functionality of device-driver1 be implemented

As specified in the Requirements the functionality of device-driver1 will be to write to stdout.  
As the application that will be build in this paper will be build with C, for writing to stdout the basic commands are:

- Name ; Explanation ; Input arguments ; Return value
- putchar ; puts the passed character on the screen and returns the same character ; Character to write ; Written character
- puts ; Writes the provided string and a trailing newline to stdout ; String to write ; Status
- printf ; writes the output to the stdout and produces the output according to the format provided ; Format, List of Format variables to write ; Status

Using the above commands the behavior of the second device-driver can be implemented.