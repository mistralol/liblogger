

namespace liblogger
{
	class LogTailIdx : public ILogger
	{
		public:
			LogTailIdx(size_t length);
			virtual ~LogTailIdx() { };
		
			std::string GetName() const;
			std::string GetDesc() const;
			void Log(const LogType Type, const std::string &str);

			std::list<std::string> GetList();
			std::list<std::string> GetList(uint64_t *idx);
			std::list<std::string> GetList(uint64_t *idx, int maxitems);
		private:
			size_t m_length;
			uint64_t m_current;
			std::map<uint64_t, std::string> m_data;
	};
};

