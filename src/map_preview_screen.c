#include "global.h"
#include "gflib.h"
#include "quest_log.h"
#include "new_menu_helpers.h"
#include "region_map.h"
#include "menu.h"
#include "field_fadetransition.h"
#include "field_weather.h"
#include "script.h"
#include "overworld.h"
#include "event_data.h"
#include "map_preview_screen.h"
#include "constants/region_map_sections.h"

static EWRAM_DATA bool8 sHasVisitedMapBefore = FALSE;
static EWRAM_DATA bool8 sAllocedBg0TilemapBuffer = FALSE;

static void Task_RunMapPreviewScreenForest(u8 taskId);

static const u8 sViridianForestMapPreviewPalette[] = INCBIN_U8("assets/graphics.bin", 0x22D3F8, 0x40);
static const u8 sViridianForestMapPreviewTiles[] = INCBIN_U8("assets/graphics.bin", 0x22D438, 0x1884);
static const u8 sViridianForestMapPreviewTilemap[] = INCBIN_U8("assets/graphics.bin", 0x22ECBC, 0x3D8);
static const u8 sRockTunnelMapPreviewPalette[] = INCBIN_U8("assets/graphics.bin", 0x22F094, 0x40);
static const u8 sRockTunnelMapPreviewTiles[] = INCBIN_U8("assets/graphics.bin", 0x22F0D4, 0x15A4);
static const u8 sRockTunnelMapPreviewTilemap[] = INCBIN_U8("assets/graphics.bin", 0x230678, 0x3F0);
static const u8 sRocketHideoutMapPreviewPalette[] = INCBIN_U8("assets/graphics.bin", 0x230A68, 0x40);
static const u8 sRocketHideoutMapPreviewTiles[] = INCBIN_U8("assets/graphics.bin", 0x230AA8, 0x7D8);
static const u8 sRocketHideoutMapPreviewTilemap[] = INCBIN_U8("assets/graphics.bin", 0x231280, 0x25C);
static const u8 sPowerPlantMapPreviewPalette[] = INCBIN_U8("assets/graphics.bin", 0x2314DC, 0x40);
static const u8 sPowerPlantMapPreviewTiles[] = INCBIN_U8("assets/graphics.bin", 0x23151C, 0x11D8);
static const u8 sPowerPlantMapPreviewTilemap[] = INCBIN_U8("assets/graphics.bin", 0x2326F4, 0x3B4);
static const u8 sPokemonMansionMapPreviewPalette[] = INCBIN_U8("assets/graphics.bin", 0x232AA8, 0x40);
static const u8 sPokemonMansionMapPreviewTiles[] = INCBIN_U8("assets/graphics.bin", 0x232AE8, 0x1908);
static const u8 sPokemonMansionMapPreviewTilemap[] = INCBIN_U8("assets/graphics.bin", 0x2343F0, 0x3DC);
static const u8 sPokemonTowerMapPreviewPalette[] = INCBIN_U8("assets/graphics.bin", 0x2347CC, 0x40);
static const u8 sPokemonTowerMapPreviewTiles[] = INCBIN_U8("assets/graphics.bin", 0x23480C, 0xF44);
static const u8 sPokemonTowerMapPreviewTilemap[] = INCBIN_U8("assets/graphics.bin", 0x235750, 0x314);
static const u8 sSilphCoMapPreviewPalette[] = INCBIN_U8("assets/graphics.bin", 0x235A64, 0x40);
static const u8 sSilphCoMapPreviewTiles[] = INCBIN_U8("assets/graphics.bin", 0x235AA4, 0x11DC);
static const u8 sSilphCoMapPreviewTilemap[] = INCBIN_U8("assets/graphics.bin", 0x236C80, 0x3A0);
static const u8 sMtMoonMapPreviewPalette[] = INCBIN_U8("assets/graphics.bin", 0x237020, 0x40);
static const u8 sMtMoonMapPreviewTiles[] = INCBIN_U8("assets/graphics.bin", 0x237060, 0x192C);
static const u8 sMtMoonMapPreviewTilemap[] = INCBIN_U8("assets/graphics.bin", 0x23898C, 0x398);
static const u8 sSeafoamIslandsMapPreviewPalette[] = INCBIN_U8("assets/graphics.bin", 0x238D24, 0x40);
static const u8 sSeafoamIslandsMapPreviewTiles[] = INCBIN_U8("assets/graphics.bin", 0x238D64, 0x1528);
static const u8 sSeafoamIslandsMapPreviewTilemap[] = INCBIN_U8("assets/graphics.bin", 0x23A28C, 0x3F8);
static const u8 sRocketWarehouseMapPreviewPalette[] = INCBIN_U8("assets/graphics.bin", 0x23A684, 0x40);
static const u8 sRocketWarehouseMapPreviewTiles[] = INCBIN_U8("assets/graphics.bin", 0x23A6C4, 0x928);
static const u8 sRocketWarehouseMapPreviewTilemap[] = INCBIN_U8("assets/graphics.bin", 0x23AFEC, 0x2BC);
static const u8 sVictoryRoadMapPreviewPalette[] = INCBIN_U8("assets/graphics.bin", 0x23B2A8, 0x40);
static const u8 sVictoryRoadMapPreviewTiles[] = INCBIN_U8("assets/graphics.bin", 0x23B2E8, 0x171C);
static const u8 sVictoryRoadMapPreviewTilemap[] = INCBIN_U8("assets/graphics.bin", 0x23CA04, 0x3BC);
static const u8 sMtEmberMapPreviewPalette[] = INCBIN_U8("assets/graphics.bin", 0x23CDC0, 0x40);
static const u8 sMtEmberMapPreviewTiles[] = INCBIN_U8("assets/graphics.bin", 0x23CE00, 0x16B4);
static const u8 sMtEmberMapPreviewTilemap[] = INCBIN_U8("assets/graphics.bin", 0x23E4B4, 0x38C);
static const u8 sSafariZoneMapPreviewPalette[] = INCBIN_U8("assets/graphics.bin", 0x23E840, 0x40);
static const u8 sSafariZoneMapPreviewTiles[] = INCBIN_U8("assets/graphics.bin", 0x23E880, 0x1510);
static const u8 sSafariZoneMapPreviewTilemap[] = INCBIN_U8("assets/graphics.bin", 0x23FD90, 0x360);
static const u8 sMoneanChamberMapPreviewPalette[] = INCBIN_U8("assets/graphics.bin", 0x2400F0, 0x40);
static const u8 sMoneanChamberMapPreviewTiles[] = INCBIN_U8("assets/graphics.bin", 0x240130, 0x14BC);
static const u8 sMoneanChamberMapPreviewTilemap[] = INCBIN_U8("assets/graphics.bin", 0x2415EC, 0x35C);
static const u8 sDottedHoleMapPreviewPalette[] = INCBIN_U8("assets/graphics.bin", 0x241948, 0x40);
static const u8 sDottedHoleMapPreviewTiles[] = INCBIN_U8("assets/graphics.bin", 0x241988, 0x1260);
static const u8 sDottedHoleMapPreviewTilemap[] = INCBIN_U8("assets/graphics.bin", 0x242BE8, 0x344);
static const u8 sCeruleanCaveMapPreviewPalette[] = INCBIN_U8("assets/graphics.bin", 0x242F2C, 0x40);
static const u8 sCeruleanCaveMapPreviewTiles[] = INCBIN_U8("assets/graphics.bin", 0x242F6C, 0x13D0);
static const u8 sCeruleanCaveMapPreviewTilemap[] = INCBIN_U8("assets/graphics.bin", 0x24433C, 0x3FC);
static const u8 sDiglettsCaveMapPreviewPalette[] = INCBIN_U8("assets/graphics.bin", 0x244738, 0x40);
static const u8 sDiglettsCaveMapPreviewTiles[] = INCBIN_U8("assets/graphics.bin", 0x244778, 0x172C);
static const u8 sDiglettsCaveMapPreviewTilemap[] = INCBIN_U8("assets/graphics.bin", 0x245EA4, 0x3E4);
static const u8 sLostCaveMapPreviewPalette[] = INCBIN_U8("assets/graphics.bin", 0x246288, 0x40);
static const u8 sLostCaveMapPreviewTiles[] = INCBIN_U8("assets/graphics.bin", 0x2462C8, 0x124C);
static const u8 sLostCaveMapPreviewTilemap[] = INCBIN_U8("assets/graphics.bin", 0x247514, 0x3E8);
static const u8 sBerryForestMapPreviewPalette[] = INCBIN_U8("assets/graphics.bin", 0x2478FC, 0x40);
static const u8 sBerryForestMapPreviewTiles[] = INCBIN_U8("assets/graphics.bin", 0x24793C, 0x1A0C);
static const u8 sBerryForestMapPreviewTilemap[] = INCBIN_U8("assets/graphics.bin", 0x249348, 0x3E0);
static const u8 sIcefallCaveMapPreviewPalette[] = INCBIN_U8("assets/graphics.bin", 0x249728, 0x40);
static const u8 sIcefallCaveMapPreviewTiles[] = INCBIN_U8("assets/graphics.bin", 0x249768, 0x1700);
static const u8 sIcefallCaveMapPreviewTilemap[] = INCBIN_U8("assets/graphics.bin", 0x24AE68, 0x3E0);
static const u8 sAlteringCaveMapPreviewPalette[] = INCBIN_U8("assets/graphics.bin", 0x24B248, 0x40);
static const u8 sAlteringCaveMapPreviewTiles[] = INCBIN_U8("assets/graphics.bin", 0x24B288, 0x12B4);
static const u8 sAlteringCaveMapPreviewTilemap[] = INCBIN_U8("assets/graphics.bin", 0x24C53C, 0x3D0);

