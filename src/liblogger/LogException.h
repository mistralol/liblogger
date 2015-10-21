
class LogException : public std::exception
{
	public:
		LogException(const std::string exception);
		~LogException();

		virtual const char *what() const throw();

	private:
		std::string m_message;
};

