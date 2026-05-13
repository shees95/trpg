cpp trpg_cpp\Inventory.h
#pragma once
#include <string>
#include <vector>
#include <memory>

class Character;
class DBM;
class Potion;

using namespace std;

// A small runtime-polymorphic item model so Inventory can hold different kinds of entries.
// Template-based creation is provided via addImpl<T>(...).
struct ItemBase
{
	virtual ~ItemBase() = default;
	virtual string getName() const = 0;
	virtual int getValue(DBM& db) const = 0;
};

struct GameItem : ItemBase
{
	string Name;
	GameItem(const string& name) : Name(name) {}
	string getName() const override { return Name; }
	int getValue(DBM& db) const override;
};

struct PotionItem : ItemBase
{
	// This wraps a Potion pointer (not owning by default). You can extend to use shared_ptr<Potion>.
	Potion* Ptr;
	string Label;
	PotionItem(Potion* p, const string& label = "Potion") : Ptr(p), Label(label) {}
	string getName() const override { return Label; }
	int getValue(DBM& db) const override;
};

class Inventory 
{
private:
	Character* Owner;

	// store heterogeneous items via ItemBase pointers
	vector<shared_ptr<ItemBase>> Inven;
	int max = 10;
	int Money = 0;

	Potion* PotionBag;

public:
	Inventory(Character* Owner);

	// legacy non-template convenience (keeps previous call site available)
	void addItem(string name);

	// Generic creation helper (template must be defined in header)
	template<typename T, typename... Args>
	void addImpl(Args&&... args)
	{
		// expand before pushing if needed (keeps previous behavior)
		if (Inven.size() >= getMaxSlot())
		{
			expandSlot(getMaxSlot() * 2);
		}

		Inven.push_back(make_shared<T>(std::forward<Args>(args)...));
	}

	void sellItem(int index);
	void expandSlot(int index);

	void setMaxSlot(int max);
	int getMaxSlot() { return max; }
	Potion* getPotion() { return PotionBag; }

	void addMoney(int money);
	void useMoney(int money);
	int getMoney() { return Money; }

	void setPotionBag();
	void setPotionBag(Potion* ptr) { this->PotionBag = ptr; }

	void ShowInventory(DBM& DB);

	// expose basic accessors for code that may need to inspect entries
	size_t size() const { return Inven.size(); }
	shared_ptr<ItemBase> at(size_t i) const { return Inven.at(i); }
};