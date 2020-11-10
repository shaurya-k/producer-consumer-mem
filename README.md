# prodcomm

This program has 4 essential functions ... 
-read input from stdin
-find whitespace and replace with an asterik
-convert lower case letters to upper case
-writing the final result to stdout

## reader module
-passes the input by line to munch1
-checks if input is larger than the reader buffersize

## munch1, munch2 modules (string manipulation)
-munch1 reads from the queue passed from reader
-munch1 replaces whitespaces with asteriks
-after this manipulation, it enqueues string to queue
-munch2 reads queue connecting to munch1
-munch2 converts lower case letters to upper case
-after this manipulation, it enqueues string to queue

## writer module
-writer reads from queue connecting to munch2
-calls the function in the stats module

## stats module
-gets a queue object from the writer module
-prints the desired statistics from the argument

## main
-driver for the program

queue object is used to communicate between all the modules


