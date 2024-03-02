#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <map>
#include <set>
#include <list>
#include <iomanip>
using namespace std;

class ManipulareDateFisiere {
public:
	virtual void citeste(string file_name) = 0;
	virtual void scrie(string file_name) = 0; 
	virtual void citesteBinar(fstream& f) = 0;
	virtual void scrieBinar(string nume_fisier_text, fstream& f) = 0;
};

class Stoc : public ManipulareDateFisiere{
private:
	map<string, float> produse_stoc;
	map<string, float> stocInitial;

public:
	Stoc() {};

	//constructor de copiere
	Stoc(Stoc& s)
	{
		if (s.getProduseStoc() > 0) {
			this->produse_stoc = s.getProduse();
		}
	}

	~Stoc() {
	}

	//getteri si setteri

	int getProduseStoc() {
		return produse_stoc.size();
	}

	map<string, float> getProduse() {
		return this->produse_stoc;
	}
	map<string, float> getStocInitial() {
		return this->stocInitial;
	}
	//operator =
	Stoc& operator=(Stoc& s)
	{
		if (this != &s)
		{
			if (s.getProduseStoc() > 0) {
				this->produse_stoc = s.getProduse();
			}
			
		}
		return *this;
	}


	//>> si <<
	friend ostream& operator<<(ostream& out, Stoc& s)
	{
		out << "\nStocul restaurantului ";
		out << "\nNumar produse din stoc: ";
		out << (int)s;
		out << "\nProduse:";
		map<string, float> ::iterator it;
		map<string, float> copie = s.getProduse();
		for (it = copie.begin(); it != copie.end(); it++) {
			out << "\nNume:" << it->first;
			out << ";   Cantitate: " << it->second;
		}
		return out;
	}

	friend istream& operator>>(istream& in, Stoc& s)
	{/*
		cout << "\nNr produse stoc: ";
		in >> s.nrProduseStoc;
		if (s.nrProduseStoc > 0)
		{
			s.numeProduseStoc = new string[s.nrProduseStoc];
			s.cantitateProduseStoc = new int[s.nrProduseStoc];
			cout << "\nIntroduceti produse in stoc.";
			for (int i = 0; i < s.nrProduseStoc; i++)
			{
				cout << "Nume: ";
				in >> s.numeProduseStoc[i];
				cout << "\nCantitate: ";
				in >> s.cantitateProduseStoc[i];
			}
		}
		return in;*/
	}

	explicit operator int()
	{
		return produse_stoc.size();
	}


	bool VerificaStocProdus(string numeProdus, float cantitateCerutaProdus)
	{
		if (this->produse_stoc[numeProdus] >= cantitateCerutaProdus) return true;
		return false;
	}

	bool actualizeazaStoc(string numeProdus, float cantitateComandata) {
		if (cantitateComandata > 0) {
			if (this->produse_stoc[numeProdus] >= cantitateComandata) {
				this->produse_stoc[numeProdus] -= cantitateComandata;
				return true;
			}
		}

		return false;
			
	}

	void scrie(string nume)
	{
		cout << "ceva";
	}

	void citeste(string file_name) { 
		ifstream input(file_name);
		if (input) {
			int nr_produse_fisier;
			input >> nr_produse_fisier;

			for (int i = 0; i < nr_produse_fisier; i++) {
				string nume_produs;
				float cantitate_produs;
				getline(input >> ws, nume_produs, ','); // Citeste numele pana la virgula, ws=whitespace, le ignora
				input >> cantitate_produs;
				this->produse_stoc[nume_produs] = cantitate_produs;
				this->stocInitial[nume_produs] = cantitate_produs;
			}
			input.close();
		}
		else {
			cout << "Eroare la deschiderea fisierului.\n";
		}
	}
    void citesteBinar(fstream& f) {
		int nr_produse_fisier, lg;
		float cantitate;
		string nume_produs;
		f.read((char*)&nr_produse_fisier, sizeof(int));
		for (int i = 0; i < nr_produse_fisier; i++)
		{
			f.read((char*)&lg, sizeof(int));
			char* buffer = new char[lg];
			f.read(buffer, lg);
			nume_produs = buffer;
			delete[] buffer;
			buffer = nullptr;
			f.read((char*)&cantitate, sizeof(int));
			this->produse_stoc[nume_produs] = cantitate;
			this->stocInitial[nume_produs] = cantitate;
		}
	}

	void scrieBinar(string nume_fisier_text,fstream& f)
	{
		ifstream f1(nume_fisier_text);
		int nr_produse_fisier;
		f1 >> nr_produse_fisier;
		f.write((char*)&nr_produse_fisier, sizeof(int));
		f1.ignore();
		for (int i = 0; i < nr_produse_fisier; i++) {
			string nume_produs;
			float cantitate_produs;
			//getline(f1, nume_produs, ','); 
			getline(f1 >> ws, nume_produs, ','); 
			f1 >> cantitate_produs;
			int lg = nume_produs.size() + 1;
			f.write((char*)&lg, sizeof(int));
			f.write(nume_produs.data(), lg);
			f.write((char*)&cantitate_produs, sizeof(float));
		}
		f.close();
	}

};

class Preparat {
private:
	string numePreparat = "";
	vector<pair<string, float>> vector_ingrediente;
	float pret = 0;

public:

	//constructori
	Preparat() {};

	Preparat(string numePreparat)
	{
		if (numePreparat.size() > 0) {
			this->numePreparat = numePreparat;
		}
	}

	Preparat(string numePreparat, float pret)
	{
		if (numePreparat.size() > 0) {
			this->numePreparat = numePreparat;
		}

		if (pret > 0) this->pret = pret;
	}

	//constructor copiere
	Preparat(const Preparat& c) {
		this->numePreparat = c.getNumePreparat();
		this->pret = c.getPret();
		this->vector_ingrediente = c.getListaIngrediente();
	}

	~Preparat() {
	}


	//getteri si setteri

	int getNrIngrediente() const {
		return this->vector_ingrediente.size();
	}
	void setNumePreparat(string numePreparat)
	{
		if (numePreparat.size() > 0) this->numePreparat = numePreparat;
	}
	string getNumePreparat() const {
		return this->numePreparat;
	}

	vector<pair<string, float>> getListaIngrediente() const {
		return this->vector_ingrediente;
	}

