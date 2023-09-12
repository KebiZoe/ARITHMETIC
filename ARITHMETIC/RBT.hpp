//
//  RBT.h
//  ARITHMETIC
//
//  Created by 曾祥宪 on 2022/11/2.
//

#ifndef RBT_h
#define RBT_h

#import "BST.hpp"
const static bool RED = true;
const static bool BLACK = false;
template <class Type>
struct RBNode: Node<Type>{
    bool color = RED;
    RBNode(Type value): Node<Type>(value), color(RED){};
    ~RBNode(){
        
    };
    virtual string toString(){
        if (color == RED) {
            return "R:"+to_string(this->_value);
        }else{
            return "B:"+to_string(this->_value);
        }
    }
};

template<class Type>
class RBT: public BST<Type>{
    typedef int (*pFunc)(Type,Type);
public:
    RBT(pFunc cmp): BST<Type>(cmp){};
    
    ~RBT(){};
    
    RBNode<Type>* createNode(Type element){
        return new RBNode(element);
    }
    
    void afterAdd(Node<Type> *node){
        RBNode<Type> *node_ = dynamic_cast<RBNode<Type> *>(node);
        RBNode<Type> *pnode = dynamic_cast<RBNode<Type> *>(node->parent);
        if (pnode == nullptr) {
            color(node_, BLACK);
            return;
        }
        if (pnode->color == BLACK) {
            return;
        }
        
        RBNode<Type> *uncle = dynamic_cast<RBNode<Type> *>(pnode->sibling());
        
        RBNode<Type> *grand = color(dynamic_cast<RBNode<Type> *>(pnode->parent), RED);
        
        if(uncle != nullptr && uncle->color == RED){
            color(pnode, BLACK);
            color(uncle, BLACK);
            afterAdd(grand);
            return;
        }
        if(pnode->isLeftChild()){ //L
            if (node->isLeftChild()) { //LL
                color(pnode, BLACK);
            }else{ // LR
                color(node_, BLACK);
                BST<Type>::rotateLeft(pnode);
            }
            BST<Type>::rotateRight(grand);
        }else{ //R
            if (node->isLeftChild()) { //RL
                color(node_, BLACK);
                BST<Type>::rotateRight(pnode);
            }else{ // RR
                color(pnode, BLACK);
            }
            BST<Type>::rotateLeft(grand);
        }
    }
    
    void afterRemove(Node<Type> *node) {
        // 如果删除的节点是红色
        // 或者 用以取代删除节点的子节点是红色
        RBNode<Type> *node_ = dynamic_cast<RBNode<Type> *>(node);
        if(node_->color == RED){
            color(node_, BLACK);
            return;
        }
        RBNode<Type> *pnode = dynamic_cast<RBNode<Type> *>(node->parent);
        if (pnode == nullptr) {
            return;
        }
        // 删除的是黑色叶子节点【下溢】
        // 判断被删除的node是左还是右
        bool left = pnode->left == nullptr || node->isLeftChild();
        RBNode<Type> *sibling = dynamic_cast<RBNode<Type> *>(left ? pnode->right : pnode -> left);
        if (left) { // 被删除的节点在左边，兄弟节点在右边
            if(sibling!=nullptr && sibling->color == RED){ // 兄弟节点是红色
                color(sibling, BLACK);
                color(pnode, RED);
                BST<Type>::rotateLeft(pnode);
                // 更换兄弟
                sibling = dynamic_cast<RBNode<Type> *>(pnode->right);
            }
            // 兄弟节点必然是黑色
            // 兄弟节点没有1个红色子节点，父节点要向下跟兄弟节点合并
            if((sibling->left == nullptr||dynamic_cast<RBNode<Type> *>(sibling->left)->color==BLACK) && (sibling->right == nullptr||dynamic_cast<RBNode<Type> *>(sibling->right)->color==BLACK)){
                bool pb = pnode->color == BLACK;
                color(pnode, BLACK);
                color(sibling, RED);
                if (pb) {
                    afterRemove(pnode);
                }
            }else{// 兄弟节点至少有1个红色子节点，向兄弟节点借元素
                // 兄弟节点的左边是黑色，兄弟要先旋转
                if (sibling->right == nullptr||dynamic_cast<RBNode<Type> *>(sibling->right)->color==BLACK) {
                    BST<Type>::rotateRight(sibling);
                    sibling = dynamic_cast<RBNode<Type> *>(pnode->right);
                }
                color(sibling, pnode->color);
                color(dynamic_cast<RBNode<Type> *>(sibling->right), BLACK);
                color(pnode, BLACK);
                BST<Type>::rotateLeft(pnode);
            }
        }else{ // 被删除的节点在右边，兄弟节点在左边
            if(sibling->color == RED){ // 兄弟节点是红色
                color(sibling, BLACK);
                color(pnode, RED);
                BST<Type>::rotateRight(pnode);
                // 更换兄弟
                sibling = dynamic_cast<RBNode<Type> *>(pnode->left);
            }
            // 兄弟节点必然是黑色
            // 兄弟节点没有1个红色子节点，父节点要向下跟兄弟节点合并
            if((sibling->left == nullptr||dynamic_cast<RBNode<Type> *>(sibling->left)->color==BLACK) && (sibling->right == nullptr||dynamic_cast<RBNode<Type> *>(sibling->right)->color==BLACK)){
                bool pb = pnode->color == BLACK;
                color(pnode, BLACK);
                color(sibling, RED);
                if (pb) {
                    afterRemove(pnode);
                }
            }else{// 兄弟节点至少有1个红色子节点，向兄弟节点借元素
                // 兄弟节点的左边是黑色，兄弟要先旋转
                if (sibling->left == nullptr||dynamic_cast<RBNode<Type> *>(sibling->left)->color==BLACK) {
                    BST<Type>::rotateLeft(sibling);
                    sibling = dynamic_cast<RBNode<Type> *>(pnode->left);
                }
                color(sibling, pnode->color);
                color(dynamic_cast<RBNode<Type> *>(sibling->left), BLACK);
                color(pnode, BLACK);
                BST<Type>::rotateRight(pnode);
            }
        }
        
    }
    
    // 染色
    RBNode<Type> * color(RBNode<Type> *node, bool color){
        if (node == nullptr) {
            return nullptr;
        }
        node->color = color;
        return node;
    }
    
    static void test(){
        RBT<int> *bst = new RBT<int>([](int a,int b)->int{
            return a-b;
        });
        
        vector<int> v = {29, 37, 43, 52, 42, 5, 79, 46, 61, 70, 87, 68, 57, 26, 7, 3};
        for_each(v.begin(), v.end(), [=](int ar){
            bst->add(ar);
            cout<< "  添加 "<< ar << endl;
            bst->display();
        });
        bst->display();
        bst->preorder([](int value){
            cout<< value << "   ";
        });
        cout<< endl;
        bst->inorder([](int value){
            cout<< value << "   ";
        });
        cout<< endl;
        bst->postorder([](int value){
            cout<< value << "   ";
        });
        cout<< endl;
        bst->leverorder([](int value){
            cout<< value << "   ";
        });
        cout<< endl;
        bst->remove(7);
        bst->display();
        bst->remove(29);
        bst->display();
        bst->clear();
        bst->display();
    }
};

#endif /* RBT_h */
