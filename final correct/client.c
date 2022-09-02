#include "defs.h"

int main()
{
  int  choice = -1; 
  int clientSocket;
  setupClientSocket(&clientSocket);
  int ID,action;
  char request[MAX_ARR];
  char string[MAX_BUFF];
  char str[MAX_STR];
  
  while (1) {

   clientMenu(&choice);
   switch(choice) {

      case 1: ;  // Print books
      	//Fomulates request string containing REQ_RET_BOOKS request type
	sprintf(request, "%d", 0);
	sendData(clientSocket, request);
	rcvData(clientSocket,string);
	printf("%s ", string);
        break;

      case 2:   // Check out a book
      	//Fomulates request string containing REQ_CHECK_OUT request type AND book ID
        printf("Please enter the book id: ");
      	fgets(str, sizeof(str), stdin);
      	sscanf(str, "%d", &ID);
      	sprintf(request, "%d %d", 1, ID);
	sendData(clientSocket, request);
	rcvData(clientSocket,string);
	sscanf(string,"%d", &action);
	//Prints confirmation messages on the success or failure of operation
	if(action == 0){
		printf("\nSuccess! Book has been checked out.\n");
	}
	else if(action == -1){
		printf("\nSorry, it seems like this book has already been checked out!\n");
	}
	else if(action == -2){
		printf("\nSorry, this book doesnt exist!\n");
	}
	else if(action == -3){
		printf("\nSorry, this book is either under repair or lost at the moment.\n");
	}
        break;

      case 3:   // Check in a book
      //Fomulates request string containing REQ_CHECK_IN request type AND book ID
	printf("Please enter the book id: ");
      	fgets(str, sizeof(str), stdin);
      	sscanf(str, "%d", &ID);
      	sprintf(request, "%d %d", 2, ID);
	sendData(clientSocket, request);
	rcvData(clientSocket,string);
	sscanf(string,"%d", &action);
	//Prints confirmation messages on the success or failure of operation
	if(action == 0){
		printf("\nSuccess! Book has been checked in.\n");
	}
	else if(action == -1){
		printf("\nSorry, it seems like this book has already been checked in!\n");
	}
	else if(action == -2){
		printf("\nSorry, this book doesnt exist!\n");
	}
	else if(action == -3){
		printf("\nSorry, this book is under repair and has not be checked out.\n");
	}
        break;

      case 0:   // Close everything
	sprintf(request, "%d", 3);
	sendData(clientSocket, request);
	close(clientSocket);
	exit(-1);
        break;

      default:
        printf("ERROR:  invalid option\n");
    }
  }

  return 0;
}

void clientMenu(int* choice)
{
  int c = -1;
  int numOptions = 3;
  char str[MAX_STR];

  printf("\nMAIN MENU\n");
  printf("  (1) Print books\n");
  printf("  (2) Check out a book\n");
  printf("  (3) Check in a book\n");
  printf("  (0) Exit\n\n");

  printf("Please enter your selection: ");
  fgets(str, sizeof(str), stdin);
  str[strcspn(str, "\n")] = 0;
  sscanf(str, "%d", &c);

  if (c == 0) {
    *choice = c;
    return;
  }

  while (c < 0 || c > numOptions) {
    printf("Please enter your selection: ");
    fgets(str, sizeof(str), stdin);
    sscanf(str, "%d", &c);
  }

  *choice = c;
}

