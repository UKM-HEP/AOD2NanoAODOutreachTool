# Tool to convert AOD to NanoAOD

Tool to convert AOD to NanoAOD file format for the purpose of education and outreach.

The branch is built on top of 

```bash
https://github.com/cms-opendata-analyses/AOD2NanoAODOutreachTool -b v1.2 AOD2NanoAOD
```

## Description

The tool can be used to read events from CMS AOD files and convert them to a reduced NanoAOD data format. Note that the tool is published for the documentation of the related datasets below and may need significant experiment-specific knowledge to be used.


## Setup for local testing

```bash
cmssw-cc6
cmsrel CMSSW_5_3_32
cd CMSSW_5_3_32/src
cmsenv
mkdir workspace
cd workspace
git clone https://github.com/UKM-HEP/AOD2NanoAODOutreachTool.git AOD2NanoAOD
cd AOD2NanoAOD
scram b -j8
```

## Test configuration locally

```bash
cd AOD2NanoAOD/test
./proc.sh
```

## To-do
- [ ] Identify the quality variables for tnp 7TeV
- [ ] Identify the quality variables for tnp 8TeV
