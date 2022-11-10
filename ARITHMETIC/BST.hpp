//
//  BST.hpp
//  ARITHMETIC
//
//  Created by 曾祥宪 on 2022/6/9.
//

#ifndef BST_hpp
#define BST_hpp

#import <stdio.h>
#import <functional>
#import "Stack.hpp"
#import "Queue.hpp"
#import <map>

template <class Type>
struct Node {
public:
    Type _value;
    Node<Type> *parent = nullptr;
    Node<Type> *left = nullptr;
    Node<Type> *right = nullptr;

    Node(Type value){
        _value = value;
        parent = nullptr;
        left = nullptr;
        right = nullptr;
    }
    virtual ~Node(){
        _value = NULL;
        parent = nullptr;
        left = nullptr;
        right = nullptr;
    }
    bool isLeaf(){
        return left == NULL && right == NULL;
    }
    bool hasTwoChildren(){
        return left != NULL && right != NULL;
    }
    bool isLeftChild(){
        return parent != NULL && this == parent->left;
    }
    bool isRightChild(){
        return parent != NULL && this == parent->right;
    }
    /// 兄弟节点
    Node<Type>* sibling(){
        if (isLeftChild()) {
            return parent->right;
        }
        if(isRightChild()){
            return parent->left;
        }
        return nullptr;
    }
    
    void static output_impl(Node *node,bool left, string const& indent){
        if (node->right != nullptr) {
            output_impl(node->right, false, indent+(left ? "|     " : "      "));
        }
        std::cout << indent;
        std::cout << (left ? "└" : "┌");
        std::cout << "----";
        std::cout << ":" << node->_value << endl;
        if (node->left != nullptr) {
            output_impl(node->left, true, indent+(left ? "      " : "|     "));
        }
    }
    void static output(Node *node){
        if (node == nullptr){
            return;
        }
        if (node->right != nullptr) {
            output_impl(node->right, false, " ");
        }
        std::cout << ":" << node->_value << endl;
        if (node->left != nullptr) {
            output_impl(node->left, true, " ");
        }
        std::cout << "--------------------------------------------------" << endl;
    }
};

template <class Type>
class BST {
    typedef int (*pFunc)(Type,Type);
public:
    int _size;
    Node<Type> *_root;
    pFunc _cmp;
    
