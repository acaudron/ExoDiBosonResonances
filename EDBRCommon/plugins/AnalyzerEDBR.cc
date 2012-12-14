#include "ExoDiBosonResonances/EDBRCommon/plugins/AnalyzerEDBR.h"


AnalyzerEDBR::AnalyzerEDBR(const edm::ParameterSet &ps){

    debug_    = ps.getParameter<bool>("debug");
    if(debug_)    cout << "AnalyzerEDBR constructor 555..." << endl;
    cout<<"pippo1"<<endl;
    isMC_       = ps.getParameter<bool>("isMC");
    treatVBFAsMultiple_    = ps.getParameter<bool>("treatVBFAsMultiple");
    Ngen_     = ps.getParameter<unsigned int>("Ngen");
    xsec_     = ps.getParameter<double>("xsec"); // in fb
    cout<<"pippo2"<<endl;
    cat_             = ps.getParameter<std::string>("EventCategory");
    XEEColl_         = ps.getParameter<edm::InputTag>("EDBREEJJColl");
    XEENoKinFitColl_ = ps.getParameter<edm::InputTag>("EDBREEJJNoKinFitColl");
    XEELDMap_        = ps.getParameter<edm::InputTag>("EDBREEJJLDValueMap");
    XMMColl_         = ps.getParameter<edm::InputTag>("EDBRMMJJColl");
    XMMNoKinFitColl_ = ps.getParameter<edm::InputTag>("EDBRMMJJNoKinFitColl");
    XMMLDMap_        = ps.getParameter<edm::InputTag>("EDBRMMJJLDValueMap");
    XEEJColl_        = ps.getParameter<edm::InputTag>("EDBREEJColl");
    XEEJLDMap_       = ps.getParameter<edm::InputTag>("EDBREEJLDValueMap");
    XMMJColl_        = ps.getParameter<edm::InputTag>("EDBRMMJColl");
    XMMJLDMap_       = ps.getParameter<edm::InputTag>("EDBRMMJLDValueMap");
    XQGMap_          = ps.getParameter<edm::InputTag>("EDBRQGValueMap");
    //XEENoKinFitLDMap_=ps.getParameter<edm::InputTag>("EDBREENoKinFitLDValueMap");
    //XMMNoKinFitLDMap_=ps.getParameter<edm::InputTag>("EDBRMMNoKinFitLDValueMap");
    
    cout<<"pippo3"<<endl;
    if(XEELDMap_.label()=="" ||XMMLDMap_.label()=="" ) readLDFromUserFloat_=true;
    else readLDFromUserFloat_=false;
    
    if(XQGMap_.label()=="") readQGFromUserFloat_=true;
    else readQGFromUserFloat_=false;
    

    outFileName_ = ps.getParameter<string>("outFileName");
    outFile_ = new TFile(outFileName_.c_str(),"recreate");
    if(debug_)cout<<"Storing output TTree in "<<outFileName_.c_str()<<endl;
    
    triggerNames_ = ps.getParameter< vector<string> >("triggerNames");
    
    if(cat_!=""){
      if( cat_!="mmjj" &&cat_!="eejj" && cat_!="mmj" && cat_!="eej"){
      throw cms::Exception("AnalyzerEDBR: Wrong event category passed as input. Possibilities are: mmjj, eejj, mmj, eej");
    }
    }

    if(debug_)cout<<"Initializing"<<endl;

    init();
    if(debug_)cout<<"Initialization is over"<<endl;

  }//end constructor