	void setPret(float pret) {
		if (pret > 0) this->pret = pret;
	}

	float getPret() const {
		return this->pret;
	}

	//operator =
	Preparat& operator=(const Preparat& c)
	{
		if (this != &c)
		{
			this->numePreparat = c.getNumePreparat();
			this->pret = c.getPret();
			this->vector_ingrediente = c.getListaIngrediente();
		}
		return *this;
	}

	//operator <
	bool operator<(const Preparat& c) const
	{
		if (this != &c)
		{
			return this->getPret() < c.getPret();
		}
		return false;
	}

	//operator ==
	bool operator==(const Preparat& c) const
	{
		int ok = 1;
		if (this != &c)
		{
			if (c.numePreparat != this->numePreparat) { ok = 0; }
			if (c.pret != this->pret) { ok = 0; }
			vector<pair<string, float>> vector_ing_c = c.getListaIngrediente();
			if (ok == 1 && this->vector_ingrediente.size() > 0 && vector_ing_c.size() > 0 && this->vector_ingrediente.size() == vector_ing_c.size())
			{
				for (int i = 0; i < this->vector_ingrediente.size(); i++)
				{
					if (this->vector_ingrediente[i].first != vector_ing_c[i].first) { ok = 0; }
					if (this->vector_ingrediente[i].second != vector_ing_c[i].second) { ok = 0; }
				}
			}
		}
		else {
			return true;
		}
		return ok;
	}

	//operatori >> si <<
	friend ostream& operator<<(ostream& out, Preparat& r)
	{
		out << "\nNume preparat: " << r.numePreparat;
		out << "\nNr ingrediente: " << r.getNrIngrediente();
		out << "\nIngrediente: ";
		vector<pair<string, float>> vector_ing_r = r.getListaIngrediente();
		for (int i = 0; i < r.getNrIngrediente(); i++)
		{
			out << "\n-" << vector_ing_r[i].first << "(" << vector_ing_r[i].second << ")";

		}
		out << "\nPret: " << r.pret;
		return out;
	}

	friend istream& operator>>(istream& in, Preparat& r)
	{/*
		if (r.nrIngrediente == 0)
		{
			cout << "\nNume preparat:";
			in >> r.numePreparat;
			int nr;
			cout << "\nNumar ingrediente: ";
			in >> nr;
			r.ingrediente = new string[nr];
			r.cantitate = new int[nr];
			r.nrIngrediente = nr;
			cout << "\nAdauga ingrediente retata si cantitati: ";
			for (int i = 0; i < nr; i++) {
				cout << "\nIngrediente: ";
				string buffer;
				in >> buffer;
				r.ingrediente[i] = buffer.data();
				cout << "\nCantitate ";
				in >> r.cantitate[i];
			}
			cout << "\nPret: ";
			in >> r.pret;
		}
		return in; */
	}

	//metode

	void adaugaIngredient(string nume, int cantitate) {
		this->vector_ingrediente.push_back(make_pair(nume, cantitate));
	}

	void emptyPreparat() {
		this->vector_ingrediente.clear();
	}


	void descarcaStocPreparat(int cant)
	{
		ofstream f("modificariStoc.txt", std::ios::app);
		f << endl;
		vector<pair<string, float>> vectorIngr = this->getListaIngrediente();
		vector<pair<string, float>>::iterator it;
		for(it= vectorIngr.begin();it!= vectorIngr.end();it++)
		{
			f <<it->first << " -" << it->second * cant << " ";
		}
		f.close();
}

};


class Desert :public Preparat {
private:
	int nivelZahar = 0;
	static int nivelZaharMaximcCopii;
public:
	//constructori
	Desert() :Preparat() {}

	Desert(Preparat p) :Preparat(p) {
	}

	Desert(string numePreparat, int pret, int nivelZahar) :Preparat(numePreparat, pret) {
		if (nivelZahar > 0) this->nivelZahar = nivelZahar;
	}

	Desert(string numePreparat) :Preparat(numePreparat) {}

	Desert(Desert& d) :Preparat(d) { 
		this->nivelZahar = d.nivelZahar;
	}

	//getteri si setteri

	void setNivelZaharMaximcCopii(int nivelZaharMaximcCopii)
	{
		Desert::nivelZaharMaximcCopii = nivelZaharMaximcCopii;
	}
	int getNivelZaharMaximcCopii() {
		return this->nivelZaharMaximcCopii;
	}
	void setNivelZahar(int nivelZahar)
	{
		if (nivelZahar > 0) this->nivelZahar - nivelZahar;
	}
	int getNivelZahar() { return this->nivelZahar; }


	//operatori << si >>
	friend ostream& operator<<(ostream& out, const Desert& d) {
		out << (Preparat&)d;
		if (d.nivelZahar > Desert::nivelZaharMaximcCopii) {
			cout << "Acest desert nu este recomandat copiilor!";
		}
		out << "Nivel zahar: " << d.nivelZahar << ".";
		return out;
	}


	// operator =
	Desert& operator=(const Desert& d) {
		if (this != &d)
		{
			this->Preparat::operator=(d);
			this->nivelZahar = d.nivelZahar;
		}
		return *this;
	}

	bool InterzisCopiilor()
	{
		return(this->nivelZahar < nivelZaharMaximcCopii);
	}
};
int Desert::nivelZaharMaximcCopii = 20;



class FelPrincipal :public Preparat {
private:
	int nrPortii = 0;
	static int nrMediuPortii;
public:
	//constructori
	FelPrincipal() :Preparat() {}

	FelPrincipal(Preparat p,  int nrPortii) :Preparat(p) {
		if (nrPortii > 0) this->nrPortii = nrPortii;
	}

	FelPrincipal(string numePreparat, float pret, int nrPortii) :Preparat(numePreparat, pret) {
		if (nrPortii > 0) this->nrPortii = nrPortii;
	}

	FelPrincipal(string numePreparat) :Preparat(numePreparat) {
	}

	FelPrincipal(const FelPrincipal& fp) :Preparat(fp)
	{
		this->nrPortii = fp.nrPortii;
	}

	//getteri si setteri


	void setNrPortii(int nrPortii)
	{
		if (nrPortii > 0) this->nrPortii = nrPortii;
	}
	int getNrPortii() {
		return this->nrPortii;
	}


