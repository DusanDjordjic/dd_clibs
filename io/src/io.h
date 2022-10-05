#ifndef _IO_H_
#define _IO_H_

char*       io_getstr(); // Reads from stdin until there is nothig more to be read
char*       io_getnstr(unsigned int n); // Reads n bytes from stdin and calls io_clear_buffer
void        io_clear_buffer(); // Reads and discards everything from stdin
long int    io_trim_str(char** str); // Trims a string and returns number of removed characters
long int    io_trim_str_left(char** str); // Trims a string from left and returns number of removed characters. -1 if error happend
long int    io_trim_str_right(char** str); // Trims a from right string and returns number of removed characters. -1 if error happend
#endif