void AnalyzerEDBR::analyze(edm::Event const& iEvent, edm::EventSetup const& eventSetup){

  if(debug_) cout<<"\n\nAnalyzing event"<<endl;

  initDataMembers();


 
  nevent = iEvent.eventAuxiliary().event();
  run    = iEvent.eventAuxiliary().run();
  ls     = iEvent.eventAuxiliary().luminosityBlock();
  if(debug_) cout<<endl<<" Run "<<run<<"  Event "<<nevent<<endl;


  // GET VERTICES
  edm::Handle<reco::VertexCollection> vertexCollection;
  if(iEvent.getByLabel("offlinePrimaryVertices",vertexCollection))  nvtx=vertexCollection->size();
  else{
    if(debug_)cout<<"WARNING: VertexCollection called \'offlinePrimaryVertices\' NOT FOUND !"<<endl;
    nvtx=0;
  }
  npu=-1;

//total number of pre-selected jets in the event
  edm::Handle<std::vector<cmg::PFJet> > allJets;
  iEvent.getByLabel("jetIDJet", allJets);
  njets = allJets->size();

  // GET MISSING ET
  edm::Handle<edm::View<pat::MET> > metHandle;
  iEvent.getByLabel("patMETs", metHandle);
  met     = metHandle->at(0).pt();
  metSign = metHandle->at(0).significance(); 

  analyzeTrigger(iEvent, eventSetup);

  bool eleEvent   = elePath_; //&&(cat_=="eejj" || cat_=="eej")
  bool muEvent    = muPath_;
  bool goodKinFit = true;



  edm::Handle<std::vector<reco::GenParticle> > genParticles;
  iEvent.getByLabel(std::string("genParticles"), genParticles);
  reco::GenParticle genEDBR;

  for(std::vector<reco::GenParticle>::const_iterator genParticle=genParticles->begin(); genParticle!=genParticles->end(); ++genParticle){
    if(genParticle->pdgId()==25||genParticle->pdgId()==39) genEDBR=(*genParticle);
      // if(debug_) cout<<"particle "<<genParticle->pdgId()<<" status "<<genParticle->status()<<endl;
  }

  // edm::Handle<edm::ValueMap<float> > qgmap;
  // if(anyPath_){
  //  if(!readQGFromUserFloat_)iEvent.getByLabel(HiggsQGMap_, qgmap);
  // }



  if(muPath_){
       
      lep=1; 

      if(singleJetPath_){
	edm::Handle<edm::View< cmg::DiMuonSingleJetEDBR > > finalEDBRcand;
	iEvent.getByLabel(XMMJColl_        , finalEDBRcand  );  // With kinfit

	
	int nCandidates=finalEDBRcand->size();
	if (nCandidates > nMaxCand) nCandidates = nMaxCand;
	if(debug_)cout<<"read from MUON event, there are "<<nCandidates<<" H cands"<<endl;
	//  if(nCandidates>0){
	//  if(muPath_)    muEvent = true;
	//  if(elePath_)   eleEvent = true;
	// }
	int ih = 0;
	for(int iih=0;iih<nCandidates;iih++){
	  
	  edm::RefToBase<cmg::DiMuonSingleJetEDBR> edbrM =finalEDBRcand->refAt(iih);
	  
	  if(edbrM->nJets()!=1){
	    throw cms::Exception("Mismatched param") <<"Event in SingleJet Path has "<<edbrM->nJets()
						     <<" jets"<<std::endl;  
	  }
	  nXjets[ih]=edbrM->nJets();
 
	  analyzeGeneric(edbrM, ih,goodKinFit);
	  analyzeSingleJet(edbrM,ih);        
	  analyzeMuon(edbrM,ih);

	
	ih++;
      }//end loop on candidates
	// if(debug_)cout<<"Adding "<<ih<<" muCands"<<endl;
	nCands += ih;

      }//end if singleJetPath

      if(doubleJetPath_){
	edm::Handle<edm::View< cmg::DiMuonDiJetEDBR > > finalEDBRcand;
	edm::Handle<edm::View< cmg::DiMuonDiJetEDBR > > finalEDBRcand_2;
	iEvent.getByLabel(XMMColl_        , finalEDBRcand  );  // With kinfit
	iEvent.getByLabel(XMMNoKinFitColl_, finalEDBRcand_2);  // Without kinfit
	
	int nCandidates=finalEDBRcand->size();
	if (nCandidates > nMaxCand) nCandidates = nMaxCand;
	if(debug_)cout<<"read from MUON event, there are "<<nCandidates<<" H cands"<<endl;
	//  if(nCandidates>0){
	//  if(muPath_)    muEvent = true;
	//  if(elePath_)   eleEvent = true;
	// }
	int ih = 0;
	for(int iih=0;iih<nCandidates;iih++){
	  
	  edm::RefToBase<cmg::DiMuonDiJetEDBR> edbrM =finalEDBRcand->refAt(iih);
	  edm::RefToBase<cmg::DiMuonDiJetEDBR> edbrM_2 =finalEDBRcand_2->refAt(iih);
	  
	  if(edbrM->nJets()!=2){
	    throw cms::Exception("Mismatched param") <<"Event in DoubleJet Path has "<<edbrM->nJets()
						     <<" jets"<<std::endl;  
	  }
	  nXjets[ih]=edbrM->nJets();
	  analyzeGeneric(edbrM,ih,goodKinFit);
	  analyzeDoubleJet(edbrM, edbrM_2,ih);        
	  analyzeMuon(edbrM,ih);

	
	ih++;
      }//end loop on candidates
	// if(debug_)cout<<"Adding "<<ih<<" muCands"<<endl;
	nCands += ih;
      }//end if doubleJetPath

  }//end if mmjj


  //  if(cat_=="eejj"){
  if(elePath_){
    edm::Handle<edm::View< cmg::DiElectronDiJetEDBR > > finalEDBRcand;
    edm::Handle<edm::View< cmg::DiElectronDiJetEDBR > > finalEDBRcand_2;
    iEvent.getByLabel(XEEColl_        , finalEDBRcand  );  // With kinfit
    iEvent.getByLabel(XEENoKinFitColl_, finalEDBRcand_2);  // Without kinfit
 
    int nCandidates=finalEDBRcand->size();
    if (nCandidates > nMaxCand) nCandidates = nMaxCand-1;
    if(debug_)cout<<"read from ELE event, there are "<<nCandidates<<" H cands"<<endl;
    //  if(nCandidates>0){
    //  if(muPath_)    muEvent = true;
    //  if(elePath_)   eleEvent = true;
    // }
    int ih = 0;
    for(int iih=0;iih<nCandidates;iih++){
       
      lep=0; 
      edm::RefToBase<cmg::DiElectronDiJetEDBR> edbrE =finalEDBRcand->refAt(iih);
      edm::RefToBase<cmg::DiElectronDiJetEDBR> edbrE_2 =finalEDBRcand_2->refAt(iih);
      nXjets[ih]=edbrE->nJets();
      //      if(nXjets[ih]==1)analyzeSingleJet(edbrE,ih);  
      // else if(nXjets[ih]==2)

//      else{
//	std::cout<<"What the hell is this EDBR(Ele) ? I see it is made wtih "<<nXjets[ih]
//		 <<" jets. Unrecognized value, skipping"<<std::endl;
//	continue;
//     }

      analyzeGeneric(edbrE, ih,goodKinFit);
      analyzeDoubleJet(edbrE,edbrE_2,ih);        
      analyzeElectron(edbrE,ih);
      ih++;

    
    }//end loop on candidates
    // if(debug_)cout<<"Adding "<<ih<<" eleCands"<<endl;
    nCands += ih;
  }//end if eejj


  //EVENT WEIGHTS
  if(isMC_){
    // Ngen=Ngen_;
    lumiw = xsec_/Ngen_;
    edm::Handle<GenEventInfoProduct> hGenEvtInfo;
    // cout<<"Am I crashing ?  "<<flush;
    if(iEvent.getByLabel("generator",hGenEvtInfo)){
      genw=hGenEvtInfo->weights()[0];
      // cout<<"  No ! "<<genw<<endl;
    }
  }
  if(debug_)  cout<<"lumi weight="<<lumiw<<"  PU weight="<<PU<<endl;
  w  = PU *HLTSF*genw*lumiw;
  wA = PUA*HLTSF*genw*lumiw;
  wB = PUB*HLTSF*genw*lumiw;


  bool passCuts=true;
  bool storeEvt=goodKinFit && (muPath_ || elePath_) && lep<2 && passCuts;
  if(storeEvt){
    //  if(debug_)cout<<"Filling the tree ("<<nCands<<endl;//" cands -> pTlep1="<< ptlep1[nCands-1]<<")"<<endl;
    outTree_->Fill(); 
    //  if(debug_)cout<<" filled."<<endl;
  }

  /// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&

 if(debug_)cout<<"Finished AnalyzerEDBR::analyze for Run "<<run<<"  Event "<<nevent<<endl;
}//
//end AnalyzerEDBR::analyze





