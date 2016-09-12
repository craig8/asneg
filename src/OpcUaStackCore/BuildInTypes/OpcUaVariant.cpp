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

#include "OpcUaStackCore/Base/Log.h"
#include "OpcUaStackCore/BuildInTypes/OpcUaVariant.h"
#include "OpcUaStackCore/BuildInTypes/Json.h"

namespace OpcUaStackCore
{

	class OpcUaVariantTypeVisitor : public boost::static_visitor<>
	{
	  public:
		void operator()(OpcUaVariantNullType) { opcUaBuildInType_ = OpcUaBuildInType_Unknown; }
		void operator()(OpcUaBoolean) { opcUaBuildInType_ = OpcUaBuildInType_OpcUaBoolean; }
		void operator()(OpcUaSByte) { opcUaBuildInType_ = OpcUaBuildInType_OpcUaSByte; }
		void operator()(OpcUaByte) { opcUaBuildInType_ = OpcUaBuildInType_OpcUaByte; }
		void operator()(OpcUaInt16) { opcUaBuildInType_ = OpcUaBuildInType_OpcUaInt16; }
		void operator()(OpcUaUInt16) { opcUaBuildInType_ = OpcUaBuildInType_OpcUaUInt16; }
		void operator()(OpcUaInt32) { opcUaBuildInType_ = OpcUaBuildInType_OpcUaInt32; }
		void operator()(OpcUaUInt32) { opcUaBuildInType_ = OpcUaBuildInType_OpcUaUInt32; }
		void operator()(OpcUaInt64) { opcUaBuildInType_ = OpcUaBuildInType_OpcUaInt64; }
		void operator()(OpcUaUInt64) { opcUaBuildInType_ = OpcUaBuildInType_OpcUaUInt64; }
		void operator()(OpcUaFloat) { opcUaBuildInType_ = OpcUaBuildInType_OpcUaFloat; }
		void operator()(OpcUaDouble) { opcUaBuildInType_ = OpcUaBuildInType_OpcUaDouble; }
		void operator()(OpcUaDateTime) { opcUaBuildInType_ = OpcUaBuildInType_OpcUaDateTime; }
		void operator()(OpcUaStatusCode) { opcUaBuildInType_ = OpcUaBuildInType_OpcUaStatusCode; }
		void operator()(OpcUaVariantSPtr opcUaVariantSPtr) {  opcUaBuildInType_ = opcUaVariantSPtr.opcUaBuildInType_; }
		
		OpcUaBuildInType opcUaBuildInType_;
	};

	OpcUaVariantSPtr::OpcUaVariantSPtr(void)
	: opcUaBuildInType_()
	, objectSPtr_()
	{
	}
	
	OpcUaVariantSPtr::~OpcUaVariantSPtr(void)
	{
	}
		

	// -------------------------------------------------------------------------
	// -------------------------------------------------------------------------
	//
	// OpcUaVariantValue
	//
	// -------------------------------------------------------------------------
	// -------------------------------------------------------------------------
	OpcUaVariantValue::OpcUaVariantValue(void)
	: variantValue_()
	{
	}
	
	OpcUaVariantValue::~OpcUaVariantValue(void)
	{
	}

	OpcUaBuildInType 
	OpcUaVariantValue::variantType(void) const
	{
		OpcUaVariantTypeVisitor opcUaVariantTypeVisitor;
		boost::apply_visitor(opcUaVariantTypeVisitor, variantValue_);
		return opcUaVariantTypeVisitor.opcUaBuildInType_;
	}

	void 
	OpcUaVariantValue::variant(const OpcUaGuid::SPtr valSPtr) 
	{
		OpcUaVariantSPtr val;
		val.opcUaBuildInType_ = OpcUaBuildInType_OpcUaGuid;
		val.objectSPtr_ = valSPtr;
		variantValue_ = val;
	}

	void 
	OpcUaVariantValue::variant(const OpcUaByteString::SPtr valSPtr) 
	{
		OpcUaVariantSPtr val;
		val.opcUaBuildInType_ = OpcUaBuildInType_OpcUaByteString;
		val.objectSPtr_ = valSPtr;
		variantValue_ = val;
	}

	void 
	OpcUaVariantValue::variant(const OpcUaString::SPtr valSPtr) 
	{
		OpcUaVariantSPtr val;
		val.opcUaBuildInType_ = OpcUaBuildInType_OpcUaString;
		val.objectSPtr_ = valSPtr;
		variantValue_ = val;
	}

	void  
	OpcUaVariantValue::variant(const OpcUaXmlElement::SPtr valSPtr)
	{
		OpcUaVariantSPtr val;
		val.opcUaBuildInType_ = OpcUaBuildInType_OpcUaXmlElement;
		val.objectSPtr_ = valSPtr;
		val.objectSPtr_ = valSPtr;
		variantValue_ = val;
	}

	void  
	OpcUaVariantValue::variant(const OpcUaNodeId::SPtr valSPtr)
	{
		OpcUaVariantSPtr val;
		val.opcUaBuildInType_ = OpcUaBuildInType_OpcUaNodeId;
		val.objectSPtr_ = valSPtr;
		val.objectSPtr_ = valSPtr;
		variantValue_ = val;
	}

	void  
	OpcUaVariantValue::variant(const OpcUaExpandedNodeId::SPtr valSPtr)
	{
		OpcUaVariantSPtr val;
		val.opcUaBuildInType_ = OpcUaBuildInType_OpcUaExpandedNodeId;
		val.objectSPtr_ = valSPtr;
		val.objectSPtr_ = valSPtr;
		variantValue_ = val;
	}

	void  
	OpcUaVariantValue::variant(const OpcUaQualifiedName::SPtr valSPtr)
	{
		OpcUaVariantSPtr val;
		val.opcUaBuildInType_ = OpcUaBuildInType_OpcUaQualifiedName;
		val.objectSPtr_ = valSPtr;
		val.objectSPtr_ = valSPtr;
		variantValue_ = val;
	}

	void  
	OpcUaVariantValue::variant(const OpcUaLocalizedText::SPtr valSPtr)
	{
		OpcUaVariantSPtr val;
		val.opcUaBuildInType_ = OpcUaBuildInType_OpcUaLocalizedText;
		val.objectSPtr_ = valSPtr;
		val.objectSPtr_ = valSPtr;
		variantValue_ = val;
	}	
	void  
	OpcUaVariantValue::variant(const OpcUaExtensionObject::SPtr valSPtr)
	{
		OpcUaVariantSPtr val;
		val.opcUaBuildInType_ = OpcUaBuildInType_OpcUaExtensionObject;
		val.objectSPtr_ = valSPtr;
		val.objectSPtr_ = valSPtr;
		variantValue_ = val;
	}

	bool 
	OpcUaVariantValue::operator!=(OpcUaVariantValue& variantValue)
	{
		return !operator==(variantValue);
	}

