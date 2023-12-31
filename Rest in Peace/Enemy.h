#ifndef ENEMY_H_
#define ENEMY_H_

#define ENEMY_MAX_HP 20

class Enemy {
public:
	Enemy();
	~Enemy();
	void TurnAction();
	void TakeDamage(int dmg_amount);
	void ApplyFreeze(int val);
	void ApplyWeakness(int val);
	void ApplPermayWeakness(int val);
	int GetHP();
	int GetFreeze();
	int GetWeakness();

private:
	int hp;
	int freezeAmount;
	int weaknessAmount;
	int weaknessAmountPerma;
};



#endif
