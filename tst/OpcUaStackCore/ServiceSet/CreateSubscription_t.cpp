#include "unittest.h"
#include "boost/asio.hpp"
#include "OpcUaStackCore/ServiceSet/CreateSubscriptionRequest.h"
#include "OpcUaStackCore/ServiceSet/CreateSubscriptionResponse.h"
#include "OpcUaStackCore/SecureChannel/MessageHeader.h"
#include "OpcUaStackCore/SecureChannel/SequenceHeader.h"
#include "OpcUaStackCore/Base/Utility.h"
#include "OpcUaStackCore/BuildInTypes/OpcUaIdentifier.h"

#include <streambuf>
#include <iostream>

using namespace OpcUaStackCore;

BOOST_AUTO_TEST_SUITE(CreateSubscription_)

BOOST_AUTO_TEST_CASE(CreateSubscription_Title)
{
	std::cout << "CreateSubscription_t" << std::endl;
}

BOOST_AUTO_TEST_CASE(CreateSubscription_Request)
{
	RequestHeader::SPtr requestHeader = constructSPtr<RequestHeader>();
	uint32_t pos;
	OpcUaNodeId typeId;
	OpcUaGuid::SPtr opcUaGuidSPtr;
	MessageHeader::SPtr messageHeaderSPtr;
	SequenceHeader::SPtr sequenceHeaderSPtr;
	CreateSubscriptionRequest::SPtr createSubscriptionRequestSPtr;
	boost::posix_time::ptime ptime = boost::posix_time::from_iso_string("16010101T000000.000000000");
	
	// stream
	boost::asio::streambuf sb1;
	std::iostream ios1(&sb1);
	boost::asio::streambuf sb2;
	std::iostream ios2(&sb2);
	boost::asio::streambuf sb;
	std::iostream ios(&sb);

	// encode security header
	OpcUaInt32 secureChannelId;
	OpcUaInt32 secureTokenId;

	secureChannelId = 153451225;
	secureTokenId = 1;

	OpcUaNumber::opcUaBinaryEncode(ios1, secureChannelId);
	OpcUaNumber::opcUaBinaryEncode(ios1, secureTokenId);

	// encode sequence header
	sequenceHeaderSPtr = constructSPtr<SequenceHeader>();
	sequenceHeaderSPtr->sequenceNumber(54);
	sequenceHeaderSPtr->requestId(4);
	sequenceHeaderSPtr->opcUaBinaryEncode(ios1);

	// encode TypeId
	typeId.nodeId(OpcUaId_CreateSubscriptionRequest_Encoding_DefaultBinary);
	typeId.opcUaBinaryEncode(ios1);

	// build CreateSubscriptionRequest
	createSubscriptionRequestSPtr = constructSPtr<CreateSubscriptionRequest>();

	// build RequestHeader
	opcUaGuidSPtr = constructSPtr<OpcUaGuid>();
	*opcUaGuidSPtr = "0D4455B2-8D2F-B74F-864F-0AF5945DD833";
	
	requestHeader->sessionAuthenticationToken().namespaceIndex(1);
	requestHeader->sessionAuthenticationToken().nodeId(opcUaGuidSPtr);
	requestHeader->time(ptime);
	requestHeader->requestHandle(0);
	requestHeader->returnDisagnostics(0);
	requestHeader->timeoutHint(300000);
	
	// build Parameter
	createSubscriptionRequestSPtr->requestedPublishingInterval(500);
	createSubscriptionRequestSPtr->requestedLifetimeCount(2400);
	createSubscriptionRequestSPtr->requestedMaxKeepAliveCount(10);
	createSubscriptionRequestSPtr->maxNotificationsPerPublish(4294967295);
	createSubscriptionRequestSPtr->publishingEnabled(true);
	createSubscriptionRequestSPtr->priority(0);

	// encode CreateSubscriptionRequest
	requestHeader->opcUaBinaryEncode(ios1);
	createSubscriptionRequestSPtr->opcUaBinaryEncode(ios1);

	// encode MessageHeader
	messageHeaderSPtr = constructSPtr<MessageHeader>();
	messageHeaderSPtr->messageType(MessageType_Message);
	messageHeaderSPtr->messageSize(OpcUaStackCore::count(sb1)+8);
	messageHeaderSPtr->opcUaBinaryEncode(ios2);

	// stream
	ios << ios2.rdbuf() << ios1.rdbuf();
	OpcUaStackCore::dumpHex(ios);
	
	std::stringstream ss;
	ss << "4d 53 47 46 60 00 00 00  d9 7a 25 09 01 00 00 00"
	   << "36 00 00 00 04 00 00 00  01 00 13 03 04 01 00 0d"
	   << "44 55 b2 8d 2f b7 4f 86  4f 0a f5 94 5d d8 33 00"
	   << "00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 ff"	
	   << "ff ff ff e0 93 04 00 00  00 00 00 00 00 00 00 40"
	   << "7f 40 60 09 00 00 0a 00  00 00 ff ff ff ff 01 00";

	BOOST_REQUIRE(OpcUaStackCore::compare(ios, ss.str(), pos) == true);

	// decode MessageHeader
	messageHeaderSPtr = constructSPtr<MessageHeader>();
	messageHeaderSPtr->opcUaBinaryDecode(ios);
	BOOST_REQUIRE(messageHeaderSPtr->messageType() == MessageType_Message);

	// decode security header
	OpcUaNumber::opcUaBinaryDecode(ios, secureChannelId);
	BOOST_REQUIRE(secureChannelId == 153451225);
	OpcUaNumber::opcUaBinaryDecode(ios, secureTokenId);
	BOOST_REQUIRE(secureTokenId == 1);

	// decode sequence header
	sequenceHeaderSPtr = constructSPtr<SequenceHeader>();
	sequenceHeaderSPtr->opcUaBinaryDecode(ios);
	BOOST_REQUIRE(sequenceHeaderSPtr->sequenceNumber() == 54);
	BOOST_REQUIRE(sequenceHeaderSPtr->requestId() == 4);

	// decode message type id
	typeId.opcUaBinaryDecode(ios);
	BOOST_REQUIRE(typeId.namespaceIndex() == 0);
	BOOST_REQUIRE(typeId.nodeId<OpcUaUInt32>() == OpcUaId_CreateSubscriptionRequest_Encoding_DefaultBinary);

	// decode ReadRequest
	createSubscriptionRequestSPtr = constructSPtr<CreateSubscriptionRequest>();
	requestHeader->opcUaBinaryDecode(ios);
	createSubscriptionRequestSPtr->opcUaBinaryDecode(ios);

	std::string str;
	str = *requestHeader->sessionAuthenticationToken().nodeId<OpcUaGuid::SPtr>();
	BOOST_REQUIRE(requestHeader->sessionAuthenticationToken().namespaceIndex() == 1);
	BOOST_REQUIRE(str == "0D4455B2-8D2F-B74F-864F-0AF5945DD833");
	BOOST_REQUIRE(requestHeader->time().dateTime() == ptime);
	BOOST_REQUIRE(requestHeader->requestHandle() == 0);
	BOOST_REQUIRE(requestHeader->returnDisagnostics() == 0);
	BOOST_REQUIRE(requestHeader->timeoutHint() == 300000);
	BOOST_REQUIRE(createSubscriptionRequestSPtr->requestedPublishingInterval() == 500);
	BOOST_REQUIRE(createSubscriptionRequestSPtr->requestedLifetimeCount() == 2400);
	BOOST_REQUIRE(createSubscriptionRequestSPtr->requestedMaxKeepAliveCount() == 10);
	BOOST_REQUIRE(createSubscriptionRequestSPtr->maxNotificationsPerPublish() == 4294967295);
	BOOST_REQUIRE(createSubscriptionRequestSPtr->publishingEnabled() == true);
	BOOST_REQUIRE(createSubscriptionRequestSPtr->priority() == 0);
}


