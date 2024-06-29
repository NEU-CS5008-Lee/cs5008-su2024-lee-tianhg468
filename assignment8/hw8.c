// name: Tian Huang
// email: huang.tian2@northeastern.edu

// please start with a copy of your hw7.c, rename it to hw.8
// and then complete the assignment
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

#define MAXSTRING 200
#define BUCKET_SIZE 400

// finite state machine states
#define STARTSTATE 0
#define S1 1
#define S2 2
#define S3 3
#define S4 4
#define S5 5
#define S6 6
#define ACCEPTSTATE 10
#define ERRORSTATE 11

struct bucket* hashTable1 = NULL;
struct bucket* hashTable2 = NULL;
struct bucket* hashTable3 = NULL;

// check if a character c is a digit
bool isDigit(char c) {
    if ('0' <= c && c <= '9') {
        return true;
    } else {
        return false;
    }
}

// append character c to string s
void appendChar(char* s, char c) {
    char charToStr[2];           // convert char to string
    charToStr[0] = c;
    charToStr[1] = '\0';          // put NUL to terminate string of one character
    strcat(s, charToStr);
}

typedef struct Node {
    char cityState[MAXSTRING];
    int population;
    struct Node* next;
} Node_t;

struct bucket{
    Node_t* head;
    int count; // # of nodes in a bucket
};

Node_t* createNode(char* cityState, int population){
    Node_t* newNode = (Node_t*)malloc(sizeof(Node_t));
    if (newNode == NULL) {
        printf("Error in creating new node: memory allocation error");
        return NULL;
    }
    strcpy(newNode->cityState, cityState);
    newNode->population = population;
    newNode->next = NULL;
    return newNode;
}

int hashFunc1(char* str) {
    return strlen(str) % BUCKET_SIZE;
}

int hashFunc2(char* str) {
    int sum = 0;
    for (int i=0; i<strlen(str); i++) {
        sum += str[i];
    }
    return sum % BUCKET_SIZE;
}

int hashFunc3(char* str) {
    if (strlen(str) < 2) {
        return 0;
    }
    return (str[0] * str[1]) % BUCKET_SIZE;
}

void insert(struct bucket* hashTable, char* cityState, int population, int (*hashFunc)(char*)) {
    int hashIndex = hashFunc(cityState);
    Node_t* newNode = createNode(cityState, population);
    // when node is empty
    if (hashTable[hashIndex].count == 0){
        hashTable[hashIndex].count = 1;
        hashTable[hashIndex].head = newNode;
    }
    // when node has a key
    else{
        newNode->next = hashTable[hashIndex].head;
        hashTable[hashIndex].head = newNode;
        hashTable[hashIndex].count++;
    }
}

void printHashTable(struct bucket* hashTable) {
    Node_t* iterator;

    printf("\n================== \n");
    for (int i = 0; i<BUCKET_SIZE; i++){
        iterator = hashTable[i].head;
        printf("\nTable[%d] : ", i);
        while (iterator != NULL)
        {
            printf("\nkey/value: [%s]/ [%d]", iterator->cityState, iterator->population);
            iterator = iterator->next;
        }
        printf("\n");
    }
    printf("\n================== \n");
}

void freeHashTable(struct bucket* hashTable) {
    for (int i = 0; i < BUCKET_SIZE; i++) {
        Node_t* iterator = hashTable[i].head;
        while (iterator != NULL) {
            Node_t* temp = iterator;
            iterator = iterator->next;
            free(temp);
        }
    }
    free(hashTable);
}


