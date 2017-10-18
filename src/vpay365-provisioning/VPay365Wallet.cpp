//
// Created by richie on 05/10/17.
//

#include "VPay365Wallet.h"
#include <secp256k1/include/secp256k1.h>
#include <ripple/protocol/Seed.h>
#include <ripple/protocol/tokens.h>
#include <ripple/protocol/SecretKey.h>
#include <ripple/crypto/KeyType.h>
#include <ripple/basics/strHex.h>
#include <ripple/basics/Slice.h>
#include <beast/core/to_string.hpp>
#include <beast/core/detail/base64.hpp>

namespace ripple {


    VPay365Wallet::VPay365Wallet() {
    }


    VPay365Wallet::VPay365Wallet(std::string secretin) {
        boost::optional<Seed> seed = parseGenericSeed(secretin);
        secret = secretin;
        keypair = generateKeyPair(KeyType::secp256k1, *seed);
        publickey = strHex(keypair.first.data(),(int)keypair.first.size());
        address = toBase58(calcAccountID(keypair.first));
    }

    std::string VPay365Wallet::getSecretfromString(std::string randomstring){
        boost::optional<Seed> seed = generateSeed(randomstring);
        return ripple::toBase58(*seed);
    }


    // returns base58 address
    std::string VPay365Wallet::getAddressfromPubKey (PublicKey pubkey) {
        return toBase58(calcAccountID(pubkey));
    }

    bool VPay365Wallet::verifyAddress (std::string address) {
        boost::optional<AccountID> localaddress = parseBase58<AccountID>(address);
        if (localaddress == boost::none) return false;
        return true;
    }

    // returns base64(publickey
    std::string VPay365Wallet::getPublicKey() {
        return beast::detail::base64_encode(keypair.first.data(),keypair.first.size());
    }

    // returns base64(signature)
    std::string VPay365Wallet::signMessage(std::string message) {
        Buffer sig = sign(keypair.first,keypair.second,makeSlice(message));
        std::string sigstr = beast::detail::base64_encode(sig.data(),sig.size());
        return sigstr;
    }

    // sig is base64(signature)
    bool VPay365Wallet::verifyMessage(std::string message, std::string sig) {
        auto sigdata = beast::detail::base64_decode(sig);
        return verify(keypair.first,makeSlice(message), makeSlice(sigdata));
    }

    // Publickey is base64(hex(pubkey))
    // sig is base64(signature)

//    bool verifyMessage(std::string message, std::string sig, std::string publicKey){
//        auto pubkey =beast::detail::base64_decode(publicKey);
//        auto sigdata = beast::detail::base64_decode(sig);
//        return verify(pubkey,makeSlice(message), makeSlice(sigdata));
//    }

    // Example from java
    // {
    //  "address":"rHzi7AJ6JS6x9GxAQENug4aXfofYzB1KGt",
    //  "telnumber":"+447709618382",
    //  "timestamp":1507283545878,
    //  "pubkey":"A/O0MEmQ86zBnKFHbXdI0GZyIeJ4QJSN9rfuJn3/Clpq",
    //  "signature":"MEUCIQD0aHHloSuOAN672v00FLLKidfXDLpeR7AgyuuJI25TyAIgV1OI/WeqkPNjcIdVpWEcVH6E15GNcAOqggk1xf9sRuE="
    // }

    std::string VPay365Wallet::getProvisioningRequest (std::string telnumber) {
        unsigned long timestamp = time(NULL)*1000; // so what!
        std::string messagetosign = address+telnumber+std::to_string(timestamp);
        std::string signature = signMessage(messagetosign);
        return "{\"address\":\""+address+"\",\"telnumber\":\""+telnumber+"\",\"timestamp\":"+std::to_string(timestamp)+",\"pubkey\":\""+getPublicKey()+"\",\"signature\":\""+signature+"\"}";
    }

    std::string VPay365Wallet::getProvisioningReply (std::string smscode) {
        std::string messagetosign = address+smscode;
        std::string signature = signMessage(messagetosign);
        return "{\"address\":\""+address+"\",\"signature\":\""+signature+"\"}";
    }

    std::string VPay365Wallet::getWithdrawalRequest (std::string currency, std::string bankname, std::string accountnumber,
                                                     std::string accountholder,std::string txhash, int amount) {
        std::string messagetosign = address+std::to_string(amount)+currency+bankname+accountnumber+accountholder+txhash;
        std::string signature = signMessage(messagetosign);
        return "{\"address\":\""+address+"\",\"amount\":"+std::to_string(amount)+
                ",\"currency\":"+currency+",\"bankname\":\""+bankname+"\",\"accountnumber\":\""+accountnumber+
                "\",\"accountholder\":\""+accountholder+"\",\"txhash\":\""+txhash+"\",\"signature\":\""+signature+"\"}";


    }

    std::string VPay365Wallet::getTopupRequest(std::string currency, int amount) {
        std::string messagetosign = address+std::to_string(amount)+currency;
        std::string signature = signMessage(messagetosign);
        return "{\"address\":\""+address+"\",\"amount\":"+std::to_string(amount)+
                ",\"currency\":"+currency+",\"signature\":\""+signature+"\"}";
    }

    std::string VPay365Wallet::getPushTokenRequest(std::string pushtoken) {
        unsigned long timestamp = time(NULL)*1000; // so what!
        std::string messagetosign = address+pushtoken+std::to_string(timestamp);
        std::string signature = signMessage(messagetosign);
        return "{\"address\":\""+address+"\",\"token\":\""+pushtoken+"\",\"timestamp\":"+std::to_string(timestamp)+",\"signature\":\""+signature+"\"}";
    }

    std::string VPay365Wallet::getBitcoinGenerationRequest() {
        unsigned long timestamp = time(NULL)*1000; // so what!
        std::string messagetosign = address+std::to_string(timestamp);
        std::string signature = signMessage(messagetosign);
        return "{\"address\":\""+address+"\",\"timestamp\":"+std::to_string(timestamp)+",\"signature\":\""+signature+"\"}";
    }

}
