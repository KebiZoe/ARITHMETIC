//
//  AVL.hpp
//  ARITHMETIC
//
//  Created by 曾祥宪 on 2022/6/26.
//

#ifndef AVL_hpp
#define AVL_hpp

#import "BST.hpp"

template <class Type>
struct AVLNode: Node<Type>{
    int height = 1;
    AVLNode(Type value): Node<Type>(value), height(1){};
    ~AVLNode(){
        height = 0;
    };
    
    /// 平衡因子
    int balanceFactor(){
        AVLNode<Type> * leftNode = dynamic_cast<AVLNode<Type> *>(this->left);
        int leftHeight = leftNode == nullptr ? 0 : leftNode->height;
        AVLNode<Type> * rightNode = dynamic_cast<AVLNode<Type> *>(this->right);
        int rightHeight = rightNode == nullptr ? 0 : rightNode->height;
        return leftHeight-rightHeight;
    }
    /// 更新高度
    void updateHeight(){
        AVLNode<Type> * leftNode = dynamic_cast<AVLNode<Type> *>(this->left);
        AVLNode<Type> * rightNode = dynamic_cast<AVLNode<Type> *>(this->right);
        int leftHeight = leftNode == nullptr ? 0 : leftNode->height;
        int rightHeight = rightNode == nullptr ? 0 : rightNode->height;
        height = 1 + max(leftHeight, rightHeight);
    }
    /// 获取较高的子节点 而且这里一般只在失衡的时候用得到，基本也就是g p n
    AVLNode<Type>* tallerChild(){
        AVLNode<Type> * leftNode = dynamic_cast<AVLNode<Type> *>(this->left);
        AVLNode<Type> * rightNode = dynamic_cast<AVLNode<Type> *>(this->right);
        int leftHeight = leftNode == nullptr ? 0 : leftNode->height;
        int rightHeight = rightNode == nullptr ? 0 : rightNode->height;
        if (leftHeight>rightHeight){
            return leftNode;
        }else if(leftHeight<rightHeight){
            return rightNode;
        }else{
            return this->isLeftChild() ? leftNode : rightNode;
        }
    }
    
};

template<class Type>
class AVL: public BST<Type>{
    typedef int (*pFunc)(Type,Type);
public:
    AVL(pFunc cmp): BST<Type>(cmp){};
    
    ~AVL(){};
    
    AVLNode<Type>* createNode(Type element){
        return new AVLNode(element);
    }
    void afterAdd(Node<Type> *node){
        // 添加的节点一定是在叶子节点，依次往上更新节点高度，直到找出失衡节点
        AVLNode<Type> *avnode = dynamic_cast<AVLNode<Type> *>(node);
        while ((avnode = dynamic_cast<AVLNode<Type> *>(avnode->parent))!=nullptr) {
            if (isBalanced(avnode)) {
                avnode->updateHeight();
            }else{/// 失衡节点
                rebalance(avnode);
                break;
            }
        }
    }
    
    void afterRotate(Node<Type> *grand,Node<Type> *parent,Node<Type> *child) {
        BST<Type>::afterRotate(grand, parent, child);
        updateHeight(grand);
        updateHeight(parent);
    }
    
    void afterRemove(Node<Type> *node) {
        AVLNode<Type> *avnode = dynamic_cast<AVLNode<Type> *>(node);
        while ((avnode = dynamic_cast<AVLNode<Type> *>(avnode->parent))!=nullptr) {
            if (isBalanced(avnode)) {
                avnode->updateHeight();
            }else{/// 失衡节点
                rebalance(avnode);
            }
        }
    }
    
    void rebalance(AVLNode<Type> *grand){
        AVLNode<Type> *parent = grand->tallerChild();
        AVLNode<Type> *node = parent->tallerChild();
        if (parent->isLeftChild()) { // L
            if (node->isLeftChild()) { // LL
                //右旋转G节点
                BST<Type>::rotateRight(grand);
            }else{ // LR
                // 先左旋转P，再右旋转G
                BST<Type>::rotateLeft(parent);
                BST<Type>::rotateRight(grand);
            }
        }else{ // R
            if (node->isLeftChild()) { // RL
                // 先右旋转P，再左旋转G
                BST<Type>::rotateRight(parent);
                BST<Type>::rotateLeft(grand);
            }else { // RR
                //左旋转G节点
                BST<Type>::rotateLeft(grand);
            }
        }
    }
    
    void updateHeight(Node<Type> *node){
        AVLNode<Type> *avnode = dynamic_cast<AVLNode<Type> *>(node);
        avnode->updateHeight();
    }
    
    
    bool isBalanced(AVLNode<Type> *node){
        return abs(node->balanceFactor())<=1;
    }
    
    static void test(){
        AVL<int> *bst = new AVL<int>([](int a,int b)->int{
            return a-b;
        });
        
        vector<int> v = {29, 37, 43, 52, 42, 5, 79, 46, 61, 70, 87, 68, 57, 26, 7, 3};
        for_each(v.begin(), v.end(), [=](int ar){
            bst->AVL<int>::add(ar);
        });
        bst->display();
        cout<<"前序遍历树"<<endl;
        bst->preorder([](int value){
            cout<< value << "   ";
        });
        cout<< endl;
        cout<<"中序遍历树"<<endl;
        bst->inorder([](int value){
            cout<< value << "   ";
        });
        cout<< endl;
        cout<<"后序遍历树"<<endl;
        bst->postorder([](int value){
            cout<< value << "   ";
        });
        cout<< endl;
        cout<<"层序遍历树"<<endl;
        bst->leverorder([](int value){
            cout<< value << "   ";
        });
        cout<< endl;
        cout<<"移除7"<<endl;
        bst->remove(7);
        bst->display();
        cout<<"移除29"<<endl;
        bst->remove(29);
        bst->display();
        cout<<"高度"<<bst->height()<<endl;
        bst->clear();
        bst->display();
    }
};



#endif /* AVL_h */
