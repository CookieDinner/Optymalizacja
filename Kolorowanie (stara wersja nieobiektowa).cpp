// Kolorowanie.cpp : main project file.

#include "stdafx.h"
#include "iostream"
#include "fstream"
#include "string"

using namespace std;

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
		
		for (int i = 1; i < size; i++) {
			for (int j = 1; j < size; j++) {			//Writing the graph's array onto the console
				cout << tab[i][j];
			}
			cout << '\n';	
		}
	}
	

    return 0;
}