	//<< si >> (nu am testat istream-ul, dar vreau tare sa fac un fisier de unde sa preiau si unde sa pun datele)
	friend ostream& operator<<(ostream& out, FelPrincipal& fp) {

		out << (Preparat&)fp;
		out << "\nNumar portii: " << fp.nrPortii << ".";
		if (fp.nrPortii > FelPrincipal::nrMediuPortii) {
			cout << " Nu se recomanda copiilor, cantitate mare de mancare.";
		}
		return out;
	}

	//operator =
	FelPrincipal& operator=(const FelPrincipal& fp) {
		if (this != &fp)
		{
			this->Preparat::operator=(fp);
			this->nrPortii = fp.nrPortii;
		}
		return *this;
	}

};

int FelPrincipal::nrMediuPortii = 3;


class Comanda {
private:
	list <pair<Preparat, int>> preparateComanda;
public:
	Comanda() {}

	~Comanda() {}

	Comanda(const Comanda& c) {
		if (c.preparateComanda.size() > 0)
			this->preparateComanda = c.preparateComanda;
	}

	list <pair<Preparat, int>> getPreparateComanda() {
		return this->preparateComanda;
	}

	int getNrPreparate() {
		return this->preparateComanda.size();
	}

	Comanda operator=(const Comanda& c) {
		if (this != &c)
		{
			if (c.preparateComanda.size() > 0)
				this->preparateComanda = c.preparateComanda;
		}
		return *this;
	}

	friend ostream& operator<<(ostream& out, Comanda& c)
	{
		if (c.getNrPreparate())
		{
			out << "\n******************";
			out << "\nComanda ta contine: " << endl;
			list<pair<Preparat, int>>::iterator it;
			list<pair<Preparat, int>> copie = c.getPreparateComanda();
			for (it = copie.begin(); it != copie.end(); it++) {
				out << "\n" << it->first.getNumePreparat() << " x " << it->second << " = " << it->first.getPret() * it->second << "lei.";
			}
			out << "\nPret total:" << c.pretTotal();
			out << "\n******************";
		}
		return out;
	}

	void adaugaPreparat(const Preparat& preparat, int cantitate) {
		auto gasit = find_if(preparateComanda.begin(), preparateComanda.end(),
			[&](const pair<Preparat, int>& pereche) {
				return pereche.first == preparat;
			});
		if (gasit != preparateComanda.end()) {
			gasit->second += cantitate;
		}
		else {
			preparateComanda.push_back(make_pair(preparat, cantitate));
		}
	}

	void scrieText(fstream& f, Comanda& c)
	{
		list<pair<Preparat, int>>::iterator it;
		list<pair<Preparat, int>> copie = c.getPreparateComanda();
		for (it = copie.begin(); it != copie.end(); it++) {
			f << it->first.getNumePreparat() <<" "<< it->second<<" ";
		}
		f << c.pretTotal() << endl;
		f.close();
	}
	void reseteaza(Comanda& c)
	{
		c.preparateComanda.clear();
	}
	float pretTotal() {
		float pretTotal = 0;
		for (auto it = preparateComanda.begin(); it != preparateComanda.end(); it++) {
			pretTotal += it->first.getPret() * it->second;
		}
		return pretTotal;
	}
};


class Meniu :public ManipulareDateFisiere {
private:
	set<FelPrincipal> feluriPrincipale;
	set<Desert> deserturi;
	Comanda comanda;
	int ComandaInCurs = -1;
	Stoc stoc;
	map<string, int> topPreparate;
	vector<pair<int,int>> topComenzi;

public:
	Meniu(int argc, char* argv[]) {
		if (argc == 3) {
			stoc.citeste(argv[1]);
			cout << argv[1];
			fstream file1("stoc.bin", ios::out | ios::binary);
			stoc.scrieBinar(argv[1], file1);
			cout << "\nDatele au fost preluate din fisier txt si salvate in fisier binar.";
			file1.close();
			this->citeste(argv[2]);
			fstream file2("preparate.bin", ios::out | ios::binary);
			this->scrieBinar(argv[2], file2);
			file2.close();
		}
		else if (argc == 1)
		{
			fstream file1("stoc.bin", ios::in | ios::binary);
			stoc.citesteBinar(file1);
			cout << "\nDatele au fost preluate din fisier binar.";
			file1.close();

			fstream file2("preparate.bin", ios::in | ios::binary);
			this->citesteBinar(file2);
			file2.close();
		}
	}

	void citeste(string file_name) {

		//initializam Feluri Principale
		ifstream f(file_name);
		if (f) { // verific daca fisierul poate fi deschis
			int nr_feluri_principale;
			f >> nr_feluri_principale;
			if (nr_feluri_principale > 0) {
				for (int i = 0; i < nr_feluri_principale; i++) {
					string denumire;
					float pret;
					int nr_ingrediente;
					int nrPortii;
					f >> denumire >> pret >> nr_ingrediente >> nrPortii;

					FelPrincipal fp(denumire, pret, nrPortii);

					for (int j = 0; j < nr_ingrediente; j++) {
						string ingredient;
						int cantitate;
						f >> ingredient >> cantitate;
						fp.adaugaIngredient(ingredient, cantitate);
					}

					this->feluriPrincipale.insert(fp);
				}
			}
			//initializam Deserturi
			int nr_deserturi;
			f >> nr_deserturi;
			if (nr_deserturi > 0) {
				for (int i = 0; i < nr_deserturi; i++) {
					string denumire;
					float pret;
					int nr_ingrediente;
					int nivelZahar;
					f >> denumire >> pret >> nr_ingrediente >> nivelZahar;

					Desert d(denumire, pret, nivelZahar);

					for (int j = 0; j < nr_ingrediente; j++) {
						string ingredient;
						int cantitate;
						f >> ingredient >> cantitate;
						d.adaugaIngredient(ingredient, cantitate);
					}

					this->deserturi.insert(d);
				}
			}
		}
		else {
			cout << "\n Fisierul nu poate fi deschis";
		}
		f.close();

	}

	void scrie(string file_name) {

	}

