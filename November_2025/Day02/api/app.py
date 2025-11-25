from flask import Flask, request, jsonify
import sys, os
sys.path.append(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
from engine.loader import load_data
from engine.recommender import recommend_items

app = Flask(__name__)
df = load_data()

# endpoint
@app.get("/recommend")
def api_recommend():
    #arg list
    prefs = {
        "sport": request.args.get("sport"),
        "style": request.args.get("style"),
        "color": request.args.get("color"),
        "cut": request.args.get("cut"),
        "budget": request.args.get("budget", type=int),
        "influence": request.args.get("influence"),
    }

    results = recommend_items(df, **prefs)

    if isinstance(results, list):
        return jsonify(results)

    # if dataframe --> convert it
    return jsonify(results.to_dict(orient="records"))

if __name__ == "__main__":
    app.run(debug=True)