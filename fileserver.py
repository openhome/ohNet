import os.path
import subprocess
import sys
import threading

sys.path.insert(0, os.path.abspath('dependencies/AnyPlatform/CherryPy'))

import cherrypy

"""
    This function serves static files from the current directory.

    CherryPy guide for serving static files can be found here:
    http://docs.cherrypy.org/stable/progguide/files/static.html
"""
def run_static_fileserver(host, port, path):
    # get the current directory
    current_dir = os.path.dirname(os.path.abspath(__file__))

    # create a dummy app for CherryPy
    class RootStatic(object):
    
        # this lets the server be shutdown by visiting "http://<server:port>/shutdown"
        @cherrypy.expose
        def shutdown(self):  
            cherrypy.engine.exit()
    
    # set the global config
    cherrypy.config.update(
        {'server.socket_host': host,
         'server.socket_port': port,
         'log.screen': None,
         'log.access_file': os.path.join(path, 'fileserver.log'),
        }
    )

    # create a configuration for serving static files
    config={'/':
        {
         'tools.staticdir.on': True,
         'tools.staticdir.dir': path,
        }
    }

    # mount our dummy app with our config
    cherrypy.tree.mount(RootStatic(), '/', config=config)

    # run the server
    cherrypy.engine.start()
    cherrypy.engine.block()

# cmds for invoking from waf to start/stop server
def invoke_test_fileserver(tsk):
    print tsk.env.BUILDDIR
    testfile = tsk.env.cxxprogram_PATTERN % tsk.generator.test
    testargs = tsk.generator.args
    bldpath = tsk.generator.bld.bldnode.abspath()
    testfilepath = os.path.join(bldpath, testfile)
    if (len(testargs) < 2):
        raise Exception("Too few args for invoking test server")
    cmdline = []
    cmdline.append(testfile)
    run_test_server(cmdline, testfilepath, bldpath, testargs[0], int(testargs[1]))

def stop_test_fileserver():
    cherrypy.engine.exit()

# thread for running a server in when using localhost
class TestThread(threading.Thread):
    def __init__(self, host, port, path):
        self.__host = host
        self.__port = port
        self.__path = path
        threading.Thread.__init__(self)
    def run(self):
        run_static_fileserver(self.__host, self.__port, self.__path)
    def stop(self):
        cherrypy.engine.exit()

# run a test server, invoke the given test file, then exit the server
def run_test_server(cmdline, testfilepath, bldpath, host, port):
    server_thread = TestThread(host, port, bldpath)
    server_thread.start()
    cherrypy.server.wait()
    subprocess.check_call(cmdline, executable=testfilepath, cwd=bldpath)
    server_thread.stop()

if __name__=="__main__":
    run_static_fileserver('127.0.0.1', 8080, os.path.dirname(os.path.abspath(__file__)))
