import os
import contextlib
import time
from fabric import Connection, Config
from invoke import Responder


class CmdResult:

    def __init__(self, run_result):
        self._run_result = run_result

        if type(run_result) is contextlib._GeneratorContextManager:
            for entry in self._run_result.gen:
                print(entry)
        elif self._run_result.exited != 0:
            raise Exception('{0}:{1} result: {2}'.format(
                self._run_result.connection.host,
                self._run_result.command,
                self._run_result.stdout.strip()))
        else:
            print(run_result)

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

    def run(self, command_text):
        return self.try_do(lambda slf: slf.run_with_password(command_text))

    def go_to_directory(self, path, create_if_not_exists=True):
        try:
            return self.try_do(lambda slf: slf._conn.cd(path))
        except Exception as ex:
            if not create_if_not_exists:
                raise ex
            else:
                self.create_dir(path)
                return self.try_do(lambda slf: slf._conn.cd(path))

    def execute_in_directory(self, full_directory_path, command_func):
        with self._conn.cd(full_directory_path):
            command_func(self)

    def create_dir_in_home_folder(self, dir_name):
        return self.execute_in_directory('~',
                                         lambda slf: slf.go_to_directory(dir_name))

    def kill_existing_dpkg_lock(self):
        self.list_running_jobs()
        try:
            self.sudo_try_do('pkill apt-get')
            time.sleep(15)
        except:
            pass

        try:
            self.sudo_try_do('pkill dpkg')
            time.sleep(15)
        except:
            pass

        return self.sudo_try_do('dpkg --configure -a')

    def list_running_jobs(self):
        return self.run('jobs')

    def apt_get_install(self, package, auto_allow=True):
        command_text = 'apt-get install -y {0}'
        if not auto_allow:
            command_text = 'apt-get install {0}'

        result = self.sudo_try_do(command_text.format(package))
        return result

    def apt_update(self):
        result = None
        try:
            result = self.sudo_try_do('apt-get update')
        except Exception as ex:
            pass
        time.sleep(15)
        return result

    def get_installed_packages(self, package_name_filter):
        results = self.sudo_try_do('apt list --installed | grep -i {0}'.format(package_name_filter))
        return results

    def uninstall_package(self, package_name, auto_allow=True):
        command_text = 'apt-get remove -y {0}'
        if not auto_allow:
            command_text = 'apt-get remove {0}'

        result = self._conn.sudo(command_text.format(package_name))
        return result

    def upgrade_all_packages(self):
        return self.sudo_try_do('apt-get upgrade')

    def try_do(self, command):
        result = None
        try:
            result = command(self)
        except Exception as ex:
            pass
        finally:
            return result

    def sudo_try_do(self, command_text):
        return self.try_do(lambda slf: slf._conn.sudo(command_text))

    def install_git(self):
        return self.apt_get_install('git')

    def git_clone(self, repo_url):
        result = self.try_do(lambda slf: slf._conn.run(
            'git clone {0}'.format(repo_url))
        )
        return result

    def git_update_current_dir(self):
        self.try_do(self.run('git fetch'))
        #self.try_do(self.run('git checkout master'))
        return self.try_do(self.run('git pull'))

    def create_dir(self, directory):
        return self.try_do(self._conn.run('mkdir -p {0}'.format(directory)))

    def create_dir_in_user_home(self, directory):
        self.try_do(lambda slf: slf._conn.cd('~'))
        return self.create_dir(directory)

    def set_file_as_executable(self, filename):
        return self.try_do(self.run('chmod +x {0}'.format(filename)))

    def execute_script_current_folder(self, script_name):
        self.set_file_as_executable(script_name)
        return self.run('./{0}'.format(script_name))

    def wget(self, remote_url, local_filename=None):
        if local_filename is None:
            return self.run('wget {0}'.format(remote_url))

        return self.run('wget -O {0} {1}'.format(local_filename, remote_url))


class RobotCxn(RemoteCxn):

    def exec_in_robot1_directory(self, command, subdir=None):
        if subdir is not None:
            return self.execute_in_directory('~/Source/robot1/{0}'.format(subdir), command)
        return self.execute_in_directory('~/Source/robot1', command)

    def exec_in_robot1_ros_directory(self, command, subdir=None):
        if subdir is not None:
            return self.execute_in_directory('~/Source/robot1-ros/{0}'.format(subdir), command)
        return self.execute_in_directory('~/Source/robot1-ros', command)

    def exec_in_source_directory(self, command):
        return self.execute_in_directory('~/Source/', command)

    def clone_my_repo(self, repo_name):
        return self.git_clone('https://github.com/gtraines/{0}.git'.format(repo_name))


class RobotDeploy(RobotCxn):

    def one_time_setup(self):
        self.apt_update()
        self.remove_preinstalled_ros_packages()
        self.install_git()
        self.get_source_repos_first_time()
        self.install_ros()

    def get_source_repos_first_time(self):
        self.create_dir_in_user_home('Source')

        self.exec_in_source_directory(lambda slf:
                                      slf.clone_my_repo('robot1'))
        self.exec_in_source_directory(lambda slf:
                                      slf.clone_my_repo('robot1-ros'))

    def install_ros(self):
        self.exec_in_robot1_ros_directory(lambda slf:
                                          slf.execute_script_current_folder('configure_helpers.sh'))
        self.sudo_try_do('bash ~/Source/robot1-ros/install_ros/install_ros_complete.sh')
        self.sudo_try_do('rosdep fix-permissions')
        self.run('rosdep update')

    def install_arduino(self):
        self.apt_get_install('openjdk-8-jdk')
        self.apt_get_install('ant')
        self.apt_get_install('avr-libc')
        self.apt_get_install('binutils-avr')
        self.apt_get_install('avrdude')
        self.apt_get_install('gcc-avr')

        self.try_do(lambda slf: slf.run_with_password('bash ~/Source/robot1/scripts/install_arduino.sh'))

    def update_sources(self):
        self.exec_in_robot1_directory(lambda slf: slf.git_update_current_dir())
        self.exec_in_robot1_ros_directory(lambda slf: slf.git_update_current_dir())

    def remove_preinstalled_ros_packages(self):
        self.kill_existing_dpkg_lock()
        ros_pkgs = [
            'ros-message-generation',
            'ros-message-runtime',
            'ros-mk',
            'ros-robot-python-dev',
            'libros-rosgraph-msgs-dev',
            'ros-base-python-dev',
            'ros-cmake-modules',
            'ros-core',
            'ros-core-dev',
            'ros-core-lisp-dev',
            'ros-core-python-dev',
            'ros-core-rosbuild-dev',
            'ros-message-generation',
            'ros-message-runtime',
            'python-rospy',
            'rosbuild',
            'rosbash',
            'roslang',
            'roslisp',
            'rosout',
            'rospack-tools',
            'libmessage-filters0d',
            'librosbag0d',
            'libtopic-tools0d',
            'python-message-filters',
            'python-rosclean',
            'python-rosgraph',
            'python-rosmaster',
            'python-rosmsg',
            'python-rosnode',
            'python-rosparam'
        ]

        for package_name in ros_pkgs:
            self.uninstall_package(package_name)

        self.sudo_try_do('apt autoremove -y')


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


def connect_rpi2():
    rcxn = RobotDeploy('192.168.1.13', 'robot1')
    return rcxn


def connect_rpi1():
    rcxn = RobotDeploy('192.168.1.14', 'robot1')
    return rcxn


if __name__ == '__main__':
    pi_rcxn = connect_rpi1()
    pi_rcxn.update_sources()
    pi_rcxn.install_arduino()

