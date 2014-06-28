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
	: requestHeaderSPtr_()
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
		OpcUaStackCore::opcUaBinaryEncode(os, secureChannelId_);
	}

	void 
	CloseSecureChannelRequest::opcUaBinaryDecode(std::istream& is)
	{
		requestHeaderSPtr_->opcUaBinaryDecode(is);
		OpcUaStackCore::opcUaBinaryDecode(is, secureChannelId_);
	}

}