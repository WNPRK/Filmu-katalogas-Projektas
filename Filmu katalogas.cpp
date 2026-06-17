#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>
#include <algorithm> // Reikalinga ctolower funkcijai

using namespace std;

// Vartotojo sukurta struktūra (struct)
struct Filmas {
    int id;
    string pavadinimas;
    string rezisierius;
    string zanras;
    int metai;
    int trukme;
};

// Pagalbinė funkcija raidžių dydžio ignoravimui
string paverstiMazosiomis(string tekstas);

// Funkcijų prototipai – BE VOID
bool nuskaitytiIsFailo(vector<Filmas>& filmuSarasas, const string& failoVardas);
bool issaugotiIFaila(const vector<Filmas>& filmuSarasas, const string& failoVardas);
int rodytiVisus(const vector<Filmas>& filmuSarasas);
int pridetiNauja(vector<Filmas>& filmuSarasas);
bool redaguotiIrasa(vector<Filmas>& filmuSarasas);
bool istrintiIrasa(vector<Filmas>& filmuSarasas);

// Papildomos funkcijos 
int filtruotiIrIeskoti(const vector<Filmas>& filmuSarasas); // Atnaujinta paieška
double skaiciuotiStatistika(const vector<Filmas>& filmuSarasas);

int main() {
    vector<Filmas> filmuSarasas;
    string failoVardas = "filmai.txt";

    if (!nuskaitytiIsFailo(filmuSarasas, failoVardas)) {
        cout << "Nepavyko uzkrauti pradiniu duomenu!\n";
    }

    int pasirinkimas;
    do {
        cout << "\n=== FILMU KATALOGO SISTEMA ===\n";
        cout << "[1] Perziureti visus filmus (Read)\n";
        cout << "[2] Prideti nauja filma (Create)\n";
        cout << "[3] Redaguoti filmo duomenis (Update)\n";
        cout << "[4] Istrinti filma is katalogo (Delete)\n";
        cout << "[5] Paieska pagal pavadinima arba zanra (Papildoma 1)\n";
        cout << "[6] Rodyti katalogo statistika (Papildoma 2)\n";
        cout << "[0] Iseiti ir issaugoti pakeitimus\n";
        cout << "Pasirinkite veiksma: ";
        cin >> pasirinkimas;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Klaida! Iveskite skaiciu nuo 0 iki 6.\n";
            continue;
        }

        switch (pasirinkimas) {
        case 1: {
            int atspausdinta = rodytiVisus(filmuSarasas);
            cout << "Is viso parodyta filmu: " << atspausdinta << "\n";
            break;
        }
        case 2: {
            int naujasId = pridetiNauja(filmuSarasas);
            cout << "Filmas sekmingai pridetas! Priskirtas ID: " << naujasId << "\n";
            break;
        }
        case 3:
            if (redaguotiIrasa(filmuSarasas)) {
                cout << "Filmo duomenys sekmingai atnaujinti!\n";
            }
            else {
                cout << "Klaida: Filmas nerastas arba neatnaujintas.\n";
            }
            break;
        case 4:
            if (istrintiIrasa(filmuSarasas)) {
                cout << "Filmas sekmingai pasalintas.\n";
            }
            else {
                cout << "Klaida: Nepavyko rasti filmo su tokiu ID.\n";
            }
            break;
        case 5: {
            int rastaKiekis = filtruotiIrIeskoti(filmuSarasas);
            cout << "Is viso rasta atitikmenu: " << rastaKiekis << "\n";
            break;
        }
        case 6: {
            double vidurkis = skaiciuotiStatistika(filmuSarasas);
            if (vidurkis > 0) {
                cout << "Statistika sekmingai apskaiciuota.\n";
            }
            break;
        }
        case 0:
            if (issaugotiIFaila(filmuSarasas, failoVardas)) {
                cout << "Pakeitimai issaugoti faile. Viso gero!\n";
            }
            else {
                cout << "Klaida: Nepavyko issaugoti duomenu!\n";
            }
            break;
        default:
            cout << "Tokio pasirinkimo nera. Bandykite dar karta.\n";
        }
    } while (pasirinkimas != 0);

    return 0;
}

