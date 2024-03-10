#include "database.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

typedef enum {name, surname, address} field;


// ### CREATION AND INSERTION OF INT TREE ### 

IndexNodeInt * create_tree_int(int root_value, Persona * p) {
    IndexNodeInt *root = malloc(sizeof(IndexNodeInt));
    if (root == NULL) { return NULL; } // Errors could be handled better
	root->value = root_value;
	root->persona = p;
    root->left = NULL;
    root->right = NULL;
    return root;
}

void insert_inorder_int(IndexNodeInt *root, int value, Persona * p) {
    if (root == NULL) { return; } // Errors could be handled better
    if (value <= root->value) {
        if (root->left == NULL) {
            IndexNodeInt *node = create_tree_int(value, p);
            root->left = node;
            return;
        }
        insert_inorder_int(root->left, value, p);
        return;
    }
    if (root->right == NULL) {
        IndexNodeInt *node = create_tree_int(value, p);
        root->right = node;
        return;
    }
    insert_inorder_int(root->right, value, p);
}

// ### CREATION AND INSERTION OF STRING TREE ### 

IndexNodeString* create_tree_string(char * root_value, Persona * p) {
	IndexNodeString *root = malloc(sizeof(IndexNodeString));
    if (root == NULL) { return NULL; } // Errors could be handled better
    root->value = root_value;
    root->persona = p;
	root->left = NULL;
    root->right = NULL;
    return root;
}

void insert_inorder_string(IndexNodeString * root, char * string, Persona * p) {
    if (root == NULL) { return; } // Errors could be handled better
	if (strcmp(string,root->value)<0) {
        if (root->left == NULL) {
            IndexNodeString *node = create_tree_string(string, p);
            root->left = node;
            return;
        }
        insert_inorder_string(root->left, string, p);
        return;
    }
    if (root->right == NULL) {
        IndexNodeString *node = create_tree_string(string, p);
        root->right = node;
        return;
    }
    insert_inorder_string(root->right, string, p);
}


Persona* findByInt(IndexNodeInt * node, int value) {
	if (node == NULL) return NULL;	// returns NULL if value is not found
	if (node->value == value) return node->persona;
	if (node->value > value) return findByInt(node->left, value);
	else return findByInt(node->right, value);
}

Persona* findByString(IndexNodeString * node, char* value) {
	if (node == NULL) return NULL;	// returns NULL if value is not found
	int cmp = strcmp(node->value, value);	
	if (cmp == 0) return node->persona;
	if (cmp > 0) return findByString(node->left, value);
	else return findByString(node->right, value);
}

// ### INTERFACE ### 

void insert(Database * database,  Persona * persona) {

	Persona * p = malloc(sizeof(Persona));
	strcpy(p->name, persona->name);
	strcpy(p->surname, persona->surname);
	strcpy(p->address, persona->address);
	p->age = persona->age;

	if (database->name == NULL) { // If the root of a tree is missing all of them are missing
		database -> name = create_tree_string(p->name, p);
		database -> surname = create_tree_string(p->surname, p);
		database -> address = create_tree_string(p->address, p);
		database -> age = create_tree_int(p->age, p);
	} else {
		insert_inorder_string(database->name, p->name, p);
		insert_inorder_string(database->surname, p->surname, p);
		insert_inorder_string(database->address, p->address, p);
		insert_inorder_int(database->age, p->age, p); 
	}
}

Persona* findByName(Database * database, char * name) {
	return findByString(database->name, name);
}
Persona* findBySurname(Database * database, char * surname) {
	return findByString(database->surname, surname);
}
Persona* findByAddress(Database * database, char * address) {
	return findByString(database->address, address);
}
Persona* findByAge(Database * database, int age) {
	return findByInt(database->age, age);
}

// ### AUXILIARY FUNCTIONS ###

void freeStringTree(IndexNodeString * n) {
	if (n == NULL) return;
	freeStringTree(n->left);
	freeStringTree(n->right);
	free(n);
} 

void freeIntTree(IndexNodeInt * n) {
	if (n == NULL) return;
	freeIntTree(n->left);
	freeIntTree(n->right);
	free(n->persona);
	free(n);
}

void freeDatabase(Database * database) {
	freeStringTree(database->name);
	freeStringTree(database->surname);
	freeStringTree(database->address);
	freeIntTree(database->age);
}

void printTree(IndexNodeString * n) {
	if (n == NULL) return;
	printTree(n->left);
	Persona * p = n->persona;
	printf("Name: %s\tSurname: %s\tAddress: %s\tAge: %d\n", p->name, p->surname, p->address, p->age);
	printTree(n->right);
}

void printDatabase(Database * database) {
	printTree(database->name);	
}