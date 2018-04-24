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

#include <OpcUaStackCore/Certificate/CryptoOpenSSLNONE.h>

namespace OpcUaStackCore
{

	CryptoOpenSSLNONE::CryptoOpenSSLNONE(void)
	:CryptoBase()
	{
		securityPolicy("http://opcfoundation.org/UA/SecurityPolicy#None");

		symmetricKeyLen(0);
		minimumAsymmetricKeyLen(0);
		maximumAsymmetricKeyLen(0);
		derivedEncryptionKeyLen(0);
		derivedSignatureKeyLen(0);
		signatureDataLen(0);
		asymmetricSignatureAlgorithmId(0);
		asymmetricEncryptionAlgorithmId(0);
		symmetricSignatureAlgorithmId(0);
		symmetricEncryptionAlgorithmId(0);

	}

	CryptoOpenSSLNONE::~CryptoOpenSSLNONE(void)
	{
	}

	OpcUaStatusCode
	CryptoOpenSSLNONE::asymmetricDecrypt(
	    char*       	encryptedTextBuf,
		uint32_t		encryptedTextLen,
		PrivateKey&		privateKey,
		char*       	plainTextBuf,
		uint32_t*		plainTextLen
	)
	{
		return BadNotSupported;
	}

	OpcUaStatusCode
	CryptoOpenSSLNONE::asymmetricEncrypt(
		char*       	plainTextBuf,
		uint32_t		plainTextLen,
		PublicKey&		publicKey,
		char*       	encryptedTextBuf,
		uint32_t*		encryptedTextLen
	)
	{
		return BadNotSupported;
	}

	OpcUaStatusCode
	CryptoOpenSSLNONE::symmetricDecrypt(
		char*       	encryptedTextBuf,
		uint32_t		encryptedTextLen,
		AESKey&	   		aesKey,
		IV&		   		iv,
		char*      		plainTextBuf,
		int32_t*   		plainTextLen
	)
	{
		return BadNotSupported;
	}

	OpcUaStatusCode
	CryptoOpenSSLNONE::symmetricEncrypt(
		char*       	plainTextBuf,
		uint32_t		plainTextLen,
		AESKey&	   		aesKey,
		IV&		   		iv,
		char*      		encryptedTextBuf,
		int32_t*   		encryptedTextLen
	)
	{
		return BadNotSupported;
	}

}