// PAGALBINĖ FUNKCIJA: Paverčia bet kokį tekstą mažosiomis raidėmis
string paverstiMazosiomis(string tekstas) {
    for (size_t i = 0; i < tekstas.length(); i++) {
        tekstas[i] = tolower(tekstas[i]);
    }
    return tekstas;
}

// 1. DUOMENŲ NUSKAITYMAS
bool nuskaitytiIsFailo(vector<Filmas>& filmuSarasas, const string& failoVardas) {
    ifstream failas(failoVardas);
    if (!failas.is_open()) {
        return false;
    }

    filmuSarasas.clear();
    string eilute;

    while (getline(failas, eilute)) {
        if (eilute.empty()) continue;

        stringstream ss(eilute);
        string idStr, pavadinimas, rezisierius, zanras, metaiStr, trukmeStr;

        if (getline(ss, idStr, ';') &&
            getline(ss, pavadinimas, ';') &&
            getline(ss, rezisierius, ';') &&
            getline(ss, zanras, ';') &&
            getline(ss, metaiStr, ';') &&
            getline(ss, trukmeStr, ';')) {

            Filmas f;
            f.id = stoi(idStr);
            f.pavadinimas = pavadinimas;
            f.rezisierius = rezisierius;
            f.zanras = zanras;
            f.metai = stoi(metaiStr);
            f.trukme = stoi(trukmeStr);

            filmuSarasas.push_back(f);
        }
    }
    failas.close();
    return true;
}

// 2. DUOMENŲ ĮRAŠYMAS
bool issaugotiIFaila(const vector<Filmas>& filmuSarasas, const string& failoVardas) {
    ofstream failas(failoVardas);
    if (!failas.is_open()) {
        return false;
    }

    for (const auto& f : filmuSarasas) {
        failas << f.id << ";" << f.pavadinimas << ";" << f.rezisierius << ";"
            << f.zanras << ";" << f.metai << ";" << f.trukme << "\n";
    }
    failas.close();
    return true;
}

// 3. READ 
int rodytiVisus(const vector<Filmas>& filmuSarasas) {
    if (filmuSarasas.empty()) {
        cout << "Katalogas yra tuscias.\n";
        return 0;
    }

    cout << "\n---------------------------------------------------------------------------------------------------------\n";
    cout << "ID   | Pavadinimas                      | Rezisierius                  | Zanras      | Metai | Trukme\n";
    cout << "---------------------------------------------------------------------------------------------------------\n";
    for (const auto& f : filmuSarasas) {
        printf("%-4d | %-32s | %-28s | %-11s | %-5d | %d min.\n",
            f.id, f.pavadinimas.c_str(), f.rezisierius.c_str(), f.zanras.c_str(), f.metai, f.trukme);
    }
    cout << "---------------------------------------------------------------------------------------------------------\n";

    return filmuSarasas.size();
}

// 4. CREATE
int pridetiNauja(vector<Filmas>& filmuSarasas) {
    Filmas naujas;

    if (filmuSarasas.empty()) {
        naujas.id = 1;
    }
    else {
        int maxId = filmuSarasas[0].id;
        for (const auto& f : filmuSarasas) {
            if (f.id > maxId) maxId = f.id;
        }
        naujas.id = maxId + 1;
    }

    cout << "Iveskite filmo pavadinima: ";
    cin.ignore();
    getline(cin, naujas.pavadinimas);
    cout << "Iveskite rezisieriu: ";
    getline(cin, naujas.rezisierius);
    cout << "Iveskite zanra: ";
    cin >> naujas.zanras;
    cout << "Iveskite isleidimo metus: ";
    cin >> naujas.metai;
    cout << "Iveskite trukme (minutemis): ";
    cin >> naujas.trukme;

    filmuSarasas.push_back(naujas);
    return naujas.id;
}

// 5. UPDATE
bool redaguotiIrasa(vector<Filmas>& filmuSarasas) {
    int ieskomasId;
    cout << "Iveskite filmo ID, kuri norite redaguoti: ";
    cin >> ieskomasId;

    for (auto& f : filmuSarasas) {
        if (f.id == ieskomasId) {
            cout << "Rastas filmas: " << f.pavadinimas << "\n";
            cout << "Iveskite nauja pavadinima: ";
            cin.ignore();
            getline(cin, f.pavadinimas);
            cout << "Iveskite nauja rezisieriu: ";
            getline(cin, f.rezisierius);
            cout << "Iveskite nauja zanra: ";
            cin >> f.zanras;
            cout << "Iveskite naujus metus: ";
            cin >> f.metai;
            cout << "Iveskite nauja trukme (min.): ";
            cin >> f.trukme;
            return true;
        }
    }
    return false;
}

