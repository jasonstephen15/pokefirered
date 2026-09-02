#include "global.h"
#include "heal_location.h"
#include "event_data.h"
#include "constants/maps.h"
#include "constants/map_event_ids.h"
#include "constants/heal_locations.h"

static void SetWhiteoutRespawnHealerNpcAsLastTalked(u32 healLocationIdx);

// Arrays described here because mapjson will overrwrite the below data file

// sHealLocations
// This array defines the fly points for unlocked spawns.

// sWhiteoutRespawnHealCenterMapIdxs
// This array defines the map where you actually respawn when you white out,
// based on where you last checkpointed.
// This is either the player's house or a Pokémon Center.
// The data are u16 instead of u8 for reasons unknown.

// sWhiteoutRespawnHealerNpcIds
// When you respawn, your character scurries back to either their house
// or a Pokémon Center, and hands their fainted Pokémon to their mother
// or the Nurse for healing.
// This array defines the index of the NPC on the map defined above
// with whom your character interacts in this cutscene.

// ===== BEGIN src/data/heal_locations.h =====
//
// DO NOT MODIFY THIS FILE! It is auto-generated from src/data/heal_locations.json and Inja template src/data/heal_locations.json.txt
//


static const struct HealLocation sHealLocations[NUM_HEAL_LOCATIONS - 1] = {
    [HEAL_LOCATION_PALLET_TOWN - 1] = {
        .mapGroup = MAP_GROUP(MAP_PALLET_TOWN),
        .mapNum = MAP_NUM(MAP_PALLET_TOWN),
        .x = 6,
        .y = 8,
    },
    [HEAL_LOCATION_VIRIDIAN_CITY - 1] = {
        .mapGroup = MAP_GROUP(MAP_VIRIDIAN_CITY),
        .mapNum = MAP_NUM(MAP_VIRIDIAN_CITY),
        .x = 26,
        .y = 27,
    },
    [HEAL_LOCATION_PEWTER_CITY - 1] = {
        .mapGroup = MAP_GROUP(MAP_PEWTER_CITY),
        .mapNum = MAP_NUM(MAP_PEWTER_CITY),
        .x = 17,
        .y = 26,
    },
    [HEAL_LOCATION_CERULEAN_CITY - 1] = {
        .mapGroup = MAP_GROUP(MAP_CERULEAN_CITY),
        .mapNum = MAP_NUM(MAP_CERULEAN_CITY),
        .x = 22,
        .y = 20,
    },
    [HEAL_LOCATION_LAVENDER_TOWN - 1] = {
        .mapGroup = MAP_GROUP(MAP_LAVENDER_TOWN),
        .mapNum = MAP_NUM(MAP_LAVENDER_TOWN),
        .x = 6,
        .y = 6,
    },
    [HEAL_LOCATION_VERMILION_CITY - 1] = {
        .mapGroup = MAP_GROUP(MAP_VERMILION_CITY),
        .mapNum = MAP_NUM(MAP_VERMILION_CITY),
        .x = 15,
        .y = 7,
    },
    [HEAL_LOCATION_CELADON_CITY - 1] = {
        .mapGroup = MAP_GROUP(MAP_CELADON_CITY),
        .mapNum = MAP_NUM(MAP_CELADON_CITY),
        .x = 48,
        .y = 12,
    },
    [HEAL_LOCATION_FUCHSIA_CITY - 1] = {
        .mapGroup = MAP_GROUP(MAP_FUCHSIA_CITY),
        .mapNum = MAP_NUM(MAP_FUCHSIA_CITY),
        .x = 25,
        .y = 32,
    },
    [HEAL_LOCATION_CINNABAR_ISLAND - 1] = {
        .mapGroup = MAP_GROUP(MAP_CINNABAR_ISLAND),
        .mapNum = MAP_NUM(MAP_CINNABAR_ISLAND),
        .x = 14,
        .y = 12,
    },
    [HEAL_LOCATION_INDIGO_PLATEAU - 1] = {
        .mapGroup = MAP_GROUP(MAP_INDIGO_PLATEAU_EXTERIOR),
        .mapNum = MAP_NUM(MAP_INDIGO_PLATEAU_EXTERIOR),
        .x = 11,
        .y = 7,
    },
    [HEAL_LOCATION_SAFFRON_CITY - 1] = {
        .mapGroup = MAP_GROUP(MAP_SAFFRON_CITY),
        .mapNum = MAP_NUM(MAP_SAFFRON_CITY),
        .x = 24,
        .y = 39,
    },
    [HEAL_LOCATION_ROUTE4 - 1] = {
        .mapGroup = MAP_GROUP(MAP_ROUTE4),
        .mapNum = MAP_NUM(MAP_ROUTE4),
        .x = 12,
        .y = 6,
    },
    [HEAL_LOCATION_ROUTE10 - 1] = {
        .mapGroup = MAP_GROUP(MAP_ROUTE10),
        .mapNum = MAP_NUM(MAP_ROUTE10),
        .x = 13,
        .y = 21,
    },
    [HEAL_LOCATION_ONE_ISLAND - 1] = {
        .mapGroup = MAP_GROUP(MAP_ONE_ISLAND),
        .mapNum = MAP_NUM(MAP_ONE_ISLAND),
        .x = 14,
        .y = 6,
    },
    [HEAL_LOCATION_TWO_ISLAND - 1] = {
        .mapGroup = MAP_GROUP(MAP_TWO_ISLAND),
        .mapNum = MAP_NUM(MAP_TWO_ISLAND),
        .x = 21,
        .y = 8,
    },
    [HEAL_LOCATION_THREE_ISLAND - 1] = {
        .mapGroup = MAP_GROUP(MAP_THREE_ISLAND),
        .mapNum = MAP_NUM(MAP_THREE_ISLAND),
        .x = 14,
        .y = 28,
    },
    [HEAL_LOCATION_FOUR_ISLAND - 1] = {
        .mapGroup = MAP_GROUP(MAP_FOUR_ISLAND),
        .mapNum = MAP_NUM(MAP_FOUR_ISLAND),
        .x = 18,
        .y = 21,
    },
    [HEAL_LOCATION_FIVE_ISLAND - 1] = {
        .mapGroup = MAP_GROUP(MAP_FIVE_ISLAND),
        .mapNum = MAP_NUM(MAP_FIVE_ISLAND),
        .x = 18,
        .y = 7,
    },
    [HEAL_LOCATION_SEVEN_ISLAND - 1] = {
        .mapGroup = MAP_GROUP(MAP_SEVEN_ISLAND),
        .mapNum = MAP_NUM(MAP_SEVEN_ISLAND),
        .x = 12,
        .y = 4,
    },
    [HEAL_LOCATION_SIX_ISLAND - 1] = {
        .mapGroup = MAP_GROUP(MAP_SIX_ISLAND),
        .mapNum = MAP_NUM(MAP_SIX_ISLAND),
        .x = 11,
        .y = 12,
    },
};