	bool 
	OpcUaVariantValue::operator==(OpcUaVariantValue& variantValue)
	{
		if (variantValue.variantType() != variantType()) return false;
		switch (variantType()) 
		{
			case OpcUaBuildInType_Unknown:
			{
				return true;
			}
			case  OpcUaBuildInType_OpcUaBoolean:
			{
				OpcUaBoolean value1 = boost::get<OpcUaBoolean>(variantValue_);
				OpcUaBoolean value2 = variantValue.variant<OpcUaBoolean>();
				return value1 == value2;
			}
			case  OpcUaBuildInType_OpcUaSByte:
			{
				OpcUaSByte value1 = boost::get<OpcUaSByte>(variantValue_);
				OpcUaSByte value2 = variantValue.variant<OpcUaSByte>();
				return value1 == value2;
			}
			case  OpcUaBuildInType_OpcUaByte:
			{
				OpcUaByte value1 = boost::get<OpcUaByte>(variantValue_);
				OpcUaByte value2 = variantValue.variant<OpcUaByte>();
				return value1 == value2;
			}
			case  OpcUaBuildInType_OpcUaInt16:
			{
				OpcUaInt16 value1 = boost::get<OpcUaInt16>(variantValue_);
				OpcUaInt16 value2 = variantValue.variant<OpcUaInt16>();
				return value1 == value2;
			}
			case  OpcUaBuildInType_OpcUaUInt16:
			{
				OpcUaUInt16 value1 = boost::get<OpcUaUInt16>(variantValue_);
				OpcUaUInt16 value2 = variantValue.variant<OpcUaUInt16>();
				return value1 == value2;
			}
			case  OpcUaBuildInType_OpcUaInt32:
			{
				OpcUaInt32 value1 = boost::get<OpcUaInt32>(variantValue_);
				OpcUaInt32 value2 = variantValue.variant<OpcUaInt32>();
				return value1 == value2;
			}
			case  OpcUaBuildInType_OpcUaUInt32:
			{
				OpcUaUInt32 value1 = boost::get<OpcUaUInt32>(variantValue_);
				OpcUaUInt32 value2 = variantValue.variant<OpcUaUInt32>();
				return value1 == value2;
			}
			case  OpcUaBuildInType_OpcUaInt64:
			{
				OpcUaInt64 value1 = boost::get<OpcUaInt64>(variantValue_);
				OpcUaInt64 value2 = variantValue.variant<OpcUaInt64>();
				return value1 == value2;
			}
			case  OpcUaBuildInType_OpcUaUInt64:
			{
				OpcUaUInt64 value1 = boost::get<OpcUaUInt64>(variantValue_);
				OpcUaUInt64 value2 = variantValue.variant<OpcUaUInt64>();
				return value1 == value2;
			}
			case  OpcUaBuildInType_OpcUaFloat:
			{
				OpcUaFloat value1 = boost::get<OpcUaFloat>(variantValue_);
				OpcUaFloat value2 = variantValue.variant<OpcUaFloat>();
				return value1 == value2;
			}
			case  OpcUaBuildInType_OpcUaDouble:
			{
				OpcUaDouble value1 = boost::get<OpcUaDouble>(variantValue_);
				OpcUaDouble value2 = variantValue.variant<OpcUaDouble>();
				return value1 == value2;
			}
			case  OpcUaBuildInType_OpcUaDateTime:
			{
				OpcUaDateTime value1 = boost::get<OpcUaDateTime>(variantValue_);
				OpcUaDateTime value2 = variantValue.variant<OpcUaDateTime>();
				return value1 == value2;
			}
			case  OpcUaBuildInType_OpcUaStatusCode:
			{
				OpcUaInt32 value1 = boost::get<OpcUaStatusCode>(variantValue_);
				OpcUaInt32 value2 = variantValue.variant<OpcUaStatusCode>();
				return value1 == value2;
			}
			case  OpcUaBuildInType_OpcUaGuid:
			{
				OpcUaVariantSPtr opcUaVariantSPtr1 = boost::get<OpcUaVariantSPtr>(variantValue_);
				OpcUaVariantSPtr opcUaVariantSPtr2 = variantValue.variant<OpcUaVariantSPtr>();
				OpcUaGuid::SPtr value1 = boost::static_pointer_cast<OpcUaGuid>(opcUaVariantSPtr1.objectSPtr_);
				OpcUaGuid::SPtr value2 = boost::static_pointer_cast<OpcUaGuid>(opcUaVariantSPtr2.objectSPtr_);
				return *value1 == *value2;
			}
			case  OpcUaBuildInType_OpcUaByteString:
			{
				OpcUaVariantSPtr opcUaVariantSPtr1 = boost::get<OpcUaVariantSPtr>(variantValue_);
				OpcUaVariantSPtr opcUaVariantSPtr2 = variantValue.variant<OpcUaVariantSPtr>();
				OpcUaByteString::SPtr value1 = boost::static_pointer_cast<OpcUaByteString>(opcUaVariantSPtr1.objectSPtr_);
				OpcUaByteString::SPtr value2 = boost::static_pointer_cast<OpcUaByteString>(opcUaVariantSPtr2.objectSPtr_);
				return *value1 == *value2;
			}
			case  OpcUaBuildInType_OpcUaString:
			{
				OpcUaVariantSPtr opcUaVariantSPtr1 = boost::get<OpcUaVariantSPtr>(variantValue_);
				OpcUaVariantSPtr opcUaVariantSPtr2 = variantValue.variant<OpcUaVariantSPtr>();
				OpcUaString::SPtr value1 = boost::static_pointer_cast<OpcUaString>(opcUaVariantSPtr1.objectSPtr_);
				OpcUaString::SPtr value2 = boost::static_pointer_cast<OpcUaString>(opcUaVariantSPtr2.objectSPtr_);
				return *value1 == *value2;
			}
			case  OpcUaBuildInType_OpcUaXmlElement:
			{
				// FIXME: actualy not used
				return false;
			}
			case  OpcUaBuildInType_OpcUaNodeId:
			{
				OpcUaVariantSPtr opcUaVariantSPtr1 = boost::get<OpcUaVariantSPtr>(variantValue_);
				OpcUaVariantSPtr opcUaVariantSPtr2 = variantValue.variant<OpcUaVariantSPtr>();
				OpcUaNodeId::SPtr value1 = boost::static_pointer_cast<OpcUaNodeId>(opcUaVariantSPtr1.objectSPtr_);
				OpcUaNodeId::SPtr value2 = boost::static_pointer_cast<OpcUaNodeId>(opcUaVariantSPtr2.objectSPtr_);
				return *value1 == *value2;
			}
			case  OpcUaBuildInType_OpcUaExpandedNodeId:
			{
				OpcUaVariantSPtr opcUaVariantSPtr1 = boost::get<OpcUaVariantSPtr>(variantValue_);
				OpcUaVariantSPtr opcUaVariantSPtr2 = variantValue.variant<OpcUaVariantSPtr>();
				OpcUaExpandedNodeId::SPtr value1 = boost::static_pointer_cast<OpcUaExpandedNodeId>(opcUaVariantSPtr1.objectSPtr_);
				OpcUaExpandedNodeId::SPtr value2 = boost::static_pointer_cast<OpcUaExpandedNodeId>(opcUaVariantSPtr2.objectSPtr_);
				return *value1 == *value2;
			}
			case  OpcUaBuildInType_OpcUaQualifiedName:
			{
				OpcUaVariantSPtr opcUaVariantSPtr1 = boost::get<OpcUaVariantSPtr>(variantValue_);
				OpcUaVariantSPtr opcUaVariantSPtr2 = variantValue.variant<OpcUaVariantSPtr>();
				OpcUaQualifiedName::SPtr value1 = boost::static_pointer_cast<OpcUaQualifiedName>(opcUaVariantSPtr1.objectSPtr_);
				OpcUaQualifiedName::SPtr value2 = boost::static_pointer_cast<OpcUaQualifiedName>(opcUaVariantSPtr2.objectSPtr_);
				return *value1 == *value2;
			}
			case  OpcUaBuildInType_OpcUaLocalizedText:
			{
				OpcUaVariantSPtr opcUaVariantSPtr1 = boost::get<OpcUaVariantSPtr>(variantValue_);
				OpcUaVariantSPtr opcUaVariantSPtr2 = variantValue.variant<OpcUaVariantSPtr>();
				OpcUaLocalizedText::SPtr value1 = boost::static_pointer_cast<OpcUaLocalizedText>(opcUaVariantSPtr1.objectSPtr_);
				OpcUaLocalizedText::SPtr value2 = boost::static_pointer_cast<OpcUaLocalizedText>(opcUaVariantSPtr2.objectSPtr_);
				return *value1 == *value2;
			}
			case  OpcUaBuildInType_OpcUaExtensionObject:
			{
				OpcUaVariantSPtr opcUaVariantSPtr1 = boost::get<OpcUaVariantSPtr>(variantValue_);
				OpcUaVariantSPtr opcUaVariantSPtr2 = variantValue.variant<OpcUaVariantSPtr>();
				OpcUaExtensionObject::SPtr value1 = boost::static_pointer_cast<OpcUaExtensionObject>(opcUaVariantSPtr1.objectSPtr_);
				OpcUaExtensionObject::SPtr value2 = boost::static_pointer_cast<OpcUaExtensionObject>(opcUaVariantSPtr2.objectSPtr_);
				return *value1 == *value2;
			}
		}
		return false;
	}

	bool
	OpcUaVariantValue::fromString(const std::string& string)
	{
		// get type and value
		size_t pos = string.find(":");
		if (pos == std::string::npos) return false;
		std::string typeString = string.substr(0, pos);
		std::string valueString = string.substr(pos+1,string.length()-pos-1);

		// get build in type
		OpcUaBuildInType type = OpcUaBuildInTypeMap::string2BuildInType(typeString);

		// create build in type
		return fromString(type, valueString);
	}