// 6. DELETE
bool istrintiIrasa(vector<Filmas>& filmuSarasas) {
    int ieskomasId;
    cout << "Iveskite filmo ID, kuri norite istrinti: ";
    cin >> ieskomasId;

    for (auto it = filmuSarasas.begin(); it != filmuSarasas.end(); ++it) {
        if (it->id == ieskomasId) {
            cout << "Filmas \"" << it->pavadinimas << "\" pasalinamas...\n";
            filmuSarasas.erase(it);
            return true;
        }
    }
    return false;
}

// 7. PAPILDOMA 1: SVEIKINGA PAIEŠKA (Ignoruoja didžiąsias/mažąsias raides ir ieško pagal abu kriterijus!)
int filtruotiIrIeskoti(const vector<Filmas>& filmuSarasas) {
    string uzklausa;
    cout << "Iveskite filmo pavadinimo arba zanro dali: ";
    cin.ignore();
    getline(cin, uzklausa);

    // Paverčiame vartotojo įvestį mažosiomis raidėmis
    string uzklausaMazosiomis = paverstiMazosiomis(uzklausa);

    int rastaKiekis = 0;
    cout << "\nPaieskos rezultatai pagal uzklausa '" << uzklausa << "':\n";
    cout << "---------------------------------------------------------------------------------------------------------\n";
    cout << "ID   | Pavadinimas                      | Rezisierius                  | Zanras      | Metai | Trukme\n";
    cout << "---------------------------------------------------------------------------------------------------------\n";

    for (const auto& f : filmuSarasas) {
        // Paverčiame esamo filmo pavadinimą ir žanrą mažosiomis raidėmis tik palyginimui
        string pavadinimasMazosiomis = paverstiMazosiomis(f.pavadinimas);
        string zanrasMazosiomis = paverstiMazosiomis(f.zanras);

        // npos reiškia, kad tekstas buvo surastas (nebūtinai identiškas, gali būti ir žodžio dalis!)
        if (pavadinimasMazosiomis.find(uzklausaMazosiomis) != string::npos ||
            zanrasMazosiomis.find(uzklausaMazosiomis) != string::npos) {

            printf("%-4d | %-32s | %-28s | %-11s | %-5d | %d min.\n",
                f.id, f.pavadinimas.c_str(), f.rezisierius.c_str(), f.zanras.c_str(), f.metai, f.trukme);
            rastaKiekis++;
        }
    }

    if (rastaKiekis == 0) {
        cout << "Atitikmenu kataloge nerasta.\n";
    }
    cout << "---------------------------------------------------------------------------------------------------------\n";

    return rastaKiekis;
}

// 8. PAPILDOMA 2: STATISTIKA
double skaiciuotiStatistika(const vector<Filmas>& filmuSarasas) {
    if (filmuSarasas.empty()) {
        cout << "Katalogas tuscias, statistika negalima.\n";
        return 0.0;
    }

    int kiekis = filmuSarasas.size();
    int bendraTrukme = 0;
    int seniausiMetai = filmuSarasas[0].metai;
    int naujausiMetai = filmuSarasas[0].metai;

    for (const auto& f : filmuSarasas) {
        bendraTrukme += f.trukme;
        if (f.metai < seniausiMetai) seniausiMetai = f.metai;
        if (f.metai > naujausiMetai) naujausiMetai = f.metai;
    }

    double vidurkis = (double)bendraTrukme / kiekis;

    cout << "\n====== KATALOGO STATISTIKA ======\n";
    cout << "Is viso filmu kataloge: " << kiekis << " vnt.\n";
    cout << "Bendra visu filmu trukme: " << bendraTrukme << " min.\n";
    cout << "Vidutine filmo trukme: " << fixed << setprecision(1) << vidurkis << " min.\n";
    cout << "Seniausias filmas isleistas: " << seniausiMetai << " m.\n";
    cout << "Naujausias filmas isleistas: " << naujausiMetai << " m.\n";
    cout << "=================================\n";

    return vidurkis;
}