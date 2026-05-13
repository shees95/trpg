#include "PotionShop.h"
#include "TUI.h"

using namespace TUI;

PotionShop::PotionShop()
{
	Init();
}


void PotionShop::Init()
{
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
	Print_ln();
	for (PotionRecipe pr : Recipes)
	{
		Print("-> " + pr.name + ": ");
		ShowIngredients(pr.ingredient);
		Print_ln();
	}
	Print_ln();
}

void PotionShop::ShowIngredients(vector<Ingredient> ingredients)
{
	int index = 1;
	for (Ingredient ingredient : ingredients)
	{
		
		ShowIngredient(ingredient);
		if (ingredients.size() >= ++index) Print(", ");
	}
}

void PotionShop::ShowIngredient(Ingredient ingredient)
{
	Print(ingredient.name + " x" + to_string(ingredient.amount));
}

void PotionShop::SearchByName(string name, bool isCorrect)
{
	bool isFind = false;
	int CntFoundRecipes = 0;

	Print_ln();
	for (const PotionRecipe& pr : Recipes)
	{
		if (pr.name.find(name) != string::npos)
		{
			Print("-> " + pr.name + ": ");
			ShowIngredients(pr.ingredient);
			Print_ln();

			isFind = true;
			CntFoundRecipes++;
		}
	}
	Print_ln("Found " + to_string(CntFoundRecipes) + " Recipes");
	Print_ln();

	if (!isFind)
	{
		Print_ln("* Search Fail");
	}
}

void PotionShop::SearchByIngredient(string ingredient, bool isCorrect)
{
	bool isFind = false;
	int CntFoundRecipes = 0;

	Print_ln();
	for (const PotionRecipe& pr : Recipes)
	{
		for (const Ingredient& ingrd : pr.ingredient)
		{
			if (ingrd.name.find(ingredient) != string::npos)
			{
				Print("-> " + pr.name + ": ");
				ShowIngredients(pr.ingredient);
				Print_ln();

				isFind = true;
				CntFoundRecipes++;
				break;
			}
		}
		
	}
	Print_ln("Found " + to_string(CntFoundRecipes) + " Recipes");
	Print_ln();

	if (!isFind)
	{
		Print_ln("* Search Fail");
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
