# 🎯 Day 02 — Fanwear Recommender System  
### *Mini-moteur de recommandation (CLI + API Flask)*

Ce projet implémente un **système de recommandation intelligent** pour fanwear féminin.  
L’objectif : proposer des articles pertinents en fonction des **préférences sportives, stylistiques et budgétaires** d’une utilisatrice.

Ce mini moteur se compose de :

- un module de **chargement des données** (loader)
- un module de **filtrage** (filters)
- un module de **scoring** (scoring)
- un **recommender engine**
- une interface en **CLI**
- une **API Flask** permettant de faire des requêtes HTTP

Le tout constitue un MVP solide, prêt pour un prototypage rapide ou une intégration ultérieure dans une interface web.

---

## 📁 **Structure du projet**
```` 
Day02/
│── api
│       └── app.py            # API Flask
│── data/
│     └── fanwear_items.csv   # Dataset d’exemple
│
│── cli/
│     └── recommend.py     # Interface en ligne de commande
│
│── engine/
│     ├── loader.py        # Chargement du CSV
│     ├── filters.py       # Filtrage intelligent des items
│     ├── scoring.py       # Système de score pondéré
│     └── recommender.py   # Moteur principal de recommandation
│
└── README.md
````
---

# 📊 **Dataset**

Le fichier `fanwear_items.csv` contient des articles décrits par plusieurs colonnes :

- `item_name`
- `sport`
- `style`
- `color`
- `cut`
- `budget`
- `influence` *(optionnel)*

Un utilisateur peut être comparé à ces attributs afin d’obtenir des recommandations personnalisées.

---

# ⚙️ **Fonctionnement du moteur**

## 🔍 1. Filtrage
Les préférences de l'utilisatrice sont appliquées pour réduire le dataset :

- sport (matching exact + insensible à la casse)
- style
- couleur
- type de coupe
- budget max
- influence (ex : fighter préféré, joueur)

Le système ignore les critères non fournis.

---

## ⭐ 2. Scoring
Chaque item filtré reçoit un score basé sur :

- correspondance sport  
- correspondance style  
- couleur  
- coupe  
- respect du budget  
- influences  

Chaque critère rapportant un nombre de points défini.  
Le moteur renvoie les articles triés du meilleur au moins bon.

---

## 📌 3. Recommandation finale
Le module `recommend_items()` retourne :

- un DataFrame OR une liste d’items  
- chaque item annoté avec un `score`
- trié par score décroissant
- prêt à être renvoyé via API / CLI

---

# 🖥️ **CLI — Ligne de commande**

Tu peux appeler le recommender directement depuis le terminal :

### ▶️ **Exemple :**
```bash
python3 cli/recommend.py –sport boxing –style techwear –budget 150
```
### Paramètres disponibles :

- `--sport`
- `--style`
- `--color`
- `--cut`
- `--budget`
- `--influence`

### Sortie :
Une liste d’articles recommandés avec leur score.

---

# 🌐 **API Flask**

### ▶️ Lancer le serveur

Depuis la racine :
```bash
python3 app.py
```
Tu verras :

```bash
Running on http://127.0.0.1:5000
```

---

## 📡 **GET /recommend**

Permet de récupérer des recommandations via HTTP.

### Exemple :
http://127.0.0.1:5000/recommend?sport=boxing&style=techwear&budget=150

### Paramètres GET :

| Query param | Description |
|-------------|-------------|
| sport       | sport préféré |
| style       | style vestimentaire |
| color       | couleur souhaitée |
| cut         | coupe de vêtement |
| budget      | budget max |
| influence   | optional (athlète / personnage / équipe) |

### Réponse JSON :

```json
[
  {
    "item_name": "Techwear Fighter Jacket",
    "sport": "boxing",
    "style": "techwear",
    "color": "black",
    "budget": 120,
    "score": 87
  },
  ...
]
```
La réponse s’adapte automatiquement selon que le moteur renvoie une liste ou un DataFrame.
