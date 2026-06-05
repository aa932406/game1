// Decompiled methods for class: Tile
// Source: gameserver.cc
// Total methods: 2

#####################################
bool __cdecl Tile::isWalkable(Tile *const this)
{
  return !this->m_mask || this->m_mask == 2;
}


#####################################
void __cdecl Tile::init(Tile *const this, int32_t parent, int32_t x, int32_t y, int32_t depth, int32_t mask)
{
  this->m_parent = parent;
  this->m_x = x;
  this->m_y = y;
  this->m_depth = depth;
  this->m_mask = mask;
}


