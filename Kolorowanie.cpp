// Kolorowanie.cpp : main project file.

#include "stdafx.h"
#include "iostream"
#include "fstream"
#include "string"

using namespace std;

int GetFirstFreeColor(int *check) {					//checks for the first available color
	int i = 1;
	while (check[i])
		i++;
	return i;
}
void BruteForce(int **t, int *ord, int s) {				
	int* colors = new int[s + 1];
	for (int i = 0; i <= s; i++)
		colors[i] = 0;

	/*
	for (int i = 1; i <= s; i++) {
		for (int j = 1; j <= s; j++) {			//Writing the graph's array onto the console
			cout << t[i][j];
		}
		cout << '\n';
	}
	*/

	for (int i = 0; i < s; i++) {					// i - goes through the order array, j - checks vertice neighbours
		for (int j = 1; j <= s; j++) {
			if (t[ord[i]][j] && (ord[i] != j)) {		//checks if the edge between ord[i] and j vertice exists and if it's not checking an edge (a,a)
				colors[t[j][j]] = 1;					//notes the colors of the "j" vertice
			}
		}
		t[ord[i]][ord[i]] = GetFirstFreeColor(colors);		//pushes the first available color for the "a" vertice onto the [a,a] spot in the array
		for (int i = 0; i <= s; i++)						//resetting the colors array
			colors[i] = 0;												
	}
	for (int i = 1; i <= s; i++) {							//writing the specific vertices' colors onto the console
		cout << t[i][i] << " ";
	}
	cout << endl;

}
int main()
{
	string buf, buf1;
	int V = 0, size = 0;
	ifstream file;
	
	file.open("myciel4.txt");						//Opening the file

	if (file.is_open()){

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
		
		
		int *order = new int[V];
		for (int i = 0; i < V; i++)					//Temporary coloring order array (put permutation generator here)
			order[i] = i + 1;

		BruteForce(tab, order, V);					//Where the magic happens...
	}
	
	

    return 0;
}
