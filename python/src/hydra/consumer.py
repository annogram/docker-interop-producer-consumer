#!/usr/bin/python3
import os

class Client(object):
    def __init__(self, command_pipe_path='/var/interop-volume/command.fifo'):
        with open(command_pipe_path, 'w') as command_pipe:
            while True:
                command_pipe.writelines('test\n')
