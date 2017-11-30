
namespace liblogger
{
	class ILogFilter
	{
		public:
			virtual ~ILogFilter() { }

			virtual bool Filter(const LogType Type, const std::string &str) = 0;
	};
};
