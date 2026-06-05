// Decompiled methods for class: PathFinder
// Source: gameserver.cc
// Total methods: 2

#####################################
int32_t __cdecl PathFinder::gValue(PathFinder *const this, Node *pSrc, Position dest)
{
  if ( pSrc->pos.y == dest.y )
    return pSrc->g + 10;
  if ( pSrc->pos.y + 2 == dest.y || pSrc->pos.y - 2 == dest.y )
    return pSrc->g + 20;
  return pSrc->g + 14;
}


#####################################
int32_t __cdecl PathFinder::hValue(PathFinder *const this, Position src, Position dest)
{
  return abs32(10 * src.x + 10 * (src.y & 1) / 2 - (10 * dest.x + 10 * (dest.y & 1) / 2)) + 10 * abs32(src.y - dest.y);
}


