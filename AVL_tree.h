#ifndef AVL_TREE_H
#define AVL_TREE_H
#include "Node.h"

template<class T, class Cond>
class AVLTree{
private:
    Node<T,Cond>  *root;
    int size{};
    void reverseInOrderTraversalImpl(Node<T,Cond>* node, int *const output, int* index);
    Node<T,Cond> *smallest;
    Node<T,Cond> *biggest;

public:
    AVLTree(): root(nullptr), size(0), smallest(nullptr), biggest(nullptr) {}
    AVLTree(T arr[],int size);
    virtual ~AVLTree();
    void insert(const Cond& key,const T& data);
    T* find(const Cond& key);
    bool exist(const Cond& key);
    T findValue(const Cond& key);
    void remove(const Cond& key);
    void reverseInOrderTraversal(int *const output);
    int getSize();
    Node<T,Cond>* getRoot();
    Node<T,Cond>* getBiggest();
    Node<T,Cond>* getSmallest();
    void fillArray(Node<T,Cond>* arr[], int index);
    void fillArrayImpl(Node<T, Cond> *node, Node<T,Cond>* arr[], int* index);

};

template<class T, class Cond>
AVLTree<T,Cond>::AVLTree(T arr[],int size)
{
//    TODO BUILD THISSS !!!!!!!!!!!!!! :(
    this->size = size;
    this->smallest = this->getSmallest();
    this->biggest = this->getBiggest();
}

template<class T, class Cond>
AVLTree<T,Cond>::~AVLTree()
{
    delete this->root;
}

template<class T, class Cond>
void AVLTree<T,Cond>::insert(const Cond &key,const T& data) {
    if(this->root == nullptr)
        this->root =  new Node<T,Cond>(key,data);
    else
        this->root = this->root->insertNode(key,data);
    this->size++;
    this->smallest = this->getSmallest();
    this->biggest = this->getBiggest();
}

template<class T, class Cond>
T*  AVLTree<T,Cond>::find(const Cond &key) {
    return root->findNode(key)->getNodeDataPointer();
}

template<class T, class Cond>
bool  AVLTree<T,Cond>::exist(const Cond &key)
{
    Node<T,Cond>* temp = root->isExist(key);
    return temp != nullptr;
}

template<class T, class Cond>
T  AVLTree<T,Cond>::findValue(const Cond &key) {
    return root->findNode(key)->getNodeData();
}

template<class T, class Cond>
void AVLTree<T,Cond>::remove(const Cond& key) {
    this->root = this->root->deleteNode(key);
    this->size--;
    this->smallest = this->getSmallest();
    this->biggest = this->getBiggest();
}

template<class T, class Cond>
void AVLTree<T, Cond>::reverseInOrderTraversal(int *const output){
    int index = 0;
    reverseInOrderTraversalImpl(root, output, &index);
}

template<class T, class Cond>
void AVLTree<T,Cond>::reverseInOrderTraversalImpl(Node<T, Cond> *node, int *const output, int* index) {
    if(node == nullptr)
        return;
    reverseInOrderTraversalImpl(node->getRight(), output, index);
    output[(*index)++] = node->getKey();
    reverseInOrderTraversalImpl(node->getLeft(), output, index);
}

template<class T, class Cond>
int AVLTree<T,Cond>::getSize()
{
    return this->size;
}

template<class T, class Cond>
Node<T,Cond>* AVLTree<T,Cond>::getRoot()
{
    return this->root;
}

template<class T, class Cond>
Node<T,Cond>* AVLTree<T,Cond>::getBiggest()
{
    if(!this->root)
        return nullptr;
    return this->root->findBiggest();
}

template<class T, class Cond>
Node<T,Cond>* AVLTree<T,Cond>::getSmallest()
{
    if(!this->root)
        return nullptr;
    return this->root->findSmallest();
}

template<class T, class Cond>
void AVLTree<T,Cond>::fillArray(Node<T,Cond>* arr[], int index) {
    fillArrayImpl(root,arr,&index);
}

template<class T, class Cond>
void AVLTree<T,Cond>::fillArrayImpl(Node<T, Cond> *node, Node<T,Cond>* arr[], int* index) {
    if (node == nullptr)
        return;
    fillArrayImpl(node->getLeft(), arr, index);
    arr[(*index)++] = node;
    fillArrayImpl(node->getRight(), arr, index);
}
#endif //AVL_TREE_H
