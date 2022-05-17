#include "pch.h"
#include "CppUnitTest.h"
#include "../ALGS_4S_third_lab/main.cpp"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ALGS4SthirdlabTest
{
	TEST_CLASS(ALGS4SthirdlabTest)
	{
	public:
		
		TEST_METHOD(MinDistanceDijkstraGraphsTest) {
			DijkstraGraphs MyDijkstraGraphs(3);
			Pair<string, int> city1("A", 0);
			Pair<string, int> city2("B", 1);
			Pair<string, int> city3("C", 2);
			MyDijkstraGraphs.add_edge(city1, city3, 5);
			MyDijkstraGraphs.add_edge(city1, city2, 1);
			MyDijkstraGraphs.add_edge(city2, city3, 2);
			Assert::IsTrue(MyDijkstraGraphs.dijkstra_lowest_cost(city1, city3) == 3);
		}
		TEST_METHOD(DijkstraAlgorithmDijkstraGraphsTest) {
			DijkstraGraphs MyDijkstraGraphs(3);
			Pair<string, int> city1("A", 0);
			Pair<string, int> city2("B", 1);
			Pair<string, int> city3("C", 2);
			MyDijkstraGraphs.add_edge(city1, city3, 5);
			MyDijkstraGraphs.add_edge(city1, city2, 1);
			MyDijkstraGraphs.add_edge(city2, city3, 2);
			Assert::IsTrue(MyDijkstraGraphs.dijkstra_lowest_cost(city1, city3) == 3);
		}
		TEST_METHOD(AddEdgeDijkstraGraphsTest) {
			DijkstraGraphs MyDijkstraGraphs(3);
			Pair<string, int> city1("A", 0);
			Pair<string, int> city2("B", 1);
			Pair<string, int> city3("C", 2);
			MyDijkstraGraphs.add_edge(city1, city3, 5);
			MyDijkstraGraphs.add_edge(city1, city2, 1);
			MyDijkstraGraphs.add_edge(city2, city3, 2);
			Assert::IsTrue(MyDijkstraGraphs.dijkstra_lowest_cost(city1, city3) == 3);
		}
		TEST_METHOD(DijkstraLowestCostDijkstraGraphsTest) {
			DijkstraGraphs MyDijkstraGraphs(3);
			Pair<string, int> city1("A", 0);
			Pair<string, int> city2("B", 1);
			Pair<string, int> city3("C", 2);
			MyDijkstraGraphs.add_edge(city1, city3, 5);
			MyDijkstraGraphs.add_edge(city1, city2, 1);
			MyDijkstraGraphs.add_edge(city2, city3, 2);
			Assert::IsTrue(MyDijkstraGraphs.dijkstra_lowest_cost(city1, city3) == 3);
			try {
				MyDijkstraGraphs.dijkstra_lowest_cost_path(city3, city1);
			}
			catch (const invalid_argument error) {
				Assert::AreEqual("there is not way from first city to second", error.what());
			}
		}
		TEST_METHOD(DijkstraLowestCostPathDijkstraGraphsTest) {
			DijkstraGraphs MyDijkstraGraphs(3);
			Pair<string, int> city1("A", 0);
			Pair<string, int> city2("B", 1);
			Pair<string, int> city3("C", 2);
			MyDijkstraGraphs.add_edge(city1, city3, 5);
			MyDijkstraGraphs.add_edge(city1, city2, 1);
			MyDijkstraGraphs.add_edge(city2, city3, 2);
			Assert::IsTrue(MyDijkstraGraphs.dijkstra_lowest_cost_path(city1, city3) == "A --> B --> C");
			Assert::IsTrue(MyDijkstraGraphs.dijkstra_lowest_cost_path(city3, city1) == "there is not way from first city to second");
		}
	};
}
