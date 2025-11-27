# 🐍 Day 03 — Streamlit Frontend + Recommender UI

## 🎯 Objectif du jour

Prendre le moteur de recommandation (Day 02) et en faire une application interactive, simple à utiliser, avec :
	•	une vraie interface Streamlit
	•	un formulaire de préférences
	•	un bouton “Recommander”
	•	un mode “Surprise Me”
	•	une visualisation des scores
	•	un bouton export CSV
	•	un Dark Theme sexy cyberpunk
	•	un code propre, modulaire, hackathon-ready

Ce frontend est l’interface finale que les organisateurs / mentors pourront tester.

---

## 🚀 Fonctionnalités incluses

### ✔️ Formulaire d’entrée (UI)

L’utilisateur peut sélectionner :
	•	sport préféré
	•	style
	•	couleur
	•	coupe
	•	budget
	•	influence (optionnel)

Chaque champ envoie ses valeurs au moteur Day02.

### ✔️ Recommandation dynamique

La fonction :
```bash
recommend_items(df, **prefs)
```
renvoie un DataFrame filtré + scoré.

L’UI affiche ensuite :
	•	les résultats triés
	•	le top 5 visuel
	•	un export CSV

---

### ✨ Surprise Me (recommandation aléatoire)

Un bouton spécial renvoie un article aléatoire du dataset.

Utile pour tester la diversité et surprendre les utilisatrices.

---

### 📊 Visualisation des scores (Altair)

Un graphique en barres affiche le top 5 des items recommandés en fonction du score.

---

### 📥 Export CSV

Les recommandations sont téléchargeables via :
```bash
st.download_button(...)
```
Permet d’envoyer les résultats au client ou à l’équipe business/design.

---

### 🌙 Style : Theme Dark Sexy (config Streamlit)

Créer un fichier :
```bash
Day03/.streamlit/config.toml
```
Avec : 
```bash
[theme]
base="dark"
primaryColor="#ff0055"
backgroundColor="#0d0d0d"
secondaryBackgroundColor="#1a1a1a"
textColor="#ffffff"
font="monospace"
```
---
## 🧩 Arborescence du projet
```bash
Day03/
│── engine/
│     ├── loader.py
│     ├── filters.py
│     ├── recommender.py
│     └── scoring.py
│
│── ui/
│     ├── app.py
│     └── ui.py
│
│── data/
│     └── fanwear_items.csv
│
└── README.md
```

---
## 🧪 Comment lancer

Dans le dossier Day03 :
```bash
streamlit run ui/streamlit_app.py
```