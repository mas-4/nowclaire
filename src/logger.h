//
// Created by mas on 9/23/22.
//

#ifndef LOGGER_H
#define LOGGER_H

enum LoggingLevel {
    LOG_LEVEL_DEBUG,
    LOG_LEVEL_INFO,
    LOG_LEVEL_WARN,
    LOG_LEVEL_ERROR,
    LOG_LEVEL_FATAL,
};

void set_logging_level(enum LoggingLevel l);
void log_fatal(const char *msg);
void log_error(const char *msg);
void log_warn(const char *msg);
void log_info(const char *msg);
void log_debug(const char *msg);

#endif //LOGGER_H

#ifdef LOGGER_H_IMPL

#include <stdio.h>

#define RED   "\x1B[31m"
#define GREEN "\x1B[32m"
#define ORANGE "\x1B[33m"
#define BLUE "\x1B[34m"
#define BOLD "\x1B[1m"
#define RESET "\x1B[0m"

enum LoggingLevel level = LOG_LEVEL_INFO;

void set_logging_level(enum LoggingLevel l) {
    level = l;
}


void log_debug(const char *msg)
{
    if (level <= LOG_LEVEL_DEBUG)
    {
        printf("%s[DEBUG]%s: %s", BLUE, RESET, msg);
    }
}

void log_info(const char *msg)
{
    if (level <= LOG_LEVEL_INFO)
    {
        printf("%s[INFO]%s: %s", GREEN, RESET, msg);
    }
}

void log_warn(const char *msg)
{
    if (level <= LOG_LEVEL_WARN)
    {
        printf("%s[WARN]%s: %s", ORANGE, RESET, msg);
    }
}

void log_error(const char *msg)
{
    if (level <= LOG_LEVEL_ERROR)
    {
        printf("%s[ERROR]%s: %s", RED, RESET, msg);
    }
}

void log_fatal(const char *msg)
{
    if (level <= LOG_LEVEL_FATAL)
    {
        printf("%s%s[FATAL]%s: %s", RED, BOLD, RESET, msg);
    }
}

#endif // LOGGER_H_IMPL