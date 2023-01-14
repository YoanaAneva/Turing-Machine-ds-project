// #define DOCTEST_CONFIG_IMPLEMENT
// #include "graph.h"
// #include "doctest.h"

// Graph<std::string, int> createTestGraph();

// TEST_CASE("Test Add Vertex"){
//     Graph<std::string, int> graph;
//     graph.addVertex("A");
//     graph.addVertex("B");

//     std::vector<std::string> result;
//     std::vector<std::string> expectedResult1 = {"A", "B"};
//     std::vector<std::string> expectedResult2 = {"B", "A"};

//     for(std::string vertex : graph){
//         result.push_back(vertex);
//     }

//     bool areEqual = result == expectedResult1 || result == expectedResult2;
//     CHECK(areEqual);

//     graph.addVertex("A");
//     graph.addVertex("A");

//     CHECK(graph.vertexExists("A"));
//     CHECK(graph.vertexExists("B"));
//     CHECK(graph.countVertexes("A") == 1);
// }

// TEST_CASE("Test Add Edge"){
//     Graph<std::string, int> cities = createTestGraph();

//     CHECK(cities.edgeExists("Sofia", "Burgas", 210));
//     CHECK(!cities.edgeExists("Sofia", "Burgas", 200));
//     CHECK(!cities.edgeExists("Sofia", "Pernik", 30));

//     CHECK(cities["Sofia"].size() == 4);
//     CHECK(cities["Sofia"][0].data == 210);
//     CHECK(cities["Sofia"][1].data == 107);
//     CHECK(cities["Sofia"][2].data == 315);
//     CHECK(cities["Sofia"][3].data == 55);
// }

// TEST_CASE("Test Iterator"){
//     Graph<std::string, int> cities = createTestGraph();

//     std::vector<std::string> cityNames;
//     for(std::string currVertex : cities){
//         cityNames.push_back(currVertex);
//     }

//     CHECK(std::count(cityNames.begin(), cityNames.end(), "Sofia"));
//     CHECK(std::count(cityNames.begin(), cityNames.end(), "Plovdiv"));
//     CHECK(std::count(cityNames.begin(), cityNames.end(), "Varna"));
//     CHECK(std::count(cityNames.begin(), cityNames.end(), "Burgas"));

//     Graph<std::string,int>::GraphIterator iter = cities.begin();

//     CHECK(*iter == cityNames[0]);

//     ++iter;

//     CHECK(*iter == cityNames[1]);

//     using Edge = Graph<std::string, int>::Edge;

//     std::vector<Edge> edges = iter.getEdges();
//     std::vector<Edge> expectedEdges = cities[cityNames[1]];
//     for(int i = 0; i < expectedEdges.size(); ++i){
//         CHECK(edges[i] == expectedEdges[i]);
//     }
// }

// Graph<std::string, int> createTestGraph(){
//     Graph<std::string, int> cities;
//     cities.addVertex("Sofia");
//     cities.addVertex("Burgas");
//     cities.addVertex("Plovdiv");
//     cities.addVertex("Varna");

//     cities.addEdge("Sofia", "Burgas", 210);
//     cities.addEdge("Sofia", "Plovdiv", 107);
//     cities.addEdge("Sofia", "Plovdiv", 107);
//     cities.addEdge("Sofia", "Varna", 315);
//     cities.addEdge("Sofia", "Varna", 55);

//     return cities;
// }

// int main(){
//     doctest::Context().run();
// }