import pandas as pd
import sys, os
sys.path.append(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
from engine.recommender import scoring

def test_scoring_basic():
    item = pd.Series({
        "sport": "boxing",
        "style": "techwear",
        "color": "black",
        "cut": "oversized",
        "price": 100
    })

    prefs = {
        "sport": "boxing",
        "style": "techwear",
        "color": "black",
        "cut": "oversized",
        "budget": 150,
        "influence": None
    }

    score = scoring(item, prefs)

    assert isinstance(score, (int, float))
    assert score > 0