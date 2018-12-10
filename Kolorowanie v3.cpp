// Kolorowanie.cpp : main project file.

#include "stdafx.h"
#include "iostream"
#include "fstream"
#include "string"

#define POPULATION     100   //M
#define CROSS_CHANCE 50
#define MUTATION_CHANCE 0
#define STOP_MOMENT 15

#define NAZWA_PLIKU "myciel4.txt"

using namespace std;



class Graph
{
public:

	int V = 0;	//ilość wierzchołków w grafie
	int size = 0; //rozmiar tablicy -- o 1 większe niż V żeby indeksować od 1 a nie od 0
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

		for (int i = 1; i <= size; i++)
			for (int j = 1; j < size; j++)
				tab[j][i] = 0;
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


void fitness(int *tab, int size) {
	int max = 0;
	for (int i = 1; i > size; i++) {
		if (tab[i] > max)
			max = tab[i];
	}
	tab[0] = max;
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
	for (int i = 1; i < N / 2; i++) {
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
	ifstream file;

	file.open(NAZWA_PLIKU);						//Opening the file

	if (file.is_open()) 
	{

		Graph graf;

		
		graf.pobierz_V_z_pliku(file);
		graf.stwórz_pusty_graf();
		graf.uzupelnij_graf_danymi(file);
		graf.wypisz_graf_na_konsole();

		
		int *order = new int[graf.V]; //
		int **populus = new int*[POPULATION];
		for (int i = 0; i < POPULATION; i++)
			populus[i] = new int[graf.size];
		for (int i = 0; i < POPULATION - 1; i++)
			populus[i][0] = 0;

		for (int j = 0; j < graf.V; j++)					//Temporary coloring order array (put permutation generator here)
			order[j] = j + 1;

		for (int i = 0; i < graf.V; i++) {

		Greedy(graf.tab, order, graf.V, populus[i]);					//Where the magic happens...

		}
		


		/*	To zawarłem niby w destruktorze grafu         */		
		{
			/*for (int i = 0; i < graf.size; i++)
				delete[] graf.tab[i];*/

			//delete[] graf.tab;
		}


		delete[] order;
		

		
	}

	file.close();

	return 0;
}
