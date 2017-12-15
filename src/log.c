#include "stdinc.h"

#include "log.h"
#include "common_handle.h"

enum manage_system_log_level printf_manage_system_log = MANAGE_SYSTEM_LOG_NOTICE;

static const char *const log_level_names[] = {
	[MANAGE_SYSTEM_LOG_ERROR]	= "ERROR",
	[MANAGE_SYSTEM_LOG_WARN]	= "WARNING",
	[MANAGE_SYSTEM_LOG_NOTICE]	= "NOTICE",
};

/* Handle manage_system_log  */
void
manage_system_log(enum manage_system_log_level level, const char *file, const int line, const char *func,
				 const char *format, ...)
{
	char buf[VA_ARGS_BUF];
	va_list ap;
	char severity = LOG_INFO;

	switch (level) {
	case MANAGE_SYSTEM_LOG_ERROR:
		severity = LOG_ERR;
		break;
	default:
		fprintf(stderr, "manage_system_log_level error\n");
		break;
	}

	va_start(ap, format);
	vsnprintf(buf, sizeof(buf), format, ap);

	openlog("MANAGE_SYSTEM", LOG_PERROR|LOG_PID, 0);		/* Output termainal and printf pid, 0 default LOG_USER  */

	/* If level is error and warn will output  */
	if (level <= printf_manage_system_log) {
		syslog(severity, "%s:%4d:%s: *%s*: %s", file, line, func, log_level_names[level], buf);
	}
	
	closelog();

	va_end(ap);
}
