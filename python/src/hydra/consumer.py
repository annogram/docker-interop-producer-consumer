#!/usr/bin/python3
import os
import pyinotify

class Client(object):
    def __init__(self, command_pipe_path='/var/interop-volume/command.fifo'):
        with open(command_pipe_path, 'a') as command_pipe:
            command_pipe.writelines('')