def filter_items(df, sport=None, style=None, color= None, cut=None, budget=None):
    filtered_df = df.copy()

    if sport:
        filtered_df = filtered_df[filtered_df["sport"] == sport]
    if style:
        filtered_df = filtered_df[filtered_df["style"] == style]
    if color:
        filtered_df = filtered_df[filtered_df["color"] == color]
    if cut:
        filtered_df = filtered_df[filtered_df["cut"] == cut]
    if budget:
        filtered_df = filtered_df[filtered_df["price"] == budget]
    return filtered_df