	bool
	OpcUaVariantValue::fromString(OpcUaBuildInType type, const std::string& string)
	{
		switch (type)
		{
			case  OpcUaBuildInType_OpcUaBoolean:
			{
				std::string stringValue = string;
				boost::to_upper(stringValue);
				OpcUaBoolean value;
				if (stringValue == "TRUE") value = true;
				else value = false;
			    variant(value);
				break;
			}
			case  OpcUaBuildInType_OpcUaSByte:
			{
				OpcUaSByte value;
				try {
					value = (OpcUaSByte)boost::lexical_cast<OpcUaInt16>(string);
				} catch(boost::bad_lexical_cast& e) {
					Log(Error, "bad_lexical_cast")
						.parameter("Value", string)
						.parameter("What", e.what());
					return false;
				}
				variant(value);
				break;
			}
			case  OpcUaBuildInType_OpcUaByte:
			{
				OpcUaByte value;
				try {
					value = (OpcUaByte)boost::lexical_cast<OpcUaUInt16>(string);
				} catch(boost::bad_lexical_cast& e) {
					Log(Error, "bad_lexical_cast")
						.parameter("Value", string)
						.parameter("What", e.what());
					return false;
				}
				variant(value);
				break;
			}
			case  OpcUaBuildInType_OpcUaInt16:
			{
				OpcUaInt16 value;
				try {
					value = boost::lexical_cast<OpcUaInt16>(string);
				} catch(boost::bad_lexical_cast& e) {
					Log(Error, "bad_lexical_cast")
						.parameter("Value", string)
						.parameter("What", e.what());
					return false;
				}
				variant(value);
				break;
			}
			case  OpcUaBuildInType_OpcUaUInt16:
			{
				OpcUaUInt16 value;
				try {
					value = boost::lexical_cast<OpcUaUInt16>(string);
				} catch(boost::bad_lexical_cast& e) {
					Log(Error, "bad_lexical_cast")
						.parameter("Value", string)
						.parameter("What", e.what());
					return false;
				}
				variant(value);
				break;
			}
			case  OpcUaBuildInType_OpcUaInt32:
			{
				OpcUaInt32 value;
				try {
					value = boost::lexical_cast<OpcUaInt32>(string);
				} catch(boost::bad_lexical_cast& e) {
					Log(Error, "bad_lexical_cast")
						.parameter("Value", string)
						.parameter("What", e.what());
					return false;
				}
				variant(value);
				break;
			}
			case  OpcUaBuildInType_OpcUaUInt32:
			{
				OpcUaUInt32 value;
				try {
					value = boost::lexical_cast<OpcUaUInt32>(string);
				} catch(boost::bad_lexical_cast& e) {
					Log(Error, "bad_lexical_cast")
						.parameter("Value", string)
						.parameter("What", e.what());
					return false;
				}
				variant(value);
				break;
			}
			case  OpcUaBuildInType_OpcUaInt64:
			{
				OpcUaInt64 value;
				try {
					value = boost::lexical_cast<OpcUaInt64>(string);
				} catch(boost::bad_lexical_cast& e) {
					Log(Error, "bad_lexical_cast")
						.parameter("Value", string)
						.parameter("What", e.what());
					return false;
				}
				variant(value);
				break;
			}
			case  OpcUaBuildInType_OpcUaUInt64:
			{
				OpcUaUInt64 value;
				try {
					value = boost::lexical_cast<OpcUaUInt64>(string);
				} catch(boost::bad_lexical_cast& e) {
					Log(Error, "bad_lexical_cast")
						.parameter("Value", string)
						.parameter("What", e.what());
					return false;
				}
				variant(value);
				break;
			}
			case  OpcUaBuildInType_OpcUaFloat:
			{
				OpcUaFloat value;
				try {
					value = boost::lexical_cast<OpcUaFloat>(string);
				} catch(boost::bad_lexical_cast& e) {
					Log(Error, "bad_lexical_cast")
						.parameter("Value", string)
						.parameter("What", e.what());
					return false;
				}
				variant(value);
				break;
			}
			case  OpcUaBuildInType_OpcUaDouble:
			{
				OpcUaDouble value;
				try {
					value = boost::lexical_cast<OpcUaDouble>(string);
				} catch(boost::bad_lexical_cast& e) {
					Log(Error, "bad_lexical_cast")
						.parameter("Value", string)
						.parameter("What", e.what());
					return false;
				}
				variant(value);
				break;
			}
			case  OpcUaBuildInType_OpcUaDateTime:
			{
				OpcUaDateTime value;
				if (!value.fromISOString(string)) {
					Log(Error, "invalid time value")
						.parameter("Value", string);
					return false;
				}
				variant(value);
				break;
			}
			case  OpcUaBuildInType_OpcUaStatusCode:
			{
				OpcUaStatusCode value = OpcUaStatusCodeMap::statusCode(string);
				if (value == BadStatusCodeUnknown) {
					Log(Error, "invalid status code value")
						.parameter("Value", string);
					return false;
				}
				variant(value);
				break;
			}
			case  OpcUaBuildInType_OpcUaGuid:
			{
				OpcUaGuid::SPtr value = constructSPtr<OpcUaGuid>();
				if (!value->value(string)) {
					Log(Error, "invalid guid value")
						.parameter("Value", string);
					return false;
				}
				variant(value);
				break;
			}
			case  OpcUaBuildInType_OpcUaByteString:
			{
				OpcUaByteString::SPtr value = constructSPtr<OpcUaByteString>();
				if (!value->fromHexString(string)) {
					Log(Error, "invalid hex string value")
						.parameter("Value", string);
					return false;
				}
				variant(value);
				break;
			}
			case  OpcUaBuildInType_OpcUaString:
			{
				OpcUaString::SPtr value = constructSPtr<OpcUaString>();
				value->value(string);
				variant(value);
				break;
			}
			case  OpcUaBuildInType_OpcUaXmlElement:
			{
				// FIXME: actualy not used
				return false;
				break;
			}

			case  OpcUaBuildInType_OpcUaNodeId:
			{
				OpcUaNodeId::SPtr value = constructSPtr<OpcUaNodeId>();
				if (!value->fromString(string)) {
					Log(Error, "invalid node id value")
						.parameter("Value", string);
					return false;
				}
				variant(value);
				break;
			}
			case OpcUaBuildInType_OpcUaExpandedNodeId:
			{
				return false;
				break;
			}
			case  OpcUaBuildInType_OpcUaQualifiedName:
			{
				OpcUaQualifiedName::SPtr value = constructSPtr<OpcUaQualifiedName>();
				if (!value->fromString(string)) {
					Log(Error, "invalid qualified name value")
						.parameter("Value", string);
					return false;
				}
				variant(value);
				break;
			}
			case  OpcUaBuildInType_OpcUaLocalizedText:
			{
				OpcUaLocalizedText::SPtr value = constructSPtr<OpcUaLocalizedText>();
				if (!value->fromString(string)) {
					Log(Error, "invalid localized text value")
						.parameter("Value", string);
					return false;
				}
				variant(value);
				break;
			}
			case  OpcUaBuildInType_OpcUaExtensionObject:
			{
				return false;
				break;
			}
			default:
			{
				Log(Error, "unknown data type")
					.parameter("Value", string);
				return false;
				return false;
			}
		}

		return true;
	}

	void 
	OpcUaVariantValue::copyTo(OpcUaVariantValue& variantValue)
	{
		switch (variantType()) 
		{
			case  OpcUaBuildInType_OpcUaBoolean:
			{
				OpcUaBoolean value;
				value = boost::get<OpcUaBoolean>(variantValue_);
				variantValue.variant(value);
				break;
			}
			case  OpcUaBuildInType_OpcUaSByte:
			{
				OpcUaSByte value;
				value = boost::get<OpcUaSByte>(variantValue_);
				variantValue.variant(value);
				break;
			}
			case  OpcUaBuildInType_OpcUaByte:
			{
				OpcUaByte value;
				value = boost::get<OpcUaByte>(variantValue_);
				variantValue.variant(value);
				break;
			}
			case  OpcUaBuildInType_OpcUaInt16:
			{
				OpcUaInt16 value;
				value = boost::get<OpcUaInt16>(variantValue_);
				variantValue.variant(value);
				break;
			}
			case  OpcUaBuildInType_OpcUaUInt16:
			{
				OpcUaUInt16 value;
				value = boost::get<OpcUaUInt16>(variantValue_);
				variantValue.variant(value);
				break;
			}
			case  OpcUaBuildInType_OpcUaInt32:
			{
				OpcUaInt32 value;
				value = boost::get<OpcUaInt32>(variantValue_);
				variantValue.variant(value);
				break;
			}
			case  OpcUaBuildInType_OpcUaUInt32:
			{
				OpcUaUInt32 value;
				value = boost::get<OpcUaUInt32>(variantValue_);
				variantValue.variant(value);
				break;
			}
			case  OpcUaBuildInType_OpcUaInt64:
			{
				OpcUaInt64 value;
				value = boost::get<OpcUaInt64>(variantValue_);
				variantValue.variant(value);
				break;
			}
			case  OpcUaBuildInType_OpcUaUInt64:
			{
				OpcUaUInt64 value;
				value = boost::get<OpcUaUInt64>(variantValue_);
				variantValue.variant(value);
				break;
			}
			case  OpcUaBuildInType_OpcUaFloat:
			{
				OpcUaFloat value;
				value = boost::get<OpcUaFloat>(variantValue_);
				variantValue.variant(value);
				break;
			}
			case  OpcUaBuildInType_OpcUaDouble:
			{
				OpcUaDouble value;
				value = boost::get<OpcUaDouble>(variantValue_);
				variantValue.variant(value);
				break;
			}
			case  OpcUaBuildInType_OpcUaDateTime:
			{
				OpcUaDateTime value;
				boost::get<OpcUaDateTime>(variantValue_).copyTo(value);
				variantValue.variant(value);
				break;
			}
			case  OpcUaBuildInType_OpcUaStatusCode:
			{
				OpcUaInt32 value; 
				value = boost::get<OpcUaStatusCode>(variantValue_);
				variantValue.variant(value);
				break;
			}
			case  OpcUaBuildInType_OpcUaGuid:
			{
				OpcUaGuid::SPtr value = constructSPtr<OpcUaGuid>();
				OpcUaVariantSPtr opcUaVariantSPtr =  boost::get<OpcUaVariantSPtr>(variantValue_);
				OpcUaGuid::SPtr opcUaGuidSPtr = boost::static_pointer_cast<OpcUaGuid>(opcUaVariantSPtr.objectSPtr_);
				opcUaGuidSPtr->copyTo(*value);
				variantValue.variant(value);
				break;
			}
			case  OpcUaBuildInType_OpcUaByteString:
			{
				OpcUaByteString::SPtr value = constructSPtr<OpcUaByteString>();
				OpcUaVariantSPtr opcUaVariantSPtr =  boost::get<OpcUaVariantSPtr>(variantValue_);
				OpcUaByteString::SPtr opcUaByteStringSPtr = boost::static_pointer_cast<OpcUaByteString>(opcUaVariantSPtr.objectSPtr_);
				opcUaByteStringSPtr->copyTo(*value);
				variantValue.variant(value);
				break;
			}
			case  OpcUaBuildInType_OpcUaString:
			{
				OpcUaString::SPtr value = constructSPtr<OpcUaString>();
				OpcUaVariantSPtr opcUaVariantSPtr =  boost::get<OpcUaVariantSPtr>(variantValue_);
				OpcUaString::SPtr opcUaStringSPtr = boost::static_pointer_cast<OpcUaString>(opcUaVariantSPtr.objectSPtr_);
				opcUaStringSPtr->copyTo(*value);
				variantValue.variant(value);
				break;
			}
			case  OpcUaBuildInType_OpcUaXmlElement:
			{
				// FIXME: actualy not used
				break;
			}
			case  OpcUaBuildInType_OpcUaNodeId:
			{
				OpcUaNodeId::SPtr value = constructSPtr<OpcUaNodeId>();
				OpcUaVariantSPtr opcUaVariantSPtr =  boost::get<OpcUaVariantSPtr>(variantValue_);
				OpcUaNodeId::SPtr opcUaNodeIdSPtr = boost::static_pointer_cast<OpcUaNodeId>(opcUaVariantSPtr.objectSPtr_);
				opcUaNodeIdSPtr->copyTo(*value);
				variantValue.variant(value);
				break;
			}
			case  OpcUaBuildInType_OpcUaExpandedNodeId:
			{
				OpcUaExpandedNodeId::SPtr value = constructSPtr<OpcUaExpandedNodeId>();
				OpcUaVariantSPtr opcUaVariantSPtr =  boost::get<OpcUaVariantSPtr>(variantValue_);
				OpcUaExpandedNodeId::SPtr opcUaExpandedNodeIdSPtr = boost::static_pointer_cast<OpcUaExpandedNodeId>(opcUaVariantSPtr.objectSPtr_);
				opcUaExpandedNodeIdSPtr->copyTo(*value);
				variantValue.variant(value);
				break;
			}
			case  OpcUaBuildInType_OpcUaQualifiedName:
			{
				OpcUaQualifiedName::SPtr value = constructSPtr<OpcUaQualifiedName>();
				OpcUaVariantSPtr opcUaVariantSPtr =  boost::get<OpcUaVariantSPtr>(variantValue_);
				OpcUaQualifiedName::SPtr opcUaQualifiedNameSPtr = boost::static_pointer_cast<OpcUaQualifiedName>(opcUaVariantSPtr.objectSPtr_);
				opcUaQualifiedNameSPtr->copyTo(*value);
				variantValue.variant(value);
				break;
			}
			case  OpcUaBuildInType_OpcUaLocalizedText:
			{
				OpcUaLocalizedText::SPtr value = constructSPtr<OpcUaLocalizedText>();
				OpcUaVariantSPtr opcUaVariantSPtr = boost::get<OpcUaVariantSPtr>(variantValue_);
				OpcUaLocalizedText::SPtr opcUaLocalizedTextSPtr = boost::static_pointer_cast<OpcUaLocalizedText>(opcUaVariantSPtr.objectSPtr_);
				opcUaLocalizedTextSPtr->copyTo(*value);
				variantValue.variant(value);
				break;
			}
			case  OpcUaBuildInType_OpcUaExtensionObject:
			{
				OpcUaExtensionObject::SPtr value = constructSPtr<OpcUaExtensionObject>();
				OpcUaVariantSPtr opcUaVariantSPtr =  boost::get<OpcUaVariantSPtr>(variantValue_);
				OpcUaExtensionObject::SPtr opcUaExtensionObjectSPtr = boost::static_pointer_cast<OpcUaExtensionObject>(opcUaVariantSPtr.objectSPtr_);
				opcUaExtensionObjectSPtr->copyTo(*value);
				variantValue.variant(value);
				break;
			}
		}
	}

