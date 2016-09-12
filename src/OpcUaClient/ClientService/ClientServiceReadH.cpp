/*
   Copyright 2016 Kai Huebl (kai@huebl-sgh.de)

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

#include "OpcUaStackCore/Base/ObjectPool.h"
#include "OpcUaStackCore/ServiceSet/ReadRawModifiedDetails.h"
#include "OpcUaStackCore/ServiceSet/HistoryData.h"
#include "OpcUaClient/ClientCommand/CommandReadH.h"
#include "OpcUaClient/ClientService/ClientServiceReadH.h"

using namespace OpcUaStackCore;

namespace OpcUaClient
{

	ClientServiceReadH::ClientServiceReadH(void)
	: ClientServiceBase()
	{
	}

	ClientServiceReadH::~ClientServiceReadH(void)
	{
	}

	ClientServiceBase::SPtr
	ClientServiceReadH::createClientService(void)
	{
		return constructSPtr<ClientServiceReadH>();
	}

	bool
	ClientServiceReadH::run(ClientServiceManager& clientServiceManager, CommandBase::SPtr& commandBase)
	{
		OpcUaStatusCode statusCode;
		CommandReadH::SPtr commandReadH = boost::static_pointer_cast<CommandReadH>(commandBase);

		// create new or get existing client object
		ClientAccessObject::SPtr clientAccessObject;
		clientAccessObject = clientServiceManager.getClientAccessObject(commandReadH->session());
		if (clientAccessObject.get() == nullptr) {
			std::stringstream ss;
			ss << "get client access object failed:"
			   << " Session=" << commandReadH->session();
			errorMessage(ss.str());
			return false;
		}

		// check session
		if (clientAccessObject->sessionService_.get() == nullptr) {
			std::stringstream ss;
			ss << "session object not exist: "
			   << " Session=" << commandReadH->session();
			return false;
		}

		// get or create attribute service
		AttributeService::SPtr attributeService;
		attributeService = clientAccessObject->getOrCreateAttributeService();
		if (attributeService.get() == nullptr) {
			std::stringstream ss;
			ss << "get client attribute service failed"
			   << " Session=" << commandReadH->session();
			errorMessage(ss.str());
			return false;
		}

		// create read request
		ServiceTransactionHistoryRead::SPtr trx;
		trx = constructSPtr<ServiceTransactionHistoryRead>();
		HistoryReadRequest::SPtr req = trx->request();

		ReadRawModifiedDetails::SPtr readDetails;
		req->historyReadDetails()->parameterTypeId().set((OpcUaUInt32)OpcUaId_ReadRawModifiedDetails_Encoding_DefaultBinary);
		readDetails = req->historyReadDetails()->parameter<ReadRawModifiedDetails>();
		readDetails->startTime(commandReadH->startTime());
		readDetails->endTime(commandReadH->endTime());

		req->nodesToRead()->resize(commandReadH->nodeIdVec().size());
		for (uint32_t idx=0; idx<commandReadH->nodeIdVec().size(); idx++) {
			HistoryReadValueId::SPtr readValueId = HistoryReadValueId::construct();
			readValueId->nodeId()->copyFrom(*commandReadH->nodeIdVec()[idx]);
			readValueId->dataEncoding().namespaceIndex((OpcUaInt16) 0);
			req->nodesToRead()->push_back(readValueId);
		}

		// send read history request
		attributeService->syncSend(trx);

		// process read response
		statusCode = trx->statusCode();
		if (statusCode != Success) {
			std::stringstream ss;
			ss << "read error: "
			   << " Session=" << commandReadH->session()
			   << " StatusCode=" << OpcUaStatusCodeMap::shortString(statusCode);
			errorMessage(ss.str());
			return false;
		}

		HistoryReadResponse::SPtr res = trx->response();
		if (res->results()->size() == 0) {
			std::stringstream ss;
			ss << "read history response length error: "
			   << " Session=" << commandReadH->session();
			errorMessage(ss.str());
			return false;
		}

		for (uint32_t idx=0; idx<res->results()->size(); idx++) {
			HistoryReadResult::SPtr readResult;
			res->results()->get(idx, readResult);
			if (readResult->statusCode() != Success) {
				std::cout << "Status=" << OpcUaStatusCodeMap::shortString(readResult->statusCode()) << std::endl;;
				continue;
			}


			OpcUaNodeId typeId = readResult->historyData()->parameterTypeId();
			uint32_t id = typeId.nodeId<OpcUaUInt32>();
			if (id != OpcUaId_HistoryData_Encoding_DefaultBinary) {
				std::stringstream ss;
				ss << "receive invalid message type: "
				   << " Session=" << commandReadH->session()
				   << " TypeNodeId=" << typeId.toString();
				errorMessage(ss.str());
				return false;
			}

			HistoryData::SPtr historyData = readResult->historyData()->parameter<HistoryData>();
			for (uint32_t idx=0; idx<historyData->dataValues()->size(); idx++) {
				OpcUaDataValue::SPtr dataValue;
				historyData->dataValues()->get(idx, dataValue);
				dataValue->out(std::cout); std::cout << std::endl;

			}
		}

		return true;
	}

}

