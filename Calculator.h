class CalculatorSingleton {
    public:
        static CalculatorSingleton * getInstance();
        void printState();
        void increaseCounter();
        int getCounter();
        void printCounter();
    // protected:
    private:
        CalculatorSingleton();
        static CalculatorSingleton * m_calculator_instance;
        bool m_state;
        int m_counter = 0;
};