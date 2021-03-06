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

#include <iostream>
#include "OpcUaStackCore/Certificate/PublicKey.h"

namespace OpcUaStackCore
{

	PublicKey::PublicKey(void)
	: OpenSSLError()
	, publicKey_(nullptr)
	{
		publicKey_ = X509_PUBKEY_new();
		if (publicKey_ == nullptr) {
			addError("create public key error in constructor");
		}
	}

	PublicKey::PublicKey(EVP_PKEY *pKey)
	: OpenSSLError()
	, publicKey_(nullptr)
	{
		publicKey_ = X509_PUBKEY_new();
		if (publicKey_ == nullptr) {
			addError("create public key error in key constructor");
		}

		int result = X509_PUBKEY_set(&publicKey_, pKey);
		if (!result) {
			addOpenSSLError();
		}
	}

	PublicKey::PublicKey(const PublicKey& copy)
	: OpenSSLError()
	, publicKey_(nullptr)
	{
		if (const_cast<PublicKey*>(&copy)->isError()) {
			addError("create public key error in copy constructor - source key error");
			return;
		}

		publicKey_ = X509_PUBKEY_new();
		if (publicKey_ == nullptr) {
			addError("create public key error in copy constructor - allocate memory error");
		}

		EVP_PKEY *pKey = X509_PUBKEY_get(copy.publicKey_);
		if (pKey==NULL) {
		    addOpenSSLError();
		    return;
		}

		int result = X509_PUBKEY_set(&publicKey_, pKey);
		if (!result) {
			addOpenSSLError();
		}

		EVP_PKEY_free(pKey);
	}

	PublicKey::~PublicKey(void)
	{
		X509_PUBKEY_free(publicKey_);
	}

	PublicKey&
	PublicKey::operator=(const PublicKey& copy)
	{
		if (const_cast<PublicKey*>(&copy)->isError()) {
			addError("public key error in assign operator - source key error");
			return *this;
		}

		EVP_PKEY *pKey = X509_PUBKEY_get(copy.publicKey_);
		if (pKey==NULL) {
		   addOpenSSLError();
		}
		else {
		   int result = X509_PUBKEY_set(&publicKey_, pKey);
		   if (!result) {
			   addOpenSSLError();
		   }

		   EVP_PKEY_free ( pKey );
	    }

		return *this;
	}

	PublicKey::operator EVP_PKEY*(void)
	{
	    EVP_PKEY* key = nullptr;
	    key = X509_PUBKEY_get(publicKey_);
	    if (!key) {
	    	const_cast<PublicKey*>(this)->addOpenSSLError();
	    }
	    return key;
	}

	uint32_t
	PublicKey::keySize(void) const
	{
	    int32_t result = -1;
	    EVP_PKEY* pKey = X509_PUBKEY_get(publicKey_);
	    if (!pKey) {
	    	const_cast<PublicKey*>(this)->addOpenSSLError();
	    }
	    else {
	        result = EVP_PKEY_bits(pKey);
	        EVP_PKEY_free( pKey );
	    }

	    return result;
	}

	KeyType
	PublicKey::keyType(void) const
	{
	    KeyType keyType = KeyType_Unknown;
	    EVP_PKEY* pKey = X509_PUBKEY_get(publicKey_);
	    if (!pKey) {
	    	const_cast<PublicKey*>(this)->addOpenSSLError();
	    }
	    else {
	        switch(EVP_PKEY_id(pKey))
	        {
	            case EVP_PKEY_RSA: keyType = KeyType_RSA; break;
	            case EVP_PKEY_DSA: keyType = KeyType_DSA; break;
	            default: break;
	        }
	        EVP_PKEY_free(pKey);
	    }
	    return keyType;
	}

	bool
	PublicKey::fromDER(const char* buf, uint32_t bufLen)
	{
	    publicKey_ = d2i_X509_PUBKEY(0, (const unsigned char**)&buf, bufLen);
	    if (!publicKey_) {
	        addOpenSSLError();
	    	return false;
	    }

	    return true;
	}

	bool
	PublicKey::toDER(char* buf, uint32_t& bufLen)
	{
	    int32_t length = i2d_X509_PUBKEY(publicKey_, 0);
	    if (length < 0) {
	    	addOpenSSLError();
	    	return false;
	    }

	    if (length > bufLen) {
	    	addError("buffer length is too short");
	    	return false;
	    }

	    bufLen = length;
	    i2d_X509_PUBKEY(publicKey_, (unsigned char**)&buf);

	    return true;
	}

}
