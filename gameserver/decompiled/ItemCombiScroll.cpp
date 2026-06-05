// Decompiled methods for class: ItemCombiScroll
// Source: gameserver.cc
// Total methods: 3

#####################################
void __cdecl ItemCombiScroll::~ItemCombiScroll(ItemCombiScroll *const this)
{
  ItemCombiScroll::~ItemCombiScroll(this);
  operator delete(this);
}


#####################################
int32_t __cdecl ItemCombiScroll::effect(
        ItemCombiScroll *const this,
        Player *const launcher,
        Unit *const target,
        int32_t *const count)
{
  int32_t m_nId; // ebx
  CExtMagicBox *MagicBox; // rax

  if ( *count <= 0 )
    return 10002;
  m_nId = this->m_nId;
  MagicBox = Player::GetMagicBox(launcher);
  if ( CExtMagicBox::ActiveScroll(MagicBox, m_nId) )
    return 0;
  Player::TiShiInfo(launcher, 13, 0);
  return 10002;
}


#####################################
bool __cdecl ItemCombiScroll::parseEffect(ItemCombiScroll *const this, int32_t id, const std::string *const strEffect)
{
  const char *v3; // rax
  int32_t m_nId; // ebx
  CfgData *v6; // rax
  const CfgItemCombiTable *ItemCombiTable; // rax

  v3 = (const char *)std::string::c_str((std::string *)strEffect);
  this->m_nId = atoi(v3);
  if ( this->m_nId <= 0 )
    return 0;
  m_nId = this->m_nId;
  v6 = Answer::Singleton<CfgData>::instance();
  ItemCombiTable = CfgData::GetItemCombiTable(v6);
  return CfgItemCombiTable::GetItemCombi(ItemCombiTable, m_nId) != 0;
}