BOOST_AUTO_TEST_CASE(CreateSubscription_Response)
{
	ResponseHeader::SPtr responseHeader = constructSPtr<ResponseHeader>();
	uint32_t pos;
	OpcUaNodeId typeId;
	OpcUaStatusCode statusCode;
	MessageHeader::SPtr messageHeaderSPtr;
	SequenceHeader::SPtr sequenceHeaderSPtr;
	CreateSubscriptionResponse::SPtr createSubscriptionResponseSPtr;
	OpcUaDateTime sourceTimestamp, serverTimestamp;
	OpcUaDataValue::SPtr dataValueSPtr;
	OpcUaVariant::SPtr variantSPtr;
	boost::posix_time::ptime ptime;
	
	// test-time
	ptime = boost::posix_time::from_iso_string("16010101T000000.000000000");

	// stream
	boost::asio::streambuf sb1;
	std::iostream ios1(&sb1);
	boost::asio::streambuf sb2;
	std::iostream ios2(&sb2);
	boost::asio::streambuf sb;
	std::iostream ios(&sb);

	// encode security header
	OpcUaInt32 secureChannelId;
	OpcUaInt32 secureTokenId;

	secureChannelId = 153451225;
	secureTokenId = 1;

	OpcUaNumber::opcUaBinaryEncode(ios1, secureChannelId);
	OpcUaNumber::opcUaBinaryEncode(ios1, secureTokenId);

	// encode sequence header
	sequenceHeaderSPtr = constructSPtr<SequenceHeader>();
	sequenceHeaderSPtr->sequenceNumber(54);
	sequenceHeaderSPtr->requestId(4);
	sequenceHeaderSPtr->opcUaBinaryEncode(ios1);

	// encode TypeId
	typeId.nodeId(OpcUaId_CreateSubscriptionResponse_Encoding_DefaultBinary);
	typeId.opcUaBinaryEncode(ios1);

	// build ReadResponse
	createSubscriptionResponseSPtr = constructSPtr<CreateSubscriptionResponse>();

	// build ResponseHeader
	statusCode = Success;
	responseHeader->time(ptime);
	responseHeader->requestHandle(0);
	responseHeader->serviceResult(statusCode);
	
	// build Parameter
	createSubscriptionResponseSPtr->subscriptionId(153451225);
	createSubscriptionResponseSPtr->revisedPublishingInterval(500);
	createSubscriptionResponseSPtr->revisedLifetimeCount(2400);
	createSubscriptionResponseSPtr->revisedMaxKeepAliveCount(10);

	// encode ReadRequest
	responseHeader->opcUaBinaryEncode(ios1);
	createSubscriptionResponseSPtr->opcUaBinaryEncode(ios1);

	// encode MessageHeader
	messageHeaderSPtr = constructSPtr<MessageHeader>();
	messageHeaderSPtr->messageType(MessageType_Message);
	messageHeaderSPtr->messageSize(OpcUaStackCore::count(sb1)+8);
	messageHeaderSPtr->opcUaBinaryEncode(ios2);

	// stream
	ios << ios2.rdbuf() << ios1.rdbuf();
	OpcUaStackCore::dumpHex(ios);

	std::stringstream ss;
	ss << "4d 53 47 46 48 00 00 00  d9 7a 25 09 01 00 00 00"
	   << "36 00 00 00 04 00 00 00  01 00 16 03 00 00 00 00"
	   << "00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00"
	   << "00 00 00 00 d9 7a 25 09  00 00 00 00 00 40 7f 40"
	   << "60 09 00 00 0a 00 00 00";
	
	BOOST_REQUIRE(OpcUaStackCore::compare(ios, ss.str(), pos) == true);

	// decode MessageHeader
	messageHeaderSPtr = constructSPtr<MessageHeader>();
	messageHeaderSPtr->opcUaBinaryDecode(ios);
	BOOST_REQUIRE(messageHeaderSPtr->messageType() == MessageType_Message);

	// decode security header
	OpcUaNumber::opcUaBinaryDecode(ios, secureChannelId);
	BOOST_REQUIRE(secureChannelId == 153451225);
	OpcUaNumber::opcUaBinaryDecode(ios, secureTokenId);
	BOOST_REQUIRE(secureTokenId == 1);

	// decode sequence header
	sequenceHeaderSPtr = constructSPtr<SequenceHeader>();
	sequenceHeaderSPtr->opcUaBinaryDecode(ios);
	BOOST_REQUIRE(sequenceHeaderSPtr->sequenceNumber() == 54);
	BOOST_REQUIRE(sequenceHeaderSPtr->requestId() == 4);

	// decode message type id
	typeId.opcUaBinaryDecode(ios);
	BOOST_REQUIRE(typeId.namespaceIndex() == 0);
	BOOST_REQUIRE(typeId.nodeId<OpcUaUInt32>() == OpcUaId_CreateSubscriptionResponse_Encoding_DefaultBinary);

	// decode ReadResponse
	createSubscriptionResponseSPtr = constructSPtr<CreateSubscriptionResponse>();
	responseHeader->opcUaBinaryDecode(ios);
	createSubscriptionResponseSPtr->opcUaBinaryDecode(ios);

	BOOST_REQUIRE(responseHeader->time().dateTime() == ptime);
	BOOST_REQUIRE(responseHeader->requestHandle() == 0);
	BOOST_REQUIRE(responseHeader->serviceResult() == Success);

	BOOST_REQUIRE(createSubscriptionResponseSPtr->subscriptionId() == 153451225);
	BOOST_REQUIRE(createSubscriptionResponseSPtr->revisedPublishingInterval() == 500);
	BOOST_REQUIRE(createSubscriptionResponseSPtr->revisedLifetimeCount() == 2400);
	BOOST_REQUIRE(createSubscriptionResponseSPtr->revisedMaxKeepAliveCount() == 10);
}

BOOST_AUTO_TEST_SUITE_END()
