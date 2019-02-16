import os
from fabric import Connection, Config
from invoke import Responder


class CmdResult:

    def __init__(self, run_result):
        self._run_result = run_result

        if self._run_result.exited != 0:
            raise Exception('{0}:{1} result: {2}'.format(
                self._run_result.connection.host,
                self._run_result.command,
                self._run_result.stdout.strip()))

    def success(self):
        if self._run_result.exited == 0 or self._run_result.ok == 'True':
            return True
        return False

    def stdout_text(self):
        return self._run_result.stdout


class RemoteCxn:
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

    def go_to_directory(self, path, create_if_not_exists=True):
        try:
            self.try_do(self._conn.cd(path))
        except Exception as ex:
            if not create_if_not_exists:
                raise ex
            else:
                self.create_dir(path)
                self.try_do(self._conn.cd(path))

    def apt_get_install(self, package, auto_allow=True):
        command_text = 'apt-get install -y {0}'
        if not auto_allow:
            command_text = 'apt-get install {0}'

        result = self._conn.sudo(command_text.format(package))
        return result

    @staticmethod
    def try_do(command):
        result = CmdResult(command)
        return result

    def sudo_try_do(self, command_text):
        return self.try_do(self._conn.sudo(command_text))

    def apt_update(self):
        result = self._conn.sudo('apt-get update')
        return result

    def install_git(self):
        self.apt_get_install('git')

    def git_clone(self, repo_url):
        return self.try_do(self._conn.run(
            'git clone {0}'.format(repo_url))
        )

    def create_dir(self, directory):
        return self.try_do(self._conn.run('mkdir {0}'.format(directory)))

    def create_dir_in_user_home(self, directory):
        self.try_do(self._conn.cd('~'))
        return self.create_dir(directory)


def prep_vic20():
    vic20_cxn = connect_vic20(os.environ.get('ROBOT_SUDO_PASSWORD'))
    vic20_cxn.apt_update()
    vic20_cxn.apt_get_install('openjdk-8-jdk')
    vic20_cxn.install_git()

    vic20_cxn.go_to_directory('Source')
    vic20_cxn.git_clone('https://github.com/gtraines/robot1.git')
    vic20_cxn.git_clone('https://github.com/gtraines/robot1-ros.git')
    vic20_cxn.go_to_directory('~/Source/robot1-ros')
    vic20_cxn._conn.run('chmod +x configure_helpers.sh')
    vic20_cxn._conn.run('./configure_helpers.sh')
    vic20_cxn.go_to_directory('~/Source/robot1-ros/install_ros/')
    vic20_cxn._conn.run('./install_ros_complete.sh')

    vic20_cxn.create_dir_in_user_home('arduino-1.8.5')
    vic20_cxn._conn.run('wget -O arduino-1.8.5.tar.xz https://github.com/arduino/Arduino/releases/download/1.8.5/Arduino-1.8.5.tar.xz')
    vic20_cxn._conn.run('unxz arduino-1.8.5.tar.xz')


def connect_vic20(password=None):
    rcxn = RemoteCxn('192.168.1.10', 'robot1v', password=password)

    return rcxn


if __name__ == '__main__':
    vic20cxn = connect_vic20(os.environ.get('ROBOT_SUDO_PASSWORD'))
