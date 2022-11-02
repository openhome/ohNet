import threading
import subprocess

class remote():
    def get_thread(self,pipe):
        for line in pipe.readlines():
                print(line)

    def rssh(self,username,host,cmd):
        import paramiko

        ssh = paramiko.SSHClient()
        ssh.set_missing_host_key_policy(paramiko.AutoAddPolicy())
        ssh.connect(host, username=username, look_for_keys='True')

        stdin, stdout, stderr = ssh.exec_command(cmd)

        stdout_thread = threading.Thread(target=self.get_thread, args=(stdout,))
        stderr_thread = threading.Thread(target=self.get_thread, args=(stderr,))

        stdout_thread.start()
        stderr_thread.start()
        stdout_thread.join()
        stderr_thread.join()

        channel = stdout.channel

        exit_status = channel.recv_exit_status()
        return exit_status

        ssh.close()

    def _rsync_cmd(self, username, host, src, dst, excludes, delete_excluded):
        cmd = []
        dst = "%s@%s:%s" %(username,host,dst)

        cmd.append('rsync'),
        cmd.append('-r'),
        cmd.append('-v'),
        cmd.append('--chmod=u=rwX,go=rX'), # New files are user-writable and world-readable
        cmd.append('--no-p'),              # Don't change permissions of existing directories (or files)

        if delete_excluded:
            cmd.append('--delete-excluded')

        for pattern in excludes:
            cmd.append('--exclude=' + pattern)

        cmd.append(src),
        cmd.append(dst)

        print(cmd)

        return cmd

    def rsync(self, username, host, src, dst, excludes=[], delete_excluded=False):
        cmd = self._rsync_cmd(username, host, src, dst, excludes, delete_excluded)
        ret = subprocess.call(cmd)
        return ret

    # garbage collect (delete) outdated items at destination
    def rsync_gc(self, username, host, src, dst):
        cmd = self._rsync_cmd(username, host, src, dst, [], False)
        cmd[1:1] = ['--itemize-changes', '--checksum', '--delete']
        ret = subprocess.call(cmd)
        return ret

    def check_rsync(self, username, host, src, dst, excludes=[], delete_excluded=False):
        cmd = self._rsync_cmd(username, host, src, dst, excludes, delete_excluded)
        ret = subprocess.check_call(cmd)
        return ret

