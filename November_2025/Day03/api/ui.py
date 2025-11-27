import streamlit as st
import pandas as pd
import sys, os
import altair as alt
import random

# Add project to path
sys.path.append(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))

from engine.loader import load_data
from engine.recommender import recommend_items

#load dataset
df = load_data()

#Streamlit UI

st.set_page_config(
    page_title = "Fanwear Recommender",
    page_icon = "👔",
    layout = "centered"
)

st.title("Fanwear Recommender")
st.write("Find your perfect fanwear")

st.divider()

# Form

st.subheader("Your preference")

sport = st.selectbox("Sport", ["", *sorted(df["sport"].unique())])
style = st.selectbox("Style", ["", *sorted(df["style"].unique())])
color = st.selectbox("Couleur", ["", *sorted(df["color"].unique())])
cut = st.selectbox("Coupe", ["", *sorted(df["cut"].unique())])

budget = st.slider("Budget max (€)", 10, 250, 100)

influence = st.text_input("Influence (athlète, team…)", "")

prefs = {
        "sport": sport or None,
        "style": style or None,
        "color": color or None,
        "cut": cut or None,
        "budget": budget,
        "influence": influence or None,
    }
#Button
if st.button("Surprise Me"):
    random_item = df.sample(1)
    st.write("Item Surprise:", random_item)

if st.button("🔍 Voir recommandations"):

    results = recommend_items(df, **prefs)

    st.divider()
    st.subheader("🔥 Résultats")

    if isinstance(results, list):
        results_df = pd.DataFrame(results)
    else:
        results_df = results

    if results_df.empty:
        st.warning("Aucun article trouvé 😭")
    else:
        st.dataframe(results_df)

        # show top 1 separately
        top = results_df.iloc[0]
        st.success(f"⭐ Meilleur match : {top.to_dict()}")
    if not results_df.empty:
        csv = results_df.to_csv(index=False).encode("utf-8")

        st.download_button(
            label="Download CSV",
            data=csv,
            file_name= "recommendations.csv",
            mime="text/csv"
        )
    if not results_df.empty:
        top5 = results_df.sort_values("score", ascending=False).head(5)

        chart = (
            alt.Chart(top5)
            .mark_bar()
            .encode(
                x=alt.X("id", title="Item ID"),
                y=alt.Y("score:Q", title="Score"),
                tooltip=["id", "score","color", "style"],
                color="score:Q",
            )
        )
        st.altair_chart(chart, use_container_width=True)



st.divider()
st.caption("Made during Hackathon Training — Day03 💜")