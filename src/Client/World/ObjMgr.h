#ifndef _OBJMGR_H
#define _OBJMGR_H

#include "common.h"
#include <set>
#include "Item.h"
#include "Unit.h"

typedef std::map<uint32,ItemProto*> ItemProtoMap;
typedef std::map<uint32,CreatureTemplate*> CreatureTemplateMap;
typedef std::map<uint64,Object*> ObjectMap;

class PseuInstance;

class ObjMgr
{
public:
    ObjMgr();
    ~ObjMgr();
    void SetInstance(PseuInstance*);
    void RemoveAll(void); // TODO: this needs to be called on SMSG_LOGOUT_COMPLETE once implemented.

    // Item Prototype functions
    uint32 GetItemProtoCount(void) { return _iproto.size(); }
    ItemProto *GetItemProto(uint32);
    void Add(ItemProto*);
    ItemProtoMap *GetItemProtoStorage(void) { return &_iproto; }

    // nonexistent items handler
    void AddNonexistentItem(uint32);
    bool ItemNonExistent(uint32);

    // Creature template functions
    uint32 GetCreatureTemplateCount(void) { return _creature_templ.size(); }
    CreatureTemplate *GetCreatureTemplate(uint32);
    void Add(CreatureTemplate*);
    CreatureTemplateMap *GetCreatureTemplateStorage(void) { return &_creature_templ; }

    // nonexistent creatures handler
    void AddNonexistentCreature(uint32);
    bool CreatureNonExistent(uint32);

    // player names related
    void AddRequestedPlayerGUID(uint32);
    bool IsRequestedPlayerGUID(uint32);
    inline void AddRequestedPlayerGUID(uint64 guid) { AddRequestedPlayerGUID(GUID_LOPART(guid)); }
    inline bool IsRequestedPlayerGUID(uint64 guid) { return IsRequestedPlayerGUID(GUID_LOPART(guid)); }


    // Object functions
    void Add(Object*);
    void Remove(uint64); // remove all objects with that guid (should be only 1 object in total anyway)
    Object *GetObj(uint64 guid);
    inline uint32 GetObjectCount(void) { return _obj.size(); }
    uint32 AssignNameToObj(uint32 entry, uint8 type, std::string name);

private:
    ItemProtoMap _iproto;
    CreatureTemplateMap _creature_templ;
    ObjectMap _obj;
    std::set<uint32> _noitem;
    std::set<uint32> _reqpnames;
    std::set<uint32> _nocreature;
    PseuInstance *_instance;

};

#endif
