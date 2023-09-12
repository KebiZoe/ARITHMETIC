//
//  Union.hpp
//  ARITHMETIC
//
//  Created by 曾祥宪 on 2023/8/30.
//

#ifndef Union_h
#define Union_h
#include <unordered_map>

template <class Type>
class Union {
private:
    struct UNode{
        Type value;
        UNode *parent;
        int rank = 1;
        UNode(Type v) {
            value = v;
            parent = this;
        }
    };
    unordered_map<Type, UNode*> *hashmap = new unordered_map<Type, UNode*>();
    
    UNode* findNode(Type v){
        UNode *node = hashmap->at(v);
        if(node == nullptr){
            return nullptr;
        }
        while (node->value!=node->parent->value) {
            node->parent = node->parent->parent;
            node = node->parent;
        }
        return node;
    }
public:
    void makeSet(Type v) {
        if (hashmap->find(v)!=hashmap->end()) return;
            hashmap->insert(tuple<Type, UNode*>(v,new UNode(v)));
        }
    
    void union_(Type v1,Type v2){
        UNode *uv = findNode(v1);
        UNode *uv2 = findNode(v2);
        if(uv == nullptr || uv2 == nullptr) return;
        if (uv2->rank > uv->rank) {
            uv->parent = uv2;
        }else if(uv->rank > uv2->rank){
            uv2->parent = uv;
        }else{
            uv->parent = uv2;
            uv2->rank += 1;
        }
    }
    bool isSame(Type v1,Type v2){
        return findNode(v1)->value == findNode(v2)->value;
    }
    
};

#endif /* Union_h */
