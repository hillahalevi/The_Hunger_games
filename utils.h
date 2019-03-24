/**************************
Student name : hilla halevi
Student : 208953083
Course Exercise Group : 01
Exercise name : ex6.c,utilis.h
***************************/
#ifndef UTILS_H
#define UTILS_H
#include "person.h"

/****************************************************************************************
* Function Name:PrintCircle
* Input:No output
* Output:Person* head
* Function the function prints all the players  and their info that are now in the game
******************************************************************************************/
void PrintCircle(Person* head);


/****************************************************************************************
* Function Name: FindNextToME
* Input:Person*
* Output:Person* head
* Function the function gets a circle of players and a gived id number and checks if it
excist if is excist it returns the person befor the person with the givaen id else returns
null
******************************************************************************************/
Person* FindNextToME(Person* head, int x);
#endif
