#!/usr/bin/python3
import os
import time
import uuid
import json
from hydra.messages import Request

class Client(object):
    def __init__(self, command_pipe_path='/var/interop-volume/command.fifo'):
        self.client_id = uuid.uuid4()
        self.pipe_path = command_pipe_path
      
    def send(self, request_type=Request, data=None):
        startup = Request.GET.value
        startup['sender'] = str(self.client_id)
        with open(self.pipe_path, 'w') as command_pipe:
            msg = json.dumps(startup, indent=None)
            print (msg)
            command_pipe.write(msg)