import sys, os, stat, time
from Card import Card
import SimUtils, MacroBuildUtils
from optparse import OptionParser

c = Card("../SimulationExamples/Bb2n.card")
output = SimUtils.GetFilesInfo(c,['jobs','g4','cluster','recon'])
print(output)
