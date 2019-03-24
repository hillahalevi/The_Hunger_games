/**************************
Student name : hilla halevi
Student : 208953083
Course Exercise Group : 01
Exercise name : ex6.c,utilis.c
***************************/
#include "person.h"
#include "utils.h"
#include <stdio.h>
#define BORDER_LINES "----------\n"

/****************************************************************************************
* Function Name:PrintCircle
* Input:No output
* Output:Person* head
* Function the function prints all the players  and their info that are now in the game
******************************************************************************************/
void PrintCircle(Person* head) {
	// Initialize current
	Person* current = head;
	if (current == NULL)
	{
		//empty circle nothing to print
		return;
	}
	//loops until the end of the circle
	while (current != NULL)
	{
		printf( BORDER_LINES );
		current->Print(current);
		//move on to the next player
		current = current->next;
	}
	printf(BORDER_LINES);
}


/****************************************************************************************
* Function Name: FindNextToME
* Input:Person*
* Output:Person* head
* Function the function gets a circle of players and a gived id number and checks if it
excist if is excist it returns the person befor the person with the givaen id else returns
null
******************************************************************************************/
Person* FindNextToME(Person* head, int x)
{
	if (head->id == x)
	{
		//if the head has the wanted id
		return head;
	}
	// Initialize current
	Person* current = head;
	
	//loops to find the person before person with the id we need
	while (current != NULL  && current->next != NULL )
	{
		if (current->next->id == x)
			//returns the person we need 
			return current;
		current = current->next;
	}
	return	NULL;
}

