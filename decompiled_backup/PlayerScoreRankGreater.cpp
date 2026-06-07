// Decompiled methods for class: PlayerScoreRankGreater
// Source: gameserver.cc
// Total methods: 1

#####################################
bool __cdecl PlayerScoreRankGreater::operator()(
        const PlayerScoreRankGreater *const this,
        const PlayerScore *_Left,
        const PlayerScore *_Right)
{
  return _Left && _Right && _Left->nDamage > _Right->nDamage;
}


