/**************************
Student name : hilla halevi
Student : 208953083
Course Exercise Group : 01
Exercise name : ex6.c,sorting.c
***************************/
#include "person.h"
#include "utils.h"
#include <stdio.h>
#include <string.h>

int Compare(Person* current, Person* headFinal, int operation);
/****************************************************************************************
* Function Name:Compare
* Input:Person* current, Person* headFinal, int operation
* Output:Person* headFinal
* Function the function takes a given  person from the circle a sertin person  and an 
operation order and compers to see who is bigger and returns the reasult
******************************************************************************************/
int Compare(Person* current, Person* headFinal, int operation) {
	if (operation == 0)
	{
		if ((current->id) > (headFinal->id))
		{
			//if our current id is bigger
			return 1;
		}
		else
		{
			//if our current id is smaller
			return -1;
		}

	}
	else
	{

		if ( (strcmp( (current->name), (headFinal->name) ) >  0 ))
		{
			//if our current name is bigger
			return 1;
		}
		else
		{
			//if our current name is smaller
			return -1;
		}
		
	}
}


Person* SoretedInsort(Person* current, Person* headFinal, int operation);
/****************************************************************************************
* Function Name:SoretedInsort
* Input:Person* current, Person* headFinal, int operation
* Output:Person* headFinal
* Function the function takes a given circle a sertin person  and an operation order
and insert the person in its right place according to the opartion order
******************************************************************************************/
Person* SoretedInsort(Person* current, Person* headFinal, int operation) {
	if (headFinal == NULL)
	{
		//empty circle insert regulary
		headFinal = current;
		return headFinal;
	}
	if ((headFinal->next == NULL) && (Compare(current, headFinal, operation)>0))
	{
		//the current needs to be inserted regulary
		headFinal->next = current;
		return headFinal;
	}
	Person* temp = headFinal;
	if (Compare(current, headFinal, operation)<0)
	{
		//the current needs to be inserted before the head
		temp = headFinal;
		headFinal = current;
		headFinal->next = temp;
		return headFinal;
	}
	//this loops until we find a place to insert current
	while ((temp->next != NULL) && (Compare(current, (temp->next), operation)>0))
	{
		//move on to the next person in tehe list
		temp = temp->next;
	}
	Person *temp1 = temp->next;
	temp->next = current;
	current->next = temp1;
	//returns the list with the new person inside
	return headFinal;
}


Person* InsertSort(Person* head, int operation);
/****************************************************************************************
* Function Name:InsertSort
* Input:Person* head, int operation
* Output:Person* finalCircle
* Function the function takes a given circle and an operation order creates a new empty 
circle and insert people from the given circle to the new one in a sorted way
and finally returns the new circle
******************************************************************************************/
Person* InsertSort(Person* head, int operation) {
	if (head == NULL || head->next == NULL)
	{
		//in case the circle is empty/has only one player
		return head;
	}
	Person* finalCircleL = NULL;
	Person* currrnt = head;
	Person* next = NULL;
	//this while loop will insert all the players in increasing order to a new list
	while (currrnt != NULL)
	{	//holds the pointer to the next person
		next = currrnt->next;
		//disconnect the current person from the pervios list
		currrnt->next = NULL;
		//send it to a function that will insert it in the right place
		finalCircleL = SoretedInsort(currrnt, finalCircleL, operation);
		//move on to the next player
		currrnt = next;

	}
	//returns the sorted list
	return finalCircleL;
}

/****************************************************************************************
* Function Name:SortCircleByID
* Input:Person* head
* Output:Person* head
* Function the function takes a given circle and returns is sorted according to the id field
******************************************************************************************/
Person* SortCircleByID(Person* head) {
	head = InsertSort(head, 0);
	return head;


}

/****************************************************************************************
* Function Name:SortCircleByName
* Input:Person* head
* Output:Person* head
* Function the function takes a given circle and returns is sorted according to the name field
******************************************************************************************/
Person* SortCircleByName(Person* head) {
	head = InsertSort(head, 1);
	return head;
}