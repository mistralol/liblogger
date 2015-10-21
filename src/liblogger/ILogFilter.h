
namespace liblogger
{
	class ILogFilter
	{
		public:
			ILogFilter() { }
			virtual ~ILogFilter() { }

			virtual bool Filter(const LogType Type, const std::string &str) { return false; }
	};
};

