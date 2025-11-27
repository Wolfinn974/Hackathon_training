import pandas as pd
import os

BASE_DIR = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))

def load_data():
    csv_path = os.path.join(BASE_DIR, "data", "fanwear_items.csv")
    return pd.read_csv(csv_path)
