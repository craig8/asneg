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

   Autor: Kai Huebl (kai@huebl-sgh.de)
 */

#ifndef __OpcUaStackCore_DataTypeGenerator_h__
#define __OpcUaStackCore_DataTypeGenerator_h__

#include <boost/property_tree/ptree.hpp>
#include <vector>

#include "OpcUaStackCore/Base/os.h"
#include "OpcUaStackCore/BuildInTypes/BuildInTypes.h"
#include "OpcUaStackCore/DataType/DataTypeDefinition.h"

namespace OpcUaStackCore
{

	class DLLEXPORT DataTypeGenerator
	{
	  public:
		typedef boost::shared_ptr<DataTypeGenerator> SPtr;

		DataTypeGenerator(void);
		~DataTypeGenerator(void);

		void projectNamespace(const std::string& projectName);
		void projectDirectory(const std::string& projectDirectory);
		void dataTypeDefinition(DataTypeDefinition::SPtr& dataTypeDefinition);
		void superTypeDataTypeDefinition(DataTypeDefinition::SPtr& dataTypeDefinition);
		std::string& sourceFileContent(void);
		std::string& headerFileContent(void);

		bool generate(void);

	  private:
		//
		// header functions
		//
		bool generateHeader(void);
		bool generateHeaderComments(void);

		//
		// source functions
		//
		bool generateSource(void);
		bool generateSourceComments(void);

		std::string projectNamespace_;
		std::string projectDirectory_;
		DataTypeDefinition::SPtr dataTypeDefinition_;
		DataTypeDefinition::SPtr superTypeDataTypeDefinition_;
		std::string sourceContent_;
		std::string headerContent_;
	};


}

#endif