    BST(pFunc cmp){
        _cmp = cmp;
        _root = nullptr;
        _size = 0;
    }
    virtual ~BST(){
        _cmp = nullptr;
        //遍历
        clear();
    }
    int size(){
        return _size;
    }
    bool isEmpty(){
        return _size == 0;
    }
    virtual Node<Type>* createNode(Type element){
        return new Node(element);
    }
    void clear(){
        // 后续遍历移除所有节点
        Stack<Node<Type>*> *stack = new Stack<Node<Type>*>();
        if (_root!=nullptr) {
            stack->push(_root);
        }
        while (!stack->isEmpty()) {
            Node<Type> *cur = stack->pop();
            if (cur->isLeaf()) {
                if (cur->isLeftChild()) {
                    cur->parent->left = nullptr;
                    delete cur;
                }else if(cur->isRightChild()){
                    cur->parent->right = nullptr;
                    delete cur;
                }else{ // 根节点
                    delete cur;
                    _root = nullptr;
                }
            }else{
                stack->push(cur);
                if (cur->right!=nullptr) {
                    stack->push(cur->right);
                }
                if (cur->left!=nullptr) {
                    stack->push(cur->left);
                }
            }
        }
        delete stack;
        _size = 0;
    }
    virtual void add(Type element){
        const char *t = typeid(element).name();
        if (strcmp(t, "i")==0) {
            goto doint;
        }
        if (element == NULL) {
            throw std::invalid_argument("添加的元素不能为null");
        }
        doint:
        // 添加第一个元素
        if(_root == nullptr){
            _root = createNode(element);
            _size++;
            afterAdd(_root);
            return;
        }
        // 添加的元素不是第一个
        Node<Type> *cur = _root;
        Node<Type> *p = _root;
        int cmp = 0;
        while (cur != nullptr) {
            cmp = _cmp(element, cur->_value);
            p = cur;
            if (cmp>0) {
                cur = cur->right;
            }else if(cmp<0){
                cur = cur->left;
            }else{
                cur->_value = element;
                return;
            }
        }
        Node<Type> *nnode = createNode(element);
        nnode->parent = p;
        if (cmp>0) {
            p->right = nnode;
        }else{
            p->left = nnode;
        }
        _size++;
        /// 添加新节点后应该调整平衡
        afterAdd(nnode);
    }
    virtual void afterAdd(Node<Type> *){
        
    }
    virtual void rotateLeft(Node<Type> *grand){
        Node<Type> *parent = grand->right;
        Node<Type> *child = parent->left;
        grand->right = child;
        parent->left = grand;
        // 维护parent和height的高度
        afterRotate(grand, parent, child);
    }
    virtual void rotateRight(Node<Type> *grand){
        Node<Type> *parent = grand->left;
        Node<Type> *child = parent->right;
        grand->left = child;
        parent->right = grand;
        // 维护parent和height的高度
        afterRotate(grand, parent, child);
    }
    void afterRotate(Node<Type> *grand,Node<Type> *parent,Node<Type> *child){
        if (grand->isLeftChild()){
            grand->parent->left = parent;
        }else if(grand->isRightChild()){
            grand->parent->right = parent;
        }else{
            _root = parent;
        }
        
        if (child != NULL){
            child->parent = grand;
        }
        
        parent->parent = grand->parent;
        grand->parent = parent;
        
        updateHeight(grand);
        updateHeight(parent);
    }
    virtual void updateHeight(Node<Type> *node){
        
    }
    void remove(Type element){
        Node<Type> *node = find(element);
        if (node == nullptr) {
            return;
        }
        // 如果有连个子节点，找到前驱节点替代，或者后驱节点替代，最后删除替代节点就行
        if(node->hasTwoChildren()){
            Node<Type> *curnode = successor(node);
            node->_value = curnode->_value;
            node = curnode;
        }
        Node<Type> *replacenode = node->left!=nullptr ? node->left : node->right;
        if (replacenode!=nullptr) {
            replacenode->parent = node->parent;
            if (node->parent==nullptr) { // 根节点
                _root = replacenode;
            }else if(node->isLeftChild()){
                node->parent->left = replacenode;
            }else{
                node->parent->right = replacenode;
            }
            afterRemove(node);
        }else if(node->parent==nullptr){
            _root = nullptr;
            afterRemove(node);
        }else{
            if(node->isLeftChild()){
                node->parent->left = nullptr;
            }else{
                node->parent->right = nullptr;
            }
            afterRemove(node);
        }
        delete node;
        _size--;
        
    }
    /// 删除节点后调节平衡
    virtual void afterRemove(Node<Type> *node) { }
    void display(){
        Node<Type>::output(_root);
    }
    /*------------------------遍历-------------------------*/
    //前序遍历 采用非递归的方式，用栈来存储遍历节点的右节点
    void preorder(void (*visitor)(Type)){
        if(visitor==nullptr) return;
        Stack<Node<Type>*> *stack = new Stack<Node<Type>*>();
        Node<Type> *cur = _root;
        while (cur!=nullptr) {
            if (cur->right!=nullptr) {
                stack->push(cur->right);
            }
            visitor(cur->_value);
            if (cur->left!=nullptr) {
                cur = cur->left;
            }else{
                if (stack->isEmpty()) {
                    cur = nullptr;
                }else{
                    cur = stack->pop();
                }
            }
        }
        delete stack;
    }
    // 中序遍历
    void inorder(void (*visitor)(Type)){
        if(visitor==nullptr) return;
        Stack<Node<Type>*> *stack = new Stack<Node<Type>*>();
        Node<Type> *cur = _root;
        map<Type, bool> visted = map<Type, bool>();
        while (cur!=nullptr) {
            if (cur->left!=nullptr&&visted[cur->left->_value]==false) {
                stack->push(cur);
                cur = cur->left;
                continue;
            }
            visted[cur->_value]=true;
            visitor(cur->_value);
            if (cur->right!=nullptr) {
                cur = cur->right;
                continue;
            }
            if (stack->isEmpty()) {
                cur = nullptr;
            }else{
                cur = stack->pop();
            }
        }
        delete stack;
    }
    // 后续遍历 先遍历左子节点后遍历右子节点，再遍历父节点
    void postorder(void (*visitor)(Type)){
        if(visitor==nullptr) return;
        Stack<Node<Type>*> *stack = new Stack<Node<Type>*>();
        if (_root!=nullptr) {
            stack->push(_root);
        }
        map<Type, bool> visted = map<Type, bool>();
        while (!stack->isEmpty()) {
            Node<Type> *cur = stack->pop();
            if (cur->isLeaf()||(cur->right!=nullptr&&visted[cur->right->_value]==true)||(cur->left!=nullptr&&visted[cur->left->_value]==true)) {
                visitor(cur->_value);
                visted[cur->_value] = true;
            }else{
                stack->push(cur);
                if (cur->right!=nullptr && visted[cur->right->_value]==false) {
                    stack->push(cur->right);
                }
                if (cur->left!=nullptr && visted[cur->left->_value]==false) {
                    stack->push(cur->left);
                }
            }
        }
        delete stack;
    }
    // 层序遍历
    void leverorder(void (*visitor)(Type)){
        if(visitor==nullptr) return;
        Queue<Node<Type>*> *que = new Queue<Node<Type>*>();
        if (_root!=nullptr) {
            que->enQueue(_root);
        }
        while (!que->isEmpty()) {
            Node<Type> *cur = que->deQueue();
            visitor(cur->_value);
            if (cur->left!=nullptr) {
                que->enQueue(cur->left);
            }
            if (cur->right!=nullptr) {
                que->enQueue(cur->right);
            }
        }
        delete que;
    }
    