int main () {

    char inputLine[MAXSTRING];   // temporary string to hold input line
    char cityStr[MAXSTRING];     // city name
    int  lineNum;                // line number (city rank)
    int  popInt;                 // population
    int  state;                  // FSM state
    int  nextChar;               // index of next character in input string
    char temp[MAXSTRING];        // temp string to build up extracted strings from input characters

    hashTable1 = (struct bucket*)malloc(BUCKET_SIZE * sizeof(struct bucket));
    hashTable2 = (struct bucket*)malloc(BUCKET_SIZE * sizeof(struct bucket));
    hashTable3 = (struct bucket*)malloc(BUCKET_SIZE * sizeof(struct bucket));

    if (hashTable1 == NULL || hashTable2 == NULL || hashTable3 == NULL) {
        printf("Memory allocation error\n");
        exit(EXIT_FAILURE);
    }

    FILE* fp;
    fp = fopen("pop.csv","r");

    if (fp != NULL) {
        fgets(inputLine, MAXSTRING, fp); // prime the pump for the first line

        // ***** BEGIN FINITE STATE MACHINE *****

        // STARTSTATE: digit -> S1
        // S1: digit -> S1; , -> S2
        // S2: " -> S3
        // S3: !" -> S3; " -> S4
        // S4: , -> S5
        // S5: " -> S6; ( -> ACCEPTSTATE
        // S6: digit -> S6; , -> S6; " -> ACCEPTSTATE;
        // ACCEPTSTATE: done!
        // else go to ERRORSTATE
        //
        while (feof(fp) == 0){

            nextChar = 0;
            state = STARTSTATE;
            strcpy(temp,"");       // temp = ""

            if (nextChar >= strlen(inputLine)){
                // if no input string then go to ERRORSTATE
                state = ERRORSTATE;
            }

            while ((state != ERRORSTATE) && (state != ACCEPTSTATE)) {
                switch (state) {
                    case STARTSTATE:
                        // look a digit to confirm a valid line
                        if (isDigit(inputLine[nextChar])) {
                            state = S1;
                            appendChar(temp, inputLine[nextChar]);
                        } else {
                            state = ERRORSTATE;
                        }
                        break;


                        // ADD YOUR CODE HERE
                    case S1:
                        if (isDigit(inputLine[nextChar])) {
                            appendChar(temp, inputLine[nextChar]);
                        } else if (inputLine[nextChar] == ',') {
                            state = S2;
                        } else {
                            state = ERRORSTATE;
                        }
                        break;

                    case S2:
                        if (inputLine[nextChar] == '"') {
                            state = S3;
                            strcpy(temp, ""); // clear temp for city name
                        } else {
                            state = ERRORSTATE;
                        }
                        break;

                    case S3:
                        if (inputLine[nextChar] == '"') {
                            state = S4;
                            strcpy(cityStr, temp);
                        } else {
                            appendChar(temp, inputLine[nextChar]);
                        }
                        break;

                    case S4:
                        if (inputLine[nextChar] == ',') {
                            state = S5;
                        } else {
                            state = ERRORSTATE;
                        }
                        break;

                    case S5:
                        if (inputLine[nextChar] == '"') {
                            state = S6;
                            strcpy(temp, ""); // clear temp for population
                        } else if (inputLine[nextChar] == '(') {
                            state = ACCEPTSTATE;
                            popInt = 0;
                        } else {
                            state = ERRORSTATE;
                        }
                        break;

                    case S6:
                        if (isDigit(inputLine[nextChar])) {
                            appendChar(temp, inputLine[nextChar]);
                        } else if (inputLine[nextChar] == ',' || inputLine[nextChar] == '"') {
                            if (inputLine[nextChar] == '"') {
                                state = ACCEPTSTATE;
                                char *endptr;
                                popInt = (int)strtol(temp, &endptr, 10); // convert to int
                            }
                        } else {
                            state = ERRORSTATE;
                        }
                        break;

                    case ACCEPTSTATE:
                        // nothing to do - we are done!
                        break;

                    default:
                        state = ERRORSTATE;
                        break;
                } // end switch

                // advance input
                nextChar++;

            }	// end while state machine loop

            // ***** END FINITE STATE MACHINE *****
            if (state == ACCEPTSTATE) {
                insert(hashTable1, cityStr, popInt, hashFunc1);
                insert(hashTable2, cityStr, popInt, hashFunc2);
                insert(hashTable3, cityStr, popInt, hashFunc3);
            }

            // process the line - print out raw line and the parsed fields
            //printf("> %.60s\n", inputLine);
            //printf("[%.30s]: %d\n", cityStr, popInt);


            // get next line
            fgets(inputLine, MAXSTRING, fp);

        } // end while file input loop


        fclose(fp);

        // Print hash tables
        printf("***** HASH TABLE 1 *****\n");
        printHashTable(hashTable1);
        printf("***** HASH TABLE 2 *****\n");
        printHashTable(hashTable2);
        printf("***** HASH TABLE 3 ***** \n");
        printHashTable(hashTable3);

        freeHashTable(hashTable1);
        freeHashTable(hashTable2);
        freeHashTable(hashTable3);

    } else {
        printf("File not found!\n");
    }

    return 0;
}
