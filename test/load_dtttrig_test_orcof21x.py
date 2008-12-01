import FWCore.ParameterSet.Config as cms

process = cms.Process("TEST")

process.PoolDBESSource = cms.ESSource("PoolDBESSource",
    loadAll = cms.bool(True),
    timetype = cms.string('runnumber'),
    toGet = cms.VPSet(
                cms.PSet( record = cms.string('DTTtrigRcd'),
                          tag = cms.string('tTrig_CRAFT_081021_1614_offline') )
    ),
    connect = cms.string('oracle://cms_orcoff_prod/CMS_COND_21X_DT'),
    DBParameters = cms.PSet(
        messageLevel = cms.untracked.int32(0),
        authenticationPath = cms.untracked.string('/afs/cern.ch/cms/DB/conddb')
    )
)

process.source = cms.Source("EmptySource",
    firstRun  = cms.untracked.uint32(1),
    numberEventsInRun  = cms.untracked.uint32(1)
)

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(1)
)

process.get = cms.EDAnalyzer("DTTtrigPrint")

process.p = cms.Path(process.get)


