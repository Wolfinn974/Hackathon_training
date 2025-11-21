# 🗂️ Day 01 — Hackathon Training  
*Multi-language Data Analysis Engine (Python & C)*

Ce premier jour de training est consacré à la création d’un **mini moteur d’analyse de données**, appliqué à un dataset lié aux préférences fanwear & sports — un thème proche du hackathon *FemTech 2025*.

Objectifs :  
🔹 manipuler un dataset rapidement  
🔹 extraire des insights utiles  
🔹 réimplémenter les mêmes analyses en Python **et** en C  
🔹 monter en compétence sur le haut niveau (Python) et le bas niveau (C)

---

## 🎯 Objectifs du Jour 1

### ✔️ Python — Data Analyst Mode
- import / exploration d’un CSV  
- value counts  
- statistiques descriptives  
- visualisation (matplotlib)  
- pivot tables  
- analyse de combinaisons  

### ✔️ C — Moteur d’analyse “from scratch”
- parsing CSV via `strtok`  
- gestion mémoire (`malloc`, `realloc`, `free`)  
- tableaux dynamiques de `struct`  
- value_counts maison  
- moyennes (sum/count)  
- top combinaisons style+couleur  
- pivot table sport × style  
- export CSV  
- mini CLI (`./explorer --export`)

Aucun framework → C pur.

---

## 📁 Structure du dossier
```
day01/
├── python/
│   ├── analysis.py
│   └── data.csv
├── c/
│   ├── analysis.c
│   ├── data.c
│   ├── data.h
│   ├── main.c
│   ├── utils.c
│   ├── Makefile
│   └── data.csv
└── README.md
```

---

## 🔍 Analyses effectuées

### 🔹 Value Counts  
- styles les plus populaires  
- sports les plus représentés  

### 🔹 Budget moyen par style  
- calcul sum + count  
- classement par style  

### 🔹 Top combinaisons style + couleur  
- tri décroissant via `qsort`  

### 🔹 Pivot table sport × style  
Tableau croisé dynamique comptant le nombre d’occurrences.

### 🔹 Export CSV  
- `style_counts.csv`  
- `sport_counts.csv`  
- `pivot_sport_style.csv`  
- `top3_combos.csv`

---

## 🚀 Lancer les projets

### ▶️ Python

```bash
cd python
python3 analysis.py
```

###▶️ C

Compiler :
```bash
cd c
make
```
Analyse directe :
```bash
./explorer
```

Export CSV :
```bash
./explorer --export
```
---
## 🧠 Ce que couvre ce jour

🔹 Python
- nettoyage de données
- analyse statistique
- visualisation
- EDA rapide et efficace

🔹 C
- logique interne des outils de data science
- gestion mémoire avancée
- architecture multi-fichiers
- pointeurs, tableaux 2D, structures
- création d’un moteur d’analyse robuste et extensible

---

## ✨ Pourquoi ce training ?

Pour arriver au hackathon avec :
- des réflexes d’analyse
- de la structure dans ta réflexion technique
- la capacité de produire des insights rapidement
- une compréhension solide autant du haut niveau que du bas niveau

---

## 🏁 Statut
- Python ✔️
- C ✔️ (analysis + export + CLI)
- Java 🕒 à venir (Jour 2)