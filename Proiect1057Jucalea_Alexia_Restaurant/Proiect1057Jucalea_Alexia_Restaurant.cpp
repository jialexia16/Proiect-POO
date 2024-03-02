#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

class Stoc {
private:
	int nrProduseStoc = 0;
	string* numeProduseStoc = nullptr;
	int* cantitateProduseStoc = nullptr;
public:
	Stoc() {};

	Stoc(int nrProduseStoc, string* numeProduseStoc, int* cantitateProduseStoc)
	{
		if (nrProduseStoc > 0 && numeProduseStoc != nullptr && cantitateProduseStoc != nullptr)
		{
			this->nrProduseStoc = nrProduseStoc;
			this->numeProduseStoc = new string[this->nrProduseStoc];
			this->cantitateProduseStoc = new int[this->nrProduseStoc];
			for (int i = 0; i < this->nrProduseStoc; i++)
			{
				this->numeProduseStoc[i] = numeProduseStoc[i];
				this->cantitateProduseStoc[i] = cantitateProduseStoc[i];
			}
		}
	}

	Stoc(const string& numeFisier) {
		incarcaStocDinFisier(numeFisier);
	}

	~Stoc() {
		delete[] numeProduseStoc;
		delete[] cantitateProduseStoc;
	}
	//getteri si setteri
	void setNrProduseStoc(int nr)
	{
		if (nr > 0) this->nrProduseStoc = nr;
	}

	int getProduseStoc() {
		return this->nrProduseStoc;
	}

	void setNumeProduseStoc(int nrProduseStoc, string* denumire)
	{
		if (nrProduseStoc > 0 && denumire != nullptr)
		{
			this->numeProduseStoc = new string[nrProduseStoc];
			for (int i = 0; i < nrProduseStoc; i++)
				this->numeProduseStoc[i] = denumire[i];
		}
	}

	void setCantitateProduseStoc(int nrProduseStoc, int* cantitate)
	{
		if (nrProduseStoc > 0 && cantitate != nullptr)
		{
			this->cantitateProduseStoc = new int[nrProduseStoc];
			for (int i = 0; i < nrProduseStoc; i++)
				this->cantitateProduseStoc[i] = cantitate[i];
		}
	}

	int* getCantitateProduseStoc() {
		return this->cantitateProduseStoc;
	}

	string* getNumeProduseStoc() {
		return this->numeProduseStoc;
	}
	//constrctor de copiere
	Stoc(const Stoc& s)
	{
		delete[] numeProduseStoc;
		delete[] cantitateProduseStoc;
		this->nrProduseStoc = s.nrProduseStoc;
		this->numeProduseStoc = new string[this->nrProduseStoc];
		this->cantitateProduseStoc = new int[this->nrProduseStoc];
		for (int i = 0; i < this->nrProduseStoc; i++)
		{
			this->numeProduseStoc[i] = s.numeProduseStoc[i];
			this->cantitateProduseStoc[i] = s.cantitateProduseStoc[i];
		}
	}

