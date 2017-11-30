
class LogException : public std::exception
{
	public:
		LogException(const std::string &message);
		~LogException();

		virtual const char *what() const noexcept;

	private:
		std::string m_message;
};
