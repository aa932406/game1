// Decompiled methods for class: TileManager
// Source: gameserver.cc
// Total methods: 6

#####################################
void __cdecl TileManager::Init(TileManager *const this)
{
  CfgData *v1; // rax
  int32_t Rdx; // r14d
  const std::pair<const int,CfgMap> *v3; // rax
  int32_t v4; // r12d
  int32_t v5; // r13d
  int32_t id; // ebx
  std::_Rb_tree_const_iterator<std::pair<const int,CfgMap> > it; // [rsp+10h] [rbp-40h] BYREF
  std::_Rb_tree_const_iterator<std::pair<const int,CfgMap> > __x; // [rsp+20h] [rbp-30h] BYREF
  const CfgMapTable *allMaps; // [rsp+28h] [rbp-28h]

  v1 = Answer::Singleton<CfgData>::instance();
  allMaps = CfgData::getMapAll(v1);
  for ( it._M_node = std::map<int,CfgMap>::begin(allMaps)._M_node;
        ;
        std::_Rb_tree_const_iterator<std::pair<int const,CfgMap>>::operator++(&it) )
  {
    __x._M_node = std::map<int,CfgMap>::end(allMaps)._M_node;
    if ( !std::_Rb_tree_const_iterator<std::pair<int const,CfgMap>>::operator!=(&it, &__x) )
      break;
    Rdx = std::_Rb_tree_const_iterator<std::pair<int const,CfgMap>>::operator->(&it)->second.Rdx;
    v3 = std::_Rb_tree_const_iterator<std::pair<int const,CfgMap>>::operator->(&it);
    v4 = roundInt((double)v3->second.height / 17.0);
    v5 = std::_Rb_tree_const_iterator<std::pair<int const,CfgMap>>::operator->(&it)->second.width / 48;
    id = std::_Rb_tree_const_iterator<std::pair<int const,CfgMap>>::operator->(&it)->second.id;
    TileManager::addMap(this, id, v5, v4, Rdx);
  }
}


#####################################
void __cdecl TileManager::addMapTest(
        TileManager *const this,
        int32_t mapid,
        int32_t width,
        int32_t height,
        int32_t Rd,
        int32_t Rdx_0)
{
  std::_Ios_Openmode v6; // eax
  CfgData *v7; // rax
  __int64 v8; // rbx
  __int64 v9; // r12
  Tile *v10; // r13
  __int64 i; // rbx
  Tile **v12; // rax
  std::vector<Position> *v13; // rax
  __int64 v14; // rax
  __int64 v15; // rax
  __int64 v16; // rax
  int32_t mapida; // [rsp+24h] [rbp-26Ch] BYREF
  TileManager *thisa; // [rsp+28h] [rbp-268h]
  _BYTE v23[512]; // [rsp+30h] [rbp-260h] BYREF
  char filename[32]; // [rsp+230h] [rbp-60h] BYREF
  Position __x; // [rsp+250h] [rbp-40h] BYREF
  Tile *pTile; // [rsp+260h] [rbp-30h]
  int32_t x; // [rsp+268h] [rbp-28h]
  int32_t y; // [rsp+26Ch] [rbp-24h]

  thisa = this;
  mapida = mapid;
  memset(filename, 0, 20);
  snprintf(filename, 0x13u, "%d_%d_%d_%d", mapid, width, height, Rd);
  v6 = std::operator|(std::_Ios_Openmode::_S_out, std::_Ios_Openmode::_S_trunc);
  std::ofstream::basic_ofstream(v23, filename, (unsigned int)v6);
  if ( mapid > 0 && width > 0 && height > 0 )
  {
    v7 = Answer::Singleton<CfgData>::instance();
    if ( CfgData::getMap(v7, mapida) )
    {
      v8 = height * width;
      v9 = operator new[](12 * v8 + 8);
      *(_QWORD *)v9 = v8;
      v10 = (Tile *)(v9 + 8);
      for ( i = v8 - 1; i != -1; --i )
        Tile::Tile(v10++);
      pTile = (Tile *)(v9 + 8);
      if ( Rd == 1 )
        TileManager::parseRd(thisa, mapida, width, height, pTile, Rdx_0);
      else
        TileManager::parseRdx(thisa, mapida, width, height, pTile, Rdx_0);
      v12 = std::map<int,Tile *>::operator[](&thisa->m_allTiles, &mapida);
      *v12 = pTile;
      for ( x = 0; x < width; ++x )
      {
        for ( y = 0; y < height; ++y )
        {
          if ( Tile::isWalkable(&pTile[x + width * y]) )
          {
            Position::Position(&__x, x, y);
            v13 = std::map<int,std::vector<Position>>::operator[](&thisa->m_walkablePositions, &mapida);
            std::vector<Position>::push_back(v13, &__x);
            v14 = std::ostream::operator<<(v23, (unsigned int)x);
            v15 = std::operator<<<std::char_traits<char>>(v14, ", ");
            v16 = std::ostream::operator<<(v15, (unsigned int)y);
            std::ostream::operator<<(v16, &std::endl<char,std::char_traits<char>>);
          }
        }
      }
    }
  }
  std::ofstream::~ofstream(v23);
}


