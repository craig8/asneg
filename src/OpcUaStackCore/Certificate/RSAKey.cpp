/*
   Copyright 2018 Kai Huebl (kai@huebl-sgh.de)

   Lizenziert gemäß Apache Licence Version 2.0 (die „Lizenz“); Nutzung dieser
   Datei nur in Übereinstimmung mit der Lizenz erlaubt.
   Eine Kopie der Lizenz erhalten Sie auf http://www.apache.org/licenses/LICENSE-2.0.

   Sofern nicht gemäß geltendem Recht vorgeschrieben oder schriftlich vereinbart,
   erfolgt die Bereitstellung der im Rahmen der Lizenz verbreiteten Software OHNE
   GEWÄHR ODER VORBEHALTE – ganz gleich, ob ausdrücklich oder stillschweigend.

   Informationen über die jeweiligen Bedingungen für Genehmigungen und Einschränkungen
   im Rahmen der Lizenz finden Sie in der Lizenz.

   Autor: Kai Huebl (kai@huebl-sgh.de)
 */

#include <string.h>
#include <openssl/pem.h>

#include "OpcUaStackCore/Certificate/OpenSSLCompat.h"
#include "OpcUaStackCore/Certificate/RSAKey.h"

namespace OpcUaStackCore
{

	RSAKey::RSAKey(void)
	: OpenSSLError()
	, pKey_(nullptr)
	{
		pKey_ = EVP_PKEY_new();
	}

	RSAKey::RSAKey(EVP_PKEY *pKey)
	: OpenSSLError()
	, pKey_(nullptr)
	{
	    if (pKey_) {
	        EVP_PKEY_up_ref(pKey);
	        pKey_ = pKey;
	    }
	}

	RSAKey::RSAKey(uint32_t bits)
	: OpenSSLError()
	, pKey_(nullptr)
	{
	    pKey_ = EVP_PKEY_new();

	    RSA *rsaKeyPair = RSA_generate_key(bits, 0x10001, 0, 0);
	    if (!rsaKeyPair) {
	    	addOpenSSLError();
	    }
	    else {
	        int iRet = EVP_PKEY_assign_RSA(pKey_, rsaKeyPair );
	        if (!iRet) {
	        	addOpenSSLError();
	        }
	    }
	}

	RSAKey::RSAKey(const RSAKey &copy)
	: OpenSSLError()
	, pKey_(nullptr)
	{
	    EVP_PKEY_up_ref(copy.pKey_);
        pKey_ = copy.pKey_;

	}

	RSAKey::~RSAKey(void)
	{
		EVP_PKEY_free(pKey_);
	}

	RSAKey&
	RSAKey::operator=(const RSAKey &copy)
	{
	    if (pKey_) {
	    	EVP_PKEY_free (pKey_);
	    }

	    EVP_PKEY_up_ref(copy.pKey_);
	    pKey_ = copy.pKey_;
	    return *this;
	}

    PrivateKey
	RSAKey::privateKey(void) const
    {
        PrivateKey privateKey(pKey_);
        return privateKey;
    }

    PublicKey
	RSAKey::publicKey(void) const
    {
    	PublicKey publicKey;

    	X509_PUBKEY* pubKey = X509_PUBKEY_new();
    	int32_t result = X509_PUBKEY_set(&pubKey, pKey_);
    	if (!result) {
    		const_cast<RSAKey*>(this)->addOpenSSLError();
    		X509_PUBKEY_free (pubKey);
    		return publicKey;
    	}

        EVP_PKEY *pKey = nullptr;
        pKey = X509_PUBKEY_get(pubKey);
        if (!pKey) {
        	const_cast<RSAKey*>(this)->addOpenSSLError();
        	X509_PUBKEY_free (pubKey);
        	return publicKey;
        }

        publicKey = PublicKey(pKey);
        EVP_PKEY_free(pKey);

        X509_PUBKEY_free(pubKey);
        return publicKey;
    }

    bool
	RSAKey::toDER(char* buf, uint32_t& bufLen) const
    {
        int32_t length = i2d_PrivateKey(pKey_, 0);
        if (length < 0) {
        	const_cast<RSAKey*>(this)->addOpenSSLError();
        	return false;
        }

        if (bufLen < length) {
        	const_cast<RSAKey*>(this)->addError("buffer length is too short");
        	return false;
        }

        bufLen = length;
        i2d_PrivateKey(pKey_, (unsigned char**)&buf);
    	return true;
    }

    bool
	RSAKey::toPEM(char* buf, uint32_t& bufLen, const char* password) const
    {
    	BIO *bio = BIO_new(BIO_s_mem());

    	int result;
        if (password) {
            result = PEM_write_bio_PrivateKey(bio, pKey_, EVP_aes_256_cbc(), 0, 0, 0, (void*)password);
        }
        else {
            result = PEM_write_bio_PrivateKey(bio, pKey_, 0, 0, 0, 0, 0);
        }

        if (result == 0) {
        	const_cast<RSAKey*>(this)->addOpenSSLError();
        	BIO_free(bio);
        	return false;
        }

        char* data = nullptr;
        uint32_t length = BIO_get_mem_data(bio, &data);

        if (length > bufLen) {
        	const_cast<RSAKey*>(this)->addError("buffer length is too short");
        	return false;
        }

        bufLen = length;
        memcpy(buf, data, bufLen);

        BIO_set_close(bio, BIO_CLOSE);
        return true;
    }

    bool
	RSAKey::fromPEM(char* buf, uint32_t bufLen, const char* password, PasswordCallback* passwordCallback, void *data)
    {
    	BIO* bio = BIO_new_mem_buf((void*)buf, bufLen);
    	if (!bio) {
    		addOpenSSLError();
    		return false;
    	}

    	RSA* rsa = nullptr;

	    if (passwordCallback) {
	        rsa = PEM_read_bio_RSAPrivateKey(bio, 0, passwordCallback, data);
	        if (!rsa) {
	        	addOpenSSLError();
	        	BIO_free(bio);
	        	return false;
	        }
	    }
	    else {
	        rsa = PEM_read_bio_RSAPrivateKey(bio, 0, passwordCallback, (void*)password);
	        if (!rsa) {
	        	addOpenSSLError();
	        	BIO_free(bio);
	            return false;
	        }
	    }

	    int result = EVP_PKEY_assign_RSA(pKey_, rsa);
	    if (!result) {
		    addOpenSSLError();
		    BIO_free(bio);
		    return false;
	    }

        BIO_free(bio);
    	return true;
    }

    bool
	RSAKey::isValid(void)
    {
    	return ( pKey_ != 0 && EVP_PKEY_get0_RSA(pKey_) != 0 && EVP_PKEY_missing_parameters(pKey_) == 0);
    }

    bool
	RSAKey::checkKeyPair(void)
    {
    	return checkKeyPair(publicKey(), privateKey());
    }

    bool
	RSAKey::checkKeyPair(const PublicKey& publicKey, const PrivateKey& privateKey)
    {
        EVP_PKEY* pPublicKey = *const_cast<PublicKey*>(&publicKey);
        EVP_PKEY* pPrivateKey = *const_cast<PrivateKey*>(&privateKey);
        if (pPublicKey && pPrivateKey)
        {
            int result = EVP_PKEY_cmp(pPublicKey, pPrivateKey);
            EVP_PKEY_free(pPublicKey);
            return (result == 1);
        }
        return false;
    }

}
