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

#include "OpcUaStackCore/ServiceSet/SetMonitoringModeResponse.h"

namespace OpcUaStackCore
{

	// ------------------------------------------------------------------------
	// ------------------------------------------------------------------------
	//
	// OpcUa SetMonitoringModeResponse
	//
	// ------------------------------------------------------------------------
	// ------------------------------------------------------------------------

	SetMonitoringModeResponse::SetMonitoringModeResponse(void)
	: Object()
	, resultArraySPtr_()
	, diagnosticInfoArraySPtr_()
	{
		resultArraySPtr_ = constructSPtr<OpcUaStatusCodeArray>();
		diagnosticInfoArraySPtr_ = constructSPtr<OpcUaDiagnosticInfoArray>();
	}

	SetMonitoringModeResponse::~SetMonitoringModeResponse(void)
	{
	}

	void 
	SetMonitoringModeResponse::results(const OpcUaStatusCodeArray::SPtr results)
	{
		resultArraySPtr_ = results;
	}
	
	OpcUaStatusCodeArray::SPtr
	SetMonitoringModeResponse::results(void) const
	{
		return resultArraySPtr_;
	}	
	
	void 
	SetMonitoringModeResponse::diagnosticInfos(const OpcUaDiagnosticInfoArray::SPtr diagnosticInfos)
	{
		diagnosticInfoArraySPtr_ = diagnosticInfos;
	}
	
	OpcUaDiagnosticInfoArray::SPtr 
	SetMonitoringModeResponse::diagnosticInfos(void) const
	{
		return diagnosticInfoArraySPtr_;
	}

	void 
	SetMonitoringModeResponse::opcUaBinaryEncode(std::ostream& os) const
	{
		resultArraySPtr_->opcUaBinaryEncode(os);
		diagnosticInfoArraySPtr_->opcUaBinaryEncode(os);
	}
	
	void 
	SetMonitoringModeResponse::opcUaBinaryDecode(std::istream& is)
	{
		resultArraySPtr_->opcUaBinaryDecode(is);
		diagnosticInfoArraySPtr_->opcUaBinaryDecode(is);
	}
}
