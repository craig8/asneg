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

#include "OpcUaStackCore/BuildInTypes/OpcUaDateTime.h"

namespace OpcUaStackCore
{


	// ------------------------------------------------------------------------
	// ------------------------------------------------------------------------
	//
	// OpcUaDateTime
	//
	// ------------------------------------------------------------------------
	// ------------------------------------------------------------------------
	boost::posix_time::ptime OpcUaDateTime::nullTime_ = boost::posix_time::from_iso_string("16010101T000000.000000000");

	OpcUaDateTime::OpcUaDateTime(void)
	: dateTime_(0)
	{
	}

	OpcUaDateTime::OpcUaDateTime(const boost::posix_time::ptime& ptime)
	: dateTime_(0)
	{
		dateTime(ptime);
	}

	OpcUaDateTime::~OpcUaDateTime(void)
	{
	}

	void 
	OpcUaDateTime::dateTime(const boost::posix_time::ptime& dateTime)
	{
		boost::posix_time::time_duration td = dateTime - nullTime_;
		if (td.is_negative()) {
			dateTime_ = 0;
		}
		else {
			dateTime_ = td.total_microseconds() * 10;
		}
	}

	boost::posix_time::ptime
	OpcUaDateTime::dateTime(void) const
	{
		boost::posix_time::time_duration td = boost::posix_time::microseconds(dateTime_/10);
		boost::posix_time::ptime ptime = nullTime_ + td;
		return ptime;
	}

	bool 
	OpcUaDateTime::exist(void) const
	{
		if (dateTime_ == 0) {
			return false;
		}
		return true;
	}

	OpcUaDateTime& 
	OpcUaDateTime::operator=(const OpcUaUInt64& dateTime)
	{
		dateTime_ = dateTime;
		return *this;
	}

	bool
	OpcUaDateTime::operator==(const OpcUaDateTime& dateTime) const
	{
		return this->dateTime() == dateTime.dateTime();
	}
		
	OpcUaDateTime::operator OpcUaUInt64 const (void)
	{
		return dateTime_;
	}

	bool 
	OpcUaDateTime::fromISOString(const std::string& dateTimeString)
	{
		std::stringstream ss;

		// do not delete this memory by yourself
		boost::posix_time::time_input_facet* facet = new boost::posix_time::time_input_facet();
		facet->set_iso_extended_format();
		ss.imbue(std::locale(ss.getloc(), facet));
		ss.str(dateTimeString);
		boost::posix_time::ptime timeFromString; 
		ss >> timeFromString;
		dateTime(timeFromString);
		return true;
	}

	std::string
	OpcUaDateTime::toISOString(void)
	{
		std::string str;
		try 
		{
			str = boost::posix_time::to_iso_extended_string(dateTime());
		} catch(std::exception&) {
			return "unknown";
		}
		return str;
	}

	void 
	OpcUaDateTime::out(std::ostream& os) const
	{
		std::string str;
		try 
		{
			str = boost::posix_time::to_iso_string(dateTime());
		} catch(std::exception&) {
			str = "unknown";
		}
		os << str;
	}

	void 
	OpcUaDateTime::opcUaBinaryEncode(std::ostream& os) const
	{
		OpcUaNumber::opcUaBinaryEncode(os, dateTime_);
	}

	void 
	OpcUaDateTime::opcUaBinaryDecode(std::istream& is)
	{
		OpcUaNumber::opcUaBinaryDecode(is, dateTime_);
	}

	void 
	OpcUaDateTime::copyTo(OpcUaDateTime& opcUaDataTime)
	{
		opcUaDataTime = dateTime_;
	}

	bool
	OpcUaDateTime::encode(boost::property_tree::ptree& pt) const
	{
		std::string dateTimeString;
		try
		{
			dateTimeString = boost::posix_time::to_iso_extended_string(dateTime());
		} catch(std::exception&) {
			return false;
		}
		pt.put_value<std::string>(dateTimeString);
		return true;
	}

	bool
	OpcUaDateTime::decode(boost::property_tree::ptree& pt)
	{
		std::stringstream ss;
		std::string dateTimeString = pt.get_value<std::string>();

		boost::posix_time::time_input_facet* facet = new boost::posix_time::time_input_facet();
		facet->set_iso_extended_format();
		ss.imbue(std::locale(ss.getloc(), facet));
		ss.str(dateTimeString);
		boost::posix_time::ptime timeFromString;
		ss >> timeFromString;
		dateTime(timeFromString);
		return true;
	}

}
