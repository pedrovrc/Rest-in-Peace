#ifndef ENEMY_H_
#define ENEMY_H_

#define ENEMY_MAX_HP 20

class Enemy {
public:
	Enemy();
	~Enemy();
	void TurnAction();
	void TakeDamage(int dmg_amount);
	int GetHP();

private:
	int hp;
};



#endif
