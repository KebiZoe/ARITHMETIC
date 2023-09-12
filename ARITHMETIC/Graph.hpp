//
//  Graph.hpp
//  ARITHMETIC
//
//  Created by 曾祥宪 on 2023/9/1.
//

#ifndef Graph_h
#define Graph_h

#include <unordered_set>
template <class V,class E>
class Graph {
    class Vertex;
    class Edge{
    public:
        Vertex *from;
        Vertex *to;
        E weight;
    
        Edge(Vertex *from,Vertex *to,E e):from(from),to(to),weight(e){}
        ~Edge(){}
        bool operator==(const Edge& edg) const{
            return from == edg.from && to == edg.to;
        }
        struct HashFunction{
            size_t operator()(const Edge& edg) const{
                size_t f = hash<Vertex>{}(edg.from);
                size_t t = hash<Vertex>{}(edg.to);
                return f^t;
            }
        };
        string toString(){
            return "EdgeInfo [from=" + from + ", to=" + to + ", weight=" + weight + "]";
        }
    };
    class Vertex{
    public:
        V value;
        unordered_set<Edge*> *inEdges = new unordered_set<Edge*>();
        unordered_set<Edge*> *outEdges = new unordered_set<Edge*>();
        bool operator==(const Vertex& other) const{
            return value == other.value;
        }
        struct HashFunction{
            size_t operator()(const Vertex& v) const{
                return hash<V>{}(v);
            }
        };
        Vertex(V v):value(v){}
        ~Vertex(){}
    };
    
public:
    unordered_map<V, Vertex *> vertices = unordered_set<V, Vertex *>();
    unordered_set<Edge *> edges = unordered_set<Edge *>();
    
    Graph(){
        
    }
    ~Graph(){
        
    }
    void addVertex(V v){
        if(vertices.find(v) != vertices.end()) return;
        vertices[v] = new Vertex(v);
    }
    
    void addEdge(V from,V to, E e){
        Vertex *fromVertex = vertices.find(from);
        if(fromVertex == vertices.end()){
            vertices[from] = new Vertex(from);
        }
        Vertex *toVertex = vertices.find(to);
        if(toVertex == vertices.end()){
            vertices[to] = new Vertex(to);
        }
        Edge *edg = new Edge(fromVertex,toVertex,e);
        if (fromVertex->outEdges->find(edg)!=fromVertex->outEdges->end()) {
            fromVertex->outEdges->erase(edg);
            toVertex->outEdges->erase(edg);
            edges.erase(edg);
        }
        fromVertex->outEdges->insert(edg);
        toVertex->outEdges->insert(edg);
        edges.insert(edg);
    }
    