static const u16 sWhiteoutRespawnHealCenterMapIdxs[NUM_HEAL_LOCATIONS - 1][2] = {
    [HEAL_LOCATION_PALLET_TOWN - 1] = { MAP_GROUP(MAP_PALLET_TOWN_PLAYERS_HOUSE_1F), MAP_NUM(MAP_PALLET_TOWN_PLAYERS_HOUSE_1F)},
    [HEAL_LOCATION_VIRIDIAN_CITY - 1] = { MAP_GROUP(MAP_VIRIDIAN_CITY_POKEMON_CENTER_1F), MAP_NUM(MAP_VIRIDIAN_CITY_POKEMON_CENTER_1F)},
    [HEAL_LOCATION_PEWTER_CITY - 1] = { MAP_GROUP(MAP_PEWTER_CITY_POKEMON_CENTER_1F), MAP_NUM(MAP_PEWTER_CITY_POKEMON_CENTER_1F)},
    [HEAL_LOCATION_CERULEAN_CITY - 1] = { MAP_GROUP(MAP_CERULEAN_CITY_POKEMON_CENTER_1F), MAP_NUM(MAP_CERULEAN_CITY_POKEMON_CENTER_1F)},
    [HEAL_LOCATION_LAVENDER_TOWN - 1] = { MAP_GROUP(MAP_LAVENDER_TOWN_POKEMON_CENTER_1F), MAP_NUM(MAP_LAVENDER_TOWN_POKEMON_CENTER_1F)},
    [HEAL_LOCATION_VERMILION_CITY - 1] = { MAP_GROUP(MAP_VERMILION_CITY_POKEMON_CENTER_1F), MAP_NUM(MAP_VERMILION_CITY_POKEMON_CENTER_1F)},
    [HEAL_LOCATION_CELADON_CITY - 1] = { MAP_GROUP(MAP_CELADON_CITY_POKEMON_CENTER_1F), MAP_NUM(MAP_CELADON_CITY_POKEMON_CENTER_1F)},
    [HEAL_LOCATION_FUCHSIA_CITY - 1] = { MAP_GROUP(MAP_FUCHSIA_CITY_POKEMON_CENTER_1F), MAP_NUM(MAP_FUCHSIA_CITY_POKEMON_CENTER_1F)},
    [HEAL_LOCATION_CINNABAR_ISLAND - 1] = { MAP_GROUP(MAP_CINNABAR_ISLAND_POKEMON_CENTER_1F), MAP_NUM(MAP_CINNABAR_ISLAND_POKEMON_CENTER_1F)},
    [HEAL_LOCATION_INDIGO_PLATEAU - 1] = { MAP_GROUP(MAP_INDIGO_PLATEAU_POKEMON_CENTER_1F), MAP_NUM(MAP_INDIGO_PLATEAU_POKEMON_CENTER_1F)},
    [HEAL_LOCATION_SAFFRON_CITY - 1] = { MAP_GROUP(MAP_SAFFRON_CITY_POKEMON_CENTER_1F), MAP_NUM(MAP_SAFFRON_CITY_POKEMON_CENTER_1F)},
    [HEAL_LOCATION_ROUTE4 - 1] = { MAP_GROUP(MAP_ROUTE4_POKEMON_CENTER_1F), MAP_NUM(MAP_ROUTE4_POKEMON_CENTER_1F)},
    [HEAL_LOCATION_ROUTE10 - 1] = { MAP_GROUP(MAP_ROUTE10_POKEMON_CENTER_1F), MAP_NUM(MAP_ROUTE10_POKEMON_CENTER_1F)},
    [HEAL_LOCATION_ONE_ISLAND - 1] = { MAP_GROUP(MAP_ONE_ISLAND_POKEMON_CENTER_1F), MAP_NUM(MAP_ONE_ISLAND_POKEMON_CENTER_1F)},
    [HEAL_LOCATION_TWO_ISLAND - 1] = { MAP_GROUP(MAP_TWO_ISLAND_POKEMON_CENTER_1F), MAP_NUM(MAP_TWO_ISLAND_POKEMON_CENTER_1F)},
    [HEAL_LOCATION_THREE_ISLAND - 1] = { MAP_GROUP(MAP_THREE_ISLAND_POKEMON_CENTER_1F), MAP_NUM(MAP_THREE_ISLAND_POKEMON_CENTER_1F)},
    [HEAL_LOCATION_FOUR_ISLAND - 1] = { MAP_GROUP(MAP_FOUR_ISLAND_POKEMON_CENTER_1F), MAP_NUM(MAP_FOUR_ISLAND_POKEMON_CENTER_1F)},
    [HEAL_LOCATION_FIVE_ISLAND - 1] = { MAP_GROUP(MAP_FIVE_ISLAND_POKEMON_CENTER_1F), MAP_NUM(MAP_FIVE_ISLAND_POKEMON_CENTER_1F)},
    [HEAL_LOCATION_SEVEN_ISLAND - 1] = { MAP_GROUP(MAP_SEVEN_ISLAND_POKEMON_CENTER_1F), MAP_NUM(MAP_SEVEN_ISLAND_POKEMON_CENTER_1F)},
    [HEAL_LOCATION_SIX_ISLAND - 1] = { MAP_GROUP(MAP_SIX_ISLAND_POKEMON_CENTER_1F), MAP_NUM(MAP_SIX_ISLAND_POKEMON_CENTER_1F)},
};

