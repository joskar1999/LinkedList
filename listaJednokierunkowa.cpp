// listaJednokierunkowa.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <vector>
using namespace std;


struct element
{
	int key;
	element * next;
};


class list
{
private:
	element * head;
	element * tail;
public:
	list()
	{
		head = NULL;
		tail = NULL;
	}

	void insertElement(int x)
	{
		element * tmp = new element;
		tmp->key = x;
		tmp->next = NULL;
		if (head == NULL)
		{
			head = tmp;
			tail = tmp;
			tmp = NULL;
		}
		else if (head->key >= tmp->key)
		{
			tmp->next = head;
			head = tmp;
		}
		else
		{
			element * current = head;
			element * nxt = head->next;
			while (current)
			{
				if (nxt == NULL)
				{
					current->next = tmp;
					tmp->next = NULL;
					break;
				}
				if (nxt->key >= tmp->key)
				{
					current->next = tmp;
					tmp->next = nxt;
					break;
				}
				current = nxt;
				nxt = nxt->next;
			}
		}
	}

	void deleteElement(int x)
	{
		element * current = head;
		element * nxt = head->next;
		if (head->key == x)
		{
			head = head->next;
			delete current;
			return;
		}
		while (current)
		{
			if (nxt->key == x)
			{
				current->next = nxt->next;
				delete nxt;
				break;
			}
			current = nxt;
			nxt = nxt->next;
		}
	}

	void deleteList()
	{
		element * tmp = new element;
		while (head != NULL)
		{
			tmp = head;
			head = head->next;
			delete tmp;
		}
	}

	void displayList()
	{
		element * tmp = new element;
		tmp = head;
		while (tmp)
		{
			cout << tmp->key << "\t";
			tmp = tmp->next;
		}
	}

	element * findElement(int x)
	{
		element * tmp = new element;
		tmp = head;
		while (true)
		{
			if (tmp->key == x) return tmp;
			else tmp = tmp->next;
		}
	}
protected:
};

void randTable(int A[], int size)
{
	int r;
	vector<bool> tab(500000, false);
	for (int i = 0; i < size; i++)
	{
		label:
		r = (rand() * rand()) % 500000;
		if (tab[r] == false)
		{
			tab[r] = true;
			A[i] = r;
		}
		else goto label;
	}
}

int main()
{
	srand(time(NULL));
	int *A;
	int start, stop;
	double time;

	fstream file;
	file.open("wyniki.txt", fstream::in | fstream::out | fstream::app);
	list lista;

	for (int i = 10000; i <= 100000; i += 10000)
	{
		A = new int[i];
		randTable(A, i);
		
		start = clock();
		
		for (int j = 0; j < i; j++)
		{
			lista.insertElement(A[j]);
		}

		stop = clock();
		time = double(stop - start) / CLOCKS_PER_SEC;
		file << "list.insertElement: " << i << " time: " << time << endl;

		start = clock();

		for (int j = 0; j < i/10; j++)
		{
			lista.findElement(A[j]);
		}

		stop = clock();
		time = double(stop - start) / CLOCKS_PER_SEC;
		file << "list.findElement: " << i << " time: " << time << endl;

		start = clock();

		lista.deleteList();

		stop = clock();
		time = double(stop - start) / CLOCKS_PER_SEC;
		file << "list.deleteList: " << i << " time: " << time << endl;

		cout << i << endl;

		delete[] A;
	}
	
	file.close();

	return 0;
}

