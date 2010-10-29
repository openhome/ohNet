import os
import subprocess

cleanCmd = "rm -rf xunit-*"
ret = subprocess.call(cleanCmd, shell=True)
if ret != 0:
        sys.exit(ret)

def ParseFile(filename):
        import xml.etree.ElementTree as ET
        doc = ET.parse(filename)
        errors = doc.findall('//error')

        out = open("xunit-" + filename,"w")
        out.write('<?xml version="1.0" encoding="UTF-8"?>\n')
        out.write('<testsuite name="memcheck" tests="1" errors="0" failures="'+str(len(errors))+'" skip="0">\n')
        out.write('    <testcase classname="ValgrindMemoryCheck " \n')
        out.write('              name="Memory check" time="0">\n')
        for error in errors:
            kind = error.find('kind')
            what = error.find('what')
            if  what == None:
                what = error.find('xwhat/text')

            out.write('        <error type="'+kind.text+'">\n')
            out.write('            '+what.text+'\n')
            out.write('        </error>\n')
        out.write('    </testcase>\n')
        out.write('</testsuite>\n')
        out.close()

path="."  # insert the path to the directory of interesthere
dirList=os.listdir(path)
for fname in dirList:
        if fname != "ParseValgrind.py":
                print fname
                ParseFile(fname)

buildCmd = "scp -r xunit-* hudson@zapp.linn.co.uk:~/jobs/Zapp-Nightly/workspace/Upnp"
ret = subprocess.call(buildCmd, shell=True)
if ret != 0:
     sys.exit(ret)
