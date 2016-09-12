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

#include "OpcUaStackCore/StandardDataTypes/Argument.h"

namespace OpcUaStackCore
{

	Argument::Argument(void)
	: Object()
	, name_()
	, dataType_()
	, valueRank_(-1)
	, arrayDimensions_()
	, description_()
	{
	}

	Argument::~Argument(void)
	{
	}


	OpcUaString&
	Argument::name(void)
	{
		return name_;
	}

	OpcUaNodeId&
	Argument::dataType(void)
	{
		return dataType_;
	}

	OpcUaInt32&
	Argument::valueRank(void)
	{
		return valueRank_;
	}

	OpcUaUInt32Array::SPtr&
	Argument::arrayDimensions(void)
	{
		return arrayDimensions_;
	}

	OpcUaLocalizedText&
	Argument::description(void)
	{
		return description_;
	}

	void
	Argument::copyTo(Argument& argument)
	{
		name_.copyTo(argument.name_);
		dataType_.copyTo(argument.dataType_);
		argument.valueRank_ = valueRank_;
		if (arrayDimensions_.get() != nullptr) {
			arrayDimensions_->copyTo(*argument.arrayDimensions_);
		}
		description_.copyTo(argument.description_);
	}

	bool
	Argument::operator==(const Argument& argument) const
	{
		Argument* dst = const_cast<Argument*>(&argument);

		if (arrayDimensions_.get() == nullptr && dst->arrayDimensions().get() != nullptr) {
			return false;
		}
		if (arrayDimensions_.get() != nullptr && dst->arrayDimensions().get() == nullptr) {
			return false;
		}
		if (*arrayDimensions_ == *dst->arrayDimensions()) return false;

		return
			name_ == dst->name() &&
			dataType_ == dst->dataType() &&
			valueRank_ == dst->valueRank() &&
			description_ == dst->description();
	}

	// ------------------------------------------------------------------------
	// ------------------------------------------------------------------------
	//
	// ExtensionObjectBase
	//
	// ------------------------------------------------------------------------
	// ------------------------------------------------------------------------
	ExtensionObjectBase::BSPtr
	Argument::factory(void)
	{
		return constructSPtr<Argument>();
	}

	void
	Argument::opcUaBinaryEncode(std::ostream& os) const
	{
		name_.opcUaBinaryEncode(os);
		dataType_.opcUaBinaryEncode(os);
		OpcUaNumber::opcUaBinaryEncode(os, valueRank_);
		if (arrayDimensions_.get() == nullptr) {
			OpcUaNumber::opcUaBinaryEncode(os, (OpcUaInt32)-1);
		}
		else {
			arrayDimensions_->opcUaBinaryEncode(os);
		}
		description_.opcUaBinaryEncode(os);
	}

	void
	Argument::opcUaBinaryDecode(std::istream& is)
	{
		arrayDimensions_ = constructSPtr<OpcUaUInt32Array>();

		name_.opcUaBinaryDecode(is);
		dataType_.opcUaBinaryDecode(is);
		OpcUaNumber::opcUaBinaryDecode(is, valueRank_);
		arrayDimensions_->opcUaBinaryDecode(is);
		description_.opcUaBinaryDecode(is);
	}

	void
	Argument::copyTo(ExtensionObjectBase& extensionObjectBase)
	{
		Argument* dst = dynamic_cast<Argument*>(&extensionObjectBase);
		copyTo(*dst);
	}

	bool
	Argument::equal(ExtensionObjectBase& extensionObjectBase) const
	{
		Argument* dst = dynamic_cast<Argument*>(&extensionObjectBase);
		return *this == *dst;
	}

	void
	Argument::out(std::ostream& os)
	{
		os << "Name="; name_.out(os);
		os << ", DataType=" << dataType_;
		os << ", ValueRank=" << valueRank_;
		os << ", ArrayDimensions="; arrayDimensions_->out(os);
		os << ", Description="; description_.out(os);
	}

}