	void citesteBinar(fstream& f) {
		int nr_feluri_principale;
		f.read((char*)&nr_feluri_principale, sizeof(int));
		for (int i = 0; i < nr_feluri_principale; i++) {
			int lg;
			string nume_preparat;
			f.read((char*)&lg, sizeof(int));
			char* buffer = new char[lg];
			f.read(buffer, lg);
			nume_preparat = buffer;
			delete[] buffer;
			buffer = nullptr;
			float pret_produs;
			f.read((char*)&pret_produs, sizeof(float));
			int nr_igrediente;
			f.read((char*)&nr_igrediente, sizeof(int));
			int nr_portii;
			f.read((char*)&nr_portii, sizeof(int));

			FelPrincipal fp(nume_preparat, pret_produs, nr_portii);

			for (int j = 0; j < nr_igrediente; j++)
			{
				string nume_ingredient;
				int n;
				f.read((char*)&n, sizeof(int));
				char* buffer = new char[n];
				f.read(buffer, n);
				nume_ingredient = buffer;
				delete[] buffer;
				buffer = nullptr;
				float cantitate_ingredient;
				f.read((char*)&cantitate_ingredient, sizeof(int));

				fp.adaugaIngredient(nume_ingredient, cantitate_ingredient);
			}

			this->feluriPrincipale.insert(fp);
		}

		int nr_deserturi;
		f.read((char*)&nr_deserturi, sizeof(int));

		for (int i = 0; i < nr_deserturi; i++) {
			int lg;
			string nume_preparat;
			f.read((char*)&lg, sizeof(int));
			char* buffer = new char[lg];
			f.read(buffer, lg);
			nume_preparat = buffer;
			delete[] buffer;
			buffer = nullptr;
			float pret_produs;
			f.read((char*)&pret_produs, sizeof(float));
			int nr_igrediente;
			f.read((char*)&nr_igrediente, sizeof(int));
			int nivel_zahar;
			f.read((char*)&nivel_zahar, sizeof(int));

			Desert d(nume_preparat, pret_produs, nivel_zahar);

			for (int j = 0; j < nr_igrediente; j++)
			{
				string nume_ingredient;
				int n;
				f.read((char*)&n, sizeof(int));
				char* buffer = new char[n];
				f.read(buffer, n);
				nume_ingredient = buffer;
				delete[] buffer;
				buffer = nullptr;
				float cantitate_ingredient;
				f.read((char*)&cantitate_ingredient, sizeof(int));

				d.adaugaIngredient(nume_ingredient, cantitate_ingredient);
			}

			this->deserturi.insert(d);
		}
	}

	void scrieBinar(string nume_fisier_text, fstream& f)
	{
		ifstream f1(nume_fisier_text);
		//scriem feluri principale
		int nr_feluri_principale;
		f1 >> nr_feluri_principale;
		f.write((char*)&nr_feluri_principale, sizeof(int));
		for (int i = 0; i < nr_feluri_principale; i++) {
			string nume_preparat;
			getline(f1 >> ws, nume_preparat, ' '); // Citeste numele pana la virgula, ws=whitespace, le ignora 
			int lg = nume_preparat.size() + 1;
			f.write((char*)&lg, sizeof(int));
			f.write(nume_preparat.data(), lg);
			float pret_produs;
			f1 >> pret_produs;
			f.write((char*)&pret_produs, sizeof(float));
			int nr_igrediente;
			f1 >> nr_igrediente;
			f.write((char*)&nr_igrediente, sizeof(int));
			int nr_portii;
			f1 >> nr_portii;
			f.write((char*)&nr_portii, sizeof(int));
			for (int j = 0; j < nr_igrediente; j++)
			{
				string nume_ingredient;
				getline(f1 >> ws, nume_ingredient, ' ');
				int n = nume_ingredient.size() + 1;
				f.write((char*)&n, sizeof(int));
				f.write(nume_ingredient.data(), n);
				float cantitate_ingredient;
				f1 >> cantitate_ingredient;
				f.write((char*)&cantitate_ingredient, sizeof(int));
			}
		}

		//scriem deserturi
		int nr_deserturi;
		f1 >> nr_deserturi;
		f.write((char*)&nr_deserturi, sizeof(int));
		for (int i = 0; i < nr_deserturi; i++) {
			string nume_preparat;
			getline(f1 >> ws, nume_preparat, ' ');
			int lg = nume_preparat.size() + 1;
			f.write((char*)&lg, sizeof(int));
			f.write(nume_preparat.data(), lg);
			float pret_produs;
			f1 >> pret_produs;
			f.write((char*)&pret_produs, sizeof(float));
			int nr_igrediente;
			f1 >> nr_igrediente;
			f.write((char*)&nr_igrediente, sizeof(int));
			int nivel_zahar;
			f1 >> nivel_zahar;
			f.write((char*)&nivel_zahar, sizeof(int));
			for (int j = 0; j < nr_igrediente; j++)
			{
				string nume_ingredient;
				getline(f1 >> ws, nume_ingredient, ' ');
				int n = nume_ingredient.size() + 1;
				f.write((char*)&n, sizeof(int));
				f.write(nume_ingredient.data(), n);
				float cantitate_ingredient;
				f1 >> cantitate_ingredient;
				f.write((char*)&cantitate_ingredient, sizeof(int));
			}
		}
		f.close();
	}


	//getteri si setteri
	set<FelPrincipal> getFeluriPrincipale() {
		return this->feluriPrincipale;
	}

	int getNrFeluriPrincipale() {
		return this->feluriPrincipale.size();
	}

	set<Desert> getDeserturi() {
		return this->deserturi;
	}

	int getNrDeserturi() {
		return this->deserturi.size();
	}

	//operatori
	friend ostream& operator<<(ostream& out, Meniu& m)
	{
		out << "                 <<<<<<  MENIU  >>>>>>";
		out << "\n\n---Feluri Principale---";
		set<FelPrincipal> copie_fp = m.getFeluriPrincipale();
		if (copie_fp.size() > 0) {
			int i = 0;
			for (set<FelPrincipal>::iterator it = copie_fp.begin(); it != copie_fp.end(); it++) {
				out << "\n" << ++i << ". " << (*it).getNumePreparat() << " - " << (*it).getPret() << " lei.";
			}
		}

		out << "\n\n---Deserturi---";
		set<Desert> copie_d = m.getDeserturi();
		if (copie_d.size() > 0) {
			int j = 0;
			for (set<Desert>::iterator it = copie_d.begin(); it != copie_d.end(); it++) {
				out << "\n" << ++j << ". " << (*it).getNumePreparat() << " - " << (*it).getPret() << " lei.";
			}
		}


		return out;
	}

