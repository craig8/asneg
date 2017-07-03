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

#include "OpcUaStackCore/ServiceSet/FindServersResponse.h"

namespace OpcUaStackCore
{

	// ------------------------------------------------------------------------
	// ------------------------------------------------------------------------
	//
	// OpcUa FindServersResponse
	//
	// ------------------------------------------------------------------------
	// ------------------------------------------------------------------------

	FindServersResponse::FindServersResponse(void)
	: Object()
	, responseHeaderSPtr_(constructSPtr<ResponseHeader>())
	, serverArraySPtr_(constructSPtr<ApplicationDescriptionArray>())
	{
	}

	FindServersResponse::~FindServersResponse(void)
	{
	}

	void 
	FindServersResponse::responseHeader(const ResponseHeader::SPtr responseHeaderSPtr)
	{
		responseHeaderSPtr_ = responseHeaderSPtr;
	}

	ResponseHeader::SPtr 
	FindServersResponse::responseHeader(void) const
	{
		return responseHeaderSPtr_;
	}
	
	void 
	FindServersResponse::servers(const ApplicationDescriptionArray::SPtr servers)
	{
		serverArraySPtr_ = servers;
	}
	
	ApplicationDescriptionArray::SPtr 
	FindServersResponse::servers(void) const
	{
		return serverArraySPtr_;
	}

	void 
	FindServersResponse::opcUaBinaryEncode(std::ostream& os) const
	{
		//responseHeaderSPtr_->opcUaBinaryEncode(os);
		serverArraySPtr_->opcUaBinaryEncode(os);
	}
	
	void 
	FindServersResponse::opcUaBinaryDecode(std::istream& is)
	{
		//responseHeaderSPtr_->opcUaBinaryDecode(is);
		serverArraySPtr_->opcUaBinaryDecode(is);
	}

}
