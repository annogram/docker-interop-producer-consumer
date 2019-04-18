#!/usr/bin/python3
import enum

class Request(enum.Enum):
    GET = {
        "type": "GET",
        "path": "/",
        "sender": "",
        "params": []
    }
    DELETE = {
        "type": "DELETE",
        "path": "/",
        "sender": "",
        "params": []
    }
    POST = {
        "type": "POST",
        "path": "/",
        "sender": "",
        "body": {},
        "params": []
    }
    PUT = {
        "type": "PUT",
        "path": "/",
        "sender": "",
        "body": {},
        "params": []
    }
