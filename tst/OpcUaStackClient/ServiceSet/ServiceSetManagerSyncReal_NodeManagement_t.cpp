#include "unittest.h"
#include "OpcUaStackClient/ServiceSet/ServiceSetManager.h"

using namespace OpcUaStackClient;

#ifdef REAL_SERVER

BOOST_AUTO_TEST_SUITE()

BOOST_AUTO_TEST_CASE(ServiceSetManagerSyncReal_NodeManagement_)
{
	std::cout << "ServiceSetManagerSyncReal_NodeManagement_t" << std::endl;
}

BOOST_AUTO_TEST_CASE(ServiceSetManagerSyncReal_NodeManagement_cc)
{
	ServiceSetManager serviceSetManager;
	NodeManagementServiceIfTestHandler nodeManagementServiceIfTestHandler;
	SessionServiceIfTestHandler sessionIfTestHandler;

	// set secure channel configuration
	SessionServiceConfig sessionServiceConfig;
	sessionServiceConfig.sessionServiceIf_ = &sessionIfTestHandler;
	sessionServiceConfig.secureChannelClient_->endpointUrl(REAL_SERVER_URI);
	sessionServiceConfig.session_->sessionName(REAL_SESSION_NAME);

	// create session
	SessionService::SPtr sessionService;
	sessionService = serviceSetManager.sessionService(sessionServiceConfig);
	BOOST_REQUIRE(sessionService.get() != nullptr);

	// connect secure channel
	BOOST_REQUIRE(sessionService->syncConnect() == Success);

	// create nodeManagement service
	NodeManagementService::SPtr nodeManagementService;
	NodeManagementServiceConfig nodeManagementServiceConfig;
	nodeManagementServiceConfig.nodeManagementServiceIf_ = &nodeManagementServiceIfTestHandler;
	nodeManagementService = serviceSetManager.nodeManagementService(sessionService, nodeManagementServiceConfig);
	BOOST_REQUIRE(nodeManagementService.get() != nullptr);

	// FIXME:

	// disconnect secure channel
	BOOST_REQUIRE(sessionService->syncDisconnect() == Success);
}


BOOST_AUTO_TEST_SUITE_END()

#endif
