/**************************
Student name : hilla halevi
Student : 208953083
Course Exercise Group : 01
Exercise name : ex6.c,person.c
***************************/
#include "person.h"
#include "utils.h"
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <stdarg.h>
#define OPERATION_NAME  0
#define OPERATION_ID  1
#define OPERATION_NUM_KIDS  2
#define OPERATION_NAME_KIDS  3
#define NAME "Name:\n"

#define KID_NAME "Kid #%d name:\n"
#define ID "ID:\n"
#define NUM_KIDS "Num of kids:\n"
#define WHO_AM_I "Name: %s\nID: %d\n"
#define ALL_MY_SONS "Kid #%d: %s\n"
#define SIZE 80


int GetName(Person * newPerson, int operation);
/****************************************************************************************
* Function Name:GetName
* Input:Person * newPerson,int operation
* Output:no output
* Function the function gets input from the user and insert to the struct according to
an operation order(first name or kids)
******************************************************************************************/
int GetName(Person * newPerson, int operation) {
	char name[SIZE];
	int i = 0;
	//chang the insert operation -to malloc derectly to the person*
	if (operation == OPERATION_NAME)
	{
		printf(NAME);
		//Geting first name from the user
		scanf("%s", name);
		//allocating memory according to the length
		int a = strlen(name) + 1;
		char * nameNow = NULL;
		nameNow = (char *)malloc(a * sizeof(char*));
		if (nameNow == NULL) {
			//Didn’t succeed.
			free(newPerson);
			return 0;
		}
		strcpy(nameNow, name);
		newPerson->name = nameNow;
	}

	if (operation == OPERATION_NAME_KIDS)
	{
		//Geting the amont of children
		int n = newPerson->numOfKids;
		if (n != 0)
		{
			//alocating an array of pointers
			char ** kidsNow = NULL;
			kidsNow = (char **)malloc(n * sizeof(char *));
			if (kidsNow == NULL) {
				//Didn’t succeed.
				free(newPerson->name);
				return 0;
			}
			for (i = 0; i < n; i++)
			{	//alocating for each childe costome made place
				printf(KID_NAME, i + 1);
				scanf("%s", name);
				int b = strlen(name) + 1;
				kidsNow[i] = NULL;
				kidsNow[i] = (char *)malloc(b * sizeof(char));
				if (kidsNow[i] == NULL) {
					//Didn’t succeed.
					free(newPerson->name);
					for (int j = 0; j <= i; j++)
					{
						free(kidsNow[j]);
					}
					free(kidsNow);
					free(newPerson);
					return 0;
				}
				//inserting to the array
				strcpy(kidsNow[i], name);
			}

			//pointing to the struct
			newPerson->kids = kidsNow;
		}

	}
	return 1;


}

void GetNum(Person * newPerson, int operation);
/****************************************************************************************
* Function Name:GetNum
* Input:Person * newPerson,int operation
* Output:no output
* Function the function gets input from the user and insert to the struct according to
an operation order(id or amout of kids)(if needed the  function wil  correct the input
befor inserting)
******************************************************************************************/
void GetNum(Person * newPerson, int operation) {
	int newNum = 0;
	if (operation == OPERATION_ID)
	{
		printf(ID);
		scanf("%d", &newNum);
		if (newNum < 0)
		{
			newNum = -newNum;
		}
		newPerson->id = newNum;
	}
	if (operation == OPERATION_NUM_KIDS)
	{
		printf(NUM_KIDS);
		scanf("%d", &newNum);
		if (newNum < 0)
		{
			newNum = -newNum;
		}
		newPerson->numOfKids = newNum;
	}

}



void Print(Person* this);
/****************************************************************************************
* Function Name:Print
* Input:Person* this
* Output:no return value
* Function the function prints a person with all its deatails
******************************************************************************************/
void Print(Person* this) {
	//storying num of kids
	int a = this->numOfKids;
	//printing name and id
	printf(WHO_AM_I, this->name, this->id);
	//printing kids
	for (int i = 1; i <= a; i++)
	{
		printf(ALL_MY_SONS, i, this->kids[i - 1]);
	}
}



