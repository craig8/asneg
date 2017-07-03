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

#ifndef __OpcUaStackServer_AttributeService_h__
#define __OpcUaStackServer_AttributeService_h__

#include "OpcUaStackCore/Base/os.h"
#include "OpcUaStackCore/Base/ObjectPool.h"
#include "OpcUaStackCore/ServiceSet/ServiceTransactionIf.h"
#include "OpcUaStackCore/ServiceSet/AttributeServiceTransaction.h"
#include "OpcUaStackServer/ServiceSet/ServiceSetBase.h"

using namespace OpcUaStackCore;

namespace OpcUaStackServer
{

	class DLLEXPORT AttributeService 
	: public ServiceSetBase
	, public Object
	{
	  public:
		typedef boost::shared_ptr<AttributeService> SPtr;

		AttributeService(void);
		~AttributeService(void);

		//- Component -----------------------------------------------------------------
		void receive(Message::SPtr message);
		//- Component -----------------------------------------------------------------

	  private:
		void receiveReadRequest(ServiceTransaction::SPtr serviceTransaction);
		void forwardRead(BaseNodeClass::SPtr baseNodeClass, ReadRequest::SPtr readRequest, ReadValueId::SPtr readValueId);
		void receiveWriteRequest(ServiceTransaction::SPtr serviceTransaction);
		OpcUaStatusCode forwardWrite(BaseNodeClass::SPtr baseNodeClass, WriteRequest::SPtr writeRequest, WriteValue::SPtr writeValue);
		void receiveHistoryReadRequest(ServiceTransaction::SPtr serviceTransaction);
		void receiveHistoryUpdateRequest(ServiceTransaction::SPtr serviceTransaction);
	};

}

#endif
