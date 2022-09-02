------------------------------------------------------------------------------------------
COMP 2401- Dr Christine Laurendeau
------------------------------------------------------------------------------------------
AUTHOR => Annabel Esin (Student Number: 101198034)
-------

PURPOSE
-------
Consists of 
1)-> server process that regulates access to the book data of the library and fulfills requests from the client process on demand;
2)-> a client process that interacts with the user, enabling them to view the books of the library, and allows them to check books in and out of the library.
The two processes will communicate with each other using TCP/IP sockets.
 
 COMPILATION INSTRUCTIONS
 --------------------
 - type "make" and enter
 
 LAUNCHING INSTRUCTIONS
 -----------------
 - type "./server &" and enter to run in the background
 - type "./client" and enter 
 
 
 IN CASE OF SERVER ERRORS
 -----------------------
 CLIENT COULDN'T CONNECT => restart server process
 COULD NOT BIND => run->fuser -k 60002/tcp
 
 CLOSE SERVER PROCESS AFTER CLOSING CLIENT
 ---------------------------------------
 - enter CTRL C
 
 
 LIST OF SOURCE AND HEADER FILES
 -----------
- stdio.h
- string.h
- stdlib.h

- books.c
- client.c
- connect.c
- defs.h
- lib.c
- server.c
- makefile
 
 