    void removeEdge(V from,V to, E e){
        Vertex *fromVertex = vertices.find(from);
        if(fromVertex == vertices.end()){
            return;
        }
        Vertex *toVertex = vertices.find(to);
        if(toVertex == vertices.end()){
            return;
        }
        Edge *edg = new Edge(fromVertex,toVertex,e);
        if (fromVertex->outEdges->find(edg)!=fromVertex->outEdges->end()) {
            fromVertex->outEdges->erase(edg);
            toVertex->outEdges->erase(edg);
            edges.erase(edg);
        }
    }
    void removeVertex(V v){
        auto it = vertices.find(v);
        if (it == vertices.end()) {
            return;
        }
        Vertex *vvv = it->second;
        for (Edge *edg : vvv->inEdges) {
            edg->from->outEdges->erase(edg);
            edges.erase(edg);
        }
        for (Edge *edg : vvv->outEdges) {
            edg->to->inEdges->erase(edg);
            edges.erase(edg);
        }
    }
    template<class F>
    void bfs(Vertex &beginVertex, const F& func){
        unordered_set<Vertex*> visitedVertices = unordered_set<Vertex*>();
        Queue<Vertex*> queue = Queue<Vertex*>();
        queue.enQueue(beginVertex);
        visitedVertices.insert(beginVertex);
        while (!queue.isEmpty()) {
            Vertex *vetx = queue.deQueue();
            func(vetx->value);
            for (Edge *edg : vetx->outEdgesdges) {
                if (visitedVertices.find(edg->to)!=visitedVertices.end()) {
                    continue;
                }
                queue.enQueue(edg->to);
                visitedVertices.insert(edg->to);
            }
        }
    }
    template<class F>
    void dfs(Vertex &beginVertex, const F& func){
        unordered_set<Vertex*> visitedVertices = unordered_set<Vertex*>();
        Stack<Vertex*> stack = Stack<Vertex*>();
        stack.push(beginVertex);
        visitedVertices.insert(beginVertex);
        while (!stack.isEmpty()) {
            Vertex *vetx = stack.top();
            for (Edge *edg : vetx->outEdgesdges) {
                if (visitedVertices.find(edg->to)!=visitedVertices.end()) {
                    continue;
                }
                stack.push(edg->from);
                stack.push(edg->to);
                visitedVertices.insert(edg->to);
                func(edg->to->value);
                break;
            }
        }
    }
    bool aov(){
        Queue<Vertex *> queue = Queue<Vertex *>();
        unordered_map<Vertex *, int> map = unordered_map<Vertex *, int>();
        for_each(vertices.begin(), vertices.end(), [](V v, Vertex *vtx){
            if (vtx->inEdges->size() == 0) {
                queue.enQueue(vtx);
            }else{
                map.insert(tuple<Vertex *, int>(vtx, vtx->inEdges->size()));
            }
        });
        vector<Vertex *> vect = std::vector<Vertex *>();
        while (queue.isEmpty()!=true) {
            Vertex *vtx = queue.deQueue();
            vect.push_back(vtx);
            unordered_set<Edge*> *outedgs = vtx->outEdges;
            for_each(outedgs->begin(), outedgs->end(), [](Edge *edg){
                int inedgs = map.at(edg->to) - 1;
                if (inedgs == 0) {
                    queue.enQueue(edg->to);
                }else{
                    map[edg->to] = inedgs;
                }
            });
        }
        if (vect.size() == vertices.size()) {
            return true;
        }else{
            return false;
        }
    }
    
    unordered_set<Edge *> prim(){
        iterator<V, Vertex*> it = vertices.begin();
        if (it == vertices.end()) {
            return unordered_set<Edge *>();
        }
        Vertex *vtx = it->second;
        unordered_set<Vertex *> addedVertics = unordered_set<Vertex *>();
        unordered_set<Edge *> edgeset = unordered_set<Edge *>();
        auto cmp = [](Edge edg1, Edge edg2)->bool{
            return edg1.weight <= edg2.weight;
        };
        Heap<Edge, decltype(cmp)> heap(vtx->outEdges,cmp);
        while (heap.size()!=0 && addedVertics.size()<vertices.size()) {
            Edge *tedg = heap.remove();
            
            if (addedVertics.find(tedg->to)!=addedVertics.end()) {
                continue;
            }
            edgeset.insert(tedg);
            addedVertics.insert(tedg->to);
            for (Edge *edg : tedg->to->outEdges) {
                heap.add(edg);
            }
        }
        
        return edgeset;
    }
    
    unordered_set<Edge *> kruskall(){
        auto cmp = [](Edge edg1, Edge edg2)->bool{
            return edg1.weight <= edg2.weight;
        };
        Heap<Edge, decltype(cmp)> heap(edges,cmp);
        unordered_set<Edge *> edgeset = unordered_set<Edge *>();
        Union<Vertex*> un = Union<Vertex*>();
        for (Vertex *v : vertices) {
            un.makeSet(v);
        }
        while (heap.size()!=0&&edgeset.size()<vertices.size()-1) {
            Edge *edg = heap.remove();
            if (un.isSame(edg->from, edg->to)) {
                continue;
            }
            un.union_(edg->from, edg->to);
            edgeset.inert(edg);
        }
        
        return edgeset;
    }
    
};

#endif /* Graph_h */