#####################################
void __cdecl TileManager::addMap(TileManager *const this, int32_t mapid, int32_t width, int32_t height, int32_t Rdx_0)
{
  CfgData *v5; // rax
  __int64 v6; // rbx
  __int64 v7; // r12
  Tile *v8; // r13
  __int64 i; // rbx
  Tile **v10; // rax
  std::vector<Position> *v11; // rax
  int32_t mapida; // [rsp+14h] [rbp-4Ch] BYREF
  TileManager *thisa; // [rsp+18h] [rbp-48h]
  Position __x; // [rsp+20h] [rbp-40h] BYREF
  CfgMap *pCfg; // [rsp+28h] [rbp-38h]
  Tile *pTile; // [rsp+30h] [rbp-30h]
  int32_t x; // [rsp+38h] [rbp-28h]
  int32_t y; // [rsp+3Ch] [rbp-24h]

  thisa = this;
  mapida = mapid;
  if ( mapid > 0 && width > 0 && height > 0 )
  {
    v5 = Answer::Singleton<CfgData>::instance();
    pCfg = CfgData::getMap(v5, mapida);
    if ( pCfg )
    {
      v6 = height * width;
      v7 = operator new[](12 * v6 + 8);
      *(_QWORD *)v7 = v6;
      v8 = (Tile *)(v7 + 8);
      for ( i = v6 - 1; i != -1; --i )
        Tile::Tile(v8++);
      pTile = (Tile *)(v7 + 8);
      if ( pCfg->hide_mini )
        TileManager::parseRd(thisa, mapida, width, height, pTile, Rdx_0);
      else
        TileManager::parseRdx(thisa, mapida, width, height, pTile, Rdx_0);
      v10 = std::map<int,Tile *>::operator[](&thisa->m_allTiles, &mapida);
      *v10 = pTile;
      for ( x = 0; x < width; ++x )
      {
        for ( y = 0; y < height; ++y )
        {
          if ( Tile::isWalkable(&pTile[x + width * y]) && (x || y) )
          {
            Position::Position(&__x, x, y);
            v11 = std::map<int,std::vector<Position>>::operator[](&thisa->m_walkablePositions, &mapida);
            std::vector<Position>::push_back(v11, &__x);
          }
        }
      }
    }
  }
}


#####################################
bool __cdecl TileManager::isWalkblePosition(
        TileManager *const this,
        int32_t mapid,
        int32_t x,
        int32_t y,
        int32_t wigth)
{
  std::pair<const int,Tile*> *v5; // rax
  int32_t mapida; // [rsp+14h] [rbp-2Ch] BYREF
  TileManager *thisa; // [rsp+18h] [rbp-28h]
  std::_Rb_tree_iterator<std::pair<const int,Tile*> > it; // [rsp+20h] [rbp-20h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,Tile*> > __x; // [rsp+30h] [rbp-10h] BYREF

  thisa = this;
  mapida = mapid;
  it._M_node = std::map<int,Tile *>::find(&this->m_allTiles, &mapida)._M_node;
  __x._M_node = std::map<int,Tile *>::end(&thisa->m_allTiles)._M_node;
  if ( !std::_Rb_tree_iterator<std::pair<int const,Tile *>>::operator!=(&it, &__x) )
    return 0;
  v5 = std::_Rb_tree_iterator<std::pair<int const,Tile *>>::operator->(&it);
  return Tile::isWalkable(&v5->second[x + y * wigth]);
}


