//
// Created by richie on 05/10/17.
//

#ifndef RIPPLE_LIBPP_VPAY365WALLET_H
#define RIPPLE_LIBPP_VPAY365WALLET_H
#include <secp256k1/include/secp256k1.h>
#include <ripple/protocol/Seed.h>
#include <ripple/protocol/tokens.h>
#include <ripple/protocol/SecretKey.h>
#include <ripple/crypto/KeyType.h>
#include <ripple/basics/strHex.h>
#include <ripple/basics/Slice.h>
#include <beast/core/to_string.hpp>
#include <beast/core/detail/base64.hpp>
#include <sys/time.h>

namespace ripple {
    class VPay365Wallet {
        std::string secret;
    public:
        std::string publickey;
    public:
        std::string address;
        std::pair<PublicKey, SecretKey> keypair;


    public:
        VPay365Wallet(std::string secret);
        std::string getAddressfromPubKey(PublicKey pubkey);
        std::string getPublicKey();
        bool verifyAddress(std::string address);
        std::string signMessage(std::string message);
        bool verifyMessage(std::string message, std::string sig);
        //bool verifyMessage(std::string message, std::string sig, std::string publicKey);
        std::string getProvisioningRequest (std::string telnumber);
        std::string getProvisioningReply (std::string smscode);
        std::string getWithdrawalRequest (std::string currency, std::string bankname, std::string accountnumber,
                                                         std::string accountholder,std::string txhash, int amount);
        std::string getTopupRequest(std::string currency, int amount);
        std::string getPushTokenRequest(std::string pushtoken);
        std::string getBitcoinGenerationRequest();
    };

}
#endif //RIPPLE_LIBPP_VPAY365WALLET_H
