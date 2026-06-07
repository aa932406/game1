// Decompiled methods for class: ItemEffectManager
// Source: gameserver.cc
// Total methods: 2

#####################################
void __cdecl ItemEffectManager::init(ItemEffectManager *const this)
{
  CfgData *v1; // rax
  ShunJianHuiXue *v2; // rbx
  Jingyandan *v3; // rbx
  MoneyGain *v4; // rbx
  LiBao *v5; // rbx
  SuiJiLiBao *v6; // rbx
  SuperExchange *v7; // rbx
  ItemAddBuff *v8; // rbx
  EnterDungeon *v9; // rbx
  CurrencyRes *v10; // rbx
  FamilyLightWine *v11; // rbx
  UpLevel *v12; // rbx
  JiuShuCard *v13; // rbx
  RandomBuff *v14; // rbx
  CDaZheQuan *v15; // rbx
  GoldEgg *v16; // rbx
  TitleCard *v17; // rbx
  RechargeCard *v18; // rbx
  RechargeValueCard *v19; // rbx
  FamilyMemberCard *v20; // rbx
  SummonBoss *v21; // rbx
  BackCityPaper *v22; // rbx
  RandomPosPaper *v23; // rbx
  ItemCombiPoint *v24; // rbx
  ItemCombiScroll *v25; // rbx
  EquipBox *v26; // rbx
  FaBaoRes *v27; // rbx
  SkillPointBook *v28; // rbx
  SkillBook *v29; // rbx
  BlessWater1 *v30; // rbx
  BlessWater2 *v31; // rbx
  JewelPavilion *v32; // rbx
  AddStarVipTime *v33; // rbx
  PetShiHua *v34; // rbx
  PetAtkSpd *v35; // rbx
  SuperCurse *v36; // rbx
  WingLevelUp *v37; // rbx
  UseCurrGift *v38; // rbx
  UseItemGift *v39; // rbx
  ChongZhiGift *v40; // rbx
  GoblinItem *v41; // rbx
  ShiZhuang *v42; // rbx
  OreItem *v43; // rbx
  MingGeChip *v44; // rbx
  MingGeItem *v45; // rbx
  MingGeExp *v46; // rbx
  LingZhu *v47; // rbx
  VipDrop *v48; // rbx
  GongMingZhi *v49; // rbx
  YanHua *v50; // rbx
  BackCityPaper *v51; // rbx
  XinMoExp *v52; // rbx
  LittleHelperCard *v53; // rbx
  ShouChongItem *v54; // rbx
  unsigned __int8 (__fastcall *v55)(ItemEffect *, _QWORD, std::string *); // rbx
  std::string *p_effect; // r12
  const std::pair<const int,CfgItem*> *v57; // rax
  const std::pair<const int,CfgItem*> *v59; // rax
  CfgItemTable items; // [rsp+20h] [rbp-D0h] BYREF
  ItemEffect *itemEffect; // [rsp+58h] [rbp-98h] BYREF
  std::_Rb_tree_const_iterator<std::pair<const int,CfgItem*> > it; // [rsp+60h] [rbp-90h] BYREF
  Answer::RwLockWrGuard lock; // [rsp+70h] [rbp-80h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,CfgItem*> > __it; // [rsp+80h] [rbp-70h] BYREF
  std::_Rb_tree_const_iterator<std::pair<const int,CfgItem*> > v65; // [rsp+90h] [rbp-60h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,CfgItem*> > v66; // [rsp+A0h] [rbp-50h] BYREF
  std::pair<std::_Rb_tree_iterator<std::pair<const int,ItemEffect*> >,bool> v67; // [rsp+B0h] [rbp-40h]
  std::pair<const int,ItemEffect*> __x; // [rsp+C0h] [rbp-30h] BYREF

  v1 = Answer::Singleton<CfgData>::instance();
  CfgData::getAllItem(&items, v1);
  Answer::RwLockWrGuard::RwLockWrGuard(&lock, &this->m_itemEffectsLock);
  std::map<int,ItemEffect *>::clear(&this->m_itemEffects);
  __it._M_node = std::map<int,CfgItem *>::begin(&items)._M_node;
  std::_Rb_tree_const_iterator<std::pair<int const,CfgItem *>>::_Rb_tree_const_iterator(&it, &__it);
  while ( 1 )
  {
    v66._M_node = std::map<int,CfgItem *>::end(&items)._M_node;
    std::_Rb_tree_const_iterator<std::pair<int const,CfgItem *>>::_Rb_tree_const_iterator(&v65, &v66);
    if ( !std::_Rb_tree_const_iterator<std::pair<int const,CfgItem *>>::operator!=(&it, &v65) )
      break;
    itemEffect = 0;
    switch ( std::_Rb_tree_const_iterator<std::pair<int const,CfgItem *>>::operator->(&it)->second->type )
    {
      case 1:
        v4 = (MoneyGain *)operator new(0x18u);
        MoneyGain::MoneyGain(v4);
        itemEffect = v4;
        break;
      case 2:
      case 0x4C:
      case 0x4D:
      case 0x4E:
      case 0x4F:
        v8 = (ItemAddBuff *)operator new(0x20u);
        ItemAddBuff::ItemAddBuff(v8);
        itemEffect = v8;
        break;
      case 3:
        v2 = (ShunJianHuiXue *)operator new(0x10u);
        ShunJianHuiXue::ShunJianHuiXue(v2);
        itemEffect = v2;
        break;
      case 0x18:
        v3 = (Jingyandan *)operator new(0x10u);
        Jingyandan::Jingyandan(v3);
        itemEffect = v3;
        break;
      case 0x1D:
        v5 = (LiBao *)operator new(0x28u);
        LiBao::LiBao(v5);
        itemEffect = v5;
        break;
      case 0x48:
        v6 = (SuiJiLiBao *)operator new(0x28u);
        SuiJiLiBao::SuiJiLiBao(v6);
        itemEffect = v6;
        break;
      case 0x4A:
        v48 = (VipDrop *)operator new(0x10u);
        VipDrop::VipDrop(v48);
        itemEffect = v48;
        break;
      case 0x4B:
        v7 = (SuperExchange *)operator new(0x28u);
        SuperExchange::SuperExchange(v7);
        itemEffect = v7;
        break;
      case 0x52:
        v10 = (CurrencyRes *)operator new(0x18u);
        CurrencyRes::CurrencyRes(v10);
        itemEffect = v10;
        break;
      case 0x56:
      case 0x57:
        v49 = (GongMingZhi *)operator new(0x10u);
        GongMingZhi::GongMingZhi(v49);
        itemEffect = v49;
        break;
      case 0x60:
        v22 = (BackCityPaper *)operator new(0x10u);
        BackCityPaper::BackCityPaper(v22, 0);
        itemEffect = v22;
        break;
      case 0x61:
        v23 = (RandomPosPaper *)operator new(0x10u);
        RandomPosPaper::RandomPosPaper(v23);
        itemEffect = v23;
        break;
      case 0x62:
        v27 = (FaBaoRes *)operator new(0x10u);
        FaBaoRes::FaBaoRes(v27);
        itemEffect = v27;
        break;
      case 0x67:
        v9 = (EnterDungeon *)operator new(0x10u);
        EnterDungeon::EnterDungeon(v9);
        itemEffect = v9;
        break;
      case 0x69:
        v11 = (FamilyLightWine *)operator new(0x18u);
        FamilyLightWine::FamilyLightWine(v11);
        itemEffect = v11;
        break;
      case 0x6A:
        v12 = (UpLevel *)operator new(0x18u);
        UpLevel::UpLevel(v12);
        itemEffect = v12;
        break;
      case 0x6B:
        v29 = (SkillBook *)operator new(0x10u);
        SkillBook::SkillBook(v29);
        itemEffect = v29;
        break;
      case 0x6C:
        v28 = (SkillPointBook *)operator new(0x18u);
        SkillPointBook::SkillPointBook(v28);
        itemEffect = v28;
        break;
      case 0x87:
        v13 = (JiuShuCard *)operator new(0x10u);
        JiuShuCard::JiuShuCard(v13);
        itemEffect = v13;
        break;
      case 0x8E:
        v14 = (RandomBuff *)operator new(0x20u);
        RandomBuff::RandomBuff(v14);
        itemEffect = v14;
        break;
      case 0x8F:
        v15 = (CDaZheQuan *)operator new(0x10u);
        CDaZheQuan::CDaZheQuan(v15);
        itemEffect = v15;
        break;
      case 0x96:
        v16 = (GoldEgg *)operator new(0x10u);
        GoldEgg::GoldEgg(v16);
        itemEffect = v16;
        break;
      case 0x9B:
        v30 = (BlessWater1 *)operator new(0x10u);
        BlessWater1::BlessWater1(v30);
        itemEffect = v30;
        break;
      case 0x9C:
        v31 = (BlessWater2 *)operator new(0x10u);
        BlessWater2::BlessWater2(v31);
        itemEffect = v31;
        break;
      case 0xA9:
        v42 = (ShiZhuang *)operator new(0x18u);
        ShiZhuang::ShiZhuang(v42);
        itemEffect = v42;
        break;
      case 0xAC:
        v18 = (RechargeCard *)operator new(0x10u);
        RechargeCard::RechargeCard(v18);
        itemEffect = v18;
        break;
      case 0xAD:
        v20 = (FamilyMemberCard *)operator new(0x10u);
        FamilyMemberCard::FamilyMemberCard(v20);
        itemEffect = v20;
        break;
      case 0xB0:
        v21 = (SummonBoss *)operator new(0x18u);
        SummonBoss::SummonBoss(v21);
        itemEffect = v21;
        break;
      case 0xB3:
        v19 = (RechargeValueCard *)operator new(0x10u);
        RechargeValueCard::RechargeValueCard(v19);
        itemEffect = v19;
        break;
      case 0xBE:
        v24 = (ItemCombiPoint *)operator new(0x10u);
        ItemCombiPoint::ItemCombiPoint(v24);
        itemEffect = v24;
        break;
      case 0xBF:
        v25 = (ItemCombiScroll *)operator new(0x10u);
        ItemCombiScroll::ItemCombiScroll(v25);
        itemEffect = v25;
        break;
      case 0xC2:
        v26 = (EquipBox *)operator new(0x10u);
        EquipBox::EquipBox(v26);
        itemEffect = v26;
        break;
      case 0xC8:
        v32 = (JewelPavilion *)operator new(8u);
        JewelPavilion::JewelPavilion(v32);
        itemEffect = v32;
        break;
      case 0xC9:
        v33 = (AddStarVipTime *)operator new(0x10u);
        AddStarVipTime::AddStarVipTime(v33);
        itemEffect = v33;
        break;
      case 0xCA:
        v34 = (PetShiHua *)operator new(0x10u);
        PetShiHua::PetShiHua(v34);
        itemEffect = v34;
        break;
      case 0xCB:
        v35 = (PetAtkSpd *)operator new(0x10u);
        PetAtkSpd::PetAtkSpd(v35);
        itemEffect = v35;
        break;
      case 0xCC:
        v36 = (SuperCurse *)operator new(0x10u);
        SuperCurse::SuperCurse(v36);
        itemEffect = v36;
        break;
      case 0xCD:
        v37 = (WingLevelUp *)operator new(0x18u);
        WingLevelUp::WingLevelUp(v37);
        itemEffect = v37;
        break;
      case 0xCE:
        v38 = (UseCurrGift *)operator new(0x18u);
        UseCurrGift::UseCurrGift(v38);
        itemEffect = v38;
        break;
      case 0xCF:
        v39 = (UseItemGift *)operator new(0x18u);
        UseItemGift::UseItemGift(v39);
        itemEffect = v39;
        break;
      case 0xD0:
        v40 = (ChongZhiGift *)operator new(0x10u);
        ChongZhiGift::ChongZhiGift(v40);
        itemEffect = v40;
        break;
      case 0xD1:
        v41 = (GoblinItem *)operator new(0x10u);
        GoblinItem::GoblinItem(v41);
        itemEffect = v41;
        break;
      case 0xD2:
        v17 = (TitleCard *)operator new(0x10u);
        TitleCard::TitleCard(v17);
        itemEffect = v17;
        break;
      case 0xDB:
        v43 = (OreItem *)operator new(0x10u);
        OreItem::OreItem(v43);
        itemEffect = v43;
        break;
      case 0xDD:
        v44 = (MingGeChip *)operator new(0x10u);
        MingGeChip::MingGeChip(v44);
        itemEffect = v44;
        break;
      case 0xDE:
        v45 = (MingGeItem *)operator new(0x10u);
        MingGeItem::MingGeItem(v45);
        itemEffect = v45;
        break;
      case 0xDF:
        v46 = (MingGeExp *)operator new(0x10u);
        MingGeExp::MingGeExp(v46);
        itemEffect = v46;
        break;
      case 0xE0:
        v47 = (LingZhu *)operator new(0x10u);
        LingZhu::LingZhu(v47);
        itemEffect = v47;
        break;
      case 0xE2:
        v50 = (YanHua *)operator new(0x18u);
        YanHua::YanHua(v50);
        itemEffect = v50;
        break;
      case 0xE3:
        v51 = (BackCityPaper *)operator new(0x10u);
        BackCityPaper::BackCityPaper(v51, 1);
        itemEffect = v51;
        break;
      case 0xE4:
        v52 = (XinMoExp *)operator new(0x10u);
        XinMoExp::XinMoExp(v52);
        itemEffect = v52;
        break;
      case 0xE6:
        v53 = (LittleHelperCard *)operator new(0x18u);
        LittleHelperCard::LittleHelperCard(v53);
        itemEffect = v53;
        break;
      case 0xE7:
        v54 = (ShouChongItem *)operator new(0x10u);
        ShouChongItem::ShouChongItem(v54);
        itemEffect = v54;
        break;
      default:
        break;
    }
    if ( itemEffect )
    {
      v55 = (unsigned __int8 (__fastcall *)(ItemEffect *, _QWORD, std::string *))*((_QWORD *)itemEffect->_vptr_ItemEffect
                                                                                 + 3);
      p_effect = &std::_Rb_tree_const_iterator<std::pair<int const,CfgItem *>>::operator->(&it)->second->effect;
      v57 = std::_Rb_tree_const_iterator<std::pair<int const,CfgItem *>>::operator->(&it);
      if ( v55(itemEffect, v57->second->id, p_effect) )
      {
        v59 = std::_Rb_tree_const_iterator<std::pair<int const,CfgItem *>>::operator->(&it);
        std::pair<int const,ItemEffect *>::pair(&__x, &v59->second->id, &itemEffect);
        v67 = std::map<int,ItemEffect *>::insert(&this->m_itemEffects, &__x);
      }
    }
    std::_Rb_tree_const_iterator<std::pair<int const,CfgItem *>>::operator++(&it);
  }
  Answer::RwLockWrGuard::~RwLockWrGuard(&lock);
  std::map<int,CfgItem *>::~map(&items);
}


