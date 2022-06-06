
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define DEBUG
#include "plural.h"


// Êîíñòðóêòîð áåç ïàðàìåòð³â äëÿ êëàñó Plural
Plural::Plural() {
	_maxSize = MAXSIZE;
	_arr = new char[_maxSize];
	if(!checkMemory(_arr))
	{
		exit(0);
	}
	_currentSize = 0;
	
}


/* Êîíñòðóêòîð ç ïàðàìåòðàìè äëÿ êëàñó Plural.
	Âõ³ä: ïîêàæ÷èê íà ðÿäîê const char* array */
Plural::Plural(const char* array)
{
	this->_maxSize = MAXSIZE;
	int counter = 0;
	if (sizeIncrease(sizeof(array)))
	{
		int i = 0;
		while (array[i] != '\0')
		{
			if (!((Plural)*this > array[i]))
			{
				_arr[counter] = array[i];
				counter++;
			}
			i++;
		}
		this->_currentSize = counter;
	}
	else { exit(0); }
}


/* Êîíñòðóêòîð ç ïàðàìåòðàìè äëÿ êëàñó Plural.
	Âõ³ä: ïîêàæ÷èê íà ìàñèâ ñèìâîë³â char* array, ðîçì³ð ìàñèâó  int size*/
Plural::Plural(char* array, int size)
{
	
	this->_maxSize = MAXSIZE;
	int counter = 0;
	if (sizeIncrease(size))
	{
		for (int i = 0; i < size; i++)
		{
			if (!((Plural)*this > array[i]))
			{
				_arr[counter] = array[i];
				counter++;
			}
		}
		this->_currentSize = counter;
	}
	else { exit(0); }
}


// Êîíñòðóêòîð êîï³þâàííÿ
Plural::Plural(const Plural& exemplar) 
{
	_currentSize = exemplar._currentSize;
	_maxSize = exemplar._maxSize;
	
	_arr = new char[_maxSize];

	if (checkMemory(_arr))
	{
		for (int i = 0; i < _currentSize; i++) 
		{
			if(_arr[i] != NULL) _arr[i] = exemplar._arr[i];
		}
	}
	
}


// Ïåðåâàíòàæåííÿ îïåðàòîðà =
Plural Plural::operator= (const Plural& exemplar)
{
	if (this == &exemplar) return *this;
	
	if (this->sizeIncrease(exemplar._currentSize))
	{
		for (int i = 0; i < exemplar._currentSize; i++)
		{
			this->_arr[i] = exemplar._arr[i];
		}
	}
	else 
	{ 
		exit(0); 
	}
	return *this;
}


// Ìåòîä ïåðåâ³ðêè âèä³ëåííÿ ïàì'ÿò³
int Plural::checkMemory(char* arr)
{
	if (arr != NULL)
	{
		return 1;
	}
	else { return 0; }
}


// Ìåòîä âèâîäó ìíîæèíè íà åêðàí
void Plural::Print() 
{
	for (int i = 0; i < _currentSize; i++)
	{
		printf("%c\t", _arr[i]);
	}
	printf("\n");
}


// Ìåòîä îòðèìàíÿ ðîçì³ðó ìíîæèíè
int Plural::GetCurrentSize() 
{
	return this->_currentSize;
}


// Ìåòîä îòðèìàíÿ ìàêñèìàëüíîãî ðîçì³ðó ìíîæèíè
int Plural::GetMaxSize()
{
	return this->_maxSize;
}


// Ìåòîä îòðèìàííÿ êîï³¿ ìíîæèíè
char* Plural::ToArray() // èç ýòîé ôóíêöèè ïåðåãðóçèòü îïåðàòîðà ïðèñâàèâàíèÿ è âîçâðàùàòü îáúåêò êëàññà Plural
{
	char* pluralCopy; 
	pluralCopy = new char[this->_currentSize];


	if (checkMemory(pluralCopy))
	{
		for (int i = 0; i < _currentSize; i++)
		{
			pluralCopy[i] = this->_arr[i];
		}
		return pluralCopy;
	}
	else 
	{
		return nullptr;
	}
}


// Ìåòîä, ùî âñòàíîâëþº ìíîæèíó ç ìàñèâó ñèìâîë³â
int Plural::SetPlural(char* inputArray, int size)
{
	delete[] _arr;
	_arr = nullptr;
	//_arr = new char[size];

	int counter = 0;
	if (!sizeIncrease(size)) return 0;
	for (int i = 0; i < size; i++)
	{
		if (!((Plural)*this > inputArray[i]))
		{ 
			_arr[counter] = inputArray[i]; 
			counter++;
		}
	} 
	this->_currentSize = counter;
	return 1;
	
}


