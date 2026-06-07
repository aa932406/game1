// Decompiled methods for class: CfgMapRoadTable
// Source: gameserver.cc
// Total methods: 1

#####################################
void __cdecl CfgMapRoadTable::Add(CfgMapRoadTable *const this, const CfgMapRoad *const road)
{
  CfgMapRoad *v2; // rax

  v2 = std::map<int,CfgMapRoad>::operator[](&this->m_mMapRoad, &road->nIndex);
  CfgMapRoad::operator=(v2, road);
}


