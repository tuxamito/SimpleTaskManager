#ifndef THEMEMANAGER_H
#define THEMEMANAGER_H

#include <unordered_set>

#include "simpletaskcommon.h"
#include "simpletheme.h"

class ThemeManager
{
public:
    ThemeManager();
    ~ThemeManager();

    uint32_t addTheme(SimpleTheme *theme);
    SimpleTheme *theme(uint32_t id);
    void removeTheme(SimpleTheme *theme);
    void removeTheme(uint32_t id);

private:
    uint32_t getFreeId();

    vtd_t _vtd;
    unordered_set<uint32_t> _vui;
};

#endif // THEMEMANAGER_H
