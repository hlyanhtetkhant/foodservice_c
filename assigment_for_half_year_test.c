#include "assigment_for_half_year.h"

int main() {
    struct Node* root = NULL;
    FILE* userText = fopen("usersText.txt", "r");
    if (userText == NULL) {
        printf("Error opening file for reading.\n");
        return 1;
    }
    loadFile(&root, userText);
    fclose(userText);

    registerUser(root);
    userText = fopen("usersText.txt","w");
    if(userText == NULL){
        printf("Error opening file for writing");
        return 1;
    }
    saveFile(root, userText);
    fclose(userText);

    freeTree(root); // Free memory after saving to file
    return 0;
}

struct Node* newNode(char* name, char* phone , char* email , char* password,int point){
    struct Node* node=(struct Node*)malloc(sizeof(struct Node));
    strncpy(node->name, name,MAX_NAME_LENGTH);
    strncpy(node->phone, phone,MAX_PHONE_LENGTH);
    strncpy(node->email, email,MAX_EMAIL_LENGTH);
    strncpy(node->password, password,MAX_PASSWORD_LENGTH);
    node->point = point ;
    node->left = NULL;
    node->right = NULL;
    return node;
}

int height(struct Node* node){
    if(node == NULL){
        return 0;
    }
    return node->height;
}

int max(int a,int b){
    return (a > b) ? a : b;
}

int getBalance(struct Node* node){
    if(node == NULL){
        return 0;
    }
    return height(node->left) - height(node->right);
}

struct Node* rightRotate(struct Node* y){
    struct Node* x = y->left;
    struct Node* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(height(y->left),height(y->right)) + 1;
    x->height = max(height(x->left),height(x->right)) + 1;

    return x;
}

struct Node* leftRotate(struct Node* x){
    struct Node* y = x->right;
    struct Node* T2 = y->left;

    y->left = x;
    x->right = T2;

    y->height = max(height(y->left),height(y->right)) + 1;
    x->height = max(height(x->left),height(x->right)) + 1;

    return y;
}

struct Node* inserContact(struct Node* node,char* name,char* phone, char* email,char* password,int point){
    if(node == NULL){
        return newNode(name,phone,email,password,point);
    }
    if(strcmp(node->name,name)<0){
        node->left = inserContact(node->left,name,phone,email,password,point);
    } else if(strcmp(node->name,name)>0) {
        node->right = inserContact(node->right, name, phone,email,password,point);
    } else{
        return node;
    }

    node->height = max(height(node->left), height(node->right)) + 1;

    int balance = getBalance(node);

    if(balance > 1 && strcmp(node->name,name)<0){
        return rightRotate(node);
    }
    if(balance < -1 && strcmp(node->name,name)>0){
        return leftRotate(node);
    }

