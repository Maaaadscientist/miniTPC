
import ROOT
import sys, os, copy
from Card import Card
import SimUtils
from optparse import OptionParser

globalArgs = {}

class SimplePlot:
    def __init__(self, name, expression, cut = '', option = '', draw = '', destination = 'histo', specifications = '', xTitle = '', yTitle = '', zTitle = '', entrylist = None):
        self.name = name
        self.expression = expression
        self.weight = 'Weight'
        self.cut = cut
        self.option = '%s goff' % option
        self.destination = destination
        self.specifications = specifications
        self.entrylist = entrylist
        self.draw = draw

        self.xTitle = xTitle
        self.yTitle = yTitle
        self.zTitle = zTitle


def CatchGlobalArguments(options):

    global globalArgs

    globalArgs['CardName'] = options.cardName #str(sys.argv[1])
    globalArgs['Process'] = options.processName 
    globalArgs['InputDir'] = options.inDir
    globalArgs['OutputFileName'] = options.outFileName
    if not globalArgs['OutputFileName'].endswith('.root'):
        globalArgs['OutputFileName'] += '.root'
        print 'Adding extension .root to output file name:', globalArgs['OutputFileName']
    globalArgs['AllIsotopes'] = bool(options.allIsotopes)

    globalArgs['WritePdf'] = bool(options.writePdf)
    globalArgs['OutputPdfFileName'] = None
    if globalArgs['WritePdf']:
        globalArgs['OutputPdfFileName'] = globalArgs['OutputFileName'].replace('.root','.pdf')

    globalArgs['Card'] = Card(globalArgs['CardName'])

def GetChainsForLocation(location):

    card = globalArgs['Card']

    processName = globalArgs['Process']
    processTitle = processName.title()

    treeName = card.Get('%sTreeName'%(globalArgs['Process'].title()))
    treeDecayName = treeName+'Decay'

    filesInfo = SimUtils.GetFilesInfo(card,[processName])

    decayChainName = card.Get('ParentName')+'DecayChain'

    chainList = {}
    chainList[decayChainName] = ROOT.TChain(treeDecayName)
    for fileInfo in filesInfo:
        if fileInfo['ShortLocationName'] != location:
            continue

        isotope = fileInfo['Isotope']
        if globalArgs['AllIsotopes']:
            if not isotope in chainList:
                chainList[isotope] = {}
                chainList[isotope] = ROOT.TChain(treeDecayName)
            chain = chainList[isotope]

        fileName = fileInfo['%sFileName'%(processTitle)]
        fileName = fileName.replace(treeName,treeDecayName)
        if globalArgs['InputDir']:
            fileName = globalArgs['InputDir'] + fileName[fileName.rfind('/'):]
        
        if os.path.isfile(fileName):
            if globalArgs['AllIsotopes']: chain.Add(fileName)
            chainList[decayChainName].Add(fileName)

    return chainList

def GetRadiusAndAxial(r1,r2,axial,pre,pos):

    return 'sqrt(%s%s%s**2 + %s%s%s**2)' % (pre,r1,pos,pre,r2,pos), '%s%s%s' % (pre,axial,pos)

def GetRadius2AndAxial(r1,r2,axial,pre,pos):

    return '%s%s%s**2 + %s%s%s**2' % (pre,r1,pos,pre,r2,pos), '%s%s%s' % (pre,axial,pos)

