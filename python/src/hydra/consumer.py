#!/usr/bin/python3
import os
import time

class Client(object):
    def __init__(self, command_pipe_path='/var/interop-volume/command.fifo'):
        with open(command_pipe_path, 'w') as command_pipe:
            for _ in range(1,111):
                command_pipe.writelines('test\n')
            time.sleep(2)
            for _ in range(1,111):
                command_pipe.writelines('yeahnah\n')
            command_pipe.writelines('s\n')
            