class CalculatorSingleton {
    public:
        static CalculatorSingleton * getInstance();
        void increaseCounter();
        int getCounter();
        void printCounter();
    // protected:
    private:
        CalculatorSingleton();
        static CalculatorSingleton * m_calculator_instance;
        int m_counter = 0;
};