	void 
	OpcUaVariantValue::out(std::ostream& os) const
	{
		switch (variantType()) 
		{
			case  OpcUaBuildInType_OpcUaBoolean:
			{
				os << boost::get<OpcUaBoolean>(variantValue_);
				break;
			}
			case  OpcUaBuildInType_OpcUaSByte:
			{
				os << (int64_t)boost::get<OpcUaSByte>(variantValue_);
				break;
			}
			case  OpcUaBuildInType_OpcUaByte:
			{
				os << (int64_t)boost::get<OpcUaByte>(variantValue_);
				break;
			}
			case  OpcUaBuildInType_OpcUaInt16:
			{
				os << (int64_t)boost::get<OpcUaInt16>(variantValue_);
				break;
			}
			case  OpcUaBuildInType_OpcUaUInt16:
			{
				os << (int64_t)boost::get<OpcUaUInt16>(variantValue_);
				break;
			}
			case  OpcUaBuildInType_OpcUaInt32:
			{
				os << boost::get<OpcUaInt32>(variantValue_);
				break;
			}
			case  OpcUaBuildInType_OpcUaUInt32:
			{
				os << boost::get<OpcUaUInt32>(variantValue_);
				break;
			}
			case  OpcUaBuildInType_OpcUaInt64:
			{
				os << boost::get<OpcUaInt64>(variantValue_);
				break;
			}
			case  OpcUaBuildInType_OpcUaUInt64:
			{
				os << boost::get<OpcUaUInt64>(variantValue_);
				break;
			}
			case  OpcUaBuildInType_OpcUaFloat:
			{
				os << boost::get<OpcUaFloat>(variantValue_);
				break;
			}
			case  OpcUaBuildInType_OpcUaDouble:
			{
				os << boost::get<OpcUaDouble>(variantValue_);
				break;
			}
			case  OpcUaBuildInType_OpcUaDateTime:
			{
				os << boost::get<OpcUaDateTime>(variantValue_);
				break;
			}
			case  OpcUaBuildInType_OpcUaStatusCode:
			{
				os << OpcUaStatusCodeMap::shortString(boost::get<OpcUaStatusCode>(variantValue_));
				break;
			}
			case  OpcUaBuildInType_OpcUaGuid:
			{
				OpcUaVariantSPtr opcUaVariantSPtr =  boost::get<OpcUaVariantSPtr>(variantValue_);
				OpcUaGuid::SPtr opcUaGuidSPtr = boost::static_pointer_cast<OpcUaGuid>(opcUaVariantSPtr.objectSPtr_);
				os << *opcUaGuidSPtr;
				break;
			}
			case  OpcUaBuildInType_OpcUaByteString:
			{
				OpcUaVariantSPtr opcUaVariantSPtr =  boost::get<OpcUaVariantSPtr>(variantValue_);
				OpcUaByteString::SPtr opcUaByteStringSPtr = boost::static_pointer_cast<OpcUaByteString>(opcUaVariantSPtr.objectSPtr_);
				os << *opcUaByteStringSPtr;
				break;
			}
			case  OpcUaBuildInType_OpcUaString:
			{
				OpcUaVariantSPtr opcUaVariantSPtr =  boost::get<OpcUaVariantSPtr>(variantValue_);
				OpcUaString::SPtr opcUaStringSPtr = boost::static_pointer_cast<OpcUaString>(opcUaVariantSPtr.objectSPtr_);
				os << *opcUaStringSPtr;
				break;
			}
			case  OpcUaBuildInType_OpcUaXmlElement:
			{
				// FIXME: actualy not used
				break;
			}
			case  OpcUaBuildInType_OpcUaNodeId:
			{
				OpcUaVariantSPtr opcUaVariantSPtr =  boost::get<OpcUaVariantSPtr>(variantValue_);
				OpcUaNodeId::SPtr opcUaNodeIdSPtr = boost::static_pointer_cast<OpcUaNodeId>(opcUaVariantSPtr.objectSPtr_);
				os << *opcUaNodeIdSPtr;
				break;
			}
			case  OpcUaBuildInType_OpcUaExpandedNodeId:
			{
				OpcUaVariantSPtr opcUaVariantSPtr =  boost::get<OpcUaVariantSPtr>(variantValue_);
				OpcUaExpandedNodeId::SPtr opcUaExpandedNodeIdSPtr = boost::static_pointer_cast<OpcUaExpandedNodeId>(opcUaVariantSPtr.objectSPtr_);
				os << *opcUaExpandedNodeIdSPtr;
				break;
			}
			case  OpcUaBuildInType_OpcUaQualifiedName:
			{
				OpcUaVariantSPtr opcUaVariantSPtr =  boost::get<OpcUaVariantSPtr>(variantValue_);
				OpcUaQualifiedName::SPtr opcUaQualifiedNameSPtr = boost::static_pointer_cast<OpcUaQualifiedName>(opcUaVariantSPtr.objectSPtr_);
				os << *opcUaQualifiedNameSPtr;
				break;
			}
			case  OpcUaBuildInType_OpcUaLocalizedText:
			{
				OpcUaVariantSPtr opcUaVariantSPtr = boost::get<OpcUaVariantSPtr>(variantValue_);
				OpcUaLocalizedText::SPtr opcUaLocalizedTextSPtr = boost::static_pointer_cast<OpcUaLocalizedText>(opcUaVariantSPtr.objectSPtr_);
				os << *opcUaLocalizedTextSPtr;
				break;
			}
			case  OpcUaBuildInType_OpcUaExtensionObject:
			{
				OpcUaVariantSPtr opcUaVariantSPtr =  boost::get<OpcUaVariantSPtr>(variantValue_);
				OpcUaExtensionObject::SPtr opcUaExtensionObjectSPtr = boost::static_pointer_cast<OpcUaExtensionObject>(opcUaVariantSPtr.objectSPtr_);
				os << *opcUaExtensionObjectSPtr;
				break;
			}
		}
	}

