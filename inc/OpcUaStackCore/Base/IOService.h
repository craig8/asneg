#ifndef __OpcUaStackCore_IOService_h__
#define __OpcUaStackCore_IOService_h__

#include <vector>
#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <boost/thread/condition.hpp>
#include "OpcUaStackCore/Base/os.h"

namespace OpcUaStackCore
{

	class DLLEXPORT IOService
	{
	  public:
		IOService();
		virtual ~IOService();

		static void secSleep(uint32_t sec);
		static void msecSleep(uint32_t msec);

		void start(uint32_t numberThreads = 1);
		void stop(void);
		template<typename HANDLER>
		  void run(HANDLER handler);
		boost::asio::io_service& io_service(void);

	  private:
		void runThreads(void);

		uint32_t numberThreads_;
		uint32_t runningThreads_;
		boost::asio::io_service io_service_;
		boost::asio::io_service::work *work_;

		boost::mutex startMutex_;
		boost::condition startCondition_;
		boost::mutex stopMutex_;
		boost::condition stopCondition_;

		typedef std::vector<boost::thread*> ThreadVec;
		ThreadVec threadVec_;
	};


	template<typename HANDLER>
	  void 
	  IOService::run(HANDLER handler)
	  {
		  io_service_.post(
		      handler
	      );
      }

}

#endif