// Decompiled: initLogger(const char *prefix, Answer
// Source: gameserver.cc

#####################################
void __cdecl initLogger(const char *prefix, Answer::LogLevel leve)
{
  int Pid; // eax
  char szFile[272]; // [rsp+40h] [rbp-160h] BYREF
  tm time; // [rsp+150h] [rbp-50h] BYREF

  memset(szFile, 0, 260);
  mkDir("log");
  Answer::DayTime::localnow(&time);
  Pid = getPid();
  snprintf(
    szFile,
    0x103u,
    "log/%s.%d.%d.%d.%d.%d.%d.%d.log",
    prefix,
    time.tm_year + 1900,
    time.tm_mon + 1,
    time.tm_mday,
    time.tm_hour,
    time.tm_min,
    time.tm_sec,
    Pid);
  Answer::Logger::open(szFile, "a");
  Answer::Logger::setLogLevel(leve);
}