static const u8 sWhiteoutRespawnHealerNpcIds[NUM_HEAL_LOCATIONS - 1] = {
    [HEAL_LOCATION_PALLET_TOWN - 1] = LOCALID_MOM,
    [HEAL_LOCATION_VIRIDIAN_CITY - 1] = LOCALID_VIRIDIAN_NURSE,
    [HEAL_LOCATION_PEWTER_CITY - 1] = LOCALID_PEWTER_NURSE,
    [HEAL_LOCATION_CERULEAN_CITY - 1] = LOCALID_CERULEAN_NURSE,
    [HEAL_LOCATION_LAVENDER_TOWN - 1] = LOCALID_LAVENDER_NURSE,
    [HEAL_LOCATION_VERMILION_CITY - 1] = LOCALID_VERMILION_NURSE,
    [HEAL_LOCATION_CELADON_CITY - 1] = LOCALID_CELADON_NURSE,
    [HEAL_LOCATION_FUCHSIA_CITY - 1] = LOCALID_FUCHSIA_NURSE,
    [HEAL_LOCATION_CINNABAR_ISLAND - 1] = LOCALID_CINNABAR_NURSE,
    [HEAL_LOCATION_INDIGO_PLATEAU - 1] = LOCALID_LEAGUE_NURSE,
    [HEAL_LOCATION_SAFFRON_CITY - 1] = LOCALID_SAFFRON_NURSE,
    [HEAL_LOCATION_ROUTE4 - 1] = LOCALID_ROUTE4_NURSE,
    [HEAL_LOCATION_ROUTE10 - 1] = LOCALID_ROUTE10_NURSE,
    [HEAL_LOCATION_ONE_ISLAND - 1] = LOCALID_ONE_ISLAND_NURSE,
    [HEAL_LOCATION_TWO_ISLAND - 1] = LOCALID_TWO_ISLAND_NURSE,
    [HEAL_LOCATION_THREE_ISLAND - 1] = LOCALID_THREE_ISLAND_NURSE,
    [HEAL_LOCATION_FOUR_ISLAND - 1] = LOCALID_FOUR_ISLAND_NURSE,
    [HEAL_LOCATION_FIVE_ISLAND - 1] = LOCALID_FIVE_ISLAND_NURSE,
    [HEAL_LOCATION_SEVEN_ISLAND - 1] = LOCALID_SEVEN_ISLAND_NURSE,
    [HEAL_LOCATION_SIX_ISLAND - 1] = LOCALID_SIX_ISLAND_NURSE,
};
// ===== END src/data/heal_locations.h =====

