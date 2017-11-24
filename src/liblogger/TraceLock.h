
namespace liblogger 
{
    class TraceLock {
        public:
            TraceLock(Trace *p);
            ~TraceLock();

            void Unlock();

        private:
            bool m_locked;
            Trace *m_trace;

    };
};