	void 
	OpcUaVariantValue::opcUaBinaryEncode(std::ostream& os, OpcUaBuildInType variantType) const
	{
		switch (variantType) 
		{
			case  OpcUaBuildInType_OpcUaBoolean:
			{
				OpcUaNumber::opcUaBinaryEncode(os, boost::get<OpcUaBoolean>(variantValue_));
				break;
			}
			case  OpcUaBuildInType_OpcUaSByte:
			{
				OpcUaNumber::opcUaBinaryEncode(os, boost::get<OpcUaSByte>(variantValue_));
				break;
			}
			case  OpcUaBuildInType_OpcUaByte:
			{
				OpcUaNumber::opcUaBinaryEncode(os, boost::get<OpcUaByte>(variantValue_));
				break;
			}
			case  OpcUaBuildInType_OpcUaInt16:
			{
				OpcUaNumber::opcUaBinaryEncode(os, boost::get<OpcUaInt16>(variantValue_));
				break;
			}
			case  OpcUaBuildInType_OpcUaUInt16:
			{
				OpcUaNumber::opcUaBinaryEncode(os, boost::get<OpcUaUInt16>(variantValue_));
				break;
			}
			case  OpcUaBuildInType_OpcUaInt32:
			{
				OpcUaNumber::opcUaBinaryEncode(os, boost::get<OpcUaInt32>(variantValue_));
				break;
			}
			case  OpcUaBuildInType_OpcUaUInt32:
			{
				OpcUaNumber::opcUaBinaryEncode(os, boost::get<OpcUaUInt32>(variantValue_));
				break;
			}
			case  OpcUaBuildInType_OpcUaInt64:
			{
				OpcUaNumber::opcUaBinaryEncode(os, boost::get<OpcUaInt64>(variantValue_));
				break;
			}
			case  OpcUaBuildInType_OpcUaUInt64:
			{
				OpcUaNumber::opcUaBinaryEncode(os, boost::get<OpcUaUInt64>(variantValue_));
				break;
			}
			case  OpcUaBuildInType_OpcUaFloat:
			{
				OpcUaNumber::opcUaBinaryEncode(os, boost::get<OpcUaFloat>(variantValue_));
				break;
			}
			case  OpcUaBuildInType_OpcUaDouble:
			{
				OpcUaNumber::opcUaBinaryEncode(os, boost::get<OpcUaDouble>(variantValue_));
				break;
			}
			case  OpcUaBuildInType_OpcUaDateTime:
			{
				boost::get<OpcUaDateTime>(variantValue_).opcUaBinaryEncode(os);
				break;
			}
			case  OpcUaBuildInType_OpcUaStatusCode:
			{
				OpcUaInt32 value = (OpcUaInt32)boost::get<OpcUaStatusCode>(variantValue_);
				OpcUaNumber::opcUaBinaryEncode(os, value);
				break;
			}
			case  OpcUaBuildInType_OpcUaGuid:
			{
				OpcUaVariantSPtr opcUaVariantSPtr =  boost::get<OpcUaVariantSPtr>(variantValue_);
				OpcUaGuid::SPtr opcUaGuidSPtr = boost::static_pointer_cast<OpcUaGuid>(opcUaVariantSPtr.objectSPtr_);
				opcUaGuidSPtr->opcUaBinaryEncode(os);
				break;
			}
			case  OpcUaBuildInType_OpcUaByteString:
			{
				OpcUaVariantSPtr opcUaVariantSPtr =  boost::get<OpcUaVariantSPtr>(variantValue_);
				OpcUaByteString::SPtr opcUaByteStringSPtr = boost::static_pointer_cast<OpcUaByteString>(opcUaVariantSPtr.objectSPtr_);
				opcUaByteStringSPtr->opcUaBinaryEncode(os);
				break;
			}
			case  OpcUaBuildInType_OpcUaString:
			{
				OpcUaVariantSPtr opcUaVariantSPtr =  boost::get<OpcUaVariantSPtr>(variantValue_);
				OpcUaString::SPtr opcUaStringSPtr = boost::static_pointer_cast<OpcUaString>(opcUaVariantSPtr.objectSPtr_);
				opcUaStringSPtr->opcUaBinaryEncode(os);
				break;
			}
			case  OpcUaBuildInType_OpcUaXmlElement:
			{
				OpcUaVariantSPtr opcUaVariantSPtr =  boost::get<OpcUaVariantSPtr>(variantValue_);
				OpcUaXmlElement::SPtr opcUaXmlElementSPtr = boost::static_pointer_cast<OpcUaXmlElement>(opcUaVariantSPtr.objectSPtr_);
				opcUaXmlElementSPtr->opcUaBinaryEncode(os);
				break;
			}
			case  OpcUaBuildInType_OpcUaNodeId:
			{
				OpcUaVariantSPtr opcUaVariantSPtr =  boost::get<OpcUaVariantSPtr>(variantValue_);
				OpcUaNodeId::SPtr opcUaNodeIdSPtr = boost::static_pointer_cast<OpcUaNodeId>(opcUaVariantSPtr.objectSPtr_);
				opcUaNodeIdSPtr->opcUaBinaryEncode(os);
				break;
			}
			case  OpcUaBuildInType_OpcUaExpandedNodeId:
			{
				OpcUaVariantSPtr opcUaVariantSPtr =  boost::get<OpcUaVariantSPtr>(variantValue_);
				OpcUaExpandedNodeId::SPtr opcUaExpandedNodeIdSPtr = boost::static_pointer_cast<OpcUaExpandedNodeId>(opcUaVariantSPtr.objectSPtr_);
				opcUaExpandedNodeIdSPtr->opcUaBinaryEncode(os);
				break;
			}
			case  OpcUaBuildInType_OpcUaQualifiedName:
			{
				OpcUaVariantSPtr opcUaVariantSPtr =  boost::get<OpcUaVariantSPtr>(variantValue_);
				OpcUaQualifiedName::SPtr opcUaQualifiedNameSPtr = boost::static_pointer_cast<OpcUaQualifiedName>(opcUaVariantSPtr.objectSPtr_);
				opcUaQualifiedNameSPtr->opcUaBinaryEncode(os);
				break;
			}
			case  OpcUaBuildInType_OpcUaLocalizedText:
			{
				OpcUaVariantSPtr opcUaVariantSPtr =  boost::get<OpcUaVariantSPtr>(variantValue_);
				OpcUaLocalizedText::SPtr opcUaLocalizedTextSPtr = boost::static_pointer_cast<OpcUaLocalizedText>(opcUaVariantSPtr.objectSPtr_);
				opcUaLocalizedTextSPtr->opcUaBinaryEncode(os);
				break;
			}
			case  OpcUaBuildInType_OpcUaExtensionObject:
			{
				OpcUaVariantSPtr opcUaVariantSPtr =  boost::get<OpcUaVariantSPtr>(variantValue_);
				OpcUaExtensionObject::SPtr opcUaExtensionObjectSPtr = boost::static_pointer_cast<OpcUaExtensionObject>(opcUaVariantSPtr.objectSPtr_);
				opcUaExtensionObjectSPtr->opcUaBinaryEncode(os);
				break;
			}
		}
	}
		
	void 
	OpcUaVariantValue::opcUaBinaryDecode(std::istream& is, OpcUaBuildInType variantType)
	{
		OpcUaVariantValueType opcUaVariantValue;
		switch (variantType) 
		{
			case  OpcUaBuildInType_OpcUaBoolean:
			{
				OpcUaBoolean opcUaBoolean;
				OpcUaNumber::opcUaBinaryDecode(is, opcUaBoolean);
				opcUaVariantValue = opcUaBoolean;
				variantValue_ = opcUaVariantValue;
				break;
			}
			case  OpcUaBuildInType_OpcUaSByte:
			{
				OpcUaSByte opcUaSByte;
				OpcUaNumber::opcUaBinaryDecode(is, opcUaSByte);
				opcUaVariantValue = opcUaSByte;
				variantValue_ = opcUaVariantValue;
				break;
			}
			case  OpcUaBuildInType_OpcUaByte:
			{
				OpcUaByte opcUaByte;
				OpcUaNumber::opcUaBinaryDecode(is, opcUaByte);
				opcUaVariantValue = opcUaByte;
				variantValue_ = opcUaVariantValue;
				break;
			}
			case  OpcUaBuildInType_OpcUaInt16:
			{
				OpcUaInt16 opcUaInt16;
				OpcUaNumber::opcUaBinaryDecode(is, opcUaInt16);
				opcUaVariantValue = opcUaInt16;
				variantValue_ = opcUaVariantValue;
				break;
			}
			case  OpcUaBuildInType_OpcUaUInt16:
			{
				OpcUaUInt16 opcUaUInt16;
				OpcUaNumber::opcUaBinaryDecode(is, opcUaUInt16);
				opcUaVariantValue = opcUaUInt16;
				variantValue_ = opcUaVariantValue;
				break;
			}
			case  OpcUaBuildInType_OpcUaInt32:
			{
				OpcUaInt32 opcUaInt32;
				OpcUaNumber::opcUaBinaryDecode(is, opcUaInt32);
				opcUaVariantValue = opcUaInt32;
				variantValue_ = opcUaVariantValue;
				break;
			}
			case  OpcUaBuildInType_OpcUaUInt32:
			{
				OpcUaUInt32 opcUaUInt32;
				OpcUaNumber::opcUaBinaryDecode(is, opcUaUInt32);
				opcUaVariantValue = opcUaUInt32;
				variantValue_ = opcUaVariantValue;
				break;
			}
			case  OpcUaBuildInType_OpcUaInt64:
			{
				OpcUaInt64 opcUaInt64;
				OpcUaNumber::opcUaBinaryDecode(is, opcUaInt64);
				opcUaVariantValue = opcUaInt64;
				variantValue_ = opcUaVariantValue;
				break;
			}
			case  OpcUaBuildInType_OpcUaUInt64:
			{
				OpcUaUInt64 opcUaUInt64;
				OpcUaNumber::opcUaBinaryDecode(is, opcUaUInt64);
				opcUaVariantValue = opcUaUInt64;
				variantValue_ = opcUaVariantValue;
				break;
			}
			case  OpcUaBuildInType_OpcUaFloat:
			{
				OpcUaFloat opcUaFloat;
				OpcUaNumber::opcUaBinaryDecode(is, opcUaFloat);
				opcUaVariantValue = opcUaFloat;
				variantValue_ = opcUaVariantValue;
				break;
			}
			case  OpcUaBuildInType_OpcUaDouble:
			{
				OpcUaDouble opcUaDouble;
				OpcUaNumber::opcUaBinaryDecode(is, opcUaDouble);
				opcUaVariantValue = opcUaDouble;
				variantValue_ = opcUaVariantValue;
				break;
			}
			case  OpcUaBuildInType_OpcUaDateTime:
			{
				OpcUaDateTime opcUaDateTime;
				opcUaDateTime.opcUaBinaryDecode(is);
				opcUaVariantValue = opcUaDateTime;
				variantValue_ = opcUaVariantValue;
				break;
			}
			case  OpcUaBuildInType_OpcUaStatusCode:
			{
				OpcUaInt32 opcUaStatusCode;
				OpcUaNumber::opcUaBinaryDecode(is, opcUaStatusCode);
				opcUaVariantValue = (OpcUaStatusCode)opcUaStatusCode;
				variantValue_ = opcUaVariantValue;
				break;
			}
			case  OpcUaBuildInType_OpcUaGuid:
			{
				OpcUaVariantSPtr val;

				OpcUaGuid::SPtr opcUaGuidSPtr = constructSPtr<OpcUaGuid>();
				opcUaGuidSPtr->opcUaBinaryDecode(is);
				val.objectSPtr_ = opcUaGuidSPtr;
				val.opcUaBuildInType_ = OpcUaBuildInType_OpcUaGuid;
				variantValue_ = val;
				break;
			}
			case  OpcUaBuildInType_OpcUaByteString:
			{
				OpcUaVariantSPtr val;

				OpcUaByteString::SPtr opcUaByteStringSPtr = constructSPtr<OpcUaByteString>();
				opcUaByteStringSPtr->opcUaBinaryDecode(is);
				val.objectSPtr_ = opcUaByteStringSPtr;
				val.opcUaBuildInType_ = OpcUaBuildInType_OpcUaByteString;
				variantValue_ = val;
				break;
			}
			case  OpcUaBuildInType_OpcUaString:
			{
				OpcUaVariantSPtr val;

				OpcUaString::SPtr opcUaStringSPtr = constructSPtr<OpcUaString>();
				opcUaStringSPtr->opcUaBinaryDecode(is);
				val.objectSPtr_ = opcUaStringSPtr;
				val.opcUaBuildInType_ = OpcUaBuildInType_OpcUaString;
				variantValue_ = val;
				break;
			}
			case  OpcUaBuildInType_OpcUaXmlElement:
			{
				OpcUaVariantSPtr val;

				OpcUaXmlElement::SPtr opcUaXmlElementSPtr = constructSPtr<OpcUaXmlElement>();
				opcUaXmlElementSPtr->opcUaBinaryDecode(is);
				val.objectSPtr_ = opcUaXmlElementSPtr;
				val.opcUaBuildInType_ = OpcUaBuildInType_OpcUaXmlElement;
				variantValue_ = val;
				break;
			}
			case  OpcUaBuildInType_OpcUaNodeId:
			{
				OpcUaVariantSPtr val;

				OpcUaNodeId::SPtr opcUaNodeIdSPtr = constructSPtr<OpcUaNodeId>();
				opcUaNodeIdSPtr->opcUaBinaryDecode(is);
				val.objectSPtr_ = opcUaNodeIdSPtr;
				val.opcUaBuildInType_ = OpcUaBuildInType_OpcUaNodeId;
				variantValue_ = val;
				break;
			}
			case  OpcUaBuildInType_OpcUaExpandedNodeId:
			{
				OpcUaVariantSPtr val;

				OpcUaExpandedNodeId::SPtr opcUaExpandedNodeIdSPtr = constructSPtr<OpcUaExpandedNodeId>();
				opcUaExpandedNodeIdSPtr->opcUaBinaryDecode(is);
				val.objectSPtr_ = opcUaExpandedNodeIdSPtr;
				val.opcUaBuildInType_ = OpcUaBuildInType_OpcUaExpandedNodeId;
				variantValue_ = val;
				break;
			}
			case  OpcUaBuildInType_OpcUaQualifiedName:
			{
				OpcUaVariantSPtr val;

				OpcUaQualifiedName::SPtr opcUaQualifiedNameSPtr = constructSPtr<OpcUaQualifiedName>();
				opcUaQualifiedNameSPtr->opcUaBinaryDecode(is);
				val.objectSPtr_ = opcUaQualifiedNameSPtr;
				val.opcUaBuildInType_ = OpcUaBuildInType_OpcUaQualifiedName;
				variantValue_ = val;
				break;
			}
			case  OpcUaBuildInType_OpcUaLocalizedText:
			{
				OpcUaVariantSPtr val;

				OpcUaLocalizedText::SPtr opcUaLocalizedTextSPtr = constructSPtr<OpcUaLocalizedText>();
				opcUaLocalizedTextSPtr->opcUaBinaryDecode(is);
				val.objectSPtr_ = opcUaLocalizedTextSPtr;
				val.opcUaBuildInType_ = OpcUaBuildInType_OpcUaLocalizedText;
				variantValue_ = val;
				break;
			}
			case  OpcUaBuildInType_OpcUaExtensionObject:
			{
				OpcUaVariantSPtr val;

				OpcUaExtensionObject::SPtr opcUaExtensionObjectSPtr = constructSPtr<OpcUaExtensionObject>();
				opcUaExtensionObjectSPtr->opcUaBinaryDecode(is);
				val.objectSPtr_ = opcUaExtensionObjectSPtr;
				val.opcUaBuildInType_ = OpcUaBuildInType_OpcUaExtensionObject;
				variantValue_ = val;
				break;
			}
		}
	}