    bool contains(Type value){
        return find(value) != nullptr;
    }
    /*------------------------完全二叉树-------------------------*/
    bool isCompleteTree(){
        Queue<Node<Type>*> *que = new Queue<Node<Type>*>();
        if (_root!=nullptr) {
            que->enQueue(_root);
        }
        bool isleaf = false; // 没有出现叶子节点
        bool iscomplete = true;
        while (!que->isEmpty()) {
            Node<Type> *cur = que->deQueue();
            if (isleaf==true && !cur->isLeaf()) {
                iscomplete = false;
                break;
            }
            
            if (cur->left!=nullptr) {
                que->enQueue(cur->left);
            }else if(cur->right!=nullptr){
                iscomplete = false;
                break;
            }
            
            if (cur->right!=nullptr) {
                que->enQueue(cur->right);
            }else{
                isleaf = true;
            }
        }
        delete que;
        return iscomplete;
    }
    /*------------------------树的高度-------------------------*/
    // 两种方法，一种是递归，另一种是层序遍历，两种算法的时间效率差不多，但是递归开辟的更多的栈空间，会消耗更多的性能
    int height(){
        Queue<Node<Type>*> *que = new Queue<Node<Type>*>();
        if (_root!=nullptr) {
            que->enQueue(_root);
        }
        int leversize = 1;
        int height = 0;
        while (!que->isEmpty()) {
            Node<Type> *cur = que->deQueue();
            leversize--;
            
            if (cur->left!=nullptr) {
                que->enQueue(cur->left);
            }
            if (cur->right!=nullptr) {
                que->enQueue(cur->right);
            }
            if (leversize==0) {
                height++;
                leversize = que->size();
            }
        }
        delete que;
        return height;
    }
    /// 用递归方式获取高度
    int recHeight(){
        return recHeight(_root);
    }
protected:
    Node<Type>* find(Type element){
        Node<Type> *cur = _root;
        while (cur != nullptr) {
            int cmp = _cmp(element, cur->_value);
            if (cmp>0) {
                cur = cur->right;
            }else if(cmp<0){
                cur = cur->left;
            }else{
                return cur;
            }
        }
        return cur;
    }
    // 前驱节点
    Node<Type>& predecessor(Node<Type>& node){
        if (node==nullptr) {
            return ;
        }
        Node<Type> *prenode = node;
        //前驱节点在左子树中left-right···right
        if (node->left!=nullptr) {
            prenode = node->left;
            while (prenode->right!=nullptr) {
                prenode = prenode->right;
            }
            return prenode;
        }
        
        while (prenode->parent!=0&&prenode->isLeftChild()) {
            prenode = prenode->parent;
        }
        return prenode->parent;
        
    }
    // 后继节点
    Node<Type>* successor(Node<Type>* node){
        if (node==nullptr) {
            return nullptr;
        }
        Node<Type> *sucnode = node;
        //前驱节点在左子树中right-left···left
        if (node->right!=nullptr) {
            sucnode = node->right;
            while (sucnode->left!=nullptr) {
                sucnode = sucnode->right;
            }
            return sucnode;
        }
        
        while (sucnode->parent!=0&&sucnode->isRightChild()) {
            sucnode = sucnode->parent;
        }
        return sucnode->parent;
    }
    
    int recHeight(Node<Type>&node){
        if (node!=nullptr) {
            return 0;
        }
        return 1+max(recHeight(node->left), recHeight(node->right));
    }
};







#endif
