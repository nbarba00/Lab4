#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>

#define MAX_LINE 1024
#define MAX_SIZE 50
#define FILE_NOT_OPEN -1
#define FAILED_MEMORY_ALLOCATION NULL
#define EMPTY_LISTS -2

struct _Element;
typedef struct _Element* Position;
typedef struct _Element {
	int coefficient;
	int exponent;
	Position next;
} Element;

int readFile(Position headPoly1, Position headPoly2, char* fileName);
int printPoly(char* polynomeName, Position first);
int addPoly1(Position resultHead, Position headPoly1, Position headPoly2);
//int addPoly2(Position resultHead, Position headPoly1, Position headPoly2);
int multiplyPoly(Position resultHead, Position headPoly1, Position headPoly2);
int freeMemory(Position head);
int parseStringIntoList(Position head, char* buffer);
Position createElement(int coefficient, int exponent);
int insertSorted(Position head, Position newElement);
int mergeAfter(Position current, Position newElement);
int insertAfter(Position current, Position newElement);
int deleteAfter(Position previous);
int createAndInsertAfter(int coefficient, int exponent, Position current);



int main() {
	Element headPoly1 = { .coefficient = 0,.exponent = 0,.next = NULL };
	Element headPoly2 = { .coefficient = 0,.exponent = 0,.next = NULL };
	Element headPolyAdd = { .coefficient = 0,.exponent = 0,.next = NULL }; 
	Element headPolyMultiply = { .coefficient = 0,.exponent = 0,.next = NULL };
	char* fileName = "polynomes.txt";

	if (readFile(&headPoly1, &headPoly2, fileName) == EXIT_SUCCESS) {
		printPoly("First polynome", headPoly1.next);
		printPoly("Second polynome", headPoly2.next);

		addPoly1(&headPolyAdd, headPoly1.next, headPoly2.next);
		multiplyPoly(&headPolyMultiply, headPoly1.next, headPoly2.next);

		printPoly("Added polynomes", headPolyAdd.next);
		printPoly("Multiplied polynomes", headPolyMultiply.next);

		freeMemory(&headPoly1);
		freeMemory(&headPoly2);
		freeMemory(&headPolyAdd);
		freeMemory(&headPolyMultiply);

		//test if we freed memory
		/*printPoly("First polynome", headPoly1.next);
		printPoly("Second polynome", headPoly2.next);
		printPoly("Added polynomes", headPolyAdd.next);
		printPoly("Multiplied polynomes", headPolyMultiply.next);*/
	}

	return EXIT_SUCCESS;
}

int readFile(Position headPoly1, Position headPoly2, char* fileName) {
	FILE* filePointer = NULL;
	char buffer[MAX_LINE] = { 0 };
	int status = EXIT_SUCCESS;

	filePointer = fopen(fileName, "r");
	if (!filePointer) {
		printf("\033[31mCan't open file!\033[0m\n");
		return FILE_NOT_OPEN;
	}

	fgets(buffer, MAX_LINE.filePointer);
	status = parseStringIntoList(headPoly1, buffer);
	if (status != EXIT_SUCCESS) {
		return EXIT_FAILURE;
	}

	fgets(buffer, MAX_LINE.filePointer);
	status = parseStringIntoList(headPoly2, buffer);
	if (status != EXIT_SUCCESS) {
		return EXIT_FAILURE;
	}

	fclose(filePointer);

	return EXIT_SUCCESS;
}

int printPoly(char* polynomeName, Position first) {
	printf("%s=", polynomeName);
	Position current = NULL;
	current = first->next;
	if (first) {
		if (first->exponent < 0) {
			if (first->coefficient == 1) {
				printf("x^(%d)", first->exponent);
			}
			else {
				printf("%dx^(%d)", first->coefficient, first->exponent);
			}
		}
		else {
			if (first->coefficient == 1) {
				printf("x^%d", first->exponent);
			}
			else {
				printf("%dx^(%d)", first->coefficient, first->exponent);
			}
		}
	}
	for (; current != NULL; current = current->next) {
		if (current->coefficient < 0) {
			if (first->exponent < 0) {
				printf(" - %dx^(%d)", abs(first->coefficient), first->exponent);
			}
			else {
				printf("-%dx^%d", abs(current->coefficient), current->exponent);
			}
		}
		else {
			if (first->exponent < 0) {
				if (first->coefficient == 1) {
					printf(" + x^(%d)", current->exponent);
				}
				else {
					printf(" + %dx^(%d)", current->coefficient, current->exponent);
				}
			}
			else {
				if (current->exponent == 1) {
					printf(" + x^(%d)", current->exponent);
				}
				else {
					printf(" + %dx^(%d)", current->coefficient, current->exponent);
				}
			}
		}
	}
}