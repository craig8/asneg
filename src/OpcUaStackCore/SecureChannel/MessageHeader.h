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

#ifndef __OpcUaStackCore_MessageHeader_h__
#define __OpcUaStackCore_MessageHeader_h__

#include "OpcUaStackCore/Base/ObjectPool.h"
#include "OpcUaStackCore/Base/os.h"
#include "OpcUaStackCore/BuildInTypes/OpcUaNumber.h"

namespace OpcUaStackCore
{

	typedef enum {
		MessageType_Unknown,
		MessageType_Hello,
		MessageType_Acknowledge,
		MessageType_OpenSecureChannel,
		MessageType_CloseSecureChannel,
		MessageType_Error,
		MessageType_Message
	} MessageType;

	class DLLEXPORT MessageHeader
	: public  Object
	{
	  public:
		typedef boost::shared_ptr<MessageHeader> SPtr;

		MessageHeader(void);
		virtual ~MessageHeader(void);

		const char* messageTypeString(void); 
		void messageType(const MessageType& messageType);
		MessageType messageType(void) const;
		void messageSize(const OpcUaUInt32& messageSize);
		OpcUaInt32 messageSize(void) const;
		void segmentFlag(char segmentFlag);
		char segmentFlag(void);

		void opcUaBinaryEncode(std::ostream& os) const;
		void opcUaBinaryDecode(std::istream& is);

	  private:
		char messageTypeString_[3];

		char segmentFlag_;
		MessageType messageType_;
		OpcUaUInt32 messageSize_;
	};

}

#endif