    if(balance > 1 && strcmp(node->left->name,name)>0){
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }
    if(balance < -1 && strcmp(node->right->name,name)<0){
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

void display_user(struct Node* root){
    if(root != NULL){
        display_user(root->left);
        printf("%s\t%s\t%s\t%s\t%d\n", root->name,root->phone,root->email,root->password,root->point);
        display_user(root->right);
    }
}

void freeTree(struct Node* root){
    if(root != NULL){
        freeTree(root->left);
        freeTree(root->right);
        freeTree(root);
    }
}

void registerUser(struct Node* node) {
    struct Node* root = NULL;
    char name[MAX_NAME_LENGTH];
    char phone[MAX_PHONE_LENGTH];
    char email[MAX_EMAIL_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    int point = 100;
    int choice = 0;

    while (1) {
        printf("  Menu\n\n");
        printf("Press 1 to Register\n");
        printf("Press 2 to Display Registered Users\n");
        printf("Press 3 to Login Users\n");
        printf("Press 4 to Exit\n");
        printf("Type Number To choose Number: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Please type your name to register: ");
                scanf(" %[^\n]", name);
                int p_chose = 1;
                while(p_chose){
                    printf("\nPlease type your phone number to register: ");
                    scanf(" %[^\n]", phone);

                    if(!isValidPhone(phone)){
                        printf("Number only 0 to 9 ");
                        p_chose = 1;
                    } else{
                        p_chose = 0;
                    }
                }

                printf("\nPlease type your email to register: ");
                scanf(" %[^\n]", email);
                int p_chose2 = 1;
                while (p_chose2){
                    printf("\nPlease type your password to register: ");
                    scanf(" %[^\n]", password);
                    if(!isValidPassword(password)){
                        printf("Password should be 6 character and need to include upper case , lower case , special letter , and number!");
                    } else{
                        p_chose2 = 0;
                    }
                }

                root = inserContact(root, name, phone, email, password, point);
                saveFile(root, "usersText.txt");
                break;
            case 2:
                display_user(node);
                break;
            case 3:
                loginPage(node);
                break;
            case 4:
                freeTree(node);
                exit(0);
            default:
                printf("Invalid choice. Please enter a number between 1 and 3.\n");
        }
    }
}

int isValidPhone(const char* phone){
    for (int i = 0; phone[i] != '\0'; i++) {
        if(!isdigit(phone[i])){
            return 0;
        }
    }
    return 1;
}

int isUpperCase(char chr) {
    return chr >= 'A' && chr <= 'Z';
}

int isLowerCase(char chr) {
    return chr >= 'a' && chr <= 'z';
}

int isSpecialCharacter(char chr) {
    return (chr >= 33 && chr <= 47) || (chr >= 58 && chr <= 64);
}

int isNumber(char chr) {
    return chr >= '0' && chr <= '9';
}

int isValidPassword(const char* password){
    int number = 0;
    int special = 0;
    int lowcha = 0;
    int uppercha = 0;
    int length = 0;
    for (int i = 0; password[i] != '\0' ; i++) {
        length++;
        if(isUpperCase(password[i])){
            uppercha = 1;
        } else if(isLowerCase(password[i])){
            lowcha = 1;
        } else if(isSpecialCharacter(password[i])){
            special = 1;
        } else if(isNumber(password[i])){
            number = 1;
        }
    }
    return uppercha && lowcha && special && number && length >= 6;
}

int compareString(const char* str1, const char* str2){
    return strcmp(str1,str2);
}

struct Node* findNode(struct Node* root,const char* email){
    if(root == NULL || compareString(root->email,email) == 0){
        return root;
    }
    if(compareString(root->email,email)<0){
        return findNode(root->left,email);
    }
    return findNode(root->right,email);
}

struct Node* login(struct Node* root, const char* email, const char* password) {
    struct Node* userNode = findNode(root, email);
    if (userNode != NULL && strcmp(userNode->password, password) == 0) {
        return userNode;
    }
    return NULL;
}

void loginPage(struct Node* root) {
    char inputEmail[MAX_EMAIL_LENGTH];
    char inputPassword[MAX_PASSWORD_LENGTH];
    printf("\nPlease type your email: ");
    scanf(" %[^\n]", inputEmail);
    printf("\nPlease type your password: ");
    scanf(" %[^\n]", inputPassword);
    loggedInUser = login(root, inputEmail, inputPassword);
    if (loggedInUser != NULL) {
        printf("Login Successful\n");
        loggedInMenu(root, loggedInUser);
    } else {
        printf("Login Failed\n");
    }
}

void saveToFile(struct Node* node, FILE* file){
    if(node == NULL)return;
    saveToFile(node->left,file);
    fprintf(file,"%s %s %s %s %d\n",node->name,node->phone,node->email,node->password,node->point);
    saveToFile(node->right,file);
}

void saveFile(struct Node* root, FILE* userText) {
    FILE* file = fopen("usersText.txt", "a");
    if (file == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }
    saveToFile(root, file);
    fclose(file);
}

void loadFile(struct Node** root, FILE* userText){
    FILE* file = fopen("usersText.txt","r");
    if(file == NULL){
        printf("Error opening file for reading");
        return;
    }

    char name[MAX_NAME_LENGTH];
    char phone[MAX_PHONE_LENGTH];
    char email[MAX_EMAIL_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    int point ;

    while (fscanf(file,"%s %s %s %s %d",name,phone,email,password,&point) != EOF){
        *root = inserContact(*root,name,phone,email,password,point);
        printf("Loaded user with phone number: %s\n", phone);
    }
    fclose(file);
}

void loggedInMenu(struct Node* root, struct Node* loggedInUser){
    int choice;
    int choice2 = 1;
    while (choice2){
        printf("\n1. Send Points\n");
        printf("2. Display Registered Users\n");
        printf("3. Logout\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                sendPoints(root, loggedInUser);
                break;
            case 2:
                display_user(root);
                break;
            case 3:
                loggedInUser = NULL;
                choice2 = 0;
                printf("Logged out.\n");
                break;
            default:
                printf("Invalid choice.\n");
        }
    }
}

void sendPoints(struct Node* root, struct Node* loggedInUser) {
    if (loggedInUser == NULL) {
        printf("Error: No user logged in.\n");
        return;
    }

    char recipientEmail[MAX_EMAIL_LENGTH];
    int pointsToSend;

    printf("\nEnter recipient's email address: ");
    scanf("%s", recipientEmail);

    struct Node* recipient = findNode(root, recipientEmail);
    if (recipient == NULL) {
        printf("Recipient with email %s not found.\n", recipientEmail);
        return;
    }

    printf("Enter points to send: ");
    scanf("%d", &pointsToSend);

    if (loggedInUser->point < pointsToSend) {
        printf("Insufficient points to send.\n");
        return;
    }

    loggedInUser->point -= pointsToSend;
    recipient->point += pointsToSend;

    printf("Points sent successfully to %s.\n", recipient->name);
}
