#!/bin/bash

# cmssw-cc6
# CMSSW_5_3_32

set e

checkExit() {
    if [ $? -eq 0 ] 
    then 
	echo "TEST $1 : The test is a Success" 
    else 
	echo "TEST $1 : The test has failed" >&2 
    fi
}

#echo "TEST 1 : Running 7TeV on DATA"
#./run.sh CMS_Run2011A_DoubleElectron_AOD_12Oct2013-v1_test.txt 500 2011 FT_53_LV5_AN1
#checkExit 1

# testing j/psi
#./run.sh CMS_Run2011A_MuEG_AOD_12Oct2013-v1_test.txt 500 2011  FT_53_LV5_AN1
./run.sh CMS_Run2011A_MuOnia_AOD_12Oct2013-v1.txt 5000 2011  FT_53_LV5_AN1
./run.sh CMS_Run2011B_MuOnia_AOD_12Oct2013-v1.txt 5000 2011  FT_53_LV5_AN1
#checkExit 1

#echo "TEST 2 : Running 7TeV on MC"
#./run.sh CMS_MonteCarlo2011_Summer11LegDR_DYJetsToLL_M-50_7TeV-madgraph-pythia6-tauola_AODSIM_PU_S13_START53_LV6-v1_test.txt 2000 2011 START53_LV6A1
#./run.sh CMS_MonteCarlo2011_JPsiToMuMu_2MuPEtaFilter_7TeV-pythia6-evtgen-v2_AODSIM_PU_S13_START53_LV6-v1.txt 50000 2011 START53_LV6A1
#checkExit 2

#echo "TEST 3 : Running 8TeV on DATA"
#./run.sh CMS_Run2012A_SingleMu_AOD_22Jan2013-v1_test.txt 500 2012 FT53_V21A_AN6_FULL
#./run.sh CMS_Run2012B_SingleMu_AOD_22Jan2013-v1_test.txt 500 2012 FT53_V21A_AN6_FULL
#./run.sh CMS_Run2012C_SingleMu_AOD_22Jan2013-v1_test.txt 5 2012 FT53_V21A_AN6_FULL
#./run.sh CMS_Run2012B_SingleElectron_AOD_22Jan2013-v1.txt 50000 2012 FT53_V21A_AN6_FULL
#checkExit 3

#echo "TEST 4 : Running 8TeV on MC"
#./run.sh CMS_MonteCarlo2012_ZZTo4e_8TeV-powheg-pythia6_test.txt 2000 2012 START53_V27
#./run.sh CMS_MonteCarlo2012_DYJetsToLL_M-50_TuneZ2Star_8TeV-madgraph-tarball_AODSIM_PU_RD1_START53_V7N-v1.txt 50000 2012 START53_V27
#checkExit 4