Person* SelfDestruct(Person* this);
/****************************************************************************************
* Function Name:SelfDestruct
* Input:Person* this
* Output:Person* -pointer to a person struct
* Function the function 'kills' the struct it came from-frees all info stored and returnes
the next struct in line(was stored in the original struct)
******************************************************************************************/
Person* SelfDestruct(Person* this) {
	//storyng the pointer to the next struct in line
	Person *c = this->next;
	free(this->name);
	//num of kids -1 becase we start our index from 0
	int m = this->numOfKids - 1;
	for (int i = 0; i <= m; i++)
	{	//free each kid
		free(this->kids[i]);
	}
	//free  all the array of the kids
	free(this->kids);
	//free all the struct
	free(this);
	//returns the next struct in line
	return c;
}



void KillNext(Person* this);
/****************************************************************************************
* Function Name:KillNext
* Input:Person* this
* Output:no output
* Function the function 'kills' the struct next to the struct it came from-frees all info
stored.
******************************************************************************************/
void KillNext(Person* this) {
	//free all the memoey alocated to the next person and conect its pointer to the next living person
	this->next = SelfDestruct(this->next);
}



Person* CreatePerson();
/****************************************************************************************
* Function Name:InitPersonValues
* Input:--
* Output:*person pointer to struct
* Function the function creates a person by inserting info to its fields
******************************************************************************************/
Person* CreatePerson()
{
	int a = 0;
	//pointer to the struct
	Person * newPerson = NULL;
	//allocate memory to the struct
	newPerson = (Person *)malloc(sizeof(Person));
	if (newPerson == NULL) {
		//Didn’t succeed.
		return NULL;
	}
	//initail all the fields
	InitPersonValues(newPerson);
	int operation = 0;
	//gets first name
	a = GetName(newPerson, OPERATION_NAME);
	if (a = 0)
	{
		//Didn’t succeed.
		return NULL;
	}
	//gets id
	GetNum(newPerson, OPERATION_ID);
	//gets num of kids
	GetNum(newPerson, OPERATION_NUM_KIDS);
	//gets names of the kids
	a = GetName(newPerson, OPERATION_NAME_KIDS);
	if (a = 0)
	{
		//Didn’t succeed.
		return NULL;
	}
	//return the pounter to the struct
	return newPerson;
}



void CreateNext(Person* this, int isNextNext, ...);
/****************************************************************************************
* Function Name:CreateNext
* Input:Person* this
* Output:no output
* Function the function create another struct and place it in the right place
******************************************************************************************/
void CreateNext(Person* this, int isNextNext, ...) {
	if (isNextNext == 1)
	{	//there is already a person we need to move him and place another 
		va_list ap;
		//finds the pointer to the next person in line
		va_start(ap, isNextNext);
		//assign the soure person to a new one(that we create now)
		this->next = CreatePerson();
		if (this->next == NULL)
		{
			//the function couldnt allocate memory
			this->next = va_arg(ap, Person*);
			return;
		}
		//assign the new person to the person we took its place
		this->next->next = va_arg(ap, Person*);
		va_end(ap);

	}
	else
	{	//open spot enter regulary
		this->next = CreatePerson();
		if (this->next == NULL)
		{
			//the function couldnt allocate memory
			while (this != NULL)
			{
				//remove all the players we already have
				this = SelfDestruct(this);
			}
			return;
		}
	}

}



void InitPersonValues(Person* person);
/****************************************************************************************
* Function Name:InitPersonValues
* Input:Person* person
* Output:no output
* Function the function initals all the feilds of a fiven struct
******************************************************************************************/
void InitPersonValues(Person* person) {
	person->next = NULL;
	person->name = NULL;
	person->id = 0;
	person->numOfKids = 0;
	person->kids = NULL;
	person->Print = &Print;
	person->KillNext = &KillNext;
	person->SelfDestruct = &SelfDestruct;
	person->CreateNext = &CreateNext;
	

}
