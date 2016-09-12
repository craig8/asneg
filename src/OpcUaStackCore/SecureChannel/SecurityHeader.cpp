/*
   Copyright 2015 Kai Huebl (kai@huebl-sgh.de)

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

#include "OpcUaStackCore/SecureChannel/SecurityHeader.h"
#include "OpcUaStackCore/SecureChannel/MessageDefaults.h"

namespace OpcUaStackCore
{

	SecurityHeader::SecurityHeader(void)
	: securityPolicyUri_()
	, senderCertificate_()
	, receiverCertificateThumbprint_()
	{
	}
		
	SecurityHeader::~SecurityHeader(void)
	{
	}

	void 
	SecurityHeader::securityPolicyUri(OpcUaByte *buf, OpcUaInt32 bufLen)
	{
		securityPolicyUri_.value(buf, bufLen);
	}

	void 
	SecurityHeader::securityPolicyUri(OpcUaByte **buf, OpcUaInt32* bufLen) const
	{
		securityPolicyUri_.value(buf, bufLen);
	}

	void 
	SecurityHeader::senderCertificate(OpcUaByte *buf, OpcUaInt32 bufLen)
	{
		senderCertificate_.value(buf, bufLen);
	}

	void 
	SecurityHeader::senderCertificate(OpcUaByte **buf, OpcUaInt32* bufLen) const
	{
		senderCertificate_.value(buf, bufLen);
	}

	void 
	SecurityHeader::receiverCertificateThumbprint(OpcUaByte *buf, OpcUaInt32 bufLen)
	{
		receiverCertificateThumbprint_.value(buf, bufLen);
	}

	void 
	SecurityHeader::receiverCertificateThumbprint(OpcUaByte **buf, OpcUaInt32* bufLen) const
	{
		receiverCertificateThumbprint_.value(buf, bufLen);
	}

	void 
	SecurityHeader::opcUaBinaryEncode(std::ostream& os) const
	{
		securityPolicyUri_.opcUaBinaryEncode(os);
		senderCertificate_.opcUaBinaryEncode(os);
		receiverCertificateThumbprint_.opcUaBinaryEncode(os);
	}

	void 
	SecurityHeader::opcUaBinaryDecode(std::istream& is)
	{
		securityPolicyUri_.opcUaBinaryDecode(is);
		senderCertificate_.opcUaBinaryDecode(is);
		receiverCertificateThumbprint_.opcUaBinaryDecode(is);
	}

}	
