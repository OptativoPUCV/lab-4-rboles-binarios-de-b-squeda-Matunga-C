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
    if (tree == NULL || tree->root == NULL) return NULL; // Verifica si el árbol es NULL o está vacío
    TreeNode * current = tree->root; // Inicializa el nodo actual como la raíz
    while (current != NULL) { // Recorre el árbol
        if (tree->lower_than(key, current->pair->key) == 0 && tree->lower_than(current->pair->key, key) == 0) { // Verifica si la clave es igual a la del nodo actual
            tree->current = current; // Actualiza el nodo actual
            return current->pair; // Retorna el par encontrado
        } else if (tree->lower_than(key, current->pair->key)) { // Si la clave es menor que la del nodo actual 
            current = current->left; // Busca en el subárbol izquierdo
        } else {
            current = current->right; // Busca en el subárbol derecho
        }
    }
    tree->current = NULL; // Si no se encuentra el nodo, actualiza el nodo actual a NULL
    return NULL;
}

void insertTreeMap(TreeMap * tree, void* key, void * value) {
    if (tree == NULL) return; // Verifica si el árbol es NULL
    if (searchTreeMap(tree, key) != NULL) return; // Verifica si la clave ya existe

    TreeNode * newNode = createTreeNode(key, value); // Crea un nuevo nodo
    if (newNode == NULL) return; // Verifica si la creación del nodo fue exitosa

    if (tree->root == NULL) { // Si el árbol está vacío, el nuevo nodo se convierte en la raíz
        tree->root = newNode; // Establece el nuevo nodo como la raíz
        tree->current = newNode; // Actualiza el nodo actual
        return;
    }

    TreeNode * current = tree->root; // Inicializa el nodo actual como la raíz
    TreeNode * parent = NULL; // Inicializa el padre como NULL

    while (current != NULL) { // Busca la posición correcta para insertar el nuevo nodo
        parent = current; // Guarda el padre del nodo actual
        if (tree->lower_than(key, current->pair->key)) {
            current = current->left; // Busca en el subárbol izquierdo
        } else { // Si la clave es mayor o igual, busca en el subárbol derecho
            current = current->right; // Busca en el subárbol derecho
        }
    }

    newNode->parent = parent; // Establece el padre del nuevo nodo

    if (tree->lower_than(key, parent->pair->key)) { // Si la clave es menor que la del padre, se inserta en el subárbol izquierdo
        parent->left = newNode; // Enlaza el nuevo nodo al subárbol izquierdo
    } else { // Si la clave es mayor o igual, se inserta en el subárbol derecho
        parent->right = newNode; // Enlaza el nuevo nodo al subárbol derecho
    }

    tree->current = newNode; // Actualiza el nodo actual
}

TreeNode * minimum(TreeNode * x){
    while (x->left != NULL) { // Busca el nodo más pequeño en el subárbol izquierdo
        x = x->left; // Busca el nodo más pequeño en el subárbol izquierdo
    }
    return x; // Retorna el nodo más pequeño encontrado
}


void removeNode(TreeMap * tree, TreeNode* node) {
    if (node == NULL) return; // Verifica si el nodo es NULL

    TreeNode * y = node; // Inicializa y como el nodo a eliminar
    TreeNode * x = NULL; // Inicializa x como NULL

    if (node->left == NULL || node->right == NULL) { // Si el nodo tiene un hijo o ninguno
        y = node; // Si el nodo tiene un hijo o ninguno, se asigna a y
    } else { // Si el nodo tiene dos hijos, se busca el sucesor
        y = minimum(node->right); // Encuentra el sucesor en el subárbol derecho
    }

    if (y->left != NULL) { // Si y tiene un hijo izquierdo
        x = y->left; // Asigna el hijo izquierdo de y a x
    } else { // Si y no tiene hijo izquierdo
        x = y->right; // Asigna el hijo derecho de y a x
    }

    if (x != NULL) { // Si x no es NULL, establece su padre
        x->parent = y->parent; // Establece el padre de x
    }

    if (y->parent == NULL) { // Si y es la raíz
        tree->root = x; // Si y es la raíz, actualiza la raíz del árbol
    } else if (y == y->parent->left) { // Si y es el hijo izquierdo de su padre
        y->parent->left = x; // Actualiza el enlace del padre de y
    } else { // Si y es
        y->parent->right = x; // Actualiza el enlace del padre de y
    }

    if (y != node) { // Si y no es el nodo a eliminar
        node->pair = y->pair; // Copia los datos del nodo a eliminar al nodo actual
    }

    free(y); // Libera la memoria del nodo eliminado
}