	void startTopPreparate(map<string,int> &topPreparate)
	{
		ifstream f("preparate.txt");
		int nrFeluriPrincipale;
		f>>nrFeluriPrincipale;
		f.ignore(numeric_limits<streamsize>::max(), '\n');
		for (int i = 0;i < nrFeluriPrincipale;i++)
		{
			string nume;
			f >> nume;
			topPreparate[nume] = 0;
			f.ignore(numeric_limits<streamsize>::max(), '\n');
		}
		int nrDeserturi;
		f >> nrDeserturi;
		f.ignore(numeric_limits<streamsize>::max(), '\n');
		for (int i = 0;i < nrDeserturi;i++)
		{
			string nume;
			f >> nume;
			topPreparate[nume] = 0;
			f.ignore(numeric_limits<streamsize>::max(), '\n');
		}
	}
	void adaugaInTopPreparate(Comanda comanda)
	{
		list<pair<Preparat, int>>::iterator it;
		list<pair<Preparat, int>> copie = comanda.getPreparateComanda();
		for (it = copie.begin(); it != copie.end(); it++)
		{
			string nume = it->first.getNumePreparat();
			this->topPreparate[nume] += it->second;
		}
	}
	bool comparatorDescrescator(const pair<string, int>& a, const pair<string, int>& b) {
		if (a.second != b.second) {
			return a.second > b.second;
		}
		return a.first < b.first;
	}
	void afiseazaTopPreparate(map<string,int> &topPreparate)
	{
		vector<pair<string, int>> vectorPerechi(topPreparate.begin(), topPreparate.end());
		vector<pair<string, int>>::iterator it;
		for (int i = 0; i < vectorPerechi.size() - 1; ++i) {
			for (int j = i + 1; j < vectorPerechi.size(); ++j) {
				if (comparatorDescrescator(vectorPerechi[j], vectorPerechi[i])) {
					swap(vectorPerechi[i], vectorPerechi[j]);
				}
			}
		}
		for (const auto& pair : vectorPerechi) {
			cout <<left<<setw(10) << pair.first << left<<setw(6) << pair.second <<endl;
		}
	}
	
	void startMeniu(Meniu& meniu) {

		void comenziClienti(); {
			ofstream f("comenzi_clienti.txt");
			f << 0<<endl;
			f.close();
		}
		void clearIstoricComenzi(); {
			ofstream f("istoricComenzi.txt", std::ios::out);
			if (!f.is_open()) {
				cout << "\nFisierul nu poate fi deschis.";
			}
			else
				f << left << setw(10)<<"COMANDA"<< left << setw(15)<<"PREPARAT"<< left << setw(10)<<"CANTITATE"<<endl;
			f.close();
		}
		void clearDescarcariStoc(); {
			ofstream f("modificariStoc.txt", std::ios::out);
			if (!f.is_open()) {
				cout << "\nFisierul nu poate fi deschis.";
			}
			else f.close();
		}
		//stoc.creareRaportStoc();
		startTopPreparate(topPreparate);

		while (1 == 1) {
			afisareComenziDisponibile();
			char cmd[50];
			int cmd_ok = 0;
			cout << "\n\nTastati:"; cin.getline(cmd, 50);

			//comenzi ce contin un singut cuvant

			if (!strcmp(cmd, "MENIU")) {
				cmd_ok = 1;
				initHeader();
				cout << meniu;
				adaugaComndaInIstoric(cmd);
			}
			if (!strcmp(cmd, "END_CMD"))
			{
				cmd_ok = 1;
				initHeader();
				if (comanda.getNrPreparate() > 0)
				{
					cout << comanda;
					ComandaInCurs = -1;
					cout << "\nVa multumim pentru comanda!";
					list<pair<Preparat, int>>::iterator it;
					list<pair<Preparat, int>> copie = comanda.getPreparateComanda();
					for (it = copie.begin(); it != copie.end(); it++)
						it->first.descarcaStocPreparat(it->second);
					int id = inregistreazaComanda();
					int pret = static_cast<int>(comanda.pretTotal());
					topComenzi.push_back(make_pair(id, pret));
					adaugaInTopPreparate(comanda);
					comanda.reseteaza(comanda);
					adaugaComndaInIstoric(cmd);
				}
				else cout << "\nVa rugam sa intorduceti preparate in comanda inainte de plasarea acesteia.";
			}

			//comenzi ce contin cel putin doua cuvinte

			char* token = strtok(cmd, " ");

			if (!strcmp(token, "MORE")) {
				cmd_ok = 1;
				initHeader();
				string copy = token;
				token = strtok(NULL, " ");
				if (token != NULL) {
					Preparat result(searchPreparat(token));
					if (result.getNumePreparat() != "") {
						cout << result;
						adaugaComndaInIstoric(copy, token);
					}
					else
						cout << "\nAcest preparat nu se afla in meniu.";
				}
			}

			if (!strcmp(token, "RAPOARTE"))
			{
				cmd_ok = 1;
				adaugaComndaInIstoric(token);
				system("CLS");
				cout << "\nPuteti accesa urmatoarele raporte:";
				cout << "\nHISTORY      COMMANDS      STOC";
				cout << "\nRaport: ";
				char rap[50];
				cin.getline(rap, 50);
				if (rap != NULL) {
					int ok = 0;
					if (!strcmp(rap, "HISTORY"))
					{
						ok = 1;
						adaugaComndaInIstoric(rap);
						system("CLS");
						cout << "                     ISTORIC COMENZI TASTATURA                \n\n";
						afiseazaIstoricComenzi();
					}
					if (!strcmp(rap, "COMMANDS"))
					{
						ok = 1;
						system("CLS");
						adaugaComndaInIstoric(rap);
						cout << "                       COMENZI CLIENTI                        \n\n"; 
						afiseazaComenziClienti();
					}
					if (!strcmp(rap, "STOC"))
					{
						ok = 1;
						adaugaComndaInIstoric(rap);
						cout << "                      MODIFICARI STOC                         \n\n";
						afisareRaportStoc();
					}
					if (ok == 0) cout << "\nNu dispunem de acest raport momentan.";
				}
			}
			if (!strcmp(token, "TOPURI"))
			{
				cmd_ok = 1;
				adaugaComndaInIstoric(token);
				system("CLS");
				cout << "\nPuteti accesa urmatoarele topuri:\n";
				cout << "\PREPARATE     COMENZI";
				cout << "\nTop dorit: ";
				char rap[50];
				cin.getline(rap, 50);
				if (rap != NULL) {
					int ok = 0;
					if (!strcmp(rap, "PREPARATE"))
					{
						ok = 1;
						adaugaComndaInIstoric(rap);
						system("CLS");
						cout << "                     TOP CELE MAI COMANDATE PREPARATE                \n\n";
						cout << left << setw(10) << "PREPARAT" << left << setw(6) << "NUMAR" << endl;
						afiseazaTopPreparate(topPreparate);
					}
					if (!strcmp(rap, "COMENZI"))
					{
						ok = 1;
						adaugaComndaInIstoric(rap);
						system("CLS");
						cout << "                     TOP VALORI COMENZI                \n\n";
						afiseazaTopComenzi(topComenzi);
					}
					if (ok == 0) cout << "\nNu dispunem de acest raport momentan.";
				}
			}

			if (!strcmp(token, "CMD")) {
				cmd_ok = 1;
				string copy = token;
				initHeader();
				ComandaInCurs = 1;
				token = strtok(NULL, " ");
				if (token != NULL) {
					string preparat = token;
					token = strtok(NULL, " ");
					if (token != NULL) {
						string str_cant = token;
						if (str_cant.find_first_not_of("0123456789") == string::npos) {
							adaugaComndaInIstoric(copy, preparat, stoi(str_cant));
							Preparat result = searchPreparat(preparat.c_str());
							if (result.getNumePreparat() != "") {
								if (verificaStocPreparat(result, stoi(str_cant)))
								{
									comanda.adaugaPreparat(result, stoi(str_cant));
									cout << "\nPreparat adaugat in comanda cu succes.";
									actualizeazaStocPreparat(result, stoi(str_cant));
								}
								else cout << "\nUps, nu avem destul stoc pentru acest preparat.";
							}
							else {
								cout << "\nAcest preparat nu se afla in meniu.";
							}

						}
						else {
							cout << "\nTe rog sa introduci un numar intreg pentru cantitate.";
						}
					}
					else {
						cout << "\nTe rog sa introduci un numar intreg pentru cantitate.";
					}
				}
				else {
					cout << "\nTe rog sa introduci denumirea preparatului si un numar intreg pentru cantitate.";
				}
			}

			if (!cmd_ok) {
				initHeader();
				cout << "\nIntroduceti o comanda valida!";
				afisareComenziDisponibile();
			}

			cout << comanda;
		}
	}

