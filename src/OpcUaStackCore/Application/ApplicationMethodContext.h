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

#ifndef __OpcUaStackCore_ApplicationMethodContext_h__
#define __OpcUaStackCore_ApplicationMethodContext_h__

#include "OpcUaStackCore/Base/BaseClass.h"
#include "OpcUaStackCore/BuildInTypes/OpcUaNodeId.h"
#include "OpcUaStackCore/BuildInTypes/OpcUaVariant.h"
#include "OpcUaStackCore/BuildInTypes/OpcUaStatusCode.h"

namespace OpcUaStackCore
{

	class ApplicationMethodContext
	{
	  public:
		BaseClass::SPtr applicationContext_;		// IN - application context from register call
		OpcUaNodeId objectNodeId_;					// IN - object node id of the function
		OpcUaNodeId methodNodeId_;					// IN - method node id of the function
		OpcUaVariantArray::SPtr inputArguments_;	// IN - input arguments
		OpcUaVariantArray::SPtr outputArguments_;	// OUT - output arguments
		OpcUaStatusCode statusCode_;				// OUT - result state of the call operation
	};

}

#endif
