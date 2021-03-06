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

#ifndef __OpcUaProjectBuilder_OpcUaProjectBuilder_h__
#define __OpcUaProjectBuilder_OpcUaProjectBuilder_h__

#include <boost/filesystem.hpp>
#include <stdint.h>

namespace OpcUaProjectBuilder
{

	class OpcUaProjectBuilder
	{
	  public:
		OpcUaProjectBuilder(void);
		~OpcUaProjectBuilder(void);

		uint32_t start(int argc, char** argv);

	  private:
		void usage(void);
		bool createProject(void);
		bool createProjectInfo(void);
		bool createProjectDirectory(void);
		bool createProjectDirectory(boost::filesystem::path& projectDirectory);
		bool createProjectFile(boost::filesystem::path& filename, const std::string& content);
		bool readProjectFile(boost::filesystem::path& filename, std::string& content);
		bool browseProjectDirectory(boost::filesystem::path& templateDirectory, boost::filesystem::path& projectDirectory);
		std::string processString(const std::string& string);

		// command line parameter
		std::string projectName_;
		std::string projectDescription_;
		std::string projectPort_;
		bool verbose_;

		boost::filesystem::path templateDirectory_;
		boost::filesystem::path projectDirectory_;
	};

}

#endif
