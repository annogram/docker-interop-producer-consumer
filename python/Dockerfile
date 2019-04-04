FROM python:3
WORKDIR /usr/src
ADD src/requirements.txt /usr/src/requirements.txt
RUN pip install --no-cache-dir -r requirements.txt
CMD ["python", "./app.py"]