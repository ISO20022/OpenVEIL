//	Copyright (c) 2018, TecSec, Inc.
//
//	Redistribution and use in source and binary forms, with or without
//	modification, are permitted provided that the following conditions are met:
//	
//		* Redistributions of source code must retain the above copyright
//		  notice, this list of conditions and the following disclaimer.
//		* Redistributions in binary form must reproduce the above copyright
//		  notice, this list of conditions and the following disclaimer in the
//		  documentation and/or other materials provided with the distribution.
//		* Neither the name of TecSec nor the names of the contributors may be
//		  used to endorse or promote products derived from this software 
//		  without specific prior written permission.
//		 
//	ALTERNATIVELY, provided that this notice is retained in full, this product
//	may be distributed under the terms of the GNU General Public License (GPL),
//	in which case the provisions of the GPL apply INSTEAD OF those given above.
//		 
//	THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
//	ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
//	WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
//	DISCLAIMED.  IN NO EVENT SHALL TECSEC BE LIABLE FOR ANY 
//	DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
//	(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
//	LOSS OF USE, DATA OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
//	ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
//	(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
//	SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
// Written by Roger Butler


#include "stdafx.h"

using namespace tscrypto;

class KASImpl : public KAS, public TSName, public tscrypto::ICryptoObject, public tscrypto::IInitializableObject, public AlgorithmInfo
{
public:
    KASImpl() : desc(nullptr)
    {
        desc = TSLookup(TSIKas, "KAS");
        if (desc)
            workspace = desc->def;
        kdfName = "KDF";
        SetName("KAS");
    }
    virtual ~KASImpl(void)
    {
        clear();
        if (desc != nullptr && !workspace.empty())
        {
            desc->finish(workspace);
            workspace.reset();
        }
    }

    // AlgorithmInfo
    virtual tsCryptoString AlgorithmName() const override
    {
        return GetName();
    }
    virtual tsCryptoString AlgorithmOID() const override
    {
        return LookUpAlgOID(GetName());
    }
    virtual TS_ALG_ID AlgorithmID() const override
    {
        return LookUpAlgID(GetName());
    }


