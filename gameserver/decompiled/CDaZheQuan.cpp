// Decompiled methods for class: CDaZheQuan
// Source: gameserver.cc
// Total methods: 3

#####################################
void __cdecl CDaZheQuan::~CDaZheQuan(CDaZheQuan *const this)
{
  CDaZheQuan::~CDaZheQuan(this);
  operator delete(this);
}


#####################################
int32_t __cdecl CDaZheQuan::effect(
        CDaZheQuan *const this,
        Player *const launcher,
        Unit *const target,
        int32_t *const count)
{
  int32_t Index; // ebx
  CfgData *v5; // rax
  CExtCharBag *Bag; // rax
  int32_t FreeSlotCount; // ebx
  CExtCharBag *v9; // rax
  DaZheQuan *pCfg; // [rsp+28h] [rbp-18h]

  Index = this->Index;
  v5 = Answer::Singleton<CfgData>::instance();
  pCfg = CfgData::GetDaZheQuanCfg(v5, Index);
  if ( !pCfg )
    return 10002;
  if ( pCfg->CurrencyValues <= 0 )
    return 10002;
  Bag = Player::GetBag(launcher);
  FreeSlotCount = CExtCharBag::GetFreeSlotCount(Bag);
  if ( FreeSlotCount < (int)std::vector<MemChrBag>::size(&pCfg->Items) )
    return 10002;
  if ( !Player::DecCurrency(
          launcher,
          (const CURRENCY_TYPE)pCfg->CurrencyType,
          pCfg->CurrencyValues,
          CURRENCY_CHANGE_REASON::GCR_DA_ZHE_QUAN,
          0) )
    return 10002;
  v9 = Player::GetBag(launcher);
  if ( !CExtCharBag::AddItem(v9, &pCfg->Items, ITEM_CHANGE_REASON::ICR_DA_ZHE_QUAN) )
    return 10002;
  else
    return 0;
}


#####################################
bool __cdecl CDaZheQuan::parseEffect(CDaZheQuan *const this, int32_t id, const std::string *const strEffect)
{
  const char *v3; // rax

  v3 = (const char *)std::string::c_str((std::string *)strEffect);
  this->Index = atoi(v3);
  return this->Index > 0;
}