def GetG4Plots():

    plots = []
    plots.append(SimplePlot(name = 'GenY_vs_GenX', expression = 'GenY:GenX', xTitle = 'X (mm)', yTitle = 'Y (mm)', draw = 'colz'))
    plots.append(SimplePlot(name = 'GenX_vs_GenZ', expression = 'GenX:GenZ', xTitle = 'Z (mm)', yTitle = 'X (mm)', draw = 'colz'))
    plots.append(SimplePlot(name = 'GenY_vs_GenZ', expression = 'GenY:GenZ', xTitle = 'Z (mm)', yTitle = 'Y (mm)', draw = 'colz'))
    plots.append(SimplePlot(name = 'NuclideZ', expression = 'NuclideZ', specifications = '(200,0,200)', xTitle = 'Isotope Atomic Number Z'))
    plots.append(SimplePlot(name = 'TotalEventEnergy', expression = 'TotalEventEnergy', specifications = '(250,0,5)', xTitle = 'Energy (MeV)', cut = 'TotalEventEnergy > 0'))
    plots.append(SimplePlot(name = 'NumDeposits', expression = 'NumDeposits', xTitle = 'Number of G4 Deposits', cut = 'TotalEventEnergy > 0'))
    plots.append(SimplePlot(name = 'NumDeposits_vs_TotalEventEnergy', expression = 'NumDeposits:TotalEventEnergy', xTitle = 'Total Energy (MeV)', yTitle = 'Number of G4 Deposits', cut = 'TotalEventEnergy > 0', draw = 'colz'))
    plots.append(SimplePlot(name = 'EnergyDeposit', expression = 'EnergyDeposit', xTitle = 'Total Energy (MeV)', cut = 'EnergyDeposit > 0'))
    plots.append(SimplePlot(name = 'Ypos_vs_Xpos', expression = 'Ypos:Xpos', xTitle = 'Xpos (mm)', yTitle = 'Ypos (mm)', cut = 'EnergyDeposit > 0', draw = 'colz'))
    plots.append(SimplePlot(name = 'Xpos_vs_Zpos', expression = 'Xpos:Zpos', xTitle = 'Zpos (mm)', yTitle = 'Xpos (mm)', cut = 'EnergyDeposit > 0', draw = 'colz'))
    plots.append(SimplePlot(name = 'Ypos_vs_Zpos', expression = 'Ypos:Zpos', xTitle = 'Zpos (mm)', yTitle = 'Ypos (mm)', cut = 'EnergyDeposit > 0', draw = 'colz'))

    r1, r2, axial = SimUtils.GetRadialAndAxialCoordinatesString(globalArgs['Card'])
    radius, axial = GetRadius2AndAxial(r1,r2,axial,'','pos')

    plots.append(SimplePlot(name = 'Radius2_vs_Axial', expression = '%s:%s'%(radius,axial), xTitle = 'Axial = %s (mm)' % (axial), yTitle = 'Radius2 = %s (mm)' % (radius), cut = 'EnergyDeposit > 0', draw = 'colz'))
    plots.append(SimplePlot(name = 'NumDeposits_vs_Radius2', expression = 'NumDeposits:%s'%(radius), xTitle = 'Radius2 = %s (mm)' % (radius), yTitle = 'Number of G4 Deposits', cut = 'EnergyDeposit > 0', draw = 'colz'))
    plots.append(SimplePlot(name = 'NumDeposits_vs_Axial', expression = 'NumDeposits:%s'%(axial), xTitle = 'Axial = %s (mm)' % (axial), yTitle = 'Number of G4 Deposits', cut = 'EnergyDeposit > 0', draw = 'colz'))
    

    return plots

def GetClusterPlots():

    plots = []
    plots.append(SimplePlot(name = 'TotalEventEnergy', expression = 'TotalEventEnergy', specifications = '(250,0,5)', xTitle = 'Total Energy (MeV)', cut = 'TotalEventEnergy > 0'))
    plots.append(SimplePlot(name = 'NumClusters', expression = 'NumClusters', xTitle = 'Number of Clusters', cut = 'TotalEventEnergy > 0'))
    plots.append(SimplePlot(name = 'NumClusters_vs_TotalEventEnergy', expression = 'NumClusters:TotalEventEnergy', specifications = '(250,0,5,50,0,50)', xTitle = 'Total Energy (MeV)', yTitle = 'Number of Clusters', cut = 'TotalEventEnergy > 0', draw = 'colz'))
    plots.append(SimplePlot(name = 'Ypos_vs_Xpos', expression = 'Ypos:Xpos', xTitle = 'Xpos (mm)', yTitle = 'Ypos (mm)', cut = 'EnergyDeposit > 0', draw = 'colz'))
    plots.append(SimplePlot(name = 'Xpos_vs_Zpos', expression = 'Xpos:Zpos', xTitle = 'Zpos (mm)', yTitle = 'Xpos (mm)', cut = 'EnergyDeposit > 0', draw = 'colz'))
    plots.append(SimplePlot(name = 'Ypos_vs_Zpos', expression = 'Ypos:Zpos', xTitle = 'Zpos (mm)', yTitle = 'Ypos (mm)', cut = 'EnergyDeposit > 0', draw = 'colz'))

    r1, r2, axial = SimUtils.GetRadialAndAxialCoordinatesString(globalArgs['Card'])
    radius, axial = GetRadius2AndAxial(r1,r2,axial,'','pos')

    plots.append(SimplePlot(name = 'Radius2_vs_Axial', expression = '%s:%s'%(radius,axial), xTitle = 'Axial = %s (mm)' % (axial), yTitle = 'Radius2 = %s (mm)' % (radius), cut = 'EnergyDeposit > 0', draw = 'colz'))
    plots.append(SimplePlot(name = 'NumClusters_vs_Radius2', expression = 'NumClusters:%s'%(radius), xTitle = 'Radius2 = %s (mm)' % (radius), yTitle = 'Number of Clusters', cut = 'EnergyDeposit > 0', draw = 'colz'))
    plots.append(SimplePlot(name = 'NumClusters_vs_Axial', expression = 'NumClusters:%s'%(axial), xTitle = 'Axial = %s (mm)' % (axial), yTitle = 'Number of Clusters', cut = 'EnergyDeposit > 0', draw = 'colz'))

    return plots

