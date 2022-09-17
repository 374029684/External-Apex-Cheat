#include <string>
#include <Windows.h>
#include <random>
#include "xor.hpp"
#include <TlHelp32.h>

uint32_t get_process_pid(const char* process_name);
bool RenameFile(std::string& path);
std::string RandomString(const int len);