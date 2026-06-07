// Decompiled methods for class: CfgMap
// Source: gameserver.cc
// Total methods: 2

#####################################
bool __cdecl CfgMap::isType(const CfgMap *const this, const MapType *const mt)
{
  return this->type == *mt;
}


#####################################
bool __cdecl CfgMap::isCross(const CfgMap *const this, const CROSS_MAP_TYPE cmt)
{
  return this->cross == cmt;
}