	bool
	OpcUaVariantValue::encode(boost::property_tree::ptree& pt, OpcUaBuildInType opcUaBuildInType) const
	{
		switch (opcUaBuildInType)
		{
			case  OpcUaBuildInType_OpcUaBoolean:
			{
				if (!Json::encode(pt, boost::get<OpcUaBoolean>(variantValue_))) return false;
				break;
			}
			case  OpcUaBuildInType_OpcUaSByte:
			{
				if (!Json::encode(pt, boost::get<OpcUaSByte>(variantValue_))) return false;
				break;
			}
			case  OpcUaBuildInType_OpcUaByte:
			{
				if (!Json::encode(pt, boost::get<OpcUaByte>(variantValue_))) return false;
				break;
			}
			case  OpcUaBuildInType_OpcUaInt16:
			{
				if (!Json::encode(pt, boost::get<OpcUaInt16>(variantValue_))) return false;
				break;
			}
			case  OpcUaBuildInType_OpcUaUInt16:
			{
				if (!Json::encode(pt, boost::get<OpcUaUInt16>(variantValue_))) return false;
				break;
			}
			case  OpcUaBuildInType_OpcUaInt32:
			{
				if (!Json::encode(pt, boost::get<OpcUaInt32>(variantValue_))) return false;
				break;
			}
			case  OpcUaBuildInType_OpcUaUInt32:
			{
				if (!Json::encode(pt, boost::get<OpcUaUInt32>(variantValue_))) return false;
				break;
			}
			case  OpcUaBuildInType_OpcUaInt64:
			{
				if (!Json::encode(pt, boost::get<OpcUaInt64>(variantValue_))) return false;
				break;
			}
			case  OpcUaBuildInType_OpcUaUInt64:
			{
				if (!Json::encode(pt, boost::get<OpcUaUInt64>(variantValue_))) return false;
				break;
			}
			case  OpcUaBuildInType_OpcUaFloat:
			{
				if (!Json::encode(pt, boost::get<OpcUaFloat>(variantValue_))) return false;
				break;
			}
			case  OpcUaBuildInType_OpcUaDouble:
			{
				if (!Json::encode(pt, boost::get<OpcUaDouble>(variantValue_))) return false;
				break;
			}
			case  OpcUaBuildInType_OpcUaDateTime:
			{
				if (!boost::get<OpcUaDateTime>(variantValue_).encode(pt)) return false;
				break;
			}
			case  OpcUaBuildInType_OpcUaStatusCode:
			{
				OpcUaInt32 value = (OpcUaInt32)boost::get<OpcUaStatusCode>(variantValue_);
				if (!Json::encode(pt, value)) return false;
				break;
			}
			case  OpcUaBuildInType_OpcUaGuid:
			{
				OpcUaVariantSPtr opcUaVariantSPtr =  boost::get<OpcUaVariantSPtr>(variantValue_);
				OpcUaGuid::SPtr opcUaGuidSPtr = boost::static_pointer_cast<OpcUaGuid>(opcUaVariantSPtr.objectSPtr_);
				if (!opcUaGuidSPtr->encode(pt)) return false;
				break;
			}
			case  OpcUaBuildInType_OpcUaByteString:
			{
				OpcUaVariantSPtr opcUaVariantSPtr =  boost::get<OpcUaVariantSPtr>(variantValue_);
				OpcUaByteString::SPtr opcUaByteStringSPtr = boost::static_pointer_cast<OpcUaByteString>(opcUaVariantSPtr.objectSPtr_);
				if (!opcUaByteStringSPtr->encode(pt)) return false;
				break;
			}
			case  OpcUaBuildInType_OpcUaString:
			{
				OpcUaVariantSPtr opcUaVariantSPtr =  boost::get<OpcUaVariantSPtr>(variantValue_);
				OpcUaString::SPtr opcUaStringSPtr = boost::static_pointer_cast<OpcUaString>(opcUaVariantSPtr.objectSPtr_);
				if (!opcUaStringSPtr->encode(pt)) return false;
				break;
			}
			case  OpcUaBuildInType_OpcUaXmlElement:
			{
				OpcUaVariantSPtr opcUaVariantSPtr =  boost::get<OpcUaVariantSPtr>(variantValue_);
				OpcUaXmlElement::SPtr opcUaXmlElementSPtr = boost::static_pointer_cast<OpcUaXmlElement>(opcUaVariantSPtr.objectSPtr_);
				if (!opcUaXmlElementSPtr->encode(pt)) return false;
				break;
			}
			case  OpcUaBuildInType_OpcUaNodeId:
			{
				OpcUaVariantSPtr opcUaVariantSPtr =  boost::get<OpcUaVariantSPtr>(variantValue_);
				OpcUaNodeId::SPtr opcUaNodeIdSPtr = boost::static_pointer_cast<OpcUaNodeId>(opcUaVariantSPtr.objectSPtr_);
				if (!opcUaNodeIdSPtr->encode(pt)) return false;
				break;
			}
			case  OpcUaBuildInType_OpcUaExpandedNodeId:
			{
				OpcUaVariantSPtr opcUaVariantSPtr =  boost::get<OpcUaVariantSPtr>(variantValue_);
				OpcUaExpandedNodeId::SPtr opcUaExpandedNodeIdSPtr = boost::static_pointer_cast<OpcUaExpandedNodeId>(opcUaVariantSPtr.objectSPtr_);
				if (!opcUaExpandedNodeIdSPtr->encode(pt)) return false;
				break;
			}
			case  OpcUaBuildInType_OpcUaQualifiedName:
			{
				OpcUaVariantSPtr opcUaVariantSPtr =  boost::get<OpcUaVariantSPtr>(variantValue_);
				OpcUaQualifiedName::SPtr opcUaQualifiedNameSPtr = boost::static_pointer_cast<OpcUaQualifiedName>(opcUaVariantSPtr.objectSPtr_);
				if (!opcUaQualifiedNameSPtr->encode(pt)) return false;
				break;
			}
			case  OpcUaBuildInType_OpcUaLocalizedText:
			{
				OpcUaVariantSPtr opcUaVariantSPtr =  boost::get<OpcUaVariantSPtr>(variantValue_);
				OpcUaLocalizedText::SPtr opcUaLocalizedTextSPtr = boost::static_pointer_cast<OpcUaLocalizedText>(opcUaVariantSPtr.objectSPtr_);
				if (!opcUaLocalizedTextSPtr->encode(pt)) return false;
				break;
			}
			case  OpcUaBuildInType_OpcUaExtensionObject:
			{
				OpcUaVariantSPtr opcUaVariantSPtr =  boost::get<OpcUaVariantSPtr>(variantValue_);
				OpcUaExtensionObject::SPtr opcUaExtensionObjectSPtr = boost::static_pointer_cast<OpcUaExtensionObject>(opcUaVariantSPtr.objectSPtr_);
				if (!opcUaExtensionObjectSPtr->encode(pt)) return false;
				break;
			}
			default:
			{
				return false;
			}
		}
		return true;
    }