void AnalyzerEDBR::init(){

  initTree();



}//end init()


void AnalyzerEDBR::initTree(){

  if(debug_)cout<<"creating the output TTree"<<endl;
  outTree_ = new TTree("SelectedCandidates","angles etc.");
  outTree_->Branch("nCands"          ,&nCands        ,"nCands/I"               );
  outTree_->Branch("cosThetaStar"    ,&hs            ,"cosThetaStar[nCands]/D" );
  outTree_->Branch("cosTheta1"       ,&h1            ,"cosTheta1[nCands]/D"    );
  outTree_->Branch("cosTheta2"       ,&h2            ,"cosTheta2[nCands]/D"    );
  outTree_->Branch("phi"             ,&phi           ,"phi[nCands]/D"          );
  outTree_->Branch("phiStar1"        ,&phiS1         ,"phiStar1[nCands]/D"     );
  outTree_->Branch("ptlep1"          ,&ptlep1        ,"ptlep1[nCands]/D"       );
  outTree_->Branch("ptlep2"          ,&ptlep2        ,"ptlep2[nCands]/D"       );
  outTree_->Branch("ptjet1"          ,&ptjet1        ,"ptjet1[nCands]/D"       );
  outTree_->Branch("ptjet2"          ,&ptjet2        ,"ptjet2[nCands]/D"       );
  outTree_->Branch("ptZll"           ,&ptZll         ,"ptZll[nCands]/D"        );
  outTree_->Branch("ptZjj"           ,&ptZjj         ,"ptZjj[nCands]/D"        );
  outTree_->Branch("yZll"            ,&yZll          ,"yZll[nCands]/D"         );
  outTree_->Branch("yZjj"            ,&yZjj          ,"yZjj[nCands]/D"         );
  outTree_->Branch("phiZll"          ,&phiZll        ,"phiZll[nCands]/D"       );
  outTree_->Branch("phiZjj"          ,&phiZjj        ,"phiZjj[nCands]/D"       );
  outTree_->Branch("etalep1"         ,&etalep1       ,"etalep1[nCands]/D"      );
  outTree_->Branch("etalep2"         ,&etalep2       ,"etalep2[nCands]/D"      );
  outTree_->Branch("etajet1"         ,&etajet1       ,"etajet1[nCands]/D"      );
  outTree_->Branch("etajet2"         ,&etajet2       ,"etajet2[nCands]/D"      );
  outTree_->Branch("lep"             ,&lep           ,"lep/D"                  );
  outTree_->Branch("region"          ,&reg           ,"region[nCands]/D"       );
  outTree_->Branch("mZZ"             ,&mzz           ,"mZZ[nCands]/D"          );
  outTree_->Branch("mZZNoKinFit"     ,&mzzNoKinFit   ,"mZZNoKinFit[nCands]/D"  );
  outTree_->Branch("ptmzz"           ,&ptmzz         ,"ptmzz[nCands]/D"        );
  outTree_->Branch("ptmzzNoKinFit"   ,&ptmzzNoKinFit ,"ptmzzNoKinFit[nCands]/D");
  outTree_->Branch("mLL"             ,&mll           ,"mLL[nCands]/D"          );
  outTree_->Branch("mJJ"             ,&mjj           ,"mJJ[nCands]/D"          );
  outTree_->Branch("mJJNoKinFit"     ,&mjjNoKinFit   ,"mJJNoKinFit[nCands]/D"  );
  outTree_->Branch("met"             ,&met           ,"met/D"                  );
  outTree_->Branch("metSign"         ,&metSign       ,"metSign/D"              );
  outTree_->Branch("nBTags"          ,&btag          ,"nBTags[nCands]/D"       );
  outTree_->Branch("deltaREDBR"     ,&deltaREDBR   ,"deltaREDBR[nCands]/D"  );
  outTree_->Branch("deltaRleplep"    ,&deltaRleplep  ,"deltaRleplep[nCands]/D" );
  outTree_->Branch("deltaRjetjet"    ,&deltaRjetjet  ,"deltaRjetjet[nCands]/D" );
  outTree_->Branch("qgProduct"       ,&qgProduct     ,"qgProduct[nCands]/D"    );
  outTree_->Branch("qgjet1"          ,&qgjet1        ,"qgjet1[nCands]/D"       );
  outTree_->Branch("qgjet2"          ,&qgjet2        ,"qgjet2[nCands]/D"       );
  outTree_->Branch("betajet1"        ,&betajet1      ,"betajet1[nCands]/D"     ); 
  outTree_->Branch("betajet2"        ,&betajet2      ,"betajet2[nCands]/D"     ); 
  outTree_->Branch("puMvajet1"       ,&puMvajet1     ,"puMvajet1[nCands]/D"    ); 
  outTree_->Branch("puMvajet2"       ,&puMvajet2     ,"puMvajet2[nCands]/D"    ); 
  outTree_->Branch("nXjets"       ,&nXjets     ,"nXjets[nCands]/I"    ); 
  outTree_->Branch("prunedmass"       ,&prunedmass    ,"prunedmass[nCands]/D"    ); 
  outTree_->Branch("mdrop"       ,&mdrop     ,"mdrop[nCands]/D"    ); 
  outTree_->Branch("nsubj12"       ,&nsubj12    ,"nsubj12[nCands]/D"    ); 
  outTree_->Branch("nsubj23"       ,&nsubj23     ,"nsubj23[nCands]/D"    ); 
  outTree_->Branch("tau1"       ,&tau1     ,"tau1[nCands]/D"    ); 
  outTree_->Branch("tau2"       ,&tau2    ,"tau2[nCands]/D"    ); 
  outTree_->Branch("qjet"       ,&qjet    ,"qjet[nCands]/D"    ); 
  outTree_->Branch("isolep1"         ,&isolep1       ,"isolep1[nCands]/D"      ); 
  outTree_->Branch("isolep2"         ,&isolep2       ,"isolep2[nCands]/D"      ); 
  outTree_->Branch("eleMVAId1"       ,&eleMVAId1     ,"eleMVAId1[nCands]/D"    );
  outTree_->Branch("eleMVAId2"       ,&eleMVAId2     ,"eleMVAId2[nCands]/D"    );
  outTree_->Branch("LD"              ,&LD            ,"LD[nCands]/D"           );
  //outTree_->Branch("aplanarity"      ,&aplanarity    ,"aplanarity[nCands]/D"   );
  // outTree_->Branch("sphericity"      ,&sphericity    ,"sphericity[nCands]/D"   );
  // outTree_->Branch("centrality"      ,&centrality    ,"centrality[nCands]/D"   );
  outTree_->Branch("q1fl"            ,&q1fl          ,"q1fl[nCands]/I"         );
  outTree_->Branch("q2fl"            ,&q2fl          ,"q2fl[nCands]/I"         );
  //outTree_->Branch("jjfl"            ,&jjfl          ,"jjfl[nCands]/I"         );
  outTree_->Branch("MCmatch"         ,&MCmatch       ,"MCmatch[nCands]/D"      );
  outTree_->Branch("nVtx"            ,&nvtx          ,"nVtx/i"                 );
  outTree_->Branch("nJets"           ,&njets         ,"nJets/i"                );
  outTree_->Branch("nPU"             ,&npu           ,"nPU/i"                  );
  outTree_->Branch("HLTweight"       ,&HLTSF         ,"HLTweight/D"            ); 
  outTree_->Branch("PUweight"        ,&PU            ,"PUweight/D"             ); 
  outTree_->Branch("PUweight2012A"   ,&PUA           ,"PUweight2012A/D"        ); 
  outTree_->Branch("PUweight2012B"   ,&PUB           ,"PUweight2012B/D"        );
  outTree_->Branch("LumiWeight"      ,&lumiw          ,"LumiWeight/D"           );  // For correct lumi scaling
  outTree_->Branch("GenWeight"       ,&genw          ,"GenWeight/D"            );  // Gen level MC weights
  outTree_->Branch("weight"          ,&w             ,"weight/D"               );  // Product of PU and lumi weights
  outTree_->Branch("weight2012A"     ,&wA            ,"weight2012A/D"          );
  outTree_->Branch("weight2012B"     ,&wB            ,"weight2012B/D"          );
  outTree_->Branch("event"           ,&nevent        ,"event/i"                );
  outTree_->Branch("run"             ,&run           ,"run/i"                  );
  outTree_->Branch("ls"              ,&ls            ,"ls/i"                   );

  if(triggerNames_.size()>0){
  if(debug_)cout<<"Adding branches with trigger names"<<endl;
  //flags for telling if the event passed a certain trig path
  char triggerNamePiuI[200];
  for(unsigned int iTrig=0;iTrig<triggerNames_.size();iTrig++) {
    sprintf(triggerNamePiuI,"%s/I",(triggerNames_.at(iTrig)).c_str());
    outTree_->Branch((triggerNames_.at(iTrig)).c_str(),        &triggerRes[iTrig],       triggerNamePiuI);
  }

  }

}//end initTree()

