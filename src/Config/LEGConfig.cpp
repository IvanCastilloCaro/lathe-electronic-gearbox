#include <Config/LEGConfig.h> 

LEGConfig* LEGConfig::m_legconfig = nullptr; 

LEGConfig* LEGConfig::getInstance() {
    if (m_legconfig == nullptr)
    {
        m_legconfig = new LEGConfig();
    }
    return m_legconfig;
}

LEGConfig::LEGConfig() : ConfigHandler() {}