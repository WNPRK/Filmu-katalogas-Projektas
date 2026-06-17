#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <cctype>

using namespace std;

// Filmo duomenų struktūra
struct Filmas {
    int id;
    string pavadinimas;
    string rezisierius;
    string zanras;
    int metai;
    int trukme; // minutėmis
};

// Funkcija, skirta paversti tekstą mažosiomis raidėmis (paieškai)
string paverstiMazosiomis(string tekstas) {
    transform(tekstas.begin(), tekstas.end(), tekstas.begin(), [](unsigned char c) {
        return tolower(c);
        });
    return tekstas;
}

// Duomenų nuskaitymas iš failo
vector<Filmas> nuskaitytiIsFailo(const string& failoVardas) {
    vector<Filmas> filmai;
    ifstream failas(failoVardas);
    if (!failas.is_open()) return filmai;

    string eilute;
    while (getline(failas, eilute)) {
        if (eilute.empty()) continue;
        stringstream ss(eilute);
        string idStr, pav, rez, zan, metaiStr, trukmeStr;

        getline(ss, idStr, ';');
        getline(ss, pav, ';');
        getline(ss, rez, ';');
        getline(ss, zan, ';');
        getline(ss, metaiStr, ';');
        getline(ss, trukmeStr, ';');

        Filmas f;
        f.id = stoi(idStr);
        f.pavadinimas = pav;
        f.rezisierius = rez;
        f.zanras = zan;
        f.metai = stoi(metaiStr);
        f.trukme = stoi(trukmeStr);
        filmai.push_back(f);
    }
    failas.close();
    return filmai;
}

// Duomenų įrašymas į failą
void irasytiIFaila(const string& failoVardas, const vector<Filmas>& filmai) {
    ofstream failas(failoVardas);
    for (const auto& f : filmai) {
        failas << f.id << ";" << f.pavadinimas << ";" << f.rezisierius << ";"
            << f.zanras << ";" << f.metai << ";" << f.trukme << "\n";
    }
    failas.close();
}

// READ: Viso katalogo rodymas lentelėje
void rodytiVisus(const vector<Filmas>& filmai) {
    if (filmai.empty()) {
        cout << "\nKatalogas yra tuscias.\n";
        return;
    }
    cout << "\n============================================================================================================================\n";
    printf("%-4s | %-32s | %-28s | %-11s | %-5s | %s\n", "ID", "Pavadinimas", "Rezisierius", "Zanras", "Metai", "Trukme (min / val)");
    cout << "----------------------------------------------------------------------------------------------------------------------------\n";

    for (const auto& f : filmai) {
        int valandos = f.trukme / 60;
        int minutes = f.trukme % 60;

        printf("%-4d | %-32s | %-28s | %-11s | %-5d | %d min / %dh %02dmin\n",
            f.id, f.pavadinimas.c_str(), f.rezisierius.c_str(), f.zanras.c_str(), f.metai, f.trukme, valandos, minutes);
    }
    cout << "============================================================================================================================\n";
}

// CREATE: Naujo filmo pridėjimas
void pridetiFilma(vector<Filmas>& filmai, const string& failoVardas) {
    Filmas f;
    f.id = filmai.empty() ? 1 : filmai.back().id + 1;

    cout << "\n--- Naujo filmo pridejimas ---\n";
    cout << "Iveskite pavadinima: ";
    cin.ignore();
    getline(cin, f.pavadinimas);
    cout << "Iveskite rezisieriu: ";
    getline(cin, f.rezisierius);
    cout << "Iveskite zanra: ";
    getline(cin, f.zanras);
    cout << "Iveskite isleidimo metus: ";
    cin >> f.metai;
    cout << "Iveskite trukme (minutemis): ";
    cin >> f.trukme;

    filmai.push_back(f);
    irasytiIFaila(failoVardas, filmai);
    cout << "\nFilmas sekmingai pridetas!\n";
}

// UPDATE: Filmo redagavimas pagal ID
void redaguotiFilma(vector<Filmas>& filmai, const string& failoVardas) {
    int id;
    cout << "\nIveskite filmo ID, kuri norite redaguoti: ";
    cin >> id;

    for (auto& f : filmai) {
        if (f.id == id) {
            cout << "\nRastas filmas: " << f.pavadinimas << "\n";
            cout << "Iveskite nauja pavadinima (arba palikite senaji): ";
            cin.ignore();
            string naujasPav;
            getline(cin, naujasPav);
            if (!naujasPav.empty()) f.pavadinimas = naujasPav;

            cout << "Iveskite nauja rezisieriu: ";
            string naujasRez;
            getline(cin, naujasRez);
            if (!naujasRez.empty()) f.rezisierius = naujasRez;

            cout << "Iveskite nauja zanra: ";
            string naujasZan;
            getline(cin, naujasZan);
            if (!naujasZan.empty()) f.zanras = naujasZan;

            cout << "Iveskite naujus metus (0 - nekeisti): ";
            int naujiMetai;
            cin >> naujiMetai;
            if (naujiMetai != 0) f.metai = naujiMetai;

            cout << "Iveskite nauja trukme minutemis (0 - nekeisti): ";
            int naujaTrukme;
            cin >> naujaTrukme;
            if (naujaTrukme != 0) f.trukme = naujaTrukme;

            irasytiIFaila(failoVardas, filmai);
            cout << "\nFilmo duomenys atnaujinti!\n";
            return;
        }
    }
    cout << "\nFilmas su ID " << id << " nerastas.\n";
}

