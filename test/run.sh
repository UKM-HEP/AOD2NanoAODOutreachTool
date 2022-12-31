#!/bin/bash

# input files ; number of event ; Year ; GT

# Exit on error
set -e

TEXT_FILES=$1
PROCESS=$(basename ${TEXT_FILES} .txt )
NEVENT=$2
YEAR=$3
GT=$4

if ([ -z "$TEXT_FILES" ] || [ -z "$NEVENT" ] || [ -z "$YEAR" ]);then
    echo "No all argument is given, exiting"
    echo "Example: ./run.sh FILE NEVENT YEAR GT"
    exit 1
fi

if [ -z "$CMSSW_BASE" ];then
    echo "CMSSW_BASE evironment is missing"
    exit 1
fi

# printout
echo "Textfiles    : $TEXT_FILES"
echo "Process      : $PROCESS"
echo "Nevent       : $NEVENT"
echo "Year         : $YEAR"
echo "Global Tag   : $GT"

#OUTPUT_DIR=${CMSSW_BASE}/src/workspace/AOD2NanoAOD/test
OUTPUT_DIR=$PWD
echo "Output directory:" $OUTPUT_DIR

echo "CMSSW base   : $CMSSW_BASE"

if [[ "${TEXT_FILES}" == *"Run"* ]]; then
    CONFIG=${CMSSW_BASE}/src/workspace/AOD2NanoAOD/configs/data_cfg.py
else
    CONFIG=${CMSSW_BASE}/src/workspace/AOD2NanoAOD/configs/simulation_cfg.py
fi

echo "CMSSW config : $CONFIG"
echo "System       : " `uname -a`

echo "### Start working"

# Make output directory
OUTDIR=${OUTPUT_DIR}/test_${PROCESS}
mkdir -p ${OUTDIR}

# Copy config file
CONFIG_COPY=${OUTDIR}/cfg_${PROCESS}.py
cp $CONFIG $CONFIG_COPY

# Modify the FwkReport
sed -i -e 's,reportEvery = 2000,reportEvery = 100,g' $CONFIG_COPY

# Modify the number of process event
sed -i -e 's,cms.untracked.int32(-1)),cms.untracked.int32('${NEVENT}')),g' $CONFIG_COPY

# Modify CMSSW config to run only a single file
FILETXT=${OUTPUT_DIR}/${TEXT_FILES}
sed -i -e "s,^files =,files = FileUtils.loadListFromFile('"${FILETXT}"') #,g" $CONFIG_COPY
sed -i -e 's,^files.extend,#files.extend,g' $CONFIG_COPY

# Modify globaltag for realistic analysis application
if [ ! -z "$GT" ]; then
    echo "Using Global Tag: ${GT}"

    #process.GlobalTag.connect = cms.string('sqlite_file:/cvmfs/cms-opendata-conddb.cern.ch/FT53_V21A_AN6_FULL.db')
    #process.GlobalTag.globaltag = "FT53_V21A_AN6::All"

    #process.GlobalTag.connect = cms.string('sqlite_file:FT53_V21A_AN6_FULL.db')
    #process.GlobalTag.globaltag = "FT53_V21A_AN6::All"

    #ln -sf /cvmfs/cms-opendata-conddb.cern.ch/FT53_V21A_AN6_FULL FT53_V21A_AN6
    #ln -sf /cvmfs/cms-opendata-conddb.cern.ch/FT53_V21A_AN6_FULL.db FT53_V21A_AN6_FULL.db
    #ln -sf /cvmfs/cms-opendata-conddb.cern.ch/FT53_V21A_AN6_FULL FT53_V21A_AN6_FULL

    # enable globaltag
    sed -i -e 's,#process.load(,process.load(,g' $CONFIG_COPY
    sed -i -e 's,#process.GlobalTag.connect,process.GlobalTag.connect,g' $CONFIG_COPY
    sed -i -e 's,#process.GlobalTag.globaltag,process.GlobalTag.globaltag,g' $CONFIG_COPY

    #http://opendata.cern.ch/docs/cms-guide-for-condition-database
    sed -i -e 's,USEGLOBALTAG,'${GT}',g' $CONFIG_COPY

    ln -sf /cvmfs/cms-opendata-conddb.cern.ch/${GT} ${GT}
    ln -sf /cvmfs/cms-opendata-conddb.cern.ch/${GT}.db ${GT}.db

    mv ${GT} ${CMSSW_BASE}/src
    mv ${GT}.db ${CMSSW_BASE}/src

    #http://opendata.cern.ch/docs/cms-guide-for-condition-database
    if [[ ${TEXT_FILES} == *"Run2012"* ]]; then
	
	GT_FULL=$(basename ${GT} _FULL )

	sed -i -e 's,'${GT}'::All,'${GT_FULL}'::All,g' $CONFIG_COPY
	ln -sf /cvmfs/cms-opendata-conddb.cern.ch/${GT_FULL} ${GT_FULL}
	mv ${GT_FULL} ${CMSSW_BASE}/src
    fi
fi

# Modify CMSSW config to read lumi mask from EOS
if [[ ${TEXT_FILES} == *"Run"* ]]; then
    if [[ ${TEXT_FILES} == *"Run2011"* ]]; then
	GJSON="Cert_160404-180252_7TeV_ReRecoNov08_Collisions11_JSON.txt"
    else
	GJSON="Cert_190456-208686_8TeV_22Jan2013ReReco_Collisions12_JSON.txt"
    fi
    sed -i -e 's,USECERTIFICATEHERE,'${CMSSW_BASE}'/src/workspace/AOD2NanoAOD/data/'${GJSON}',g' $CONFIG_COPY
fi

# Modify config to write output directly to EOS
OUTFILE=${OUTDIR}/${PROCESS}.root
sed -i -e 's,output.root,'${OUTFILE}',g' $CONFIG_COPY

cd ${CMSSW_BASE}/src

cat $CONFIG_COPY
cmsRun $CONFIG_COPY

# Copy output file
#xrdcp -f ${PROCESS}_${ID}.root root://eosuser.cern.ch/${OUTPUT_DIR}/${PROCESS}/${PROCESS}_${ID}.root
#rm ${PROCESS}_${ID}.root

echo "### End of job"
