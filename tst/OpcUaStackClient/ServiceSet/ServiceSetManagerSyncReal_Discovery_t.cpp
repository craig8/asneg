#include "unittest.h"
#include "OpcUaStackClient/ServiceSet/ServiceSetManager.h"

using namespace OpcUaStackClient;

#ifdef REAL_SERVER

BOOST_AUTO_TEST_SUITE()

BOOST_AUTO_TEST_CASE(ServiceSetManagerSyncReal_Discovery_)
{
	std::cout << "ServiceSetManagerSyncReal_Discovery_t" << std::endl;
}

BOOST_AUTO_TEST_CASE(ServiceSetManagerSyncReal_Discovery_discovery_GetEndpoints)
{
	ServiceSetManager serviceSetManager;
	DiscoveryServiceIfTestHandler discoveryServiceIfTestHandler;
	SessionServiceIfTestHandler sessionIfTestHandler;

	// set secure channel configuration
	SessionServiceConfig sessionServiceConfig;
	sessionServiceConfig.mode_ = SessionService::M_SecureChannel;
	sessionServiceConfig.sessionServiceIf_ = &sessionIfTestHandler;
	sessionServiceConfig.secureChannelClient_->endpointUrl(REAL_SERVER_URI);
	sessionServiceConfig.session_->sessionName(REAL_SESSION_NAME);

	// create session
	SessionService::SPtr sessionService;
	sessionService = serviceSetManager.sessionService(sessionServiceConfig);
	BOOST_REQUIRE(sessionService.get() != nullptr);

	// connect secure channel
	BOOST_REQUIRE(sessionService->syncConnect() == Success);

	// create discovery service
	DiscoveryService::SPtr discoveryService;
	DiscoveryServiceConfig discoveryServiceConfig;
	discoveryServiceConfig.discoveryServiceIf_ = &discoveryServiceIfTestHandler;
	discoveryService = serviceSetManager.discoveryService(sessionService, discoveryServiceConfig);
	BOOST_REQUIRE(discoveryService.get() != nullptr);

	// create and send GetEndpointsRequest
	ServiceTransactionGetEndpoints::SPtr trx;
	trx = constructSPtr<ServiceTransactionGetEndpoints>();
	GetEndpointsRequest::SPtr req = trx->request();
	req->endpointUrl(REAL_SERVER_URI);

	discoveryService->syncSend(trx);
	GetEndpointsResponse::SPtr res = trx->response();
	BOOST_REQUIRE(trx->statusCode() == Success);
	BOOST_REQUIRE(res->endpoints()->size() > 0);

	// disconnect secure channel
	BOOST_REQUIRE(sessionService->syncDisconnect() == Success);
}


BOOST_AUTO_TEST_SUITE_END()

#endif
