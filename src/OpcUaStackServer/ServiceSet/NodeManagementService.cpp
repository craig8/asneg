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

#include "OpcUaStackCore/BuildInTypes/OpcUaIdentifier.h"
#include "OpcUaStackCore/Base/Log.h"
#include "OpcUaStackServer/ServiceSet/NodeManagementService.h"
#include "OpcUaStackServer/AddressSpaceModel/ObjectNodeClass.h"

namespace OpcUaStackServer
{

	NodeManagementService::NodeManagementService(void)
	{
	}

	NodeManagementService::~NodeManagementService(void)
	{
	}

	void 
	NodeManagementService::receive(Message::SPtr message)
	{
		ServiceTransaction::SPtr serviceTransaction = boost::static_pointer_cast<ServiceTransaction>(message);
		switch (serviceTransaction->nodeTypeRequest().nodeId<uint32_t>()) 
		{
			case OpcUaId_AddNodesRequest_Encoding_DefaultBinary:
				receiveAddNodesRequest(serviceTransaction);
				break;
			case OpcUaId_AddReferencesRequest_Encoding_DefaultBinary:
				receiveAddReferencesRequest(serviceTransaction);
				break;
			case OpcUaId_DeleteNodesRequest_Encoding_DefaultBinary:
				receiveDeleteNodesRequest(serviceTransaction);
				break;
			case OpcUaId_DeleteReferencesRequest_Encoding_DefaultBinary:
				receiveDeleteReferencesRequest(serviceTransaction);
				break;
			default:
				serviceTransaction->statusCode(BadInternalError);
				serviceTransaction->componentSession()->send(serviceTransaction);
		}
	}

	void 
	NodeManagementService::receiveAddNodesRequest(ServiceTransaction::SPtr serviceTransaction)
	{
		OpcUaStatusCode statusCode = Success;
		ServiceTransactionAddNodes::SPtr trx = boost::static_pointer_cast<ServiceTransactionAddNodes>(serviceTransaction);
		AddNodesRequest::SPtr addNodesRequest = trx->request();
		AddNodesResponse::SPtr addNodesResponse = trx->response();

		uint32_t size = addNodesRequest->nodesToAdd()->size();
		addNodesResponse->results()->resize(size);

		Log(Debug, "node management service add nodes request")
			.parameter("Trx", serviceTransaction->transactionId())
			.parameter("NumberNodes", size);

		for (uint32_t idx=0; idx<size; idx++) {
			AddNodesResult::SPtr addNodesResult = AddNodesResult::construct();
			addNodesResponse->results()->set(idx, addNodesResult);
			
			AddNodesItem::SPtr addNodesItem;
			addNodesRequest->nodesToAdd()->get(idx, addNodesItem);

			statusCode = addNode(idx, addNodesItem, addNodesResult);
			if (statusCode != Success) break; 
		}

		serviceTransaction->statusCode(statusCode);
		serviceTransaction->componentSession()->send(serviceTransaction);
	}

	void 
	NodeManagementService::receiveAddReferencesRequest(ServiceTransaction::SPtr serviceTransaction)
	{
		// FIXME:
		serviceTransaction->statusCode(BadInternalError);
		serviceTransaction->componentSession()->send(serviceTransaction);
	}

	void 
	NodeManagementService::receiveDeleteNodesRequest(ServiceTransaction::SPtr serviceTransaction)
	{
		// FIXME:
		serviceTransaction->statusCode(BadInternalError);
		serviceTransaction->componentSession()->send(serviceTransaction);
	}

	void 
	NodeManagementService::receiveDeleteReferencesRequest(ServiceTransaction::SPtr serviceTransaction)
	{
		// FIXME:
		serviceTransaction->statusCode(BadInternalError);
		serviceTransaction->componentSession()->send(serviceTransaction);
	}


	// ------------------------------------------------------------------------
	// ------------------------------------------------------------------------
	//
	// add node
	//
	// ------------------------------------------------------------------------
	// ------------------------------------------------------------------------
	OpcUaStatusCode 
	NodeManagementService::addNode(uint32_t pos, BaseNodeClass::SPtr baseNodeClass)
	{
		if ((informationModel_->find(baseNodeClass->nodeId().data())).get() != nullptr) {
			Log(Error, "node already exist")
					.parameter("Pos", pos)
					.parameter("BrowseName", baseNodeClass->browseName());
			return BadNodeIdExists;
		}
		informationModel_->insert(baseNodeClass);
		return Success;
	}

	OpcUaStatusCode 
	NodeManagementService::addNode(uint32_t pos, AddNodesItem::SPtr addNodesItem, AddNodesResult::SPtr addNodesResult)
	{
		switch (addNodesItem->nodeClass()->nodeClassType())
		{
			case NodeClassType_Object: return addNodeObject(pos, addNodesItem, addNodesResult);
			case NodeClassType_Variable:
			case NodeClassType_Method:
			case NodeClassType_ObjectType:
			case NodeClassType_VariableType:
			case NodeClassType_ReferenceType:
			case NodeClassType_DataType:
			case NodeClassType_View:
			case NodeClassType_Unspecified:
			case NodeClassType_Dummy:
			default:
			{
				Log(Error, "invalid node class")
					.parameter("Pos", pos)
					.parameter("BrowseName", *addNodesItem->browseName());
				addNodesResult->statusCode(BadInternalError);
			}
		}
		return Success;
	}

	OpcUaStatusCode 
	NodeManagementService::addBaseNodeClass(uint32_t pos, BaseNodeClass::SPtr baseNodeClass, AddNodesItem::SPtr addNodesItem, AddNodesResult::SPtr addNodesResult)
	{
		baseNodeClass->nodeClass().data(addNodesItem->nodeClass()->nodeClassType());
		baseNodeClass->browseName().data(*addNodesItem->browseName());
		return Success;
	}

	OpcUaStatusCode 
	NodeManagementService::addNodeObject(uint32_t pos, AddNodesItem::SPtr addNodesItem, AddNodesResult::SPtr addNodesResult)
	{
		OpcUaStatusCode statusCode;
		ObjectNodeClass::SPtr objectNodeClass = ObjectNodeClass::construct();

		// set base attributes
		statusCode = addBaseNodeClass(pos, objectNodeClass, addNodesItem, addNodesResult);
		if (statusCode != Success) return statusCode;

		OpcUaNodeId nodeId; //= addNodesItem->requestedNewNodeId();
		objectNodeClass->nodeId().data(nodeId);

		// get object attributes 
		if (addNodesItem->nodeAttributes().parameterTypeId().nodeId<uint32_t>() != OpcUaId_ObjectAttributes) {
			Log(Error, "invalid attribute type")
				.parameter("Pos", pos)
				.parameter("BrowseName", *addNodesItem->browseName())
				.parameter("AttributeType", addNodesItem->nodeAttributes().parameterTypeId().nodeId<uint32_t>());
			addNodesResult->statusCode(BadInvalidArgument);
			return Success;
		}
		ObjectAttributes::SPtr objectAttributes = addNodesItem->nodeAttributes().parameter<ObjectAttributes>(); 
		
		objectNodeClass->displayName().data(*objectAttributes->displayName());
		objectNodeClass->description().data(*objectAttributes->description());
		objectNodeClass->eventNotifier().data(objectAttributes->eventNotifier());
		objectNodeClass->writeMask().data(objectAttributes->writeMask());
		objectNodeClass->userWriteMask().data(objectAttributes->userWriteMask());
		
		addNodesResult->statusCode(Success);
		return BadInternalError;
	}

}
