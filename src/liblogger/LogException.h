
class LogException : public std::exception
{
	public:
		LogException(const std::string message);
		~LogException();

		virtual const char *what() const throw();

	private:
		std::string m_message;
};

