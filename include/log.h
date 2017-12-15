#ifndef __LOG_H__
#define __LOG_H__

enum manage_system_log_level {
	MANAGE_SYSTEM_LOG_ERROR,
	MANAGE_SYSTEM_LOG_WARN,
	MANAGE_SYSTEM_LOG_NOTICE,
};

/* Define manage_system log handle function  */
#define LOG_ERROR(...) \
		manage_system_log(MANAGE_SYSTEM_LOG_ERROR, __FILE__, __LINE__, __func__, __VA_ARGS__)

void manage_system_log(enum manage_system_log_level, const char *file,
		       const int line, const char *func, const char *format, ...);

#endif /* __LOG_H__ end  */
