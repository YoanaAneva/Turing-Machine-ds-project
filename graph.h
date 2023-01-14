#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

template<class VertexType, class EdgeData>
class Graph{
public:
    struct Edge{
        EdgeData data;
        VertexType dest;

        bool operator==(const Edge& other) { return data == other.data && dest == other.dest; }
    };
private:
    std::unordered_map<VertexType, std::vector<Edge>> graph;

public:
    void addVertex(const VertexType&);
    void addEdge(const VertexType&, const VertexType&, const EdgeData&);

    bool vertexExists(const VertexType&) const;
    bool edgeExists(const VertexType&, const VertexType&, const EdgeData&) const;

    const std::vector<Edge>& operator[](const VertexType&) const;

    // using MapConstIter = typename std::unordered_map<VertexType,std::vector<Edge>>::const_iterator;
    
    class GraphIterator{
    friend class Graph;
    private:
       typename std::unordered_map<VertexType,std::vector<Edge>>::const_iterator iter;

        GraphIterator(const typename std::unordered_map<VertexType,std::vector<Edge>>::const_iterator& iter_) : iter(iter_) {}
    public:
        GraphIterator& operator++();
        const VertexType& operator*() const;
        bool operator!=(const GraphIterator&);
        const std::vector<Edge>& getEdges() const;
    };

    GraphIterator begin() const;
    GraphIterator end() const;

    size_t countVertexes(const VertexType& vertex) const{
        return graph.count(vertex);
    }
};

template<class VertexType, class EdgeData>
void Graph<VertexType, EdgeData>::addVertex(const VertexType& data){
    graph[data];
}

template<class VertexType, class EdgeData>
void Graph<VertexType, EdgeData>::addEdge(const VertexType& startState, const VertexType& destState, const EdgeData& data){
    if(!vertexExists(startState) || !vertexExists(destState)){
        std::cout << "Cannot add edge, no such start or destination vertex" << std::endl;
        return;
    }
    if(edgeExists(startState, destState, data)){
        std::cout << "This edge already exists" << std::endl;
        return;
    }
    Edge newEdge{data, destState};
    graph[startState].push_back(newEdge);
}

template<class VertexType, class EdgeData>
bool Graph<VertexType, EdgeData>::vertexExists(const VertexType& data) const{
    return graph.count(data) > 0;
}

template<class VertexType, class EdgeData>
bool Graph<VertexType, EdgeData>::edgeExists(const VertexType& startState, const VertexType& destState, const EdgeData& edgeData) const{
    if(!vertexExists(startState) || !vertexExists(destState)){
        return false;
    }
    std::vector<Edge> edges = graph.at(startState);
    for(Edge edge : edges){
        if(edge.dest == destState && edge.data == edgeData){
            return true;
        }
    }
    return false;
}

template<class VertexType, class EdgeData>
const std::vector<typename Graph<VertexType, EdgeData>::Edge>& Graph<VertexType, EdgeData>::operator[](const VertexType& data) const{
    if(!vertexExists(data)){
        throw std::out_of_range("No such vertex");
    }
    return graph.at(data);
}

template<class VertexType, class EdgeData>
typename Graph<VertexType, EdgeData>::GraphIterator& Graph<VertexType, EdgeData>::GraphIterator::operator++(){
    ++iter;
    return *this;
}

template<class VertexType, class EdgeData>
const VertexType& Graph<VertexType, EdgeData>::GraphIterator::operator*() const{
    return iter->first;
}

template<class VertexType, class EdgeData>
bool Graph<VertexType, EdgeData>::GraphIterator::operator!=(const typename Graph<VertexType, EdgeData>::GraphIterator& other){
    return iter != other.iter; 
}

template<class VertexType, class EdgeData>
const std::vector<typename Graph<VertexType, EdgeData>::Edge>& Graph<VertexType, EdgeData>::GraphIterator::getEdges() const{
    return iter->second;
}

template<class VertexType, class EdgeData>
typename Graph<VertexType, EdgeData>::GraphIterator Graph<VertexType, EdgeData>::begin() const{
    return GraphIterator(graph.begin());
} 

template<class VertexType, class EdgeData>
typename Graph<VertexType, EdgeData>::GraphIterator Graph<VertexType, EdgeData>::end() const{
    return GraphIterator(graph.end());
}