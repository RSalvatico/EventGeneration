import FWCore.ParameterSet.Config as cms

process = cms.Process("USER")

process.load("FWCore.MessageService.MessageLogger_cfi")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

process.source = cms.Source("PoolSource",
                                fileNames = cms.untracked.vstring(
            'file:'
                )
                            )

#Output file
process.TFileService = cms.Service("TFileService",
   fileName = cms.string("InspectGenparticles_output.root")
)

process.InspectGenparticles = cms.EDAnalyzer('InspectGenparticles'
                              )

process.p = cms.Path(process.InspectGenparticles)
