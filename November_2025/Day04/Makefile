test:
	pytest -q

cover:
	coverage run -m pytest
	coverage report

run-api:
	uvicorn api.main:app --reload

run-ui:
	streamlit run ui/streamlit_app.py

.PHONY: test cover run-api run-ui