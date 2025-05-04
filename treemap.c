#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "treemap.h"

typedef struct TreeNode TreeNode;


struct TreeNode {
    Pair* pair;
    TreeNode * left;
    TreeNode * right;
    TreeNode * parent;
};

struct TreeMap {
    TreeNode * root;
    TreeNode * current;
    int (*lower_than) (void* key1, void* key2);
};

int is_equal(TreeMap* tree, void* key1, void* key2){
    if(tree->lower_than(key1,key2)==0 &&  
        tree->lower_than(key2,key1)==0) return 1;
    else return 0;
}


TreeNode * createTreeNode(void* key, void * value) {
    TreeNode * new = (TreeNode *)malloc(sizeof(TreeNode));
    if (new == NULL) return NULL;
    new->pair = (Pair *)malloc(sizeof(Pair));
    new->pair->key = key;
    new->pair->value = value;
    new->parent = new->left = new->right = NULL;
    return new;
}

TreeMap * createTreeMap(int (*lower_than) (void* key1, void* key2)) {
    TreeMap * new = (TreeMap *)malloc(sizeof(TreeMap)); // Reserva memoria para el TreeMap
    if (new == NULL) return NULL; // Verifica si la reserva de memoria fue exitosa
    new->root = NULL; // Inicializa el nodo raíz como NULL
    new->current = NULL; // Inicializa el nodo actual como NULL
    new->lower_than = lower_than;   // Asigna la función de comparación proporcionada
    return new;
}


void insertTreeMap(TreeMap * tree, void* key, void * value) {
    if(tree == NULL) return; // Verifica si el árbol es NULL

    if(tree->root == NULL){ // Si el árbol está vacío, crea el nodo raíz
        tree->root = createTreeNode(key, value); // Crea un nuevo nodo con la clave y el valor proporcionados
        tree->current = tree->root; // Establece el nodo actual como la raíz
        return;
    }

    TreeNode* current = tree->root; // Inicializa el nodo actual como la raíz
    TreeNode* parent = NULL; // Inicializa el nodo padre como NULL

    while (current != NULL){ // Recorre el árbol hasta encontrar la posición adecuada para insertar el nuevo nodo
        parent = current; // Guarda el nodo padre actual
        if(tree->lower_than(key,current->pair->key)){ // Si la clave es menor que la clave del nodo actual
            current = current->left; // Mueve hacia la izquierda
        } else if(tree->lower_than(current->pair->key, key)){ // Si la clave es mayor que la clave del nodo actual
            current = current->right; // Mueve hacia la derecha
        } else{ // Si la clave es igual a la clave del nodo actual
            current->pair->value = value; // Actualiza el valor del nodo actual
            return; // Sale de la función
        }
    }

    TreeNode* newNode = createTreeNode(key, value); // Crea un nuevo nodo con la clave y el valor proporcionados
    if (newNode == NULL) return; // Verifica si la creación del nuevo nodo fue exitosa

    newNode->parent = parent; // Establece el padre del nuevo nodo
    if(tree->lower_than(key,parent->pair->key)){ // Si la clave es menor que la clave del nodo padre
        parent->left = newNode; // Inserta el nuevo nodo como hijo izquierdo del nodo padre
    } else{ // Si la clave es mayor o igual que la clave del nodo padre
        parent->right = newNode; // Inserta el nuevo nodo como hijo derecho del nodo padre
    }
}

TreeNode * minimum(TreeNode * x){

    return NULL;
}


void removeNode(TreeMap * tree, TreeNode* node) {

}

void eraseTreeMap(TreeMap * tree, void* key){
    if (tree == NULL || tree->root == NULL) return;

    if (searchTreeMap(tree, key) == NULL) return;
    TreeNode* node = tree->current;
    removeNode(tree, node);

}




Pair * searchTreeMap(TreeMap * tree, void* key) {
    return NULL;
}


Pair * upperBound(TreeMap * tree, void* key) {
    return NULL;
}

Pair * firstTreeMap(TreeMap * tree) {
    return NULL;
}

Pair * nextTreeMap(TreeMap * tree) {
    return NULL;
}
