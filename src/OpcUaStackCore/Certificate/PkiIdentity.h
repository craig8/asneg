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

#ifndef __OpcUaStackCore_PkiIdentity_h__
#define __OpcUaStackCore_PkiIdentity_h__

#include <string>
#include "OpcUaStackCore/Base/os.h"

namespace OpcUaStackCore
{

	class DLLEXPORT PkiIdentity
	{
	  public:
		PkiIdentity(void);
		~PkiIdentity(void);

		void organization(const std::string& organization);
	    std::string& organization(void);
	    void organizationUnit(const std::string& organizationUnit);
	    std::string& organizationUnit(void);
	    void locality(const std::string& locality);
	    std::string& locality(void);
	    void state(const std::string& state);
	    std::string& state(void);
	    void country(const std::string& country);
	    std::string& country(void);
	    void commonName(const std::string& commonName);
	    std::string& commonName(void);
	    void domainComponent(const std::string& domainComponent);
	    std::string& domainComponent(void);

		bool operator==(const PkiIdentity &other) const;

	  private:
	    std::string organization_;
	    std::string organizationUnit_;
	    std::string locality_;
	    std::string state_;
	    std::string country_;
	    std::string commonName_;
	    std::string domainComponent_;
	};

}

#endif
