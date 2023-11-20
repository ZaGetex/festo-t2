//
// Created by Tobias Jähnichen on 29.04.21.
//

#ifndef PRAKTIKUMPR2_SIMLOGGER_H
#define PRAKTIKUMPR2_SIMLOGGER_H

#include <fstream>
#include <sstream>

#define  LOGGER Simlogger::getLogger()

class Simlogger {
private:
    Simlogger();
    Simlogger(const Simlogger&){};
    Simlogger& operator=(const Simlogger&){return *this;};

    static std::string filename;
    static Simlogger* instance;
    static std::ofstream logfile;

public:
    virtual ~Simlogger();
    static Simlogger &getLogger();
    static void deleteLogger();

    void setLogfile(std::string filename);

    void log(const std::string& msg);
    void log(const char * format, ...);

    Simlogger& operator<<(const std::string& msg);
    Simlogger& operator<<(const int i);
    Simlogger& operator<<(const unsigned int i);
    Simlogger& operator<<(const double d);
    Simlogger& operator<<(std::basic_ostream<char, std::char_traits<char> >& (*manip)(std::basic_ostream<char, std::char_traits<char> >&));
    Simlogger & operator<<(std::ios_base & (*base) (std::ios_base &));
    std::ios_base& hex(std::ios_base& __str);
};


#endif //PRAKTIKUMPR2_SIMLOGGER_H
