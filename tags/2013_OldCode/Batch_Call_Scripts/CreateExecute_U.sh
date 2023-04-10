############################################################################
# The purpose of this script is to send jobs to the batch to produce separate
# files for each daugher in the U238 decay chain with correct relative 
# branching ratios in the specified components of nEXO.  The number of files 
# and number of decays produced in each file are defined in the 
# 'DecayValues.txt' script.  It creates python scripts for each file and then 
# executes them.  A different seed is used for each file.

#!/bin/sh
iso="U238"

. Batch_Call_Scripts/DecayValues.txt

### Name of the python file ####
### Incrementation and .py extention are added below ###
PythonFileName=""

### Define the path to the nEXO Executable ####
ExecutablePath=""

### Define the output root file name
### Incrementation is already included
outputFileName=""

### List components to simulate Th232 chain decays in

for type in TPC FieldRing TReflector APDPlatter TeflonInsulator FieldSupport
#ActiveLXe InactiveLXe
#InnerCryo OuterCryo HFE

do 
echo "$type"
if [ $iso = U238 ]; then

numdecays="numdecays_$type"
eval numdecays=\$$numdecays
factor="factor_$type"
eval factor=\$$factor
echo "$factor"



## List the specific isotopes you want to simulate

for piece in Th234 Pa234 Ra226 Pb214 Bi214 Pb210
#U238 Th234 Pa234 U234 Th230 Ra226 Rn222 Po218 Pb214 Bi214 Po214 Pb210 Bi210 Po210


#Pieces with emitted gammas
# Th234 Pa234 Ra226 Pb214 Bi214 Pb210

do
echo "$piece"
if [ $piece = U238 ]; then
gpsion="/gps/ion 92 238
/grdm/nucleusLimits 238 238 92 92"
fi

if [ $piece = Th234 ]; then
gpsion="/gps/ion 90 234 234
/grdm/nucleusLimits 234 234 90 90"
fi

if [ $piece = Pa234 ]; then
gpsion="/gps/ion 91 234 0 73.92
/grdm/nucleusLimits 234 234 91 91"
fi

if [ $piece = U234 ]; then
gpsion="/gps/ion 92 234
/grdm/nucleusLimits 234 234 92 92"
fi

if [ $piece = Th230 ]; then
gpsion="/gps/ion 90 230
/grdm/nucleusLimits 230 230 90 90"
fi

if [ $piece = Ra226 ]; then
gpsion="/gps/ion 88 226
/grdm/nucleusLimits 226 226 88 88"
fi

if [ $piece = Rn222 ]; then
gpsion="/gps/ion 86 222
/grdm/nucleusLimits 222 222 86 86"
fi

if [ $piece = Po218 ]; then
gpsion="/gps/ion 84 218
/grdm/nucleusLimits 218 218 84 84"
fi

if [ $piece = Pb214 ]; then
gpsion="/gps/ion 82 214
/grdm/nucleusLimits 214 214 82 82"
fi

if [ $piece = Bi214 ]; then
gpsion="/gps/ion 83 214
/grdm/nucleusLimits 214 214 83 83"
fi

if [ $piece = Po214 ]; then
gpsion="/gps/ion 84 214
/grdm/nucleusLimits 214 214 84 84"
fi

if [ $piece = Pb210 ]; then
gpsion="/gps/ion 82 210
/grdm/nucleusLimits 210 210 82 82"
fi

if [ $piece = Bi210 ]; then
gpsion="/gps/ion 83 210
/grdm/nucleusLimits 210 210 83 83"
fi

if [ $piece = Po210 ]; then
gpsion="/gps/ion 84 210
/grdm/nucleusLimits 210 210 84 84"
fi


for((i = 1; i <= $factor; i++))
do
echo "
##############################################################################
#           Event Generator for $piece in the $type
#
##############################################################################

/rootfile/fileName ${outputFileName}_${i}

/run/initialize

/run/verbose 0
/event/verbose 0
/tracking/verbose 0
/grdm/verbose 0

/gps/pos/type Volume
/gps/pos/shape Cylinder
/gps/pos/centre 0 0 0 cm
/gps/pos/halfz 200 cm
/gps/pos/radius 200 cm
/gps/pos/confine $type
/gps/energy 0 keV
/gps/particle ion
$gpsion

/run/beamOn $numdecays

"  > ${PythonFileName}_${i}.py

bsub -q xxl ${ExecutablePath} ${PythonFileName}_${i}.py $i
done


done
done

else
echo "Not the right isotope."
fi

done






