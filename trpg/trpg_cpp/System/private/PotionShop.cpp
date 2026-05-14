#include "../public/PotionShop.h"

#include "../../Character/public/Character.h"
#include "../../UI/public/BaseUI.h"
#include "../public/DBM.h"

PotionShop::PotionShop()
	: inventory(this)
{
	Init();
}

void PotionShop::ShowShopBuyUI(Character& Buyer)
{
	ShowShopInventory();
	
	BaseUI::Print_ln("Want some?");
	int selection = BaseUI::Print_Choice_Number(0, inventory.GetMaxSlot());
	if (selection == 0) return;
	
	ShopBuy(Buyer, selection);
}

void PotionShop::ShowShopInventory()
{
	int i = 1;
	for (ItemBase& item : inventory.GetInven())
	{
		if (item.GetStack() > 0)
		{
			BaseUI::Print_ln(to_string(i) + ". " + item.GetItemName() + " [" + to_string(item.GetStack()) + "] (" + to_string(item.GetPrice()) + "G)");
		}
		else
		{
			BaseUI::Print_ln(to_string(i) + ". " + item.GetItemName() + " [Out of Stock]");
		}
		
		i++;
	}
	
	BaseUI::Print_ln();
}

void PotionShop::ShopBuy(Character& Buyer, const int& index)
{
	// 재고 있음
	if (inventory.GetInven(index - 1).GetStack() > 0)
	{
		Buyer.GetInventory().AddItem(inventory.GetInven(index - 1).GetItemInfo());
		inventory.GetInven(index - 1).SubItem(1);
		
	}
}


void PotionShop::Init()
{
	inventory.AddItems(DBM::GetItemFromName("HP Potion"), 5);
	inventory.AddItems(DBM::GetItemFromName("MP Potion"), 5);
	
	Recipes.emplace_back(
		"HP Potion",
		vector<Ingredient>
		{
			{ "Herb", 1 },
			{ "Clear Water" , 1 }
		}
		
	);

	Recipes.emplace_back(
		"MP Potion",
		vector<Ingredient>
		{
			{ "Herb", 1 },
			{ "Berry" , 1 }
		}

	);
}

void PotionShop::ShowAllRecipes()
{
	BaseUI::Print_ln();
	for (PotionRecipe pr : Recipes)
	{
		BaseUI::Print("-> " + pr.name + ": ");
		ShowIngredients(pr.ingredient);
		BaseUI::Print_ln();
	}
	BaseUI::Print_ln();
}

void PotionShop::ShowIngredients(vector<Ingredient> ingredients)
{
	int index = 1;
	for (Ingredient ingredient : ingredients)
	{
		
		ShowIngredient(ingredient);
		if (ingredients.size() >= ++index) BaseUI::Print(", ");
	}
}

void PotionShop::ShowIngredient(Ingredient ingredient)
{
	BaseUI::Print(ingredient.name + " x" + to_string(ingredient.amount));
}

void PotionShop::SearchByName(string name, bool isCorrect)
{
	bool isFind = false;
	int CntFoundRecipes = 0;

	BaseUI::Print_ln();
	for (const PotionRecipe& pr : Recipes)
	{
		if (pr.name.find(name) != string::npos)
		{
			BaseUI::Print("-> " + pr.name + ": ");
			ShowIngredients(pr.ingredient);
			BaseUI::Print_ln();

			isFind = true;
			CntFoundRecipes++;
		}
	}
	BaseUI::Print_ln("Found " + to_string(CntFoundRecipes) + " Recipes");
	BaseUI::Print_ln();

	if (!isFind)
	{
		BaseUI::Print_ln("* Search Fail");
	}
}

void PotionShop::SearchByIngredient(string ingredient, bool isCorrect)
{
	bool isFind = false;
	int CntFoundRecipes = 0;

	BaseUI::Print_ln();
	for (const PotionRecipe& pr : Recipes)
	{
		for (const Ingredient& ingrd : pr.ingredient)
		{
			if (ingrd.name.find(ingredient) != string::npos)
			{
				BaseUI::Print("-> " + pr.name + ": ");
				ShowIngredients(pr.ingredient);
				BaseUI::Print_ln();

				isFind = true;
				CntFoundRecipes++;
				break;
			}
		}
		
	}
	BaseUI::Print_ln("Found " + to_string(CntFoundRecipes) + " Recipes");
	BaseUI::Print_ln();

	if (!isFind)
	{
		BaseUI::Print_ln("* Search Fail");
	}
}

PotionRecipe::PotionRecipe(string name, vector<Ingredient> ingredients)
{
	this->name = name;

	for (const Ingredient& ingrd : ingredients)
	{
		this->ingredient.emplace_back(ingrd);
	}
}
