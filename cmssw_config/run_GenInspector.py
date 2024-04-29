import FWCore.ParameterSet.Config as cms
import glob
import os

process = cms.Process("USER")

process.load("FWCore.MessageService.MessageLogger_cfi")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

dirName = "/eos/user/r/rselvati/SleptonsSneutronsSeveralJets/"
fileList = filter(os.path.isfile, glob.glob(dirName + "*.root"))
fList = []
for f in fileList:
    fs = str(f).replace("/eos/","file:/eos/")
    fList.append(fs)
    
process.source = cms.Source("PoolSource",
                            fileNames = cms.untracked.vstring(
                                fList
                            )
)
process.source.duplicateCheckMode = cms.untracked.string('noDuplicateCheck')
#Output file
process.TFileService = cms.Service("TFileService",
   fileName = cms.string("SleptonsSneutronsSeveralJets_GenInspector.root")
)

process.GenInspector = cms.EDAnalyzer('GenInspector'
                              )

process.p = cms.Path(process.GenInspector)
