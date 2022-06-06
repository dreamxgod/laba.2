
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define DEBUG

const int MAXSIZE = 20;

class Plural
{
	
public:
	
	Plural();												// Êîíñòðóêòîð áåç ïàðàìåòðîâ äëÿ êëàñó Plural
	Plural(char* array, int size);							// Êîíñòðóêòîð ç ïàðàìåòðàìè äëÿ êëàñó Plural
	Plural(const char* arr);								// Êîíñòðóêòîð ç ïàðàìåòðàìè(ðÿäêîì ñèìâîë³â) äëÿ êëàñó Plural
	Plural(const Plural& exemplar);							// Êîíñòðóêòîð êîï³þâàííÿ
	~Plural();												// Äåñòðóêòîð

	Plural operator* (const Plural& exemplar);				// Ïåðåâàíòàæåííÿ îïåðàòîðà *
	int operator<(const Plural& exemplar);					// Ïåðåâàíòàæåííÿ îïåðàòîðà <
	Plural operator= (const Plural& exemplar);				// Ïåðåâàíòàæåííÿ îïåðàòîðà =
	//friend int operator> (const Plural arr, char symbol);	// Ïåðåâàíòàæåííÿ îïåðàòîðà >
	int operator> (char symbol);
	

	int add(char symbol);									// Ôóíêö³ÿ, ùî äîäàº åëåìåíò â ìíîæèíó
	int sizeIncrease(int demandSize);						// Ôóíêö³ÿ, ùî çá³ëüøóº ìàêñèìàëüíîé ìîæëèâèé ðîçì³ð ìàñèâó òàê, ùîá _maxSize > demandSize 
	int GetCurrentSize();									// Ìåòîä îòðèìàíÿ ðîçì³ðó ìíîæèíè
	int GetMaxSize();										// Ìåòîä îòðèìàíÿ ìàêñèìàëüíîãî ðîçì³ðó ìíîæèíè
	char* ToArray();
	int SetPlural(char* arrayOfChar, int size);				// Ìåòîä, ùî âñòàíîâëþº ìíîæèíó ç ìàñèâó ñèìâîë³â
	int SetPlural(const char* inputArray);					// Ìåòîä, ùî âñòàíîâëþº ìíîæèíó ç ðÿäêà (ìàñèâó ñèìâîë³â ç \0 â ê³íö³)
	
	
	void Print();											// Ìåòîä âèâîäó ìíîæèíè íà åêðàí

private:

	//char* arrayToSet(char* arr, int size);
	int checkMemory(char* arr);					// Ôóíêö³ÿ ïåðåâ³ðêè âèä³ëåííÿ ïàì'ÿò³ 

	char* _arr;
	int _maxSize;
	int _currentSize;
	
};

//#endif