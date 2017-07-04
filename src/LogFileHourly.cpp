
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <dirent.h>
#include <sstream>

#include "liblogger.h"

namespace liblogger
{

LogFileHourly::LogFileHourly(const std::string dir, const std::string prefix, int maxage) :
	m_dir(dir),
	m_prefix(prefix),
	m_maxage(maxage),
	m_fname(""),
	m_fp(NULL)
{

}

LogFileHourly::~LogFileHourly()
{
	if (m_fp != NULL)
	{
		if (fclose(m_fp) < 0)
		{
			abort();
		}
	}
}

void LogFileHourly::GetName(std::string *str)
{
	*str = "FileHourly";
}

void LogFileHourly::GetDesc(std::string *str)
{
	*str = "Logs to a new file evey hour";
}

void LogFileHourly::Log(const LogType Type, const std::string &str)
{
	if (m_fp == NULL)
	{

	}
	
	time_t current = time(NULL);
	struct tm timeinfo;
	char fname[1024];
	char buf[128];

	localtime_r(&current, &timeinfo);
	
	if (strftime(fname, sizeof(fname), "%Y%m%d%H", &timeinfo) == 0)
	{
		std::stringstream ss;
		ss << "strftime failed: '" << "' error: " << strerror(errno);
		throw(LogException(ss.str()));
	}
	const std::string cname = m_dir + "/" + m_prefix + "-" + fname;
	
	if (m_fname != cname)
	{
		if (m_fp != NULL)
		{
			if (fclose(m_fp) < 0)
			{
				std::stringstream ss;
				ss << "Cannot close file: '" << m_fname << "' error: " << strerror(errno);
				throw(LogException(ss.str()));
			}
			m_fp = NULL;
		}
		m_fname = cname;
		RemoveOld();
	}
	
	if (m_fp == NULL)
	{
		m_fp = fopen(m_fname.c_str(), "a");
		if (m_fp == NULL)
		{
			std::stringstream ss;
			ss << "Cannot open file: '" << m_fname << "' error: " << strerror(errno);
			throw(LogException(ss.str()));
		}
	}
	
	if (strftime(buf, sizeof(buf), "%F %T", &timeinfo) == 0)
	{
		std::stringstream ss;
		ss << "strftime failed: '" << "' error: " << strerror(errno);
		throw(LogException(ss.str()));
	}

	if (fprintf(m_fp, "%s - %s [PID: %d] - %s\n", buf, LogTypeToStr(Type).c_str(), getpid(), str.c_str()) < 0)
	{
		std::stringstream ss;
		ss << "failed to write to file '" << m_fname << "' error:" << strerror(errno);
		throw(LogException(ss.str()));
	}
	if (fflush(m_fp) < 0)
	{
		std::stringstream ss;
		ss << "failed to fflush to file '" << m_fname << "' error:" << strerror(errno);
		throw(LogException(ss.str()));	
	}
}

void LogFileHourly::Rotate()
{
	if (m_fp != NULL)
	{
		if (fclose(m_fp) < 0)
		{
			std::stringstream ss;
			ss << "Cannot close file: '" << m_fname << "' error: " << strerror(errno);
			throw(LogException(ss.str()));
		}
		m_fp = NULL;
	}
	RemoveOld();
}

void LogFileHourly::RemoveOld()
{

	if (m_maxage <= 0)
		return;

	DIR *d = opendir(m_dir.c_str());
	if (d == NULL)
	{
		std::stringstream ss;
		ss << "Unable to open directory '" << m_dir << "' error:" << strerror(errno);
		throw(LogException(ss.str()));	
	}
	
	time_t current = time(NULL);
	struct tm timeinfo;
	char strtime[1024];

	localtime_r(&current, &timeinfo);
	
	if (strftime(strtime, sizeof(strtime), "%Y%m%d%H", &timeinfo) == 0)
	{
		std::stringstream ss;
		ss << "strftime failed: '" << "' error: " << strerror(errno);
		if (closedir(d) < 0)
		{
			std::stringstream ss2;
			ss2 << "Unable to close directory '" << m_dir << "' error:" << strerror(errno);
			throw(LogException(ss2.str()));
		}
		throw(LogException(ss.str()));
	}
	
	int oldest = 0;
	if (sscanf(strtime, "%d", &oldest) != 1)
		abort();
	oldest -= m_maxage;

	while(1)
	{
		errno = 0;
		struct dirent *info = readdir(d);
		if (info == NULL)
			break; //EOF
		std::string fname = info->d_name;
		std::string prefix = m_prefix + "-";
		if (fname.compare(0, prefix.length(), prefix) == 0)
		{
			//Parse and comare time.
			int time = 0;
			if (sscanf(&fname.c_str()[prefix.length()], "%d", &time) == 1)
			{
				if (time < oldest)
				{
					std::string file = m_dir + "/" + fname;
					if (unlink(file.c_str()) < 0)
					{
						std::stringstream ss;
						ss << "Unable to remove file '" << file.c_str() << "' error:" << strerror(errno);
						throw(LogException(ss.str()));	
					}
				}
			}
			else
			{
				//Cant parse
			}
		}
	}

	if (errno != 0)
	{
		std::stringstream ss;
		ss << "readdir failed in '" << m_dir << "' error:" << strerror(errno);
		if (closedir(d) < 0)
		{
			std::stringstream ss2;
			ss2 << "Unable to close directory '" << m_dir << "' error:" << strerror(errno);
			throw(LogException(ss2.str()));
		}
		throw(LogException(ss.str()));
	}
	
	if (closedir(d) < 0)
	{
		std::stringstream ss;
		ss << "Unable to close directory '" << m_dir << "' error:" << strerror(errno);
		throw(LogException(ss.str()));	
	}
}

};

