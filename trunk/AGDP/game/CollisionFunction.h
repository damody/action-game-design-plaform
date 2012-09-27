#pragma once
#include <game\Attack.h>
#include <game\Body.h>
#include <game\CatchInfo.h>

bool Collision_Attack_Body(const Attack& a, const Body& b);
bool Collision_Attack_Bodys(const Attack& a, const Bodys& b);
bool Collision_CatchInfo_Body(const CatchInfo& a, const Body& b);
bool Collision_CatchInfo_Bodys(const CatchInfo& a, const Bodys& b);
bool Collision_Body_Attack(const Body& a, const Attack& b);
bool Collision_Body_Attacks(const Body& a, const Attacks& b);
bool Collision_Body_CatchInfo(const Body& a, const CatchInfo& b);
bool Collision_Body_CatchInfos(const Body& a, const CatchInfos& b);

