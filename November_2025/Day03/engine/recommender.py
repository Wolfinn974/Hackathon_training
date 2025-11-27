from engine.filters import filter_items
from engine.scoring import scoring

def recommend_items(df, **preferences):
    filtered_items = filter_items(
        df,
        sport=preferences.get("sport"),
        style=preferences.get("style"),
        color=preferences.get("color"),
        cut=preferences.get("cut"),
        budget=preferences.get("budget"),
    )

    if filtered_items.empty:
        return []

    filtered_items = filtered_items.copy()
    filtered_items["score"] = filtered_items.apply(lambda row: scoring(row, preferences), axis=1)
    filtered_items = filtered_items.sort_values("score", ascending=False)

    return filtered_items.head(5)