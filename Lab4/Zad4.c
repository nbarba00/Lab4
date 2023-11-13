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
int addPoly1(Position resultHead, Position firstElementPoly1, Position firstElementPoly2);
int addPoly2(Position resultHead, Position firstElementPoly1, Position firstElementPoly2);
int multiplyPoly(Position resultHead, Position firstElementPoly1, Position firstElementPoly2);
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

		first = first->exponent;
	}

	for (; current != NULL; current = current->next) {
		if (current->coefficient < 0) {
			if (first->exponent < 0) {
				printf(" - %dx^(%d)", abs(first->coefficient), first->exponent);
			}
			else {
				printf("-%dx^%d", abs(first->coefficient), first->exponent);
			}
		}
		else {
			if (first->exponent < 0) {
				if (first->coefficient == 1) {
					printf(" + x^(%d)", first->exponent);
				}
				else {
					printf(" + %dx^(%d)", first->coefficient, first->exponent);
				}
			}
			else {
				if (first->coefficient == 1) {
					printf(" + x^(%d)", firstt->exponent);
				}
				else {
					printf(" + %dx^(%d)", first->coefficient, first->exponent);
				}
			}
		}
	}

	printf("\n");
	return EXIT_SUCCESS;
}

int addPoly1(Position resultHead, Position firstElementPoly1, Position firstElementPoly2) {
		Position currentPoly1 = firstElementPoly1;
		Position currentPoly2 = firstElementPoly2;
		Position currentResult = resultHead;
		Position remainingPoly = NULL;

		//untill the end of one(or both)polynomes
		while (currentPoly1 != NULL && currentPoly2 != NULL) {
			if (currentPoly1->exponent == currentPoly2->exponent) {
				if(currentPoly1->cefficient+currentPoly2->coefficient!=0) {
					createAndInsertAfter(currentPoly1->coefficient + currentPoly2->coefficient, currentPoly1->exponent);
					currentResult = currentResult->next;
				}
				currentPoly1 = currentPoly1->next;
				currentPoly2 = currentPoly2->next;

			}
			else if (currentPoly1->exponent < currentPoly2->exponent) {
				createAndInsertAfter(currentPoly1->coefficient, currentPoly1->exponent, currentResult);
				currentPoly1 = currentPoly1->next;
				currentResult = currentResult->next;
			}
			else {//if(currentPoly1->exponent>currentPoly2->exponent)
				createAndInsertAfter(currentPoly2->coefficient, currentPoly2->exponent, currentResult);
				currentPoly2 = currentPoly2->next;
				currentResult = currentResult->next;
			}

		}
		if (currentPoly1 == NULL) {
			remainingPoly = currentPoly2;
		}
		else {
			remainingPoly = currentPoly1;
		}
		//finish with the rest of the remainingPoly
		while (remainingPoly != NULL) {
			createAndInsertAfter(remainingPoly->coefficient, remainingPoly->exponent, currentResult);
			remainingPoly = remainingPoly->next;
			currentResult = currentResult->next;
		}

		return EXIT_SUCCESS;
}

int addPoly2(Position resultHead, Position headPoly1, Position headPoly2)
{
	Position currentPoly1 = firstElementPoly1;
	Position currentPoly2 = firstElementPoly2;

	for (; currentPoly1 != NULL; currentPoly1 = currentPoly1->next)
	{
		Position newElement = createElement(currentPoly1->coefficient, currentPoly1->exponent);
		if (!newElement)
		{
			return EXIT_FAILURE;
		}

		insertSorted(resultHead, newElement);
	}
	for (; currentPoly2 != NULL; currentPoly2 = currentPoly2->next)
	{
		Position newElement = createElement(currentPoly2->coefficient, currentPoly2->exponent);
		if (!newElement)
		{
			return EXIT_FAILURE;
		}

		insertSorted(resultHead, newElement);
	}
	return EXIT_SUCCESS;
}

int multiplyPoly(Position resultHead, Position firstElementPoly1, Position firstElementPoly2)
{
	if (firstElementPoly1 == NULL || firstElementPoly2 == NULL)
		return EMPTY_LISTS;
	for (Position currentPoly1 = firstElementPOly1; currentPoly1 != NULL; currentPoly1 = currentPoly1->next) {
		for (Position currentPoly2 = firstElementPOly2; currentPoly2 != NULL; currentPoly2 = currentPoly2->next) {
			Position newElement = createElement(currentPoly1->coefficient * currentPoly2->coefficient, currentPoly1->exponent + currentPoly2->exponent);
			if (!newElement) {
				return EXIT_FAILURE;
			}

			insertSorted(resultHead, newElement);
		}
	}
	return EXIT_SUCCESS;

}
