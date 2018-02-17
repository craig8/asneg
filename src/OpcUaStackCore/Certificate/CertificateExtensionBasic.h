/*
   Copyright 2018 Kai Huebl (kai@huebl-sgh.de)

   Lizenziert gemäß Apache Licence Version 2.0 (die „Lizenz“); Nutzung dieser
   Datei nur in Übereinstimmung mit der Lizenz erlaubt.
   Eine Kopie der Lizenz erhalten Sie auf http://www.apache.org/licenses/LICENSE-2.0.

   Sofern nicht gemäß geltendem Recht vorgeschrieben oder schriftlich vereinbart,
   erfolgt die Bereitstellung der im Rahmen der Lizenz verbreiteten Software OHNE
   GEWÄHR ODER VORBEHALTE – ganz gleich, ob ausdrücklich oder stillschweigend.

   CertificateExtensionBasicrmationen über die jeweiligen Bedingungen für Genehmigungen und Einschränkungen
   im Rahmen der Lizenz finden Sie in der Lizenz.

   Autor: Kai Huebl (kai@huebl-sgh.de)
 */

#ifndef __OpcUaStackCore_CertificateExtensionBasic_h__
#define __OpcUaStackCore_CertificateExtensionBasic_h__

#include <openssl/x509.h>
#include <openssl/x509v3.h>
#include "OpcUaStackCore/Base/os.h"
#include "OpcUaStackCore/Certificate/OpenSSLError.h"

namespace OpcUaStackCore
{

	class DLLEXPORT CertificateExtensionBasic
	: public OpenSSLError
	{
	  public:
		CertificateExtensionBasic(void);
		~CertificateExtensionBasic(void);

		void basicConstraints(const std::string& basicConstraints);
		std::string& basicConstraints(void);
		void nsComment(const std::string& nsComment);
		std::string& nsComment(void);
		void subjectKeyIdentifier(const std::string& subjectKeyIdentifier);
		std::string& subjectKeyIdentifier(void);
		void authorityKeyIdentifier(const std::string& authorityKeyIdentifier);
		std::string& authorityKeyIdentifier(void);
		void keyUsage(const std::string& keyUsage);
		std::string& keyUsage(void);
		void extendedKeyUsage(const std::string& extendedKeyUsage);
		std::string& extendedKeyUsage(void);

		bool encodeX509(X509 *cert, X509V3_CTX& ctx);

	  private:
		bool encodeX509Extension(X509 *cert, X509V3_CTX& ctx, const std::string& key, const std::string& value);

		std::string basicConstraints_;
		std::string nsComment_;
		std::string subjectKeyIdentifier_;
		std::string authorityKeyIdentifier_;
		std::string keyUsage_;
		std::string extendedKeyUsage_;
	};

}

#endif
