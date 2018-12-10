// Kolorowanie.cpp : main project file.

#include "stdafx.h"
#include "iostream"
#include "fstream"
#include "string"

#define POPULATION 100
#define CROSS_CHANCE 50
#define MUTATION_CHANCE 0
#define STOP_MOMENT 15

using namespace std;

void fitness(int *tab, int size) {
	int min = 99999999;
	for (int i = 1; i > size; i++) {
		if (tab[i] < min)
			min = tab[i];
	}
	tab[0] = min;
}
void sort(int **tab, int M, int N) {
	int temp = 0;
	int min = 9999999;
	int id = 0;
	for (int i = 0; i < M; i++) {
		for (int j = i; j < M; j++) {
			if (tab[j][0] < min) {
				min = tab[j][0];
				id = j;
			}
		}
		for (int j = 0; j < N; j++) {
			temp = tab[i][j];
			tab[i][j] = tab[id][j];
			tab[id][j] = temp;
		}
		min = 99999999;
	}
}
void cross(int **tab, int M, int N, int parent1, int parent2, int child) {
	for (int i = 0; i < N / 2; i++) {
		tab[child][i] = tab[parent1][i];
	}
	for (int i = (N / 2 + 1); i < N; i++) {
		tab[child][i] = tab[parent2][i];
	}
}
void clean(int **graph, int *tab, int N) {
	
}
int GetFirstFreeColor(int *check) {					//checks for the first available color
	int i = 1;
	while (check[i])
		i++;
	return i;
}
void Greedy(int **tab, int *order, int s, int *current) {
	int* colors = new int[s + 1];
	for (int i = 0; i <= s; i++)
		colors[i] = 0;
	

	for (int i = 0; i < s; i++) {					// i - goes through the order array, j - checks vertice neighbours
		for (int j = 1; j <= s; j++) {
			if (tab[order[i]][j] && (order[i] != j)) {		//checks if the edge between ord[i] and j vertice exists and if it's not checking an edge (a,a)
				colors[tab[j][j]] = 1;					//notes the colors of the "j" vertice
			}
		}
		
		tab[order[i]][order[i]] = current[order[i]] = GetFirstFreeColor(colors);		//pushes the first available color for the "a" vertice onto the [a,a] spot in the array
		for (int i = 0; i <= s; i++)						//resetting the colors array
			colors[i] = 0;
	}
	for (int i = 0; i < s; i++) {							//writing the specific vertices' colors onto the console
		cout << order[i] << " ";
	}
	cout << endl;
	delete[] colors;
}
int main()
{
	string buf, buf1;
	int V = 0, size = 0;
	ifstream file;

	file.open("myciel4.txt");						//Opening the file

	if (file.is_open()) {

		getline(file, buf);
		V = stoi(buf);
		size = V + 1;

		int **tab = new int*[size];			//Creating 2D graph's array (vertices start from 1 instead of 0 for clarity sake)
		for (int i = 0; i < size; i++)
			tab[i] = new int[size];

		for (int i = 1; i <= size; i++)
			for (int j = 1; j < size; j++)
				tab[j][i] = 0;

		while (!file.eof()) {

			getline(file, buf, ' ');				//"Grabbing" the edge...
			getline(file, buf1, '\n');

			tab[stoi(buf)][stoi(buf1)] = 1;
			tab[stoi(buf1)][stoi(buf)] = 1;				//...and slapping it into the array
		}

		for (int i = 1; i <= V; i++) {
			for (int j = 1; j <= V; j++) {			//Writing the graph's array onto the console
				cout << tab[i][j];
			}
			cout << '\n';
		}
		int *order = new int[V];
		
		int **populus = new int*[POPULATION];
		for (int i = 0; i < POPULATION; i++)
			populus[i] = new int[size];
		for (int i = 0; i < POPULATION - 1; i++)
			populus[i][0] = 0;

		for (int j = 0; j < V; j++)					//Temporary coloring order array (put permutation generator here)
			order[j] = j + 1;

		/*for (int i = 0; i < V; i++) {	
			Greedy(tab, order, V, populus[i]);					//Where the magic happens...

			
		}
		*/
		
		
	}

	return 0;
}