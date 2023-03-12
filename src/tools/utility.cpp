#include "utility.h"

const QString Utility::heroNames[138] = { "Antimage", "Axe", "Bane", "Bloodseeker", "Crystal Maiden", "Drow Ranger",
                                      "Earthshaker", "Juggernaut", "Mirana", "Shadow Fiend", "Morphling", "Phantom Lancer",
                                      "Puck", "Pudge", "Razor", "Sand King", "Storm Spirit", "Sven", "Tiny", "Vengeful Spirit",
                                      "Windrunner", "Zeus", "Kunnka", "Lina", "Lich", "Lion", "Shadow Shaman", "Slardar",
                                      "Tidehunter", "Witch Doctor", "Riki", "Enigma", "Tinker", "Sniper", "Necrophos",
                                      "Warlock", "Beastmaster", "Queen of Pain", "Venomancer", "Faceless Void", "Wraith King",
                                      "Death Prophet", "Phantom Assassin", "Pugna", "Templar Assassin", "Viper", "Luna",
                                      "Dragon Knight", "Dazzle", "Clockwerk", "Leshrac", "Nature's Prophet", "Lifestealer",
                                      "Dark Seer", "Clinkz", "Omniknight", "Enchantress", "Huskar", "Night Stalker", "Broodmother",
                                      "Bounty Hunter", "Weaver", "Jakiro", "Batrider", "Chen", "Spectre", "Doom", "Ancient Apparition",
                                      "Ursa", "Spirit Breaker", "Gyrocopter", "Alchemist", "Invoker", "Silencer", "Outworld Devourer",
                                      "Lycan", "Brewmaster", "Shadow Demon", "Lone Druid", "Chaos Knight", "Meepo", "Treant Protector",
                                      "Ogre Magi", "Undying", "Rubick", "Disruptor", "Nyx Assassin", "Naga Siren", "Keeper of the Light",
                                      "Io", "Visage", "Slark", "Medusa", "Troll Warlord", "Centaur Warrunner", "Magnus", "Timbersaw",
                                      "Bristleback", "Tusk", "Skywrath Mage", "Abaddon", "Elder Titan", "Legion Commander", "Ember Spirit",
                                      "Earth Spirit", "Terrorblade", "Phoenix", "Oracle", "Techies", "Winter Wyvern", "Arc Warden",
                                      "Underlord", "Monkey King", "Dark Willow", "Pangolier", "Grimstroke", "Mars", "Snapfire", "Void Spirit",
                                      "Hoodwink", "Dawnbreaker", "Marci", "Primal Beast", "Muerta" };
QString Utility::getHeroNameByID(int id)
{
    if(id < 0 or id > 138)
        return "Incorrect hero ID";
    return heroNames[id - 1];
}
