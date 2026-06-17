# 1. Projekto pavadinimas
Struktūrinio programavimo projektinis darbas: Filmų valdymo sistema (Katalogas)

---

## 2. Projekto tikslas
Sukurti veikiančią C++ konsolinę programą, skirtą struktūrizuotų duomenų valdymui, pritaikant kurso metu įgytas žinias: darbą su funkcijomis, srautais (duomenų skaitymu/įrašymu į failus), vartotojo sukurtomis struktūromis (`struct`) ir dinaminėmis kolekcijomis (`std::vector`).

---

## 3. Pasirinktos temos aprašymas
Projektui pasirinkta tema – **Filmų katalogas**. Programa skirta patogiam filmų duomenų (tokių kaip pavadinimas, režisierius, žanras, leidimo metai bei trukmė) saugojimui ir redagavimui. Ši sistema leidžia vartotojui greitai peržiūrėti esamą filmų sąrašą, pridėti naujus filmus, keisti jų informaciją arba pašalinti pasenusius įrašus tiesiai per konsolę.

---

## 4. Programos funkcionalumo aprašymas (CRUD)
Aplikacijoje pilnai realizuotas standartinis duomenų valdymo ciklas (CRUD):
* **Create (Sukurti):** Vartotojas gali įvesti naujo filmo duomenis. Programa automatiškai suranda paskutinį ID ir sugeneruoja naują unikalų ID (+1).
* **Read (Skaityti):** Visi kataloge esantys filmai išvedami į ekraną tvarkingai suformatuotoje ir išlygiuotoje lentelėje.
* **Update (Redaguoti):** Įvedus filmo ID, galima pakeisti jo informaciją. Paspaudus „Enter“ ir palikus laukelį tuščią (arba įvedus 0), išlaikomi senieji duomenys.
* **Delete (Ištrinti):** Vartotojas gali visiškai pašalinti filmą iš sistemos įvesdamas jo ID. Duomenų vektorius atnaujinamas ir failas perrašomas iš naujo.

---

## 5. Naudojamų failų aprašymas
* **`main.cpp`** – pagrindinis programinio kodo failas, kuriame realizuotos visos funkcijos ir meniu valdymas.
* **`filmai.txt`** – tekstinis duomenų failas, kuriame saugoma visa informacija apie filmus. 
  * Duomenys saugomi struktūrizuotu formatu, kur kiekvienas filmo bruožas yra atskirtas kabliataškiu (`;`).
  * Pavyzdys: `1;Avataras;James Cameron;Sci-Fi;2009;162`
  * Pradiniame faile yra paruošta ne mažiau kaip 15 įrašų.

---

## 6. Papildomų funkcijų aprašymas
Programa turi dvi papildomas duomenų apdorojimo funkcijas:
1. **Išmani paieška (Raidžių dydžio ignoravimas):** Vartotojas gali ieškoti filmo pagal pavadinimo arba žanro dalį. Paieška konvertuoja tekstą į mažąsias raides, todėl suranda filmą nepriklausomai nuo to, ar vartotojas įvedė didžiąsias, ar mažąsias raides (pvz., įvedus „sci-fi“, suras „Sci-Fi“).
2. **Katalogo statistika:** Programa automatiškai apskaičiuoja ir ekrane parodo bendrą filmų skaičių, bendrą trukmę, vidutinę filmų trukmę (su kableliu) bei suranda kraštines reikšmes – patį seniausią ir patį naujausią filmą kataloge.
3. **Laiko formatavimas:** Ekrane filmo trukmė automatiškai konvertuojama iš minučių į valandas ir minutes (pvz., `150 min / 2h 30min`), kad vartotojui būtų patogiau skaityti.

---

## 7. Programos paleidimo instrukcija
Projektas sukurtas naudojant standartinę C++ kalbą ir gali būti paleistas per bet kurią IDE (pvz., *Visual Studio*) arba sukompiliuotas rankiniu būdu per terminalą.

Kompiliavimo ir paleidimo komandos per terminalą:
```bash
# Kompiliavimas
g++ main.cpp -o programa

# Paleidimas (Windows)
programa.exe

# Paleidimas (Linux / Mac)
./programa