#include "defs.h"

int listenSocket;

int main()
{
  LibraryType *lib= malloc(sizeof(LibraryType));
  int clientSocket;
//Initialise and load library data
  initLibrary(&lib,"Spring Day Library");
//Set up server's listening socket 
  setupServerSocket(&listenSocket);
  signal(SIGUSR1, handleSig1);	
/* wait for connection request */
  acceptConnection(listenSocket, &clientSocket); 
/*serves all requests on client socket*/
  serveOneClient(clientSocket, lib);
  free(lib);
  return 0;
}

/*
  Function:  serveOneClient
  Purpose:   serves all requests from client process connects at given client socket 
   in-out:   library collection, clientSocket
*/
void serveOneClient(int clientSocket, LibraryType *lib){
  char buffer[MAX_BUFF];
  char string[MAX_BUFF];
  int action,ID;
  while(1){
  	rcvData(clientSocket,buffer);
  	//Converts first charcater of recieved data buffer to numeric value 
  	sscanf(&buffer[0],"%d", &action);
  	
  	//Formats library's entire book collection and returns to client process
  	if(action == 0){
  		formatBooks(&lib->books, string);
  		sendData(clientSocket, string);
  	}
  	//Request to check out a book 
  	else if(action == 1){
  		//Sends the requestion action and book's ID to check out
  		sscanf(buffer,"%d %d", &action, &ID);
  		//returns C_OK
  		if(checkOutBook(lib,ID)== 0){
  			sprintf(string, "%d", 0);
  		}
  		//returns C_NOK
  		else if(checkOutBook(lib, ID)== -1){
  			sprintf(string, "%d", -1);
  		}
  		//returns BOOK_NOT_FOUND
  		else if(checkOutBook(lib, ID)== -2){
  			sprintf(string, "%d", -2);
  		}
  		//returns BAD_STATUS  
  		else {
  			sprintf(string, "%d", -3);
  		}
  		sendData(clientSocket, string);
  	}
  	if(action == 2){
  		//Sends the requestion action and book's ID to check in
  		sscanf(buffer,"%d %d", &action, &ID);
  		//returns C_OK
  		if(checkInBook(lib,ID)== 0){
  			sprintf(string, "%d", 0);
  		}
  		//returns C_NOK
  		else if(checkInBook(lib, ID)== -1){
  			sprintf(string, "%d", -1);
  		}
  		//returns BOOK_NOT_FOUND
  		else if(checkInBook(lib, ID)== -2){
  			sprintf(string, "%d", -2);
  		}
  		//returns BAD_STATUS  
  		else {
  			sprintf(string, "%d", -3);
  		}
  		sendData(clientSocket, string);
  	}
  	if(action == 3){
  	//Termination of server process 
  		close(clientSocket);
  		closeAll(lib);
  		exit(-1);
  	}
  }
}

/*
  Function:  closeAll
  Purpose:   cleans up server by closing listenSocket and cleaning library data
   in-out:   Library collection 
*/
void closeAll(LibraryType *lib){
  cleanupLibrary(lib);
  close(listenSocket);
}

/*
  Function:  handleSig1 
  Purpose:   cleans up server resourses and server terminating process 
*/
void handleSig1(int i){
	close(listenSocket);
	exit(SIGUSR1);
}
