#ifndef SIMPLETASKCOMMON_H
#define SIMPLETASKCOMMON_H

#include <cstdint>
#include <unordered_map>
#include <list>

using namespace std;

class SimpleTask;
class SimpleTaskManager;

enum STDoneType {NOTDONE, DONE};

typedef unordered_map<uint32_t,SimpleTask*> vst_t;
typedef list<SimpleTask*> lst_t;

#endif // SIMPLETASKCOMMON_H
