# Tool to convert AOD to NanoAOD

Tool to convert AOD to NanoAOD file format for the purpose of education and outreach.

## Description

The tool can be used to read events from CMS AOD files and convert them to a reduced NanoAOD data format. Note that the tool is published for the documentation of the related datasets below and may need significant experiment-specific knowledge to be used.

## Build module

Note: the main branch is developed on top of 

```bash
https://github.com/cms-opendata-analyses/AOD2NanoAODOutreachTool -b v1.2 AOD2NanoAOD
```

```bash
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
cmsRun configs/simulation_cfg.py
cmsRun configs/data_cfg.py
```

## Example scripts for batch system submission

You can use the following script to submit to any [HTCondor](https://research.cs.wisc.edu/htcondor/) batch system.

```bash
./submit_jobs.sh /path/to/job/directory
```

You can merge the job files with the following script.

```bash
./merge_jobs.py /path/to/job/outputs
```
