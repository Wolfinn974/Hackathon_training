import streamlit as st
import pandas as pd
import altair as alt
import sys, os
import random
import requests

# Add project root to path
sys.path.append(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))

from engine.loader import load_data
from engine.recommender import recommend_items

API_URL = "http://localhost:8000/api/recommend"

def fetch_recommendations(prefs):
    try:
        response = requests.get(API_URL, params=prefs, timeout=5)
        response.raise_for_status()
        data = response.json()

        # L'API renvoie une liste -> convertissons en DataFrame
        return pd.DataFrame(data)

    except Exception as e:
        st.error(f"❌ API error: {e}")
        return pd.DataFrame()

# ===========================
# PAGE CONFIG
# ===========================
st.set_page_config(
    page_title="Fanwear Recommender",
    page_icon="🖤",
    layout="wide"
)

# ===========================
# STYLE CUSTOM (DARK MODE + UI STYLING)
# ===========================
st.markdown("""
<style>
    /* Global font */
    html, body, [class*="css"] {
        font-family: 'Inter', sans-serif;
    }
    /* Center title */
    .title-center {
        text-align:center !important;
    }
    /* Sexy dark card */
    .result-card {
        padding: 1rem;
        border-radius: 10px;
        background: rgba(30,30,30,0.5);
        border: 1px solid rgba(80,80,80,0.4);
    }
    .highlight {
        color:#ff79c6 !important;
        font-weight:600;
    }
</style>
""", unsafe_allow_html=True)

# ===========================
# LOAD DATA
# ===========================
df = load_data()

st.markdown("<h1 class='title-center'>🎀 Fanwear Recommender</h1>", unsafe_allow_html=True)
st.write("Trouvez la tenue parfaite selon vos goûts 💅🔥")

st.divider()

# ===========================
# USER INPUT PANEL
# ===========================
st.subheader("🧩 Vos préférences")

col1, col2 = st.columns(2)

with col1:
    sport = st.selectbox("Sport préféré", ["", *sorted(df["sport"].unique())])
    style = st.selectbox("Style fanwear", ["", *sorted(df["style"].unique())])
    color = st.selectbox("Couleur dominante", ["", *sorted(df["color"].unique())])

with col2:
    cut = st.selectbox("Coupe / Fit", ["", *sorted(df["cut"].unique())])
    budget = st.slider("Budget maximum (€)", 10, 250, 100)
    influence = st.text_input("Influence (athlète, équipe…)", "")

prefs = {
    "sport": sport or None,
    "style": style or None,
    "color": color or None,
    "cut": cut or None,
    "budget": budget,
    "influence": influence or None,
}

# ===========================
# SURPRISE
# ===========================
st.markdown("### 🎁 Surprise Me")
if st.button("🎲 Recommandation aléatoire"):
    random_item = df.sample(1)
    st.info("✨ **Item tiré au hasard :**")
    st.dataframe(random_item)
    st.stop()

# ===========================
# RECOMMENDATIONS
# ===========================
st.markdown("### 🔍 Rechercher des recommandations")

if st.button("🚀 Lancer la recommandation"):

    results_df = fetch_recommendations(prefs)

    st.divider()
    st.subheader("🔥 Résultats")

    if results_df.empty:
        st.warning("Aucun article trouvé 😭")
        st.stop()

    # --- MAIN TABLE
    st.dataframe(results_df)

    # --- TOP MATCH CARD
    top = results_df.iloc[0]

    st.markdown("""
        <div class='result-card'>
            <h3 style='margin-bottom:0'>⭐ Meilleur match</h3>
        </div>
    """, unsafe_allow_html=True)

    st.json(top.to_dict())

    # --- DOWNLOAD CSV
    csv = results_df.to_csv(index=False).encode("utf-8")
    st.download_button(
        "⬇️ Télécharger recommandations",
        csv,
        "recommendations.csv",
        mime="text/csv"
    )

    # --- CHART
    st.markdown("### 📊 Score des 5 meilleurs articles")
    top5 = results_df.sort_values("score", ascending=False).head(5)

    chart = (
        alt.Chart(top5)
        .mark_bar()
        .encode(
            x=alt.X("id:N", title="ID"),
            y=alt.Y("score:Q", title="Score"),
            tooltip=["id", "score", "style", "color"],
            color=alt.Color("score:Q", scale=alt.Scale(scheme="magma"))
        )
    )

    st.altair_chart(chart, use_container_width=True)

st.divider()
st.caption("Hackathon Training — Day 03 • Made by Léhane 💜")