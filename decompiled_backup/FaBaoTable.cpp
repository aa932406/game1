// Decompiled methods for class: FaBaoTable
// Source: gameserver.cc
// Total methods: 1

#####################################
void __cdecl FaBaoTable::AddFaBao(FaBaoTable *const this, int8_t Type, CfgFaBao *const Stu)
{
  CfgFaBao *v3; // rax

  if ( IsFaBaoType(Type) )
  {
    v3 = std::map<int,CfgFaBao>::operator[](&this->m_CfgFaBao[Type], &Stu->FaBaoLevel);
    CfgFaBao::operator=(v3, Stu);
  }
}


