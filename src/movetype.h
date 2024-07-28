#ifndef MOVETYPE_H
#define MOVETYPE_H
enum class MoveType {
    MoveOrAttack,
    MoveOnly,
    AttackOnly,
    UnblockableMoveOrAttack,
    Teleport,             // extra
    UnblockableAttackOnly // extra
};
#endif
