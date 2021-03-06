/*
   Copyright 2017 Kai Huebl (kai@huebl-sgh.de)

   Lizenziert gemäß Apache Licence Version 2.0 (die „Lizenz“); Nutzung dieser
   Datei nur in Übereinstimmung mit der Lizenz erlaubt.
   Eine Kopie der Lizenz erhalten Sie auf http://www.apache.org/licenses/LICENSE-2.0.

   Sofern nicht gemäß geltendem Recht vorgeschrieben oder schriftlich vereinbart,
   erfolgt die Bereitstellung der im Rahmen der Lizenz verbreiteten Software OHNE
   GEWÄHR ODER VORBEHALTE – ganz gleich, ob ausdrücklich oder stillschweigend.

   Informationen über die jeweiligen Bedingungen für Genehmigungen und Einschränkungen
   im Rahmen der Lizenz finden Sie in der Lizenz.

   Autor: Aleksey Timin (atimin@gmail.com)
 */

#include <OpcUaStackPubSub/Network/ConnectionManagerBase.h>

namespace OpcUaStackPubSub
{

	ConnectionManagerBase::ConnectionManagerBase(void)
	: receiverSet_()
	{
	}

	ConnectionManagerBase::~ConnectionManagerBase(void)
	{
	}

	bool
	ConnectionManagerBase::registerReceiverIf(const NetworkReceiverIf::SPtr& receiver)
	{
		std::pair<NetworkReceiverIf::Set::iterator, bool> result = receiverSet_.insert(receiver);
		return result.second;
	}

	bool
	ConnectionManagerBase::deregisterReceiverIf(const NetworkReceiverIf::SPtr& receiver)
	{
		return receiverSet_.erase(receiver) > 0;
	}

}
