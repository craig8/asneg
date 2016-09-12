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

#include "OpcUaStackCore/SecureChannel/CloseSecureChannelRequest.h"

namespace OpcUaStackCore
{

	// ------------------------------------------------------------------------
	// ------------------------------------------------------------------------
	//
	// CloseSecureChannelRequest
	//
	// ------------------------------------------------------------------------
	// ------------------------------------------------------------------------
	CloseSecureChannelRequest::CloseSecureChannelRequest(void)
	: requestHeaderSPtr_(RequestHeader::construct())
	, secureChannelId_()
	{
	}
		
	CloseSecureChannelRequest::~CloseSecureChannelRequest(void)
	{
	}

	void 
	CloseSecureChannelRequest::requestHeader(const RequestHeader::SPtr requestHeaderSPtr)
	{
		requestHeaderSPtr_ = requestHeaderSPtr;
	}

	RequestHeader::SPtr  
	CloseSecureChannelRequest::requestHeader(void) const
	{
		return requestHeaderSPtr_;
	}

	void  
	CloseSecureChannelRequest::secureChannelId(const OpcUaByte *buf, OpcUaInt32 bufLen)
	{
		secureChannelId_.value(buf, bufLen);
	}

	void  
	CloseSecureChannelRequest::secureChannelId(OpcUaByte **buf, OpcUaInt32* bufLen) const
	{
		secureChannelId_.value(buf, bufLen);
	}

	void 
	CloseSecureChannelRequest::opcUaBinaryEncode(std::ostream& os) const
	{
		requestHeaderSPtr_->opcUaBinaryEncode(os);
		secureChannelId_.opcUaBinaryEncode(os);
	}

	void 
	CloseSecureChannelRequest::opcUaBinaryDecode(std::istream& is)
	{
		requestHeaderSPtr_->opcUaBinaryDecode(is);
		secureChannelId_.opcUaBinaryDecode(is);
	}

}
