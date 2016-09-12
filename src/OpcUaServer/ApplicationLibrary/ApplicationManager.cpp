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
#include "OpcUaStackCore/Utility/Environment.h"
#include "OpcUaStackServer/Application/ApplicationInfo.h"
#include "OpcUaServer/ApplicationLibrary/ApplicationManager.h"

using namespace OpcUaStackServer;

namespace OpcUaServer
{

	ApplicationManager::ApplicationManager(void)
	: applicationLibraryMap_()
	, config_(nullptr)
	{
	}

	ApplicationManager::~ApplicationManager(void)
	{
		applicationLibraryMap_.clear();
	}

	bool
	ApplicationManager::startup(void)
	{
		std::string configurationFileName = config_->getValue("Global.ConfigurationFileName", "Unknown");

		// get list of all configured applications
		std::vector<Config> applicationVec;
		config_->getChilds("OpcUaServer.Applications.Application", applicationVec);
		if (applicationVec.size() == 0) {
			Log(Info, "no application in configuration available")
				.parameter("ConfigurationFileName", configurationFileName)
				.parameter("ParameterPath", "OpcUaServer.Applications.Application");
			return true;
		}

		// parse all applications
		std::vector<Config>::iterator it;
		for (it = applicationVec.begin(); it != applicationVec.end(); it++) {
			ApplicationInfo applicationInfo;

			// parse application name
			boost::optional<std::string> applicationName = it->getValue("Name");
			if (!applicationName) {
				Log(Info, "no application name in configuration available")
					.parameter("ConfigurationFileName", configurationFileName)
					.parameter("ParameterPath", "OpcUaServer.Applications.Application.Name");
				return false;
			}
			applicationInfo.applicationName(*applicationName);

			// parse library name
			boost::optional<std::string> libraryName = it->getValue("Library");
			if (!libraryName) {
				Log(Info, "no application library in configuration available")
					.parameter("ConfigurationFileName", configurationFileName)
					.parameter("ApplicationName", applicationName)
					.parameter("ParameterPath", "OpcUaServer.Applications.Application.Library");
				return false;
			}
			applicationInfo.libraryName(*libraryName);

			// parse config
			boost::optional<std::string> configFileName = it->getValue("Config");
			if (!configFileName) {
				Log(Info, "no configuration file in configuration available")
					.parameter("ConfigurationFileName", configurationFileName)
					.parameter("ApplicationName", applicationName)
					.parameter("ParameterPath", "OpcUaServer.Applications.Application.Config");
				return false;
			}
			applicationInfo.configFileName(*configFileName);

			// set environment variables
			applicationInfo.installDir(Environment::installDir());
			applicationInfo.binDir(Environment::binDir());
			applicationInfo.confDir(Environment::confDir());
			applicationInfo.logDir(Environment::logDir());

			// check application name
			ApplicationLibrary::Map::iterator it;
			it = applicationLibraryMap_.find(*applicationName);
			if (it != applicationLibraryMap_.end()) {
				Log(Info, "duplicate application found in configuration")
					.parameter("ConfigurationFileName", configurationFileName)
					.parameter("ApplicationName", applicationName);
				return false;
			}

			Log(Info, "load application library")
			    .parameter("ApplicationName", *applicationName)
				.parameter("LibraryName", *libraryName)
			    .parameter("ConfigFile", *configFileName);

			// create application library instance
			ApplicationLibrary::SPtr applicationLibrary = constructSPtr<ApplicationLibrary>();
			applicationLibrary->applicationInfo(applicationInfo);
			if (!applicationLibrary->startup()) {
				return false;
			}

			// call startup function
			ApplicationIf* applicationIf;
			applicationIf = applicationLibrary->applicationIf();
			applicationIf->config(config_);
			applicationIf->applicationInfo(&applicationLibrary->applicationInfo());

			applicationLibraryMap_.insert(
				std::make_pair(*applicationName, applicationLibrary)
			);

		}

		return true;
	}

	bool
	ApplicationManager::shutdown(void)
	{
		return true;
	}

	void
	ApplicationManager::config(Config& config)
	{
		config_ = &config;
	}

	Config&
	ApplicationManager::config(void)
	{
		return *config_;
	}

	ApplicationLibrary::Map&
	ApplicationManager::applicationLibraryMap(void)
	{
		return applicationLibraryMap_;
	}

}
