#ifndef LINKEDLIST_H
#define LINKEDLIST_H

struct Node {
	int typeId;
	struct Node* next;
	struct Node* prev;
};

struct Node* createNode(int typeId);
void addNodeTail(struct Node** head, int typeId);
void removeNodeHead(struct Node** head);
void removeNodeTail(struct Node** head);

#endif