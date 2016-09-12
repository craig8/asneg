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

#include "OpcUaStackServer/NodeSet/NodeSetNamespace.h"
#include "OpcUaStackCore/Base/Log.h"

using namespace OpcUaStackCore;

namespace OpcUaStackServer
{

	bool NodeSetNamespace::startup_ = false;
	NamespaceVec NodeSetNamespace::globalNamespaceVec_;
	NamespaceMap NodeSetNamespace::globalNamespaceMap_;

	NodeSetNamespace::NodeSetNamespace(void)
	: inputNamespaceIndexVec_()
	, outputNamespaceIndexMap_()
	, localNamespaceVec_()
	{
		outputNamespaceIndexMap_.insert(std::make_pair(0,0));
		localNamespaceVec_.push_back("http://opcfoundation.org/UA/"); 
		startup();
		
	}

	NodeSetNamespace::~NodeSetNamespace(void)
	{
	}

	void
	NodeSetNamespace::clearGlobal(void)
	{
		startup_ = false;
		globalNamespaceVec_.clear();
		globalNamespaceMap_.clear();
		clear();
	}

	void
	NodeSetNamespace::clear(void)
	{
		inputNamespaceIndexVec_.clear();
		outputNamespaceIndexMap_.clear();
		localNamespaceVec_.clear();
		localNamespaceVec_.push_back("http://opcfoundation.org/UA/");
		outputNamespaceIndexMap_.insert(std::make_pair(0,0));
	}

	void
	NodeSetNamespace::startup(void)
	{
		if (startup_) return;
		startup_ = true;

		// clear namespace vector an namespace map
		globalNamespaceVec_.clear();
		globalNamespaceMap_.clear();

		// add opc ua standard namespace
		globalNamespaceVec_.push_back("http://opcfoundation.org/UA/");
		globalNamespaceMap_.insert(std::make_pair("http://opcfoundation.org/UA/", 0));
	}

	uint16_t 
	NodeSetNamespace::addGlobalNamespace(const std::string& namespaceUri)
	{
		uint16_t globalNamespaceIndex;
		NamespaceMap::iterator mit;
		mit = globalNamespaceMap_.find(namespaceUri);
		if (mit == globalNamespaceMap_.end()) {
			globalNamespaceIndex = globalNamespaceMap_.size();
			globalNamespaceVec_.push_back(namespaceUri);
			globalNamespaceMap_.insert(std::make_pair(namespaceUri, globalNamespaceIndex));

			Log(Info, "global namespace add")
				.parameter("NamespaceUri", namespaceUri)
				.parameter("NamespaceIndex", globalNamespaceIndex);
		}
		else {
			globalNamespaceIndex = mit->second;
		}

		return globalNamespaceIndex;
	}

	std::string 
	NodeSetNamespace::getGlobalNamespaceUri(uint16_t globalNamespaceIndex)
	{
		if (globalNamespaceVec_.size() <= globalNamespaceIndex) {
			return "http://unknown.org/Unknown/";
		}
		return globalNamespaceVec_[globalNamespaceIndex];
	}

	void 
	NodeSetNamespace::decodeNamespaceUris(std::vector<std::string>& namespaceUriVec)
	{
		inputNamespaceIndexVec_.clear();
		inputNamespaceIndexVec_.push_back(0);
		
		if (namespaceUriVec.size() == 0) return;

		if (namespaceUriVec[0] != "http://opcfoundation.org/UA/") {
			inputNamespaceIndexVec_.push_back(0);
		}

		std::vector<std::string>::iterator it;
		for (it = namespaceUriVec.begin(); it != namespaceUriVec.end(); it++) {
			std::string namespaceUri = *it;

			uint16_t globalNamespaceIndex = this->addGlobalNamespace(namespaceUri);
			if (namespaceUri != "http://opcfoundation.org/UA/") {
				localNamespaceVec_.push_back(namespaceUri);
				inputNamespaceIndexVec_.push_back(globalNamespaceIndex);
			}

			Log(Info, "local namespace add")
				.parameter("NamespaceUri", namespaceUri)
				.parameter("LocalNamespaceIndex", inputNamespaceIndexVec_.size()-1)
				.parameter("GlobalNamespaceIndex", globalNamespaceIndex);
		}
	}

	void 
	NodeSetNamespace::decodeNamespaceUris(boost::property_tree::ptree& ptree)
	{
		inputNamespaceIndexVec_.clear();
		inputNamespaceIndexVec_.push_back(0);

		boost::optional<boost::property_tree::ptree&> namespaceUris = ptree.get_child_optional("NamespaceUris");
		if (!namespaceUris) {
			return;
		}

		boost::property_tree::ptree::iterator it;
		for (it=namespaceUris->begin(); it!=namespaceUris->end(); it++) {
			if (it->first != "Uri") continue;
			std::string namespaceUri = it->second.data();
			uint16_t globalNamespaceIndex = this->addGlobalNamespace(namespaceUri);
			localNamespaceVec_.push_back(namespaceUri);
			inputNamespaceIndexVec_.push_back(globalNamespaceIndex);

			Log(Info, "local namespace add")
				.parameter("NamespaceUri", namespaceUri)
				.parameter("LocalNamespaceIndex", inputNamespaceIndexVec_.size()-1)
				.parameter("GlobalNamespaceIndex", globalNamespaceIndex);
		}
	}

	void 
	NodeSetNamespace::encodeNamespaceUris(boost::property_tree::ptree& ptree)
	{
		bool first = true;
		NamespaceVec::iterator it;
		for (it = localNamespaceVec_.begin(); it != localNamespaceVec_.end(); it++) {
			if (first) {
				first = false;
				continue;
			}
			ptree.add("NamespaceUris.Uri", *it);
		}
	}

	uint32_t
	NodeSetNamespace::addNewGlobalNamespace(const std::string& namespaceUri)
	{
		return addGlobalNamespace(namespaceUri);
	}

	NamespaceVec& 
	NodeSetNamespace::globalNamespaceVec(void)
	{
		return globalNamespaceVec_;
	}

	uint16_t 
	NodeSetNamespace::mapToGlobalNamespaceIndex(uint16_t localNamespaceIndex)
	{
		if (localNamespaceIndex >= inputNamespaceIndexVec_.size()) {
			return 999;
		}
		return inputNamespaceIndexVec_[localNamespaceIndex];
	}

	NamespaceVec& 
	NodeSetNamespace::localNamespaceVec(void)
	{
		return localNamespaceVec_;
	}

	uint16_t 
	NodeSetNamespace::mapToLocalNamespaceIndex(uint16_t globalNamespaceIndex)
	{
		NamespaceIndexMap::iterator it;
		it = outputNamespaceIndexMap_.find(globalNamespaceIndex);
		if (it != outputNamespaceIndexMap_.end()) {
			return it->second;
		}

		std::string globalNamespaceUri = getGlobalNamespaceUri(globalNamespaceIndex);
		uint16_t localNamespaceIndex = localNamespaceVec_.size();
		localNamespaceVec_.push_back(globalNamespaceUri);
		outputNamespaceIndexMap_.insert(std::make_pair(globalNamespaceIndex, localNamespaceIndex));

		return localNamespaceIndex;
	}

	uint16_t 
	NodeSetNamespace::mapToGlobalNamespaceIndex(const std::string& namespaceUri)
	{
		NamespaceMap::iterator it = globalNamespaceMap_.find(namespaceUri);
		if (it == globalNamespaceMap_.end()) {
			return 0xFFFF;
		}
		return it->second;
	}

}
