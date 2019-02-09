import os
from fabric import Connection, Config
from invoke import Responder


class RobotConnection:
    PASSWORD_KEY = 'ROBOT_SUDO_PASSWORD'

    def __init__(self, remote_host, username, port=22, password=None):
        self._password = password

        if self._password is None:
            self._password = os.getenv(self.PASSWORD_KEY)

        if self._password is None or self._password == '':
            raise ValueError('ROBOT_SUDO_PASSWORD not set or missing value')

        self._config = Config(overrides={'sudo': {'password': self._password}})
        self._conn = Connection(host=remote_host, user=username, port=port,
                                connect_kwargs={'password': self._password},
                                config=self._config)

        self.run_with_password('uname -s')

    def run_with_password(self, command_text):
        pass_watcher = Responder(pattern=r'password:',
                                 response='{0}\n'.format(self._password),)

        result = self._conn.run(command_text, pty=True, watchers=[pass_watcher])
        return result

    def apt_get_install(self, package, auto_allow=True):
        command_text = 'apt-get install -y {0}'
        if not auto_allow:
            command_text = 'apt-get install {0}'

        result = self._conn.sudo(command_text.format(package))
        return result


def connect_vic20(password=None):
    rcxn = RobotConnection('192.168.1.10', 'robot1v', password=password)

    return rcxn
