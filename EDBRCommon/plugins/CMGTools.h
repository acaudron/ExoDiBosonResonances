#ifndef __ExoDiBosonResonances_EDBRCommon_CMGTools_h__
#define __ExoDiBosonResonances_EDBRCommon_CMGTools_h__

#include "ExoDiBosonResonances/EDBRCommon/interface/CompoundFactories.h"
#include "ExoDiBosonResonances/EDBRCommon/interface/VJetFactory.h"
//#include "ExoDiBosonResonances/EDBRCommon/interface/PFJetSmearFactory.h"
#include "CMGTools/Common/plugins/PhysicsObjectProducer.h"
#include "CMGTools/Common/interface/GenericPhysicsObjectSelectorDefinition.h"
#include "CommonTools/UtilAlgos/interface/StringCutObjectSelector.h"
#include "CommonTools/UtilAlgos/interface/SingleObjectSelector.h"
#include "CommonTools/UtilAlgos/interface/ObjectSelector.h"

typedef PhysicsObjectProducer<cmg::VJetFactory> VJetPOProducer;
//typedef PhysicsObjectProducer<cmg::PFJetSmearFactory> PFJetSmearPOProducer;
typedef ObjectSelector<cmg::GenericPhysicsObjectSelectorDefinition<cmg::VJet> > CmgVJetSelector;

typedef PhysicsObjectProducer<cmg::DiGenParticleFactory> DiGenParticlePOProducer;
typedef PhysicsObjectProducer<cmg::DiPFJetKinFitFactory> DiPFJetKinFitPOProducer;
typedef PhysicsObjectProducer<cmg::DiJetKinFitFactory> DiJetKinFitPOProducer;

typedef PhysicsObjectProducer<cmg::DiMuonDiJetFactory> DiMuonDiJetPOProducer;
typedef PhysicsObjectProducer<cmg::DiElectronDiJetFactory> DiElectronDiJetPOProducer;
typedef PhysicsObjectProducer<cmg::DiGenParticleDiGenParticleFactory> DiGenParticleDiGenParticlePOProducer;

typedef PhysicsObjectProducer<cmg::DiMuonSingleJetFactory> DiMuonSingleJetPOProducer;
typedef PhysicsObjectProducer<cmg::DiElectronSingleJetFactory> DiElectronSingleJetPOProducer;

typedef PhysicsObjectProducer<cmg::DiMuonDiJetEDBRFactory> DiMuonDiJetEDBRPOProducer;
typedef PhysicsObjectProducer<cmg::DiElectronDiJetEDBRFactory> DiElectronDiJetEDBRPOProducer;
typedef PhysicsObjectProducer<cmg::DiGenParticleDiGenParticleEDBRFactory> DiGenParticleDiGenParticleEDBRPOProducer;

typedef PhysicsObjectProducer<cmg::DiMuonSingleJetEDBRFactory> DiMuonSingleJetEDBRPOProducer;
typedef PhysicsObjectProducer<cmg::DiElectronSingleJetEDBRFactory> DiElectronSingleJetEDBRPOProducer;


#endif
