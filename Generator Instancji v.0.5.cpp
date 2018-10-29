// Generator Instancji.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>


using namespace std;

int losuj_z_przedziału(int Od, int Do)
{
	int wynik;
	int zm1 = (Do - Od) + 1;

	wynik = (rand() % zm1) + Od;

	return wynik;

}

void make_matrix(int &size, int **tab)
{

	
	for (int i = 0; i < size; i++)
		tab[i] = new int[size];

	for (int i = 1; i <= size; i++)
		for (int j = 1; j < size; j++)
			tab[j][i] = 0;


}

void wypisz_macierz(int &size, int **tab)
{
	for (int i = 1; i < size; i++) {
		for (int j = 1; j < size; j++) {			//Writing the graph's array onto the console
			cout << tab[i][j];
		}
		cout << '\n';
	}
}

//OPIS FUNKCJI
/*Po kolei do każdego wierzchołka dodaje jakąś krawędź. 
Wierchołek poprzedni jest zawsze mniejszy od losowanego.
W ten sposób zapewniamy spójność grafu*/
void wstępne_uzupełnienie_krawędziami(int &V, int **tab)
{
	for (int i = 1; i < (V); i++) //size-1 bo nie ma wierzchołka większego niż ostatni
	{
		
		int drugi_wierzch = losuj_z_przedziału(i+1,V); //drugi wierzchołek > od obecnego i <= największego
		while (drugi_wierzch == i)
			drugi_wierzch = losuj_z_przedziału(i + 1, V);

		tab[i][drugi_wierzch] = 1;
		tab[drugi_wierzch][i] = 1;
	}
}

int main()
{
	srand(time(NULL));

	string nazwa_pliku, buf;
	int V, size, E;
	ofstream file; //otwiera plik do zapisu (kasuje poprzedni jeśli taki istniał)

	//Dane wejściowe - wpisywanie przez uzytkownika:
	////////////////////////////////////////////////
	{
		cout << "Podaj nazwe pliku: ";
		cin >> nazwa_pliku;
		cout << endl;

		cout << "Podaj ilosc wierzcholkow: ";
		cin >> V;
		cout << endl;
		size = V + 1;

		cout << "Podaj ilosc krawedzi: ";
		cin >> E;
		cout << endl;
	}
	////////////////////////////////////////////////


	int **tab = new int*[size];   //tworzy tablicę...
	make_matrix(size, tab);		  //... i ją uzupełnia
	wstępne_uzupełnienie_krawędziami(V, tab);


	wypisz_macierz(size,tab);

	file.open(nazwa_pliku);
	file << V << endl;
	
	for (int i = 1; i <= size; i++)
	{
		for (int j = 1; j <= size; j++)
		{
			if (tab[i][j] == 1 && i<j)
			{
				file << i << " " << j << endl;
			}
		}
	}

	
	cout << "\n\n\n";
	


	delete [] tab;
	file.close();

    return 0;
}

