#ifndef AVL_TREE_H
#define AVL_TREE_H
#include "Node.h"

template<class T, class Cond>
class AVLTree {
private:
    Node<T, Cond> *root;
    int size{};
    //void reverseInOrderTraversalImpl(Node<T,Cond>* node, int *const output, int* index);
    Node<T, Cond> *smallest;
    Node<T, Cond> *secondSmallest;
    Node<T, Cond> *thirdSmallest;
    Node<T, Cond> *biggest;
    Node<T, Cond> *secondBiggest;
    Node<T, Cond> *thirdBiggest;

public:
    AVLTree(): root(nullptr), size(0), smallest(nullptr),secondSmallest(nullptr),thirdSmallest(nullptr),biggest(nullptr),
                                                        secondBiggest(nullptr),thirdBiggest(nullptr){}
    AVLTree(Node<T, Cond>* arr[],int size, int start, int end);
    virtual ~AVLTree();
    void insert(const Cond& key,const T& data);
    T* find(const Cond& key);
    bool exist(const Cond& key);
    //T findValue(const Cond& key);
    void remove(const Cond& key);
    //void reverseInOrderTraversal(int *const output);
    Node<T,Cond>* sortedArrayTo(Node<T, Cond>* arr[], int start, int end);
    int getSize();
    Node<T,Cond>* getRoot();
    //Node<T,Cond>* findNode(Cond &key);
    Node<T,Cond>* getBiggest();
    Node<T,Cond>* getSmallest();
    Node<T,Cond>* getSecondBiggest();
    Node<T,Cond>* getSecondSmallest();
    Node<T,Cond>* getThirdBiggest();
    Node<T,Cond>* getThirdSmallest();
    Node<T,Cond>* get_biggest();
    Node<T,Cond>* get_smallest();
    Node<T,Cond>* get_second_biggest();
    Node<T,Cond>* get_second_smallest();
    Node<T,Cond>* get_third_biggest();
    Node<T,Cond>* get_third_smallest();
    void fillArray(Node<T,Cond>* arr[], int index);
    void fillArrayImpl(Node<T, Cond> *node, Node<T,Cond>* arr[], int* index);
};

template<class T,class Cond>
Node<T,Cond>* AVLTree<T,Cond>::sortedArrayTo( Node<T, Cond>* arr[], int start, int end)
{
    if (start > end)
        return nullptr;
    int mid = start + (end - start) / 2;
    Node<T,Cond>* currNode =  new Node<T,Cond>(arr[mid]->getKey(),arr[mid]->getNodeData());
    currNode->setLeft(sortedArrayTo(arr, start, mid - 1));
    currNode->setRight(sortedArrayTo(arr, mid + 1, end));
    currNode->calcHeight();
    return currNode;
}

template<class T, class Cond>
AVLTree<T,Cond>::AVLTree(Node<T, Cond>* arr[],int size, int start, int end): root(this->sortedArrayTo(arr,start,end)),
size(size), smallest(this->getSmallest()), secondSmallest(this->getSecondSmallest()), thirdSmallest(this->getThirdSmallest()),
biggest(this->getBiggest()), secondBiggest(this->getSecondBiggest()), thirdBiggest(this->getThirdBiggest())
{
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
    this->secondSmallest = this->getSecondSmallest();
    this->thirdSmallest = this->getThirdSmallest();
    this->biggest = this->getBiggest();
    this->secondBiggest = this->getSecondBiggest();
    this->thirdBiggest = this->getThirdBiggest();
}

template<class T, class Cond>
T*  AVLTree<T,Cond>::find(const Cond &key) {
    return root->findNode(key)->getNodeDataPointer();
}

//template<class T, class Cond>
//Node<T,Cond>*  AVLTree<T,Cond>::findNode(Cond &key) {
//    return root->findNode(key);
//}

template<class T, class Cond>
bool  AVLTree<T,Cond>::exist(const Cond &key)
{
    Node<T,Cond>* temp = root->isExist(key);
    return temp != nullptr;
}

//template<class T, class Cond>
//T  AVLTree<T,Cond>::findValue(const Cond &key) {
//    return root->findNode(key)->getNodeData();
//}

template<class T, class Cond>
void AVLTree<T,Cond>::remove(const Cond& key) {
    this->root = this->root->deleteNode(key);
    this->size--;
    this->smallest = this->getSmallest();
    this->secondSmallest = this->getSecondSmallest();
    this->thirdSmallest = this->getThirdSmallest();
    this->biggest = this->getBiggest();
    this->secondBiggest = this->getSecondBiggest();
    this->thirdBiggest = this->getThirdBiggest();
}

//template<class T, class Cond>
//void AVLTree<T, Cond>::reverseInOrderTraversal(int *const output){
//    int index = 0;
//    reverseInOrderTraversalImpl(root, output, &index);
//}
//
//template<class T, class Cond>
//void AVLTree<T,Cond>::reverseInOrderTraversalImpl(Node<T, Cond> *node, int *const output, int* index) {
//    if(node == nullptr)
//        return;
//    reverseInOrderTraversalImpl(node->getRight(), output, index);
//    output[(*index)++] = node->getKey();
//    reverseInOrderTraversalImpl(node->getLeft(), output, index);
//}

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
Node<T,Cond>* AVLTree<T,Cond>::getSecondBiggest()
{
    if((!this->root)||(this->size==1))
        return nullptr;
    return this->root->findSecondBiggest(root);
}

template<class T, class Cond>
Node<T,Cond>* AVLTree<T,Cond>::getSecondSmallest()
{
    if((!this->root)||(this->size==1))
        return nullptr;
    return this->root->findSecondSmallest(root);
}

template<class T, class Cond>
Node<T,Cond>* AVLTree<T,Cond>::getThirdBiggest()
{
    if((!this->root)||(this->size<=2))
        return nullptr;
    return this->root->findThirdBiggest(root);
}

template<class T, class Cond>
Node<T,Cond>* AVLTree<T,Cond>::getThirdSmallest()
{
    if((!this->root)||(this->size<=2))
        return nullptr;
    return this->root->findThirdSmallest(root);
}

template<class T, class Cond>
Node<T,Cond>* AVLTree<T,Cond>::get_biggest() {
    return this->biggest;
}
template<class T, class Cond>
Node<T,Cond>* AVLTree<T,Cond>::get_smallest() {
    return this->smallest;
}
template<class T, class Cond>
Node<T,Cond>* AVLTree<T,Cond>::get_second_biggest() {
    return this->secondBiggest;
}
template<class T, class Cond>
Node<T,Cond>* AVLTree<T,Cond>::get_second_smallest() {
    return this->secondSmallest;
}
template<class T, class Cond>
Node<T,Cond>* AVLTree<T,Cond>::get_third_biggest()  {
    return this->thirdBiggest;
}
template<class T, class Cond>
Node<T,Cond>* AVLTree<T,Cond>::get_third_smallest() {
    return this->thirdSmallest;
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
