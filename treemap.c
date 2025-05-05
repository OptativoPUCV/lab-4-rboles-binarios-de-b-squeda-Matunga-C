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

Pair * searchTreeMap(TreeMap * tree, void* key) {
    if (tree == NULL || tree->root == NULL) return NULL;
    TreeNode * current = tree->root;
    while (current != NULL) {
        if (tree->lower_than(key, current->pair->key) == 0 && tree->lower_than(current->pair->key, key) == 0) {
            tree->current = current; // Actualiza el nodo actual
            return current->pair; // Retorna el par encontrado
        } else if (tree->lower_than(key, current->pair->key)) {
            current = current->left; // Busca en el subárbol izquierdo
        } else {
            current = current->right; // Busca en el subárbol derecho
        }
    }
    tree->current = NULL; // Si no se encuentra el nodo, actualiza el nodo actual a NULL
    return NULL;
}

/*Implemente la función void insertTreeMap(TreeMap * tree, void* key, void * value). Esta función inserta un nuevo dato (key,value) en el árbol y hace que el current apunte al nuevo nodo.
Para insertar un dato, primero debe realizar una búsqueda para encontrar donde debería ubicarse. Luego crear el nuevo nodo y enlazarlo. Si la clave del dato ya existe retorne sin hacer nada (recuerde que el mapa no permite claves repetidas).
*/

void insertTreeMap(TreeMap * tree, void* key, void * value) {
    if (tree == NULL) return; // Verifica si el árbol es NULL
    if (searchTreeMap(tree, key) != NULL) return; // Verifica si la clave ya existe

    TreeNode * newNode = createTreeNode(key, value); // Crea un nuevo nodo
    if (newNode == NULL) return; // Verifica si la creación del nodo fue exitosa

    if (tree->root == NULL) { // Si el árbol está vacío, el nuevo nodo se convierte en la raíz
        tree->root = newNode;
        tree->current = newNode; // Actualiza el nodo actual
        return;
    }

    TreeNode * current = tree->root;
    TreeNode * parent = NULL;

    while (current != NULL) {
        parent = current; // Guarda el padre del nodo actual
        if (tree->lower_than(key, current->pair->key)) {
            current = current->left; // Busca en el subárbol izquierdo
        } else {
            current = current->right; // Busca en el subárbol derecho
        }
    }

    newNode->parent = parent; // Establece el padre del nuevo nodo

    if (tree->lower_than(key, parent->pair->key)) {
        parent->left = newNode; // Enlaza el nuevo nodo al subárbol izquierdo
    } else {
        parent->right = newNode; // Enlaza el nuevo nodo al subárbol derecho
    }

    tree->current = newNode; // Actualiza el nodo actual
}

TreeNode * minimum(TreeNode * x){
    while (x->left != NULL) {
        x = x->left; // Busca el nodo más pequeño en el subárbol izquierdo
    }
    return x; // Retorna el nodo más pequeño encontrado
}


void removeNode(TreeMap * tree, TreeNode* node) {

}

void eraseTreeMap(TreeMap * tree, void* key){
    if (tree == NULL || tree->root == NULL) return;

    if (searchTreeMap(tree, key) == NULL) return;
    TreeNode* node = tree->current;
    removeNode(tree, node);

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
