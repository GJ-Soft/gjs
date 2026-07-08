#ifndef _ORG_GJS_C_CC_CPP_LOG_CONFIG_H
#define _ORG_GJS_C_CC_CPP_LOG_CONFIG_H



#include <CppBase.h>


//#ifdef LOG4CXX
#include <log4cxx/log4cxx.h>
#include <log4cxx/xml/domconfigurator.h>
#include <log4cxx/logger.h>
#include <log4cxx/logstring.h>
#include <log4cxx/helpers/pool.h>
#include <log4cxx/basicconfigurator.h>
#include <log4cxx/rolling/rollingfileappender.h>
#include <log4cxx/consoleappender.h>
#include <log4cxx/patternlayout.h>
#include <log4cxx/logmanager.h>
#include <log4cxx/mdc.h>


//#else ifdef LOG4CPP
//#	include <log4cpp/Category.hh>
//#	include <log4cpp/Appender.hh>
//#	include <log4cpp/FileAppender.hh>
//#	include <log4cpp/OstreamAppender.hh>
//#	include <log4cpp/Layout.hh>
//#	include <log4cpp/BasicLayout.hh>
//#	include <log4cpp/Priority.hh>
//#endif


#include <locale.h>


#include <iostream>
#include <sstream>



#define LOG_FIC_CFG_DEF					"log4cxx.xml"

#define LOG_TMP_RECONFIGURACION			3600000

#define LOG_PATRON_DEF 					"[%d{yyyy-MM-dd HH:mm:ss}] %c %-5p - %m%n"
#define	LOG_PATRON_FECHA_DEF			"'.'yyyy-MM-dd"
#define LOG_PATRON_CONSOLA_MIN			"%m%n"





#endif
