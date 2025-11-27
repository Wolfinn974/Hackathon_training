from fastapi import APIRouter, Query
from api.validator import Preferences
import sys, os
sys.path.append(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
from engine.loader import load_data
from engine.recommender import recommend_items

router = APIRouter(prefix="/api", tags=["Recommender"])

df = load_data()

@router.get("/recommend")
def recommend(preferences: Preferences = Query(...)):
    result = recommend_items(df, **preferences.dict())
    return result.to_dict(orient="records")


@router.post("/recommend-json")
def recommend_json(preferences: Preferences):
    results = recommend_items(df, **preferences.dict())
    return results.to_dict(orient="records")

@router.get("/health")
def health():
    return {"status": "ok", "rows_loaded": len(df)}

@router.get("/stats")
def stats():
    return {
        "sports": df["sport"].value_counts().to_dict(),
        "styles": df["style"].value_counts().to_dict(),
        "avg_price_by_style": df.groupby("style")["price"].mean().round(2).to_dict(),
        "dataset_size": len(df)
    }
@router.get("/top")
def top(n: int = 3):
    return {
        "top_styles": df["style"].value_counts().head(n).to_dict(),
        "top_sports": df["sport"].value_counts().head(n).to_dict(),
        "top_colors": df["color"].value_counts().head(n).to_dict(),
    }