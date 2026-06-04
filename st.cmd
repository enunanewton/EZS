#!/usr/bin/env softIoc

epicsEnvSet("IOC","iocsysmon")
epicsEnvSet("TOP","../..")

cd "${TOP}"

dbLoadDatabase "dbd/sysmon.dbd"
sysmon_registerRecordDeviceDriver pdbbase

dbLoadRecords "db/sysmon.db"

iocInit
