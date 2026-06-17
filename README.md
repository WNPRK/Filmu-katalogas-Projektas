# Struktūrinio programavimo projektas: Filmų katalogas

Sveiki! Tai mano struktūrinio programavimo kurso projektinis darbas – filmų valdymo programa, parašyta su C++. Programos tikslas buvo sukurti patogią sistemą, kuri leidžia tvarkyti filmų sąrašą konsolėje ir visus duomenis saugo tekstiniame faile, kad jie neišsitrintų išjungus programą.

## 💾 Kaip viskas veikia (Struktūra)
* Kodas parašytas naudojant standartinę C++ kalbą.
* Sukūriau specialią `struct Filmas` struktūrą, kurioje saugomi visi filmo duomenys (ID, pavadinimas, režisierius, žanras, metai, trukmė).
* Kadangi filmų skaičius gali keistis, visiems duomenims saugoti atmintyje panaudojau `std::vector`.
* Visi filmai automatiškai įrašomi ir nuskaitomi iš failo `filmai.txt`. Duomenis faile atskyriau naudojant kabliataškį (`;`).

## 🛠️ Ką programa geba daryti?
Programa palaiko visas pagrindines funkcijas (CRUD):
1. **Pridėti naują filmą** – vartotojas įveda duomenis, o programa pati sugeneruoja unikalų ID.
2. **Peržiūrėti katalogą** – visi filmai išspausdinami ekrane tvarkingoje lentelėje, kurioje nesubėga rėmeliai.
3. **Redaguoti filmą** – galima surasti filmą pagal jo ID ir pakeisti jo informaciją.
4. **Ištrinti filmą** – pašalina filmą iš sąrašo pagal ID ir atnaujina failą.

### 🌟 Papildomi patobulinimai, kuriuos pridėjau:
* **Paieška, nujautri raidžių dydžiui:** Patobulinau paieškos funkciją. Dabar nesvarbu, ar vartotojas parašys „AVATARAS“, ar „avataras“ – programa vis tiek suras filmą (naudojama funkcija, kuri laikinai paverčia tekstą mažosiomis raidėmis).
* **Katalogo statistika:** Programa moka paskaičiuoti bendrą filmų skaičių, filmų trukmės vidurkį minutėmis, taip pat suranda patį seniausią ir naujausią filmą sąraše.
* **Trukme valandomis:** UI ekrane filmo trukmė automatiškai konvertuojama ir rodoma valandomis bei minutėmis (pvz., vietoj `150 min` rodo `2h 30min`).