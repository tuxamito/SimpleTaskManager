#include "thememanager.h"

ThemeManager::ThemeManager()
{
}

ThemeManager::~ThemeManager()
{
}

uint32_t ThemeManager::addTheme(SimpleTheme *theme)
{
    uint32_t nid = theme->id();

    if(nid)
    {
        if(_vui.find(nid) != _vui.end())
        {
            nid = 0;
        }
        else
        {
            _vui.insert(nid);
            _vtd.insert(vtd_t::value_type(nid, theme));
        }
    }

    if(!nid)
    {
        nid = this->getFreeId();
        if(nid)
        {
            theme->setId(nid);
            _vui.insert(nid);
            _vtd.insert(vtd_t::value_type(nid, theme));
        }
    }

    return nid;
}

SimpleTheme *ThemeManager::theme(uint32_t id)
{
    auto elem = _vtd.find(id);
    if(elem != _vtd.end())
    {
        return (*elem).second;
    }

    return NULL;
}

void ThemeManager::removeTheme(SimpleTheme *theme)
{
    this->removeTheme(theme->id());
}

void ThemeManager::removeTheme(uint32_t id)
{
    auto elem = _vtd.find(id);
    if(elem != _vtd.end())
    {
        _vtd.erase(elem);
        _vui.erase(id);
    }
}

uint32_t ThemeManager::getFreeId()
{
    for(uint32_t i = 1; i!=0; i++)
    {
        if(_vui.find(i) == _vui.end())
            return i;
    }

    return 0;
}
