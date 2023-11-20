//
// Created by Tobias Jähnichen on 29.04.21.
//

#include "simlogger.h"
#include <iostream>
#include <cstdarg>


Simlogger* Simlogger::instance = nullptr;
std::string Simlogger::filename = "../../../festo/log.txt";
std::ofstream Simlogger::logfile;

Simlogger::Simlogger(){
    logfile.open(filename, std::ios::out);
    if(!logfile.is_open() || !logfile.good()){
        std::cerr << "Warning: Could not open Logfile: " << filename << std::endl;
    }
}

Simlogger::~Simlogger() {
    if(logfile.is_open()){
        logfile.flush();
        logfile.close();
    }
}



Simlogger & Simlogger::getLogger() {
    if(nullptr == instance){
        instance = new Simlogger();
    }
    return *instance;
}

void Simlogger::deleteLogger() {
    if(nullptr != instance){
        delete instance;
        instance = nullptr;
    }

}

void Simlogger::setLogfile(std::string filename) {
    if(logfile.is_open()){
        logfile.close();
    }
    logfile.open(filename, std::ios::out);
    if(!logfile.is_open() || !logfile.good()){
        std::cerr << "Warning: Could not open Logfile: " << filename << std::endl;
    }
}

void Simlogger::log(const std::string &msg) {
    logfile << msg << std::endl;
}

void Simlogger::log(const char *format, ...) {
    char* msg = nullptr;
    int length = 0;
    va_list args;
    va_list argcopy;
    va_start(args, format);
    va_copy(argcopy, args);
    length = vsnprintf(NULL, 0, format, argcopy) + 1;
    va_end(argcopy);
    msg = new char[length];
    vsnprintf(msg, length, format, args);
    logfile << msg << std::endl;
}

Simlogger &Simlogger::operator<<(const std::string &msg) {
    logfile << msg;
    std::cout << msg;
    return *this;
}



Simlogger &Simlogger::operator<<(const double d) {
    logfile << d;
    std::cout << d;
    return *this;
}

Simlogger &Simlogger::operator<<(std::basic_ostream<char, std::char_traits<char> >& (*manip)(std::basic_ostream<char, std::char_traits<char> >&)) {
    logfile << std::endl;
    std::cout << std::endl;
    return *this;
}

Simlogger &Simlogger::operator<<(std::ios_base & (*base) (std::ios_base &)) {
    base(logfile);
    base(std::cout);
    return *this;
}

std::ios_base &Simlogger::hex(std::ios_base &__str) {
    std::cout << "HexHex" << std::endl;
    return __str;
}

Simlogger &Simlogger::operator<<(const int i) {
    logfile << i;
    std::cout << i;
    return *this;
}

Simlogger &Simlogger::operator<<(const unsigned int i) {
    logfile << i;
    std::cout << i;
    return *this;
}


