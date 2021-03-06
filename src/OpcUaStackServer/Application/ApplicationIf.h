/*
   Copyright 2015-2017 Kai Huebl (kai@huebl-sgh.de)

   Lizenziert gem���� Apache Licence Version 2.0 (die ���Lizenz���); Nutzung dieser
   Datei nur in ��bereinstimmung mit der Lizenz erlaubt.
   Eine Kopie der Lizenz erhalten Sie auf http://www.apache.org/licenses/LICENSE-2.0.

   Sofern nicht gem���� geltendem Recht vorgeschrieben oder schriftlich vereinbart,
   erfolgt die Bereitstellung der im Rahmen der Lizenz verbreiteten Software OHNE
   GEW��HR ODER VORBEHALTE ��� ganz gleich, ob ausdr��cklich oder stillschweigend.

   Informationen ��ber die jeweiligen Bedingungen f��r Genehmigungen und Einschr��nkungen
   im Rahmen der Lizenz finden Sie in der Lizenz.

   Autor: Kai Huebl (kai@huebl-sgh.de)
 */

#ifndef __OpcUaStackServer_ApplicationIf_h__
#define __OpcUaStackServer_ApplicationIf_h__

#include "OpcUaStackCore/Base/os.h"
#include "OpcUaStackCore/Base/Config.h"
#include "OpcUaStackServer/Application/ApplicationServiceIf.h"
#include "OpcUaStackServer/Application/ApplicationInfo.h"
#include "OpcUaStackServer/InformationModel/InformationModel.h"

namespace OpcUaStackServer
{

	class DLLEXPORT ApplicationIf
	{
	  public:
		ApplicationIf(void)
	    : applicationServiceIf_(nullptr)
	  	, config_(nullptr)
	    , applicationInfo_(nullptr)
	    {
	    }
		virtual ~ApplicationIf(void) {}

		virtual bool startup(void) = 0;
		virtual bool shutdown(void) = 0;
		virtual void receive(ServiceTransaction::SPtr serviceTransaction) {};

		void service(ApplicationServiceIf* applicationServiceIf) {
			applicationServiceIf_ = applicationServiceIf;
		}

		ApplicationServiceIf& service(void) {
			return *applicationServiceIf_;
		}

		void config(Config* config) {
			config_ = config;
		}

		Config* config(void) {
			return config_;
		}

		void applicationInfo(ApplicationInfo* applicationInfo) {
			applicationInfo_ = applicationInfo;
		}

		ApplicationInfo* applicationInfo(void) {
			return applicationInfo_;
		}

		void informationModel(InformationModel::SPtr model) {
		  informationModel_ = model;
		}

		InformationModel::SPtr informationModel(void) {
		  return informationModel_;
		}

		virtual std::string version(void)
		{
			return "0.0.0";
		}

	  private:
		ApplicationServiceIf* applicationServiceIf_;
		Config* config_;
		ApplicationInfo* applicationInfo_;
		InformationModel::SPtr informationModel_;
	};

}

#endif
