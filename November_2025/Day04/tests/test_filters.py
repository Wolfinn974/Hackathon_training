import pandas as pd
import sys, os
sys.path.append(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
from engine.filters import filter_items

def test_filter_by_sport():
    df = pd.DataFrame([
        {"sport": "boxing", "style": "techwear"},
        {"sport": "running", "style": "streetwear"}
    ])

    filtered = filter_items(df, sport="boxing")
    assert len(filtered) == 1
    assert filtered.iloc[0]["sport"] == "boxing"
def test_filter_by_style_and_color():
    df = pd.DataFrame([
        {"sport": "boxing", "style": "techwear", "color": "black"},
        {"sport": "boxing", "style": "techwear", "color": "red"}
    ])

    filtered = filter_items(df, style="techwear", color="black")
    assert len(filtered) == 1
    assert filtered.iloc[0]["color"] == "black"