	void afisareComenziDisponibile() {
		cout << "\n\nTastati una din urmatoarele comenzi:";
		cout << "\nMENIU                                          MORE [nume_preparat]";
		cout << "\nCMD [nume_preparat] [cantitatea]               END_CMD ";
		cout << "\nRAPOARTE                                       TOPURI";
	}

	void initHeader() {
		system("CLS");
		cout << "\nBine ati venit la restaurantul nostu!\n\n\n";
	}

	Preparat searchPreparat(const char* denumire) {

		auto it = find_if(feluriPrincipale.begin(), feluriPrincipale.end(),
			[denumire](const FelPrincipal& fel) {
				return fel.getNumePreparat() == denumire;
			});

		if (it != feluriPrincipale.end()) {
			return *it;
		}

		auto it2 = find_if(deserturi.begin(), deserturi.end(),
			[denumire](const Desert& bun) {
				return bun.getNumePreparat() == denumire;
			});

		if (it2 != deserturi.end()) {
			return *it2;
		}

		return Preparat();
	}
	bool verificaStocPreparat(Preparat&  p, int cant)
	{
		vector<pair<string, float>> vector_ingrediente = p.getListaIngrediente();
		vector<pair<string, float>>::iterator it;
		for (it = vector_ingrediente.begin();it != vector_ingrediente.end();it++)
		{
			if (!stoc.VerificaStocProdus(it->first, cant * it->second))
			{
				return 0;
			}
		}
		return 1;
	}
	void actualizeazaStocPreparat(Preparat& p, int cant) {
		vector<pair<string, float>> vector_ingrediente = p.getListaIngrediente();
		vector<pair<string, float>>::iterator it;
		for (it = vector_ingrediente.begin();it != vector_ingrediente.end();it++)
			stoc.actualizeazaStoc(it->first, cant * it->second);
	}

