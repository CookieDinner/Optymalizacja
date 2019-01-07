// Kolorowanie.cpp : main project file.

#include "stdafx.h"
#include "iostream"
#include "fstream"
#include "string"
#include "time.h"
#include "stdlib.h"
#include "stdio.h"

#define POPULATION     100  //M
#define CROSS_CHANCE 50
#define MUTATION_CHANCE 0
#define STOP_MOMENT 100
#define GEN_DIVIDER 3
#define GREED_NUM 10

#define NAZWA_PLIKU "gc_1000_300013.txt"

using namespace std;



class Graph
{
public:

	int V = 0;	//iloœæ wierzcho³ków w grafie
	int size = 0; //rozmiar tablicy -- o 1 wiêksze ni¿ V ¿eby indeksowaæ od 1 a nie od 0
	int **tab; //nasz graf


	void pobierz_V_z_pliku(ifstream &file)
	{
		string buf;
		getline(file, buf);
		V = stoi(buf);
		size = V + 1;
	}

	void stwórz_pusty_graf()
	{
		tab = new int*[size];			//Creating 2D graph's array (vertices start from 1 instead of 0 for clarity sake)
		for (int i = 0; i < size; i++)
			tab[i] = new int[size];

		for (int i = 1; i < size; i++)
			for (int j = 1; j < size; j++)
				tab[i][j] = 0;
	}

	void uzupelnij_graf_danymi(ifstream &file)
	{

		while (!file.eof()) {

			string buf, buf1;
			getline(file, buf, ' ');				//"Grabbing" the edge...
			getline(file, buf1, '\n');

			tab[stoi(buf)][stoi(buf1)] = 1;
			tab[stoi(buf1)][stoi(buf)] = 1;				//...and slapping it into the array
		}
	}

	void wypisz_graf_na_konsole()
	{
		for (int i = 1; i < size; i++) {
			for (int j = 1; j < size; j++) {			//Writing the graph's array onto the console
				cout << tab[i][j];
			}
			cout << '\n';
		}
	}


	virtual ~Graph()
	{
		/*for (int i = 0; i < size; i++)
		delete[] tab[i];*/
		delete[] tab;
	}

};
void cycle(int *order, int size) {
	int temp = order[0], i;
	for (i = 0; i < size - 1; i++)
		order[i] = order[i + 1];
	order[i] = temp;
}
void fitness(int **tab, int size)
{
	for (int j = 0; j < POPULATION; j++) {
		int max = 0;
		for (int i = 1; i <= size; i++)
		{
			if (tab[j][i] > max)
				max = tab[j][i];
		}

		tab[j][0] = max;
	}
}
void sort(int **tab, int M, int N)
{
	int temp = 0;
	int min = 9999999;
	int id = 0;
	for (int i = 0; i < M; i++)
	{
		for (int j = i; j < M; j++)
		{
			if (tab[j][0] < min)
			{
				min = tab[j][0];
				id = j;
			}
		}
		for (int j = 0; j <= N; j++)
		{
			temp = tab[i][j];
			tab[i][j] = tab[id][j];
			tab[id][j] = temp;
		}
		min = 99999999;
	}
}
void cross(int **tab, int N, int parent1, int parent2, int child)
{
	for (int i = 1; i < (N / 2); i++)
	{
		tab[child][i] = tab[parent1][i];
	}

	for (int i = (N / 2); i <= N; i++)
	{
		tab[child][i] = tab[parent2][i];
	}
}
void cleanColor(int **graph, int *tab, int N, int vertice) {
	int starter = 1;
	bool flag = true;
	while (flag) {
		flag = false;
		for (int i = 1; i <= N; i++)
			if (graph[vertice][i] && tab[i] == starter) {
				flag = true;
				starter++;
			}
	}
	tab[vertice] = starter;
}
void clean(int **graph, int *tab, int N) {
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			if (graph[i][j] && (tab[i] == tab[j])) {
				cleanColor(graph, tab, N, i);
				break;
			}
		}
	}
}
void addRandomChromosomes(int **graph, int **tab, int M, int N, int X) {
	for (int i = N; i < M; i++) {
		for (int j = 1; j <= X; j++)
			tab[i][j] = (((rand() % (X + 1)) / GEN_DIVIDER) + 1);
		clean(graph, tab[i], X);
	}
}



