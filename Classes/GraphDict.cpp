#include "GraphDict.h"
#include<iostream>

GraphDict::GraphDict()
{
	G.start = NULL;
	totalNode = 0;
}

/*set awal gaddag
	mengambil scene yg aktif
	menyiapkan simpul awal (G.start ->'+')
	memasukan semua kata di file ke dalam graf ->ospd.txt
	set kelas papan menginisialisasi papan jadi kosong
	*/
void GraphDict::initGraph()
{
	ifstream file;
	file.open("CSW12.txt");
	string str;
	addSimpul('+');
	while (std::getline(file, str))
	{
		//std::cout<<str<<"\n";
		addWord(str);
	}
	file.close();
}

//menambahkan kata ke graf 
void GraphDict::addWord(string kata)
{

	/*
	*pembuatan graf (tambah kata) berdasarkan algoritma GADDAG
	*delimiter menggunakan karakter "-"
	*/
	node *state = G.start;
	node *forceState;
	int i = 0;
	//int n = strlen(kata);
	int n = kata.length();
	int m;


	//untuk menyusun kata secara terbalik dalam graph sehingga di simpul kata[0] status eow = 1
	for (i = n - 1; i >= 2; i--)
	{
		state = addArc(state, kata[i]);
	}

	state = addFinalArc(state, kata[1], kata[0]);
	//memasukan kata dalam beberapa formasi termasuk delimiter
	state = G.start;
	for (i = n - 2; i >= 0; i--)
	{
		state = addArc(state, kata[i]);
	}
	state = addFinalArc(state, '-', kata[n - 1]);
	for (m = n - 3; m >= 0; m--)
	{
		forceState = state;
		state = G.start;
		for (i = m; i >= 0; i--)
		{
			state = addArc(state, kata[i]);
		}
		state = addArc(state, '-');
		state = forceArc(state, kata[m + 1], forceState);
	}

}

//membuat node yang baru, node sebelum adalah node sebelumnya dari sumber yang sama
void GraphDict::addSimpul(char huruf)
{
	//huruf = toupper(huruf);
	node *baru = new node;
	baru->huruf = huruf;
	baru->next = NULL;
	baru->arc = NULL;
	baru->jmlAnak = 0;
	if (G.start == nullptr)
	{
		baru->prev = NULL;
		G.start = baru;
	}
	else
	{
		node *now = G.start;

		while (now->next != NULL) {
			now = now->next;
		}
		baru->prev = now;
		now->next = baru;
	}
	nodes.push(baru);

}

//menghubungkan node dengan membuat jalur baru, ini digunakan jika ternyata node yang dimaksud sudah ada
void GraphDict::addJalur(node *awal, node *akhir)
{
	if (awal != NULL && akhir != NULL)
	{
		jalur *baru = new jalur;
		baru->nextjalur = NULL;
		baru->tujuan = akhir;
		if (awal->arc == NULL)
		{
			awal->arc = baru;
			awal->jmlAnak++;
		}
		else
		{
			//jika sudah ada jalur sebelumnya di node awal
			int status = 0; // 
			jalur *now = awal->arc;
			//cek apakah sudah ada jalur yang sama atau belum
			if (now->tujuan->huruf == akhir->huruf)
			{
				status = 1;
			}
			while (now->nextjalur != NULL && status == 0)
			{
				//cek apakah sudah ada jalur yang sama atau belum
				if (now->nextjalur->tujuan->huruf == akhir->huruf)
				{
					status = 1;
				}
				else
				{
					now = now->nextjalur;
				}
			}
			if (status == 0)
			{
				now->nextjalur = baru;
				awal->jmlAnak++;
			}
		}
		jalurs.push(baru);

	}
}

node * GraphDict::addArc(node *sebelum, char huruf)
{

	//huruf = toupper(huruf);
	//cek apakah node sebelum sudah pernah memiliki jalur ke huruf tersebut 
	int status = 0;
	jalur *now = sebelum->arc;
	node *state;
	if (now != NULL)
	{
		while (now != NULL && status == 0)
		{
			if (now->tujuan->huruf == huruf)
			{
				//std::cout<<"sudah ada : "<<huruf<<"\n";
				state = now->tujuan;
				status = 1;
			}
			else
			{
				now = now->nextjalur;
			}
		}
	}

	if (status == 0)
	{
		//std::cout<<count<<" belum ada\n";
		node *baru = (node *)malloc(sizeof(node));
		baru->huruf = huruf;
		baru->eow = 0;
		baru->next = NULL;
		baru->arc = NULL;
		baru->jmlAnak = 0;
		//baru->toFile = 0;
		sebelum->next = baru;
		addJalur(sebelum, baru);
		state = baru;
		totalNode++;
	}

	return state;
}

node * GraphDict::addFinalArc(node *sebelum, char pertama, char kedua)
{

	node *state;
	state = addArc(sebelum, pertama);
	state = addArc(state, kedua);
	state->eow = 1;
	return state;
}

node * GraphDict::forceArc(node *sebelum, char huruf, node *forceState)
{
	node *state;
	state = addArc(sebelum, huruf);
	state->next = forceState;
	addJalur(state, forceState);
	return state;
}

node * GraphDict::getRoot()
{
	return G.start;
}

//memastikan apakah yang ditaruh adalah kata atau bukan
bool GraphDict::isWord(string kata)
{
	bool word = false;
	node *now = G.start;
	int stat;
	int stop = 0;
	jalur *jalan;
	int i = kata.length() - 1;
	while (now != NULL && stop == 0)
	{
		if (now->arc != NULL)
		{
			jalan = now->arc;
			stat = 0;


			while (jalan != NULL && stat == 0)
			{

				if (jalan->tujuan->huruf == kata[i])
				{
					if (i == 0)
					{
						if (jalan->tujuan->eow == 1)
						{
							word = true;
						}
						stop = 1;
						stat = 1;
					}
					else
					{
						now = jalan->tujuan;
						i--;
						stat = 1;
					}
				}
				else
				{
					jalan = jalan->nextjalur;
				}
			}
			if (stat == 0)
			{
				stop = 1;
			}
		}
		else
		{
			stop = 1;
		}
	}

	return word;
}


Graph GraphDict::getGraph()
{
	return G;
}

int GraphDict::getTotalNode()
{
	return totalNode;
}

void GraphDict::clearGraph()
{
	while (!nodes.empty())
	{
		node *n = nodes.front();
		nodes.pop();
		delete n;
	}

	while (!jalurs.empty())
	{
		jalur *j = jalurs.front();
		jalurs.pop();
		delete j;
	}
	G.start = NULL;
	totalNode = 0;
}

GraphDict::~GraphDict()
{

}
