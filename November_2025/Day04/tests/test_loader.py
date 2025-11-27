import sys, os
sys.path.append(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))

from engine.loader import load_data

def test_load_data():
    df = load_data()

    assert df is not None
    assert len(df) > 0
    for col in ["sport", "style", "color", "cut", "price"]:
        assert col in df.columns