#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include<set>
#include <unordered_map>
#include <queue>
#include <stack>


namespace std{
    struct Edge {
        int _destination;
        Edge(int dest) : _destination(dest){}
    };

    struct Vertex {
        int id;
        std::vector<Edge> edges;
        Vertex(int i) : id(i) {}
    };

    class Graph {
    public:
        std::vector<Vertex> vertices;
        void addEdge(int source, int destination, int weight) {
            for (auto &i : vertices) {
                if (i.id == source){i.edges.emplace_back(destination);}
                if (i.id == destination){i.edges.emplace_back(source);}
            }

        }

        Graph(const std::vector<std::vector<int>>& matrix) {
            for (auto &i : matrix) {
                vertices.emplace_back(i[0]);
                vertices.emplace_back(i[1]);
                addEdge(i[0],i[1],1);
                addEdge(i[1],i[0],1);
            }
        }

        void reachableVertices(const int key, std::set<int>& reachable) {
            std::set<int> visited;
            dfs(key, visited);

            for (auto &i:visited) {
                reachable.insert(i);
            }
        }

    private:
        void dfs(int startVertexId, std::set<int>& visited) {
            stack<int> stack;
            stack.push(startVertexId);
            while (!stack.empty()) {
                int currentVertexId = stack.top();
                stack.pop();
                if (visited.count(currentVertexId) == 0) {
                    visited.insert(currentVertexId);
                    int currentVertexIndex = -1;
                    for (int i = 0; i < vertices.size(); ++i) {
                        if (vertices[i].id == currentVertexId) {
                            currentVertexIndex = i;
                            break;
                        }
                    }
                    if (currentVertexIndex != -1) {
                        for (const Edge& edge : vertices[currentVertexIndex].edges) {
                            int neighborId = edge._destination;
                            if (visited.count(neighborId) == 0) {
                                stack.push(neighborId);
                            }
                        }
                    }
                }
            }
        }
    };

    class Solution {
    private:
        static bool compare(const vector<int>& v1, const vector<int>& v2)
        {
            return v1[2] < v2[2];
        }
    public:


        vector<int> findAllPeople(int n, vector<vector<int>>& meetings, int firstPerson) {
            sort(meetings.begin(), meetings.end(), compare);
            map<int,vector<vector<int>>> mapp;
            for (auto &i: meetings) {
                vector<int> tmp;
                tmp.push_back(i[0]);
                tmp.push_back(i[1]);
                mapp[i[2]].push_back(tmp);
            }
            set<int> KeySecret = {0,firstPerson};
            for (auto &i: mapp) {
                auto graph = Graph(i.second);
                for (auto &j : KeySecret) {
                    graph.reachableVertices(j,KeySecret);
                }
            }
            return vector<int>(KeySecret.begin(), KeySecret.end());
        }
    };
}


int main(){
    auto t = new std::Solution;
    std::vector<std::vector<int>> tt = {
    {0,1,8},{0,5,5},{0,5,4},{1,4,5},{0,3,15},{1,0,10},{0,2,14},{2,1,18},{0,5,3},{3,2,1},{4,5,14},{5,3,13},{2,4,5},{2,1,14},{1,3,3},{1,5,17},{2,4,17}};
    auto tm = t->findAllPeople(6,tt,3);
    for (auto& i : tm) {
        std::cout << i;
    }

    return 0;
}