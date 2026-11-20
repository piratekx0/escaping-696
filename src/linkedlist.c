#include <stdio.h>
#include <stdlib.h>

#include "linkedlist.h"

struct Node* createNode(int typeId) {
	struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));

	newNode->typeId = typeId;
	newNode->next = NULL;
	newNode->prev = NULL;

	return newNode;
}

void addNodeTail(struct Node** head, int typeId) {
	struct Node* newNode = createNode(typeId);
	newNode->next = NULL;

	if (*head == NULL) {
		*head = newNode;
		newNode->prev = NULL;
		return;
	}

	struct Node* tail = *head;
	while  (tail->next != NULL) {
		tail = tail->next;
	}
	tail->next = newNode;
	newNode->prev = tail;
}

void removeNodeHead(struct Node** head) {
	if (*head == NULL) return;
	if ((*head)->next == NULL) {
		free(*head);
		*head = NULL;
		return;
	}

	struct Node* temp = *head;
	*head = (*head)->next;
	(*head)->prev = NULL;
	free(temp);
}

void removeNodeTail(struct Node** head) {
	if (*head == NULL) return;
	if ((*head)->next == NULL) {
		free(*head);
		*head = NULL;
		return;
	}

	struct Node* tail = *head;
	while (tail->next->next != NULL) {
		tail = tail->next;
	}
	
	free(tail->next);
	tail->next = NULL;
}