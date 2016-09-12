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

   Autor: Samuel Huebl (samuel.huebl@asneg.de)
 */

#include "OpcUaStackCore/StandardDataTypes/SemanticChangeStructureDataType.h"

namespace OpcUaStackCore
{

	SemanticChangeStructureDataType::SemanticChangeStructureDataType(void)
	: ObjectPool<SemanticChangeStructureDataType>()
	, affected_()
	, affectedType_()
	{
	}

	SemanticChangeStructureDataType::~SemanticChangeStructureDataType(void)
	{
	}

	OpcUaNodeId&
	SemanticChangeStructureDataType::affected(void)
	{
		return affected_;
	}

	void
	SemanticChangeStructureDataType::affected(OpcUaNodeId affected)
	{
		affected_ = affected;
	}

	OpcUaNodeId&
	SemanticChangeStructureDataType::affectedType(void)
	{
		return affectedType_;
	}

	void
	SemanticChangeStructureDataType::affectedType(OpcUaNodeId affectedType)
	{
		affectedType_ = affectedType;
	}

	void
	SemanticChangeStructureDataType::copyTo(SemanticChangeStructureDataType& semanticChangeStructureDataType)
	{
		affected_.copyTo(semanticChangeStructureDataType.affected());
		affectedType_.copyTo(semanticChangeStructureDataType.affectedType());
	}

	bool
	SemanticChangeStructureDataType::operator==(const SemanticChangeStructureDataType& semanticChangeStructureDataType) const
	{
		SemanticChangeStructureDataType* dst = const_cast<SemanticChangeStructureDataType*>(&semanticChangeStructureDataType);
		return
			affected_ == dst->affected() &&
			affectedType_ == dst->affectedType();
	}

	// ------------------------------------------------------------------------
	// ------------------------------------------------------------------------
	//
	// ExtensionObjectBase
	//
	// ------------------------------------------------------------------------
	// ------------------------------------------------------------------------
	ExtensionObjectBase::BSPtr
	SemanticChangeStructureDataType::factory(void)
	{
		return SemanticChangeStructureDataType::construct();
	}

	void
	SemanticChangeStructureDataType::opcUaBinaryEncode(std::ostream& os) const
	{
		affected_.opcUaBinaryEncode(os);
		affectedType_.opcUaBinaryEncode(os);
	}

	void
	SemanticChangeStructureDataType::opcUaBinaryDecode(std::istream& is)
	{
		affected_.opcUaBinaryDecode(is);
		affectedType_.opcUaBinaryDecode(is);
	}

	void
	SemanticChangeStructureDataType::copyTo(ExtensionObjectBase& extensionObjectBase)
	{
		SemanticChangeStructureDataType* dst = dynamic_cast<SemanticChangeStructureDataType*>(&extensionObjectBase);
		copyTo(*dst);
	}

	bool
	SemanticChangeStructureDataType::equal(ExtensionObjectBase& extensionObjectBase) const
	{
		SemanticChangeStructureDataType* dst = dynamic_cast<SemanticChangeStructureDataType*>(&extensionObjectBase);
		return *this == *dst;
	}

	void
	SemanticChangeStructureDataType::out(std::ostream& os)
	{
		os << "Affected=" << affected_;
		os << ", AffectedType=" << affectedType_;
	}

}

