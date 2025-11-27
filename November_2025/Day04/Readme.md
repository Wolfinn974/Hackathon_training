# 💜Recommender Engine — Hackathon Training

## Python · FastAPI · Streamlit · CSV ML-like scoring
Un moteur de recommandation complet construit pour le training d'un Hackathon :
→ API propre
→ UI utilisateur
→ Scoring & filtres avancés
→ Tests + CI
→ Docker-ready

---

### 🚀 Fonctionnalités

#### 🔍 Recommender Engine
	•	Filtrage sur : sport, style, color, cut, budget, influence
	•	Scoring intelligent
	•	Tri top-N
	•	Export CSV

### 🌐 API FastAPI

Endpoints :
	•	GET /recommend
	•	POST /recommend/json
	•	GET /health
	•	GET /stats
	•	GET /top

CORS activé, JSON clean.

### 🎨 UI Streamlit

Application web simple :
	•	Formulaire → préférences
	•	Résultats triés
	•	Scores visibles
	•	Option “Surprise me!”

### 🧪 Tests + Coverage
	•	Tests unitaires pour chaque module
	•	Tests API
	•	Couverture coverage run -m pytest

### 🐳 Docker
	•	API dans un conteneur
	•	Streamlit dans un autre
	•	docker-compose up pour lancer tout

---

## 📦 Installation

1) Cloner
2) Installer
```bash 
pip install -r requirements.txt
```

## ▶️ Lancer l’API
```bash
make run-api
```

API visible :
👉 http://localhost:8000/recommend

## 🎨 Lancer l’UI
```bash 
make run-ui
```
UI visible :
👉 http://localhost:8501

## 🧪 Tests & Coverage

```bash 
make test
make cover
```

## 🐳 Docker

Lancer toute l’architecture :
```bash 
docker-compose up --build
```
API → localhost:8000
UI → localhost:8501
## 🧱 Architecture

```bash
        +------------------------+
        |       Streamlit UI     |
        +------------+-----------+
                     |
                     v  HTTP GET/POST
        +------------+-----------+
        |         FastAPI API     |
        +------------+-----------+
                     |
                     v
        +------------------------+
        |   Recommender Engine   |
        | filters + scoring + df |
        +------------------------+
                     |
                     v
              fanwear_items.csv (dataset)
```