#####################################
int32_t __cdecl ItemEffectManager::effect(
        ItemEffectManager *const this,
        int32_t itemid,
        Player *const launcher,
        Unit *const target,
        int32_t *const count)
{
  int32_t v5; // ebx
  std::pair<const int,ItemEffect*> *v6; // rax
  int32_t itemida; // [rsp+24h] [rbp-4Ch] BYREF
  ItemEffectManager *thisa; // [rsp+28h] [rbp-48h]
  std::_Rb_tree_iterator<std::pair<const int,ItemEffect*> > it; // [rsp+30h] [rbp-40h] BYREF
  Answer::RwLockRdGuard lock; // [rsp+40h] [rbp-30h] BYREF
  std::_Rb_tree_iterator<std::pair<const int,ItemEffect*> > __x; // [rsp+50h] [rbp-20h] BYREF

  thisa = this;
  itemida = itemid;
  Answer::RwLockRdGuard::RwLockRdGuard(&lock, &this->m_itemEffectsLock);
  it._M_node = std::map<int,ItemEffect *>::find(&this->m_itemEffects, &itemida)._M_node;
  __x._M_node = std::map<int,ItemEffect *>::end(&thisa->m_itemEffects)._M_node;
  if ( std::_Rb_tree_iterator<std::pair<int const,ItemEffect *>>::operator==(&it, &__x) )
  {
    v5 = 10002;
  }
  else
  {
    v6 = std::_Rb_tree_iterator<std::pair<int const,ItemEffect *>>::operator->(&it);
    v5 = (*((__int64 (__fastcall **)(ItemEffect *, Player *const, Unit *const, int32_t *const))v6->second->_vptr_ItemEffect
          + 2))(
           v6->second,
           launcher,
           target,
           count);
  }
  Answer::RwLockRdGuard::~RwLockRdGuard(&lock);
  return v5;
}