	//operator =
	Stoc& operator=(Stoc& s)
	{
		if (this != &s)
		{
			delete[] numeProduseStoc;
			delete[] cantitateProduseStoc;
			this->nrProduseStoc = s.nrProduseStoc;
			this->numeProduseStoc = new string[this->nrProduseStoc];
			this->cantitateProduseStoc = new int[this->nrProduseStoc];
			for (int i = 0; i < this->nrProduseStoc; i++)
			{
				this->numeProduseStoc[i] = s.numeProduseStoc[i];
				this->cantitateProduseStoc[i] = s.cantitateProduseStoc[i];
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
		for (int i = 0; i < s.nrProduseStoc; i++)
		{
			out << "\nNume:" << s.numeProduseStoc[i];
			out << ";   Cantitate: " << s.cantitateProduseStoc[i];
		}
		return out;
	}

	friend istream& operator>>(istream& in, Stoc& s)
	{
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
		return in;
	}

	explicit operator int()
	{
		return this->nrProduseStoc;
	}


	// Metoda pentru a incarca stocul din fisier
	void incarcaStocDinFisier(const string& numeFisier) {
		ifstream fisierStoc(numeFisier);
		if (fisierStoc) {
			fisierStoc >> nrProduseStoc;

			numeProduseStoc = new string[nrProduseStoc];
			cantitateProduseStoc = new int[nrProduseStoc];

			for (int i = 0; i < nrProduseStoc; i++) {
				getline(fisierStoc >> ws, numeProduseStoc[i], ','); // Citeste numele pana la virgula, ws=whitespace, le ignora
				fisierStoc >> cantitateProduseStoc[i];
			}
			fisierStoc.close();
		}
		else {
			cout << "Eroare la deschiderea fisierului.\n";
		}
	}

	int operator[](string& numeProdus) {
		for (int i = 0; i < nrProduseStoc; ++i) {
			if (numeProduseStoc[i] == numeProdus) {
				return i;//am grija daca am lapte de soia si lapte
			}
		}
		return -1; // Returneaza -1 pentru a indica ca numele de produs nu a fost gasit
	}

	bool VerificaStocProdus(string numeProdus, int cantitateCerutaProdus)
	{
		int i = (*this)[numeProdus];
		if (i != -1)
			return this->cantitateProduseStoc[i] >= cantitateCerutaProdus;
		else return 0;
	}

	bool actualizeazaStoc(string numeProdus, int cantitateComandata) {
		if (cantitateComandata > 0)
			if (VerificaStocProdus(numeProdus, cantitateComandata))
			{
				int i = (*this)[numeProdus];
				this->cantitateProduseStoc[i] -= cantitateComandata;
				return true;
			}
			else {
				return false;
			}
		else {
			return false;
		}
	}

};

class Preparat {
private:
	string numePreparat = "";
	int nrIngrediente = 0;
	string* ingrediente = nullptr;
	int* cantitate = nullptr;
	float pret = 0;
public:

	//constructori
	Preparat() {};
	Preparat(string numePreparat, int nrIngrediente, const string* ingrediente, const int* cantitate, float pret) {
		if (numePreparat.size() > 0) this->numePreparat = numePreparat;
		if (nrIngrediente > 0 && ingrediente != nullptr && cantitate != nullptr)
		{
			this->numePreparat = numePreparat;
			this->nrIngrediente = nrIngrediente;
			this->ingrediente = new string[this->nrIngrediente];
			this->cantitate = new int[this->nrIngrediente];
			for (int i = 0; i < this->nrIngrediente; i++)
			{
				this->ingrediente[i] = ingrediente[i];
				this->cantitate[i] = cantitate[i];
			}
		}
		if (pret > 0) {
			this->pret = pret;
		}
	}
	Preparat(string numePreparat)
	{
		if (numePreparat.size() > 0) {
			this->numePreparat = numePreparat;
		}
	}
	virtual ~Preparat() {
		delete[]	this->ingrediente;
		this->ingrediente = nullptr;
		delete[] this->cantitate;
		this->cantitate = nullptr;
	}


	//getteri si setteri
	void setNrIngrediente(int nrIngrediente) {
		if (nrIngrediente > 0) this->nrIngrediente = nrIngrediente;
	}
	int getNrIngrediente() {
		return this->nrIngrediente;
	}
	void setNumePreparat(string numePreparat)
	{
		if (numePreparat.size() > 0) this->numePreparat = numePreparat;
	}
	string getNumePreparat() {
		return this->numePreparat;
	}

	void setIngrediente(int nrIngrediente, string* ingrediente, int* cantitate)
	{
		if (nrIngrediente > 0 && ingrediente != nullptr && cantitate != nullptr)
		{
			this->nrIngrediente = nrIngrediente;
			this->ingrediente = new string[this->nrIngrediente];
			this->cantitate = new int[this->nrIngrediente];
			for (int i = 0; i < this->nrIngrediente; i++)
			{
				this->ingrediente[i] = ingrediente[i];
				this->cantitate[i] = cantitate[i];
			}
		}
	}
	string* getListaIngrediente() {
		return this->ingrediente;
	}
	int* getCantitatiIngrediente() {
		return this->cantitate;
	}

	void setPret(float pret) {
		if (pret > 0) this->pret = pret;
	}

	float getPret() {
		return this->pret;
	}

	//constructor copiere
	Preparat(const Preparat& c) {
		delete[] this->ingrediente;
		this->ingrediente = nullptr;
		delete[] this->cantitate;
		this->cantitate = nullptr;
		if (c.numePreparat.size() > 0) { this->numePreparat = c.numePreparat; }
		if (c.nrIngrediente > 0 && c.ingrediente != nullptr && c.cantitate != nullptr)
		{
			this->numePreparat = c.numePreparat;
			this->nrIngrediente = c.nrIngrediente;
			this->ingrediente = new string[this->nrIngrediente];
			this->cantitate = new int[this->nrIngrediente];
			for (int i = 0; i < this->nrIngrediente; i++)
			{
				this->ingrediente[i] = c.ingrediente[i];
				this->cantitate[i] = c.cantitate[i];
			}
		}
		this->pret = c.pret;
	}

	//operator =
	Preparat& operator=(const Preparat& c)
	{
		if (this != &c)
		{
			delete[] this->ingrediente;
			this->ingrediente = nullptr;
			delete[] this->cantitate;
			this->cantitate = nullptr;

			if (c.numePreparat.size() > 0) { this->numePreparat = c.numePreparat; }
			if (c.nrIngrediente > 0 && c.ingrediente != nullptr && c.cantitate != nullptr)
			{
				this->numePreparat = c.numePreparat;
				this->nrIngrediente = c.nrIngrediente;
				this->ingrediente = new string[this->nrIngrediente];
				this->cantitate = new int[this->nrIngrediente];
				for (int i = 0; i < this->nrIngrediente; i++)
				{
					this->ingrediente[i] = c.ingrediente[i];
					this->cantitate[i] = c.cantitate[i];
				}
			}
			this->pret = c.pret;
		}
		return *this;
	}

	//operator ==
	bool operator==(const Preparat& c)
	{
		int ok = 1;
		if (this != &c)
		{
			if (c.numePreparat != this->numePreparat) { ok = 0; }
			if (c.nrIngrediente != this->nrIngrediente) { ok = 0; }
			if (c.cantitate != this->cantitate) { ok = 0; }
			if (c.pret != this->pret) { ok = 0; }
			if (ok == 1 && c.nrIngrediente > 0 && c.ingrediente != nullptr && c.cantitate != nullptr)
			{
				for (int i = 0; i < this->nrIngrediente; i++)
				{
					if (c.ingrediente[i] != this->ingrediente[i]) { ok = 0; }
					if (c.cantitate[i] != this->cantitate[i]) { ok = 0; }
				}
			}
		}
		else {
			return true;
		}
		return ok;
	}

	//operatori >> si <<
	friend ostream& operator<<(ostream& out, const Preparat& r)
	{
		out << "\nNume preparat: " << r.numePreparat;
		out << "\nNr ingrediente: " << r.nrIngrediente;
		out << "\nIngrediente: ";
		for (int i = 0; i < r.nrIngrediente; i++)
		{
			out << "\n-" << r.ingrediente[i] << "(" << r.cantitate[i] << ")";

		}
		out << "\nPret: " << r.pret;
		return out;
	}
	friend istream& operator>>(istream& in, Preparat& r)
	{
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
		return in;
	}

	//metode

	void adaugaIngredient(string nume, int cantitate) {
		int* copieCantitate = new int[this->nrIngrediente + 1];
		string* copieIngrediente = new string[this->nrIngrediente + 1];

		for (int i = 0; i < this->nrIngrediente; i++) {
			copieCantitate[i] = this->cantitate[i];
			copieIngrediente[i] = this->ingrediente[i];
		}

		copieCantitate[this->nrIngrediente] = cantitate;
		copieIngrediente[this->nrIngrediente] = nume;

		delete[] this->cantitate;
		delete[] this->ingrediente;

		this->cantitate = copieCantitate;
		this->ingrediente = copieIngrediente;
		this->nrIngrediente++;
	}

	void emptyPreparat() {
		delete[]	this->ingrediente;
		this->ingrediente = nullptr;
		delete[] this->cantitate;
		this->cantitate = nullptr;
		this->nrIngrediente = 0;
	}

};

enum CategorieDulciuri {
	TORTURI,
	PRAJITURI,
	INGHETATE,
	ALTE_DULCIURI
};


class Desert :public Preparat {
private:
	CategorieDulciuri categorie = ALTE_DULCIURI;
	//de adaugat atribute
	int nivelZahar = 0;
	static int nivelZaharMaximcCopii;
public:
	//constructori
	Desert() :Preparat() {}

	Desert(Preparat p, CategorieDulciuri cat) :Preparat(p) {
		if (cat == TORTURI || cat == PRAJITURI || cat == INGHETATE || cat == ALTE_DULCIURI)
			this->categorie = cat;
	}

	Desert(string numePreparat, int nrIngrediente, const string* ingrediente, const int* cantitate, float pret, CategorieDulciuri cat, int nivelZahar) :Preparat(numePreparat, nrIngrediente, ingrediente, cantitate, pret) {
		if (cat == TORTURI || cat == PRAJITURI || cat == INGHETATE || cat == ALTE_DULCIURI)
			this->categorie = cat;
		if (nivelZahar > 0) this->nivelZahar = nivelZahar;
	}

	Desert(string numePreparat) :Preparat(numePreparat) {}

	Desert(const Desert& d) :Preparat(d) {
		this->categorie = d.categorie;
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
	void setCategorie(CategorieDulciuri cat) {
		if (cat == TORTURI || cat == PRAJITURI || cat == INGHETATE || cat == ALTE_DULCIURI)
			this->categorie = cat;
	}
	CategorieDulciuri getCategorie() {
		return static_cast<CategorieDulciuri>(categorie);
	}
	static const char* numeCategoritoString(CategorieDulciuri categorie) {
		switch (categorie) {
		case TORTURI:
			return "Torturi";
		case PRAJITURI:
			return "Prajituri";
		case INGHETATE:
			return "Inghetate";
		case ALTE_DULCIURI:
			return "Alte dulciuri";
		default:
			return "Categorie necunoscuta";
		}
	}

	//operatori << si >>
	friend ostream& operator<<(ostream& out, const Desert& d) {
		out << (Preparat)d;
		out << "\nCategorie: " << Desert::numeCategoritoString(d.categorie) << "\n";
		if (d.nivelZahar > Desert::nivelZaharMaximcCopii) {
			cout << "Acest desert nu este recomandat copiilor!";
		}
		out << "Nivel zahar: " << d.nivelZahar << ".";
		return out;
	}
	friend istream& operator>>(istream& in, Desert& d)
	{
		in >> (Preparat&)d;
		cout << "\nCategorie dulciuri (1-4) \n1.Torturi\n2.Prajituri\n3.Inghetate\n4.Alte dulciuri:";

		int val;
		in >> val;

		switch (val) {
		case 1:
			d.categorie = TORTURI;
			break;
		case 2:
			d.categorie = PRAJITURI;
			break;
		case 3:
			d.categorie = INGHETATE;
			break;
		case 4:
			d.categorie = ALTE_DULCIURI;
			break;
		default:
			cout << "Valoare nevalida pentru CategorieDulciuri. Setat la ALTE_DULCIURI.\n";
			d.categorie = ALTE_DULCIURI;
			break;
		}
		cout << "\nNivel de zahar: ";
		in >> d.nivelZahar;
		return in;
	}



	// operator =
	Desert& operator=(const Desert& d) {
		if (this != &d)
		{
			this->Preparat::operator=(d);
			this->categorie = d.categorie;
			this->nivelZahar = d.nivelZahar;
		}
		return *this;
	}
	bool contineLapte() {
		for (int i = 0; i < this->getNrIngrediente(); i++) {
			if (strcmp(this->getListaIngrediente()[i].c_str(), "lapte") == 0) {
				return true;
			}
		}
		return false;
	}


	//operator []
	int operator[](const string& ingredientCautat) //apelez cu "lapte"
	{
		string* ingrediente = new string[this->getNrIngrediente()];
		ingrediente = this->getListaIngrediente();
		for (int i = 0; i < this->getNrIngrediente(); i++)
			if (ingrediente[i] == ingredientCautat)
				return i;
	}
	bool InterzisCopiilor()
	{
		return(this->nivelZahar < nivelZaharMaximcCopii);
	}
};
int Desert::nivelZaharMaximcCopii = 20;

enum TipFelPrincipal {
	garnitura, ciorba, mic_dejun, aperitiv, salata, gustare
};

class FelPrincipal :public Preparat {
private:
	TipFelPrincipal tip;
	int nrPortii = 0;
	static int nrMediuPortii;
public:
	//constructori
	FelPrincipal() :Preparat() {}

	FelPrincipal(Preparat p, TipFelPrincipal tip, int nrPortii) :Preparat(p) {
		if (tip == garnitura || tip == ciorba || tip == mic_dejun || tip == aperitiv || tip == salata || tip == gustare)
			this->tip = tip;
		if (nrPortii > 0) this->nrPortii = nrPortii;
	}

	FelPrincipal(string numePreparat, int nrIngrediente, const string* ingrediente, const int* cantitate, float pret, TipFelPrincipal tip, int nrPortii) :Preparat(numePreparat, nrIngrediente, ingrediente, cantitate, pret) {
		if (tip == garnitura || tip == ciorba || tip == mic_dejun || tip == aperitiv || tip == salata || tip == gustare)
			this->tip = tip;
		if (nrPortii > 0) this->nrPortii = nrPortii;
	}

	FelPrincipal(string numePreparat) :Preparat(numePreparat) {
	}

	FelPrincipal(const FelPrincipal& fp) :Preparat(fp)
	{
		this->tip = fp.tip;
		this->nrPortii = fp.nrPortii;
	}

	//getteri si setteri

	void setTip(TipFelPrincipal tip) {
		if (tip == garnitura || tip == ciorba || tip == mic_dejun || tip == aperitiv || tip == salata || tip == gustare)
			this->tip = tip;
	}
	TipFelPrincipal getTip() {
		return static_cast<TipFelPrincipal>(tip);
	}

	void setNrPortii(int nrPortii)
	{
		if (nrPortii > 0) this->nrPortii = nrPortii;
	}
	int getNrPortii() {
		return this->nrPortii;
	}

	bool contineCarne() {
		string* ingrediente = this->getListaIngrediente();
		for (int i = 0; i < this->getNrIngrediente(); i++) {
			if (ingrediente[i].find("carne") != string::npos) {
				return true;
			}
		}
		return false;
	}

	static const string felPricipalToString(TipFelPrincipal tip) {
		switch (tip) {
		case garnitura:
			return "garnitura";
		case ciorba:
			return "ciorba";
		case mic_dejun:
			return "mic dejun";
		case aperitiv:
			return "aperitiv";
		case salata:
			return "salata";
		case gustare:
			return "gustare";
		default:
			return "altceva";
		}
	}


	//<< si >> (nu am testat istream-ul, dar vreau tare sa fac un fisier de unde sa preiau si unde sa pun datele)
	friend ostream& operator<<(ostream& out, FelPrincipal& fp) {

		out << (Preparat)fp;
		out << "\nTip fel principal: " << FelPrincipal::felPricipalToString(fp.tip);
		out << "\nNumar portii: " << fp.nrPortii << ".";
		if (fp.nrPortii > FelPrincipal::nrMediuPortii) {
			cout << " Nu se recomanda copiilor, cantitate mare de mancare.";
		}
		return out;
	}
	friend istream& operator>>(istream& in, FelPrincipal& fp)
	{
		in >> (Preparat&)fp;
		cout << "\nTip fel principal: ";
		cout << "\nFel principal (1-4) \n1.Garnitura\n2.Ciorba\n3.Mic dejun\n4.Aperitiv\n5.Salata\n6.Gustare:";

		int val;
		in >> val;

		switch (val) {
		case 1:
			fp.tip = garnitura;
			break;
		case 2:
			fp.tip = ciorba;
			break;
		case 3:
			fp.tip = mic_dejun;
			break;
		case 4:
			fp.tip = aperitiv;
			break;
		case 5:
			fp.tip = salata;
			break;
		case 6:
			fp.tip = gustare;
			break;
		default:
			cout << "Valoare nevalida pentru Tip Fel Principal. Setat la garnitura.\n";
			fp.tip = garnitura;
			break;
		}
		cout << "\nNumar portii: ";
		in >> fp.nrPortii;
		return in;
	}

	//operator =
	FelPrincipal& operator=(const FelPrincipal& fp) {
		if (this != &fp)
		{
			this->Preparat::operator=(fp);
			this->tip = fp.tip;
			this->nrPortii = fp.nrPortii;
		}
		return *this;
	}

};

int FelPrincipal::nrMediuPortii = 3;


class Comanda {
private:
	const int id;
	int nrPreparate = 0;
	Preparat* preparate = nullptr;
	int nomilk = -1; // -1 - lapte de vaca         +1 - fara lapte de vaca;
	string meat_type = "pui";
	static int ultimulIdUtilizat;

public:
	//constructori
	Comanda() :id(++ultimulIdUtilizat) {}
	Comanda(int nrPreparate, Preparat* preparate, int nomilk, string meat_type) :id(++ultimulIdUtilizat) {

		if (nrPreparate > 0 && preparate != nullptr)
		{
			this->preparate = new Preparat[nrPreparate];
			for (int i = 0; i < nrPreparate; i++)
				this->preparate[i] = preparate[i];
		}
		this->nomilk = nomilk;
		this->meat_type = meat_type;
	}

	Comanda(int nrPreparate, Preparat* preparate) :id(++ultimulIdUtilizat) {
		if (nrPreparate > 0 && preparate != nullptr)
		{
			this->preparate = new Preparat[nrPreparate];
			for (int i = 0; i < nrPreparate; i++)
				this->preparate[i] = preparate[i];
		}
	}
	Comanda(const Comanda& c) :id(c.id) {
		this->nrPreparate = c.nrPreparate;
		this->preparate = new FelPrincipal[c.nrPreparate];
		for (int i = 0; i < c.nrPreparate; i++)
			this->preparate[i] = c.preparate[i];
		this->nomilk = c.nomilk;
		this->meat_type = c.meat_type;
	}
	Comanda(int nomilk, string meat_type) :id(++ultimulIdUtilizat) {
		this->nomilk = nomilk;
		this->meat_type = meat_type;
	}

	//destructor
	~Comanda()
	{
		delete[] this->preparate;
		this->preparate = nullptr;
	}

	//getteri,setter
	int getIdComanda() const { return this->id; }
	void setPreparateComanda(int nrPreparate, Preparat* preparate)
	{
		if (nrPreparate > 0 && preparate != nullptr)
		{
			this->preparate = new FelPrincipal[nrPreparate];
			for (int i = 0; i < nrPreparate; i++)
				this->preparate[i] = preparate[i];
		}
	}
	int getNrPreparate() {

		return this->nrPreparate;
	}
	Preparat* getPreparateComanda() {
		return this->preparate;
	}
	void setMeatType(string tip_carne) {
		this->meat_type = tip_carne;
	}
	string getMeatType()
	{
		return this->meat_type;
	}

	int getNoMilk()
	{
		return this->nomilk;
	}


	int toggleNomilk() {
		this->nomilk *= (-1);
		return this->nomilk;
	}

	//operator =
	Comanda operator=(const Comanda& c) {
		if (this != &c)
		{
			this->nrPreparate = c.nrPreparate;
			this->preparate = new FelPrincipal[c.nrPreparate];
			for (int i = 0; i < c.nrPreparate; i++)
				this->preparate[i] = c.preparate[i];
			this->nomilk = c.nomilk;
			this->meat_type = c.meat_type;
		}
		return *this;
	}
	//>> si <<
	friend ostream& operator<<(ostream& out, Comanda& c)
	{


		if (c.nrPreparate)
		{
			out << "\n****************************************************";
			out << "\nComanda ta contine: " << endl;
			float pretTotal = 0;
			for (int i = 0; i < c.nrPreparate; i++) {
				out << "\n" << c.preparate[i].getNumePreparat() << "   -   " << c.preparate[i].getPret() << "lei.";
				pretTotal += c.preparate[i].getPret();
			}
			cout << "\n                      Pret total: " << (c >= 100 ? pretTotal * 0.9 : pretTotal) << "lei" << (c >= 100 ? " discount 10% " : "");
			out << "\n****************************************************";
		}
		return out;

	}
	friend istream& operator>>(istream& in, Comanda& c)
	{

		cout << "Introduceti numarul de preparate: ";
		in >> c.nrPreparate;
		if (c.nrPreparate > 0) {
			c.preparate = new FelPrincipal[c.nrPreparate];
			cout << "Introduceti detaliile pentru fiecare fel principal:" << endl;
			for (int i = 0; i < c.nrPreparate; i++) {
				cout << "Preparat " << i + 1 << ":" << endl;
				in >> c.preparate[i];
			}
		}
		cout << "Introduceti nomilk (-1 pentru lapte de vaca, 1 pentru lapte vegan): ";
		in >> c.nomilk;

		cout << "Introduceti meat_type: ";
		in >> c.meat_type;

		return in;
	}

	void operator+(Preparat& p) {
		Preparat* tempPreparate = new Preparat[this->nrPreparate + 1];
		for (int i = 0; i < this->nrPreparate; i++)
		{
			tempPreparate[i] = preparate[i];
		}
		tempPreparate[this->nrPreparate] = p;
		this->nrPreparate++;
		delete[] this->preparate;
		this->preparate = tempPreparate;

	}

	bool operator>=(int valoare) {
		float pretTotal = 0;
		for (int i = 0; i < this->nrPreparate; i++) {
			pretTotal += this->preparate[i].getPret();
		}

		return pretTotal >= 100;
	}

	//operator negare
	bool operator!()
	{
		return this->nomilk > 0;
	}

};

class Meniu {
private:
	FelPrincipal* feluriPrincipale = nullptr;
	Desert* deserturi = nullptr;
	int nr_feluri_principale = 0;
	int nr_deserturi = 0;
	static int ultimulIdUtilizat;
	Comanda comanda;
	Stoc stoc;

public:
	Meniu() {

		//initializam Feluri Principale
		ifstream f("feluri_principale.txt");
		string* denumire_ingrediente;
		int* cantitati_ingrediente;
		if (f) { // ferific daca fisierul poate fi deschis
			int nr_feluri_principale;
			f >> nr_feluri_principale;
			if (nr_feluri_principale > 0) {
				feluriPrincipale = new FelPrincipal[nr_feluri_principale];
				this->nr_feluri_principale = nr_feluri_principale;
				for (int i = 0; i < nr_feluri_principale; i++) {
					string denumire;
					float pret;
					int nr_ingrediente;
					int nrPortii;
					f >> denumire >> pret >> nr_ingrediente >> nrPortii;

					string* denumire_ingrediente = new string[nr_ingrediente];
					int* cantitati_ingrediente = new int[nr_ingrediente];

					for (int j = 0; j < nr_ingrediente; j++) {
						string ingredient;
						int cantitate;
						f >> ingredient >> cantitate;
						denumire_ingrediente[j] = ingredient;
						cantitati_ingrediente[j] = cantitate;
					}
					feluriPrincipale[i] = FelPrincipal(denumire, nr_ingrediente, denumire_ingrediente, cantitati_ingrediente, pret, garnitura, nrPortii);
					feluriPrincipale[i].setPret(pret);
					feluriPrincipale[i].setIngrediente(nr_ingrediente, denumire_ingrediente, cantitati_ingrediente);

				}
			}
		}
		else {
			cout << "\n Fisierul nu poate fi deschis";
		}
		f.close();

		//initializam Deserturi
		ifstream d("deserturi.txt");
		if (d) { // verific daca fisierul poate fi deschis
			int nr_deserturi;
			d >> nr_deserturi;
			if (nr_deserturi > 0) {
				deserturi = new Desert[nr_deserturi];
				this->nr_deserturi = nr_deserturi;
				for (int i = 0; i < nr_deserturi; i++) {
					string denumire;
					float pret;
					int nr_ingrediente;
					int nivelZahar;
					d >> denumire >> pret >> nr_ingrediente >> nivelZahar;

					denumire_ingrediente = new string[nr_ingrediente];
					cantitati_ingrediente = new int[nr_ingrediente];

					for (int j = 0; j < nr_ingrediente; j++) {
						string ingredient;
						int cantitate;
						d >> ingredient >> cantitate;
						denumire_ingrediente[j] = ingredient;
						cantitati_ingrediente[j] = cantitate;
					}
					deserturi[i] = Desert(denumire, nr_ingrediente, denumire_ingrediente, cantitati_ingrediente, pret, ALTE_DULCIURI, nivelZahar);
					deserturi[i].setPret(pret);
					deserturi[i].setIngrediente(nr_ingrediente, denumire_ingrediente, cantitati_ingrediente);

				}
			}
		}
		else {
			cout << "\n Fisierul nu poate fi deschis";
		}
		f.close();

		//initializam Stoc-ul
		stoc.incarcaStocDinFisier("stoc.txt");
	}

	//getteri si setteri
	FelPrincipal* getFeluriPrincipale() {
		return this->feluriPrincipale;
	}

	int getNrFeluriPrincipale() {
		return this->nr_feluri_principale;
	}

	Desert* getDeserturi() {
		return this->deserturi;
	}

	int getNrDeserturi() {
		return this->nr_deserturi;
	}

	//operatori
	friend ostream& operator<<(ostream& out, Meniu& m)
	{
		out << "                 <<<<<<  MENIU  >>>>>>";
		out << "\n\n---Feluri Principale---";
		FelPrincipal* fp = m.getFeluriPrincipale();
		int nr_fp = m.getNrFeluriPrincipale();
		if (fp != nullptr && nr_fp > 0) {
			for (int i = 0; i < nr_fp; i++) {
				cout << "\n" << i + 1 << ". " << fp[i].getNumePreparat() << " - " << fp[i].getPret();
			}
		}

		out << "\n\n---Deserturi---";
		Desert* d = m.getDeserturi();
		int nr_d = m.getNrDeserturi();
		if (d != nullptr && nr_d > 0) {
			for (int i = 0; i < nr_d; i++) {
				cout << "\n" << i + 1 << ". " << d[i].getNumePreparat() << " - " << d[i].getPret();
			}
		}


		return out;
	}


	void startMeniu(Meniu& meniu) {
		//initHeader();
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
			}

			if (!strcmp(cmd, "NOMILK")) {
				cmd_ok = 1;
				initHeader();
				if (this->comanda.toggleNomilk() < 0)
					cout << "\nRetelele vor contine lapte de vaca.";
				else
					cout << "\nRetelele NU vor contine lapte de vaca.";
			}

			//comenzi ce contin cel putin doua cuvinte

			char* token = strtok(cmd, " ");

			if (!strcmp(token, "MORE")) {
				cmd_ok = 1;
				initHeader();
				token = strtok(NULL, " ");
				if (token != NULL) {
					Preparat* result = searchPreparat(token);
					if (result != nullptr) {
						if (dynamic_cast<FelPrincipal*>(result)) {
							FelPrincipal* fp = dynamic_cast<FelPrincipal*>(result);
							cout << *fp;

						}
						else if (dynamic_cast<Desert*>(result)) {
							Desert* d = dynamic_cast<Desert*>(result);
							cout << *d;
						}
					}
					else
						cout << "\nAcest preparat nu se afla in meniu.";
				}
			}

			if (!strcmp(token, "MEATTYPE")) {
				cmd_ok = 1;
				initHeader();
				token = strtok(NULL, " ");
				if (token != NULL) {
					if (!strcmp(token, "pui") || !strcmp(token, "porc") || !strcmp(token, "vita") || !strcmp(token, "peste")) {
						this->comanda.setMeatType(token);
						cout << "\nTipul de carne pentru comenzi a fost actualizata cu: " << token;
					}
					else {
						cout << "\nNu detinem acest tip de carne";
					}
				}
			}


			if (!strcmp(token, "CMD")) {
				cmd_ok = 1;
				initHeader();
				token = strtok(NULL, " ");
				if (token != NULL) {
					string preparat = token;
					token = strtok(NULL, " ");
					if (token != NULL) {
						string str_cant = token;
						if (str_cant.find_first_not_of("0123456789") == string::npos) {
							Preparat* result = searchPreparat(preparat.c_str());
							if (result != nullptr) {
								if (adaugaPreparatInComanda(*result, stoi(str_cant))) {
									cout << "\nPreparat adaugat in comanda cu succes.";
								}
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
				cout << "\nIntroduceti o comanda valida!";
				//afisareComenziDisponibile();
			}

			cout << comanda;
		}
	}

	void afisareComenziDisponibile() {
		cout << "\n\nTastati una din urmatoarele comenzi:";
		cout << "\nMENIU                                          MORE [nume_preparat]";
		cout << "\nNOMILK                                         MEATTYPE [pui | porc | vita | peste]";
		cout << "\nCMD [nume_preparat] [cantitatea]               ";
	}

	void initHeader() {
		system("CLS");
		cout << "\nBine ati venit la restaurantul nostu!\n\n\n";
	}

	Preparat* searchPreparat(const char* denumire) {
		for (int i = 0; i < this->nr_feluri_principale; i++) {
			string denumire_copy = denumire;
			if (feluriPrincipale[i].getNumePreparat() == denumire) {
				return &feluriPrincipale[i];
			}
		}

		for (int i = 0; i < this->nr_deserturi; i++) {
			string denumire_copy = denumire;
			if (deserturi[i].getNumePreparat() == denumire_copy) {
				return &deserturi[i];
			}
		}

		return nullptr;
	}

	bool adaugaPreparatInComanda(Preparat p, int cant) {

		int ok = 1;
		int* cant_ingrediente = p.getCantitatiIngrediente();
		string* nume_ingrediente = p.getListaIngrediente();
		for (int i = 0; i < p.getNrIngrediente() && ok == 1; i++) {
			if (nume_ingrediente[i] == "lapte" && comanda.getNoMilk() == 1) {
				nume_ingrediente[i] = "lapte_vegetal";
			}

			if (nume_ingrediente[i].find("carne") != string::npos && nume_ingrediente[i] != "carne_" + comanda.getMeatType()) {
				nume_ingrediente[i] = "carne_" + comanda.getMeatType();
			}

			if (!stoc.VerificaStocProdus(nume_ingrediente[i], cant * cant_ingrediente[i])) {
				ok = 0;
				cout << "\nNu avem ingrediente necesare pentru preparatul " << p.getNumePreparat() << ". Nu este suficient: " << nume_ingrediente[i] << ".";
			}
		}

		if (ok) {
			for (int i = 0; i < p.getNrIngrediente(); i++) {
				stoc.actualizeazaStoc(nume_ingrediente[i], cant * cant_ingrediente[i]);
			}

			for (int i = 0; i < cant; i++) { comanda + p; }
			return true;
		}

		return false;
	}

};

int Comanda::ultimulIdUtilizat = 0;

void main()
{
	Meniu meniu;
	meniu.startMeniu(meniu);

}