// Ìåòîä, ùî âñòàíîâëþº ìíîæèíó ç ðÿäêà (ìàñèâó ñèìâîë³â ç \0 â ê³íö³)
int Plural::SetPlural(const char* inputArray)
{
	delete[] _arr;
	_arr = new char[_maxSize];
	int counter = 0;
	if (!sizeIncrease(sizeof(inputArray))) return 0;
	int i = 0;
	while (inputArray[i] != '\0')
	{
		if (!((Plural)*this > inputArray[i]))
		{
			_arr[counter] = inputArray[i];
			counter++;
		}
		i++;
	}
	this->_currentSize = counter;
	return 1;
}


// Ôóíêö³ÿ, ùî äîäàº åëåìåíò â ìíîæèíó
int Plural::add(char symbol)
{
	
	if (!(*this > symbol))
	{
		if (!sizeIncrease(_currentSize + 1)) return 0;
		_arr[_currentSize - 1] = symbol;
	}
	return 1;
}


// Ôóíêö³ÿ, ùî çá³ëüøóº ìàêñèìàëüíîé ìîæëèâèé ðîçì³ð ìàñèâó òàê, ùîá _maxSize > demandSize 
int Plural::sizeIncrease(int demandSize)
{
	if ((_maxSize > demandSize) && (checkMemory(_arr)))
	{
		_currentSize = demandSize;
		return 1; 
	}
	else
	{
		do
		{
			_maxSize += MAXSIZE;
		} while (_maxSize < demandSize);

		if (checkMemory(_arr)) { delete[] _arr; }
		_arr = new char[_maxSize];
		if (!checkMemory(_arr)) return 0;
		_currentSize = demandSize;

	}
	return 1;
	
}
/*
char* Plural::arrayToSet(char* arr, int size)
{
	// [1,2,1,1,3,4,3,2,5] i
	//[1,2,3,4,] j
	char* res;
	res = new char[size];
	res[0] = arr[0];
	
	int counter = 1;
	for (int i = 1; i < size; i++)
	{
		for (int j = 0; j < i; j++)
		{
			if (res[j] == arr[i])
			{
				break;
			}
			else
			{
				if ((i - j == 1) && (res[j] != arr[i]))
				{
					res[counter] = arr[i];
					counter++;
				}
			}
		}
	}
	
	return res;
}
Plural1 < Plural2 == Plural1.oprator<(Plural2)
*/


//Ïåðåâàíòàæåííÿ îïåðàòîðà < (ïåðåâ³ðêà íà ï³äìíîæèíó)
int Plural::operator<(const Plural& exemplar) 
{
	for (int i = 0; i < exemplar._currentSize; i++)
	{
		if (!((Plural)*this > exemplar._arr[i]))
		{ 
			return 0; 
		}
	}
	return 1;
}


//Ïåðåâàíòàæåííÿ îïåðàòîðà * (ïåðåòèí ìíîæèí). Ðåçóëüòàò: ìíîæèíà ñï³ëüíèõ åëåìåíò³â
Plural Plural::operator* (const Plural& exemplar)
{
	Plural* res = new Plural;

	if (exemplar._currentSize > this->_currentSize)
	{
		res->sizeIncrease(exemplar._currentSize);
	}
	else
	{
		res->sizeIncrease(this->_currentSize);
	}


	int counter = 0;


	if (checkMemory(res->_arr)) {
		for (int i = 0; i < exemplar._currentSize; i++)
		{
			for (int j = 0; j < this->_currentSize; j++)
			{
				if ((exemplar._arr[i] == _arr[j]))
				{
					res->_arr[counter] = _arr[j];
					counter++;
					break;
				}
			}
		}
		res->_currentSize = counter;
	}
	else
	{
		exit(0);
	}
	return *res;
}


// Äåñòðóêòîð
Plural::~Plural() 
{
	delete[] _arr;
}


// Ïåðåâàíòàæåííÿ îïåðàòîðà > ÷åðåç äðóæíþ ôóíêö³þ (ïåðåâ³ðêà íà ï³äìíîæèíó)
/*int operator> (const Plural arr, char symbol)
{
	for (int i=0; i < arr._currentSize; i++)
	{
		if (arr._arr[i] == symbol) { return 1; }
	}
	return 0;
}
*/

//Ïåðåâàíòàæåííÿ îïåðàòîðà > (ïåðåâ³ðêà ñèìâîëà íà ïðèíàëåæí³ñòü â ìíîæèí³)

int Plural::operator> (char symbol)
{
	for (int i = 0; i < _currentSize; i++)
	{
		if (_arr[i] == symbol) { return 1; }
	}
	return 0;
}