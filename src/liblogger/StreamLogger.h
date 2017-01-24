
namespace liblogger
{
	class StreamLogger
	{
		public:
			StreamLogger();
			~StreamLogger();
		
			
			StreamLogger& operator<<(const LogType& type)
			{
				m_type = type;
				return *this;
			}
	
			template<typename T> StreamLogger& operator<<(const T& t)
			{
				m_buffer << t;
				return *this;
			}
		
			StreamLogger& operator<<(std::ostream& (*fn)(std::ostream&))
			{
				Logger(m_type, m_buffer.str());
				m_buffer.str("");
				return *this;
			}
		
		private:
			std::stringstream m_buffer;
			LogType m_type;
			
	};
	
	StreamLogger &GetStreamLogger();
};





