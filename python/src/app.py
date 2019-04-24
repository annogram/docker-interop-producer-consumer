#!/usr/bin/python3

from hydra.consumer import Client
from hydra.messages import Request

c = Client()
c.send(Request.GET)
c.send(Request.DELETE)