	//pentru raportul comenzilor inregistrate
	int incrementeazaIdComanda()
	{
		fstream f("comenzi_clienti.txt");
		int id;
		f >> id;
		f.seekp(0);
		f << ++id;
		f.close();
		return id;
	}
	int inregistreazaComanda()
	{
		int id = incrementeazaIdComanda();
		fstream f("comenzi_clienti.txt", std::ios::app);
		f << id << " ";
		comanda.scrieText(f, comanda);
		f.close();
		return id;
	}
	void afiseazaComenziClienti() {
		ifstream f("comenzi_clienti.txt");
		char linie[3];
		f.getline(linie,3);
		int nr;
		nr = stoi(linie);
		cout << "\nNumar comenzi inregistrate: " << nr<<endl;
		while(nr)
		{
			char linie[100];
			f.getline(linie,100);
			char* token = strtok(linie, " ");
			int index;
			index = stoi(token);
			cout<<endl<< index << ".";
			//aici inserez primul ingredient din comanda 
			char* denumire = strtok(NULL, " ");
			char* cantitate = strtok(NULL, " ");
			while (cantitate!=nullptr)
			{
				cout << denumire << " " << stoi(cantitate)<<" ";
				denumire = strtok(NULL, " ");
				cantitate = strtok(NULL, " ");
			}
			cout << "pret:";
			if (denumire != nullptr) {
				int pret = stoi(denumire);
				cout << pret;
			}
			else cout<<"-";
			nr--;
		}
		f.close();
	}
	bool comparatorDescrescator(const pair<int, int>& a, const pair<int, int>& b) {
		if (a.second != b.second) {
			return a.second > b.second;
		}
		return a.first < b.first;
	}
	void afiseazaTopComenzi(vector<pair<int,int>> &topComenzi)
	{
		int min = topComenzi[0].second;
		int max= topComenzi[0].second;
		int sum = 0;
		cout << left << setw(5) << "ID" << left << setw(8) << "Valoare" << endl;
		for (int i = 0; i < topComenzi.size() - 1; ++i) {
			for (int j = i + 1; j < topComenzi.size(); ++j) {
				if (comparatorDescrescator(topComenzi[j], topComenzi[i])) {
					swap(topComenzi[i], topComenzi[j]);
				}
			}
		}
		for (int i = 0; i < topComenzi.size(); ++i) {
			if (topComenzi[i].second < min) min = topComenzi[i].second;
			if (topComenzi[i].second > max) max = topComenzi[i].second;
			sum += topComenzi[i].second;
		}
		for (const auto& pair : topComenzi) {
			cout << left << setw(5) << pair.first << left << setw(8) << pair.second <<" lei"<<endl;
		}
		cout << "\nValoare maxima: " << max << " lei";
		cout << "\nValoare minima: " << min << " lei";
		cout << "\nValoarea comenzilor: " << sum << " lei";
		cout << "\nValoare medie comenzi: " << sum / topComenzi.size() << " lei";
	}

	
	//raport comenzi tastatura 
	//sa fi facut adaugaComandaInIstoric fct virtuala?
	void adaugaComndaInIstoric(string cmd, string preparat, int cant) {
		fstream f("istoricComenzi.txt", std::ios::app);
		f << left << setw(10) << cmd <<left << setw(15) << preparat << left << setw(10) << cant << endl;
	}
	void adaugaComndaInIstoric(string cmd) {
		fstream f("istoricComenzi.txt", std::ios::app);
		f << cmd << endl;

	}
	void adaugaComndaInIstoric(string cmd, string preparat) {
		fstream f("istoricComenzi.txt", std::ios::app);
		f << left << setw(10) << cmd <<left<<setw(15) << preparat << endl;
	}
	void afiseazaIstoricComenzi() {
		ifstream f("istoricComenzi.txt");
		char header[100];
		f.getline(header, 100);
		char* token = strtok(header, " ");
		string header1 = token;
		token = strtok(NULL, " ");
		string header2 = token;
		token = strtok(NULL, " ");
		string header3 = token;
		cout << left << setw(10) << header1 << left << setw(15) << header2 << left << setw(10) << header3 << endl;
		char cmd[50];
		while (f.getline(cmd, 50)) {
			char* token = strtok(cmd, " ");
			string command = token;
			token = strtok(NULL, " ");
			if (token != NULL) {
				string preparat = token;
				token = strtok(NULL, " ");
				if (token != NULL)
				{
					int cantitate = stoi(token);
					cout <<endl<< left << setw(10) <<command << left << setw(15) << preparat << left << setw(10) << cantitate;
				}
				else {
					string cantitate = " - ";
					cout << endl << left << setw(10) << command << left << setw(15) << preparat << left << setw(10) << cantitate;
				}

			}
			else {
				string preparat = "-";
				string cantitate = " - ";
				cout << endl << left << setw(10) << command << left << setw(15) << preparat << left << setw(10) << cantitate;
			}
		}
		f.close();
	};

	//raport stoc
	vector<float> getVectorModificari(string nume)
	{
		ifstream f("modificariStoc.txt");
		vector<float> modif;
		char linie[100];
		f.getline(linie, 100);
		while (f.getline(linie, 100))
		{
			char* token;
			token = strtok(linie, " ");
			char* numeGasit = token;
			token = strtok(NULL, " ");
			char* cant = token;
			bool gasit = 0;
			while (numeGasit!=nullptr&&gasit==0)
			{
					if (strcmp(numeGasit, nume.c_str()) == 0) {
						gasit = 1;
						modif.push_back(stof(cant));
					}
					else {
						numeGasit = strtok(NULL, " ");
						cant = strtok(NULL, " ");
					}
			}
		}
		f.close();
		return modif;
	}
	void afisareRaportStoc() {
		cout << left << setw(15) << "Produs" << left << setw(8) << "Initial" << left << setw(30) << "Modificari" << left << setw(6) << "Ramas";
		map<string, float> produseStoc = this->stoc.getStocInitial();//aici ii dau stocul modificat
		map<string, float> ::iterator it;
		map<string, vector<float>> vectorModificari;

		for (it = produseStoc.begin(); it != produseStoc.end(); it++) {
			vectorModificari[it->first] = getVectorModificari(it->first);
		}
		for (it = produseStoc.begin(); it != produseStoc.end(); it++) {
			cout << endl << left << setw(15) << it->first << left << setw(8) << it->second;
			vector<float>::iterator it2;
			if (vectorModificari[it->first].empty()) {
				cout << left << setw(30) << " - ";
			}
			else {
				cout << left << setw(30);
				char vectorString[30];
				vectorString[0] = '\0';
				for (it2 = vectorModificari[it->first].begin(); it2 != vectorModificari[it->first].end(); it2++) {
					string tempStr =to_string(static_cast<int>(*it2));
					it->second += *it2;
					strcat(vectorString, tempStr.c_str());
					strcat(vectorString, " ");
				}
				cout << vectorString;
			}
			cout << left << setw(6) << "|" << it->second;
		}
	}

	void writeToFile(fstream& f) {

		ifstream f1("Stoc.txt");
		int nr_produse_fisier;
		f1 >> nr_produse_fisier;
		f.write((char*)&nr_produse_fisier, sizeof(int));
		for (int i = 0; i < nr_produse_fisier; i++) {
			string nume_produs;
			float cantitate_produs;
			getline(f1 >> ws, nume_produs, ','); // Citeste numele pana la virgula, ws=whitespace, le ignora 
			f1 >> cantitate_produs;
			int lg = nume_produs.size() + 1;
			f.write((char*)&lg, sizeof(int));
			f.write(nume_produs.data(), lg);
			f.write((char*)&cantitate_produs, sizeof(int));
		}
		f.close();
	}	

