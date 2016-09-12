#include "unittest.h"
#include "OpcUaStackClient/ValueBasedInterface/VBIClient.h"
#include "OpcUaStackClient/ValueBasedInterface/VBIClientHandlerTest.h"

using namespace OpcUaStackClient;

#ifdef REAL_SERVER

BOOST_AUTO_TEST_SUITE(VBIAsyncReal_Attribute_)

BOOST_AUTO_TEST_CASE(VBIAsyncReal_Attribute_)
{
	std::cout << "VBIAsyncReal_Attribute_t" << std::endl;
}

BOOST_AUTO_TEST_CASE(VBIAsyncReal_Attribute_read)
{
	VBIClientHandlerTest vbiClientHandlerTest;
	VBIClient client;

	// set session change callback
	client.setSessionChangeCallback(
		boost::bind(&VBIClientHandlerTest::sessionStateUpdate, &vbiClientHandlerTest, (uint32_t)1234, _1, _2)
	);

	// connect session
	ConnectContext connectContext;
	connectContext.endpointUrl_ = REAL_SERVER_URI;
	connectContext.sessionName_ = REAL_SESSION_NAME;
	vbiClientHandlerTest.sessionStateUpdate_.initEvent();
	client.asyncConnect(connectContext);
	BOOST_REQUIRE(vbiClientHandlerTest.sessionStateUpdate_.waitForEvent(1000) == true);
	BOOST_REQUIRE(vbiClientHandlerTest.sessionState_ == SS_Connect);
	BOOST_REQUIRE(vbiClientHandlerTest.clientHandle_ == 1234);

	// read
	OpcUaNodeId nodeId;
	nodeId.set((OpcUaInt32)2259);
	vbiClientHandlerTest.readComplete_.initEvent();
	client.asyncRead(
		nodeId,
		boost::bind(&VBIClientHandlerTest::readComplete, &vbiClientHandlerTest, _1, _2, _3)
	);
	BOOST_REQUIRE(vbiClientHandlerTest.readComplete_.waitForEvent(1000) == true);
	BOOST_REQUIRE(vbiClientHandlerTest.statusCode_ == Success);
	vbiClientHandlerTest.dataValue_.out(std::cout);

	// disconnect session
	vbiClientHandlerTest.sessionStateUpdate_.initEvent();
	client.asyncDisconnect();
	BOOST_REQUIRE(vbiClientHandlerTest.sessionStateUpdate_.waitForEvent(1000) == true);
	BOOST_REQUIRE(vbiClientHandlerTest.sessionState_ == SS_Disconnect);
	BOOST_REQUIRE(vbiClientHandlerTest.clientHandle_ == 1234);
}

BOOST_AUTO_TEST_CASE(VBIAsyncReal_Attribute_write)
{
	VBIClientHandlerTest vbiClientHandlerTest;
	VBIClient client;

	// set session change callback
	client.setSessionChangeCallback(
		boost::bind(&VBIClientHandlerTest::sessionStateUpdate, &vbiClientHandlerTest, (uint32_t)1234, _1, _2)
	);

	// connect session
	ConnectContext connectContext;
	connectContext.endpointUrl_ = REAL_SERVER_URI;
	connectContext.sessionName_ = REAL_SESSION_NAME;
	vbiClientHandlerTest.sessionStateUpdate_.initEvent();
	client.asyncConnect(connectContext);
	BOOST_REQUIRE(vbiClientHandlerTest.sessionStateUpdate_.waitForEvent(1000) == true);
	BOOST_REQUIRE(vbiClientHandlerTest.sessionState_ == SS_Connect);
	BOOST_REQUIRE(vbiClientHandlerTest.clientHandle_ == 1234);

	// write
	OpcUaNodeId nodeId;
	OpcUaDataValue dataValue;
	dataValue.variant()->set((OpcUaBoolean)1);
	nodeId.set("Demo.Static.Scalar.Boolean", 2);
	vbiClientHandlerTest.writeComplete_.initEvent();
	client.asyncWrite(
		nodeId,
		dataValue,
		boost::bind(&VBIClientHandlerTest::writeComplete, &vbiClientHandlerTest, _1, _2)
	);
	BOOST_REQUIRE(vbiClientHandlerTest.writeComplete_.waitForEvent(1000) == true);
	BOOST_REQUIRE(vbiClientHandlerTest.statusCode_ == Success);

	// disconnect session
	vbiClientHandlerTest.sessionStateUpdate_.initEvent();
	client.asyncDisconnect();
	BOOST_REQUIRE(vbiClientHandlerTest.sessionStateUpdate_.waitForEvent(1000) == true);
	BOOST_REQUIRE(vbiClientHandlerTest.sessionState_ == SS_Disconnect);
	BOOST_REQUIRE(vbiClientHandlerTest.clientHandle_ == 1234);
}

BOOST_AUTO_TEST_SUITE_END()

#endif
