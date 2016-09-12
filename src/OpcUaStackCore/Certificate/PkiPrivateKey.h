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

#ifndef __OpcUaStackCore_PkiPrivateKey_h__
#define __OpcUaStackCore_PkiPrivateKey_h__

#include <openssl/x509.h>
#include "OpcUaStackCore/Base/os.h"
#include "OpcUaStackCore/Certificate/PkiError.h"

namespace OpcUaStackCore
{

	class DLLEXPORT PkiPrivateKey
	: public PkiError
	{
	  public:
		PkiPrivateKey(void);
		~PkiPrivateKey(void);

		void privateKey(EVP_PKEY* privateKey);
		EVP_PKEY* privateKey(void);

	  private:
		EVP_PKEY* privateKey_;
	};

}

#endif
