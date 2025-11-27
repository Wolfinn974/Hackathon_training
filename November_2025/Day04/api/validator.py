from pydantic import BaseModel
from typing import Optional

class Preferences(BaseModel):
    sport: Optional[str] = None
    style: Optional[str] = None
    color: Optional[str] = None
    cut: Optional[str] = None
    budget: Optional[int] = None
    influence: Optional[str] = None