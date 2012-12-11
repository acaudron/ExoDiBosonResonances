import FWCore.ParameterSet.Config as cms

# JETS  CA8 ----------------------------

from RecoJets.JetProducers.ak5PFJets_cfi import ak5PFJets
ca8PFJetsCHS = ak5PFJets.clone(
    src = 'pfNoPileUp',
    jetPtMin = cms.double(10.0),
    doAreaFastjet = cms.bool(True),
    rParam = cms.double(0.8),
    jetAlgorithm = cms.string("CambridgeAachen"),
    )

jetSource = 'ca8PFJetsCHS'

# corrections 
from PhysicsTools.PatAlgos.recoLayer0.jetCorrFactors_cfi import *
patJetCorrFactorsCA8CHS = patJetCorrFactors.clone()
patJetCorrFactorsCA8CHS.src = jetSource
# will need to add L2L3 corrections in the cfg
patJetCorrFactorsCA8CHS.levels = ['L1FastJet', 'L2Relative', 'L3Absolute']
patJetCorrFactorsCA8CHS.payload = 'AK7PFchs'
patJetCorrFactorsCA8CHS.useRho = True

# parton and gen jet matching

from PhysicsTools.PatAlgos.mcMatchLayer0.jetMatch_cfi import *
patJetPartonMatchCA8CHS = patJetPartonMatch.clone()
patJetPartonMatchCA8CHS.src = jetSource
patJetGenJetMatchCA8CHS = patJetGenJetMatch.clone()
patJetGenJetMatchCA8CHS.src = jetSource
patJetGenJetMatchCA8CHS.matched = 'ca8GenJetsNoNu'

from PhysicsTools.PatAlgos.mcMatchLayer0.jetFlavourId_cff import *
patJetPartonAssociationCA8CHS = patJetPartonAssociation.clone()
patJetPartonAssociationCA8CHS.jets = jetSource

# pat jets

from PhysicsTools.PatAlgos.producersLayer1.jetProducer_cfi import *
patJetsCA8CHS = patJets.clone()
patJetsCA8CHS.jetSource = jetSource
patJetsCA8CHS.addJetCharge = False
patJetsCA8CHS.embedCaloTowers = False
patJetsCA8CHS.embedPFCandidates = False
patJetsCA8CHS.addAssociatedTracks = False
patJetsCA8CHS.addBTagInfo = False
patJetsCA8CHS.addDiscriminators = False
patJetsCA8CHS.getJetMCFlavour = False
patJetsCA8CHS.jetCorrFactorsSource = cms.VInputTag(cms.InputTag('patJetCorrFactorsCA8CHS'))
patJetsCA8CHS.genPartonMatch = cms.InputTag('patJetPartonMatchCA8CHS')
patJetsCA8CHS.genJetMatch = cms.InputTag('patJetGenJetMatchCA8CHS')

from PhysicsTools.PatAlgos.selectionLayer1.jetSelector_cfi import *
selectedPatJetsCA8CHS = selectedPatJets.clone()
selectedPatJetsCA8CHS.src = 'patJetsCA8CHS'
selectedPatJetsCA8CHS.cut = 'pt()>20'

from RecoJets.Configuration.RecoGenJets_cff import ak7GenJetsNoNu
ca8GenJetsNoNu = ak7GenJetsNoNu.clone()
ca8GenJetsNoNu.rParam = 0.8
ca8GenJetsNoNu.jetAlgorithm = "CambridgeAachen"

from RecoJets.Configuration.GenJetParticles_cff import genParticlesForJetsNoNu
jetMCSequenceCA8CHS = cms.Sequence(
    patJetPartonMatchCA8CHS +
    genParticlesForJetsNoNu +
    ca8GenJetsNoNu +
    patJetGenJetMatchCA8CHS
    )

PATCMGJetSequenceCA8CHS = cms.Sequence(
    ca8PFJetsCHS +
    jetMCSequenceCA8CHS +
    patJetCorrFactorsCA8CHS +
    patJetsCA8CHS +
    selectedPatJetsCA8CHS
    )