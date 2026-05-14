#pragma once
#include <string>
#include <vector>
using namespace std;
// 특정 문자열 일치 시, 전부 검색
// 전체 문자열 일치 시, 해당 아이템 제작 레시피 출력
// 재료 문자열 일치 시, 포함된 제작 레시피 출력



struct Ingredient
{
	string name;
	int amount;
};

class PotionRecipe
{
public:
	string name;
	vector<Ingredient> ingredient;

	PotionRecipe(string name, vector<Ingredient> ingredient);
};

class PotionShop
{
private:
	void Init();

	vector<PotionRecipe> Recipes;

public:
	PotionShop();

	void ShowAllRecipes();

	void ShowIngredients(vector<Ingredient> ingredients);
	void ShowIngredient(Ingredient ingredient);
	void SearchByName(string name, bool isCorrect);
	void SearchByIngredient(string ingredient, bool isCorrect);
};