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

#include "OpcUaStackCore/ServiceSet/FindServersRequest.h"

namespace OpcUaStackCore
{

	// ------------------------------------------------------------------------
	// ------------------------------------------------------------------------
	//
	// OpcUa FindServersRequest
	//
	// ------------------------------------------------------------------------
	// ------------------------------------------------------------------------

	FindServersRequest::FindServersRequest(void)
	: Object()
	, requestHeaderSPtr_(constructSPtr<RequestHeader>())
	, endpointUrl_()
	, localeIdArraySPtr_(constructSPtr<OpcUaStringArray>())
	, serverUriArraySPtr_(constructSPtr<OpcUaStringArray>())
	{
	}

	FindServersRequest::~FindServersRequest(void)
	{
	}

	void 
	FindServersRequest::requestHeader(const RequestHeader::SPtr requestHeaderSPtr)
	{
		requestHeaderSPtr_ = requestHeaderSPtr;
	}

	RequestHeader::SPtr 
	FindServersRequest::requestHeader(void) const
	{
		return requestHeaderSPtr_;
	}

	void 
	FindServersRequest::endpointUrl(const OpcUaString& endpointUrl)
	{
		endpointUrl_ = endpointUrl;
	}

	void 
	FindServersRequest::endpointUrl(const std::string& endpointUrl)
	{
		endpointUrl_.value(endpointUrl);
	}
	
	OpcUaString& 
	FindServersRequest::endpointUrl(void)
	{
		return endpointUrl_;
	}
	
	void 
	FindServersRequest::localeIds(const OpcUaStringArray::SPtr localeIds)
	{
		localeIdArraySPtr_ = localeIds;
	}
	
	OpcUaStringArray::SPtr 
	FindServersRequest::localeIds(void) const
	{
		return localeIdArraySPtr_;
	}
	
	void 
	FindServersRequest::serverUris(const OpcUaStringArray::SPtr serverUris)
	{
		serverUriArraySPtr_ = serverUris;
	}
	
	OpcUaStringArray::SPtr 
	FindServersRequest::serverUris(void) const
	{
		return serverUriArraySPtr_;
	}

	void 
	FindServersRequest::opcUaBinaryEncode(std::ostream& os) const
	{
		//requestHeaderSPtr_->opcUaBinaryEncode(os);
		endpointUrl_.opcUaBinaryEncode(os);
		localeIdArraySPtr_->opcUaBinaryEncode(os);
		serverUriArraySPtr_->opcUaBinaryEncode(os);
	}
	
	void 
	FindServersRequest::opcUaBinaryDecode(std::istream& is)
	{
		//requestHeaderSPtr_->opcUaBinaryDecode(is);
		endpointUrl_.opcUaBinaryDecode(is);
		localeIdArraySPtr_->opcUaBinaryDecode(is);
		serverUriArraySPtr_->opcUaBinaryDecode(is);
	}

}
