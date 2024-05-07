//
// Created by hlyan on 4/19/24.
//

#ifndef DDSA_ASSIGMENT_FOR_HALF_YEAR_H
#define DDSA_ASSIGMENT_FOR_HALF_YEAR_H


#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "ctype.h"

#define MAX_NAME_LENGTH 50
#define MAX_PHONE_LENGTH 20
#define MAX_EMAIL_LENGTH 60
#define MAX_PASSWORD_LENGTH 20

//structure Declare

struct Node{
    char name[MAX_NAME_LENGTH];
    char phone[MAX_PHONE_LENGTH];
    char email[MAX_EMAIL_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    int point ;

    struct Node* left;
    struct Node* right;
    int height;
};

struct Node* loggedInUser = NULL;



//Function Declare
struct Node* newNode(char* name, char* phone, char* email , char* password, int point);
int height(struct Node* node);
int max(int a,int b);
int getBalance(struct Node* node);
struct Node* rightRotate(struct Node* y);
struct Node* leftRotate(struct Node* x);
struct Node* inserContact(struct Node* node,char* name,char* phone,char* email ,char* password, int point );
void display_user(struct Node* root);
void freeTree(struct Node* root);
void registerUser(struct Node* root);
int isValidPhone(const char* phone);
int isUpperCase(char chr);
int isLowerCase(char chr);
int isSpecialCharacter(char chr);
int isNumber(char chr);
int isValidPassword(const char* password);
void loginPage(struct Node* root);
struct Node* login(struct Node* root, const char* email, const char* password);
struct Node* findNode(struct Node* root,const char* email);
int compareString(const char* str1, const char* str2);
void saveToFile(struct Node* node, FILE* file);
void saveFile(struct Node* root, FILE* userText);
void loadFile(struct Node** root,FILE * userText);
void loggedInMenu(struct Node* root, struct Node* loggedInUser);
void sendPoints(struct Node* root, struct Node* loggedInUser);

#endif //DDSA_ASSIGMENT_FOR_HALF_YEAR_H