void eraseTreeMap(TreeMap * tree, void* key){
    if (tree == NULL || tree->root == NULL) return;

    if (searchTreeMap(tree, key) == NULL) return;
    TreeNode* node = tree->current;
    removeNode(tree, node);

}

/*La función Pair* upperBound(TreeMap* tree, void* key) retorna el **Pair** con clave igual a key. En caso de no encontrarlo retorna el primer par asociado a una clave mayor o igual a key. 
Para implementarla puede realizar una búsqueda normal y usar un puntero a nodo auxiliar ub_node que vaya guardando el nodo con la menor clave *mayor o igual a key*. Finalmente retorne el par del nodo ub\_node.
*/

Pair * upperBound(TreeMap * tree, void* key) {
    if (tree == NULL || tree->root == NULL) return NULL; // Verifica si el árbol es NULL o está vacío
    TreeNode * current = tree->root; // Inicializa el nodo actual como la raíz
    TreeNode * ub_node = NULL; // Inicializa el nodo auxiliar para el upper bound

    while (current != NULL) { // Recorre el árbol
        if (tree->lower_than(key, current->pair->key)) { // Si la clave es menor que la del nodo actual
            ub_node = current; // Actualiza el nodo auxiliar
            current = current->left; // Busca en el subárbol izquierdo
        } else { // Si la clave es mayor o igual a la del nodo actual
            current = current->right; // Busca en el subárbol derecho
        }
    }

    if (ub_node != NULL) { // Si se encontró un nodo auxiliar válido
        return ub_node->pair; // Retorna el par encontrado
    } else {
        return NULL; // Si no se encontró un nodo auxiliar, retorna NULL
    }
}

Pair * firstTreeMap(TreeMap * tree) {
    if (tree == NULL || tree->root == NULL) return NULL; // Verifica si el árbol es NULL o está vacío
    TreeNode * current = tree->root; // Inicializa el nodo actual como la raíz

    while (current->left != NULL) { // Busca el nodo más pequeño en el árbol
        current = current->left; // Mueve al hijo izquierdo
    }
    tree->current = current; // Actualiza el nodo actual

    return current->pair; // Retorna el par encontrado
}

Pair * nextTreeMap(TreeMap * tree) {
    if (tree == NULL || tree->current == NULL) return NULL; // Verifica si el árbol es NULL o el nodo actual es NULL
    TreeNode * current = tree->current; // Inicializa el nodo actual como el nodo actual del árbol
    if (current->right != NULL) { // Si el nodo actual tiene un hijo derecho
        current = current->right; // Mueve al hijo derecho
        while (current->left != NULL) { // Busca el nodo más pequeño en el subárbol derecho
            current = current->left; // Mueve al hijo izquierdo
        }
        tree->current = current; // Actualiza el nodo actual
        return current->pair; // Retorna el par encontrado
    } else { // Si no tiene hijo derecho, busca hacia arriba
        TreeNode * parent = current->parent; // Inicializa el padre como el padre del nodo actual
        while (parent != NULL && parent->right == current) { // Busca hacia arriba hasta encontrar un padre que sea hijo izquierdo
            current = parent; // Mueve al padre
            parent = parent->parent; // Mueve al abuelo
        }
        tree->current = parent; // Actualiza el nodo actual
        return parent != NULL ? parent->pair : NULL; // Retorna el par encontrado o NULL si no hay más nodos
    }
    return NULL;
}
