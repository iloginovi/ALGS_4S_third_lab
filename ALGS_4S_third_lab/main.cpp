#include<iostream>
#include "pair.h"
#include "list.h"
#include "stack.h"
#include<fstream>
#include<string>
#include <iomanip>
#include "Map.h"
using namespace std;








class DijkstraGraphs {

	int count_vertexes; 
	Map<int, string> InverseCitiesMap; 
	List<Pair<Pair<string, int>, int> >* AdjacencyList; 

	int* dist;
	int* prev;
	bool* visited;

	
	int min_distance() {
		int min = INT_MAX, index = 0;
		for (int i = 0; i < count_vertexes; i++)
			if (dist[i] <= min && visited[i] == false) {
				min = dist[i];
				index = i;
			}
		return index;
	}

	
	void dijkstra_algorithm(Pair<string, int> start, Pair<string, int> finish) {

		for (int i = 0; i < count_vertexes; i++) { visited[i] = false; };
		for (int i = 0; i < count_vertexes; i++)
			dist[i] = INT_MAX;
		dist[start.second] = 0;
		for (int i = 0; i < count_vertexes - 1; i++) {
			int minimum_distance = min_distance();
			visited[minimum_distance] = true;
			auto current = AdjacencyList[minimum_distance].head;
			while (current != NULL) {
				if (visited[current->value.first.second] == false && dist[minimum_distance] != INT_MAX && dist[current->value.first.second] > dist[minimum_distance] + current->value.second) {
					dist[current->value.first.second] = dist[minimum_distance] + current->value.second;
					prev[current->value.first.second] = minimum_distance;
				}
				current = current->next;
			}
		}

	}

public:
	
	DijkstraGraphs(const int vertexes) {
		count_vertexes = vertexes;
		AdjacencyList = new List<Pair<Pair<string, int>, int> >[count_vertexes];
		dist = new int[count_vertexes];
		prev = new int[count_vertexes];
		visited = new bool[count_vertexes];
	}

	
	~DijkstraGraphs() {
		delete[] AdjacencyList;
		delete[] dist;
		delete[] prev;
		delete[] visited;
		InverseCitiesMap.~Map();
	}

	
	void add_edge(Pair<string, int> vertex_from, Pair<string, int> vertex_to, int weight) {
		AdjacencyList[vertex_from.second].push_back(Pair<Pair<string, int>, int>(vertex_to, weight));
		InverseCitiesMap.insert(vertex_from.second, vertex_from.first);
		InverseCitiesMap.insert(vertex_to.second, vertex_to.first);
	}

	
	int dijkstra_lowest_cost(Pair<string, int> start, Pair<string, int> finish) {

		dijkstra_algorithm(start, finish);

		
		if (dist[finish.second] == INT_MAX) {
			throw invalid_argument("there is not way from first city to second");
		}

		return dist[finish.second];
	}

	
	string dijkstra_lowest_cost_path(Pair<string, int> start, Pair<string, int> finish) {

		dijkstra_algorithm(start, finish);

		string answer = "";

		
		if (dist[finish.second] == INT_MAX) {
			return "there is not way from first city to second";
		}
		else {
			List<string> path;
			for (int v = finish.second; v != start.second; v = prev[v]) {
				path.push_back(InverseCitiesMap.find(v)->value);
			}
			path.push_back(start.first);
			path.reverse();
			auto output = path.head;
			while (output != NULL) {
				answer += output->value;
				if (output != path.last) answer += " --> ";
				output = output->next;
			}

			return answer;
		}

	}

};

int main() {

	cout << "Read the graph adjacency list from file, print them and create graph:\n\n";

	List<string> CitiesCounter;
	Map<string, int> CitiesMap;

	ifstream file_input;
	file_input.open("input.txt");
	string oneString;
	string FirstCityName = "";
	string SecondCityName = "";
	string toInt = "";
	int costTravel = 0;
	while (!file_input.eof()) {
		getline(file_input, oneString);
		cout << oneString << '\n';
		FirstCityName = oneString.substr(0, oneString.find(';'));
		if (!CitiesCounter.contains(FirstCityName)) {
			CitiesMap.insert(FirstCityName, CitiesCounter.size);
			CitiesCounter.push_back(FirstCityName);
		}
		oneString.erase(0, oneString.find(';') + 1);
		SecondCityName = oneString.substr(0, oneString.find(';'));
		if (!CitiesCounter.contains(SecondCityName)) {
			CitiesMap.insert(SecondCityName, CitiesCounter.size);
			CitiesCounter.push_back(SecondCityName);
		}
		oneString.erase(0, oneString.find(';') + 1);
		toInt = oneString.substr(0, oneString.find(';'));
		oneString.erase(0, oneString.find(';') + 1);
		toInt = oneString.substr(0, oneString.find(';'));
	}
	file_input.close();

	int Vertexes = CitiesCounter.size;

	
	DijkstraGraphs MyDijkstraGraphs(Vertexes);

	
	file_input.open("input.txt");
	while (!file_input.eof()) {
		getline(file_input, oneString);
		FirstCityName = oneString.substr(0, oneString.find(';'));
		oneString.erase(0, oneString.find(';') + 1);
		SecondCityName = oneString.substr(0, oneString.find(';'));
		oneString.erase(0, oneString.find(';') + 1);
		toInt = oneString.substr(0, oneString.find(';'));
		if (toInt != "N/A") {
			costTravel = stoi(toInt);
			MyDijkstraGraphs.add_edge(Pair<string, int>(CitiesMap.find(FirstCityName)->key, CitiesMap.find(FirstCityName)->value),Pair<string, int>(CitiesMap.find(SecondCityName)->key, CitiesMap.find(SecondCityName)->value), costTravel);
		}
		oneString.erase(0, oneString.find(';') + 1);
		toInt = oneString.substr(0, oneString.find(';'));
		if (toInt != "N/A") {
			costTravel = stoi(toInt);
			MyDijkstraGraphs.add_edge(Pair<string, int>(CitiesMap.find(SecondCityName)->key, CitiesMap.find(SecondCityName)->value), Pair<string, int>(CitiesMap.find(FirstCityName)->key, CitiesMap.find(FirstCityName)->value), costTravel);
		}
	}

	
	string city_from = "Rome";
	string city_to = "London";

	cout << "\nFind the lowest cost path from " << city_from << " to " << city_to << ":\n";

	cout << MyDijkstraGraphs.dijkstra_lowest_cost_path(Pair<string, int>(CitiesMap.find(city_from)->key, CitiesMap.find(city_from)->value), Pair<string, int>(CitiesMap.find(city_to)->key, CitiesMap.find(city_to)->value));

	cout << "\nTravelling cost is: ";

	try {
		cout << MyDijkstraGraphs.dijkstra_lowest_cost(Pair<string, int>(CitiesMap.find(city_from)->key, CitiesMap.find(city_from)->value), Pair<string, int>(CitiesMap.find(city_to)->key, CitiesMap.find(city_to)->value));
	}
	catch (const invalid_argument error) {
		cout << error.what();
	}

}