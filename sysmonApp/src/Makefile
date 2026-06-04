# SPDX-FileCopyrightText: 2003 Argonne National Laboratory
#
# SPDX-License-Identifier: EPICS


TOP=../..

include $(TOP)/configure/CONFIG

PROD_IOC = sysmon

DBD += sysmon.dbd

sysmon_DBD += base.dbd
sysmon_DBD += sysmonSub.dbd

sysmon_SRCS += sysmon_registerRecordDeviceDriver.cpp
sysmon_SRCS_DEFAULT += sysmonMain.cpp
sysmon_SRCS += sysmonSub.c

sysmon_LIBS += $(EPICS_BASE_IOC_LIBS)

include $(TOP)/configure/RULES
