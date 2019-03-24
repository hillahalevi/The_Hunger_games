/**************************
Student name : hilla halevi
Student : 208953083
Course Exercise Group : 01
Exercise name : ex6.c,game.c
***************************/
#include "person.h"
#include "utils.h"
#include <stdio.h>
#define COME_AND_PLAY "Add a person to the game? (0|1)\n"
#define LATERS "Are you late? (0|1)\n"
#define WHO_IS_UR_BFF "Insert your best friend's ID:\n"
#define NO_ID "No Such ID: %d\n"
#define OH_I_AM_SCARED "Is there a coward in here? (0|1)\n"
#define COWARDS_REMOVAL "Insert your ID, you, lame pudding-heart coward:\n"
#define REMOVAL_MSG "Let the world know that you are a coward, %s!\n"
#define KILL_MSG "%s kills %s"
#define KILL_KIDS " and %s"
#define WIN_MSG "Ah, ha, ha, ha, stayin' alive, stayin' alive! Ah, ha, ha, ha, \"%s\" stayin' alive!\n"


/****************************************************************************************
* Function Name:InitTheHungerGame
* Input:No output
* Output:Person* head 
* Function the function starts the game and creates unattached circles of players and
returns the head of the person ,if used several times without atarting the game it could 
cause memory leak but this is how our system is designed
******************************************************************************************/
Person* InitTheHungerGame() {
	int a = 0;
	printf(COME_AND_PLAY);
	//sacn the choice
	scanf("%d", &a);
	if (a == 0)
	{
		//there are no people at all
		return NULL;
	}
	Person *head = CreatePerson();
	Person *temp = head;
	if (head == NULL)
	{	//coudlnt allocate memory
		return NULL;

	}
	//this while loop will loop as long the user want to insert new people to the circle
	while (a == 1)
	{
		printf(COME_AND_PLAY);
		//sacn the choice
		scanf("%d", &a);
		if (a == 0)
		{
			break;
		}
		temp->CreateNext(temp, 0);
		if (temp->next == NULL)
		{
			//the function couldnt allocate memory
			return NULL;
		}
		//move the pointer to the next person
		temp = temp->next;

	}
	//returns the first person
	return head;
}


/****************************************************************************************
* Function Name:InsertLaters
* Input:Person* head
* Output:no output
* Function the function enables players to join the game late,and locates them next to their
best friend ,in case their friend is not in the game/the circle is empty there wont be any
insrtion.
******************************************************************************************/
void InsertLaters(Person* head) {
	while (head != NULL)
	{
		int a = 0;
		printf(LATERS);
		//sacn the choice
		scanf("%d", &a);
		if (a == 0)
		{
			//not late
			return;
		}
		else
		{
			Person* bff = NULL;
			int id = 0;
			printf(WHO_IS_UR_BFF);
			//sacn the choice
			scanf("%d", &id);
			//find me returns the head /person before the person we need or NULL
			bff = FindNextToME(head, id);
			if (bff == NULL)
			{	//there is no such id 
				printf(NO_ID, id);
			}
			else
			{
				Person* stranger;
				//if we got the head we need to check if its the best friend or not
				if (bff == head &&head->id == id)
				{
					 //the current person thats next to the bff
					stranger = bff->next;
					//placing the friends together
					bff->CreateNext(bff, 1, stranger);
				}
				else
				{
					stranger = bff->next->next;
					//locate the new person next to his bff
					bff->CreateNext(bff->next, 1, stranger);
				}


				if (bff->next == stranger)
				{
					//couldnt allocate memory 
					return;
				}
			}

		}
	}

}

/****************************************************************************************
* Function Name:RemoveCowards
* Input:Person* head
* Output:no output
* Function the function enables players to drop out the game before the killing begin
it asks for id and remove (if exict)the person with this id
******************************************************************************************/
Person* RemoveCowards(Person* head) {
	while (head != NULL)
	{
		int a = 0;
		printf(OH_I_AM_SCARED);
		//sacn the choice
		scanf("%d", &a);
		if (a == 0)
		{
			return head;
		}
		else
		{
			printf(COWARDS_REMOVAL);
			//sacn the choice
			scanf("%d", &a);
			//find me returns the person before the person we need or NULL of theres no such id or 
			Person *b = FindNextToME(head, a);
			if (b == NULL)
			{	//there is no such id 
				printf(NO_ID, a);
				continue;
			}
			
			if (b == head)
			{
				printf(REMOVAL_MSG, head->name);
				//remove the first person and appoint the new head
				head = b->SelfDestruct(b);
			}
			else
			{
				printf(REMOVAL_MSG, b->next->name);
				//removing the cowerd and reconnect the circle
				b->next = b->next->SelfDestruct(b->next);
			}



		}
	}
	//the circle is empty
	return NULL;
}

/****************************************************************************************
* Function Name:LetTheHungerGameBegin
* Input:Person* head
* Output:no output
* Function the function starts the game,by taking a given circle of players and each one
kils his friend ,the game finishes with a wining massaege  by thelast survivor
******************************************************************************************/
void LetTheHungerGameBegin(Person* head) {
	// Initialize current
	Person* current = head;
	if (head == NULL)
	{
		return;
	}
	while (head->next != NULL)
	{
		//in each loop we kill according to the game
		//each kills his next 
		while (current != NULL && current->next != NULL)
		{
			printf(KILL_MSG, current->name, current->next->name);
			if (current->next->numOfKids == 0)
			{
				//if the victem has no kids we will just kill him
				printf("\n");
				current->KillNext(current);
				//reconect the circle
				current = current->next;
			}
			else
			{
				for (int i = 1; i <= current->next->numOfKids; i++)
				{
					//if kids are involved -kill them
					printf(KILL_KIDS, current->next->kids[i - 1]);
				}
				printf("\n");
				current->KillNext(current);
				current = current->next;
			}
			//we kill all the players until we reach the head again

		}
		if (current == NULL)
		{
			//start again
			current = head;
		}
		else
		{
			//we need to kill the head
			printf(KILL_MSG, current->name, head->name);
			for (int i = 1; i <= head->numOfKids; i++)
			{
				printf(KILL_KIDS, head->kids[i - 1]);
			}
			printf("\n");
			//apoint new head 
			current = head = head->SelfDestruct(head);
		}


	}
	//the current head=the only player that was left
	printf(WIN_MSG, head->name);
	//free all remaining memory(the victirios memory)
	current->SelfDestruct(current);


}
