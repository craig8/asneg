#include "unittest.h"
#include "OpcUaStackClient/ValueBasedInterface/VBIClient.h"
#include "OpcUaStackClient/ValueBasedInterface/VBIClientHandlerTest.h"

using namespace OpcUaStackClient;

#ifdef REAL_SERVER

BOOST_AUTO_TEST_SUITE(VBISyncReal_MonitoredItem_)

BOOST_AUTO_TEST_CASE(VBISyncReal_MonitoredItem_)
{
	std::cout << "VBISyncReal_MonitoredItem_t" << std::endl;
}

BOOST_AUTO_TEST_CASE(VBISyncReal_MonitoredItem_create_delete)
{
	OpcUaStatusCode statusCode;
	VBIClient client;

	// connect session
	ConnectContext connectContext;
	connectContext.endpointUrl_ = REAL_SERVER_URI;
	connectContext.sessionName_ = REAL_SESSION_NAME;
	BOOST_REQUIRE(client.syncConnect(connectContext) == Success);

	// create subscription
	uint32_t subscriptionId;
	BOOST_REQUIRE(client.syncCreateSubscription(subscriptionId) == Success);

	// create monitored item
	uint32_t clientHandle = 2345;
	OpcUaNodeId nodeId;
	nodeId.set((OpcUaUInt32)2258);
	uint32_t monitoredItemId;
	BOOST_REQUIRE(client.syncCreateMonitoredItem(nodeId, subscriptionId, clientHandle, monitoredItemId) == Success);

	// delete monitored item
	BOOST_REQUIRE(client.syncDeleteMonitoredItem(subscriptionId, monitoredItemId) == Success);

	// delete subscription
	BOOST_REQUIRE(client.syncDeleteSubscription(subscriptionId) == Success);

	// disconnect session
	BOOST_REQUIRE(client.syncDisconnect() == Success);
}

BOOST_AUTO_TEST_CASE(VBISyncReal_MonitoredItem_create_delete_callback)
{
	VBIClientHandlerTest vbiClientHandlerTest;
	OpcUaStatusCode statusCode;
	VBIClient client;

	// connect session
	ConnectContext connectContext;
	connectContext.endpointUrl_ = REAL_SERVER_URI;
	connectContext.sessionName_ = REAL_SESSION_NAME;
	BOOST_REQUIRE(client.syncConnect(connectContext) == Success);

	// set data change callback
	client.setDataChangeCallback(
		boost::bind(&VBIClientHandlerTest::dataChangeCallback, &vbiClientHandlerTest, _1, _2)
	);

	// create subscription
	uint32_t subscriptionId;
	BOOST_REQUIRE(client.syncCreateSubscription(subscriptionId) == Success);

	// create monitored item
	uint32_t clientHandle = 3344;
	OpcUaNodeId nodeId;
	nodeId.set((OpcUaUInt32)2258);
	uint32_t monitoredItemId;
	vbiClientHandlerTest.dataChangeCallback_.initEvent();
	BOOST_REQUIRE(client.syncCreateMonitoredItem(nodeId, subscriptionId, clientHandle, monitoredItemId) == Success);
	BOOST_REQUIRE(vbiClientHandlerTest.dataChangeCallback_.waitForEvent(1000) == true);
	BOOST_REQUIRE(vbiClientHandlerTest.clientHandle_ == clientHandle);

	// delete monitored item
	BOOST_REQUIRE(client.syncDeleteMonitoredItem(subscriptionId, monitoredItemId) == Success);

	// delete subscription
	BOOST_REQUIRE(client.syncDeleteSubscription(subscriptionId) == Success);

	// disconnect session
	BOOST_REQUIRE(client.syncDisconnect() == Success);
}

BOOST_AUTO_TEST_CASE(VBISyncReal_MonitoredItem_data_change)
{
	VBIClientHandlerTest vbiClientHandlerTest;
	OpcUaStatusCode statusCode;
	VBIClient client;

	// connect session
	ConnectContext connectContext;
	connectContext.endpointUrl_ = REAL_SERVER_URI;
	connectContext.sessionName_ = REAL_SESSION_NAME;
	BOOST_REQUIRE(client.syncConnect(connectContext) == Success);

	// set data change callback
	client.setDataChangeCallback(
		boost::bind(&VBIClientHandlerTest::dataChangeCallback, &vbiClientHandlerTest, _1, _2)
	);

	// create subscription
	uint32_t subscriptionId;
	BOOST_REQUIRE(client.syncCreateSubscription(subscriptionId) == Success);

	// create monitored item
	uint32_t clientHandle = 3344;
	OpcUaNodeId nodeId;
	nodeId.set((OpcUaUInt32)2258);
	uint32_t monitoredItemId;
	vbiClientHandlerTest.dataChangeCallback_.initEvent();
	BOOST_REQUIRE(client.syncCreateMonitoredItem(nodeId, subscriptionId, clientHandle, monitoredItemId) == Success);
	BOOST_REQUIRE(vbiClientHandlerTest.dataChangeCallback_.waitForEvent(1000) == true);
	BOOST_REQUIRE(vbiClientHandlerTest.clientHandle_ == clientHandle);

	// data change
	for (uint32_t idx=0; idx<2; idx++) {
		vbiClientHandlerTest.dataChangeCallback_.initEvent();
		BOOST_REQUIRE(vbiClientHandlerTest.dataChangeCallback_.waitForEvent(3000) == true);
	}

	// delete monitored item
	BOOST_REQUIRE(client.syncDeleteMonitoredItem(subscriptionId, monitoredItemId) == Success);

	// delete subscription
	BOOST_REQUIRE(client.syncDeleteSubscription(subscriptionId) == Success);

	// disconnect session
	BOOST_REQUIRE(client.syncDisconnect() == Success);
}

BOOST_AUTO_TEST_SUITE_END()

#endif