    // KAS
    virtual void clear() override
    {
        finish();
    }
    virtual tsCryptoString get_KdfName() const override
    {
        return kdfName + tsCryptoString("-") + kdfMacName;
    }
    virtual bool set_KdfName(const tsCryptoStringBase& name) override
    {
        tsCryptoString Name(name);
        if (!gFipsState.operational() || desc == nullptr || workspace.empty())
            return false;

        if (tsStrniCmp(Name.c_str(), "KDF-", 4) == 0)
            Name.erase(0, 4);

        kdfMacName = Name;
        return true;
    }
    virtual tsCryptoData get_IDu() const override
    {
        if (desc == nullptr || workspace.empty())
            return tsCryptoData();

        uint32_t len;
        tsCryptoData tmp;

        if (!desc->getIDu(workspace, NULL, &len))
            return tsCryptoData();
        tmp.resize(len);
        if (!desc->getIDu(workspace, tmp.rawData(), &len))
            return tsCryptoData();
        tmp.resize(len);
        return tmp;
    }
    virtual bool set_IDu(const tsCryptoData &data) override
    {
        if (!gFipsState.operational() || desc == nullptr || workspace.empty())
            return false;
        return desc->setIDu(workspace, data.c_str(), (uint32_t)data.size());
    }
    virtual tsCryptoData get_IDv() const override
    {
        if (desc == nullptr || workspace.empty())
            return tsCryptoData();

        uint32_t len;
        tsCryptoData tmp;

        if (!desc->getIDv(workspace, NULL, &len))
            return tsCryptoData();
        tmp.resize(len);
        if (!desc->getIDv(workspace, tmp.rawData(), &len))
            return tsCryptoData();
        tmp.resize(len);
        return tmp;
    }
    virtual bool set_IDv(const tsCryptoData &data) override
    {
        if (!gFipsState.operational() || desc == nullptr || workspace.empty())
            return false;
        return desc->setIDv(workspace, data.c_str(), (uint32_t)data.size());
    }
    virtual size_t get_KcKeyLengthInBits() const override
    {
        if (desc == nullptr || workspace.empty())
            return 0;

        return desc->getKcKeyLengthInBits(workspace);
    }
    virtual bool set_KcKeyLengthInBits(size_t setTo) override
    {
        if (!gFipsState.operational() || desc == nullptr || workspace.empty())
            return false;
        return desc->setKcKeyLengthInBits(workspace, (uint32_t)setTo);
    }
    virtual tsCryptoString get_KcAlgorithmName() const override
    {
        return macName;
    }
    virtual bool set_KcAlgorithmName(const tsCryptoStringBase& name) override
    {
        if (!gFipsState.operational() || desc == nullptr || workspace.empty())
            return false;
        if (!desc->configure(workspace, kdfName.c_str(), kdfMacName.c_str(), macName.c_str()))
            return false;
        return true;
    }
    virtual tsCryptoData get_KcSuffixU() const override
    {
        if (desc == nullptr || workspace.empty())
            return tsCryptoData();

        uint32_t len;
        tsCryptoData tmp;

        if (!desc->getKcSuffixU(workspace, NULL, &len))
            return tsCryptoData();
        tmp.resize(len);
        if (!desc->getKcSuffixU(workspace, tmp.rawData(), &len))
            return tsCryptoData();
        tmp.resize(len);
        return tmp;
    }
    virtual bool set_KcSuffixU(const tsCryptoData &data) override
    {
        if (!gFipsState.operational() || desc == nullptr || workspace.empty())
            return false;
        return desc->setKcSuffixU(workspace, data.c_str(), (uint32_t)data.size());
    }
    virtual tsCryptoData get_KcSuffixV() const override
    {
        if (desc == nullptr || workspace.empty())
            return tsCryptoData();

        uint32_t len;
        tsCryptoData tmp;

        if (!desc->getKcSuffixV(workspace, NULL, &len))
            return tsCryptoData();
        tmp.resize(len);
        if (!desc->getKcSuffixV(workspace, tmp.rawData(), &len))
            return tsCryptoData();
        tmp.resize(len);
        return tmp;
    }
    virtual bool set_KcSuffixV(const tsCryptoData &data) override
    {
        if (!gFipsState.operational() || desc == nullptr || workspace.empty())
            return false;
        return desc->setKcSuffixV(workspace, data.c_str(), (uint32_t)data.size());
    }
    virtual size_t get_KcLengthInBits() const override
    {
        if (desc == nullptr || workspace.empty())
            return 0;

        return desc->getKcLengthInBits(workspace);
    }
    virtual bool set_KcLengthInBits(size_t setTo) override
    {
        if (!gFipsState.operational() || desc == nullptr || workspace.empty())
            return false;
        return desc->setKcLengthInBits(workspace, (uint32_t)setTo);
    }
    virtual tsCryptoData get_OtherInfoPrefix() const override
    {
        if (desc == nullptr || workspace.empty())
            return tsCryptoData();

        uint32_t len;
        tsCryptoData tmp;

        if (!desc->getOtherInfoPrefix(workspace, NULL, &len))
            return tsCryptoData();
        tmp.resize(len);
        if (!desc->getOtherInfoPrefix(workspace, tmp.rawData(), &len))
            return tsCryptoData();
        tmp.resize(len);
        return tmp;
    }
    virtual bool set_OtherInfoPrefix(const tsCryptoData &data) override
    {
        if (!gFipsState.operational() || desc == nullptr || workspace.empty())
            return false;
        return desc->setOtherInfoPrefix(workspace, data.c_str(), (uint32_t)data.size());
    }
    virtual tsCryptoData get_OtherInfoSuffix() const override
    {
        if (desc == nullptr || workspace.empty())
            return tsCryptoData();

        uint32_t len;
        tsCryptoData tmp;

        if (!desc->getOtherInfoSuffix(workspace, NULL, &len))
            return tsCryptoData();
        tmp.resize(len);
        if (!desc->getOtherInfoSuffix(workspace, tmp.rawData(), &len))
            return tsCryptoData();
        tmp.resize(len);
        return tmp;
    }
    virtual bool set_OtherInfoSuffix(const tsCryptoData &data) override
    {
        if (!gFipsState.operational() || desc == nullptr || workspace.empty())
            return false;
        return desc->setOtherInfoSuffix(workspace, data.c_str(), (uint32_t)data.size());
    }
    virtual tsCryptoData get_CCMNonce() const override
    {
        if (desc == nullptr || workspace.empty())
            return tsCryptoData();

        uint32_t len;
        tsCryptoData tmp;

        if (!desc->getCCMNonce(workspace, NULL, &len))
            return tsCryptoData();
        tmp.resize(len);
        if (!desc->getCCMNonce(workspace, tmp.rawData(), &len))
            return tsCryptoData();
        tmp.resize(len);
        return tmp;
    }
    virtual bool set_CCMNonce(const tsCryptoData &data) override
    {
        if (!gFipsState.operational() || desc == nullptr || workspace.empty())
            return false;
        return desc->setCCMNonce(workspace, data.c_str(), (uint32_t)data.size());
    }
    virtual bool computeCCMNonce(size_t nonceBitLength, tsCryptoData &nonce) override
    {
        if (!gFipsState.operational() || desc == nullptr || workspace.empty())
            return false;
        tsCryptoData tmp;

        tmp.resize((nonceBitLength + 7) / 8);
        if (!tsInternalGenerateRandomBits(tmp.rawData(), (uint32_t)nonceBitLength, true, (uint8_t*)"KAS Nonce", 9))
            return false;

        if (!desc->setCCMNonce(workspace, tmp.c_str(), (uint32_t)tmp.size()))
            return false;
        return true;
    }
    virtual size_t get_CCMTagLengthInBytes() const override
    {
        if (!gFipsState.operational() || desc == nullptr || workspace.empty())
            return false;
        return desc->getCCMTagLengthInBytes(workspace);
    }
    virtual bool set_CCMTagLengthInBytes(size_t setTo) override
    {
        if (!gFipsState.operational() || desc == nullptr || workspace.empty())
            return false;
        if (setTo < 4 || setTo > 16 || (setTo & 1) != 0)
            return false;
        return desc->setCCMTagLengthInBytes(workspace, (uint32_t)setTo);
    }
    virtual tsCryptoData get_NonceU() const override
    {
        if (desc == nullptr || workspace.empty())
            return tsCryptoData();

        uint32_t len;
        tsCryptoData tmp;

        if (!desc->getNonceU(workspace, NULL, &len))
            return tsCryptoData();
        tmp.resize(len);
        if (!desc->getNonceU(workspace, tmp.rawData(), &len))
            return tsCryptoData();
        tmp.resize(len);
        return tmp;
    }
    virtual bool set_NonceU(const tsCryptoData &data) override
    {
        if (!gFipsState.operational() || desc == nullptr || workspace.empty())
            return false;
        return desc->setNonceU(workspace, data.c_str(), (uint32_t)data.size());
    }
    virtual bool computeNonceU(size_t nonceBitLength, tsCryptoData &nonce) override
    {
        if (!gFipsState.operational() || desc == nullptr || workspace.empty())
            return false;
        tsCryptoData tmp;

        tmp.resize((nonceBitLength + 7) / 8);
        if (!tsInternalGenerateRandomBits(tmp.rawData(), (uint32_t)nonceBitLength, true, (uint8_t*)"KAS Nonce", 9))
            return false;

        if (!desc->setNonceU(workspace, tmp.c_str(), (uint32_t)tmp.size()))
            return false;
        return true;
    }
    virtual tsCryptoData get_NonceV() const override
    {
        if (desc == nullptr || workspace.empty())
            return tsCryptoData();

        uint32_t len;
        tsCryptoData tmp;

        if (!desc->getNonceV(workspace, NULL, &len))
            return tsCryptoData();
        tmp.resize(len);
        if (!desc->getNonceV(workspace, tmp.rawData(), &len))
            return tsCryptoData();
        tmp.resize(len);
        return tmp;
    }
    virtual bool set_NonceV(const tsCryptoData &data) override
    {
        if (!gFipsState.operational() || desc == nullptr || workspace.empty())
            return false;
        return desc->setNonceV(workspace, data.c_str(), (uint32_t)data.size());
    }
    virtual bool computeNonceV(size_t nonceBitLength, tsCryptoData &nonce) override
    {
        if (!gFipsState.operational() || desc == nullptr || workspace.empty())
            return false;
        tsCryptoData tmp;

        tmp.resize((nonceBitLength + 7) / 8);
        if (!tsInternalGenerateRandomBits(tmp.rawData(), (uint32_t)nonceBitLength, true, (uint8_t*)"KAS Nonce", 9))
            return false;

        if (!desc->setNonceV(workspace, tmp.c_str(), (uint32_t)tmp.size()))
            return false;
        return true;
    }
    virtual bool initialize(bool isPartyU, size_t kmLengthInBits, /*IN*/ std::shared_ptr<AsymmetricKey> staticKey, /*INOUT*/ std::shared_ptr<AsymmetricKey> ephemeralKey) override
    {
        if (!gFipsState.operational() || desc == nullptr || workspace.empty())
            return false;

        std::shared_ptr<EccKey> eccStatic = std::dynamic_pointer_cast<EccKey>(staticKey);
        std::shared_ptr<EccKey> eccEphemeral = std::dynamic_pointer_cast<EccKey>(ephemeralKey);
        std::shared_ptr<DhKey> dhStatic = std::dynamic_pointer_cast<DhKey>(staticKey);
        std::shared_ptr<DhKey> dhEphemeral = std::dynamic_pointer_cast<DhKey>(ephemeralKey);
        std::shared_ptr<TSALG_Access> accStatic = std::dynamic_pointer_cast<TSALG_Access>(staticKey);
        std::shared_ptr<TSALG_Access> accEphemeral = std::dynamic_pointer_cast<TSALG_Access>(ephemeralKey);
        TSWORKSPACE staticKeyPair;
        TSWORKSPACE ephemeralKeyPair;

        if (!!accStatic)
        {
            staticKeyPair = accStatic->getKeyPair();
        }
        if (!!accEphemeral)
        {
            ephemeralKeyPair = accEphemeral->getKeyPair();
        }
        if (!!eccStatic || !!eccEphemeral || !!dhStatic || !!dhEphemeral)
        {
            return desc->init(workspace, isPartyU, (uint32_t)kmLengthInBits, staticKeyPair, ephemeralKeyPair);
        }
        else
            return false;
    }
    virtual bool finish() override
    {
        if (!gFipsState.operational() || desc == nullptr || workspace.empty())
            return false;
        return desc->finish(workspace);
    }
    virtual bool setKCDirection(bool bilateral, bool unilateralFromMe) override
    {
        if (!gFipsState.operational() || desc == nullptr || workspace.empty())
            return false;

        return desc->setKCDirection(workspace, bilateral, unilateralFromMe);
    }
    virtual bool computeZ(std::shared_ptr<AsymmetricKey> otherStaticKey, std::shared_ptr<AsymmetricKey> otherEphemeral) override
    {
        if (!gFipsState.operational() || desc == nullptr || workspace.empty())
            return false;

        std::shared_ptr<TSALG_Access> accStatic = std::dynamic_pointer_cast<TSALG_Access>(otherStaticKey);
        std::shared_ptr<TSALG_Access> accEphemeral = std::dynamic_pointer_cast<TSALG_Access>(otherEphemeral);
        TSWORKSPACE staticKeyPair;
        TSWORKSPACE ephemeralKeyPair;

        if (!!accStatic)
        {
            staticKeyPair = accStatic->getKeyPair();
        }
        if (!!accEphemeral)
        {
            ephemeralKeyPair = accEphemeral->getKeyPair();
        }

        return desc->computeZ(workspace, staticKeyPair, ephemeralKeyPair);
    }
    virtual bool computeMac(tsCryptoData &mac) override
    {
        uint32_t len;

        if (!gFipsState.operational() || desc == nullptr || workspace.empty())
            return false;

        if (!desc->computeMac(workspace, nullptr, &len))
            return false;
        mac.resize(len);
        if (!desc->computeMac(workspace, mac.rawData(), &len))
        {
            mac.resize(len);
            return false;
        }
        mac.resize(len);
        return true;
    }
    virtual bool verifyMac(const tsCryptoData &mac) override
    {
        if (!gFipsState.operational() || desc == nullptr || workspace.empty())
            return false;

        return desc->verifyMac(workspace, mac.c_str(), (uint32_t)mac.size());
    }
    virtual bool retrieveKeyingMaterial(tsCryptoData &keyingMaterial) override
    {
        if (!gFipsState.operational() || desc == nullptr || workspace.empty())
            return false;
        uint32_t len;

        keyingMaterial.clear();
        if (!desc->retrieveKeyingMaterial(workspace, NULL, &len))
            return false;
        keyingMaterial.resize(len);
        if (!desc->retrieveKeyingMaterial(workspace, keyingMaterial.rawData(), &len))
            return false;
        keyingMaterial.resize(len);
        return true;
    }
    virtual bool get_Z(tsCryptoData &data) override
    {
        if (!gFipsState.operational() || desc == nullptr || workspace.empty())
            return false;

        uint32_t len;

        data.clear();
        if (!desc->getZ(workspace, NULL, &len))
            return false;
        data.resize(len);
        if (!desc->getZ(workspace, data.rawData(), &len))
            return false;
        data.resize(len);
        return true;
    }
    virtual bool get_MacData(tsCryptoData &data) override
    {
        if (!gFipsState.operational() || desc == nullptr || workspace.empty())
            return false;

        uint32_t len;

        data.clear();
        if (!desc->getMacData(workspace, NULL, &len))
            return false;
        data.resize(len);
        if (!desc->getMacData(workspace, data.rawData(), &len))
            return false;
        data.resize(len);
        return true;
    }
    virtual bool get_OtherMacData(tsCryptoData &data) override
    {
        if (!gFipsState.operational() || desc == nullptr || workspace.empty())
            return false;

        uint32_t len;

        data.clear();
        if (!desc->getOtherMacData(workspace, NULL, &len))
            return false;
        data.resize(len);
        if (!desc->getOtherMacData(workspace, data.rawData(), &len))
            return false;
        data.resize(len);
        return true;
    }
    virtual bool get_OtherInfo(tsCryptoData &data) override
    {
        if (!gFipsState.operational() || desc == nullptr || workspace.empty())
            return false;

        uint32_t len;

        data.clear();
        if (!desc->getOtherInfo(workspace, NULL, &len))
            return false;
        data.resize(len);
        if (!desc->getOtherInfo(workspace, data.rawData(), &len))
            return false;
        data.resize(len);
        return true;
    }
    virtual bool computeZForOtherInfo(const tsCryptoData &otherInfo, std::shared_ptr<AsymmetricKey> otherStaticKey, std::shared_ptr<AsymmetricKey> otherEphemeral) override
    {
        if (!gFipsState.operational() || desc == nullptr || workspace.empty())
            return false;

        std::shared_ptr<TSALG_Access> accStatic = std::dynamic_pointer_cast<TSALG_Access>(otherStaticKey);
        std::shared_ptr<TSALG_Access> accEphemeral = std::dynamic_pointer_cast<TSALG_Access>(otherEphemeral);
        TSWORKSPACE staticKeyPair = nullptr;
        TSWORKSPACE ephemeralKeyPair = nullptr;

        if (!!accStatic)
        {
            staticKeyPair = accStatic->getKeyPair();
        }
        if (!!accEphemeral)
        {
            ephemeralKeyPair = accEphemeral->getKeyPair();
        }

        return desc->computeZForOtherInfo(workspace, otherInfo.c_str(), (uint32_t)otherInfo.size(), staticKeyPair, ephemeralKeyPair);
    }
    virtual bool get_DKM(tsCryptoData &data) override
    {
        if (!gFipsState.operational() || desc == nullptr || workspace.empty())
            return false;

        uint32_t len;

        data.clear();
        if (!desc->getDKM(workspace, NULL, &len))
            return false;
        data.resize(len);
        if (!desc->getDKM(workspace, data.rawData(), &len))
            return false;
        data.resize(len);
        return true;
    }
    virtual bool computeMacForData(const tsCryptoData &data, tsCryptoData &mac) override
    {
        if (!gFipsState.operational() || desc == nullptr || workspace.empty())
            return false;

        uint32_t len;

        mac.clear();
        if (!desc->computeMacForData(workspace, data.c_str(), (uint32_t)data.size(), NULL, &len))
            return false;
        mac.resize(len);
        if (!desc->computeMacForData(workspace, data.c_str(), (uint32_t)data.size(), mac.rawData(), &len))
            return false;
        mac.resize(len);
        return true;
    }

