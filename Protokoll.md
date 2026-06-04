# Protokoll — EPICS aSub SCAN Übungsaufgabe


**Modul:** Echtzeitsysteme · 3. Semester · BHT Berlin
**Name:** ENUNA WAFO SIETOK
**Matrikelnr.:** 109720
**Datum:** 04.06.2026


---

## 1. Systemumgebung

| Parameter    | Wert             |
|--------------|------------------|
| OS           | macOS darwin-aarch64 |
| EPICS Base   | R7.0.9           |
| CPUs         | 8                |
| RAM          | 16 GiB           |


---

## 2. PV-Werte (caget)
caget SYS:LOAD1 SYS:LOAD5 SYS:LOAD15 SYS:NCPUS SYS:MEMTOTAL SYS:UPTIME

Ergebnis:

SYS:LOAD1       1.64062
SYS:LOAD5       1.67725
SYS:LOAD15      1.5874
SYS:NCPUS       8
SYS:MEMTOTAL    16
SYS:UPTIME      72953

Alle Werte plausibel:
- Load averages im Bereich 0...8 (= nCPU)
- NCPUS = 8 korrekt
- MEMTOTAL = 16 GiB korrekt
- UPTIME > 0



---

## 3. SCAN-Verhalten (camonitor)

Befehl:

camonitor SYS:LOAD1 SYS:UPTIME | tee camonitor.log

Auszug (46 Sekunden Aufzeichnung):

SYS:LOAD1   2026-06-05 01:22:48.218416  1.5249
SYS:UPTIME  2026-06-05 01:22:48.218426  73349
SYS:LOAD1   2026-06-05 01:22:50.216426  1.5625
SYS:UPTIME  2026-06-05 01:22:50.216455  73351
...
SYS:UPTIME  2026-06-05 01:23:34.209279  73395



---

## 4. Auswertung der Periode

Aufzeichnungsdauer: 01:23:34 - 01:22:48 = 46 Sekunden
Anzahl UPTIME-Updates: 23

Mittlere Periode:
T_mittel = 46 s / 23 = 2.000 s

Sollwert: 2.000 s (SCAN = "2 second")
Abweichung: < 1 ms


---

## 5. Jitter-Ursachen

In den Zeitstempeln sind kleine Schwankungen von +/- 2-8 ms erkennbar.

**Scheduler-Jitter:**
macOS ist kein Echtzeit-Betriebssystem. Der EPICS-Timer-Thread
konkurriert mit anderen Prozessen um CPU-Zeit und kann vom
Kernel-Scheduler um wenige Millisekunden verzögert werden.

**Channel Access Overhead:**
Die Zeitstempel werden nach der CA-Übertragung gesetzt.
Netzwerk- und Socket-Latenz (localhost) addieren einen
variablen Overhead von typisch 1-5 ms.

**Fazit:**
Für nicht-zeitkritische Anwendungen wie Systemmonitoring
ist der Jitter akzeptabel. Für harte Echtzeit wäre ein
RTOS oder I/O Intr SCAN notwendig.



---

## 6. Bonusaufgaben

### B2 — SYS:LOAD_WARN

In sysmon.db implementiert:

record(calc, "SYS:LOAD_WARN") {
    field(INPA, "SYS:LOAD1 CP")
    field(INPB, "SYS:NCPUS CP")
    field(CALC, "A>B")
}

Liefert 1 wenn SYS:LOAD1 > SYS:NCPUS, sonst 0.

### B3 — Fehlerbehandlung

Alle sysctlbyname()- und getloadavg()-Aufrufe prüfen
den Rückgabewert und loggen Fehler via epicsPrintf().


