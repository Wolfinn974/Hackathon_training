def scoring(item, preference):
    score = 0

    if item["sport"] == preference.get("sport"):
        score += 40
    if item["style"] == preference.get("style"):
        score += 30
    if item["color"] == preference.get("color"):
        score += 20
    if item["cut"] == preference.get("cut"):
        score += 15

    budget = preference.get("budget")
    if budget:
        if item["price"] <= budget:
            score += 20
        else:
            score -= (item["price"] - budget)

    influence = preference.get("influence")
    if influence and item.get("influence") == influence:
        score += 10
    return score