int GetFirstFreeColor(int *check, int size) //checks for the first available color
{
	int color = 1;
	bool flag = true;
	while (flag) {
		flag = false;
		for (int i = 1; i <= size; i++) {
			if (color == check[i]) {
				color++;
				flag = true;
			}
		}
	}
	return color;
}

void Greedy(int **tab, int *order, int s, int *current) {
	int* colors = new int[s + 1];
	for (int i = 0; i <= s; i++)
		colors[i] = 0;


	for (int i = 0; i < s; i++) // i - goes through the order array, j - checks vertice neighbours
	{
		for (int j = 1; j <= s; j++)
		{
			if ((order[i] != j) && tab[order[i]][j])  //checks if the edge between ord[i] and j vertice exists and if it's not checking an edge (a,a)
			{
				colors[j] = current[j];					//notes the neighbours of the currently checked vertice
			}
		}

		//tab[order[i]][order[i]] = GetFirstFreeColor(colors);
		current[order[i]] = GetFirstFreeColor(colors, s);		//pushes the first available color for the "a" vertice onto the [a,a] spot in the array

		for (int i = 0; i <= s; i++) {						//resetting the colors array
			colors[i] = 0;
		}
	}

	/*for (int i = 1; i <= s; i++)
	{
		tab[i][i] = 0;
	}*/

	delete[] colors;
}



int main()
{
	srand(unsigned(time(NULL)));
	ifstream file;

	file.open(NAZWA_PLIKU);						//Opening the file

	if (file.is_open())
	{

		Graph graf;


		graf.pobierz_V_z_pliku(file);
		graf.stwórz_pusty_graf();
		graf.uzupelnij_graf_danymi(file);
		//graf.wypisz_graf_na_konsole();


		int *order = new int[graf.V]; //
		for (int j = 0; j < graf.V; j++)					
			order[j] = j + 1;

		int **populus = new int*[POPULATION];
		for (int i = 0; i < POPULATION; i++)
			populus[i] = new int[graf.size];
		for (int i = 0; i < POPULATION; i++)
			for (int j = 0; j < graf.size; j++)
				populus[i][j] = 0;

		for (int i = 0; i < GREED_NUM; i++)
		{
			Greedy(graf.tab, order, graf.V, populus[i]);
			cycle(order, graf.V);
		}



		/*	To zawar³em niby w destruktorze grafu         */
		//{
		/*for (int i = 0; i < graf.size; i++)
		delete[] graf.tab[i];*/

		//delete[] graf.tab;
		//}

		addRandomChromosomes(graf.tab, populus, POPULATION, GREED_NUM, graf.V);

		fitness(populus, graf.V);
		sort(populus, POPULATION, graf.V);
		for (int i = 0; i < STOP_MOMENT; i++) {
			for (int i = 0; i < (POPULATION / 2); i += 2) {
				cross(populus, graf.V, i, i + 1, ((POPULATION - 1) - (i / 2)));
				clean(graf.tab, populus[((POPULATION - 1) - (i / 2))], graf.V);
			}
			fitness(populus, graf.V);
			sort(populus, POPULATION, graf.V);
			cout << "I = " << i << endl;
		}

		for (int i = 0; i < POPULATION; i++) {
			cout << populus[i][0] << ". ";
			//for (int j = 1; j <= graf.V; j++)
				//cout << populus[i][j] << " ";
			cout << endl;
		}


		delete[] order;
	}

	file.close();

	return 0;
}