// DELETE: Filmo trynimas pagal ID
void istrintiFilma(vector<Filmas>& filmai, const string& failoVardas) {
    int id;
    cout << "\nIveskite filmo ID, kuri norite istrinti: ";
    cin >> id;

    for (auto it = filmai.begin(); it != filmai.end(); ++it) {
        if (it->id == id) {
            cout << "\nFilmas \"" << it->pavadinimas << "\" pasalinamas.\n";
            filmai.erase(it);
            irasytiIFaila(failoVardas, filmai);
            cout << "Filmas sekmingai istrintas!\n";
            return;
        }
    }
    cout << "\nFilmas su ID " << id << " nerastas.\n";
}

// Išmani paieška (neveikia didžiosios/mažosios raidės)
void filtruotiIrIeskoti(const vector<Filmas>& filmai) {
    if (filmai.empty()) {
        cout << "\nKatalogas tuscias, nera ko ieskoti.\n";
        return;
    }

    cout << "\nIveskite filmo pavadinimo arba zanro dali paieskai: ";
    cin.ignore();
    string fraze;
    getline(cin, fraze);
    string ieskomaFraze = paverstiMazosiomis(fraze);

    bool rasta = false;

    cout << "\n============================================================================================================================\n";
    printf("%-4s | %-32s | %-28s | %-11s | %-5s | %s\n", "ID", "Pavadinimas", "Rezisierius", "Zanras", "Metai", "Trukme (min / val)");
    cout << "----------------------------------------------------------------------------------------------------------------------------\n";

    for (const auto& f : filmai) {
        string pavMazosiomis = paverstiMazosiomis(f.pavadinimas);
        string zanMazosiomis = paverstiMazosiomis(f.zanras);

        // Tikriname, ar pavadinime arba žanre yra ieškoma frazė
        if (pavMazosiomis.find(ieskomaFraze) != string::npos || zanMazosiomis.find(ieskomaFraze) != string::npos) {
            int valandos = f.trukme / 60;
            int minutes = f.trukme % 60;

            printf("%-4d | %-32s | %-28s | %-11s | %-5d | %d min / %dh %02dmin\n",
                f.id, f.pavadinimas.c_str(), f.rezisierius.c_str(), f.zanras.c_str(), f.metai, f.trukme, valandos, minutes);
            rasta = true;
        }
    }
    cout << "============================================================================================================================\n";

    if (!rasta) {
        cout << "Pagal jusu uzklausa \"" << fraze << "\" nieko nerasta.\n";
    }
}

// Statistikos skaičiavimas
void rodytiStatistika(const vector<Filmas>& filmai) {
    if (filmai.empty()) {
        cout << "\nKatalogas tuscias, statistika negalima.\n";
        return;
    }

    int bendraTrukme = 0;
    const Filmas* seniausias = &filmai[0];
    const Filmas* naujausias = &filmai[0];

    for (const auto& f : filmai) {
        bendraTrukme += f.trukme;
        if (f.metai < seniausias->metai) seniausias = &f;
        if (f.metai > naujausias->metai) naujausias = &f;
    }

    double vidurkis = (double)bendraTrukme / filmai.size();

    cout << "\n======= KATALOGO STATISTIKA =======\n";
    cout << "Is viso filmu kataloge: " << filmai.size() << " vnt.\n";
    cout << "Bendra visu filmu trukme: " << bendraTrukme << " min.\n";
    printf("Vidutine filmo trukme: %.1f min.\n", vidurkis);
    cout << "Seniausias filmas: " << seniausias->pavadinimas << " (" << seniausias->metai << " m.)\n";
    cout << "Naujausias filmas: " << naujausias->pavadinimas << " (" << naujausias->metai << " m.)\n";
    cout << "===================================\n";
}

int main() {
    const string failoVardas = "filmai.txt";
    vector<Filmas> filmai = nuskaitytiIsFailo(failoVardas);

    int pasirinkimas = 0;
    do {
        cout << "\n--- FILMU KATALOGO VALDYMAS ---\n";
        cout << "1. Rodyti visus filmus\n";
        cout << "2. Prideti nauja filma\n";
        cout << "3. Redaguoti filma pagal ID\n";
        cout << "4. Istrinti filma pagal ID\n";
        cout << "5. Paieska pagal pavadinima/zanra\n";
        cout << "6. Ziureti katalogo statistika\n";
        cout << "7. Iseeiti is programos\n";
        cout << "Pasirinkite veiksma (1-7): ";
        cin >> pasirinkimas;

        switch (pasirinkimas) {
        case 1: rodytiVisus(filmai); break;
        case 2: pridetiFilma(filmai, failoVardas); break;
        case 3: redaguotiFilma(filmai, failoVardas); break;
        case 4: istrintiFilma(filmai, failoVardas); break;
        case 5: filtruotiIrIeskoti(filmai); break;
        case 6: rodytiStatistika(filmai); break;
        case 7: cout << "\nDarbas baigtas. Geros dienos!\n"; break;
        default: cout << "\nNeteisingas pasirinkimas. Bandykite dar karta.\n";
        }
    } while (pasirinkimas != 7);

    return 0;
}