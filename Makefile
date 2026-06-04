TOP = .
include $(TOP)/configure/CONFIG
DIRS += configure
DIRS += sysmonApp
DIRS += iocBoot
include $(TOP)/configure/RULES_TOP
