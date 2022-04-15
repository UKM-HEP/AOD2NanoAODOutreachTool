import os, subprocess
from subprocess import PIPE, Popen
from catalogue import datasets

cwd = os.getcwd()

for ientry in datasets:
    handle= '--title '+ientry if not datasets[ientry]['data'] else '--doi '+datasets[ientry]['doi'].split('http://doi.org/')[-1]
    cmd='docker run -i -t --rm cernopendata/cernopendata-client get-metadata %s --output-value files' %( handle )
    cmdtxt=cmd+' | grep _file_index.txt'
    #os.system(cmd)
    listdict = subprocess.check_output(cmdtxt, shell=True).splitlines()
    files = list(map( lambda x : x.decode("utf-8").strip() , listdict ))
    files = list(filter( lambda x : 'uri' in x , files ))
    xrdcp = 'docker run -v $PWD:/home/cmsusr:rw -i --rm cmsopendata/cmssw_5_3_32-slc6_amd64_gcc472 xrdcp' if 'CMSSW_' not in cwd else 'xrdcp'
    for ifile in files:
        os.system( '%s %s /home/cmsusr' %( xrdcp , ifile.replace("\"","").split("uri: ")[-1] ) )
    break
