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

#ifndef __OpcUaStackCore_AddNodesResponse_h__
#define __OpcUaStackCore_AddNodesResponse_h__

#include <stdint.h>
#include "OpcUaStackCore/Base/ObjectPool.h"
#include "OpcUaStackCore/Base/os.h"
#include "OpcUaStackCore/BuildInTypes/BuildInTypes.h"
#include "OpcUaStackCore/SecureChannel/ResponseHeader.h"
#include "OpcUaStackCore/ServiceSet/AddNodesResult.h"

namespace OpcUaStackCore
{

	class DLLEXPORT AddNodesResponse : public  ObjectPool<AddNodesResponse>
	{
	  public:
		typedef boost::shared_ptr<AddNodesResponse> SPtr;

		AddNodesResponse(void);
		virtual ~AddNodesResponse(void);

		void results(const AddNodesResultArray::SPtr addNodesResultArraySPtr);
		AddNodesResultArray::SPtr results() const;

		void diagnosticInfos(const OpcUaDiagnosticInfoArray::SPtr diagnosticInfosSPtr);
		OpcUaDiagnosticInfoArray::SPtr diagnosticInfos(void) const;
	
		void opcUaBinaryEncode(std::ostream& os) const;
		void opcUaBinaryDecode(std::istream& is);

	  private:
		  AddNodesResultArray::SPtr addNodesResultArraySPtr_;
		  OpcUaDiagnosticInfoArray::SPtr diagnosticInfoArraySPtr_;
	};

}

#endif
