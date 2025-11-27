from fastapi.testclient import TestClient
import sys, os
sys.path.append(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
from api.main import app

client = TestClient(app)

def test_health():
    r = client.get("/api/health")
    assert r.status_code == 200
    assert r.json()["status"] == "ok"

def test_recommend_get():
    r = client.get("/api/recommend?sport=boxing&budget=150")
    assert r.status_code == 200
    assert isinstance(r.json(), list)

def test_recommend_post():
    payload = {
        "sport": "boxing",
        "budget": 150
    }

    r = client.post("/api/recommend-json", json=payload)

    assert r.status_code == 200
    assert isinstance(r.json(), list)

def test_stats():
    r = client.get("/api/stats")
    assert r.status_code == 200
    data = r.json()

    assert "sports" in data
    assert "styles" in data
    assert "avg_price_by_style" in data

def test_top():
    r = client.get("/api/top?n=3")
    assert r.status_code == 200
    data = r.json()

    assert "top_styles" in data
    assert "top_sports" in data