static const struct MapPreviewScreen sMapPreviewScreenData[MPS_COUNT] = {
    [MPS_VIRIDIAN_FOREST] = {
        .mapsec = MAPSEC_VIRIDIAN_FOREST,
        .type = MPS_TYPE_FOREST,
        .flagId = FLAG_WORLD_MAP_VIRIDIAN_FOREST,
        .tilesptr = sViridianForestMapPreviewTiles,
        .tilemapptr = sViridianForestMapPreviewTilemap,
        .palptr = sViridianForestMapPreviewPalette
    },
    [MPS_MT_MOON] = {
        .mapsec = MAPSEC_MT_MOON,
        .type = MPS_TYPE_CAVE,
        .flagId = FLAG_WORLD_MAP_MT_MOON_1F,
        .tilesptr = sMtMoonMapPreviewTiles,
        .tilemapptr = sMtMoonMapPreviewTilemap,
        .palptr = sMtMoonMapPreviewPalette
    },
    [MPS_DIGLETTS_CAVE] = {
        .mapsec = MAPSEC_DIGLETTS_CAVE,
        .type = MPS_TYPE_CAVE,
        .flagId = FLAG_WORLD_MAP_DIGLETTS_CAVE_B1F,
        .tilesptr = sDiglettsCaveMapPreviewTiles,
        .tilemapptr = sDiglettsCaveMapPreviewTilemap,
        .palptr = sDiglettsCaveMapPreviewPalette
    },
    [MPS_ROCK_TUNNEL] = {
        .mapsec = MAPSEC_ROCK_TUNNEL,
        .type = MPS_TYPE_CAVE,
        .flagId = FLAG_WORLD_MAP_ROCK_TUNNEL_1F,
        .tilesptr = sRockTunnelMapPreviewTiles,
        .tilemapptr = sRockTunnelMapPreviewTilemap,
        .palptr = sRockTunnelMapPreviewPalette
    },
    [MPS_POKEMON_TOWER] = {
        .mapsec = MAPSEC_POKEMON_TOWER,
        .type = MPS_TYPE_CAVE,
        .flagId = FLAG_WORLD_MAP_POKEMON_TOWER_1F,
        .tilesptr = sPokemonTowerMapPreviewTiles,
        .tilemapptr = sPokemonTowerMapPreviewTilemap,
        .palptr = sPokemonTowerMapPreviewPalette
    },
    [MPS_SAFARI_ZONE] = {
        .mapsec = MAPSEC_KANTO_SAFARI_ZONE,
        .type = MPS_TYPE_FOREST,
        .flagId = FLAG_WORLD_MAP_SAFARI_ZONE_CENTER,
        .tilesptr = sSafariZoneMapPreviewTiles,
        .tilemapptr = sSafariZoneMapPreviewTilemap,
        .palptr = sSafariZoneMapPreviewPalette
    },
    [MPS_SEAFOAM_ISLANDS] = {
        .mapsec = MAPSEC_SEAFOAM_ISLANDS,
        .type = MPS_TYPE_CAVE,
        .flagId = FLAG_WORLD_MAP_SEAFOAM_ISLANDS_1F,
        .tilesptr = sSeafoamIslandsMapPreviewTiles,
        .tilemapptr = sSeafoamIslandsMapPreviewTilemap,
        .palptr = sSeafoamIslandsMapPreviewPalette
    },
    [MPS_POKEMON_MANSION] = {
        .mapsec = MAPSEC_POKEMON_MANSION,
        .type = MPS_TYPE_FOREST,
        .flagId = FLAG_WORLD_MAP_POKEMON_MANSION_1F,
        .tilesptr = sPokemonMansionMapPreviewTiles,
        .tilemapptr = sPokemonMansionMapPreviewTilemap,
        .palptr = sPokemonMansionMapPreviewPalette
    },
    [MPS_ROCKET_HIDEOUT] = {
        .mapsec = MAPSEC_ROCKET_HIDEOUT,
        .type = MPS_TYPE_FOREST,
        .flagId = FLAG_WORLD_MAP_ROCKET_HIDEOUT_B1F,
        .tilesptr = sRocketHideoutMapPreviewTiles,
        .tilemapptr = sRocketHideoutMapPreviewTilemap,
        .palptr = sRocketHideoutMapPreviewPalette
    },
    [MPS_SILPH_CO] = {
        .mapsec = MAPSEC_SILPH_CO,
        .type = MPS_TYPE_CAVE,
        .flagId = FLAG_WORLD_MAP_SILPH_CO_1F,
        .tilesptr = sSilphCoMapPreviewTiles,
        .tilemapptr = sSilphCoMapPreviewTilemap,
        .palptr = sSilphCoMapPreviewPalette
    },
    [MPS_VICTORY_ROAD] = {
        .mapsec = MAPSEC_KANTO_VICTORY_ROAD,
        .type = MPS_TYPE_CAVE,
        .flagId = FLAG_WORLD_MAP_VICTORY_ROAD_1F,
        .tilesptr = sVictoryRoadMapPreviewTiles,
        .tilemapptr = sVictoryRoadMapPreviewTilemap,
        .palptr = sVictoryRoadMapPreviewPalette
    },
    [MPS_CERULEAN_CAVE] = {
        .mapsec = MAPSEC_CERULEAN_CAVE,
        .type = MPS_TYPE_CAVE,
        .flagId = FLAG_WORLD_MAP_CERULEAN_CAVE_1F,
        .tilesptr = sCeruleanCaveMapPreviewTiles,
        .tilemapptr = sCeruleanCaveMapPreviewTilemap,
        .palptr = sCeruleanCaveMapPreviewPalette
    },
    [MPS_POWER_PLANT] = {
        .mapsec = MAPSEC_POWER_PLANT,
        .type = MPS_TYPE_FOREST,
        .flagId = FLAG_WORLD_MAP_POWER_PLANT,
        .tilesptr = sPowerPlantMapPreviewTiles,
        .tilemapptr = sPowerPlantMapPreviewTilemap,
        .palptr = sPowerPlantMapPreviewPalette
    },
    [MPS_MT_EMBER] = {
        .mapsec = MAPSEC_MT_EMBER,
        .type = MPS_TYPE_CAVE,
        .flagId = FLAG_WORLD_MAP_MT_EMBER_EXTERIOR,
        .tilesptr = sMtEmberMapPreviewTiles,
        .tilemapptr = sMtEmberMapPreviewTilemap,
        .palptr = sMtEmberMapPreviewPalette
    },
    [MPS_ROCKET_WAREHOUSE] = {
        .mapsec = MAPSEC_ROCKET_WAREHOUSE,
        .type = MPS_TYPE_FOREST,
        .flagId = FLAG_WORLD_MAP_THREE_ISLAND_BERRY_FOREST,
        .tilesptr = sRocketWarehouseMapPreviewTiles,
        .tilemapptr = sRocketWarehouseMapPreviewTilemap,
        .palptr = sRocketWarehouseMapPreviewPalette
    },
    [MPS_MONEAN_CHAMBER] = {
        .mapsec = MAPSEC_MONEAN_CHAMBER,
        .type = MPS_TYPE_CAVE,
        .flagId = FLAG_WORLD_MAP_SEVEN_ISLAND_TANOBY_RUINS_MONEAN_CHAMBER,
        .tilesptr = sMoneanChamberMapPreviewTiles,
        .tilemapptr = sMoneanChamberMapPreviewTilemap,
        .palptr = sMoneanChamberMapPreviewPalette
    },
    [MPS_DOTTED_HOLE] = {
        .mapsec = MAPSEC_DOTTED_HOLE,
        .type = MPS_TYPE_CAVE,
        .flagId = FLAG_WORLD_MAP_SIX_ISLAND_DOTTED_HOLE_1F,
        .tilesptr = sDottedHoleMapPreviewTiles,
        .tilemapptr = sDottedHoleMapPreviewTilemap,
        .palptr = sDottedHoleMapPreviewPalette
    },
    [MPS_BERRY_FOREST] = {
        .mapsec = MAPSEC_BERRY_FOREST,
        .type = MPS_TYPE_FOREST,
        .flagId = FLAG_WORLD_MAP_THREE_ISLAND_BERRY_FOREST,
        .tilesptr = sBerryForestMapPreviewTiles,
        .tilemapptr = sBerryForestMapPreviewTilemap,
        .palptr = sBerryForestMapPreviewPalette
    },
    [MPS_ICEFALL_CAVE] = {
        .mapsec = MAPSEC_ICEFALL_CAVE,
        .type = MPS_TYPE_CAVE,
        .flagId = FLAG_WORLD_MAP_FOUR_ISLAND_ICEFALL_CAVE_ENTRANCE,
        .tilesptr = sIcefallCaveMapPreviewTiles,
        .tilemapptr = sIcefallCaveMapPreviewTilemap,
        .palptr = sIcefallCaveMapPreviewPalette
    },
    [MPS_LOST_CAVE] = {
        .mapsec = MAPSEC_LOST_CAVE,
        .type = MPS_TYPE_CAVE,
        .flagId = FLAG_WORLD_MAP_FIVE_ISLAND_LOST_CAVE_ENTRANCE,
        .tilesptr = sLostCaveMapPreviewTiles,
        .tilemapptr = sLostCaveMapPreviewTilemap,
        .palptr = sLostCaveMapPreviewPalette
    },
    [MPS_ALTERING_CAVE] = {
        .mapsec = MAPSEC_ALTERING_CAVE,
        .type = MPS_TYPE_CAVE,
        .flagId = FLAG_WORLD_MAP_SIX_ISLAND_ALTERING_CAVE,
        .tilesptr = sAlteringCaveMapPreviewTiles,
        .tilemapptr = sAlteringCaveMapPreviewTilemap,
        .palptr = sAlteringCaveMapPreviewPalette
    },
    [MPS_PATTERN_BUSH] = {
        .mapsec = MAPSEC_PATTERN_BUSH,
        .type = MPS_TYPE_FOREST,
        .flagId = FLAG_WORLD_MAP_SIX_ISLAND_PATTERN_BUSH,
        .tilesptr = sViridianForestMapPreviewTiles,
        .tilemapptr = sViridianForestMapPreviewTilemap,
        .palptr = sViridianForestMapPreviewPalette
    },
    [MPS_LIPTOO_CHAMBER] = {
        .mapsec = MAPSEC_LIPTOO_CHAMBER,
        .type = MPS_TYPE_CAVE,
        .flagId = FLAG_WORLD_MAP_SEVEN_ISLAND_TANOBY_RUINS_MONEAN_CHAMBER,
        .tilesptr = sMoneanChamberMapPreviewTiles,
        .tilemapptr = sMoneanChamberMapPreviewTilemap,
        .palptr = sMoneanChamberMapPreviewPalette
    },
    [MPS_WEEPTH_CHAMBER] = {
        .mapsec = MAPSEC_WEEPTH_CHAMBER,
        .type = MPS_TYPE_CAVE,
        .flagId = FLAG_WORLD_MAP_SEVEN_ISLAND_TANOBY_RUINS_MONEAN_CHAMBER,
        .tilesptr = sMoneanChamberMapPreviewTiles,
        .tilemapptr = sMoneanChamberMapPreviewTilemap,
        .palptr = sMoneanChamberMapPreviewPalette
    },
    [MPS_TDILFORD_CHAMBER] = {
        .mapsec = MAPSEC_DILFORD_CHAMBER,
        .type = MPS_TYPE_CAVE,
        .flagId = FLAG_WORLD_MAP_SEVEN_ISLAND_TANOBY_RUINS_MONEAN_CHAMBER,
        .tilesptr = sMoneanChamberMapPreviewTiles,
        .tilemapptr = sMoneanChamberMapPreviewTilemap,
        .palptr = sMoneanChamberMapPreviewPalette
    },
    [MPS_SCUFIB_CHAMBER] = {
        .mapsec = MAPSEC_SCUFIB_CHAMBER,
        .type = MPS_TYPE_CAVE,
        .flagId = FLAG_WORLD_MAP_SEVEN_ISLAND_TANOBY_RUINS_MONEAN_CHAMBER,
        .tilesptr = sMoneanChamberMapPreviewTiles,
        .tilemapptr = sMoneanChamberMapPreviewTilemap,
        .palptr = sMoneanChamberMapPreviewPalette
    },
    [MPS_RIXY_CHAMBER] = {
        .mapsec = MAPSEC_RIXY_CHAMBER,
        .type = MPS_TYPE_CAVE,
        .flagId = FLAG_WORLD_MAP_SEVEN_ISLAND_TANOBY_RUINS_MONEAN_CHAMBER,
        .tilesptr = sMoneanChamberMapPreviewTiles,
        .tilemapptr = sMoneanChamberMapPreviewTilemap,
        .palptr = sMoneanChamberMapPreviewPalette
    },
    [MPS_VIAPOIS_CHAMBER] = {
        .mapsec = MAPSEC_VIAPOIS_CHAMBER,
        .type = MPS_TYPE_CAVE,
        .flagId = FLAG_WORLD_MAP_SEVEN_ISLAND_TANOBY_RUINS_MONEAN_CHAMBER,
        .tilesptr = sMoneanChamberMapPreviewTiles,
        .tilemapptr = sMoneanChamberMapPreviewTilemap,
        .palptr = sMoneanChamberMapPreviewPalette
    }
};

