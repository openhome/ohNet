import threading
import subprocess

class remote():
                def get_thread(self,pipe):
                        for line in pipe.readlines():
                                print line

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

		def rsync(self,username,host,src,dst):
			
			cmd = []
			dst = "%s@%s:%s" %(username,host,dst)

			cmd.append('rsync'),
			cmd.append('-r'),
			cmd.append('-v'),
			cmd.append(src),
			cmd.append(dst)
			
			ret = subprocess.call(cmd)
			return ret


