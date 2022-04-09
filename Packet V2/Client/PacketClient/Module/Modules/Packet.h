
#include "Module.h"
class Packet : public IModule {

public:
    bool fourx = false;
    bool multiply = false;
    bool noPacket = false;
    int multipltBy = 2;

    Packet();
    ~Packet();

    std::string name = "Packet";

    // Inherited via IModule
    void onEnable() override;
    bool allowAutoStart() override;
    virtual const char* getModuleName() override;
    virtual const char* getRawModuleName() override;
};