static const struct WindowTemplate sMapNameWindow = {
    .bg = 0,
    .tilemapLeft = 0,
    .tilemapTop = 0,
    .width = 13,
    .height = 2,
    .paletteNum = 14,
    .baseBlock = 0x1C2
};

static const struct BgTemplate sMapPreviewBgTemplate[1] = {
    {
        .mapBaseIndex = 31
    }
};

static u8 GetMapPreviewScreenIdx(u8 mapsec)
{
    s32 i;

    for (i = 0; i < MPS_COUNT; i++)
    {
        if (sMapPreviewScreenData[i].mapsec == mapsec)
        {
            return i;
        }
    }
    return MPS_COUNT;
}

bool8 MapHasPreviewScreen(u8 mapsec, u8 type)
{
    u8 idx;

    idx = GetMapPreviewScreenIdx(mapsec);
    if (idx != MPS_COUNT)
    {
        if (type == MPS_TYPE_ANY)
        {
            return TRUE;
        }
        else
        {
            return sMapPreviewScreenData[idx].type == type ? TRUE : FALSE;
        }
    }
    else
    {
        return FALSE;
    }
}

bool32 MapHasPreviewScreen_HandleQLState2(u8 mapsec, u8 type)
{
    if (gQuestLogState == QL_STATE_PLAYBACK)
    {
        return FALSE;
    }
    else
    {
        return MapHasPreviewScreen(mapsec, type);
    }
}