def GetReconPlots():

    plots = []
    plots.append(SimplePlot(name = 'ReconFlag', expression = 'ReconFlag', specifications = '(5,-2,3)', xTitle = 'Reconstruction Flag'))
    plots.append(SimplePlot(name = 'TotalReconEnergy', expression = 'TotalReconEnergy', specifications = '(250,0,5)', xTitle = 'Reconstructed Energy (MeV)', cut = 'ReconFlag == 2'))
    plots.append(SimplePlot(name = 'SmearedEnergy', expression = 'SmearedEnergy', specifications = '(250,0,5)', xTitle = 'Smeared Energy (MeV)', cut = 'ReconFlag == 2'))
    plots.append(SimplePlot(name = 'StandoffDistance', expression = 'StandoffDistance', specifications = '(1000,0,1000)', xTitle = 'Standoff Distance (mm)', cut = 'ReconFlag == 2'))
    plots.append(SimplePlot(name = 'NumReconClusters', expression = 'NumReconClusters', xTitle = 'Number of Reconstructed Clusters', cut = 'ReconFlag == 2'))
    plots.append(SimplePlot(name = 'NumReconClusters_vs_TotalEventEnergy', expression = 'NumReconClusters:TotalEventEnergy', specifications = '(250,0,5,20,0,20)', xTitle = 'Total Energy (MeV)', yTitle = 'Number of Reconstructed Clusters', cut = 'ReconFlag == 2', draw = 'colz'))
    plots.append(SimplePlot(name = 'NumReconClusters_vs_TotalReconEnergy', expression = 'NumReconClusters:TotalReconEnergy', specifications = '(250,0,5,20,0,20)', xTitle = 'Reconstructed Energy (MeV)', yTitle = 'Number of Reconstructed Clusters', cut = 'ReconFlag == 2', draw = 'colz'))

    plots.append(SimplePlot(name = 'TotalReconEnergy_ss', expression = 'TotalReconEnergy', specifications = '(250,0,5)', xTitle = 'SS Reconstructed Energy (MeV)', cut = 'ReconFlag == 2 && NumReconClusters == 1'))
    plots.append(SimplePlot(name = 'SmearedEnergy_ss', expression = 'SmearedEnergy', specifications = '(250,0,5)', xTitle = 'SS Smeared Energy (MeV)', cut = 'ReconFlag == 2 && NumReconClusters == 1'))
    plots.append(SimplePlot(name = 'StandoffDistance_ss', expression = 'StandoffDistance', specifications = '(1000,0,1000)', xTitle = 'Standoff Distance (mm)', cut = 'ReconFlag == 2 && NumReconClusters == 1'))
    plots.append(SimplePlot(name = 'TotalReconEnergy_ms', expression = 'TotalReconEnergy', specifications = '(250,0,5)', xTitle = 'MS Reconstructed Energy (MeV)', cut = 'ReconFlag == 2 && NumReconClusters > 1'))
    plots.append(SimplePlot(name = 'SmearedEnergy_ms', expression = 'SmearedEnergy', specifications = '(250,0,5)', xTitle = 'MS Smeared Energy (MeV)', cut = 'ReconFlag == 2 && NumReconClusters > 1'))
    plots.append(SimplePlot(name = 'StandoffDistance_ms', expression = 'StandoffDistance', specifications = '(1000,0,1000)', xTitle = 'Standoff Distance (mm)', cut = 'ReconFlag == 2 && NumReconClusters > 1'))

    return plots