void AnalyzerEDBR::initDataMembers(){

 lep   = -99;
  lumiw  =   1.0;
  PU    =   1.0;
  PUA   =   1.0;
  PUB   =   11.0;
  genw  =   1.0;
  w     =   0.0;
  wA    =   1.0;
  wB    =   1.0;
  HLTSF =   1.0;
  nCands=0;
}//end AnalyzeEDBR::initDataMembers()

void AnalyzerEDBR::analyzeTrigger(edm::Event const& iEvent, edm::EventSetup const& eventSetup){

  edm::Handle<edm::TriggerResults> HLTR;
  iEvent.getByLabel(edm::InputTag("TriggerResults","","HLT"), HLTR);

  for(unsigned int iTrig=0;iTrig<triggerNames_.size();iTrig++) {
    int triggerIndex = (int)hltConfig.triggerIndex((triggerNames_.at(iTrig)).c_str()) ;
    triggerRes[iTrig] = 0;
    // triggerIndex must be less than the size of HLTR or you get a CMSException: _M_range_check
    if (triggerIndex < (int)HLTR->size()) triggerRes[iTrig] = (int)HLTR->accept(triggerIndex);
  }

  //check which analysis paths the event passed.
  //this matters as we can ask for some specific things according to the 
  //path (for example electron specific quantitites for cands passing the eejj path)

  preselM_=iEvent.triggerResultsByName("CMG").accept("preselMuPath");
  finalM_=false;// iEvent.triggerResultsByName("CMG").accept("cmgXZZMM");
  sbM_=false;//iEvent.triggerResultsByName("CMG").triggerIndex("cmgXZZMMSideband")!=iEvent.triggerResultsByName("CMG").size() &&     iEvent.triggerResultsByName("CMG").accept("cmgXZZMMSideband");
  preselE_=iEvent.triggerResultsByName("CMG").accept("preselElePath");
  finalE_=false;// iEvent.triggerResultsByName("CMG").accept("cmgXZZEE");
  sbE_=false;//iEvent.triggerResultsByName("CMG").triggerIndex("cmgXZZEESideband")!=iEvent.triggerResultsByName("CMG").size() &&  iEvent.triggerResultsByName("CMG").accept("cmgXZZEESideband");

  preselM1J_=iEvent.triggerResultsByName("CMG").accept("preselMuMergedPath");
  finalM1J_=false;// iEvent.triggerResultsByName("CMG").accept("cmgXZZMMJ");
  sbM1J_=false;//iEvent.triggerResultsByName("CMG").triggerIndex("cmgXZZMMJSideband")!=iEvent.triggerResultsByName("CMG").size() &&     iEvent.triggerResultsByName("CMG").accept("cmgXZZMMJSideband");
  preselE1J_=iEvent.triggerResultsByName("CMG").accept("preselEleMergedPath");
  finalE1J_=false;// iEvent.triggerResultsByName("CMG").accept("cmgXZZEEJ");
  sbE1J_=false;//iEvent.triggerResultsByName("CMG").triggerIndex("cmgXZZEEJSideband")!=iEvent.triggerResultsByName("CMG").size() &&  iEvent.triggerResultsByName("CMG").accept("cmgXZZEEJSideband");



  muPath_=false;
  elePath_=false;
  anyPath_=false;
  singleJetPath_=false;
  doubleJetPath_=false;
  if(preselM_ || finalM_ || sbM_||preselM1J_ || finalM1J_ || sbM1J_)muPath_=true;
  if(preselE_ || finalE_ || sbE_||preselE1J_ || finalE1J_ || sbE1J_)elePath_=true;
  if(preselE1J_ || finalE1J_ || sbE1J_|| preselM1J_ || finalM1J_ || sbM1J_ )singleJetPath_=true;
  if(preselE_ || finalE_ || sbE_|| preselM_ || finalM_ || sbM_ )doubleJetPath_=true;
  if(muPath_ || elePath_) anyPath_=true;

}//end  AnalyzeEDBR::analyzeTrigger()

