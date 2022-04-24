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

TreeMap * createTreeMap(int (*lower_than) (void* key1, void* key2)) 
{
  TreeMap* tree= (TreeMap*)malloc(sizeof(TreeMap));
  tree->lower_than = lower_than;
  return tree;
}

// Comienza en la raíz del árbol y realiza una búsqueda de la clave del dato a insertar (e.g., 13). 
// Justo antes de llegar a un NULL (e.g., aux->left==NULL), se crea un nodo n con la clave y el dato y se inserta como hijo correspondiente del último nodo actual:
// aux->left = n; n->parent = aux

void insertTreeMap(TreeMap * tree, void* key, void * value) 
{
  TreeNode* n;
  tree->current=tree->root;
  aux=tree->current;
  while(aux!=NULL)
  {
    if(is_equal(tree,key,aux->pair->key)==1)
    {
      return;
    }
    else
    {
      n=createTreeNode(key,value);
      if(tree->lower_than(aux->pair->key,key)==1)
      {
        if(aux->right==NULL)
        {
          aux->right=n;
          n->parent=aux;
          aux=aux->right;
          return;
        }
        aux=aux->right;
      }
      else
      {
        if(aux->left==NULL)
        {
          aux->left=n;
          n->parent=aux;
          aux=aux->left;
          return;
        }
        aux=aux->left;
      }
    }
  }
}

TreeNode * minimum(TreeNode * x){
  TreeNode* aux=x;
  while(aux->left!=NULL)
    {
      aux=aux->left;
    }
    return aux;
}

void removeNode(TreeMap * tree, TreeNode* node) {
}

void eraseTreeMap(TreeMap * tree, void* key){
    if (tree == NULL || tree->root == NULL) return;

    if (searchTreeMap(tree, key) == NULL) return;
    TreeNode* node = tree->current;
    removeNode(tree, node);
}

Pair * searchTreeMap(TreeMap * tree, void* key) 
{
  TreeNode* aux=tree->root;
  while(aux!=NULL)
    {
      if (is_equal(tree,aux->pair->key,key)==1)
      {
        tree->current=aux;
        return aux->pair;
      }
      else
      {
        if(tree->lower_than(aux->pair->key,key)==1)
        {
          aux=aux->right;
        }
        else
        {
          aux=aux->left;
        }
      }
    }
  return NULL;
}

Pair * upperBound(TreeMap * tree, void* key) {
    return NULL;
}

Pair * firstTreeMap(TreeMap * tree) {
  TreeNode* node=minimum(tree->root);
  return node->pair;
}

Pair * nextTreeMap(TreeMap * tree) {
    return NULL;
}