static u32 GetHealLocationIndexFromMapGroupAndNum(u16 mapGroup, u16 mapNum)
{
    u32 i;

    for (i = 0; i < ARRAY_COUNT(sHealLocations); i++) {
        if (sHealLocations[i].mapGroup == mapGroup && sHealLocations[i].mapNum == mapNum)
        {
            return i + 1;
        }
    }

    return HEAL_LOCATION_NONE;
}

static const struct HealLocation * GetHealLocationPointerFromMapGroupAndNum(u16 mapGroup, u16 mapNum)
{
    u32 i = GetHealLocationIndexFromMapGroupAndNum(mapGroup, mapNum);
    if (i == HEAL_LOCATION_NONE)
        return NULL;

    return &sHealLocations[i - 1];
}

const struct HealLocation * GetHealLocation(u32 idx)
{
    if (idx == HEAL_LOCATION_NONE)
        return NULL;
    if (idx > ARRAY_COUNT(sHealLocations))
        return NULL;
    return &sHealLocations[idx - 1];
}

void SetWhiteoutRespawnWarpAndHealerNpc(struct WarpData * warp)
{
    u32 healLocationIdx;

    if (VarGet(VAR_MAP_SCENE_TRAINER_TOWER) == 1)
    {
        if (!gSaveBlock1Ptr->trainerTower[gSaveBlock1Ptr->towerChallengeId].spokeToOwner)
            VarSet(VAR_MAP_SCENE_TRAINER_TOWER, 0);
        gSpecialVar_LastTalked = 1;
        warp->x = 4;
        warp->y = 11;
        warp->mapGroup = MAP_GROUP(MAP_TRAINER_TOWER_LOBBY);
        warp->mapNum = MAP_NUM(MAP_TRAINER_TOWER_LOBBY);
        warp->warpId = 0xFF;
    }
    else
    {
        healLocationIdx = GetHealLocationIndexFromMapGroupAndNum(gSaveBlock1Ptr->lastHealLocation.mapGroup, gSaveBlock1Ptr->lastHealLocation.mapNum);
#ifdef BUGFIX
        // Avoid out of bounds read
        if (healLocationIdx == HEAL_LOCATION_NONE)
            return;
#endif
        warp->mapGroup = sWhiteoutRespawnHealCenterMapIdxs[healLocationIdx - 1][0];
        warp->mapNum = sWhiteoutRespawnHealCenterMapIdxs[healLocationIdx - 1][1];
        warp->warpId = WARP_ID_NONE;

        if (sWhiteoutRespawnHealCenterMapIdxs[healLocationIdx - 1][0] == MAP_GROUP(MAP_PALLET_TOWN_PLAYERS_HOUSE_1F) && sWhiteoutRespawnHealCenterMapIdxs[healLocationIdx - 1][1] == MAP_NUM(MAP_PALLET_TOWN_PLAYERS_HOUSE_1F))
        {
            warp->x = 8;
            warp->y = 5;
        }
        else if (sWhiteoutRespawnHealCenterMapIdxs[healLocationIdx - 1][0] == MAP_GROUP(MAP_INDIGO_PLATEAU_POKEMON_CENTER_1F) && sWhiteoutRespawnHealCenterMapIdxs[healLocationIdx - 1][1] == MAP_NUM(MAP_INDIGO_PLATEAU_POKEMON_CENTER_1F))
        {
            warp->x = 13;
            warp->y = 12;
        }
        else if (sWhiteoutRespawnHealCenterMapIdxs[healLocationIdx - 1][0] == MAP_GROUP(MAP_ONE_ISLAND_POKEMON_CENTER_1F) && sWhiteoutRespawnHealCenterMapIdxs[healLocationIdx - 1][1] == MAP_NUM(MAP_ONE_ISLAND_POKEMON_CENTER_1F))
        {
            warp->x = 5;
            warp->y = 4;
        }
        else if (sWhiteoutRespawnHealCenterMapIdxs[healLocationIdx - 1][0] == MAP_GROUP(MAP_TRAINER_TOWER_LOBBY) && sWhiteoutRespawnHealCenterMapIdxs[healLocationIdx - 1][1] == MAP_NUM(MAP_TRAINER_TOWER_LOBBY))
        {
            warp->x = 4;
            warp->y = 11;
            VarSet(VAR_MAP_SCENE_TRAINER_TOWER, 0);
        }
        else
        {
            warp->x = 7;
            warp->y = 4;
        }
        SetWhiteoutRespawnHealerNpcAsLastTalked(healLocationIdx);
    }
}

static void SetWhiteoutRespawnHealerNpcAsLastTalked(u32 healLocationIdx)
{
    gSpecialVar_LastTalked = sWhiteoutRespawnHealerNpcIds[healLocationIdx - 1];
}
