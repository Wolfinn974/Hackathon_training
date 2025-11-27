import argparse
import sys, os
sys.path.append(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
from engine.loader import load_data
from engine.recommender import recommend_items
import pandas as pd

parser = argparse.ArgumentParser(description="Fanwear Recommender CLI")

parser.add_argument("--sport")
parser.add_argument("--style")
parser.add_argument("--color")
parser.add_argument("--cut")
parser.add_argument("--budget", type=int)
parser.add_argument("--influence")

args = parser.parse_args()

df = load_data()

prefs = {
    "sport": args.sport,
    "style": args.style,
    "color": args.color,
    "cut": args.cut,
    "budget": args.budget,
    "influence": args.influence
}

results = recommend_items(df, **prefs)

if not len(results):
    print("No recommendations found.")
else:
    print("\nTOP 5 RECOMMENDATIONS\n")
    for _, row in results.iterrows():
        print(f"{row['style']} {row['sport']} - {row['price']}€ ({row['score']})")