	void writeToFile2(fstream& f)
	{
		ifstream f1("preparate.txt");
		//scriem feluri principale
		int nr_feluri_principale;
		f1 >> nr_feluri_principale;
		f.write((char*)&nr_feluri_principale, sizeof(int));
		for (int i = 0; i < nr_feluri_principale; i++) {
			string nume_preparat;
			getline(f1 >> ws, nume_preparat, ' '); // Citeste numele pana la virgula, ws=whitespace, le ignora 
			int lg = nume_preparat.size() + 1;
			f.write((char*)&lg, sizeof(int));
			f.write(nume_preparat.data(), lg);
			float pret_produs;
			f1 >> pret_produs;
			f.write((char*)&pret_produs, sizeof(float));
			int nr_igrediente;
			f1 >> nr_igrediente;
			f.write((char*)&nr_igrediente, sizeof(int));
			int nr_portii;
			f1 >> nr_portii;
			f.write((char*)&nr_portii, sizeof(int));
			for (int j = 0; j < nr_igrediente; j++)
			{
				string nume_ingredient;
				getline(f1 >> ws, nume_ingredient, ' ');
				int n = nume_ingredient.size() + 1;
				f.write((char*)&n, sizeof(int));
				f.write(nume_ingredient.data(), n);
				float cantitate_ingredient;
				f1 >> cantitate_ingredient;
				f.write((char*)&cantitate_ingredient, sizeof(int));
			}
		}

		//scriem deserturi
		int nr_deserturi;
		f1 >> nr_deserturi;
		f.write((char*)&nr_deserturi, sizeof(int));
		for (int i = 0; i < nr_deserturi; i++) {
			string nume_preparat;
			getline(f1 >> ws, nume_preparat, ' ');
			int lg = nume_preparat.size() + 1;
			f.write((char*)&lg, sizeof(int));
			f.write(nume_preparat.data(), lg);
			float pret_produs;
			f1 >> pret_produs;
			f.write((char*)&pret_produs, sizeof(float));
			int nr_igrediente;
			f1 >> nr_igrediente;
			f.write((char*)&nr_igrediente, sizeof(int));
			int nivel_zahar;
			f1 >> nivel_zahar;
			f.write((char*)&nivel_zahar, sizeof(int));
			for (int j = 0; j < nr_igrediente; j++)
			{
				string nume_ingredient;
				getline(f1 >> ws, nume_ingredient, ' ');
				int n = nume_ingredient.size() + 1;
				f.write((char*)&n, sizeof(int));
				f.write(nume_ingredient.data(), n);
				float cantitate_ingredient;
				f1 >> cantitate_ingredient;
				f.write((char*)&cantitate_ingredient, sizeof(int));
			}
		}
		f.close();
	}

	void restoreFromFile(fstream& f) {
		int nr_produse_fisier, lg;
		float cantitate;
		string nume_produs;
		f.read((char*)&nr_produse_fisier, sizeof(int));
		cout << nr_produse_fisier << endl;
		for (int i = 0;i < nr_produse_fisier;i++)
		{
			f.read((char*)&lg, sizeof(int));
			char* buffer = new char[lg];
			f.read(buffer, lg);
			nume_produs = buffer;
			cout << nume_produs << " ";
			delete[] buffer;
			buffer = nullptr;
			f.read((char*)&cantitate, sizeof(int));
			cout << cantitate;
			cout << endl;
		}
	}

	void restoreFromFile2(fstream& f) {
		int nr_feluri_principale;
		f.read((char*)&nr_feluri_principale, sizeof(int));
		cout << nr_feluri_principale << endl;

		for (int i = 0; i < nr_feluri_principale; i++) {
			int lg;
			string nume_preparat;
			f.read((char*)&lg, sizeof(int));
			char* buffer = new char[lg];
			f.read(buffer, lg);
			nume_preparat = buffer;
			cout << nume_preparat << " ";
			delete[] buffer;
			buffer = nullptr;
			float pret_produs;
			f.read((char*)&pret_produs, sizeof(float));
			cout << pret_produs << " ";
			int nr_igrediente;
			f.read((char*)&nr_igrediente, sizeof(int));
			cout << nr_igrediente << " ";
			int nr_portii;
			f.read((char*)&nr_portii, sizeof(int));
			cout << nr_portii << " ";
			for (int j = 0; j < nr_igrediente; j++)
			{
				string nume_ingredient;
				int n;
				f.read((char*)&n, sizeof(int));
				char* buffer = new char[n];
				f.read(buffer, n);
				nume_ingredient = buffer;
				cout << nume_ingredient << " ";
				delete[] buffer;
				buffer = nullptr;
				float cantitate_ingredient;
				f.read((char*)&cantitate_ingredient, sizeof(int));
				cout << cantitate_ingredient << " ";
			}
			cout << endl;
		}

		int nr_deserturi;
		f.read((char*)&nr_deserturi, sizeof(int));
		cout << nr_deserturi << endl;

		for (int i = 0; i < nr_deserturi; i++) {
			int lg;
			string nume_preparat;
			f.read((char*)&lg, sizeof(int));
			char* buffer = new char[lg];
			f.read(buffer, lg);
			nume_preparat = buffer;
			cout << nume_preparat << " ";
			delete[] buffer;
			buffer = nullptr;
			float pret_produs;
			f.read((char*)&pret_produs, sizeof(float));
			cout << pret_produs << " ";
			int nr_igrediente;
			f.read((char*)&nr_igrediente, sizeof(int));
			cout << nr_igrediente << " ";
			int nivel_zahar;
			f.read((char*)&nivel_zahar, sizeof(int));
			cout << nivel_zahar << " ";
			for (int j = 0; j < nr_igrediente; j++)
			{
				string nume_ingredient;
				int n;
				f.read((char*)&n, sizeof(int));
				char* buffer = new char[n];
				f.read(buffer, n);
				nume_ingredient = buffer;
				cout << nume_ingredient << " ";
				delete[] buffer;
				buffer = nullptr;
				float cantitate_ingredient;
				f.read((char*)&cantitate_ingredient, sizeof(int));
				cout << cantitate_ingredient << " ";
			}
			cout << endl;
		}
	}
};


void main(int argc, char* argv[])
{
	
	Meniu meniu(argc, argv);
	meniu.startMeniu(meniu);
	//afiseazaComenziClienti();
 
	
	/*
	fstream file("stoc.bin", ios::out | ios::binary);
	meniu.writeToFile(file);
	file.close();
	fstream file2("stoc.bin", ios::in | ios::binary);
	restoreFromFile(file2);
	file2.close();	
	fstream file3("preparate.bin", ios::out | ios::binary);
	writeToFile2(file3);
	file3.close();
	fstream file4("preparate.bin", ios::in | ios::binary);
	restoreFromFile2(file4);
	file4.close(); */
}




