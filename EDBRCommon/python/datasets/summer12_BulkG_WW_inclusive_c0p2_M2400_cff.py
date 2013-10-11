import FWCore.ParameterSet.Config as cms

cmgFiles = cms.untracked.vstring()
source = cms.Source("PoolSource",
                    noEventSort = cms.untracked.bool(True),
                    duplicateCheckMode = cms.untracked.string("noDuplicateCheck"),
                    fileNames = cmgFiles
                   )

cmgFiles.extend([
    '/store/cmst3/group/exovv/santanas/EDBR_PATtuple_edbr_zz_20130605_Summer12MC_BulkGravitonsWW_20130916_175629/santanas/BulkG_WW_inclusive_c0p2_M2400_GENSIM/EDBR_PATtuple_edbr_zz_20130605/1b325ddfb984c14533be7920e22baeef/BulkG_WW_inclusive_c0p2_M2400_GENSIM__shuai-BulkG_WW_inclusive_c0p2_M2400_AODSIM-2c74483358b1f8805e5601fc325d256c__USER_10_1_57x.root',
    '/store/cmst3/group/exovv/santanas/EDBR_PATtuple_edbr_zz_20130605_Summer12MC_BulkGravitonsWW_20130916_175629/santanas/BulkG_WW_inclusive_c0p2_M2400_GENSIM/EDBR_PATtuple_edbr_zz_20130605/1b325ddfb984c14533be7920e22baeef/BulkG_WW_inclusive_c0p2_M2400_GENSIM__shuai-BulkG_WW_inclusive_c0p2_M2400_AODSIM-2c74483358b1f8805e5601fc325d256c__USER_11_1_MVr.root',
    '/store/cmst3/group/exovv/santanas/EDBR_PATtuple_edbr_zz_20130605_Summer12MC_BulkGravitonsWW_20130916_175629/santanas/BulkG_WW_inclusive_c0p2_M2400_GENSIM/EDBR_PATtuple_edbr_zz_20130605/1b325ddfb984c14533be7920e22baeef/BulkG_WW_inclusive_c0p2_M2400_GENSIM__shuai-BulkG_WW_inclusive_c0p2_M2400_AODSIM-2c74483358b1f8805e5601fc325d256c__USER_12_1_1Hk.root',
    '/store/cmst3/group/exovv/santanas/EDBR_PATtuple_edbr_zz_20130605_Summer12MC_BulkGravitonsWW_20130916_175629/santanas/BulkG_WW_inclusive_c0p2_M2400_GENSIM/EDBR_PATtuple_edbr_zz_20130605/1b325ddfb984c14533be7920e22baeef/BulkG_WW_inclusive_c0p2_M2400_GENSIM__shuai-BulkG_WW_inclusive_c0p2_M2400_AODSIM-2c74483358b1f8805e5601fc325d256c__USER_13_1_dLu.root',
    '/store/cmst3/group/exovv/santanas/EDBR_PATtuple_edbr_zz_20130605_Summer12MC_BulkGravitonsWW_20130916_175629/santanas/BulkG_WW_inclusive_c0p2_M2400_GENSIM/EDBR_PATtuple_edbr_zz_20130605/1b325ddfb984c14533be7920e22baeef/BulkG_WW_inclusive_c0p2_M2400_GENSIM__shuai-BulkG_WW_inclusive_c0p2_M2400_AODSIM-2c74483358b1f8805e5601fc325d256c__USER_14_1_Fm7.root',
    '/store/cmst3/group/exovv/santanas/EDBR_PATtuple_edbr_zz_20130605_Summer12MC_BulkGravitonsWW_20130916_175629/santanas/BulkG_WW_inclusive_c0p2_M2400_GENSIM/EDBR_PATtuple_edbr_zz_20130605/1b325ddfb984c14533be7920e22baeef/BulkG_WW_inclusive_c0p2_M2400_GENSIM__shuai-BulkG_WW_inclusive_c0p2_M2400_AODSIM-2c74483358b1f8805e5601fc325d256c__USER_15_1_z3e.root',
    '/store/cmst3/group/exovv/santanas/EDBR_PATtuple_edbr_zz_20130605_Summer12MC_BulkGravitonsWW_20130916_175629/santanas/BulkG_WW_inclusive_c0p2_M2400_GENSIM/EDBR_PATtuple_edbr_zz_20130605/1b325ddfb984c14533be7920e22baeef/BulkG_WW_inclusive_c0p2_M2400_GENSIM__shuai-BulkG_WW_inclusive_c0p2_M2400_AODSIM-2c74483358b1f8805e5601fc325d256c__USER_16_1_Ksn.root',
    '/store/cmst3/group/exovv/santanas/EDBR_PATtuple_edbr_zz_20130605_Summer12MC_BulkGravitonsWW_20130916_175629/santanas/BulkG_WW_inclusive_c0p2_M2400_GENSIM/EDBR_PATtuple_edbr_zz_20130605/1b325ddfb984c14533be7920e22baeef/BulkG_WW_inclusive_c0p2_M2400_GENSIM__shuai-BulkG_WW_inclusive_c0p2_M2400_AODSIM-2c74483358b1f8805e5601fc325d256c__USER_17_1_g4g.root',
    '/store/cmst3/group/exovv/santanas/EDBR_PATtuple_edbr_zz_20130605_Summer12MC_BulkGravitonsWW_20130916_175629/santanas/BulkG_WW_inclusive_c0p2_M2400_GENSIM/EDBR_PATtuple_edbr_zz_20130605/1b325ddfb984c14533be7920e22baeef/BulkG_WW_inclusive_c0p2_M2400_GENSIM__shuai-BulkG_WW_inclusive_c0p2_M2400_AODSIM-2c74483358b1f8805e5601fc325d256c__USER_18_1_Fwa.root',
    '/store/cmst3/group/exovv/santanas/EDBR_PATtuple_edbr_zz_20130605_Summer12MC_BulkGravitonsWW_20130916_175629/santanas/BulkG_WW_inclusive_c0p2_M2400_GENSIM/EDBR_PATtuple_edbr_zz_20130605/1b325ddfb984c14533be7920e22baeef/BulkG_WW_inclusive_c0p2_M2400_GENSIM__shuai-BulkG_WW_inclusive_c0p2_M2400_AODSIM-2c74483358b1f8805e5601fc325d256c__USER_19_1_RH9.root',
    '/store/cmst3/group/exovv/santanas/EDBR_PATtuple_edbr_zz_20130605_Summer12MC_BulkGravitonsWW_20130916_175629/santanas/BulkG_WW_inclusive_c0p2_M2400_GENSIM/EDBR_PATtuple_edbr_zz_20130605/1b325ddfb984c14533be7920e22baeef/BulkG_WW_inclusive_c0p2_M2400_GENSIM__shuai-BulkG_WW_inclusive_c0p2_M2400_AODSIM-2c74483358b1f8805e5601fc325d256c__USER_1_1_QTR.root',
    '/store/cmst3/group/exovv/santanas/EDBR_PATtuple_edbr_zz_20130605_Summer12MC_BulkGravitonsWW_20130916_175629/santanas/BulkG_WW_inclusive_c0p2_M2400_GENSIM/EDBR_PATtuple_edbr_zz_20130605/1b325ddfb984c14533be7920e22baeef/BulkG_WW_inclusive_c0p2_M2400_GENSIM__shuai-BulkG_WW_inclusive_c0p2_M2400_AODSIM-2c74483358b1f8805e5601fc325d256c__USER_20_1_73C.root',
    '/store/cmst3/group/exovv/santanas/EDBR_PATtuple_edbr_zz_20130605_Summer12MC_BulkGravitonsWW_20130916_175629/santanas/BulkG_WW_inclusive_c0p2_M2400_GENSIM/EDBR_PATtuple_edbr_zz_20130605/1b325ddfb984c14533be7920e22baeef/BulkG_WW_inclusive_c0p2_M2400_GENSIM__shuai-BulkG_WW_inclusive_c0p2_M2400_AODSIM-2c74483358b1f8805e5601fc325d256c__USER_21_1_cdE.root',
    '/store/cmst3/group/exovv/santanas/EDBR_PATtuple_edbr_zz_20130605_Summer12MC_BulkGravitonsWW_20130916_175629/santanas/BulkG_WW_inclusive_c0p2_M2400_GENSIM/EDBR_PATtuple_edbr_zz_20130605/1b325ddfb984c14533be7920e22baeef/BulkG_WW_inclusive_c0p2_M2400_GENSIM__shuai-BulkG_WW_inclusive_c0p2_M2400_AODSIM-2c74483358b1f8805e5601fc325d256c__USER_2_1_jXy.root',
    '/store/cmst3/group/exovv/santanas/EDBR_PATtuple_edbr_zz_20130605_Summer12MC_BulkGravitonsWW_20130916_175629/santanas/BulkG_WW_inclusive_c0p2_M2400_GENSIM/EDBR_PATtuple_edbr_zz_20130605/1b325ddfb984c14533be7920e22baeef/BulkG_WW_inclusive_c0p2_M2400_GENSIM__shuai-BulkG_WW_inclusive_c0p2_M2400_AODSIM-2c74483358b1f8805e5601fc325d256c__USER_3_1_74V.root',
    '/store/cmst3/group/exovv/santanas/EDBR_PATtuple_edbr_zz_20130605_Summer12MC_BulkGravitonsWW_20130916_175629/santanas/BulkG_WW_inclusive_c0p2_M2400_GENSIM/EDBR_PATtuple_edbr_zz_20130605/1b325ddfb984c14533be7920e22baeef/BulkG_WW_inclusive_c0p2_M2400_GENSIM__shuai-BulkG_WW_inclusive_c0p2_M2400_AODSIM-2c74483358b1f8805e5601fc325d256c__USER_4_1_Na7.root',
    '/store/cmst3/group/exovv/santanas/EDBR_PATtuple_edbr_zz_20130605_Summer12MC_BulkGravitonsWW_20130916_175629/santanas/BulkG_WW_inclusive_c0p2_M2400_GENSIM/EDBR_PATtuple_edbr_zz_20130605/1b325ddfb984c14533be7920e22baeef/BulkG_WW_inclusive_c0p2_M2400_GENSIM__shuai-BulkG_WW_inclusive_c0p2_M2400_AODSIM-2c74483358b1f8805e5601fc325d256c__USER_5_1_44X.root',
    '/store/cmst3/group/exovv/santanas/EDBR_PATtuple_edbr_zz_20130605_Summer12MC_BulkGravitonsWW_20130916_175629/santanas/BulkG_WW_inclusive_c0p2_M2400_GENSIM/EDBR_PATtuple_edbr_zz_20130605/1b325ddfb984c14533be7920e22baeef/BulkG_WW_inclusive_c0p2_M2400_GENSIM__shuai-BulkG_WW_inclusive_c0p2_M2400_AODSIM-2c74483358b1f8805e5601fc325d256c__USER_6_1_bu4.root',
    '/store/cmst3/group/exovv/santanas/EDBR_PATtuple_edbr_zz_20130605_Summer12MC_BulkGravitonsWW_20130916_175629/santanas/BulkG_WW_inclusive_c0p2_M2400_GENSIM/EDBR_PATtuple_edbr_zz_20130605/1b325ddfb984c14533be7920e22baeef/BulkG_WW_inclusive_c0p2_M2400_GENSIM__shuai-BulkG_WW_inclusive_c0p2_M2400_AODSIM-2c74483358b1f8805e5601fc325d256c__USER_7_1_3v6.root',
    '/store/cmst3/group/exovv/santanas/EDBR_PATtuple_edbr_zz_20130605_Summer12MC_BulkGravitonsWW_20130916_175629/santanas/BulkG_WW_inclusive_c0p2_M2400_GENSIM/EDBR_PATtuple_edbr_zz_20130605/1b325ddfb984c14533be7920e22baeef/BulkG_WW_inclusive_c0p2_M2400_GENSIM__shuai-BulkG_WW_inclusive_c0p2_M2400_AODSIM-2c74483358b1f8805e5601fc325d256c__USER_8_1_7ow.root',
    '/store/cmst3/group/exovv/santanas/EDBR_PATtuple_edbr_zz_20130605_Summer12MC_BulkGravitonsWW_20130916_175629/santanas/BulkG_WW_inclusive_c0p2_M2400_GENSIM/EDBR_PATtuple_edbr_zz_20130605/1b325ddfb984c14533be7920e22baeef/BulkG_WW_inclusive_c0p2_M2400_GENSIM__shuai-BulkG_WW_inclusive_c0p2_M2400_AODSIM-2c74483358b1f8805e5601fc325d256c__USER_9_1_Kqx.root',
    ])