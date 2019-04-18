#!/usr/bin/python3
import os
import time
import uuid
import json
from hydra.messages import GET, POST, PUT, DELETE

class Client(object):
    def __init__(self, command_pipe_path='/var/interop-volume/command.fifo'):
        startup = GET
        client_id = uuid.uuid4()
        startup['sender'] = str(client_id)
        with open(command_pipe_path, 'w') as command_pipe:
            msg = json.dumps(GET, indent=None) + '\n'
            print (msg)
            command_pipe.write(msg)
            command_pipe.writelines('s\n')
            