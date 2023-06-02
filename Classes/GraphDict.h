#include<string>
#include<stdio.h>
#include<ctype.h>
#include<vector>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <queue>


typedef struct simpul *alamatsimpul;

typedef struct jlr *alamatjalur;

typedef struct jlr
{
	alamatjalur nextjalur;
	alamatsimpul tujuan;
}jalur;

//huruf bisa berupa huruf biasa atau delimiter
typedef struct simpul
{
	char huruf;
	//untuk menandai apakah simpul tersebut membentuk kata atau tidak jika ditelusur dari root
	int eow;
	int jmlAnak; //jumlah jalur yang dimiliki
	//int toFile;
	//jika eow maka disimpan index kata tersebut di file kamus ->keperluan definition
	alamatsimpul next;
	alamatsimpul prev;
	jalur *arc;
}node;

struct Graph
{
	node *start;
};

using namespace std;
class GraphDict
{
	private:
		Graph G;
		int totalNode;
	public:
		GraphDict();
		void initGraph();
		void addWord(string kata);
		void addSimpul(char huruf);
		void addJalur(node * awal, node * akhir);
		node * addArc(node *sebelum, char huruf);
		node * addFinalArc(node * sebelum, char pertama, char kedua);
		node * forceArc(node * sebelum, char huruf, node * forceState);
		node * getRoot();
		queue<node *>nodes;
		queue<jalur *>jalurs;
		bool isWord(string kata);
		Graph getGraph();
		int getTotalNode();
		void clearGraph();
		~GraphDict();
};

