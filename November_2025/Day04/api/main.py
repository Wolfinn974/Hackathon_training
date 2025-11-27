from fastapi import FastAPI
from api.router import router
from starlette.middleware.cors import CORSMiddleware

app = FastAPI(
    title="Fanwear Reco API",
    description="recommendation engine for fanwear",
    version="0.1.0",
)

#middleware cors
app.add_middleware(
    CORSMiddleware,
    allow_origins=["*"],
    allow_credentials=True,
    allow_methods=["*"],
    allow_headers=["*"]
)

app.include_router(router)