void MapPreview_InitBgs(void)
{
    InitBgsFromTemplates(0, sMapPreviewBgTemplate, NELEMS(sMapPreviewBgTemplate));
    ShowBg(0);
}

void MapPreview_LoadGfx(u8 mapsec)
{
    u8 idx;

    idx = GetMapPreviewScreenIdx(mapsec);
    if (idx != MPS_COUNT)
    {
       ResetTempTileDataBuffers();
       LoadPalette(sMapPreviewScreenData[idx].palptr, BG_PLTT_ID(13), 3 * PLTT_SIZE_4BPP);
       DecompressAndCopyTileDataToVram(0, sMapPreviewScreenData[idx].tilesptr, 0, 0, 0);
       if (GetBgTilemapBuffer(0) == NULL)
       {
           SetBgTilemapBuffer(0, Alloc(BG_SCREEN_SIZE));
           sAllocedBg0TilemapBuffer = TRUE;
       }
       else
       {
           sAllocedBg0TilemapBuffer = FALSE;
       }
       CopyToBgTilemapBuffer(0, sMapPreviewScreenData[idx].tilemapptr, 0, 0x000);
       CopyBgTilemapBufferToVram(0);
    }
}

void MapPreview_Unload(s32 windowId)
{
    RemoveWindow(windowId);
    if (sAllocedBg0TilemapBuffer)
    {
        Free(GetBgTilemapBuffer(0));
    }
}

