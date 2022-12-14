import FWCore.ParameterSet.Config as cms

process = cms.Process("USER")

process.load("FWCore.MessageService.MessageLogger_cfi")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

process.source = cms.Source("PoolSource",
                                fileNames = cms.untracked.vstring(
            'file:N2toC1W_GENSIM_2018_tot.root'
                )
                            )

#Output file
process.TFileService = cms.Service("TFileService",
   fileName = cms.string("N2toC1W_GENSIM_2018_output.root")
)

process.GenInspector = cms.EDAnalyzer('GenInspector'
                              )

process.p = cms.Path(process.GenInspector)