def MakePlots(location,chainList,plots,outFile, canvas = None):

    cutList = []
    for plot in plots:
        if plot.cut != '':
            cutList.append(plot.cut)
    cutSet = set(cutList)
    cutDict = {}
    for c,cut in enumerate(cutSet):
        cutDict[cut] = {}
        for i,isotope in enumerate(chainList):
            chain = chainList[isotope]
            entries = chain.GetEntries()
            listName = 'elist_%d_%d' % (c,i)
            print 'Selecting events for %s in %s with cut "%s" ...'%(isotope, location, cut)
            chain.Draw('>>%s'%(listName),cut,'entrylist')
            cutDict[cut][isotope] = ROOT.gDirectory.Get(listName)
            print '... selected', cutDict[cut][isotope].GetN(), 'events out of a total ', entries, '!'
            #del cutDict[cut][isotope]
    for plot in plots:
        if plot.cut in cutDict:
            plot.entrylist = cutDict[plot.cut]

    #dir = ROOT.gDirectory

    locationDir = outFile.mkdir(location)
    locationDir.cd()

    isotopeDirs = {}

    decayChainDir = None

    for plot in plots:
        for isotope in chainList:
            locationDir.cd()
            if not isotope in isotopeDirs:
                isotopeDirs[isotope] = locationDir.mkdir(isotope)
            isotopeDir = isotopeDirs[isotope]
            chain = chainList[isotope]
            isotopeDir.cd()

            print 'Making %s for %s in %s ...' % (plot.name,isotope,location)
                        
            if plot.entrylist:
                chain.SetEntryList(plot.entrylist[isotope])
            chain.Draw("%s>>%s%s"%(plot.expression,plot.destination,plot.specifications),plot.weight,plot.option)

            destination = isotopeDir.Get(plot.destination)
            destination.GetXaxis().SetTitle(plot.xTitle)
            destination.GetYaxis().SetTitle(plot.yTitle)
            destination.GetZaxis().SetTitle(plot.zTitle)
            destination.SetTitle('%s, %s'%(isotope,location))
            destination.SetName(plot.name)
            destination.Write()

            if globalArgs['WritePdf']:
                canvas.cd()
                destination.Draw(plot.draw)
                canvas.Print(globalArgs['OutputPdfFileName'])


def LoopAllLocations():

    card = globalArgs['Card']

    outFile = ROOT.TFile.Open(globalArgs['OutputFileName'],'recreate')

    canvas = ROOT.TCanvas()
    if globalArgs['WritePdf']:
        canvas.Print('%s['%(globalArgs['OutputPdfFileName']))

    for pos in card.Get('LocationList').split(','):
        location = pos[pos.rfind('/')+1:]
        chainList = GetChainsForLocation(location)

        plots = None
        if globalArgs['Process'].lower() == 'g4': 
            plots = GetG4Plots()
        if globalArgs['Process'].lower() == 'cluster': 
            plots = GetClusterPlots()
        if globalArgs['Process'].lower() == 'recon': 
            plots = GetClusterPlots() + GetReconPlots()

        if len(plots) > 0: 
            MakePlots(location, chainList, plots, outFile, canvas)

    if globalArgs['WritePdf']:
        canvas.Print('%s]'%(globalArgs['OutputPdfFileName']))
    outFile.Close()    

if __name__ == "__main__":

    usage = "usage: python MakeSimplePlotsDecayChain.py -c CardName -p Process -i InputDir -o OutputName"
    parser = OptionParser(usage)
    
    parser.add_option("-c","--card", dest="cardName", nargs=1)
    parser.add_option("-p","--process", dest="processName", nargs=1)
    parser.add_option("-i","--input-dir", dest="inDir", nargs=1)
    parser.add_option("-o","--output", dest="outFileName", nargs=1)
    parser.add_option("-a","--all-isotopes", dest="allIsotopes", action="store_true",default=False)
    parser.add_option("-w","--write-pdf", dest="writePdf", action="store_true",default=False)

    options,args = parser.parse_args()   
    print 'Using options:', options

    if not (options.cardName and options.processName and options.outFileName):
        print 'Missing options...', usage
        sys.exit()

    CatchGlobalArguments(options)
    
    LoopAllLocations()

    