bool32 MapPreview_IsGfxLoadFinished(void)
{
    return FreeTempTileDataBuffersIfPossible();
}

void MapPreview_StartForestTransition(u8 mapsec)
{
    u8 taskId;

    taskId = CreateTask(Task_RunMapPreviewScreenForest, 0);
    gTasks[taskId].data[2] = GetBgAttribute(0, BG_ATTR_PRIORITY);
    gTasks[taskId].data[4] = GetGpuReg(REG_OFFSET_BLDCNT);
    gTasks[taskId].data[5] = GetGpuReg(REG_OFFSET_BLDALPHA);
    gTasks[taskId].data[3] = GetGpuReg(REG_OFFSET_DISPCNT);
    gTasks[taskId].data[6] = GetGpuReg(REG_OFFSET_WININ);
    gTasks[taskId].data[7] = GetGpuReg(REG_OFFSET_WINOUT);
    gTasks[taskId].data[10] = MapPreview_GetDuration(mapsec);
    gTasks[taskId].data[8] = 16;
    gTasks[taskId].data[9] = 0;
    SetBgAttribute(0, BG_ATTR_PRIORITY, 0);
    SetGpuReg(REG_OFFSET_BLDCNT, BLDCNT_TGT1_BG0 | BLDCNT_EFFECT_BLEND | BLDCNT_TGT2_BG1 | BLDCNT_TGT2_BG2 | BLDCNT_TGT2_BG3 | BLDCNT_TGT2_OBJ | BLDCNT_TGT2_BD);
    SetGpuReg(REG_OFFSET_BLDALPHA, BLDALPHA_BLEND(16, 0));
    SetGpuRegBits(REG_OFFSET_WININ, WININ_WIN0_CLR | WININ_WIN1_CLR);
    SetGpuRegBits(REG_OFFSET_WINOUT, WINOUT_WIN01_CLR);
    gTasks[taskId].data[11] = MapPreview_CreateMapNameWindow(mapsec);
    LockPlayerFieldControls();
}

