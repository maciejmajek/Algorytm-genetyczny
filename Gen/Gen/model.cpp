#include "model.h"
#include "genetyka.h"
#include <iostream>
#include <ctime>
#include <iomanip>
#include <chrono>
#include <fstream>
using namespace std;
struct Gdata {
	int *popdata;
	int n_of_generation;
	Gdata *next;
};
//
//
void standard(int pop_size, int chrom_size, double xmin, double xmax, int num_of_generations, double chance_of_mutation, double chance_of_crossover, int q, int method)
{
	std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
	//Gdata *dane = new Gdata;
	ofstream output("outpucik.txt");
	int *winner = new int[chrom_size];
	int **tab = new int*[pop_size];
	for (int i = 0; i < pop_size; i++)
	{
		tab[i] = new int[chrom_size];
	}
	init(tab, pop_size, chrom_size);
	double max;
	for (int k = 0; k < num_of_generations; k++)
	{
		int **out = new int*[pop_size];
		for (int i = 0; i < pop_size; i++)
		{
			out[i] = new int[chrom_size];
		}

		mutationAndCrossover(tab, pop_size, chrom_size, chance_of_mutation, chance_of_crossover);
		tournament(tab, out, xmin, xmax, pop_size, chrom_size, q, method, winner);
		copying(out, tab, pop_size, chrom_size);
		for (int i = 0; i < pop_size; i++)
		{
			delete[] out[i];
		}
		delete[] out;
		//Gdata *temp = new Gdata;
		//temp->popdata = winner;
		//temp->n_of_generation = k;
		//temp->next = NULL;
		//dane->next = temp;
		system("cls");
		cout <<"Wykonano "<< double(k+1) / double(num_of_generations)*100<< " procent."<< endl;
	}
	
	for (int i = 0; i < pop_size; i++)
	{
		delete[] tab[i];
	}
	delete[] tab;
	cout << "Zwycieski chromosom" << endl;
	for (int i = 0; i < chrom_size; i++)
	{
		cout << winner[i];
	}
	cout << endl <<
		"f(" <<setprecision(20)
		<< xmin + binToDec(winner, chrom_size, method)*(xmax - xmin) / (pow(2, chrom_size) - 1)
		<< ")" << " = " <<setprecision(20)<< fitness(winner, chrom_size, xmin, xmax, method) 
		<< endl;
	std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
	cout << "Obliczenie ekstremum globalnego funkcji na przedziale [" 
		<< xmin << "," << xmax << "] trwalo " 
		<< std::chrono::duration_cast<std::chrono::seconds>(end - start).count() 
		<< " sekund." << endl << "koniec" << endl;
	
}
