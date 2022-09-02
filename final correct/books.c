#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "defs.h"

/*
  Function:  initList
  Purpose:   initializes the required fields of the given book list
*/
void initList(BookListType *list){
	list->head= NULL;
	list->tail=NULL;
}

/*
  Function:  initBook
  Purpose:   dynamically alloactes the memory for a new book and initialises the elements 
   in-out:   the book parameters
*/
void initBook(int i, char*t, char*a, int y, BookStatusType st,BookType**book){
	BookType *newBook= malloc(sizeof(BookType));
	newBook->id= i;
	strcpy(newBook->title, t);
	strcpy(newBook->author, a);
	newBook->year=y;
	newBook->status= st;
	*book= newBook;
}

/*
  Function:  addBook
  Purpose:   adds the new book to the list in aphabetical order by title name
   in-out:   the book list, book
*/
void addBook(BookListType*list, BookType*b){
	NodeType *currNode;
  	NodeType *prevNode;
  	NodeType *newNode;
  	
  	currNode = list->head;
  	prevNode = NULL;
  	
  	newNode = malloc(sizeof(NodeType));
  	newNode->data = b;
  	newNode->next = NULL;
  
  	while(currNode !=NULL){
  		if(strcmp(b->title,currNode->data->title)<0){
  			break;
  		}
  		prevNode= currNode;
  		currNode= currNode->next;	
  	}
  	
  	if(prevNode == NULL){
  		list->head= newNode;
    	}
  	else{
    		prevNode->next = newNode;
    	}
  	newNode->next = currNode;
  	
  	if(currNode == NULL){
  		list->tail=newNode;
  	}		
}
/*
  Function:  findBook
  Purpose:   finds the book with the given course id within the book list
   in-out:   the book list
   return:   C_OK for success, C_NOK for failure
*/

int findBook(BookListType *list, int id, BookType **b){
	NodeType *current;
	current= list->head;
	
	if(current==NULL){
		return C_NOK;
	}
	
	while(current !=NULL){
		if(current->data->id == id){
			*b= current->data;
			return C_OK;
		}
		current = current->next;	
	}
	return C_NOK;	
}

/*
  Function:  formatBook
  Purpose:   formats all info for single books and stores in outsr parameter 
   in-out:   book, retuned string 
*/
void formatBook(BookType *b, char *outStr){
	char string[MAX_ARR];
	char status[MAX_STR];
	convertStatus(b->status, status);
	sprintf(string,"\n%-5d|%-38s|%-20s|%-10d|%-5s", b->id, b->title, b->author, b->year,status);
	strcpy(outStr,string);	
}

/*
  Function:  formatBooks
  Purpose:   transverses book list, formats books and stores in outsr parameter 
   in-out:   book list, retuned string 
*/
void formatBooks(BookListType *list, char *outStr){
	NodeType *current;
	current= list->head;
	
	char temp[MAX_ARR];
	char books[MAX_BUFF]={0};
	while(current != NULL){
		formatBook(current->data,temp);
		strcat(books,temp);
		current= current->next;
	} 
	strcpy(outStr,books);
	
	//Formats tail and head data and adds to booklist
	strcat(books, "\n-----HEAD");
	formatBook(list->head->data,temp);
	strcat(books,temp);
	strcpy(outStr,books);
	strcat(books, "\n-----TAIL");
	formatBook(list->tail->data,temp);
	strcat(books,temp);
	strcpy(outStr,books);
}	

/*
  Function:  cleanupList
  Purpose:   deallocates the dynamically allocated memory for the book collection
   in-out:   BooklistType collection 
*/
void cleanupList(BookListType *list){
	NodeType *currNode;
  	NodeType *nextNode=NULL;

  	currNode = list->head;
  	
  	while (currNode != NULL) {
    		nextNode = currNode->next;
    		free(currNode->data);
    		free(currNode);
    		currNode = nextNode;
  	}
}

/*
  Function:  convertStatus
  Purpose:   indicates the book status 
   in-out:   BookStatusTYpe s
   return:   corresponding string using the s parameter
*/
void convertStatus(BookStatusType st, char *s){
	if(st== CHECKED_IN){
		strcpy(s,"Checked In");
	}
	if(st== CHECKED_OUT){
		strcpy(s,"Checked Out");
	}
	if(st== UNDER_REPAIR){
		strcpy(s,"Under Repair");
	}
	if(st== LOST){
		strcpy(s,"Lost");
	}
}