#####################################
void __cdecl TileManager::parseRd(
        TileManager *const this,
        int32_t mapid,
        int32_t width,
        int32_t height,
        Tile *pTile,
        int32_t Rdx_0)
{
  int32_t v6; // ecx
  Tile *v7; // rax
  int32_t v8; // ecx
  Tile *v9; // rax
  int32_t v10; // ecx
  Tile *v11; // rax
  int32_t v12; // ecx
  Tile *v13; // rax
  char filename[260]; // [rsp+30h] [rbp-120h] BYREF
  uint32_t destLen; // [rsp+134h] [rbp-1Ch] BYREF
  uint8_t *pDest; // [rsp+138h] [rbp-18h]
  int err; // [rsp+144h] [rbp-Ch]
  int32_t tileIndex; // [rsp+148h] [rbp-8h]
  int32_t i; // [rsp+14Ch] [rbp-4h]

  memset(filename, 0, sizeof(filename));
  snprintf(filename, 0x103u, "map/%d.rd", Rdx_0);
  destLen = height * width / 4 + 1;
  pDest = (uint8_t *)calloc(destLen, 1u);
  err = Answer::Zip::uncompressFile(filename, pDest, &destLen);
  if ( err )
  {
    Answer::Logger::print(Answer::LogLevel::LOG_LEVEL_ERROR, "Map::parseRd uncompressFile return %d\n", err);
    free(pDest);
  }
  else
  {
    tileIndex = 0;
    for ( i = 0; (int)destLen > i && height * width / 4 > i; ++i )
    {
      v6 = pDest[i] & 3;
      v7 = &pTile[tileIndex++];
      Tile::setMask(v7, v6);
      v8 = (pDest[i] & 0xC) >> 2;
      v9 = &pTile[tileIndex++];
      Tile::setMask(v9, v8);
      v10 = (pDest[i] & 0x30) >> 4;
      v11 = &pTile[tileIndex++];
      Tile::setMask(v11, v10);
      v12 = pDest[i] >> 6;
      v13 = &pTile[tileIndex++];
      Tile::setMask(v13, v12);
    }
    free(pDest);
  }
}


#####################################
void __cdecl TileManager::parseRdx(
        TileManager *const this,
        int32_t mapid,
        int32_t width,
        int32_t height,
        Tile *pTile,
        int32_t Rdx_0)
{
  _BYTE v9[256]; // [rsp+30h] [rbp-340h] BYREF
  __int64 v10; // [rsp+130h] [rbp-240h] BYREF
  char filename[264]; // [rsp+240h] [rbp-130h] BYREF
  int32_t mask; // [rsp+348h] [rbp-28h] BYREF
  int32_t depth; // [rsp+34Ch] [rbp-24h] BYREF
  int32_t y; // [rsp+350h] [rbp-20h] BYREF
  int32_t x; // [rsp+354h] [rbp-1Ch] BYREF
  int32_t parent; // [rsp+358h] [rbp-18h] BYREF
  int32_t id[5]; // [rsp+35Ch] [rbp-14h] BYREF

  memset(filename, 0, 260);
  snprintf(filename, 0x103u, "map/%d.rdx", Rdx_0);
  std::ifstream::basic_ifstream(v9, filename, 8);
  if ( (unsigned __int8)std::ifstream::is_open(v9) != 1 )
  {
    Answer::Logger::print(
      Answer::LogLevel::LOG_LEVEL_ERROR,
      "Map::parseRdx failed to open rdx file with mapid = %d\n",
      mapid);
  }
  else
  {
    while ( (unsigned __int8)std::ios::eof(&v10) != 1 )
    {
      id[0] = 0;
      std::istream::operator>>(v9, id);
      parent = 0;
      std::istream::operator>>(v9, &parent);
      x = 0;
      std::istream::operator>>(v9, &x);
      y = 0;
      std::istream::operator>>(v9, &y);
      depth = 0;
      std::istream::operator>>(v9, &depth);
      mask = 0;
      std::istream::operator>>(v9, &mask);
      if ( id[0] >= 0 && height * width > id[0] && parent >= -1 && height * width > id[0] )
        Tile::init(&pTile[id[0]], parent, x, y, depth, mask);
    }
  }
  std::ifstream::~ifstream(v9);
}


