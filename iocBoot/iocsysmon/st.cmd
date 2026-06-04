#!/usr/bin/env softIoc


epicsEnvSet("IOC","iocsysmon")
epicsEnvSet("TOP","/Users/enwa8233/hrz_data/EZS")

cd "${TOP}"

dbLoadDatabase "dbd/sysmon.dbd"
sysmon_registerRecordDeviceDriver pdbbase

dbLoadRecords "db/sysmon.db"

iocInit