    // tscrypto::IInitializableObject
    virtual bool InitializeWithFullName(const tscrypto::tsCryptoStringBase& fullName) override
    {
        tsCryptoString algorithm(fullName);

        SetName(algorithm);
        return true;
    }

private:
    const TSIKas* desc;
    mutable SmartCryptoWorkspace workspace;
    tsCryptoString kdfName, kdfMacName, macName;


 //   tsCryptoString m_kdfName;
 //   tsCryptoData m_IDu;
 //   tsCryptoData m_IDv;
 //   size_t m_macKeyLengthInBits;
 //   size_t m_macLengthInBits;
 //   tsCryptoString m_MACAlgorithmName;
 //   tsCryptoData m_KcSuffixU;
 //   tsCryptoData m_KcSuffixV;
 //   tsCryptoData m_OtherInfoPrefix;
 //   tsCryptoData m_OtherInfoSuffix;
 //   tsCryptoData m_NonceU;
 //   tsCryptoData m_NonceV;

 //   bool m_isPartyU;
 //   size_t m_kmLengthInBits;
    //std::shared_ptr<AsymmetricKey> m_myStaticKey;
    //std::shared_ptr<AsymmetricKey> m_myEphemeralKey;
    //std::shared_ptr<AsymmetricKey> m_ephemU;
    //std::shared_ptr<AsymmetricKey> m_ephemV;
    //std::shared_ptr<KeyDerivationFunction> m_kdf;
    //std::shared_ptr<MessageAuthenticationCode> m_mac;
 //   tsCryptoData m_generatedKey;
 //   tsCryptoData m_macKey;
 //   bool m_bilateral;
 //   bool m_unilateralFromMe;
 //   tsCryptoData m_Z;
 //   size_t m_eCount;
 //   size_t m_sCount;
 //   tsCryptoData m_ccmNonce;
 //   size_t m_ccmTagLen;
};

tscrypto::ICryptoObject* CreateKAS()
{
    return dynamic_cast<tscrypto::ICryptoObject*>(new KASImpl);
}
