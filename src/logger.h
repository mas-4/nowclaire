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
void log_debug(const char *format, ...);
void log_info(const char *format, ...);
void log_warn(const char *format, ...);
void log_error(const char *format, ...);
void log_fatal(const char *format, ...);


#endif //LOGGER_H

#ifdef LOGGER_H_IMPL

#include <stdio.h>
#include <stdarg.h>

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

void log_debug(const char *format, ...)
{
    if (level <= LOG_LEVEL_DEBUG)
    {
        va_list args;
        va_start(args, format);

        printf("%s[DEBUG]%s: ", BLUE, RESET);
        vprintf(format, args);
        printf("\n");

        va_end(args);
    }
}

void log_info(const char *format, ...)
{
    if (level <= LOG_LEVEL_INFO)
    {
        va_list args;
        va_start(args, format);

        printf("%s[INFO]%s: ", GREEN, RESET);
        vprintf(format, args);
        printf("\n");

        va_end(args);
    }
}

void log_warn(const char *format, ...)
{
    if (level <= LOG_LEVEL_WARN)
    {
        va_list args;
        va_start(args, format);

        printf("%s[WARN]%s: ", ORANGE, RESET);
        vprintf(format, args);
        printf("\n");

        va_end(args);
    }
}

void log_error(const char *format, ...)
{
    if (level <= LOG_LEVEL_ERROR)
    {
        va_list args;
        va_start(args, format);

        printf("%s[ERROR]%s: ", RED, RESET);
        vprintf(format, args);
        printf("\n");

        va_end(args);
    }
}

void log_fatal(const char *format, ...)
{
    if (level <= LOG_LEVEL_FATAL)
    {
        va_list args;
        va_start(args, format);

        printf("%s[FATAL]%s: ", RED, RESET);
        vprintf(format, args);
        printf("\n");

        va_end(args);
    }
}


#endif // LOGGER_H_IMPL