	bool
	OpcUaVariantValue::decode(boost::property_tree::ptree& pt, OpcUaBuildInType opcUaBuildInType)
	{
		OpcUaVariantValueType opcUaVariantValue;
		switch (opcUaBuildInType)
		{
			case  OpcUaBuildInType_OpcUaBoolean:
			{
				OpcUaBoolean opcUaBoolean;
				if (!Json::decode(pt, opcUaBoolean)) return false;
				opcUaVariantValue = opcUaBoolean;
				variantValue_ = opcUaVariantValue;
				break;
			}
			case  OpcUaBuildInType_OpcUaSByte:
			{
				OpcUaSByte opcUaSByte;
				if (!Json::decode(pt, opcUaSByte)) return false;
				opcUaVariantValue = opcUaSByte;
				variantValue_ = opcUaVariantValue;
				break;
			}
			case  OpcUaBuildInType_OpcUaByte:
			{
				OpcUaByte opcUaByte;
				if (!Json::decode(pt, opcUaByte)) return false;
				opcUaVariantValue = opcUaByte;
				variantValue_ = opcUaVariantValue;
				break;
			}
			case  OpcUaBuildInType_OpcUaInt16:
			{
				OpcUaInt16 opcUaInt16;
				if (!Json::decode(pt, opcUaInt16)) return false;
				opcUaVariantValue = opcUaInt16;
				variantValue_ = opcUaVariantValue;
				break;
			}
			case  OpcUaBuildInType_OpcUaUInt16:
			{
				OpcUaUInt16 opcUaUInt16;
				if (!Json::decode(pt, opcUaUInt16)) return false;
				opcUaVariantValue = opcUaUInt16;
				variantValue_ = opcUaVariantValue;
				break;
			}
			case  OpcUaBuildInType_OpcUaInt32:
			{
				OpcUaInt32 opcUaInt32;
				if (!Json::decode(pt, opcUaInt32)) {
					return false;
				}
				opcUaVariantValue = opcUaInt32;
				variantValue_ = opcUaVariantValue;
				break;
			}
			case  OpcUaBuildInType_OpcUaUInt32:
			{
				OpcUaUInt32 opcUaUInt32;
				if (!Json::decode(pt, opcUaUInt32)) return false;
				opcUaVariantValue = opcUaUInt32;
				variantValue_ = opcUaVariantValue;
				break;
			}
			case  OpcUaBuildInType_OpcUaInt64:
			{
				OpcUaInt64 opcUaInt64;
				if (!Json::decode(pt, opcUaInt64)) return false;
				opcUaVariantValue = opcUaInt64;
				variantValue_ = opcUaVariantValue;
				break;
			}
			case  OpcUaBuildInType_OpcUaUInt64:
			{
				OpcUaUInt64 opcUaUInt64;
				if (!Json::decode(pt, opcUaUInt64)) return false;
				opcUaVariantValue = opcUaUInt64;
				variantValue_ = opcUaVariantValue;
				break;
			}
			case  OpcUaBuildInType_OpcUaFloat:
			{
				OpcUaFloat opcUaFloat;
				if (!Json::decode(pt, opcUaFloat)) return false;
				opcUaVariantValue = opcUaFloat;
				variantValue_ = opcUaVariantValue;
				break;
			}
			case  OpcUaBuildInType_OpcUaDouble:
			{
				OpcUaDouble opcUaDouble;
				if (!Json::decode(pt, opcUaDouble)) return false;
				opcUaVariantValue = opcUaDouble;
				variantValue_ = opcUaVariantValue;
				break;
			}
			case  OpcUaBuildInType_OpcUaDateTime:
			{
				OpcUaDateTime opcUaDateTime;
				if (!opcUaDateTime.decode(pt)) return false;
				opcUaVariantValue = opcUaDateTime;
				variantValue_ = opcUaVariantValue;
				break;
			}
			case  OpcUaBuildInType_OpcUaStatusCode:
			{
				OpcUaInt32 opcUaStatusCode;
				if (!Json::decode(pt, opcUaStatusCode)) return false;
				opcUaVariantValue = (OpcUaStatusCode)opcUaStatusCode;
				variantValue_ = opcUaVariantValue;
				break;
			}
			case  OpcUaBuildInType_OpcUaGuid:
			{
				OpcUaVariantSPtr val;

				OpcUaGuid::SPtr opcUaGuidSPtr = constructSPtr<OpcUaGuid>();
				if (!opcUaGuidSPtr->decode(pt)) return false;
				val.objectSPtr_ = opcUaGuidSPtr;
				val.opcUaBuildInType_ = OpcUaBuildInType_OpcUaGuid;
				variantValue_ = val;
				break;
			}
			case  OpcUaBuildInType_OpcUaByteString:
			{
				OpcUaVariantSPtr val;

				OpcUaByteString::SPtr opcUaByteStringSPtr = constructSPtr<OpcUaByteString>();
				if (!opcUaByteStringSPtr->decode(pt)) return false;
				val.objectSPtr_ = opcUaByteStringSPtr;
				val.opcUaBuildInType_ = OpcUaBuildInType_OpcUaByteString;
				variantValue_ = val;
				break;
			}
			case  OpcUaBuildInType_OpcUaString:
			{
				OpcUaVariantSPtr val;

				OpcUaString::SPtr opcUaStringSPtr = constructSPtr<OpcUaString>();
				if (!opcUaStringSPtr->decode(pt)) return false;
				val.objectSPtr_ = opcUaStringSPtr;
				val.opcUaBuildInType_ = OpcUaBuildInType_OpcUaString;
				variantValue_ = val;
				break;
			}
			case  OpcUaBuildInType_OpcUaXmlElement:
			{
				OpcUaVariantSPtr val;

				OpcUaXmlElement::SPtr opcUaXmlElementSPtr = constructSPtr<OpcUaXmlElement>();
				if (!opcUaXmlElementSPtr->decode(pt)) return false;
				val.objectSPtr_ = opcUaXmlElementSPtr;
				val.opcUaBuildInType_ = OpcUaBuildInType_OpcUaXmlElement;
				variantValue_ = val;
				break;
			}
			case  OpcUaBuildInType_OpcUaNodeId:
			{
				OpcUaVariantSPtr val;

				OpcUaNodeId::SPtr opcUaNodeIdSPtr = constructSPtr<OpcUaNodeId>();
				if (!opcUaNodeIdSPtr->decode(pt)) return false;
				val.objectSPtr_ = opcUaNodeIdSPtr;
				val.opcUaBuildInType_ = OpcUaBuildInType_OpcUaNodeId;
				variantValue_ = val;
				break;
			}
			case  OpcUaBuildInType_OpcUaExpandedNodeId:
			{
				OpcUaVariantSPtr val;

				OpcUaExpandedNodeId::SPtr opcUaExpandedNodeIdSPtr = constructSPtr<OpcUaExpandedNodeId>();
				if (opcUaExpandedNodeIdSPtr->decode(pt)) return false;
				val.objectSPtr_ = opcUaExpandedNodeIdSPtr;
				val.opcUaBuildInType_ = OpcUaBuildInType_OpcUaExpandedNodeId;
				variantValue_ = val;
				break;
			}
			case  OpcUaBuildInType_OpcUaQualifiedName:
			{
				OpcUaVariantSPtr val;

				OpcUaQualifiedName::SPtr opcUaQualifiedNameSPtr = constructSPtr<OpcUaQualifiedName>();
				if (!opcUaQualifiedNameSPtr->decode(pt)) return false;
				val.objectSPtr_ = opcUaQualifiedNameSPtr;
				val.opcUaBuildInType_ = OpcUaBuildInType_OpcUaQualifiedName;
				variantValue_ = val;
				break;
			}
			case  OpcUaBuildInType_OpcUaLocalizedText:
			{
				OpcUaVariantSPtr val;

				OpcUaLocalizedText::SPtr opcUaLocalizedTextSPtr = constructSPtr<OpcUaLocalizedText>();
				if (!opcUaLocalizedTextSPtr->decode(pt)) return false;
				val.objectSPtr_ = opcUaLocalizedTextSPtr;
				val.opcUaBuildInType_ = OpcUaBuildInType_OpcUaLocalizedText;
				variantValue_ = val;
				break;
			}
			case  OpcUaBuildInType_OpcUaExtensionObject:
			{
				OpcUaVariantSPtr val;

				OpcUaExtensionObject::SPtr opcUaExtensionObjectSPtr = constructSPtr<OpcUaExtensionObject>();
				if (!opcUaExtensionObjectSPtr->decode(pt)) return false;
				val.objectSPtr_ = opcUaExtensionObjectSPtr;
				val.opcUaBuildInType_ = OpcUaBuildInType_OpcUaExtensionObject;
				variantValue_ = val;
				break;
			}
			default:
				return false;
				break;
		}
		return true;
	 }


	// ------------------------------------------------------------------------
	// ------------------------------------------------------------------------
	//
	// OpcUaVariant
	//
	// ------------------------------------------------------------------------
	// ------------------------------------------------------------------------
	OpcUaVariant::OpcUaVariant(void)
	:  Object()
	, variantValueVec_()
	, arrayLength_(-1)
	, arrayDimensionsVec_()
	{
		clear();
	}
		
	OpcUaVariant::~OpcUaVariant(void)
	{
	}

	void 
	OpcUaVariant::clear(void)
	{
		OpcUaVariantValue variantValue;
		variantValueVec_.clear();
		variantValueVec_.push_back(variantValue);

		arrayLength_ = -1;
		arrayDimensionsVec_.clear();
	}

	void 
	OpcUaVariant::arrayLength(const OpcUaInt32& arrayLength)
	{
		arrayLength_ = arrayLength;
	}

	OpcUaInt32 
	OpcUaVariant::arrayLength(void)
	{
		return arrayLength_;
	}

	bool
	OpcUaVariant::isArray(void)
	{
		return arrayLength_ > -1;
	}

	void 
	OpcUaVariant::arrayDimension(const OpcUaArrayDimensionsVec& arrayDimensionsVec)
	{
		if (arrayLength_ < 2) {
			return;
		}
		if (arrayDimensionsVec.size() == 0) {
			return;
		}

		uint32_t count = 0;
		OpcUaArrayDimensionsVec::const_iterator it;
		for (it = arrayDimensionsVec.begin(); it != arrayDimensionsVec.end(); it++) {
			if (it == arrayDimensionsVec.begin()) {
				count = *it;
			}
			else {
				count *= *it;
			}
		}

		if (arrayLength_ != count) {
			return;
		}

		arrayDimensionsVec_.clear();
		arrayDimensionsVec_ = arrayDimensionsVec;
	}
	