u16 MapPreview_CreateMapNameWindow(u8 mapsec)
{
    u16 windowId;
    u32 xctr;
    #ifdef BUGFIX
    // Fixes access violations indicated below.
    u8 color[3];
    #else
    u8 color[0];
    #endif

    windowId = AddWindow(&sMapNameWindow);
    FillWindowPixelBuffer(windowId, PIXEL_FILL(1));
    PutWindowTilemap(windowId);
    color[0] = TEXT_COLOR_WHITE; // Access violation
    color[1] = TEXT_COLOR_RED; // Access violation
    color[2] = TEXT_COLOR_LIGHT_GRAY; // Access violation
    GetMapName(gStringVar4, mapsec, 0);
    xctr = 104 - GetStringWidth(FONT_NORMAL, gStringVar4, 0);
    AddTextPrinterParameterized4(windowId, FONT_NORMAL, xctr / 2, 2, 0, 0, color/* Access violation */, -1, gStringVar4);
    return windowId;
}

bool32 ForestMapPreviewScreenIsRunning(void)
{
    if (FuncIsActiveTask(Task_RunMapPreviewScreenForest) == TRUE)
    {
        return FALSE;
    }
    else
    {
        return TRUE;
    }
}

static void Task_RunMapPreviewScreenForest(u8 taskId)
{
    s16 * data;

    data = gTasks[taskId].data;
    switch (data[0])
    {
    case 0:
        if (!MapPreview_IsGfxLoadFinished() && !IsDma3ManagerBusyWithBgCopy())
        {
            CopyWindowToVram(data[11], COPYWIN_FULL);
            data[0]++;
        }
        break;
    case 1:
        if (!IsDma3ManagerBusyWithBgCopy())
        {
            FadeInFromBlack();
            data[0]++;
        }
        break;
    case 2:
        if (IsWeatherNotFadingIn())
        {
            Overworld_PlaySpecialMapMusic();
            data[0]++;
        }
        break;
    case 3:
        data[1]++;
        if (data[1] > data[10])
        {
            data[1] = 0;
            data[0]++;
        }
        break;
    case 4:
        switch (data[1])
        {
        case 0:
            data[9]++;
            if (data[9] > 16)
            {
                data[9] = 16;
            }
            break;
        case 1:
            data[8]--;
            if (data[8] < 0)
            {
                data[8] = 0;
            }
            break;
        }
        data[1] = (data[1] + 1) % 3;
        SetGpuReg(REG_OFFSET_BLDALPHA, BLDALPHA_BLEND(data[8], data[9]));
        if (data[8] == 0 && data[9] == 16)
        {
            FillBgTilemapBufferRect_Palette0(0, 0, 0, 0, 32, 32);
            CopyBgTilemapBufferToVram(0);
            data[0]++;
        }
        break;
    case 5:
        if (!IsDma3ManagerBusyWithBgCopy())
        {
            MapPreview_Unload(data[11]);
            SetBgAttribute(0, BG_ATTR_PRIORITY, data[2]);
            SetGpuReg(REG_OFFSET_DISPCNT, data[3]);
            SetGpuReg(REG_OFFSET_BLDCNT, data[4]);
            SetGpuReg(REG_OFFSET_BLDALPHA, data[5]);
            SetGpuReg(REG_OFFSET_WININ, data[6]);
            SetGpuReg(REG_OFFSET_WINOUT, data[7]);
            DestroyTask(taskId);
        }
        break;
    }
}

const struct MapPreviewScreen * GetDungeonMapPreviewScreenInfo(u8 mapsec)
{
    u8 idx;

    idx = GetMapPreviewScreenIdx(mapsec);
    if (idx == MPS_COUNT)
    {
        return NULL;
    }
    else
    {
        return &sMapPreviewScreenData[idx];
    }
}

u16 MapPreview_GetDuration(u8 mapsec)
{
    u8 idx;
    u16 flagId;

    idx = GetMapPreviewScreenIdx(mapsec);
    if (idx == MPS_COUNT)
    {
        return 0;
    }
    flagId = sMapPreviewScreenData[idx].flagId;
    if (sMapPreviewScreenData[idx].type == MPS_TYPE_CAVE)
    {
        if (!FlagGet(flagId))
        {
            return 120;
        }
        else
        {
            return 40;
        }
    }
    else {
        if (sHasVisitedMapBefore)
        {
            return 120;
        }
        else
        {
            return 40;
        }
    }
}

void MapPreview_SetFlag(u16 flagId)
{
    if (!FlagGet(flagId))
    {
        sHasVisitedMapBefore = TRUE;
    }
    else
    {
        sHasVisitedMapBefore = FALSE;
    }
    FlagSet(flagId);
}
