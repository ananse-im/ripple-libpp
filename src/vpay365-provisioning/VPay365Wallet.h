//
// Created by richie on 05/10/17.
//

#ifndef RIPPLE_LIBPP_VPAY365WALLET_H
#define RIPPLE_LIBPP_VPAY365WALLET_H

#include <PublicKey.h>
#include <SecretKey.h>
#include <tokens.h>

#include <sys/time.h>
#include <string>

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