	OpcUaArrayDimensionsVec&
	OpcUaVariant::arrayDimension(void)
	{
		return arrayDimensionsVec_;
	}

	void 
	OpcUaVariant::variant(const OpcUaVariantValue::Vec& variantValueVec)
	{
		variantValueVec_ = variantValueVec;
		arrayLength_ = variantValueVec_.size();
	}

	OpcUaVariantValue::Vec& 
	OpcUaVariant::variant(void)
	{
		return variantValueVec_;
	}

	void 
	OpcUaVariant::pushBack(const OpcUaVariantValue& variantValue)
	{
		if (arrayLength_ == -1 && variantValueVec_.size() == 1) {
			variantValueVec_[0] = variantValue;
			arrayLength_ = variantValueVec_.size();
			return;
		}

		variantValueVec_.push_back(variantValue);
		arrayLength_ = variantValueVec_.size();
	}

	OpcUaBuildInType 
	OpcUaVariant::variantType(void) const
	{
		if (variantValueVec_.size() == 0) {
			return OpcUaBuildInType_Unknown;
		}
		return variantValueVec_[0].variantType();
	}

	bool
	OpcUaVariant::fromString(const std::string& string)
	{
		// split string into type and variable
		size_t pos = string.find(":");
		if (pos == std::string::npos) return false;

		std::string typeString = string.substr(0, pos);
		std::string valueString = string.substr(pos+1, string.length()-pos-1);
		bool isArray = false;

		// type can be an array
		if (typeString.length() > 5) {
			std::string substr = typeString.substr(typeString.length()-5, 5);
			boost::to_upper(substr);
			if (substr == "ARRAY") {
				isArray = true;
				typeString = typeString.substr(0, typeString.length()-5);
			}
		}

		// get build in type
		OpcUaBuildInType type = OpcUaBuildInTypeMap::string2BuildInType(typeString);

		// create build in type
		return fromString(type, isArray, valueString);
	}

	bool
	OpcUaVariant::fromString(OpcUaBuildInType type, bool isArray, const std::string& string)
	{
		// FIXME: read array
		if (isArray) return false;

		OpcUaVariantValue variantValue;
		if (!variantValue.fromString(type, string)) return false;
		clear();
		variantValueVec_[0] = variantValue;
		return true;
	}

	void 
	OpcUaVariant::copyTo(OpcUaVariant& variant)
	{
		variant.variant().clear();
		OpcUaVariantValue::Vec& sourceVariantValueVec = this->variant();
		OpcUaVariantValue::Vec& destVariantValueVec = variant.variant();

		OpcUaVariantValue::Vec::iterator it;
		for (it = sourceVariantValueVec.begin(); it != sourceVariantValueVec.end(); it++) {
			OpcUaVariantValue value;
			it->copyTo(value);
			destVariantValueVec.push_back(value);
		}

		variant.arrayLength(arrayLength_);
		variant.arrayDimension(arrayDimensionsVec_);
	}

	void
	OpcUaVariant::copyFrom(OpcUaVariant& variant)
	{
		variant.copyTo(*this);
	}

	bool 
	OpcUaVariant::operator==(OpcUaVariant& variant)
	{
		if (variant.arrayLength() != arrayLength_) return false;
		if (variant.variant().size() != variantValueVec_.size() ) return false;
		if (variant.arrayDimension().size() != arrayDimensionsVec_.size()) return false;

		OpcUaVariantValue::Vec& sourceVariantValueVec = this->variant();
		OpcUaVariantValue::Vec& destVariantValueVec = variant.variant();
		for (uint32_t idx=0; idx<variantValueVec_.size(); idx++) {
			if (sourceVariantValueVec[idx] != destVariantValueVec[idx]) return false; 
		}

		OpcUaArrayDimensionsVec& sourceDimensionsVec = arrayDimensionsVec_;
		OpcUaArrayDimensionsVec& destDimensionsVec = variant.arrayDimension();
		for (uint32_t idx=0; idx<sourceDimensionsVec.size(); idx++) {
			if (sourceDimensionsVec[idx] != destDimensionsVec[idx]) return false; 
		}

		return true;
	}

	bool 
	OpcUaVariant::operator!=(OpcUaVariant& variant)
	{
		return !operator==(variant);
	}

	void 
	OpcUaVariant::out(std::ostream& os) const
	{
		if (this->variantType() == OpcUaBuildInType_Unknown) {
			os << "---";
			return;
		}

		if (arrayLength_ == -1) {
			os << variantValueVec_[0];
		}
		else if (arrayLength_ == 0) {
			os << "[]";
		} 
		else {
			bool first = true;
			OpcUaVariantValue::Vec::const_iterator it;
			os << "[";
			for (it = variantValueVec_.begin(); it != variantValueVec_.end(); it++) {
				if (!first) os << ",";
				os << *it;
				first = false;
			}
			os << "]";
		}
	}

	void 
	OpcUaVariant::opcUaBinaryEncode(std::ostream& os) const
	{
		OpcUaBuildInType variantType = this->variantType();
		OpcUaByte encodingMask = (OpcUaByte)variantType;
		OpcUaInt32 arrayLength = arrayLength_;

		// handle array 
		if (arrayLength != -1 && arrayLength != variantValueVec_.size()) arrayLength = 0;
		if (arrayLength != -1 && variantType == OpcUaBuildInType_Unknown) arrayLength = 0; 

		if (arrayLength != -1) {
			encodingMask += 128;
		}

		if (arrayDimensionsVec_.size() > 0) {
			encodingMask += 64;
		}

		OpcUaNumber::opcUaBinaryEncode(os, encodingMask);
		if (arrayLength != -1) {
			OpcUaNumber::opcUaBinaryEncode(os, arrayLength);
		}

		if (variantType != OpcUaBuildInType_Unknown) {
			if (arrayLength == -1) {
				variantValueVec_[0].opcUaBinaryEncode(os, variantType);
			}
			else if (arrayLength == 0) {
			} 
			else {
				OpcUaVariantValue::Vec::const_iterator it;
				for (it = variantValueVec_.begin(); it != variantValueVec_.end(); it++) {
					it->opcUaBinaryEncode(os, variantType);
				}
			}
		}

		if (arrayDimensionsVec_.size() > 0) {
			OpcUaArrayDimensionsVec::const_iterator it;
			for (it = arrayDimensionsVec_.begin(); it != arrayDimensionsVec_.end(); it++) {
				OpcUaNumber::opcUaBinaryEncode(os, *it);
			}
		}
	}
		
	void 
	OpcUaVariant::opcUaBinaryDecode(std::istream& is)
	{
		OpcUaByte encodingMask;

		OpcUaNumber::opcUaBinaryDecode(is, encodingMask);

		arrayLength_ = -1;
		if ((encodingMask & 128) == 128) {
			OpcUaNumber::opcUaBinaryDecode(is, arrayLength_);
		}

		OpcUaByte encodingMaskTmp = encodingMask & 0x3F;
		OpcUaBuildInType variantType = (OpcUaBuildInType)encodingMaskTmp;

		variantValueVec_.clear();
		if (variantType != OpcUaBuildInType_Unknown) {
			if (arrayLength_ == -1) {
				OpcUaVariantValue variantValue;
				variantValueVec_.push_back(variantValue);
				variantValueVec_[0].opcUaBinaryDecode(is, variantType);
			}
			else if (arrayLength_ == 0) {
			}
			else {
				for (uint32_t idx=0; idx<(uint32_t)arrayLength_; idx++) {
					OpcUaVariantValue variantValue;
					variantValue.opcUaBinaryDecode(is, variantType);
					variantValueVec_.push_back(variantValue);
				}
			}
		}

		arrayDimensionsVec_.clear();

		if (arrayLength_ < 2) {
			return;
		}

		if ((encodingMask & 64) == 64) {
			OpcUaUInt32 arrayDimensions;
			OpcUaNumber::opcUaBinaryDecode(is, arrayDimensions);
			arrayDimensionsVec_.push_back(arrayDimensions);
			OpcUaUInt32 count = arrayDimensions;

			while (count < (uint32_t)arrayLength_) {
				OpcUaNumber::opcUaBinaryDecode(is, arrayDimensions);
				arrayDimensionsVec_.push_back(arrayDimensions);
				count = count * arrayDimensions;
			}
		}
	}

	bool
	OpcUaVariant::encode(boost::property_tree::ptree& pt) const
	{
		OpcUaBuildInType variantType = this->variantType();
		if (variantType == OpcUaBuildInType_Unknown) return false;

		if (arrayLength_ == -1) {
			if (!variantValueVec_[0].encode(pt, variantType)) return false;
		}
		else if (arrayLength_ == 0) {
		}
		else {
			OpcUaVariantValue::Vec::const_iterator it;
			for (it = variantValueVec_.begin(); it != variantValueVec_.end(); it++) {
				boost::property_tree::ptree ptVariant;
				if (!it->encode(ptVariant, variantType)) return false;
				pt.push_back(std::make_pair("", ptVariant));
			}
		}
		return true;
	}

	bool
	OpcUaVariant::decode(boost::property_tree::ptree& pt, const OpcUaBuildInType& opcUaBuildInType, bool isArray)
	{
		if (opcUaBuildInType == OpcUaBuildInType_Unknown) return false;

		arrayLength_ = -1;
		if (isArray) {
			arrayLength_ = pt.size();
		}
		variantValueVec_.clear();

		if (arrayLength_ == -1) {
			OpcUaVariantValue variantValue;
			variantValueVec_.push_back(variantValue);
			if (!variantValueVec_[0].decode(pt, opcUaBuildInType)) return false;
		}
		else if (arrayLength_ == 0) {
		}
		else {
			boost::property_tree::ptree::iterator it;
			for (it = pt.begin(); it != pt.end(); it++) {
				OpcUaVariantValue variantValue;
				if (!variantValue.decode(it->second, opcUaBuildInType)) return false;
				variantValueVec_.push_back(variantValue);
			}
		}

		arrayDimensionsVec_.clear();
		return true;
	}

};