/*********************
void AnalyzerEDBR::analyzeMuon(edm::RefToBase<cmg::DiMuonDiJetEDBR > edbr, int ih){
  //nothing to be done
  //
  //
  if(debug_)cout<<"AnalyzerEDBR::analyzeMuon"<<endl;
  //dummy for muons 
  eleMVAId1[ih] = -1.0;
  eleMVAId2[ih] = -1.0;
}

//void AnalyzerEDBR::analyzeElectron(edm::RefToBase<cmg::DiElectronDiJetEDBR > edbr, int ih){
void AnalyzerEDBR::analyzeElectron(T edbr, int ih){

  if(debug_)cout<<"AnalyzerEDBR::analyzeElectron"<<endl;
  bool highptLep1=true;
  if(edbr->leg1().leg2().pt()>edbr->leg1().leg1().pt())highptLep1=false;
  

  if(highptLep1){
    eleMVAId1[ih] = edbr->leg1().leg1().mvaTrigV0(); 
    eleMVAId2[ih] = edbr->leg1().leg2().mvaTrigV0();
  } 
  else{
    eleMVAId1[ih] = edbr->leg1().leg2().mvaTrigV0(); 
    eleMVAId2[ih] = edbr->leg1().leg1().mvaTrigV0();
  }
}
*************************/


double AnalyzerEDBR::deltaR(reco::LeafCandidate p1,reco::LeafCandidate p2){
  double deltaEta = fabs(p1.eta()-p2.eta());
  double deltaPhi = (p1.phi()-p2.phi());
  while (deltaPhi > 3.14) deltaPhi -= 2*3.14;
  while (deltaPhi <= -3.14) deltaPhi += 2*3.14;     
  return sqrt(deltaPhi*deltaPhi + deltaEta*deltaEta);
}
double AnalyzerEDBR::deltaR(double phi1,double eta1,double phi2,double eta2){
  double deltaEta = fabs(eta1-eta2);
  double deltaPhi = (phi1-phi2);
  while (deltaPhi > 3.14) deltaPhi -= 2*3.14;
  while (deltaPhi <= -3.14) deltaPhi += 2*3.14;     
  return sqrt(deltaPhi*deltaPhi + deltaEta*deltaEta);
}



#include "FWCore/Framework/interface/MakerMacros.h"
DEFINE_FWK_MODULE(AnalyzerEDBR);
