#include "global.h"
#include "gflib.h"
#include "graphics.h"
#include "m4a.h"
#include "scanline_effect.h"
#include "task.h"
#include "new_menu_helpers.h"
#include "event_data.h"
#include "help_system.h"
#include "menu_indicators.h"
#include "overworld.h"
#include "strings.h"
#include "menu.h"
#include "pokedex_screen.h"
#include "data.h"
#include "pokedex.h"
#include "trainer_pokemon_sprites.h"
#include "decompress.h"
#include "constants/songs.h"
#include "constants/sound.h"
#include "pokedex_area_markers.h"
#include "field_specials.h"

#define TAG_AREA_MARKERS 2001

enum TextMode {
    TEXT_LEFT,
    TEXT_CENTER,
    TEXT_RIGHT
};

struct PokedexScreenData
{
    u8 taskId;
    u8 state;
    u8 data[2];
    u8 areaMarkersTaskId;
    u32 unlockedCategories;
    u32 modeSelectInput;
    u16 modeSelectItemsAbove;
    u16 modeSelectCursorPos;
    u8 modeSelectWindowId;
    u8 selectionIconWindowId;
    u8 dexCountsWindowId;
    u8 modeSelectListMenuId;
    u16 pageSpecies[4];
    u8 categoryMonWindowIds[4];
    u8 categoryMonInfoWindowIds[4];
    u8 category;
    u8 firstPageInCategory;
    u8 lastPageInCategory;
    u8 pageNum;
    u8 numMonsOnPage;
    u8 categoryCursorPosInPage;
    u8 categoryPageSelectionCursorTimer;
    u8 parentOfCategoryMenu;
    u32 characteristicMenuInput;
    u16 kantoOrderMenuItemsAbove;
    u16 kantoOrderMenuCursorPos;
    u16 characteristicOrderMenuItemsAbove;
    u16 characteristicOrderMenuCursorPos;
    u16 nationalOrderMenuItemsAbove;
    u16 nationalOrderMenuCursorPos;
    u8 numericalOrderWindowId;
    u8 orderedListMenuTaskId;
    u8 dexOrderId;
    struct ListMenuItem * listItems;
    u16 orderedDexCount;
    u8 windowIds[0x10];
    u16 dexSpecies;
    u16 * bgBufsMem;
    u8 scrollArrowsTaskId;
    u8 categoryPageCursorTaskId;
    u16 modeSelectCursorPosBak;
    u8 unlockedSeviiAreas;
    u16 numSeenKanto;
    u16 numOwnedKanto;
    u16 numSeenNational;
    u16 numOwnedNational;
};

struct PokedexScreenWindowGfx
{
    const u32 * tiles;
    const u16 * pal;
};

struct PokedexCategoryPage
{
    const u16 * species;
    u8 count;
};

EWRAM_DATA static struct PokedexScreenData * sPokedexScreenData = NULL;

static void Task_PokedexScreen(u8 taskId);
static void DexScreen_InitGfxForTopMenu(void);
static void Task_DexScreen_NumericalOrder(u8 taskId);
static void DexScreen_InitGfxForNumericalOrderList(void);
static void Task_DexScreen_CharacteristicOrder(u8 taskId);
static void DexScreen_CreateCharacteristicListMenu(void);
static u16 DexScreen_CountMonsInOrderedList(u8 orderIdx);
static void DexScreen_InitListMenuForOrderedList(const struct ListMenuTemplate * template, u8 order);
static u8 DexScreen_CreateDexOrderScrollArrows(void);
static void DexScreen_DestroyDexOrderListMenu(u8 order);
static void Task_DexScreen_CategorySubmenu(u8 taskId);
static u8 DexScreen_CreateCategoryMenuScrollArrows(void);
static int DexScreen_InputHandler_GetShoulderInput(void);
static void Task_DexScreen_ShowMonPage(u8 taskId);
static bool32 DexScreen_TryScrollMonsVertical(u8 direction);
static void DexScreen_RemoveWindow(u8 *windowId_p);
static void DexScreen_AddTextPrinterParameterized(u8 windowId, u8 fontId, const u8 *str, u8 x, u8 y, u8 colorIdx);
static void DexScreen_PrintNum3RightAlign(u8 windowId, u8 fontId, u16 num, u8 x, u8 y, u8 colorIdx);
static void DexScreen_PrintMonDexNo(u8 windowId, u8 fontId, u16 species, u8 x, u8 y);
static u16 DexScreen_GetDexCount(u8 caseId, bool8 whichDex);
static void DexScreen_PrintControlInfo(const u8 *src);
static void DexScreen_DestroyCategoryPageMonIconAndInfoWindows(void);
static bool8 DexScreen_CreateCategoryListGfx(bool8 justRegistered);
static void DexScreen_CreateCategoryPageSelectionCursor(u8 cursorPos);
static void DexScreen_UpdateCategoryPageCursorObject(u8 taskId, u8 cursorPos, u8 numMonsInPage);
static bool8 DexScreen_FlipCategoryPageInDirection(u8 direction);
void DexScreen_DexPageZoomEffectFrame(u8 bg, u8 scale);
static u8 DexScreen_DrawMonDexPage(bool8 justRegistered);
u8 RemoveDexPageWindows(void);
u8 DexScreen_DrawMonAreaPage(void);
static bool8 DexScreen_IsPageUnlocked(u8 category, u8 pageNum);
static bool8 DexScreen_IsCategoryUnlocked(u8 category);
static u8 DexScreen_GetPageLimitsForCategory(u8 category);
static bool8 DexScreen_LookUpCategoryBySpecies(u16 species);
u8 DexScreen_DestroyAreaScreenResources(void);
void DexScreen_CreateCategoryPageSpeciesList(u8 category, u8 pageNum);
static u8 DexScreen_PageNumberToRenderablePages(u16 page);
void DexScreen_InputHandler_StartToCry(void);
void DexScreen_PrintStringWithAlignment(const u8 *str, s32 mode);
static void MoveCursorFunc_DexModeSelect(s32 itemIndex, bool8 onInit, struct ListMenu *list);
static void ItemPrintFunc_DexModeSelect(u8 windowId, u32 itemId, u8 y);
static void ItemPrintFunc_OrderedListMenu(u8 windowId, u32 itemId, u8 y);
static void Task_DexScreen_RegisterNonKantoMonBeforeNationalDex(u8 taskId);
static void Task_DexScreen_RegisterMonToPokedex(u8 taskId);

// ===== BEGIN src/data/pokemon_graphics/footprint_table.h =====
const u8 *const gMonFootprintTable[] =
{
    [SPECIES_NONE] = gMonFootprint_Bulbasaur,
    [SPECIES_BULBASAUR] = gMonFootprint_Bulbasaur,
    [SPECIES_IVYSAUR] = gMonFootprint_Ivysaur,
    [SPECIES_VENUSAUR] = gMonFootprint_Venusaur,
    [SPECIES_CHARMANDER] = gMonFootprint_Charmander,
    [SPECIES_CHARMELEON] = gMonFootprint_Charmeleon,
    [SPECIES_CHARIZARD] = gMonFootprint_Charizard,
    [SPECIES_SQUIRTLE] = gMonFootprint_Squirtle,
    [SPECIES_WARTORTLE] = gMonFootprint_Wartortle,
    [SPECIES_BLASTOISE] = gMonFootprint_Blastoise,
    [SPECIES_CATERPIE] = gMonFootprint_Caterpie,
    [SPECIES_METAPOD] = gMonFootprint_Metapod,
    [SPECIES_BUTTERFREE] = gMonFootprint_Butterfree,
    [SPECIES_WEEDLE] = gMonFootprint_Weedle,
    [SPECIES_KAKUNA] = gMonFootprint_Kakuna,
    [SPECIES_BEEDRILL] = gMonFootprint_Beedrill,
    [SPECIES_PIDGEY] = gMonFootprint_Pidgey,
    [SPECIES_PIDGEOTTO] = gMonFootprint_Pidgeotto,
    [SPECIES_PIDGEOT] = gMonFootprint_Pidgeot,
    [SPECIES_RATTATA] = gMonFootprint_Rattata,
    [SPECIES_RATICATE] = gMonFootprint_Raticate,
    [SPECIES_SPEAROW] = gMonFootprint_Spearow,
    [SPECIES_FEAROW] = gMonFootprint_Fearow,
    [SPECIES_EKANS] = gMonFootprint_Ekans,
    [SPECIES_ARBOK] = gMonFootprint_Arbok,
    [SPECIES_PIKACHU] = gMonFootprint_Pikachu,
    [SPECIES_RAICHU] = gMonFootprint_Raichu,
    [SPECIES_SANDSHREW] = gMonFootprint_Sandshrew,
    [SPECIES_SANDSLASH] = gMonFootprint_Sandslash,
    [SPECIES_NIDORAN_F] = gMonFootprint_NidoranF,
    [SPECIES_NIDORINA] = gMonFootprint_Nidorina,
    [SPECIES_NIDOQUEEN] = gMonFootprint_Nidoqueen,
    [SPECIES_NIDORAN_M] = gMonFootprint_NidoranM,
    [SPECIES_NIDORINO] = gMonFootprint_Nidorino,
    [SPECIES_NIDOKING] = gMonFootprint_Nidoking,
    [SPECIES_CLEFAIRY] = gMonFootprint_Clefairy,
    [SPECIES_CLEFABLE] = gMonFootprint_Clefable,
    [SPECIES_VULPIX] = gMonFootprint_Vulpix,
    [SPECIES_NINETALES] = gMonFootprint_Ninetales,
    [SPECIES_JIGGLYPUFF] = gMonFootprint_Jigglypuff,
    [SPECIES_WIGGLYTUFF] = gMonFootprint_Wigglytuff,
    [SPECIES_ZUBAT] = gMonFootprint_Zubat,
    [SPECIES_GOLBAT] = gMonFootprint_Golbat,
    [SPECIES_ODDISH] = gMonFootprint_Oddish,
    [SPECIES_GLOOM] = gMonFootprint_Gloom,
    [SPECIES_VILEPLUME] = gMonFootprint_Vileplume,
    [SPECIES_PARAS] = gMonFootprint_Paras,
    [SPECIES_PARASECT] = gMonFootprint_Parasect,
    [SPECIES_VENONAT] = gMonFootprint_Venonat,
    [SPECIES_VENOMOTH] = gMonFootprint_Venomoth,
    [SPECIES_DIGLETT] = gMonFootprint_Diglett,
    [SPECIES_DUGTRIO] = gMonFootprint_Dugtrio,
    [SPECIES_MEOWTH] = gMonFootprint_Meowth,
    [SPECIES_PERSIAN] = gMonFootprint_Persian,
    [SPECIES_PSYDUCK] = gMonFootprint_Psyduck,
    [SPECIES_GOLDUCK] = gMonFootprint_Golduck,
    [SPECIES_MANKEY] = gMonFootprint_Mankey,
    [SPECIES_PRIMEAPE] = gMonFootprint_Primeape,
    [SPECIES_GROWLITHE] = gMonFootprint_Growlithe,
    [SPECIES_ARCANINE] = gMonFootprint_Arcanine,
    [SPECIES_POLIWAG] = gMonFootprint_Poliwag,
    [SPECIES_POLIWHIRL] = gMonFootprint_Poliwhirl,
    [SPECIES_POLIWRATH] = gMonFootprint_Poliwrath,
    [SPECIES_ABRA] = gMonFootprint_Abra,
    [SPECIES_KADABRA] = gMonFootprint_Kadabra,
    [SPECIES_ALAKAZAM] = gMonFootprint_Alakazam,
    [SPECIES_MACHOP] = gMonFootprint_Machop,
    [SPECIES_MACHOKE] = gMonFootprint_Machoke,
    [SPECIES_MACHAMP] = gMonFootprint_Machamp,
    [SPECIES_BELLSPROUT] = gMonFootprint_Bellsprout,
    [SPECIES_WEEPINBELL] = gMonFootprint_Weepinbell,
    [SPECIES_VICTREEBEL] = gMonFootprint_Victreebel,
    [SPECIES_TENTACOOL] = gMonFootprint_Tentacool,
    [SPECIES_TENTACRUEL] = gMonFootprint_Tentacruel,
    [SPECIES_GEODUDE] = gMonFootprint_Geodude,
    [SPECIES_GRAVELER] = gMonFootprint_Graveler,
    [SPECIES_GOLEM] = gMonFootprint_Golem,
    [SPECIES_PONYTA] = gMonFootprint_Ponyta,
    [SPECIES_RAPIDASH] = gMonFootprint_Rapidash,
    [SPECIES_SLOWPOKE] = gMonFootprint_Slowpoke,
    [SPECIES_SLOWBRO] = gMonFootprint_Slowbro,
    [SPECIES_MAGNEMITE] = gMonFootprint_Magnemite,
    [SPECIES_MAGNETON] = gMonFootprint_Magneton,
    [SPECIES_FARFETCHD] = gMonFootprint_Farfetchd,
    [SPECIES_DODUO] = gMonFootprint_Doduo,
    [SPECIES_DODRIO] = gMonFootprint_Dodrio,
    [SPECIES_SEEL] = gMonFootprint_Seel,
    [SPECIES_DEWGONG] = gMonFootprint_Dewgong,
    [SPECIES_GRIMER] = gMonFootprint_Grimer,
    [SPECIES_MUK] = gMonFootprint_Muk,
    [SPECIES_SHELLDER] = gMonFootprint_Shellder,
    [SPECIES_CLOYSTER] = gMonFootprint_Cloyster,
    [SPECIES_GASTLY] = gMonFootprint_Gastly,
    [SPECIES_HAUNTER] = gMonFootprint_Haunter,
    [SPECIES_GENGAR] = gMonFootprint_Gengar,
    [SPECIES_ONIX] = gMonFootprint_Onix,
    [SPECIES_DROWZEE] = gMonFootprint_Drowzee,
    [SPECIES_HYPNO] = gMonFootprint_Hypno,
    [SPECIES_KRABBY] = gMonFootprint_Krabby,
    [SPECIES_KINGLER] = gMonFootprint_Kingler,
    [SPECIES_VOLTORB] = gMonFootprint_Voltorb,
    [SPECIES_ELECTRODE] = gMonFootprint_Electrode,
    [SPECIES_EXEGGCUTE] = gMonFootprint_Exeggcute,
    [SPECIES_EXEGGUTOR] = gMonFootprint_Exeggutor,
    [SPECIES_CUBONE] = gMonFootprint_Cubone,
    [SPECIES_MAROWAK] = gMonFootprint_Marowak,
    [SPECIES_HITMONLEE] = gMonFootprint_Hitmonlee,
    [SPECIES_HITMONCHAN] = gMonFootprint_Hitmonchan,
    [SPECIES_LICKITUNG] = gMonFootprint_Lickitung,
    [SPECIES_KOFFING] = gMonFootprint_Koffing,
    [SPECIES_WEEZING] = gMonFootprint_Weezing,
    [SPECIES_RHYHORN] = gMonFootprint_Rhyhorn,
    [SPECIES_RHYDON] = gMonFootprint_Rhydon,
    [SPECIES_CHANSEY] = gMonFootprint_Chansey,
    [SPECIES_TANGELA] = gMonFootprint_Tangela,
    [SPECIES_KANGASKHAN] = gMonFootprint_Kangaskhan,
    [SPECIES_HORSEA] = gMonFootprint_Horsea,
    [SPECIES_SEADRA] = gMonFootprint_Seadra,
    [SPECIES_GOLDEEN] = gMonFootprint_Goldeen,
    [SPECIES_SEAKING] = gMonFootprint_Seaking,
    [SPECIES_STARYU] = gMonFootprint_Staryu,
    [SPECIES_STARMIE] = gMonFootprint_Starmie,
    [SPECIES_MR_MIME] = gMonFootprint_Mrmime,
    [SPECIES_SCYTHER] = gMonFootprint_Scyther,
    [SPECIES_JYNX] = gMonFootprint_Jynx,
    [SPECIES_ELECTABUZZ] = gMonFootprint_Electabuzz,
    [SPECIES_MAGMAR] = gMonFootprint_Magmar,
    [SPECIES_PINSIR] = gMonFootprint_Pinsir,
    [SPECIES_TAUROS] = gMonFootprint_Tauros,
    [SPECIES_MAGIKARP] = gMonFootprint_Magikarp,
    [SPECIES_GYARADOS] = gMonFootprint_Gyarados,
    [SPECIES_LAPRAS] = gMonFootprint_Lapras,
    [SPECIES_DITTO] = gMonFootprint_Ditto,
    [SPECIES_EEVEE] = gMonFootprint_Eevee,
    [SPECIES_VAPOREON] = gMonFootprint_Vaporeon,
    [SPECIES_JOLTEON] = gMonFootprint_Jolteon,
    [SPECIES_FLAREON] = gMonFootprint_Flareon,
    [SPECIES_PORYGON] = gMonFootprint_Porygon,
    [SPECIES_OMANYTE] = gMonFootprint_Omanyte,
    [SPECIES_OMASTAR] = gMonFootprint_Omastar,
    [SPECIES_KABUTO] = gMonFootprint_Kabuto,
    [SPECIES_KABUTOPS] = gMonFootprint_Kabutops,
    [SPECIES_AERODACTYL] = gMonFootprint_Aerodactyl,
    [SPECIES_SNORLAX] = gMonFootprint_Snorlax,
    [SPECIES_ARTICUNO] = gMonFootprint_Articuno,
    [SPECIES_ZAPDOS] = gMonFootprint_Zapdos,
    [SPECIES_MOLTRES] = gMonFootprint_Moltres,
    [SPECIES_DRATINI] = gMonFootprint_Dratini,
    [SPECIES_DRAGONAIR] = gMonFootprint_Dragonair,
    [SPECIES_DRAGONITE] = gMonFootprint_Dragonite,
    [SPECIES_MEWTWO] = gMonFootprint_Mewtwo,
    [SPECIES_MEW] = gMonFootprint_Mew,
    [SPECIES_CHIKORITA] = gMonFootprint_Chikorita,
    [SPECIES_BAYLEEF] = gMonFootprint_Bayleef,
    [SPECIES_MEGANIUM] = gMonFootprint_Meganium,
    [SPECIES_CYNDAQUIL] = gMonFootprint_Cyndaquil,
    [SPECIES_QUILAVA] = gMonFootprint_Quilava,
    [SPECIES_TYPHLOSION] = gMonFootprint_Typhlosion,
    [SPECIES_TOTODILE] = gMonFootprint_Totodile,
    [SPECIES_CROCONAW] = gMonFootprint_Croconaw,
    [SPECIES_FERALIGATR] = gMonFootprint_Feraligatr,
    [SPECIES_SENTRET] = gMonFootprint_Sentret,
    [SPECIES_FURRET] = gMonFootprint_Furret,
    [SPECIES_HOOTHOOT] = gMonFootprint_Hoothoot,
    [SPECIES_NOCTOWL] = gMonFootprint_Noctowl,
    [SPECIES_LEDYBA] = gMonFootprint_Ledyba,
    [SPECIES_LEDIAN] = gMonFootprint_Ledian,
    [SPECIES_SPINARAK] = gMonFootprint_Spinarak,
    [SPECIES_ARIADOS] = gMonFootprint_Ariados,
    [SPECIES_CROBAT] = gMonFootprint_Crobat,
    [SPECIES_CHINCHOU] = gMonFootprint_Chinchou,
    [SPECIES_LANTURN] = gMonFootprint_Lanturn,
    [SPECIES_PICHU] = gMonFootprint_Pichu,
    [SPECIES_CLEFFA] = gMonFootprint_Cleffa,
    [SPECIES_IGGLYBUFF] = gMonFootprint_Igglybuff,
    [SPECIES_TOGEPI] = gMonFootprint_Togepi,
    [SPECIES_TOGETIC] = gMonFootprint_Togetic,
    [SPECIES_NATU] = gMonFootprint_Natu,
    [SPECIES_XATU] = gMonFootprint_Xatu,
    [SPECIES_MAREEP] = gMonFootprint_Mareep,
    [SPECIES_FLAAFFY] = gMonFootprint_Flaaffy,
    [SPECIES_AMPHAROS] = gMonFootprint_Ampharos,
    [SPECIES_BELLOSSOM] = gMonFootprint_Bellossom,
    [SPECIES_MARILL] = gMonFootprint_Marill,
    [SPECIES_AZUMARILL] = gMonFootprint_Azumarill,
    [SPECIES_SUDOWOODO] = gMonFootprint_Sudowoodo,
    [SPECIES_POLITOED] = gMonFootprint_Politoed,
    [SPECIES_HOPPIP] = gMonFootprint_Hoppip,
    [SPECIES_SKIPLOOM] = gMonFootprint_Skiploom,
    [SPECIES_JUMPLUFF] = gMonFootprint_Jumpluff,
    [SPECIES_AIPOM] = gMonFootprint_Aipom,
    [SPECIES_SUNKERN] = gMonFootprint_Sunkern,
    [SPECIES_SUNFLORA] = gMonFootprint_Sunflora,
    [SPECIES_YANMA] = gMonFootprint_Yanma,
    [SPECIES_WOOPER] = gMonFootprint_Wooper,
    [SPECIES_QUAGSIRE] = gMonFootprint_Quagsire,
    [SPECIES_ESPEON] = gMonFootprint_Espeon,
    [SPECIES_UMBREON] = gMonFootprint_Umbreon,
    [SPECIES_MURKROW] = gMonFootprint_Murkrow,
    [SPECIES_SLOWKING] = gMonFootprint_Slowking,
    [SPECIES_MISDREAVUS] = gMonFootprint_Misdreavus,
    [SPECIES_UNOWN] = gMonFootprint_Unown,
    [SPECIES_WOBBUFFET] = gMonFootprint_Wobbuffet,
    [SPECIES_GIRAFARIG] = gMonFootprint_Girafarig,
    [SPECIES_PINECO] = gMonFootprint_Pineco,
    [SPECIES_FORRETRESS] = gMonFootprint_Forretress,
    [SPECIES_DUNSPARCE] = gMonFootprint_Dunsparce,
    [SPECIES_GLIGAR] = gMonFootprint_Gligar,
    [SPECIES_STEELIX] = gMonFootprint_Steelix,
    [SPECIES_SNUBBULL] = gMonFootprint_Snubbull,
    [SPECIES_GRANBULL] = gMonFootprint_Granbull,
    [SPECIES_QWILFISH] = gMonFootprint_Qwilfish,
    [SPECIES_SCIZOR] = gMonFootprint_Scizor,
    [SPECIES_SHUCKLE] = gMonFootprint_Shuckle,
    [SPECIES_HERACROSS] = gMonFootprint_Heracross,
    [SPECIES_SNEASEL] = gMonFootprint_Sneasel,
    [SPECIES_TEDDIURSA] = gMonFootprint_Teddiursa,
    [SPECIES_URSARING] = gMonFootprint_Ursaring,
    [SPECIES_SLUGMA] = gMonFootprint_Slugma,
    [SPECIES_MAGCARGO] = gMonFootprint_Magcargo,
    [SPECIES_SWINUB] = gMonFootprint_Swinub,
    [SPECIES_PILOSWINE] = gMonFootprint_Piloswine,
    [SPECIES_CORSOLA] = gMonFootprint_Corsola,
    [SPECIES_REMORAID] = gMonFootprint_Remoraid,
    [SPECIES_OCTILLERY] = gMonFootprint_Octillery,
    [SPECIES_DELIBIRD] = gMonFootprint_Delibird,
    [SPECIES_MANTINE] = gMonFootprint_Mantine,
    [SPECIES_SKARMORY] = gMonFootprint_Skarmory,
    [SPECIES_HOUNDOUR] = gMonFootprint_Houndour,
    [SPECIES_HOUNDOOM] = gMonFootprint_Houndoom,
    [SPECIES_KINGDRA] = gMonFootprint_Kingdra,
    [SPECIES_PHANPY] = gMonFootprint_Phanpy,
    [SPECIES_DONPHAN] = gMonFootprint_Donphan,
    [SPECIES_PORYGON2] = gMonFootprint_Porygon2,
    [SPECIES_STANTLER] = gMonFootprint_Stantler,
    [SPECIES_SMEARGLE] = gMonFootprint_Smeargle,
    [SPECIES_TYROGUE] = gMonFootprint_Tyrogue,
    [SPECIES_HITMONTOP] = gMonFootprint_Hitmontop,
    [SPECIES_SMOOCHUM] = gMonFootprint_Smoochum,
    [SPECIES_ELEKID] = gMonFootprint_Elekid,
    [SPECIES_MAGBY] = gMonFootprint_Magby,
    [SPECIES_MILTANK] = gMonFootprint_Miltank,
    [SPECIES_BLISSEY] = gMonFootprint_Blissey,
    [SPECIES_RAIKOU] = gMonFootprint_Raikou,
    [SPECIES_ENTEI] = gMonFootprint_Entei,
    [SPECIES_SUICUNE] = gMonFootprint_Suicune,
    [SPECIES_LARVITAR] = gMonFootprint_Larvitar,
    [SPECIES_PUPITAR] = gMonFootprint_Pupitar,
    [SPECIES_TYRANITAR] = gMonFootprint_Tyranitar,
    [SPECIES_LUGIA] = gMonFootprint_Lugia,
    [SPECIES_HO_OH] = gMonFootprint_HoOh,
    [SPECIES_CELEBI] = gMonFootprint_Celebi,
    [SPECIES_OLD_UNOWN_B] = gMonFootprint_QuestionMark,
    [SPECIES_OLD_UNOWN_C] = gMonFootprint_QuestionMark,
    [SPECIES_OLD_UNOWN_D] = gMonFootprint_QuestionMark,
    [SPECIES_OLD_UNOWN_E] = gMonFootprint_QuestionMark,
    [SPECIES_OLD_UNOWN_F] = gMonFootprint_QuestionMark,
    [SPECIES_OLD_UNOWN_G] = gMonFootprint_QuestionMark,
    [SPECIES_OLD_UNOWN_H] = gMonFootprint_QuestionMark,
    [SPECIES_OLD_UNOWN_I] = gMonFootprint_QuestionMark,
    [SPECIES_OLD_UNOWN_J] = gMonFootprint_QuestionMark,
    [SPECIES_OLD_UNOWN_K] = gMonFootprint_QuestionMark,
    [SPECIES_OLD_UNOWN_L] = gMonFootprint_QuestionMark,
    [SPECIES_OLD_UNOWN_M] = gMonFootprint_QuestionMark,
    [SPECIES_OLD_UNOWN_N] = gMonFootprint_QuestionMark,
    [SPECIES_OLD_UNOWN_O] = gMonFootprint_QuestionMark,
    [SPECIES_OLD_UNOWN_P] = gMonFootprint_QuestionMark,
    [SPECIES_OLD_UNOWN_Q] = gMonFootprint_QuestionMark,
    [SPECIES_OLD_UNOWN_R] = gMonFootprint_QuestionMark,
    [SPECIES_OLD_UNOWN_S] = gMonFootprint_QuestionMark,
    [SPECIES_OLD_UNOWN_T] = gMonFootprint_QuestionMark,
    [SPECIES_OLD_UNOWN_U] = gMonFootprint_QuestionMark,
    [SPECIES_OLD_UNOWN_V] = gMonFootprint_QuestionMark,
    [SPECIES_OLD_UNOWN_W] = gMonFootprint_QuestionMark,
    [SPECIES_OLD_UNOWN_X] = gMonFootprint_QuestionMark,
    [SPECIES_OLD_UNOWN_Y] = gMonFootprint_QuestionMark,
    [SPECIES_OLD_UNOWN_Z] = gMonFootprint_QuestionMark,
    [SPECIES_TREECKO] = gMonFootprint_Treecko,
    [SPECIES_GROVYLE] = gMonFootprint_Grovyle,
    [SPECIES_SCEPTILE] = gMonFootprint_Sceptile,
    [SPECIES_TORCHIC] = gMonFootprint_Torchic,
    [SPECIES_COMBUSKEN] = gMonFootprint_Combusken,
    [SPECIES_BLAZIKEN] = gMonFootprint_Blaziken,
    [SPECIES_MUDKIP] = gMonFootprint_Mudkip,
    [SPECIES_MARSHTOMP] = gMonFootprint_Marshtomp,
    [SPECIES_SWAMPERT] = gMonFootprint_Swampert,
    [SPECIES_POOCHYENA] = gMonFootprint_Poochyena,
    [SPECIES_MIGHTYENA] = gMonFootprint_Mightyena,
    [SPECIES_ZIGZAGOON] = gMonFootprint_Zigzagoon,
    [SPECIES_LINOONE] = gMonFootprint_Linoone,
    [SPECIES_WURMPLE] = gMonFootprint_Wurmple,
    [SPECIES_SILCOON] = gMonFootprint_Silcoon,
    [SPECIES_BEAUTIFLY] = gMonFootprint_Beautifly,
    [SPECIES_CASCOON] = gMonFootprint_Cascoon,
    [SPECIES_DUSTOX] = gMonFootprint_Dustox,
    [SPECIES_LOTAD] = gMonFootprint_Lotad,
    [SPECIES_LOMBRE] = gMonFootprint_Lombre,
    [SPECIES_LUDICOLO] = gMonFootprint_Ludicolo,
    [SPECIES_SEEDOT] = gMonFootprint_Seedot,
    [SPECIES_NUZLEAF] = gMonFootprint_Nuzleaf,
    [SPECIES_SHIFTRY] = gMonFootprint_Shiftry,
    [SPECIES_NINCADA] = gMonFootprint_Nincada,
    [SPECIES_NINJASK] = gMonFootprint_Ninjask,
    [SPECIES_SHEDINJA] = gMonFootprint_Shedinja,
    [SPECIES_TAILLOW] = gMonFootprint_Taillow,
    [SPECIES_SWELLOW] = gMonFootprint_Swellow,
    [SPECIES_SHROOMISH] = gMonFootprint_Shroomish,
    [SPECIES_BRELOOM] = gMonFootprint_Breloom,
    [SPECIES_SPINDA] = gMonFootprint_Spinda,
    [SPECIES_WINGULL] = gMonFootprint_Wingull,
    [SPECIES_PELIPPER] = gMonFootprint_Pelipper,
    [SPECIES_SURSKIT] = gMonFootprint_Surskit,
    [SPECIES_MASQUERAIN] = gMonFootprint_Masquerain,
    [SPECIES_WAILMER] = gMonFootprint_Wailmer,
    [SPECIES_WAILORD] = gMonFootprint_Wailord,
    [SPECIES_SKITTY] = gMonFootprint_Skitty,
    [SPECIES_DELCATTY] = gMonFootprint_Delcatty,
    [SPECIES_KECLEON] = gMonFootprint_Kecleon,
    [SPECIES_BALTOY] = gMonFootprint_Baltoy,
    [SPECIES_CLAYDOL] = gMonFootprint_Claydol,
    [SPECIES_NOSEPASS] = gMonFootprint_Nosepass,
    [SPECIES_TORKOAL] = gMonFootprint_Torkoal,
    [SPECIES_SABLEYE] = gMonFootprint_Sableye,
    [SPECIES_BARBOACH] = gMonFootprint_Barboach,
    [SPECIES_WHISCASH] = gMonFootprint_Whiscash,
    [SPECIES_LUVDISC] = gMonFootprint_Luvdisc,
    [SPECIES_CORPHISH] = gMonFootprint_Corphish,
    [SPECIES_CRAWDAUNT] = gMonFootprint_Crawdaunt,
    [SPECIES_FEEBAS] = gMonFootprint_Feebas,
    [SPECIES_MILOTIC] = gMonFootprint_Milotic,
    [SPECIES_CARVANHA] = gMonFootprint_Carvanha,
    [SPECIES_SHARPEDO] = gMonFootprint_Sharpedo,
    [SPECIES_TRAPINCH] = gMonFootprint_Trapinch,
    [SPECIES_VIBRAVA] = gMonFootprint_Vibrava,
    [SPECIES_FLYGON] = gMonFootprint_Flygon,
    [SPECIES_MAKUHITA] = gMonFootprint_Makuhita,
    [SPECIES_HARIYAMA] = gMonFootprint_Hariyama,
    [SPECIES_ELECTRIKE] = gMonFootprint_Electrike,
    [SPECIES_MANECTRIC] = gMonFootprint_Manectric,
    [SPECIES_NUMEL] = gMonFootprint_Numel,
    [SPECIES_CAMERUPT] = gMonFootprint_Camerupt,
    [SPECIES_SPHEAL] = gMonFootprint_Spheal,
    [SPECIES_SEALEO] = gMonFootprint_Sealeo,
    [SPECIES_WALREIN] = gMonFootprint_Walrein,
    [SPECIES_CACNEA] = gMonFootprint_Cacnea,
    [SPECIES_CACTURNE] = gMonFootprint_Cacturne,
    [SPECIES_SNORUNT] = gMonFootprint_Snorunt,
    [SPECIES_GLALIE] = gMonFootprint_Glalie,
    [SPECIES_LUNATONE] = gMonFootprint_Lunatone,
    [SPECIES_SOLROCK] = gMonFootprint_Solrock,
    [SPECIES_AZURILL] = gMonFootprint_Azurill,
    [SPECIES_SPOINK] = gMonFootprint_Spoink,
    [SPECIES_GRUMPIG] = gMonFootprint_Grumpig,
    [SPECIES_PLUSLE] = gMonFootprint_Plusle,
    [SPECIES_MINUN] = gMonFootprint_Minun,
    [SPECIES_MAWILE] = gMonFootprint_Mawile,
    [SPECIES_MEDITITE] = gMonFootprint_Meditite,
    [SPECIES_MEDICHAM] = gMonFootprint_Medicham,
    [SPECIES_SWABLU] = gMonFootprint_Swablu,
    [SPECIES_ALTARIA] = gMonFootprint_Altaria,
    [SPECIES_WYNAUT] = gMonFootprint_Wynaut,
    [SPECIES_DUSKULL] = gMonFootprint_Duskull,
    [SPECIES_DUSCLOPS] = gMonFootprint_Dusclops,
    [SPECIES_ROSELIA] = gMonFootprint_Roselia,
    [SPECIES_SLAKOTH] = gMonFootprint_Slakoth,
    [SPECIES_VIGOROTH] = gMonFootprint_Vigoroth,
    [SPECIES_SLAKING] = gMonFootprint_Slaking,
    [SPECIES_GULPIN] = gMonFootprint_Gulpin,
    [SPECIES_SWALOT] = gMonFootprint_Swalot,
    [SPECIES_TROPIUS] = gMonFootprint_Tropius,
    [SPECIES_WHISMUR] = gMonFootprint_Whismur,
    [SPECIES_LOUDRED] = gMonFootprint_Loudred,
    [SPECIES_EXPLOUD] = gMonFootprint_Exploud,
    [SPECIES_CLAMPERL] = gMonFootprint_Clamperl,
    [SPECIES_HUNTAIL] = gMonFootprint_Huntail,
    [SPECIES_GOREBYSS] = gMonFootprint_Gorebyss,
    [SPECIES_ABSOL] = gMonFootprint_Absol,
    [SPECIES_SHUPPET] = gMonFootprint_Shuppet,
    [SPECIES_BANETTE] = gMonFootprint_Banette,
    [SPECIES_SEVIPER] = gMonFootprint_Seviper,
    [SPECIES_ZANGOOSE] = gMonFootprint_Zangoose,
    [SPECIES_RELICANTH] = gMonFootprint_Relicanth,
    [SPECIES_ARON] = gMonFootprint_Aron,
    [SPECIES_LAIRON] = gMonFootprint_Lairon,
    [SPECIES_AGGRON] = gMonFootprint_Aggron,
    [SPECIES_CASTFORM] = gMonFootprint_Castform,
    [SPECIES_VOLBEAT] = gMonFootprint_Volbeat,
    [SPECIES_ILLUMISE] = gMonFootprint_Illumise,
    [SPECIES_LILEEP] = gMonFootprint_Lileep,
    [SPECIES_CRADILY] = gMonFootprint_Cradily,
    [SPECIES_ANORITH] = gMonFootprint_Anorith,
    [SPECIES_ARMALDO] = gMonFootprint_Armaldo,
    [SPECIES_RALTS] = gMonFootprint_Ralts,
    [SPECIES_KIRLIA] = gMonFootprint_Kirlia,
    [SPECIES_GARDEVOIR] = gMonFootprint_Gardevoir,
    [SPECIES_BAGON] = gMonFootprint_Bagon,
    [SPECIES_SHELGON] = gMonFootprint_Shelgon,
    [SPECIES_SALAMENCE] = gMonFootprint_Salamence,
    [SPECIES_BELDUM] = gMonFootprint_Beldum,
    [SPECIES_METANG] = gMonFootprint_Metang,
    [SPECIES_METAGROSS] = gMonFootprint_Metagross,
    [SPECIES_REGIROCK] = gMonFootprint_Regirock,
    [SPECIES_REGICE] = gMonFootprint_Regice,
    [SPECIES_REGISTEEL] = gMonFootprint_Registeel,
    [SPECIES_KYOGRE] = gMonFootprint_Kyogre,
    [SPECIES_GROUDON] = gMonFootprint_Groudon,
    [SPECIES_RAYQUAZA] = gMonFootprint_Rayquaza,
    [SPECIES_LATIAS] = gMonFootprint_Latias,
    [SPECIES_LATIOS] = gMonFootprint_Latios,
    [SPECIES_JIRACHI] = gMonFootprint_Jirachi,
    [SPECIES_DEOXYS] = gMonFootprint_Deoxys,
    [SPECIES_CHIMECHO] = gMonFootprint_Chimecho,
    [SPECIES_EGG] = gMonFootprint_Bulbasaur,
};
// ===== END src/data/pokemon_graphics/footprint_table.h =====

const u32 sCategoryMonInfoBgTiles[] = INCBIN_U32("assets/graphics.bin", 0x2527FC, 0x150);
const u32 sKantoDexTiles[] = INCBIN_U32("assets/graphics.bin", 0x25294C, 0x138);
const u32 sNatDexTiles[] = INCBIN_U32("assets/graphics.bin", 0x252A84, 0x11C);
const u16 sKantoDexPalette[0x100] = INCBIN_U16("assets/graphics.bin", 0x252BA0, 0x200);

const u16 sDexScreen_CategoryCursorPals[] = {
    RGB(24, 22, 17), RGB(26, 24, 20),
    RGB(26, 20, 15), RGB(27, 23, 19),
    RGB(28, 18, 15), RGB(28, 22, 19),
    RGB(30, 16, 13), RGB(29, 21, 18),
    RGB(28, 18, 15), RGB(28, 22, 19),
    RGB(26, 20, 15), RGB(27, 23, 19)
};

const u16 sNationalDexPalette[0x100] = INCBIN_U16("assets/graphics.bin", 0x252DA0, 0x200);
const u32 sTopMenuIconTiles_Cave[] = INCBIN_U32("assets/graphics.bin", 0x252FA0, 0x2F8);
const u32 sTopMenuIconTiles_Urban[] = INCBIN_U32("assets/graphics.bin", 0x253298, 0x318);
const u32 sTopMenuSelectionIconTiles_Cancel[] = INCBIN_U32("assets/graphics.bin", 0x2535B0, 0x23C);
const u32 sTopMenuIconTiles_Forest[] = INCBIN_U32("assets/graphics.bin", 0x2537EC, 0x390);
const u32 sTopMenuIconTiles_Grassland[] = INCBIN_U32("assets/graphics.bin", 0x253B7C, 0x34C);
const u32 sTopMenuIconTiles_QuestionMark[] = INCBIN_U32("assets/graphics.bin", 0x253EC8, 0x238);
const u32 sTopMenuIconTiles_Mountain[] = INCBIN_U32("assets/graphics.bin", 0x254100, 0x314);
const u32 sTopMenuIconTiles_Rare[] = INCBIN_U32("assets/graphics.bin", 0x254414, 0x2B0);
const u32 sTopMenuIconTiles_Sea[] = INCBIN_U32("assets/graphics.bin", 0x2546C4, 0x238);
const u32 sTopMenuIconTiles_Numerical[] = INCBIN_U32("assets/graphics.bin", 0x2548FC, 0x2A8);
const u32 sTopMenuIconTiles_RoughTerrain[] = INCBIN_U32("assets/graphics.bin", 0x254BA4, 0x354);
const u32 sTopMenuIconTiles_WatersEdge[] = INCBIN_U32("assets/graphics.bin", 0x254EF8, 0x388);
const u32 sTopMenuIconTiles_Type[] = INCBIN_U32("assets/graphics.bin", 0x255280, 0x338);
const u32 sTopMenuIconTiles_Lightest[] = INCBIN_U32("assets/graphics.bin", 0x2555B8, 0x294);
const u32 sTopMenuIconTiles_Smallest[] = INCBIN_U32("assets/graphics.bin", 0x25584C, 0x294);
const u16 sTopMenuIconPals_Cave[] = INCBIN_U16("assets/graphics.bin", 0x255AE0, 0x20);
const u16 sTopMenuIconPals_Urban[] = INCBIN_U16("assets/graphics.bin", 0x255B00, 0x20);
const u16 sTopMenuSelectionIconPals_Cancel[] = INCBIN_U16("assets/graphics.bin", 0x255B20, 0x20);
const u16 sTopMenuIconPals_Forest[] = INCBIN_U16("assets/graphics.bin", 0x255B40, 0x20);
const u16 sTopMenuIconPals_Grassland[] = INCBIN_U16("assets/graphics.bin", 0x255B60, 0x20);
const u16 sTopMenuIconPals_QuestionMark[] = INCBIN_U16("assets/graphics.bin", 0x255B80, 0x20);
const u16 sTopMenuIconPals_Mountain[] = INCBIN_U16("assets/graphics.bin", 0x255BA0, 0x20);
const u16 sTopMenuIconPals_Rare[] = INCBIN_U16("assets/graphics.bin", 0x255BC0, 0x20);
const u16 sTopMenuIconPals_Sea[] = INCBIN_U16("assets/graphics.bin", 0x255BE0, 0x20);
const u16 sTopMenuIconPals_Numerical[] = INCBIN_U16("assets/graphics.bin", 0x255C00, 0x20);
const u16 sTopMenuIconPals_RoughTerrain[] = INCBIN_U16("assets/graphics.bin", 0x255C20, 0x20);
const u16 sTopMenuIconPals_WatersEdge[] = INCBIN_U16("assets/graphics.bin", 0x255C40, 0x20);
const u16 sTopMenuIconPals_Type[] = INCBIN_U16("assets/graphics.bin", 0x255C60, 0x20);
const u16 sTopMenuIconPals_Lightest[] = INCBIN_U16("assets/graphics.bin", 0x255C80, 0x20);
const u16 sTopMenuIconPals_Smallest[] = INCBIN_U16("assets/graphics.bin", 0x255CA0, 0x20);
const u8 sDexScreen_CaughtIcon[] = INCBIN_U8("assets/graphics.bin", 0x255CC0, 0x20);
const u32 sTilemap_AreaMap_Kanto[] = INCBIN_U32("assets/graphics.bin", 0x255CE0, 0x2F0);
const u32 sTilemap_AreaMap_OneIsland[] = INCBIN_U32("assets/graphics.bin", 0x255FD0, 0x78);
const u32 sTilemap_AreaMap_TwoIsland[] = INCBIN_U32("assets/graphics.bin", 0x256048, 0x74);
const u32 sTilemap_AreaMap_ThreeIsland[] = INCBIN_U32("assets/graphics.bin", 0x2560BC, 0x7C);
const u32 sTilemap_AreaMap_FourIsland[] = INCBIN_U32("assets/graphics.bin", 0x256138, 0x80);
const u32 sTilemap_AreaMap_FiveIsland[] = INCBIN_U32("assets/graphics.bin", 0x2561B8, 0xB8);
const u32 sTilemap_AreaMap_SixIsland[] = INCBIN_U32("assets/graphics.bin", 0x256270, 0xA4);
const u32 sTilemap_AreaMap_SevenIsland[] = INCBIN_U32("assets/graphics.bin", 0x256314, 0xAC);
const u16 sBlitTiles_WideEllipse[] = INCBIN_U16("assets/graphics.bin", 0x2563C0, 0x2C0);

// ===== BEGIN src/data/pokemon/pokedex_orders.h =====
const u16 gPokedexOrder_Alphabetical[] =
{
    NATIONAL_DEX_OLD_UNOWN_B,
    NATIONAL_DEX_OLD_UNOWN_C,
    NATIONAL_DEX_OLD_UNOWN_D,
    NATIONAL_DEX_OLD_UNOWN_E,
    NATIONAL_DEX_OLD_UNOWN_F,
    NATIONAL_DEX_OLD_UNOWN_G,
    NATIONAL_DEX_OLD_UNOWN_H,
    NATIONAL_DEX_OLD_UNOWN_I,
    NATIONAL_DEX_OLD_UNOWN_J,
    NATIONAL_DEX_OLD_UNOWN_K,
    NATIONAL_DEX_OLD_UNOWN_L,
    NATIONAL_DEX_OLD_UNOWN_M,
    NATIONAL_DEX_OLD_UNOWN_N,
    NATIONAL_DEX_OLD_UNOWN_O,
    NATIONAL_DEX_OLD_UNOWN_P,
    NATIONAL_DEX_OLD_UNOWN_Q,
    NATIONAL_DEX_OLD_UNOWN_R,
    NATIONAL_DEX_OLD_UNOWN_S,
    NATIONAL_DEX_OLD_UNOWN_T,
    NATIONAL_DEX_OLD_UNOWN_U,
    NATIONAL_DEX_OLD_UNOWN_V,
    NATIONAL_DEX_OLD_UNOWN_W,
    NATIONAL_DEX_OLD_UNOWN_X,
    NATIONAL_DEX_OLD_UNOWN_Y,
    NATIONAL_DEX_OLD_UNOWN_Z,
    // Actual pokemon start here.
    NATIONAL_DEX_ABRA,
    NATIONAL_DEX_ABSOL,
    NATIONAL_DEX_AERODACTYL,
    NATIONAL_DEX_AGGRON,
    NATIONAL_DEX_AIPOM,
    NATIONAL_DEX_ALAKAZAM,
    NATIONAL_DEX_ALTARIA,
    NATIONAL_DEX_AMPHAROS,
    NATIONAL_DEX_ANORITH,
    NATIONAL_DEX_ARBOK,
    NATIONAL_DEX_ARCANINE,
    NATIONAL_DEX_ARIADOS,
    NATIONAL_DEX_ARMALDO,
    NATIONAL_DEX_ARON,
    NATIONAL_DEX_ARTICUNO,
    NATIONAL_DEX_AZUMARILL,
    NATIONAL_DEX_AZURILL,
    NATIONAL_DEX_BAGON,
    NATIONAL_DEX_BALTOY,
    NATIONAL_DEX_BANETTE,
    NATIONAL_DEX_BARBOACH,
    NATIONAL_DEX_BAYLEEF,
    NATIONAL_DEX_BEAUTIFLY,
    NATIONAL_DEX_BEEDRILL,
    NATIONAL_DEX_BELDUM,
    NATIONAL_DEX_BELLOSSOM,
    NATIONAL_DEX_BELLSPROUT,
    NATIONAL_DEX_BLASTOISE,
    NATIONAL_DEX_BLAZIKEN,
    NATIONAL_DEX_BLISSEY,
    NATIONAL_DEX_BRELOOM,
    NATIONAL_DEX_BULBASAUR,
    NATIONAL_DEX_BUTTERFREE,
    NATIONAL_DEX_CACNEA,
    NATIONAL_DEX_CACTURNE,
    NATIONAL_DEX_CAMERUPT,
    NATIONAL_DEX_CARVANHA,
    NATIONAL_DEX_CASCOON,
    NATIONAL_DEX_CASTFORM,
    NATIONAL_DEX_CATERPIE,
    NATIONAL_DEX_CELEBI,
    NATIONAL_DEX_CHANSEY,
    NATIONAL_DEX_CHARIZARD,
    NATIONAL_DEX_CHARMANDER,
    NATIONAL_DEX_CHARMELEON,
    NATIONAL_DEX_CHIKORITA,
    NATIONAL_DEX_CHIMECHO,
    NATIONAL_DEX_CHINCHOU,
    NATIONAL_DEX_CLAMPERL,
    NATIONAL_DEX_CLAYDOL,
    NATIONAL_DEX_CLEFABLE,
    NATIONAL_DEX_CLEFAIRY,
    NATIONAL_DEX_CLEFFA,
    NATIONAL_DEX_CLOYSTER,
    NATIONAL_DEX_COMBUSKEN,
    NATIONAL_DEX_CORPHISH,
    NATIONAL_DEX_CORSOLA,
    NATIONAL_DEX_CRADILY,
    NATIONAL_DEX_CRAWDAUNT,
    NATIONAL_DEX_CROBAT,
    NATIONAL_DEX_CROCONAW,
    NATIONAL_DEX_CUBONE,
    NATIONAL_DEX_CYNDAQUIL,
    NATIONAL_DEX_DELCATTY,
    NATIONAL_DEX_DELIBIRD,
    NATIONAL_DEX_DEOXYS,
    NATIONAL_DEX_DEWGONG,
    NATIONAL_DEX_DIGLETT,
    NATIONAL_DEX_DITTO,
    NATIONAL_DEX_DODRIO,
    NATIONAL_DEX_DODUO,
    NATIONAL_DEX_DONPHAN,
    NATIONAL_DEX_DRAGONAIR,
    NATIONAL_DEX_DRAGONITE,
    NATIONAL_DEX_DRATINI,
    NATIONAL_DEX_DROWZEE,
    NATIONAL_DEX_DUGTRIO,
    NATIONAL_DEX_DUNSPARCE,
    NATIONAL_DEX_DUSCLOPS,
    NATIONAL_DEX_DUSKULL,
    NATIONAL_DEX_DUSTOX,
    NATIONAL_DEX_EEVEE,
    NATIONAL_DEX_EKANS,
    NATIONAL_DEX_ELECTABUZZ,
    NATIONAL_DEX_ELECTRIKE,
    NATIONAL_DEX_ELECTRODE,
    NATIONAL_DEX_ELEKID,
    NATIONAL_DEX_ENTEI,
    NATIONAL_DEX_ESPEON,
    NATIONAL_DEX_EXEGGCUTE,
    NATIONAL_DEX_EXEGGUTOR,
    NATIONAL_DEX_EXPLOUD,
    NATIONAL_DEX_FARFETCHD,
    NATIONAL_DEX_FEAROW,
    NATIONAL_DEX_FEEBAS,
    NATIONAL_DEX_FERALIGATR,
    NATIONAL_DEX_FLAAFFY,
    NATIONAL_DEX_FLAREON,
    NATIONAL_DEX_FLYGON,
    NATIONAL_DEX_FORRETRESS,
    NATIONAL_DEX_FURRET,
    NATIONAL_DEX_GARDEVOIR,
    NATIONAL_DEX_GASTLY,
    NATIONAL_DEX_GENGAR,
    NATIONAL_DEX_GEODUDE,
    NATIONAL_DEX_GIRAFARIG,
    NATIONAL_DEX_GLALIE,
    NATIONAL_DEX_GLIGAR,
    NATIONAL_DEX_GLOOM,
    NATIONAL_DEX_GOLBAT,
    NATIONAL_DEX_GOLDEEN,
    NATIONAL_DEX_GOLDUCK,
    NATIONAL_DEX_GOLEM,
    NATIONAL_DEX_GOREBYSS,
    NATIONAL_DEX_GRANBULL,
    NATIONAL_DEX_GRAVELER,
    NATIONAL_DEX_GRIMER,
    NATIONAL_DEX_GROUDON,
    NATIONAL_DEX_GROVYLE,
    NATIONAL_DEX_GROWLITHE,
    NATIONAL_DEX_GRUMPIG,
    NATIONAL_DEX_GULPIN,
    NATIONAL_DEX_GYARADOS,
    NATIONAL_DEX_HARIYAMA,
    NATIONAL_DEX_HAUNTER,
    NATIONAL_DEX_HERACROSS,
    NATIONAL_DEX_HITMONCHAN,
    NATIONAL_DEX_HITMONLEE,
    NATIONAL_DEX_HITMONTOP,
    NATIONAL_DEX_HO_OH,
    NATIONAL_DEX_HOOTHOOT,
    NATIONAL_DEX_HOPPIP,
    NATIONAL_DEX_HORSEA,
    NATIONAL_DEX_HOUNDOOM,
    NATIONAL_DEX_HOUNDOUR,
    NATIONAL_DEX_HUNTAIL,
    NATIONAL_DEX_HYPNO,
    NATIONAL_DEX_IGGLYBUFF,
    NATIONAL_DEX_ILLUMISE,
    NATIONAL_DEX_IVYSAUR,
    NATIONAL_DEX_JIGGLYPUFF,
    NATIONAL_DEX_JIRACHI,
    NATIONAL_DEX_JOLTEON,
    NATIONAL_DEX_JUMPLUFF,
    NATIONAL_DEX_JYNX,
    NATIONAL_DEX_KABUTO,
    NATIONAL_DEX_KABUTOPS,
    NATIONAL_DEX_KADABRA,
    NATIONAL_DEX_KAKUNA,
    NATIONAL_DEX_KANGASKHAN,
    NATIONAL_DEX_KECLEON,
    NATIONAL_DEX_KINGDRA,
    NATIONAL_DEX_KINGLER,
    NATIONAL_DEX_KIRLIA,
    NATIONAL_DEX_KOFFING,
    NATIONAL_DEX_KRABBY,
    NATIONAL_DEX_KYOGRE,
    NATIONAL_DEX_LAIRON,
    NATIONAL_DEX_LANTURN,
    NATIONAL_DEX_LAPRAS,
    NATIONAL_DEX_LARVITAR,
    NATIONAL_DEX_LATIAS,
    NATIONAL_DEX_LATIOS,
    NATIONAL_DEX_LEDIAN,
    NATIONAL_DEX_LEDYBA,
    NATIONAL_DEX_LICKITUNG,
    NATIONAL_DEX_LILEEP,
    NATIONAL_DEX_LINOONE,
    NATIONAL_DEX_LOMBRE,
    NATIONAL_DEX_LOTAD,
    NATIONAL_DEX_LOUDRED,
    NATIONAL_DEX_LUDICOLO,
    NATIONAL_DEX_LUGIA,
    NATIONAL_DEX_LUNATONE,
    NATIONAL_DEX_LUVDISC,
    NATIONAL_DEX_MACHAMP,
    NATIONAL_DEX_MACHOKE,
    NATIONAL_DEX_MACHOP,
    NATIONAL_DEX_MAGBY,
    NATIONAL_DEX_MAGCARGO,
    NATIONAL_DEX_MAGIKARP,
    NATIONAL_DEX_MAGMAR,
    NATIONAL_DEX_MAGNEMITE,
    NATIONAL_DEX_MAGNETON,
    NATIONAL_DEX_MAKUHITA,
    NATIONAL_DEX_MANECTRIC,
    NATIONAL_DEX_MANKEY,
    NATIONAL_DEX_MANTINE,
    NATIONAL_DEX_MAREEP,
    NATIONAL_DEX_MARILL,
    NATIONAL_DEX_MAROWAK,
    NATIONAL_DEX_MARSHTOMP,
    NATIONAL_DEX_MASQUERAIN,
    NATIONAL_DEX_MAWILE,
    NATIONAL_DEX_MEDICHAM,
    NATIONAL_DEX_MEDITITE,
    NATIONAL_DEX_MEGANIUM,
    NATIONAL_DEX_MEOWTH,
    NATIONAL_DEX_METAGROSS,
    NATIONAL_DEX_METANG,
    NATIONAL_DEX_METAPOD,
    NATIONAL_DEX_MEW,
    NATIONAL_DEX_MEWTWO,
    NATIONAL_DEX_MIGHTYENA,
    NATIONAL_DEX_MILOTIC,
    NATIONAL_DEX_MILTANK,
    NATIONAL_DEX_MINUN,
    NATIONAL_DEX_MISDREAVUS,
    NATIONAL_DEX_MOLTRES,
    NATIONAL_DEX_MR_MIME,
    NATIONAL_DEX_MUDKIP,
    NATIONAL_DEX_MUK,
    NATIONAL_DEX_MURKROW,
    NATIONAL_DEX_NATU,
    NATIONAL_DEX_NIDOKING,
    NATIONAL_DEX_NIDOQUEEN,
    NATIONAL_DEX_NIDORAN_F,
    NATIONAL_DEX_NIDORAN_M,
    NATIONAL_DEX_NIDORINA,
    NATIONAL_DEX_NIDORINO,
    NATIONAL_DEX_NINCADA,
    NATIONAL_DEX_NINETALES,
    NATIONAL_DEX_NINJASK,
    NATIONAL_DEX_NOCTOWL,
    NATIONAL_DEX_NOSEPASS,
    NATIONAL_DEX_NUMEL,
    NATIONAL_DEX_NUZLEAF,
    NATIONAL_DEX_OCTILLERY,
    NATIONAL_DEX_ODDISH,
    NATIONAL_DEX_OMANYTE,
    NATIONAL_DEX_OMASTAR,
    NATIONAL_DEX_ONIX,
    NATIONAL_DEX_PARAS,
    NATIONAL_DEX_PARASECT,
    NATIONAL_DEX_PELIPPER,
    NATIONAL_DEX_PERSIAN,
    NATIONAL_DEX_PHANPY,
    NATIONAL_DEX_PICHU,
    NATIONAL_DEX_PIDGEOT,
    NATIONAL_DEX_PIDGEOTTO,
    NATIONAL_DEX_PIDGEY,
    NATIONAL_DEX_PIKACHU,
    NATIONAL_DEX_PILOSWINE,
    NATIONAL_DEX_PINECO,
    NATIONAL_DEX_PINSIR,
    NATIONAL_DEX_PLUSLE,
    NATIONAL_DEX_POLITOED,
    NATIONAL_DEX_POLIWAG,
    NATIONAL_DEX_POLIWHIRL,
    NATIONAL_DEX_POLIWRATH,
    NATIONAL_DEX_PONYTA,
    NATIONAL_DEX_POOCHYENA,
    NATIONAL_DEX_PORYGON,
    NATIONAL_DEX_PORYGON2,
    NATIONAL_DEX_PRIMEAPE,
    NATIONAL_DEX_PSYDUCK,
    NATIONAL_DEX_PUPITAR,
    NATIONAL_DEX_QUAGSIRE,
    NATIONAL_DEX_QUILAVA,
    NATIONAL_DEX_QWILFISH,
    NATIONAL_DEX_RAICHU,
    NATIONAL_DEX_RAIKOU,
    NATIONAL_DEX_RALTS,
    NATIONAL_DEX_RAPIDASH,
    NATIONAL_DEX_RATICATE,
    NATIONAL_DEX_RATTATA,
    NATIONAL_DEX_RAYQUAZA,
    NATIONAL_DEX_REGICE,
    NATIONAL_DEX_REGIROCK,
    NATIONAL_DEX_REGISTEEL,
    NATIONAL_DEX_RELICANTH,
    NATIONAL_DEX_REMORAID,
    NATIONAL_DEX_RHYDON,
    NATIONAL_DEX_RHYHORN,
    NATIONAL_DEX_ROSELIA,
    NATIONAL_DEX_SABLEYE,
    NATIONAL_DEX_SALAMENCE,
    NATIONAL_DEX_SANDSHREW,
    NATIONAL_DEX_SANDSLASH,
    NATIONAL_DEX_SCEPTILE,
    NATIONAL_DEX_SCIZOR,
    NATIONAL_DEX_SCYTHER,
    NATIONAL_DEX_SEADRA,
    NATIONAL_DEX_SEAKING,
    NATIONAL_DEX_SEALEO,
    NATIONAL_DEX_SEEDOT,
    NATIONAL_DEX_SEEL,
    NATIONAL_DEX_SENTRET,
    NATIONAL_DEX_SEVIPER,
    NATIONAL_DEX_SHARPEDO,
    NATIONAL_DEX_SHEDINJA,
    NATIONAL_DEX_SHELGON,
    NATIONAL_DEX_SHELLDER,
    NATIONAL_DEX_SHIFTRY,
    NATIONAL_DEX_SHROOMISH,
    NATIONAL_DEX_SHUCKLE,
    NATIONAL_DEX_SHUPPET,
    NATIONAL_DEX_SILCOON,
    NATIONAL_DEX_SKARMORY,
    NATIONAL_DEX_SKIPLOOM,
    NATIONAL_DEX_SKITTY,
    NATIONAL_DEX_SLAKING,
    NATIONAL_DEX_SLAKOTH,
    NATIONAL_DEX_SLOWBRO,
    NATIONAL_DEX_SLOWKING,
    NATIONAL_DEX_SLOWPOKE,
    NATIONAL_DEX_SLUGMA,
    NATIONAL_DEX_SMEARGLE,
    NATIONAL_DEX_SMOOCHUM,
    NATIONAL_DEX_SNEASEL,
    NATIONAL_DEX_SNORLAX,
    NATIONAL_DEX_SNORUNT,
    NATIONAL_DEX_SNUBBULL,
    NATIONAL_DEX_SOLROCK,
    NATIONAL_DEX_SPEAROW,
    NATIONAL_DEX_SPHEAL,
    NATIONAL_DEX_SPINARAK,
    NATIONAL_DEX_SPINDA,
    NATIONAL_DEX_SPOINK,
    NATIONAL_DEX_SQUIRTLE,
    NATIONAL_DEX_STANTLER,
    NATIONAL_DEX_STARMIE,
    NATIONAL_DEX_STARYU,
    NATIONAL_DEX_STEELIX,
    NATIONAL_DEX_SUDOWOODO,
    NATIONAL_DEX_SUICUNE,
    NATIONAL_DEX_SUNFLORA,
    NATIONAL_DEX_SUNKERN,
    NATIONAL_DEX_SURSKIT,
    NATIONAL_DEX_SWABLU,
    NATIONAL_DEX_SWALOT,
    NATIONAL_DEX_SWAMPERT,
    NATIONAL_DEX_SWELLOW,
    NATIONAL_DEX_SWINUB,
    NATIONAL_DEX_TAILLOW,
    NATIONAL_DEX_TANGELA,
    NATIONAL_DEX_TAUROS,
    NATIONAL_DEX_TEDDIURSA,
    NATIONAL_DEX_TENTACOOL,
    NATIONAL_DEX_TENTACRUEL,
    NATIONAL_DEX_TOGEPI,
    NATIONAL_DEX_TOGETIC,
    NATIONAL_DEX_TORCHIC,
    NATIONAL_DEX_TORKOAL,
    NATIONAL_DEX_TOTODILE,
    NATIONAL_DEX_TRAPINCH,
    NATIONAL_DEX_TREECKO,
    NATIONAL_DEX_TROPIUS,
    NATIONAL_DEX_TYPHLOSION,
    NATIONAL_DEX_TYRANITAR,
    NATIONAL_DEX_TYROGUE,
    NATIONAL_DEX_UMBREON,
    NATIONAL_DEX_UNOWN,
    NATIONAL_DEX_URSARING,
    NATIONAL_DEX_VAPOREON,
    NATIONAL_DEX_VENOMOTH,
    NATIONAL_DEX_VENONAT,
    NATIONAL_DEX_VENUSAUR,
    NATIONAL_DEX_VIBRAVA,
    NATIONAL_DEX_VICTREEBEL,
    NATIONAL_DEX_VIGOROTH,
    NATIONAL_DEX_VILEPLUME,
    NATIONAL_DEX_VOLBEAT,
    NATIONAL_DEX_VOLTORB,
    NATIONAL_DEX_VULPIX,
    NATIONAL_DEX_WAILMER,
    NATIONAL_DEX_WAILORD,
    NATIONAL_DEX_WALREIN,
    NATIONAL_DEX_WARTORTLE,
    NATIONAL_DEX_WEEDLE,
    NATIONAL_DEX_WEEPINBELL,
    NATIONAL_DEX_WEEZING,
    NATIONAL_DEX_WHISCASH,
    NATIONAL_DEX_WHISMUR,
    NATIONAL_DEX_WIGGLYTUFF,
    NATIONAL_DEX_WINGULL,
    NATIONAL_DEX_WOBBUFFET,
    NATIONAL_DEX_WOOPER,
    NATIONAL_DEX_WURMPLE,
    NATIONAL_DEX_WYNAUT,
    NATIONAL_DEX_XATU,
    NATIONAL_DEX_YANMA,
    NATIONAL_DEX_ZANGOOSE,
    NATIONAL_DEX_ZAPDOS,
    NATIONAL_DEX_ZIGZAGOON,
    NATIONAL_DEX_ZUBAT
};

const u16 gPokedexOrder_Weight[] =
{
    NATIONAL_DEX_GASTLY,
    NATIONAL_DEX_HAUNTER,
    NATIONAL_DEX_HOPPIP,
    NATIONAL_DEX_DIGLETT,
    NATIONAL_DEX_CASTFORM,
    NATIONAL_DEX_KOFFING,
    NATIONAL_DEX_IGGLYBUFF,
    NATIONAL_DEX_MISDREAVUS,
    NATIONAL_DEX_CHIMECHO,
    NATIONAL_DEX_SKIPLOOM,
    NATIONAL_DEX_JIRACHI,
    NATIONAL_DEX_SWABLU,
    NATIONAL_DEX_SHEDINJA,
    NATIONAL_DEX_TOGEPI,
    NATIONAL_DEX_SURSKIT,
    NATIONAL_DEX_PIDGEY,
    NATIONAL_DEX_SUNKERN,
    NATIONAL_DEX_BARBOACH,
    NATIONAL_DEX_PICHU,
    NATIONAL_DEX_AZURILL,
    NATIONAL_DEX_ROSELIA,
    NATIONAL_DEX_NATU,
    NATIONAL_DEX_SPEAROW,
    NATIONAL_DEX_MURKROW,
    NATIONAL_DEX_SHUPPET,
    NATIONAL_DEX_TAILLOW,
    NATIONAL_DEX_EXEGGCUTE,
    NATIONAL_DEX_TORCHIC,
    NATIONAL_DEX_LOTAD,
    NATIONAL_DEX_CATERPIE,
    NATIONAL_DEX_JUMPLUFF,
    NATIONAL_DEX_CLEFFA,
    NATIONAL_DEX_WEEDLE,
    NATIONAL_DEX_TOGETIC,
    NATIONAL_DEX_DRATINI,
    NATIONAL_DEX_RATTATA,
    NATIONAL_DEX_MASQUERAIN,
    NATIONAL_DEX_WURMPLE,
    NATIONAL_DEX_QWILFISH,
    NATIONAL_DEX_MEW,
    NATIONAL_DEX_SHELLDER,
    NATIONAL_DEX_SEEDOT,
    NATIONAL_DEX_DITTO,
    NATIONAL_DEX_BELLSPROUT,
    NATIONAL_DEX_PLUSLE,
    NATIONAL_DEX_MEOWTH,
    NATIONAL_DEX_MINUN,
    NATIONAL_DEX_SHROOMISH,
    NATIONAL_DEX_CELEBI,
    NATIONAL_DEX_CORSOLA,
    NATIONAL_DEX_TREECKO,
    NATIONAL_DEX_SPINDA,
    NATIONAL_DEX_UNOWN,
    NATIONAL_DEX_PARAS,
    NATIONAL_DEX_ODDISH,
    NATIONAL_DEX_JIGGLYPUFF,
    NATIONAL_DEX_NINCADA,
    NATIONAL_DEX_BELLOSSOM,
    NATIONAL_DEX_MAGNEMITE,
    NATIONAL_DEX_PIKACHU,
    NATIONAL_DEX_SMOOCHUM,
    NATIONAL_DEX_SENTRET,
    NATIONAL_DEX_WEEPINBELL,
    NATIONAL_DEX_CHIKORITA,
    NATIONAL_DEX_SWINUB,
    NATIONAL_DEX_EEVEE,
    NATIONAL_DEX_KRABBY,
    NATIONAL_DEX_CUBONE,
    NATIONAL_DEX_RALTS,
    NATIONAL_DEX_BULBASAUR,
    NATIONAL_DEX_EKANS,
    NATIONAL_DEX_NIDORAN_F,
    NATIONAL_DEX_PINECO,
    NATIONAL_DEX_FEEBAS,
    NATIONAL_DEX_OMANYTE,
    NATIONAL_DEX_ZUBAT,
    NATIONAL_DEX_CLEFAIRY,
    NATIONAL_DEX_MUDKIP,
    NATIONAL_DEX_SNUBBULL,
    NATIONAL_DEX_MAREEP,
    NATIONAL_DEX_CYNDAQUIL,
    NATIONAL_DEX_HORSEA,
    NATIONAL_DEX_CHARMANDER,
    NATIONAL_DEX_SUNFLORA,
    NATIONAL_DEX_MARILL,
    NATIONAL_DEX_WOOPER,
    NATIONAL_DEX_SPINARAK,
    NATIONAL_DEX_GLOOM,
    NATIONAL_DEX_LUVDISC,
    NATIONAL_DEX_TEDDIURSA,
    NATIONAL_DEX_NIDORAN_M,
    NATIONAL_DEX_SQUIRTLE,
    NATIONAL_DEX_WINGULL,
    NATIONAL_DEX_TOTODILE,
    NATIONAL_DEX_WEEZING,
    NATIONAL_DEX_VULPIX,
    NATIONAL_DEX_METAPOD,
    NATIONAL_DEX_SILCOON,
    NATIONAL_DEX_MAGIKARP,
    NATIONAL_DEX_KAKUNA,
    NATIONAL_DEX_GULPIN,
    NATIONAL_DEX_VOLTORB,
    NATIONAL_DEX_LEDYBA,
    NATIONAL_DEX_HOUNDOUR,
    NATIONAL_DEX_SKITTY,
    NATIONAL_DEX_SABLEYE,
    NATIONAL_DEX_MEDITITE,
    NATIONAL_DEX_CORPHISH,
    NATIONAL_DEX_AIPOM,
    NATIONAL_DEX_CASCOON,
    NATIONAL_DEX_MAWILE,
    NATIONAL_DEX_KABUTO,
    NATIONAL_DEX_WIGGLYTUFF,
    NATIONAL_DEX_SANDSHREW,
    NATIONAL_DEX_REMORAID,
    NATIONAL_DEX_NINJASK,
    NATIONAL_DEX_CHINCHOU,
    NATIONAL_DEX_POLIWAG,
    NATIONAL_DEX_ANORITH,
    NATIONAL_DEX_VENOMOTH,
    NATIONAL_DEX_BANETTE,
    NATIONAL_DEX_IVYSAUR,
    NATIONAL_DEX_FLAAFFY,
    NATIONAL_DEX_POOCHYENA,
    NATIONAL_DEX_WYNAUT,
    NATIONAL_DEX_DUNSPARCE,
    NATIONAL_DEX_XATU,
    NATIONAL_DEX_DUSKULL,
    NATIONAL_DEX_FARFETCHD,
    NATIONAL_DEX_TRAPINCH,
    NATIONAL_DEX_GOLDEEN,
    NATIONAL_DEX_ELECTRIKE,
    NATIONAL_DEX_VIBRAVA,
    NATIONAL_DEX_VICTREEBEL,
    NATIONAL_DEX_BAYLEEF,
    NATIONAL_DEX_DELIBIRD,
    NATIONAL_DEX_WHISMUR,
    NATIONAL_DEX_DRAGONAIR,
    NATIONAL_DEX_SNORUNT,
    NATIONAL_DEX_ZIGZAGOON,
    NATIONAL_DEX_ILLUMISE,
    NATIONAL_DEX_VOLBEAT,
    NATIONAL_DEX_RATICATE,
    NATIONAL_DEX_VILEPLUME,
    NATIONAL_DEX_QUILAVA,
    NATIONAL_DEX_CHARMELEON,
    NATIONAL_DEX_GROWLITHE,
    NATIONAL_DEX_COMBUSKEN,
    NATIONAL_DEX_MACHOP,
    NATIONAL_DEX_ABRA,
    NATIONAL_DEX_NIDORINO,
    NATIONAL_DEX_PSYDUCK,
    NATIONAL_DEX_SWELLOW,
    NATIONAL_DEX_NINETALES,
    NATIONAL_DEX_NIDORINA,
    NATIONAL_DEX_POLIWHIRL,
    NATIONAL_DEX_GEODUDE,
    NATIONAL_DEX_KIRLIA,
    NATIONAL_DEX_SHUCKLE,
    NATIONAL_DEX_ALTARIA,
    NATIONAL_DEX_CARVANHA,
    NATIONAL_DEX_TYROGUE,
    NATIONAL_DEX_HOOTHOOT,
    NATIONAL_DEX_MAGBY,
    NATIONAL_DEX_BALTOY,
    NATIONAL_DEX_GROVYLE,
    NATIONAL_DEX_KECLEON,
    NATIONAL_DEX_LANTURN,
    NATIONAL_DEX_WARTORTLE,
    NATIONAL_DEX_GOREBYSS,
    NATIONAL_DEX_RELICANTH,
    NATIONAL_DEX_ELEKID,
    NATIONAL_DEX_WHISCASH,
    NATIONAL_DEX_LILEEP,
    NATIONAL_DEX_NUMEL,
    NATIONAL_DEX_SLAKOTH,
    NATIONAL_DEX_JOLTEON,
    NATIONAL_DEX_CROCONAW,
    NATIONAL_DEX_FLAREON,
    NATIONAL_DEX_SEADRA,
    NATIONAL_DEX_ESPEON,
    NATIONAL_DEX_HUNTAIL,
    NATIONAL_DEX_UMBREON,
    NATIONAL_DEX_MARSHTOMP,
    NATIONAL_DEX_NUZLEAF,
    NATIONAL_DEX_SNEASEL,
    NATIONAL_DEX_MANKEY,
    NATIONAL_DEX_PELIPPER,
    NATIONAL_DEX_BEAUTIFLY,
    NATIONAL_DEX_OCTILLERY,
    NATIONAL_DEX_AZUMARILL,
    NATIONAL_DEX_WOBBUFFET,
    NATIONAL_DEX_VAPOREON,
    NATIONAL_DEX_SANDSLASH,
    NATIONAL_DEX_PARASECT,
    NATIONAL_DEX_BEEDRILL,
    NATIONAL_DEX_MUK,
    NATIONAL_DEX_PIDGEOTTO,
    NATIONAL_DEX_GRIMER,
    NATIONAL_DEX_RAICHU,
    NATIONAL_DEX_PONYTA,
    NATIONAL_DEX_ELECTABUZZ,
    NATIONAL_DEX_VENONAT,
    NATIONAL_DEX_SPOINK,
    NATIONAL_DEX_DUSCLOPS,
    NATIONAL_DEX_MEDICHAM,
    NATIONAL_DEX_DUSTOX,
    NATIONAL_DEX_PERSIAN,
    NATIONAL_DEX_BUTTERFREE,
    NATIONAL_DEX_PRIMEAPE,
    NATIONAL_DEX_DROWZEE,
    NATIONAL_DEX_FURRET,
    NATIONAL_DEX_PORYGON2,
    NATIONAL_DEX_LOMBRE,
    NATIONAL_DEX_LINOONE,
    NATIONAL_DEX_DELCATTY,
    NATIONAL_DEX_CRAWDAUNT,
    NATIONAL_DEX_DUGTRIO,
    NATIONAL_DEX_ARIADOS,
    NATIONAL_DEX_PHANPY,
    NATIONAL_DEX_POLITOED,
    NATIONAL_DEX_STARYU,
    NATIONAL_DEX_CHANSEY,
    NATIONAL_DEX_OMASTAR,
    NATIONAL_DEX_TANGELA,
    NATIONAL_DEX_SLUGMA,
    NATIONAL_DEX_HOUNDOOM,
    NATIONAL_DEX_LEDIAN,
    NATIONAL_DEX_SLOWPOKE,
    NATIONAL_DEX_PORYGON,
    NATIONAL_DEX_MIGHTYENA,
    NATIONAL_DEX_YANMA,
    NATIONAL_DEX_FEAROW,
    NATIONAL_DEX_SUDOWOODO,
    NATIONAL_DEX_SEAKING,
    NATIONAL_DEX_BRELOOM,
    NATIONAL_DEX_DODUO,
    NATIONAL_DEX_PIDGEOT,
    NATIONAL_DEX_SPHEAL,
    NATIONAL_DEX_CLEFABLE,
    NATIONAL_DEX_LATIAS,
    NATIONAL_DEX_MANECTRIC,
    NATIONAL_DEX_ZANGOOSE,
    NATIONAL_DEX_KABUTOPS,
    NATIONAL_DEX_GENGAR,
    NATIONAL_DEX_LOUDRED,
    NATIONAL_DEX_JYNX,
    NATIONAL_DEX_NOCTOWL,
    NATIONAL_DEX_GIRAFARIG,
    NATIONAL_DEX_BAGON,
    NATIONAL_DEX_MAGMAR,
    NATIONAL_DEX_MAROWAK,
    NATIONAL_DEX_TENTACOOL,
    NATIONAL_DEX_VIGOROTH,
    NATIONAL_DEX_BLISSEY,
    NATIONAL_DEX_ABSOL,
    NATIONAL_DEX_ALAKAZAM,
    NATIONAL_DEX_HITMONTOP,
    NATIONAL_DEX_GARDEVOIR,
    NATIONAL_DEX_GRANBULL,
    NATIONAL_DEX_HITMONLEE,
    NATIONAL_DEX_HITMONCHAN,
    NATIONAL_DEX_SKARMORY,
    NATIONAL_DEX_CACNEA,
    NATIONAL_DEX_BLAZIKEN,
    NATIONAL_DEX_SCEPTILE,
    NATIONAL_DEX_SEVIPER,
    NATIONAL_DEX_CLAMPERL,
    NATIONAL_DEX_ZAPDOS,
    NATIONAL_DEX_HERACROSS,
    NATIONAL_DEX_POLIWRATH,
    NATIONAL_DEX_MR_MIME,
    NATIONAL_DEX_PINSIR,
    NATIONAL_DEX_LUDICOLO,
    NATIONAL_DEX_TENTACRUEL,
    NATIONAL_DEX_GOLBAT,
    NATIONAL_DEX_MAGCARGO,
    NATIONAL_DEX_ARTICUNO,
    NATIONAL_DEX_PILOSWINE,
    NATIONAL_DEX_SCYTHER,
    NATIONAL_DEX_KADABRA,
    NATIONAL_DEX_SMEARGLE,
    NATIONAL_DEX_AERODACTYL,
    NATIONAL_DEX_SHIFTRY,
    NATIONAL_DEX_KINGLER,
    NATIONAL_DEX_NIDOQUEEN,
    NATIONAL_DEX_MAGNETON,
    NATIONAL_DEX_ARON,
    NATIONAL_DEX_LATIOS,
    NATIONAL_DEX_MOLTRES,
    NATIONAL_DEX_CRADILY,
    NATIONAL_DEX_DEOXYS,
    NATIONAL_DEX_AMPHAROS,
    NATIONAL_DEX_NIDOKING,
    NATIONAL_DEX_GLIGAR,
    NATIONAL_DEX_ARBOK,
    NATIONAL_DEX_LICKITUNG,
    NATIONAL_DEX_ELECTRODE,
    NATIONAL_DEX_ARMALDO,
    NATIONAL_DEX_MACHOKE,
    NATIONAL_DEX_STANTLER,
    NATIONAL_DEX_GRUMPIG,
    NATIONAL_DEX_LARVITAR,
    NATIONAL_DEX_CROBAT,
    NATIONAL_DEX_QUAGSIRE,
    NATIONAL_DEX_MILTANK,
    NATIONAL_DEX_HYPNO,
    NATIONAL_DEX_GOLDUCK,
    NATIONAL_DEX_CACTURNE,
    NATIONAL_DEX_SLOWBRO,
    NATIONAL_DEX_TYPHLOSION,
    NATIONAL_DEX_SLOWKING,
    NATIONAL_DEX_KANGASKHAN,
    NATIONAL_DEX_STARMIE,
    NATIONAL_DEX_SWALOT,
    NATIONAL_DEX_TORKOAL,
    NATIONAL_DEX_SWAMPERT,
    NATIONAL_DEX_FLYGON,
    NATIONAL_DEX_EXPLOUD,
    NATIONAL_DEX_DODRIO,
    NATIONAL_DEX_BLASTOISE,
    NATIONAL_DEX_MAKUHITA,
    NATIONAL_DEX_SEALEO,
    NATIONAL_DEX_TAUROS,
    NATIONAL_DEX_SHARPEDO,
    NATIONAL_DEX_FERALIGATR,
    NATIONAL_DEX_SEEL,
    NATIONAL_DEX_CHARIZARD,
    NATIONAL_DEX_RAPIDASH,
    NATIONAL_DEX_BELDUM,
    NATIONAL_DEX_NOSEPASS,
    NATIONAL_DEX_VENUSAUR,
    NATIONAL_DEX_TROPIUS,
    NATIONAL_DEX_MEGANIUM,
    NATIONAL_DEX_SALAMENCE,
    NATIONAL_DEX_GRAVELER,
    NATIONAL_DEX_CLAYDOL,
    NATIONAL_DEX_SHELGON,
    NATIONAL_DEX_RHYHORN,
    NATIONAL_DEX_SCIZOR,
    NATIONAL_DEX_DEWGONG,
    NATIONAL_DEX_RHYDON,
    NATIONAL_DEX_DONPHAN,
    NATIONAL_DEX_EXEGGUTOR,
    NATIONAL_DEX_LAIRON,
    NATIONAL_DEX_MEWTWO,
    NATIONAL_DEX_URSARING,
    NATIONAL_DEX_FORRETRESS,
    NATIONAL_DEX_MACHAMP,
    NATIONAL_DEX_WAILMER,
    NATIONAL_DEX_SLAKING,
    NATIONAL_DEX_CLOYSTER,
    NATIONAL_DEX_WALREIN,
    NATIONAL_DEX_PUPITAR,
    NATIONAL_DEX_KINGDRA,
    NATIONAL_DEX_SOLROCK,
    NATIONAL_DEX_ARCANINE,
    NATIONAL_DEX_MILOTIC,
    NATIONAL_DEX_LUNATONE,
    NATIONAL_DEX_REGICE,
    NATIONAL_DEX_RAIKOU,
    NATIONAL_DEX_SUICUNE,
    NATIONAL_DEX_ENTEI,
    NATIONAL_DEX_HO_OH,
    NATIONAL_DEX_TYRANITAR,
    NATIONAL_DEX_METANG,
    NATIONAL_DEX_REGISTEEL,
    NATIONAL_DEX_RAYQUAZA,
    NATIONAL_DEX_ONIX,
    NATIONAL_DEX_DRAGONITE,
    NATIONAL_DEX_LUGIA,
    NATIONAL_DEX_LAPRAS,
    NATIONAL_DEX_CAMERUPT,
    NATIONAL_DEX_MANTINE,
    NATIONAL_DEX_REGIROCK,
    NATIONAL_DEX_GYARADOS,
    NATIONAL_DEX_HARIYAMA,
    NATIONAL_DEX_GLALIE,
    NATIONAL_DEX_GOLEM,
    NATIONAL_DEX_KYOGRE,
    NATIONAL_DEX_AGGRON,
    NATIONAL_DEX_WAILORD,
    NATIONAL_DEX_STEELIX,
    NATIONAL_DEX_SNORLAX,
    NATIONAL_DEX_METAGROSS,
    NATIONAL_DEX_GROUDON
};

const u16 gPokedexOrder_Height[] =
{
    NATIONAL_DEX_DIGLETT,
    NATIONAL_DEX_AZURILL,
    NATIONAL_DEX_NATU,
    NATIONAL_DEX_WEEDLE,
    NATIONAL_DEX_PICHU,
    NATIONAL_DEX_CLEFFA,
    NATIONAL_DEX_TOGEPI,
    NATIONAL_DEX_CASTFORM,
    NATIONAL_DEX_IGGLYBUFF,
    NATIONAL_DEX_CATERPIE,
    NATIONAL_DEX_TAILLOW,
    NATIONAL_DEX_DITTO,
    NATIONAL_DEX_EEVEE,
    NATIONAL_DEX_ROSELIA,
    NATIONAL_DEX_SPEAROW,
    NATIONAL_DEX_PIDGEY,
    NATIONAL_DEX_SUNKERN,
    NATIONAL_DEX_SHELLDER,
    NATIONAL_DEX_RATTATA,
    NATIONAL_DEX_MAGNEMITE,
    NATIONAL_DEX_PARAS,
    NATIONAL_DEX_WURMPLE,
    NATIONAL_DEX_JIRACHI,
    NATIONAL_DEX_CUBONE,
    NATIONAL_DEX_MUDKIP,
    NATIONAL_DEX_WOOPER,
    NATIONAL_DEX_HORSEA,
    NATIONAL_DEX_MEOWTH,
    NATIONAL_DEX_NIDORAN_F,
    NATIONAL_DEX_SWINUB,
    NATIONAL_DEX_MEW,
    NATIONAL_DEX_SWABLU,
    NATIONAL_DEX_ARON,
    NATIONAL_DEX_PLUSLE,
    NATIONAL_DEX_MINUN,
    NATIONAL_DEX_EXEGGCUTE,
    NATIONAL_DEX_PIKACHU,
    NATIONAL_DEX_BELLOSSOM,
    NATIONAL_DEX_GULPIN,
    NATIONAL_DEX_ZIGZAGOON,
    NATIONAL_DEX_SHROOMISH,
    NATIONAL_DEX_OMANYTE,
    NATIONAL_DEX_CACNEA,
    NATIONAL_DEX_KRABBY,
    NATIONAL_DEX_RALTS,
    NATIONAL_DEX_HOPPIP,
    NATIONAL_DEX_TORCHIC,
    NATIONAL_DEX_CLAMPERL,
    NATIONAL_DEX_GEODUDE,
    NATIONAL_DEX_MARILL,
    NATIONAL_DEX_BARBOACH,
    NATIONAL_DEX_SMOOCHUM,
    NATIONAL_DEX_VOLTORB,
    NATIONAL_DEX_NINCADA,
    NATIONAL_DEX_SABLEYE,
    NATIONAL_DEX_MURKROW,
    NATIONAL_DEX_QWILFISH,
    NATIONAL_DEX_SQUIRTLE,
    NATIONAL_DEX_TREECKO,
    NATIONAL_DEX_BALTOY,
    NATIONAL_DEX_ODDISH,
    NATIONAL_DEX_LOTAD,
    NATIONAL_DEX_JIGGLYPUFF,
    NATIONAL_DEX_SURSKIT,
    NATIONAL_DEX_CYNDAQUIL,
    NATIONAL_DEX_KABUTO,
    NATIONAL_DEX_LINOONE,
    NATIONAL_DEX_TORKOAL,
    NATIONAL_DEX_NIDORAN_M,
    NATIONAL_DEX_SPINARAK,
    NATIONAL_DEX_MANKEY,
    NATIONAL_DEX_SEEDOT,
    NATIONAL_DEX_POOCHYENA,
    NATIONAL_DEX_PHANPY,
    NATIONAL_DEX_UNOWN,
    NATIONAL_DEX_CHINCHOU,
    NATIONAL_DEX_PORYGON2,
    NATIONAL_DEX_POLIWAG,
    NATIONAL_DEX_BAGON,
    NATIONAL_DEX_FEEBAS,
    NATIONAL_DEX_SHUPPET,
    NATIONAL_DEX_TOTODILE,
    NATIONAL_DEX_CELEBI,
    NATIONAL_DEX_WYNAUT,
    NATIONAL_DEX_SANDSHREW,
    NATIONAL_DEX_CHIMECHO,
    NATIONAL_DEX_LUVDISC,
    NATIONAL_DEX_HOUNDOUR,
    NATIONAL_DEX_SILCOON,
    NATIONAL_DEX_ELECTRIKE,
    NATIONAL_DEX_CHARMANDER,
    NATIONAL_DEX_MEDITITE,
    NATIONAL_DEX_WINGULL,
    NATIONAL_DEX_REMORAID,
    NATIONAL_DEX_CORPHISH,
    NATIONAL_DEX_CORSOLA,
    NATIONAL_DEX_ILLUMISE,
    NATIONAL_DEX_SNUBBULL,
    NATIONAL_DEX_VULPIX,
    NATIONAL_DEX_LARVITAR,
    NATIONAL_DEX_BELDUM,
    NATIONAL_DEX_WHISMUR,
    NATIONAL_DEX_PINECO,
    NATIONAL_DEX_ELEKID,
    NATIONAL_DEX_CLEFAIRY,
    NATIONAL_DEX_SHUCKLE,
    NATIONAL_DEX_TEDDIURSA,
    NATIONAL_DEX_KAKUNA,
    NATIONAL_DEX_SKITTY,
    NATIONAL_DEX_TOGETIC,
    NATIONAL_DEX_GOLDEEN,
    NATIONAL_DEX_MAWILE,
    NATIONAL_DEX_MAREEP,
    NATIONAL_DEX_SKIPLOOM,
    NATIONAL_DEX_KOFFING,
    NATIONAL_DEX_DUGTRIO,
    NATIONAL_DEX_CASCOON,
    NATIONAL_DEX_NUMEL,
    NATIONAL_DEX_ANORITH,
    NATIONAL_DEX_VOLBEAT,
    NATIONAL_DEX_HOOTHOOT,
    NATIONAL_DEX_TRAPINCH,
    NATIONAL_DEX_SPOINK,
    NATIONAL_DEX_METAPOD,
    NATIONAL_DEX_BELLSPROUT,
    NATIONAL_DEX_SNORUNT,
    NATIONAL_DEX_RATICATE,
    NATIONAL_DEX_MARSHTOMP,
    NATIONAL_DEX_SWELLOW,
    NATIONAL_DEX_MAGBY,
    NATIONAL_DEX_GROWLITHE,
    NATIONAL_DEX_MISDREAVUS,
    NATIONAL_DEX_BULBASAUR,
    NATIONAL_DEX_TYROGUE,
    NATIONAL_DEX_SLUGMA,
    NATIONAL_DEX_SLAKOTH,
    NATIONAL_DEX_KIRLIA,
    NATIONAL_DEX_AIPOM,
    NATIONAL_DEX_JOLTEON,
    NATIONAL_DEX_NIDORINA,
    NATIONAL_DEX_AZUMARILL,
    NATIONAL_DEX_SHEDINJA,
    NATIONAL_DEX_MACHOP,
    NATIONAL_DEX_NINJASK,
    NATIONAL_DEX_MASQUERAIN,
    NATIONAL_DEX_DUSKULL,
    NATIONAL_DEX_SUNFLORA,
    NATIONAL_DEX_JUMPLUFF,
    NATIONAL_DEX_STARYU,
    NATIONAL_DEX_FLAAFFY,
    NATIONAL_DEX_SPHEAL,
    NATIONAL_DEX_PSYDUCK,
    NATIONAL_DEX_MAGCARGO,
    NATIONAL_DEX_FARFETCHD,
    NATIONAL_DEX_ZUBAT,
    NATIONAL_DEX_PORYGON,
    NATIONAL_DEX_SENTRET,
    NATIONAL_DEX_CARVANHA,
    NATIONAL_DEX_GLOOM,
    NATIONAL_DEX_RAICHU,
    NATIONAL_DEX_MAGIKARP,
    NATIONAL_DEX_SNEASEL,
    NATIONAL_DEX_LAIRON,
    NATIONAL_DEX_COMBUSKEN,
    NATIONAL_DEX_OCTILLERY,
    NATIONAL_DEX_NIDORINO,
    NATIONAL_DEX_FLAREON,
    NATIONAL_DEX_DELIBIRD,
    NATIONAL_DEX_TENTACOOL,
    NATIONAL_DEX_ABRA,
    NATIONAL_DEX_GROVYLE,
    NATIONAL_DEX_WHISCASH,
    NATIONAL_DEX_QUILAVA,
    NATIONAL_DEX_ESPEON,
    NATIONAL_DEX_GRIMER,
    NATIONAL_DEX_CHIKORITA,
    NATIONAL_DEX_GRUMPIG,
    NATIONAL_DEX_NOSEPASS,
    NATIONAL_DEX_PERSIAN,
    NATIONAL_DEX_MIGHTYENA,
    NATIONAL_DEX_VENONAT,
    NATIONAL_DEX_MAGNETON,
    NATIONAL_DEX_PONYTA,
    NATIONAL_DEX_MAKUHITA,
    NATIONAL_DEX_LUNATONE,
    NATIONAL_DEX_SANDSLASH,
    NATIONAL_DEX_DROWZEE,
    NATIONAL_DEX_TANGELA,
    NATIONAL_DEX_PRIMEAPE,
    NATIONAL_DEX_LEDYBA,
    NATIONAL_DEX_WIGGLYTUFF,
    NATIONAL_DEX_PARASECT,
    NATIONAL_DEX_OMASTAR,
    NATIONAL_DEX_LOUDRED,
    NATIONAL_DEX_WARTORTLE,
    NATIONAL_DEX_GRAVELER,
    NATIONAL_DEX_UMBREON,
    NATIONAL_DEX_LILEEP,
    NATIONAL_DEX_POLIWHIRL,
    NATIONAL_DEX_VAPOREON,
    NATIONAL_DEX_BEEDRILL,
    NATIONAL_DEX_MAROWAK,
    NATIONAL_DEX_WEEPINBELL,
    NATIONAL_DEX_RELICANTH,
    NATIONAL_DEX_RHYHORN,
    NATIONAL_DEX_IVYSAUR,
    NATIONAL_DEX_KECLEON,
    NATIONAL_DEX_NUZLEAF,
    NATIONAL_DEX_BEAUTIFLY,
    NATIONAL_DEX_PIDGEOTTO,
    NATIONAL_DEX_ARIADOS,
    NATIONAL_DEX_SEEL,
    NATIONAL_DEX_POLITOED,
    NATIONAL_DEX_CROCONAW,
    NATIONAL_DEX_CHANSEY,
    NATIONAL_DEX_BANETTE,
    NATIONAL_DEX_DONPHAN,
    NATIONAL_DEX_STARMIE,
    NATIONAL_DEX_CHARMELEON,
    NATIONAL_DEX_PILOSWINE,
    NATIONAL_DEX_BUTTERFREE,
    NATIONAL_DEX_VIBRAVA,
    NATIONAL_DEX_ELECTABUZZ,
    NATIONAL_DEX_CRAWDAUNT,
    NATIONAL_DEX_DELCATTY,
    NATIONAL_DEX_ALTARIA,
    NATIONAL_DEX_SHELGON,
    NATIONAL_DEX_NINETALES,
    NATIONAL_DEX_GLIGAR,
    NATIONAL_DEX_SEALEO,
    NATIONAL_DEX_SPINDA,
    NATIONAL_DEX_PUPITAR,
    NATIONAL_DEX_SLOWPOKE,
    NATIONAL_DEX_SOLROCK,
    NATIONAL_DEX_MILTANK,
    NATIONAL_DEX_FEAROW,
    NATIONAL_DEX_VILEPLUME,
    NATIONAL_DEX_MUK,
    NATIONAL_DEX_FORRETRESS,
    NATIONAL_DEX_SUDOWOODO,
    NATIONAL_DEX_ABSOL,
    NATIONAL_DEX_YANMA,
    NATIONAL_DEX_DUSTOX,
    NATIONAL_DEX_LICKITUNG,
    NATIONAL_DEX_SMEARGLE,
    NATIONAL_DEX_LANTURN,
    NATIONAL_DEX_ELECTRODE,
    NATIONAL_DEX_LOMBRE,
    NATIONAL_DEX_BRELOOM,
    NATIONAL_DEX_BAYLEEF,
    NATIONAL_DEX_SEADRA,
    NATIONAL_DEX_WEEZING,
    NATIONAL_DEX_PELIPPER,
    NATIONAL_DEX_METANG,
    NATIONAL_DEX_NIDOQUEEN,
    NATIONAL_DEX_CACTURNE,
    NATIONAL_DEX_SHIFTRY,
    NATIONAL_DEX_MEDICHAM,
    NATIONAL_DEX_ZANGOOSE,
    NATIONAL_DEX_KABUTOPS,
    NATIONAL_DEX_KINGLER,
    NATIONAL_DEX_KADABRA,
    NATIONAL_DEX_SEAKING,
    NATIONAL_DEX_CLEFABLE,
    NATIONAL_DEX_MAGMAR,
    NATIONAL_DEX_WOBBUFFET,
    NATIONAL_DEX_GASTLY,
    NATIONAL_DEX_MR_MIME,
    NATIONAL_DEX_POLIWRATH,
    NATIONAL_DEX_TAUROS,
    NATIONAL_DEX_LATIAS,
    NATIONAL_DEX_AMPHAROS,
    NATIONAL_DEX_VIGOROTH,
    NATIONAL_DEX_LEDIAN,
    NATIONAL_DEX_GOLEM,
    NATIONAL_DEX_WALREIN,
    NATIONAL_DEX_DODUO,
    NATIONAL_DEX_HOUNDOOM,
    NATIONAL_DEX_NIDOKING,
    NATIONAL_DEX_JYNX,
    NATIONAL_DEX_HITMONCHAN,
    NATIONAL_DEX_STANTLER,
    NATIONAL_DEX_GRANBULL,
    NATIONAL_DEX_HITMONTOP,
    NATIONAL_DEX_QUAGSIRE,
    NATIONAL_DEX_CLAYDOL,
    NATIONAL_DEX_SWAMPERT,
    NATIONAL_DEX_BLISSEY,
    NATIONAL_DEX_LUDICOLO,
    NATIONAL_DEX_EXPLOUD,
    NATIONAL_DEX_DUNSPARCE,
    NATIONAL_DEX_PINSIR,
    NATIONAL_DEX_CLOYSTER,
    NATIONAL_DEX_MACHOKE,
    NATIONAL_DEX_GIRAFARIG,
    NATIONAL_DEX_PIDGEOT,
    NATIONAL_DEX_XATU,
    NATIONAL_DEX_CRADILY,
    NATIONAL_DEX_HITMONLEE,
    NATIONAL_DEX_VENOMOTH,
    NATIONAL_DEX_GENGAR,
    NATIONAL_DEX_HERACROSS,
    NATIONAL_DEX_GLALIE,
    NATIONAL_DEX_SCYTHER,
    NATIONAL_DEX_SALAMENCE,
    NATIONAL_DEX_MANECTRIC,
    NATIONAL_DEX_ARMALDO,
    NATIONAL_DEX_ALAKAZAM,
    NATIONAL_DEX_HYPNO,
    NATIONAL_DEX_NOCTOWL,
    NATIONAL_DEX_TENTACRUEL,
    NATIONAL_DEX_DUSCLOPS,
    NATIONAL_DEX_ZAPDOS,
    NATIONAL_DEX_GOLBAT,
    NATIONAL_DEX_METAGROSS,
    NATIONAL_DEX_GARDEVOIR,
    NATIONAL_DEX_BLASTOISE,
    NATIONAL_DEX_SLOWBRO,
    NATIONAL_DEX_HAUNTER,
    NATIONAL_DEX_MACHAMP,
    NATIONAL_DEX_REGIROCK,
    NATIONAL_DEX_SWALOT,
    NATIONAL_DEX_SCEPTILE,
    NATIONAL_DEX_SKARMORY,
    NATIONAL_DEX_GOLDUCK,
    NATIONAL_DEX_DEOXYS,
    NATIONAL_DEX_VICTREEBEL,
    NATIONAL_DEX_RAPIDASH,
    NATIONAL_DEX_CHARIZARD,
    NATIONAL_DEX_HUNTAIL,
    NATIONAL_DEX_DEWGONG,
    NATIONAL_DEX_ARTICUNO,
    NATIONAL_DEX_TYPHLOSION,
    NATIONAL_DEX_AERODACTYL,
    NATIONAL_DEX_GOREBYSS,
    NATIONAL_DEX_URSARING,
    NATIONAL_DEX_MEGANIUM,
    NATIONAL_DEX_REGICE,
    NATIONAL_DEX_SCIZOR,
    NATIONAL_DEX_KINGDRA,
    NATIONAL_DEX_DRATINI,
    NATIONAL_DEX_DODRIO,
    NATIONAL_DEX_SHARPEDO,
    NATIONAL_DEX_CROBAT,
    NATIONAL_DEX_FURRET,
    NATIONAL_DEX_ARCANINE,
    NATIONAL_DEX_RAIKOU,
    NATIONAL_DEX_BLAZIKEN,
    NATIONAL_DEX_CAMERUPT,
    NATIONAL_DEX_RHYDON,
    NATIONAL_DEX_REGISTEEL,
    NATIONAL_DEX_EKANS,
    NATIONAL_DEX_FLYGON,
    NATIONAL_DEX_TROPIUS,
    NATIONAL_DEX_LATIOS,
    NATIONAL_DEX_SUICUNE,
    NATIONAL_DEX_MOLTRES,
    NATIONAL_DEX_VENUSAUR,
    NATIONAL_DEX_EXEGGUTOR,
    NATIONAL_DEX_SLOWKING,
    NATIONAL_DEX_TYRANITAR,
    NATIONAL_DEX_SLAKING,
    NATIONAL_DEX_WAILMER,
    NATIONAL_DEX_MEWTWO,
    NATIONAL_DEX_AGGRON,
    NATIONAL_DEX_SNORLAX,
    NATIONAL_DEX_MANTINE,
    NATIONAL_DEX_ENTEI,
    NATIONAL_DEX_DRAGONITE,
    NATIONAL_DEX_KANGASKHAN,
    NATIONAL_DEX_HARIYAMA,
    NATIONAL_DEX_FERALIGATR,
    NATIONAL_DEX_LAPRAS,
    NATIONAL_DEX_SEVIPER,
    NATIONAL_DEX_ARBOK,
    NATIONAL_DEX_GROUDON,
    NATIONAL_DEX_HO_OH,
    NATIONAL_DEX_DRAGONAIR,
    NATIONAL_DEX_KYOGRE,
    NATIONAL_DEX_LUGIA,
    NATIONAL_DEX_MILOTIC,
    NATIONAL_DEX_GYARADOS,
    NATIONAL_DEX_RAYQUAZA,
    NATIONAL_DEX_ONIX,
    NATIONAL_DEX_STEELIX,
    NATIONAL_DEX_WAILORD
};

const u16 gPokedexOrder_Type[] =
{
    SPECIES_RATTATA,
    SPECIES_RATICATE,
    SPECIES_CLEFAIRY,
    SPECIES_CLEFABLE,
    SPECIES_JIGGLYPUFF,
    SPECIES_WIGGLYTUFF,
    SPECIES_MEOWTH,
    SPECIES_PERSIAN,
    SPECIES_LICKITUNG,
    SPECIES_CHANSEY,
    SPECIES_KANGASKHAN,
    SPECIES_TAUROS,
    SPECIES_DITTO,
    SPECIES_EEVEE,
    SPECIES_PORYGON,
    SPECIES_SNORLAX,
    SPECIES_SENTRET,
    SPECIES_FURRET,
    SPECIES_CLEFFA,
    SPECIES_IGGLYBUFF,
    SPECIES_TOGEPI,
    SPECIES_AIPOM,
    SPECIES_DUNSPARCE,
    SPECIES_SNUBBULL,
    SPECIES_GRANBULL,
    SPECIES_TEDDIURSA,
    SPECIES_URSARING,
    SPECIES_PORYGON2,
    SPECIES_STANTLER,
    SPECIES_SMEARGLE,
    SPECIES_MILTANK,
    SPECIES_BLISSEY,
    SPECIES_ZIGZAGOON,
    SPECIES_LINOONE,
    SPECIES_SLAKOTH,
    SPECIES_VIGOROTH,
    SPECIES_SLAKING,
    SPECIES_WHISMUR,
    SPECIES_LOUDRED,
    SPECIES_EXPLOUD,
    SPECIES_AZURILL,
    SPECIES_SKITTY,
    SPECIES_DELCATTY,
    SPECIES_SPINDA,
    SPECIES_ZANGOOSE,
    SPECIES_CASTFORM,
    SPECIES_KECLEON,
    SPECIES_OLD_UNOWN_B,
    SPECIES_OLD_UNOWN_C,
    SPECIES_OLD_UNOWN_D,
    SPECIES_OLD_UNOWN_E,
    SPECIES_OLD_UNOWN_F,
    SPECIES_OLD_UNOWN_G,
    SPECIES_OLD_UNOWN_H,
    SPECIES_OLD_UNOWN_I,
    SPECIES_OLD_UNOWN_J,
    SPECIES_OLD_UNOWN_K,
    SPECIES_OLD_UNOWN_L,
    SPECIES_OLD_UNOWN_M,
    SPECIES_OLD_UNOWN_N,
    SPECIES_OLD_UNOWN_O,
    SPECIES_OLD_UNOWN_P,
    SPECIES_OLD_UNOWN_Q,
    SPECIES_OLD_UNOWN_R,
    SPECIES_OLD_UNOWN_S,
    SPECIES_OLD_UNOWN_T,
    SPECIES_OLD_UNOWN_U,
    SPECIES_OLD_UNOWN_V,
    SPECIES_OLD_UNOWN_W,
    SPECIES_OLD_UNOWN_X,
    SPECIES_OLD_UNOWN_Y,
    SPECIES_OLD_UNOWN_Z,
    SPECIES_PIDGEY,
    SPECIES_PIDGEOTTO,
    SPECIES_PIDGEOT,
    SPECIES_SPEAROW,
    SPECIES_FEAROW,
    SPECIES_FARFETCHD,
    SPECIES_DODUO,
    SPECIES_DODRIO,
    SPECIES_HOOTHOOT,
    SPECIES_NOCTOWL,
    SPECIES_TOGETIC,
    SPECIES_TAILLOW,
    SPECIES_SWELLOW,
    SPECIES_SWABLU,
    SPECIES_GIRAFARIG,
    SPECIES_MANKEY,
    SPECIES_PRIMEAPE,
    SPECIES_MACHOP,
    SPECIES_MACHOKE,
    SPECIES_MACHAMP,
    SPECIES_HITMONLEE,
    SPECIES_HITMONCHAN,
    SPECIES_TYROGUE,
    SPECIES_HITMONTOP,
    SPECIES_MAKUHITA,
    SPECIES_HARIYAMA,
    SPECIES_MEDITITE,
    SPECIES_MEDICHAM,
    SPECIES_EKANS,
    SPECIES_ARBOK,
    SPECIES_NIDORAN_F,
    SPECIES_NIDORINA,
    SPECIES_NIDORAN_M,
    SPECIES_NIDORINO,
    SPECIES_GRIMER,
    SPECIES_MUK,
    SPECIES_KOFFING,
    SPECIES_WEEZING,
    SPECIES_GULPIN,
    SPECIES_SWALOT,
    SPECIES_SEVIPER,
    SPECIES_ZUBAT,
    SPECIES_GOLBAT,
    SPECIES_CROBAT,
    SPECIES_NIDOQUEEN,
    SPECIES_NIDOKING,
    SPECIES_SANDSHREW,
    SPECIES_SANDSLASH,
    SPECIES_DIGLETT,
    SPECIES_DUGTRIO,
    SPECIES_CUBONE,
    SPECIES_MAROWAK,
    SPECIES_PHANPY,
    SPECIES_DONPHAN,
    SPECIES_TRAPINCH,
    SPECIES_GROUDON,
    SPECIES_GLIGAR,
    SPECIES_RHYHORN,
    SPECIES_RHYDON,
    SPECIES_BALTOY,
    SPECIES_CLAYDOL,
    SPECIES_VIBRAVA,
    SPECIES_FLYGON,
    SPECIES_SUDOWOODO,
    SPECIES_NOSEPASS,
    SPECIES_REGIROCK,
    SPECIES_AERODACTYL,
    SPECIES_GEODUDE,
    SPECIES_GRAVELER,
    SPECIES_GOLEM,
    SPECIES_ONIX,
    SPECIES_LARVITAR,
    SPECIES_PUPITAR,
    SPECIES_ANORITH,
    SPECIES_ARMALDO,
    SPECIES_OMANYTE,
    SPECIES_OMASTAR,
    SPECIES_KABUTO,
    SPECIES_KABUTOPS,
    SPECIES_LILEEP,
    SPECIES_CRADILY,
    SPECIES_LUNATONE,
    SPECIES_SOLROCK,
    SPECIES_TYRANITAR,
    SPECIES_CATERPIE,
    SPECIES_METAPOD,
    SPECIES_PINSIR,
    SPECIES_PINECO,
    SPECIES_WURMPLE,
    SPECIES_SILCOON,
    SPECIES_CASCOON,
    SPECIES_VOLBEAT,
    SPECIES_ILLUMISE,
    SPECIES_HERACROSS,
    SPECIES_BUTTERFREE,
    SPECIES_SCYTHER,
    SPECIES_LEDYBA,
    SPECIES_LEDIAN,
    SPECIES_YANMA,
    SPECIES_BEAUTIFLY,
    SPECIES_MASQUERAIN,
    SPECIES_NINJASK,
    SPECIES_WEEDLE,
    SPECIES_KAKUNA,
    SPECIES_BEEDRILL,
    SPECIES_VENONAT,
    SPECIES_VENOMOTH,
    SPECIES_SPINARAK,
    SPECIES_ARIADOS,
    SPECIES_DUSTOX,
    SPECIES_NINCADA,
    SPECIES_SHUCKLE,
    SPECIES_SHEDINJA,
    SPECIES_FORRETRESS,
    SPECIES_SCIZOR,
    SPECIES_SURSKIT,
    SPECIES_PARAS,
    SPECIES_PARASECT,
    SPECIES_MISDREAVUS,
    SPECIES_SHUPPET,
    SPECIES_BANETTE,
    SPECIES_DUSKULL,
    SPECIES_DUSCLOPS,
    SPECIES_GASTLY,
    SPECIES_HAUNTER,
    SPECIES_GENGAR,
    SPECIES_MAWILE,
    SPECIES_REGISTEEL,
    SPECIES_SKARMORY,
    SPECIES_STEELIX,
    SPECIES_ARON,
    SPECIES_LAIRON,
    SPECIES_AGGRON,
    SPECIES_BELDUM,
    SPECIES_METANG,
    SPECIES_METAGROSS,
    SPECIES_JIRACHI,
    SPECIES_CHARMANDER,
    SPECIES_CHARMELEON,
    SPECIES_VULPIX,
    SPECIES_NINETALES,
    SPECIES_GROWLITHE,
    SPECIES_ARCANINE,
    SPECIES_PONYTA,
    SPECIES_RAPIDASH,
    SPECIES_MAGMAR,
    SPECIES_FLAREON,
    SPECIES_CYNDAQUIL,
    SPECIES_QUILAVA,
    SPECIES_TYPHLOSION,
    SPECIES_SLUGMA,
    SPECIES_MAGBY,
    SPECIES_ENTEI,
    SPECIES_TORCHIC,
    SPECIES_TORKOAL,
    SPECIES_COMBUSKEN,
    SPECIES_BLAZIKEN,
    SPECIES_CHARIZARD,
    SPECIES_MOLTRES,
    SPECIES_HO_OH,
    SPECIES_NUMEL,
    SPECIES_CAMERUPT,
    SPECIES_MAGCARGO,
    SPECIES_SQUIRTLE,
    SPECIES_WARTORTLE,
    SPECIES_BLASTOISE,
    SPECIES_PSYDUCK,
    SPECIES_GOLDUCK,
    SPECIES_POLIWAG,
    SPECIES_POLIWHIRL,
    SPECIES_SEEL,
    SPECIES_SHELLDER,
    SPECIES_KRABBY,
    SPECIES_KINGLER,
    SPECIES_HORSEA,
    SPECIES_SEADRA,
    SPECIES_GOLDEEN,
    SPECIES_SEAKING,
    SPECIES_STARYU,
    SPECIES_MAGIKARP,
    SPECIES_VAPOREON,
    SPECIES_TOTODILE,
    SPECIES_CROCONAW,
    SPECIES_FERALIGATR,
    SPECIES_MARILL,
    SPECIES_AZUMARILL,
    SPECIES_POLITOED,
    SPECIES_REMORAID,
    SPECIES_OCTILLERY,
    SPECIES_SUICUNE,
    SPECIES_MUDKIP,
    SPECIES_WAILMER,
    SPECIES_WAILORD,
    SPECIES_CORPHISH,
    SPECIES_FEEBAS,
    SPECIES_MILOTIC,
    SPECIES_CLAMPERL,
    SPECIES_HUNTAIL,
    SPECIES_GOREBYSS,
    SPECIES_LUVDISC,
    SPECIES_KYOGRE,
    SPECIES_POLIWRATH,
    SPECIES_GYARADOS,
    SPECIES_MANTINE,
    SPECIES_WINGULL,
    SPECIES_PELIPPER,
    SPECIES_TENTACOOL,
    SPECIES_TENTACRUEL,
    SPECIES_QWILFISH,
    SPECIES_WOOPER,
    SPECIES_QUAGSIRE,
    SPECIES_MARSHTOMP,
    SPECIES_SWAMPERT,
    SPECIES_BARBOACH,
    SPECIES_WHISCASH,
    SPECIES_CORSOLA,
    SPECIES_RELICANTH,
    SPECIES_LOTAD,
    SPECIES_LOMBRE,
    SPECIES_LUDICOLO,
    SPECIES_CHINCHOU,
    SPECIES_LANTURN,
    SPECIES_SLOWPOKE,
    SPECIES_SLOWBRO,
    SPECIES_STARMIE,
    SPECIES_SLOWKING,
    SPECIES_DEWGONG,
    SPECIES_CLOYSTER,
    SPECIES_LAPRAS,
    SPECIES_KINGDRA,
    SPECIES_CARVANHA,
    SPECIES_SHARPEDO,
    SPECIES_CRAWDAUNT,
    SPECIES_TANGELA,
    SPECIES_CHIKORITA,
    SPECIES_BAYLEEF,
    SPECIES_MEGANIUM,
    SPECIES_BELLOSSOM,
    SPECIES_SUNKERN,
    SPECIES_SUNFLORA,
    SPECIES_TREECKO,
    SPECIES_GROVYLE,
    SPECIES_SCEPTILE,
    SPECIES_SEEDOT,
    SPECIES_SHROOMISH,
    SPECIES_CACNEA,
    SPECIES_BRELOOM,
    SPECIES_HOPPIP,
    SPECIES_SKIPLOOM,
    SPECIES_JUMPLUFF,
    SPECIES_TROPIUS,
    SPECIES_BULBASAUR,
    SPECIES_IVYSAUR,
    SPECIES_VENUSAUR,
    SPECIES_ODDISH,
    SPECIES_GLOOM,
    SPECIES_VILEPLUME,
    SPECIES_BELLSPROUT,
    SPECIES_WEEPINBELL,
    SPECIES_VICTREEBEL,
    SPECIES_ROSELIA,
    SPECIES_EXEGGCUTE,
    SPECIES_EXEGGUTOR,
    SPECIES_NUZLEAF,
    SPECIES_SHIFTRY,
    SPECIES_CACTURNE,
    SPECIES_PIKACHU,
    SPECIES_RAICHU,
    SPECIES_VOLTORB,
    SPECIES_ELECTRODE,
    SPECIES_ELECTABUZZ,
    SPECIES_JOLTEON,
    SPECIES_PICHU,
    SPECIES_MAREEP,
    SPECIES_FLAAFFY,
    SPECIES_AMPHAROS,
    SPECIES_ELEKID,
    SPECIES_RAIKOU,
    SPECIES_ELECTRIKE,
    SPECIES_MANECTRIC,
    SPECIES_PLUSLE,
    SPECIES_MINUN,
    SPECIES_ZAPDOS,
    SPECIES_MAGNEMITE,
    SPECIES_MAGNETON,
    SPECIES_ABRA,
    SPECIES_KADABRA,
    SPECIES_ALAKAZAM,
    SPECIES_DROWZEE,
    SPECIES_HYPNO,
    SPECIES_MR_MIME,
    SPECIES_MEWTWO,
    SPECIES_MEW,
    SPECIES_ESPEON,
    SPECIES_UNOWN,
    SPECIES_WOBBUFFET,
    SPECIES_RALTS,
    SPECIES_KIRLIA,
    SPECIES_GARDEVOIR,
    SPECIES_SPOINK,
    SPECIES_GRUMPIG,
    SPECIES_CHIMECHO,
    SPECIES_WYNAUT,
    SPECIES_DEOXYS,
    SPECIES_NATU,
    SPECIES_XATU,
    SPECIES_LUGIA,
    SPECIES_CELEBI,
    SPECIES_SNORUNT,
    SPECIES_GLALIE,
    SPECIES_REGICE,
    SPECIES_ARTICUNO,
    SPECIES_DELIBIRD,
    SPECIES_SWINUB,
    SPECIES_PILOSWINE,
    SPECIES_SPHEAL,
    SPECIES_SEALEO,
    SPECIES_WALREIN,
    SPECIES_JYNX,
    SPECIES_SMOOCHUM,
    SPECIES_DRATINI,
    SPECIES_DRAGONAIR,
    SPECIES_BAGON,
    SPECIES_SHELGON,
    SPECIES_DRAGONITE,
    SPECIES_ALTARIA,
    SPECIES_SALAMENCE,
    SPECIES_RAYQUAZA,
    SPECIES_LATIAS,
    SPECIES_LATIOS,
    SPECIES_UMBREON,
    SPECIES_POOCHYENA,
    SPECIES_MIGHTYENA,
    SPECIES_ABSOL,
    SPECIES_MURKROW,
    SPECIES_SABLEYE,
    SPECIES_HOUNDOUR,
    SPECIES_HOUNDOOM,
    SPECIES_SNEASEL
};
// ===== END src/data/pokemon/pokedex_orders.h =====

static const u8 gExpandedPlaceholder_PokedexDescription[] = _("");

// ===== BEGIN src/data/pokemon/pokedex_text.h =====
#if defined(FIRERED)
// ===== BEGIN src/data/pokemon/pokedex_text_fr.h =====
const u8 gDummyPokedexText[] = _(
    "This is a newly discovered POKéMON. It is\n"
    "currently under investigation. No detailed\n"
    "information is available at this time.");

const u8 gDummyPokedexTextUnused[] = _("");

const u8 gBulbasaurPokedexText[] = _(
    "There is a plant seed on its back right\n"
    "from the day this POKéMON is born.\n"
    "The seed slowly grows larger.");

const u8 gBulbasaurPokedexTextUnused[] = _("");

const u8 gIvysaurPokedexText[] = _(
    "There is a plant bulb on its back.\n"
    "When it absorbs nutrients, the bulb is said\n"
    "to blossom into a large flower.");

const u8 gIvysaurPokedexTextUnused[] = _("");

const u8 gVenusaurPokedexText[] = _(
    "A bewitching aroma wafts from its flower.\n"
    "The fragrance becalms those engaged in\n"
    "a battle.");

const u8 gVenusaurPokedexTextUnused[] = _("");

const u8 gCharmanderPokedexText[] = _(
    "From the time it is born, a flame burns\n"
    "at the tip of its tail. Its life would end\n"
    "if the flame were to go out.");

const u8 gCharmanderPokedexTextUnused[] = _("");

const u8 gCharmeleonPokedexText[] = _(
    "It lashes about with its tail to knock\n"
    "down its foe. It then tears up the fallen\n"
    "opponent with sharp claws.");

const u8 gCharmeleonPokedexTextUnused[] = _("");

const u8 gCharizardPokedexText[] = _(
    "Its wings can carry this POKéMON close to\n"
    "an altitude of 4,600 feet. It blows out\n"
    "fire at very high temperatures.");

const u8 gCharizardPokedexTextUnused[] = _("");

const u8 gSquirtlePokedexText[] = _(
    "When it retracts its long neck into its\n"
    "shell, it squirts out water with vigorous\n"
    "force.");

const u8 gSquirtlePokedexTextUnused[] = _("");

const u8 gWartortlePokedexText[] = _(
    "This POKéMON is very popular as a pet.\n"
    "Its fur-covered tail is a symbol of its\n"
    "longevity.");

const u8 gWartortlePokedexTextUnused[] = _("");

const u8 gBlastoisePokedexText[] = _(
    "It crushes its foe under its heavy body\n"
    "to cause fainting. In a pinch, it will\n"
    "withdraw inside its shell.");

const u8 gBlastoisePokedexTextUnused[] = _("");

const u8 gCaterpiePokedexText[] = _(
    "It is covered with a green skin. When it\n"
    "grows, it sheds the skin, covers itself\n"
    "with silk, and becomes a cocoon.");

const u8 gCaterpiePokedexTextUnused[] = _("");

const u8 gMetapodPokedexText[] = _(
    "Even though it is encased in a sturdy\n"
    "shell, the body inside is tender.\n"
    "It can't withstand a harsh attack.");

const u8 gMetapodPokedexTextUnused[] = _("");

const u8 gButterfreePokedexText[] = _(
    "The wings are protected by rain-repellent\n"
    "dust. As a result, this POKéMON can fly\n"
    "about even in rain.");

const u8 gButterfreePokedexTextUnused[] = _("");

const u8 gWeedlePokedexText[] = _(
    "Often found in forests and grasslands.\n"
    "It has a sharp, toxic barb of around two\n"
    "inches on top of its head.");

const u8 gWeedlePokedexTextUnused[] = _("");

const u8 gKakunaPokedexText[] = _(
    "This POKéMON is in a temporary stage\n"
    "while making its body. It is almost\n"
    "completely unable to move on its own.");

const u8 gKakunaPokedexTextUnused[] = _("");

const u8 gBeedrillPokedexText[] = _(
    "May appear in a swarm. Flies at violent\n"
    "speeds, all the while stabbing with the\n"
    "toxic stinger on its rear.");

const u8 gBeedrillPokedexTextUnused[] = _("");

const u8 gPidgeyPokedexText[] = _(
    "Does not like to fight. It hides in\n"
    "tall grass and so on, foraging for food\n"
    "such as small bugs.");

const u8 gPidgeyPokedexTextUnused[] = _("");

const u8 gPidgeottoPokedexText[] = _(
    "The claws on its feet are well developed.\n"
    "It can carry prey such as an EXEGGCUTE\n"
    "to its nest over 60 miles away.");

const u8 gPidgeottoPokedexTextUnused[] = _("");

const u8 gPidgeotPokedexText[] = _(
    "It spreads its gorgeous wings widely to\n"
    "intimidate enemies. It races through the\n"
    "skies at Mach-2 speed.");

const u8 gPidgeotPokedexTextUnused[] = _("");

const u8 gRattataPokedexText[] = _(
    "Its fangs are long and very sharp.\n"
    "They grow continuously, so it gnaws on\n"
    "hard things to whittle them down.");

const u8 gRattataPokedexTextUnused[] = _("");

const u8 gRaticatePokedexText[] = _(
    "Its rear feet have three toes each.\n"
    "They are webbed, enabling it to swim\n"
    "across rivers.");

const u8 gRaticatePokedexTextUnused[] = _("");

const u8 gSpearowPokedexText[] = _(
    "It busily flits around here and there.\n"
    "Even if it is frail, it can be a tough\n"
    "foe that uses MIRROR MOVE.");

const u8 gSpearowPokedexTextUnused[] = _("");

const u8 gFearowPokedexText[] = _(
    "Its huge and magnificent wings can keep it\n"
    "aloft in the sky. It can remain flying a\n"
    "whole day without landing.");

const u8 gFearowPokedexTextUnused[] = _("");

const u8 gEkansPokedexText[] = _(
    "A very common sight in grassland, etc.\n"
    "It flicks its tongue in and out to sense\n"
    "danger in its surroundings.");

const u8 gEkansPokedexTextUnused[] = _("");

const u8 gArbokPokedexText[] = _(
    "The pattern on its belly appears to be a\n"
    "frightening face. Weak foes will flee just\n"
    "at the sight of the pattern.");

const u8 gArbokPokedexTextUnused[] = _("");

const u8 gPikachuPokedexText[] = _(
    "It has small electric sacs on both its\n"
    "cheeks. If threatened, it looses electric\n"
    "charges from the sacs.");

const u8 gPikachuPokedexTextUnused[] = _("");

const u8 gRaichuPokedexText[] = _(
    "Its electric charges can reach even\n"
    "100,000 volts. Careless contact can cause\n"
    "even an Indian elephant to faint.");

const u8 gRaichuPokedexTextUnused[] = _("");

const u8 gSandshrewPokedexText[] = _(
    "It burrows and lives underground.\n"
    "If threatened, it curls itself up into a\n"
    "ball for protection.");

const u8 gSandshrewPokedexTextUnused[] = _("");

const u8 gSandslashPokedexText[] = _(
    "It is adept at attacking with the spines\n"
    "on its back and its sharp claws while\n"
    "quickly scurrying about.");

const u8 gSandslashPokedexTextUnused[] = _("");

const u8 gNidoranFPokedexText[] = _(
    "Though small, it must be treated with\n"
    "caution because of its powerfully toxic\n"
    "barbs. The female has smaller horns.");

const u8 gNidoranFPokedexTextUnused[] = _("");

const u8 gNidorinaPokedexText[] = _(
    "The female has a gentle temperament.\n"
    "It emits ultrasonic cries that have the\n"
    "power to befuddle foes.");

const u8 gNidorinaPokedexTextUnused[] = _("");

const u8 gNidoqueenPokedexText[] = _(
    "The body is covered by stiff, needle-\n"
    "like scales. If it becomes excited,\n"
    "the needles bristle outwards.");

const u8 gNidoqueenPokedexTextUnused[] = _("");

const u8 gNidoranMPokedexText[] = _(
    "Its large ears are flapped like wings\n"
    "when it is listening to distant sounds.\n"
    "It extends toxic barbs when angered.");

const u8 gNidoranMPokedexTextUnused[] = _("");

const u8 gNidorinoPokedexText[] = _(
    "It is easily angered. By swinging its well-\n"
    "developed horn wildly, it can even punch\n"
    "through diamond.");

const u8 gNidorinoPokedexTextUnused[] = _("");

const u8 gNidokingPokedexText[] = _(
    "It is recognized by its rock-hard hide\n"
    "and its extended horn. Be careful with\n"
    "the horn as it contains venom.");

const u8 gNidokingPokedexTextUnused[] = _("");

const u8 gClefairyPokedexText[] = _(
    "Its adorable appearance makes it popular\n"
    "as a pet. However, it is rare and\n"
    "difficult to find.");

const u8 gClefairyPokedexTextUnused[] = _("");

const u8 gClefablePokedexText[] = _(
    "It has an acute sense of hearing. It can\n"
    "easily hear a pin being dropped nearly\n"
    "1,100 yards away.");

const u8 gClefablePokedexTextUnused[] = _("");

const u8 gVulpixPokedexText[] = _(
    "While young, it has six gorgeous tails.\n"
    "When it grows, several new tails are\n"
    "sprouted.");

const u8 gVulpixPokedexTextUnused[] = _("");

const u8 gNinetalesPokedexText[] = _(
    "It has nine long tails and fur that \n"
    "gleams gold. It is said to live for \n"
    "1,000 years.");

const u8 gNinetalesPokedexTextUnused[] = _("");

const u8 gJigglypuffPokedexText[] = _(
    "It captivates foes with its huge, round\n"
    "eyes, then lulls them to sleep by singing\n"
    "a soothing melody.");

const u8 gJigglypuffPokedexTextUnused[] = _("");

const u8 gWigglytuffPokedexText[] = _(
    "Its fur is extremely fine, dense, and\n"
    "supple. The exquisitely pleasant fur\n"
    "conveys an image of luxury.");

const u8 gWigglytuffPokedexTextUnused[] = _("");

const u8 gZubatPokedexText[] = _(
    "It has no eyes. Instead, it relies on\n"
    "its ultrasonic cries for echo location to\n"
    "flit about in darkness.");

const u8 gZubatPokedexTextUnused[] = _("");

const u8 gGolbatPokedexText[] = _(
    "It clamps down on its prey with needle-\n"
    "sharp fangs and drains over 10 ounces of\n"
    "blood in one gulp.");

const u8 gGolbatPokedexTextUnused[] = _("");

const u8 gOddishPokedexText[] = _(
    "Its scientific name is “Oddium Wanderus.”\n"
    "At night, it is said to walk nearly 1,000\n"
    "feet on its two roots.");

const u8 gOddishPokedexTextUnused[] = _("");

const u8 gGloomPokedexText[] = _(
    "Its pistils exude an incredibly foul odor.\n"
    "The horrid stench can cause fainting at a\n"
    "distance of 1.25 miles.");

const u8 gGloomPokedexTextUnused[] = _("");

const u8 gVileplumePokedexText[] = _(
    "Its petals are the largest in the world.\n"
    "It fiendishly scatters allergy-causing\n"
    "pollen from its petals.");

const u8 gVileplumePokedexTextUnused[] = _("");

const u8 gParasPokedexText[] = _(
    "Growing out of the bug's back are\n"
    "mushrooms called tochukaso. The mushrooms\n"
    "grow with the bug host.");

const u8 gParasPokedexTextUnused[] = _("");

const u8 gParasectPokedexText[] = _(
    "It scatters toxic spores from the\n"
    "mushroom cap. In China, the spores are\n"
    "used as herbal medicine.");

const u8 gParasectPokedexTextUnused[] = _("");

const u8 gVenonatPokedexText[] = _(
    "Its eyes act as radar, enabling it to be\n"
    "active in darkness. The eyes can also\n"
    "shoot powerful beams.");

const u8 gVenonatPokedexTextUnused[] = _("");

const u8 gVenomothPokedexText[] = _(
    "The wings are covered with dustlike\n"
    "scales. Every time it flaps its wings, it\n"
    "looses highly toxic dust.");

const u8 gVenomothPokedexTextUnused[] = _("");

const u8 gDiglettPokedexText[] = _(
    "It burrows through the ground at a\n"
    "shallow depth. It leaves raised earth in\n"
    "its wake, making it easy to spot.");

const u8 gDiglettPokedexTextUnused[] = _("");

const u8 gDugtrioPokedexText[] = _(
    "In battle, it digs through the ground and\n"
    "strikes the unsuspecting foe from an\n"
    "unexpected direction.");

const u8 gDugtrioPokedexTextUnused[] = _("");

const u8 gMeowthPokedexText[] = _(
    "All it does is sleep during the daytime.\n"
    "At night, it patrols its territory with its\n"
    "eyes aglow.");

const u8 gMeowthPokedexTextUnused[] = _("");

const u8 gPersianPokedexText[] = _(
    "Has a vicious temperament. Beware if it\n"
    "raises its tail straight up. It is a signal\n"
    "that it is about to pounce and bite.");

const u8 gPersianPokedexTextUnused[] = _("");

const u8 gPsyduckPokedexText[] = _(
    "It is constantly wracked by a headache.\n"
    "When the headache turns intense, it begins\n"
    "using mysterious powers.");

const u8 gPsyduckPokedexTextUnused[] = _("");

const u8 gGolduckPokedexText[] = _(
    "The forelegs are webbed, helping to make\n"
    "it an adept swimmer. It can be seen\n"
    "swimming elegantly in lakes, etc.");

const u8 gGolduckPokedexTextUnused[] = _("");

const u8 gMankeyPokedexText[] = _(
    "Light and agile on its feet, and ferocious\n"
    "in temperament. When angered, it flies into\n"
    "an uncontrollable frenzy.");

const u8 gMankeyPokedexTextUnused[] = _("");

const u8 gPrimeapePokedexText[] = _(
    "It is always outrageously furious. If it\n"
    "gives chase, it will tenaciously track the\n"
    "target no matter how far.");

const u8 gPrimeapePokedexTextUnused[] = _("");

const u8 gGrowlithePokedexText[] = _(
    "Very friendly and faithful to people.\n"
    "It will try to repel enemies by barking\n"
    "and biting.");

const u8 gGrowlithePokedexTextUnused[] = _("");

const u8 gArcaninePokedexText[] = _(
    "A POKéMON that is described in Chinese\n"
    "legends. It is said to race at an\n"
    "unbelievable speed.");

const u8 gArcaninePokedexTextUnused[] = _("");

const u8 gPoliwagPokedexText[] = _(
    "Its slick black skin is thin and damp.\n"
    "A part of its internal organs can be seen\n"
    "through the skin as a spiral pattern.");

const u8 gPoliwagPokedexTextUnused[] = _("");

const u8 gPoliwhirlPokedexText[] = _(
    "Its two legs are well developed.\n"
    "Even though it can live on the ground,\n"
    "it prefers living in water.");

const u8 gPoliwhirlPokedexTextUnused[] = _("");

const u8 gPoliwrathPokedexText[] = _(
    "An adept swimmer, it knows the front\n"
    "crawl, butterfly, and more. It is faster\n"
    "than the best human swimmers.");

const u8 gPoliwrathPokedexTextUnused[] = _("");

const u8 gAbraPokedexText[] = _(
    "It sleeps for 18 hours a day. It uses a\n"
    "variety of extrasensory powers even\n"
    "while asleep.");

const u8 gAbraPokedexTextUnused[] = _("");

const u8 gKadabraPokedexText[] = _(
    "It happened one morning - a boy with\n"
    "extrasensory powers awoke in bed\n"
    "transformed into KADABRA.");

const u8 gKadabraPokedexTextUnused[] = _("");

const u8 gAlakazamPokedexText[] = _(
    "It does not like physical attacks very \n"
    "much. Instead, it freely uses extra-\n"
    "sensory powers to defeat foes.");

const u8 gAlakazamPokedexTextUnused[] = _("");

const u8 gMachopPokedexText[] = _(
    "Its whole body is composed of muscles.\n"
    "Even though it's the size of a human\n"
    "child, it can hurl 100 grown-ups.");

const u8 gMachopPokedexTextUnused[] = _("");

const u8 gMachokePokedexText[] = _(
    "Its formidable body never gets tired.\n"
    "It helps people by doing work such as\n"
    "the moving of heavy goods.");

const u8 gMachokePokedexTextUnused[] = _("");

const u8 gMachampPokedexText[] = _(
    "Its four ruggedly developed arms can\n"
    "launch a flurry of 1,000 punches in just\n"
    "two seconds.");

const u8 gMachampPokedexTextUnused[] = _("");

const u8 gBellsproutPokedexText[] = _(
    "Its bud looks like a human face. Because\n"
    "of the bud, it is rumored to be a type of\n"
    "legendary mandrake plant.");

const u8 gBellsproutPokedexTextUnused[] = _("");

const u8 gWeepinbellPokedexText[] = _(
    "The leafy parts act as cutters for\n"
    "slashing foes. It spits a fluid that\n"
    "dissolves everything.");

const u8 gWeepinbellPokedexTextUnused[] = _("");

const u8 gVictreebelPokedexText[] = _(
    "Lures prey into its mouth with a honeylike\n"
    "aroma. The helpless prey is melted with\n"
    "a dissolving fluid.");

const u8 gVictreebelPokedexTextUnused[] = _("");

const u8 gTentacoolPokedexText[] = _(
    "Its eyes are as transparent as crystals.\n"
    "From them, it shoots mysterious\n"
    "beams of light.");

const u8 gTentacoolPokedexTextUnused[] = _("");

const u8 gTentacruelPokedexText[] = _(
    "It has 80 tentacles that move about\n"
    "freely. They can sting, causing poisoning\n"
    "and sharp, stabbing pain.");

const u8 gTentacruelPokedexTextUnused[] = _("");

const u8 gGeodudePokedexText[] = _(
    "Its round form makes it easy to pick up.\n"
    "Some people have used them to hurl\n"
    "at each other in a snowball fight.");

const u8 gGeodudePokedexTextUnused[] = _("");

const u8 gGravelerPokedexText[] = _(
    "Be careful while hiking on mountain trails.\n"
    "GRAVELER may come rolling down the path\n"
    "without slowing.");

const u8 gGravelerPokedexTextUnused[] = _("");

const u8 gGolemPokedexText[] = _(
    "It is enclosed in a hard shell that is as\n"
    "rugged as slabs of rock. It sheds skin\n"
    "once a year to grow larger.");

const u8 gGolemPokedexTextUnused[] = _("");

const u8 gPonytaPokedexText[] = _(
    "Its body is light, and its legs are\n"
    "incredibly powerful. It can clear\n"
    "Ayers Rock in one leap.");

const u8 gPonytaPokedexTextUnused[] = _("");

const u8 gRapidashPokedexText[] = _(
    "It can gallop at a top speed of 150\n"
    "miles per hour. It can race as fast as a\n"
    "bullet train while ablaze.");

const u8 gRapidashPokedexTextUnused[] = _("");

const u8 gSlowpokePokedexText[] = _(
    "It is always vacantly lost in thought, but\n"
    "no one knows what it is thinking about.\n"
    "It is good at fishing with its tail.");

const u8 gSlowpokePokedexTextUnused[] = _("");

const u8 gSlowbroPokedexText[] = _(
    "When a SLOWPOKE went hunting in the sea,\n"
    "its tail was bitten by a SHELLDER. That\n"
    "made it evolve into SLOWBRO.");

const u8 gSlowbroPokedexTextUnused[] = _("");

const u8 gMagnemitePokedexText[] = _(
    "It moves while constantly hovering.\n"
    "It discharges THUNDER WAVE and so on\n"
    "from the units at its sides.");

const u8 gMagnemitePokedexTextUnused[] = _("");

const u8 gMagnetonPokedexText[] = _(
    "A linked cluster formed of several\n"
    "MAGNEMITE. It discharges powerful\n"
    "magnetic waves at high voltage.");

const u8 gMagnetonPokedexTextUnused[] = _("");

const u8 gFarfetchdPokedexText[] = _(
    "It always walks about with a plant stalk\n"
    "clamped in its beak. The stalk is used for\n"
    "building its nest.");

const u8 gFarfetchdPokedexTextUnused[] = _("");

const u8 gDoduoPokedexText[] = _(
    "A two-headed POKéMON that was discovered\n"
    "as a sudden mutation. It runs at a pace\n"
    "of over 60 miles per hour.");

const u8 gDoduoPokedexTextUnused[] = _("");

const u8 gDodrioPokedexText[] = _(
    "An odd species that is rarely found.\n"
    "The three heads respectively represent\n"
    "joy, sadness, and anger.");

const u8 gDodrioPokedexTextUnused[] = _("");

const u8 gSeelPokedexText[] = _(
    "Covered with light blue fur, its hide is\n"
    "thick and tough. It is active in bitter\n"
    "cold of minus 40 degrees Fahrenheit.");

const u8 gSeelPokedexTextUnused[] = _("");

const u8 gDewgongPokedexText[] = _(
    "Its body is covered with a pure white\n"
    "fur. The colder the weather, the more\n"
    "active it becomes.");

const u8 gDewgongPokedexTextUnused[] = _("");

const u8 gGrimerPokedexText[] = _(
    "Sludge exposed to X rays from the moon\n"
    "transformed into GRIMER. It loves feeding\n"
    "on filthy things.");

const u8 gGrimerPokedexTextUnused[] = _("");

const u8 gMukPokedexText[] = _(
    "It is usually undetectable because it\n"
    "blends in with the ground. Touching it can\n"
    "cause terrible poisoning.");

const u8 gMukPokedexTextUnused[] = _("");

const u8 gShellderPokedexText[] = _(
    "It is encased in a shell that is harder\n"
    "than diamond. Inside, however, it is\n"
    "surprisingly tender.");

const u8 gShellderPokedexTextUnused[] = _("");

const u8 gCloysterPokedexText[] = _(
    "Its shell is extremely hard. It cannot be\n"
    "shattered, even with a bomb. The shell\n"
    "opens only when it is attacking.");

const u8 gCloysterPokedexTextUnused[] = _("");

const u8 gGastlyPokedexText[] = _(
    "A being that exists as a thin gas. It can\n"
    "topple an Indian elephant by enveloping\n"
    "the prey in two seconds.");

const u8 gGastlyPokedexTextUnused[] = _("");

const u8 gHaunterPokedexText[] = _(
    "If you get the feeling of being watched\n"
    "in darkness when nobody is around,\n"
    "HAUNTER is there.");

const u8 gHaunterPokedexTextUnused[] = _("");

const u8 gGengarPokedexText[] = _(
    "It is said to emerge from darkness to\n"
    "steal the lives of those who become lost\n"
    "in mountains.");

const u8 gGengarPokedexTextUnused[] = _("");

const u8 gOnixPokedexText[] = _(
    "It usually lives underground. It searches\n"
    "for food while boring its way through the\n"
    "ground at 50 miles per hour.");

const u8 gOnixPokedexTextUnused[] = _("");

const u8 gDrowzeePokedexText[] = _(
    "A descendent of the legendary animal\n"
    "baku, which is said to eat dreams. It is\n"
    "skilled at hypnotism.");

const u8 gDrowzeePokedexTextUnused[] = _("");

const u8 gHypnoPokedexText[] = _(
    "It carries a pendulum-like device. There\n"
    "once was an incident in which it took \n"
    "away a child it hypnotized.");

const u8 gHypnoPokedexTextUnused[] = _("");

const u8 gKrabbyPokedexText[] = _(
    "It can be found near the sea. The large\n"
    "pincers grow back if they are torn out of\n"
    "their sockets.");

const u8 gKrabbyPokedexTextUnused[] = _("");

const u8 gKinglerPokedexText[] = _(
    "Its large and hard pincer has 10,000-\n"
    "horsepower strength. However, being so\n"
    "big, it is unwieldy to move.");

const u8 gKinglerPokedexTextUnused[] = _("");

const u8 gVoltorbPokedexText[] = _(
    "A life-form whose identity is unknown.\n"
    "It is said to SCREECH or suddenly\n"
    "SELFDESTRUCT.");

const u8 gVoltorbPokedexTextUnused[] = _("");

const u8 gElectrodePokedexText[] = _(
    "It explodes in response to even minor\n"
    "stimuli. It is feared, with the nickname\n"
    "of “The Bomb Ball.”");

const u8 gElectrodePokedexTextUnused[] = _("");

const u8 gExeggcutePokedexText[] = _(
    "Even though it appears to be eggs of\n"
    "some sort, it was discovered to be a life-\n"
    "form more like plant seeds.");

const u8 gExeggcutePokedexTextUnused[] = _("");

const u8 gExeggutorPokedexText[] = _(
    "It is called “The Walking Tropical\n"
    "Rainforest.” Each of the nuts has\n"
    "a face and a will of its own.");

const u8 gExeggutorPokedexTextUnused[] = _("");

const u8 gCubonePokedexText[] = _(
    "It wears the skull of its dead mother on\n"
    "its head. When it becomes lonesome, it is\n"
    "said to cry loudly.");

const u8 gCubonePokedexTextUnused[] = _("");

const u8 gMarowakPokedexText[] = _(
    "It is small and was originally very weak.\n"
    "Its temperament turned ferocious when it\n"
    "began using bones.");

const u8 gMarowakPokedexTextUnused[] = _("");

const u8 gHitmonleePokedexText[] = _(
    "The legs freely contract and stretch.\n"
    "The stretchy legs allow it to hit a\n"
    "distant foe with a rising kick.");

const u8 gHitmonleePokedexTextUnused[] = _("");

const u8 gHitmonchanPokedexText[] = _(
    "The spirit of a pro boxer has infused this\n"
    "POKéMON. It throws punches that are\n"
    "faster than a bullet train.");

const u8 gHitmonchanPokedexTextUnused[] = _("");

const u8 gLickitungPokedexText[] = _(
    "Its tongue is twice the length of its\n"
    "body. It can be moved like an arm for\n"
    "grabbing food and attacking.");

const u8 gLickitungPokedexTextUnused[] = _("");

const u8 gKoffingPokedexText[] = _(
    "Its thin, balloon-like body is inflated by\n"
    "horribly toxic gases. It reeks when it is\n"
    "nearby.");

const u8 gKoffingPokedexTextUnused[] = _("");

const u8 gWeezingPokedexText[] = _(
    "Very rarely, a sudden mutation can result\n"
    "in two small KOFFING twins becoming\n"
    "conjoined as a WEEZING.");

const u8 gWeezingPokedexTextUnused[] = _("");

const u8 gRhyhornPokedexText[] = _(
    "Strong, but not too bright, this POKéMON\n"
    "can shatter even a skyscraper with its\n"
    "charging TACKLES.");

const u8 gRhyhornPokedexTextUnused[] = _("");

const u8 gRhydonPokedexText[] = _(
    "It begins walking on its hind legs after\n"
    "evolution. It can punch holes through\n"
    "boulders with its horn.");

const u8 gRhydonPokedexTextUnused[] = _("");

const u8 gChanseyPokedexText[] = _(
    "It lays several eggs a day. The eggs are\n"
    "apparently rich in nutrients and extremely\n"
    "delicious.");

const u8 gChanseyPokedexTextUnused[] = _("");

const u8 gTangelaPokedexText[] = _(
    "Blue plant vines cloak the POKéMON's\n"
    "identity in a tangled mass. It entangles\n"
    "anything that gets close.");

const u8 gTangelaPokedexTextUnused[] = _("");

const u8 gKangaskhanPokedexText[] = _(
    "The female raises its offspring in a pouch\n"
    "on its belly. It is skilled at attacking\n"
    "using COMET PUNCH.");

const u8 gKangaskhanPokedexTextUnused[] = _("");

const u8 gHorseaPokedexText[] = _(
    "It maintains balance using its tail, which\n"
    "is wound up like a coil. It may spray ink\n"
    "from its mouth.");

const u8 gHorseaPokedexTextUnused[] = _("");

const u8 gSeadraPokedexText[] = _(
    "Its body bristles with sharp spikes.\n"
    "Carelessly trying to touch it could cause\n"
    "fainting from the spikes.");

const u8 gSeadraPokedexTextUnused[] = _("");

const u8 gGoldeenPokedexText[] = _(
    "Its dorsal and pectoral fins are strongly\n"
    "developed like muscles. It can swim at a\n"
    "speed of five knots.");

const u8 gGoldeenPokedexTextUnused[] = _("");

const u8 gSeakingPokedexText[] = _(
    "The horn on its head is sharp like a\n"
    "drill. It bores a hole in a boulder to\n"
    "make its nest.");

const u8 gSeakingPokedexTextUnused[] = _("");

const u8 gStaryuPokedexText[] = _(
    "It appears in large numbers by seashores.\n"
    "At night, its central core flashes with a\n"
    "red light.");

const u8 gStaryuPokedexTextUnused[] = _("");

const u8 gStarmiePokedexText[] = _(
    "This POKéMON has a geometric body.\n"
    "Because of its body, the locals suspect\n"
    "that it is an alien creature.");

const u8 gStarmiePokedexTextUnused[] = _("");

const u8 gMrmimePokedexText[] = _(
    "It is adept at conning people. It is said\n"
    "to be able to create walls out of thin\n"
    "air by miming.");

const u8 gMrmimePokedexTextUnused[] = _("");

const u8 gScytherPokedexText[] = _(
    "It tears and shreds prey with its wickedly\n"
    "sharp scythes. It very rarely spreads its\n"
    "wings to fly.");

const u8 gScytherPokedexTextUnused[] = _("");

const u8 gJynxPokedexText[] = _(
    "It speaks using a language that sounds\n"
    "human. Research is under way to determine\n"
    "what is being said.");

const u8 gJynxPokedexTextUnused[] = _("");

const u8 gElectabuzzPokedexText[] = _(
    "It loves to feed on strong electricity.\n"
    "It occasionally appears around large\n"
    "power plants and so on.");

const u8 gElectabuzzPokedexTextUnused[] = _("");

const u8 gMagmarPokedexText[] = _(
    "Found near the mouth of a volcano.\n"
    "This fire-breather's body temperature is\n"
    "nearly 2,200 degrees Fahrenheit.");

const u8 gMagmarPokedexTextUnused[] = _("");

const u8 gPinsirPokedexText[] = _(
    "Its two long pincer horns are powerful.\n"
    "Once they grip an enemy, they won't\n"
    "release until the foe is torn.");

const u8 gPinsirPokedexTextUnused[] = _("");

const u8 gTaurosPokedexText[] = _(
    "When it is about to TACKLE, it whips\n"
    "its body repeatedly with its three\n"
    "long tails.");

const u8 gTaurosPokedexTextUnused[] = _("");

const u8 gMagikarpPokedexText[] = _(
    "It is virtually worthless in terms of both\n"
    "power and speed. It is the most weak and\n"
    "pathetic POKéMON in the world.");

const u8 gMagikarpPokedexTextUnused[] = _("");

const u8 gGyaradosPokedexText[] = _(
    "It has an extremely aggressive nature.\n"
    "The HYPER BEAM it shoots from its mouth\n"
    "totally incinerates all targets.");

const u8 gGyaradosPokedexTextUnused[] = _("");

const u8 gLaprasPokedexText[] = _(
    "Its high intelligence enables it to\n"
    "understand human speech. It likes to ferry\n"
    "people on its back.");

const u8 gLaprasPokedexTextUnused[] = _("");

const u8 gDittoPokedexText[] = _(
    "It can freely recombine its own cellular\n"
    "structure to transform into other life-\n"
    "forms.");

const u8 gDittoPokedexTextUnused[] = _("");

const u8 gEeveePokedexText[] = _(
    "An extremely rare POKéMON that may\n"
    "evolve in a number of different ways\n"
    "depending on stimuli.");

const u8 gEeveePokedexTextUnused[] = _("");

const u8 gVaporeonPokedexText[] = _(
    "Its body's cellular structure is similar to\n"
    "the molecular composition of water.\n"
    "It can melt invisibly in water.");

const u8 gVaporeonPokedexTextUnused[] = _("");

const u8 gJolteonPokedexText[] = _(
    "If it is angered or startled, the fur all\n"
    "over its body bristles like sharp needles\n"
    "that pierce foes.");

const u8 gJolteonPokedexTextUnused[] = _("");

const u8 gFlareonPokedexText[] = _(
    "It has a flame bag inside its body. After\n"
    "inhaling deeply, it blows out flames of\n"
    "nearly 3,100 degrees Fahrenheit.");

const u8 gFlareonPokedexTextUnused[] = _("");

const u8 gPorygonPokedexText[] = _(
    "Using the most advanced technologies,\n"
    "scientists finally succeeded in making the\n"
    "first artificial POKéMON.");

const u8 gPorygonPokedexTextUnused[] = _("");

const u8 gOmanytePokedexText[] = _(
    "A prehistoric POKéMON that lived in the\n"
    "primordial sea, it swims by twisting its\n"
    "10 tentacles about.");

const u8 gOmanytePokedexTextUnused[] = _("");

const u8 gOmastarPokedexText[] = _(
    "Its tentacles are highly developed as if\n"
    "they are hands and feet. As soon as it\n"
    "ensnares prey, it bites.");

const u8 gOmastarPokedexTextUnused[] = _("");

const u8 gKabutoPokedexText[] = _(
    "This POKéMON was regenerated from the\n"
    "fossil of an ancient creature. It protects\n"
    "itself with a hard shell.");

const u8 gKabutoPokedexTextUnused[] = _("");

const u8 gKabutopsPokedexText[] = _(
    "It swims freely through water. It catches\n"
    "prey with its scythe-like arms and drains\n"
    "the victim's fluids.");

const u8 gKabutopsPokedexTextUnused[] = _("");

const u8 gAerodactylPokedexText[] = _(
    "It was regenerated from a dinosaur's\n"
    "genetic matter that was found in amber.\n"
    "It flies with high-pitched cries.");

const u8 gAerodactylPokedexTextUnused[] = _("");

const u8 gSnorlaxPokedexText[] = _(
    "It is not satisfied unless it eats over 880\n"
    "pounds of food every day. When it is done\n"
    "eating, it goes promptly to sleep.");

const u8 gSnorlaxPokedexTextUnused[] = _("");

const u8 gArticunoPokedexText[] = _(
    "One of the legendary bird POKéMON.\n"
    "With its long tail trailing behind, its\n"
    "flying form is magnificent.");

const u8 gArticunoPokedexTextUnused[] = _("");

const u8 gZapdosPokedexText[] = _(
    "One of the legendary bird POKéMON.\n"
    "While it is flying, it makes crackling and\n"
    "snapping sounds.");

const u8 gZapdosPokedexTextUnused[] = _("");

const u8 gMoltresPokedexText[] = _(
    "One of the legendary bird POKéMON.\n"
    "Those seeing it are overwhelmed by its\n"
    "orange wings that seem to be on fire.");

const u8 gMoltresPokedexTextUnused[] = _("");

const u8 gDratiniPokedexText[] = _(
    "Even the young can exceed 6.5 feet in\n"
    "length. It grows larger by repeatedly\n"
    "shedding skin.");

const u8 gDratiniPokedexTextUnused[] = _("");

const u8 gDragonairPokedexText[] = _(
    "It is said to live in seas and lakes.\n"
    "Even though it has no wings, it has been\n"
    "seen flying occasionally.");

const u8 gDragonairPokedexTextUnused[] = _("");

const u8 gDragonitePokedexText[] = _(
    "It can fly in spite of its big and bulky\n"
    "physique. It circles the globe in just\n"
    "16 hours.");

const u8 gDragonitePokedexTextUnused[] = _("");

const u8 gMewtwoPokedexText[] = _(
    "A POKéMON whose genetic code was\n"
    "repeatedly recombined for research.\n"
    "It turned vicious as a result.");

const u8 gMewtwoPokedexTextUnused[] = _("");

const u8 gMewPokedexText[] = _(
    "A POKéMON of South America that was\n"
    "thought to have been extinct. It is very\n"
    "intelligent and learns any move.");

const u8 gMewPokedexTextUnused[] = _("");

const u8 gChikoritaPokedexText[] = _(
#if REVISION == 0
    "Its pleasantly aromatic leaves have the\n"
    #else
    "Its pleasantly aromatic leaf has the\n"
    #endif
    "ability to check the humidity and\n"
    "temperature."
);

const u8 gChikoritaPokedexTextUnused[] = _("");

const u8 gBayleefPokedexText[] = _(
    "A spicy aroma emanates from around its\n"
    "neck. The aroma acts as a stimulant to\n"
    "restore health.");

const u8 gBayleefPokedexTextUnused[] = _("");

const u8 gMeganiumPokedexText[] = _(
    "MEGANIUM's breath has the power to revive\n"
    "dead grass and plants. It can make them\n"
    "healthy again.");

const u8 gMeganiumPokedexTextUnused[] = _("");

const u8 gCyndaquilPokedexText[] = _(
    "It usually stays hunched over. If it is\n"
    "angry or surprised, it shoots flames out\n"
    "of its back.");

const u8 gCyndaquilPokedexTextUnused[] = _("");

const u8 gQuilavaPokedexText[] = _(
    "This POKéMON is fully covered by\n"
    "nonflammable fur. It can withstand any\n"
    "kind of fire attack.");

const u8 gQuilavaPokedexTextUnused[] = _("");

const u8 gTyphlosionPokedexText[] = _(
    "It has a secret, devastating move. It\n"
    "rubs its blazing fur together to cause\n"
    "huge explosions.");

const u8 gTyphlosionPokedexTextUnused[] = _("");

const u8 gTotodilePokedexText[] = _(
    "It is small but rough and tough. It won't\n"
    "hesitate to take a bite out of anything\n"
    "that moves.");

const u8 gTotodilePokedexTextUnused[] = _("");

const u8 gCroconawPokedexText[] = _(
    "It opens its huge jaws wide when\n"
    "attacking. If it loses any fangs while\n"
    "biting, they grow back in.");

const u8 gCroconawPokedexTextUnused[] = _("");

const u8 gFeraligatrPokedexText[] = _(
    "It is hard for it to support its own\n"
    "weight out of water, so it gets down on\n"
    "all fours. But it moves fast.");

const u8 gFeraligatrPokedexTextUnused[] = _("");

const u8 gSentretPokedexText[] = _(
    "It stands on its tail so it can see a long\n"
    "way. If it spots an enemy, it cries loudly\n"
    "to warn its kind.");

const u8 gSentretPokedexTextUnused[] = _("");

const u8 gFurretPokedexText[] = _(
    "There is no telling where its tail begins.\n"
    "Despite its short legs, it is quick at\n"
    "hunting RATTATA.");

const u8 gFurretPokedexTextUnused[] = _("");

const u8 gHoothootPokedexText[] = _(
    "It has a perfect sense of time. Whatever\n"
    "happens, it keeps rhythm by precisely\n"
    "tilting its head in time.");

const u8 gHoothootPokedexTextUnused[] = _("");

const u8 gNoctowlPokedexText[] = _(
    "When it needs to think, it rotates its head\n"
    "180 degrees to sharpen its intellectual\n"
    "power.");

const u8 gNoctowlPokedexTextUnused[] = _("");

const u8 gLedybaPokedexText[] = _(
    "When the weather turns cold, numerous\n"
    "LEDYBA gather from everywhere to cluster\n"
    "and keep each other warm.");

const u8 gLedybaPokedexTextUnused[] = _("");

const u8 gLedianPokedexText[] = _(
    "The star patterns on its back grow larger\n"
    "or smaller depending on the number of\n"
    "stars in the night sky.");

const u8 gLedianPokedexTextUnused[] = _("");

const u8 gSpinarakPokedexText[] = _(
    "It spins a web using fine--but durable--\n"
    "thread. It then waits patiently for prey\n"
    "to be trapped.");

const u8 gSpinarakPokedexTextUnused[] = _("");

const u8 gAriadosPokedexText[] = _(
    "A single strand of a special string is\n"
    "endlessly spun out of its rear. The string\n"
    "leads back to its nest.");

const u8 gAriadosPokedexTextUnused[] = _("");

const u8 gCrobatPokedexText[] = _(
    "The development of wings on its legs\n"
    "enables it to fly fast but also makes it\n"
    "tough to stop and rest.");

const u8 gCrobatPokedexTextUnused[] = _("");

const u8 gChinchouPokedexText[] = _(
    "On the dark ocean floor, its only means\n"
    "of communication is its constantly\n"
    "flashing lights.");

const u8 gChinchouPokedexTextUnused[] = _("");

const u8 gLanturnPokedexText[] = _(
    "It blinds prey with an intense burst of\n"
    "light, then swallows the immobilized prey\n"
    "in a single gulp.");

const u8 gLanturnPokedexTextUnused[] = _("");

const u8 gPichuPokedexText[] = _(
    "Despite its small size, it can zap even\n"
    "adult humans. However, if it does so, it\n"
    "also surprises itself.");

const u8 gPichuPokedexTextUnused[] = _("");

const u8 gCleffaPokedexText[] = _(
    "When numerous meteors illuminate the\n"
    "night sky, sightings of CLEFFA strangely\n"
    "increase.");

const u8 gCleffaPokedexTextUnused[] = _("");

const u8 gIgglybuffPokedexText[] = _(
    "Its extremely flexible and elastic body\n"
    "makes it bounce continuously--anytime,\n"
    "anywhere.");

const u8 gIgglybuffPokedexTextUnused[] = _("");

const u8 gTogepiPokedexText[] = _(
    "A proverb claims that happiness will come\n"
    "to anyone who can make a sleeping TOGEPI\n"
    "stand up.");

const u8 gTogepiPokedexTextUnused[] = _("");

const u8 gTogeticPokedexText[] = _(
    "It grows dispirited if it is not with kind\n"
    "people. It can float in midair without\n"
    "moving its wings.");

const u8 gTogeticPokedexTextUnused[] = _("");

const u8 gNatuPokedexText[] = _(
    "It usually forages for food on the ground\n"
    "but may, on rare occasions, hop onto\n"
    "branches to peck at shoots.");

const u8 gNatuPokedexTextUnused[] = _("");

const u8 gXatuPokedexText[] = _(
    "In South America, it is said that its right\n"
    "eye sees the future and its left eye\n"
    "views the past.");

const u8 gXatuPokedexTextUnused[] = _("");

const u8 gMareepPokedexText[] = _(
    "Its fleece grows continually. In the\n"
    "summer, the fleece is fully shed, but it\n"
    "grows back in a week.");

const u8 gMareepPokedexTextUnused[] = _("");

const u8 gFlaaffyPokedexText[] = _(
    "Its fluffy fleece easily stores\n"
    "electricity. Its rubbery hide keeps it\n"
    "from being electrocuted.");

const u8 gFlaaffyPokedexTextUnused[] = _("");

const u8 gAmpharosPokedexText[] = _(
    "The bright light on its tail can be seen\n"
    "far away. It has been treasured since\n"
    "ancient times as a beacon.");

const u8 gAmpharosPokedexTextUnused[] = _("");

const u8 gBellossomPokedexText[] = _(
    "Plentiful in the tropics. When it dances,\n"
    "its petals rub together and make a\n"
    "pleasant ringing sound.");

const u8 gBellossomPokedexTextUnused[] = _("");

const u8 gMarillPokedexText[] = _(
    "The end of its tail serves as a buoy that\n"
    "keeps it from drowning, even in a vicious\n"
    "current.");

const u8 gMarillPokedexTextUnused[] = _("");

const u8 gAzumarillPokedexText[] = _(
    "When it plays in water, it rolls up its\n"
    "elongated ears to prevent their insides\n"
    "from getting wet.");

const u8 gAzumarillPokedexTextUnused[] = _("");

const u8 gSudowoodoPokedexText[] = _(
    "It disguises itself as a tree to avoid\n"
    "attack. It hates water, so it will\n"
    "disappear if it starts raining.");

const u8 gSudowoodoPokedexTextUnused[] = _("");

const u8 gPolitoedPokedexText[] = _(
    "Whenever three or more of these get\n"
    "together, they sing in a loud voice that\n"
    "sounds like bellowing.");

const u8 gPolitoedPokedexTextUnused[] = _("");

const u8 gHoppipPokedexText[] = _(
    "Its body is so light, it must grip the\n"
    "ground firmly with its feet to keep from\n"
    "being blown away.");

const u8 gHoppipPokedexTextUnused[] = _("");

const u8 gSkiploomPokedexText[] = _(
    "It spreads its petals to absorb sunlight.\n"
    "It also floats in the air to get closer to\n"
    "the sun.");

const u8 gSkiploomPokedexTextUnused[] = _("");

const u8 gJumpluffPokedexText[] = _(
    "It drifts on seasonal winds and spreads\n"
    "its cotton-like spores all over the world \n"
    "to make more offspring.");

const u8 gJumpluffPokedexTextUnused[] = _("");

const u8 gAipomPokedexText[] = _(
    "It lives atop tall trees. When leaping\n"
    "from branch to branch, it deftly uses its\n"
    "tail for balance.");

const u8 gAipomPokedexTextUnused[] = _("");

const u8 gSunkernPokedexText[] = _(
    "It lives by drinking only dewdrops from\n"
    "under the leaves of plants. It is said\n"
    "that it eats nothing else.");

const u8 gSunkernPokedexTextUnused[] = _("");

const u8 gSunfloraPokedexText[] = _(
    "In the daytime, it rushes about in a\n"
    "hectic manner, but it comes to a complete\n"
    "stop when the sun sets.");

const u8 gSunfloraPokedexTextUnused[] = _("");

const u8 gYanmaPokedexText[] = _(
    "Its large eyes can scan 360 degrees.\n"
    "It looks in all directions to seek out\n"
    "insects as its prey.");

const u8 gYanmaPokedexTextUnused[] = _("");

const u8 gWooperPokedexText[] = _(
    "When it walks around on the ground,\n"
    "it coats its body with a slimy, poisonous\n"
    "film.");

const u8 gWooperPokedexTextUnused[] = _("");

const u8 gQuagsirePokedexText[] = _(
    "Due to its relaxed and carefree attitude,\n"
    "it often bumps its head on boulders and\n"
    "boat hulls as it swims.");

const u8 gQuagsirePokedexTextUnused[] = _("");

const u8 gEspeonPokedexText[] = _(
    "By reading air currents, it can predict\n"
    "things such as the weather or its foe's\n"
    "next move.");

const u8 gEspeonPokedexTextUnused[] = _("");

const u8 gUmbreonPokedexText[] = _(
    "When darkness falls, the rings on its body\n"
    "begin to glow, striking fear in the hearts\n"
    "of anyone nearby.");

const u8 gUmbreonPokedexTextUnused[] = _("");

const u8 gMurkrowPokedexText[] = _(
    "It is said that when chased, it lures its\n"
    "attacker onto dark mountain trails where\n"
    "the foe will get lost.");

const u8 gMurkrowPokedexTextUnused[] = _("");

const u8 gSlowkingPokedexText[] = _(
    "When its head was bitten, toxins entered\n"
    "SLOWPOKE's head and unlocked an\n"
    "extraordinary power.");

const u8 gSlowkingPokedexTextUnused[] = _("");

const u8 gMisdreavusPokedexText[] = _(
    "It loves to bite and yank people's hair\n"
    "from behind without warning, just to see\n"
    "their shocked reactions.");

const u8 gMisdreavusPokedexTextUnused[] = _("");

const u8 gUnownPokedexText[] = _(
    "Its flat, thin body is always stuck on\n"
    "walls. Its shape appears to have some\n"
    "meaning.");

const u8 gUnownPokedexTextUnused[] = _("");

const u8 gWobbuffetPokedexText[] = _(
    "To keep its pitch-black tail hidden, it\n"
    "lives quietly in the darkness. It is never\n"
    "first to attack.");

const u8 gWobbuffetPokedexTextUnused[] = _("");

const u8 gGirafarigPokedexText[] = _(
    "Its tail, which also contains a small\n"
    "brain, may bite on its own if it notices an\n"
    "alluring smell.");

const u8 gGirafarigPokedexTextUnused[] = _("");

const u8 gPinecoPokedexText[] = _(
    "It hangs and waits for flying-insect prey\n"
    "to come near. It does not move about\n"
    "much on its own.");

const u8 gPinecoPokedexTextUnused[] = _("");

const u8 gForretressPokedexText[] = _(
    "It remains immovably rooted to its tree.\n"
    "It scatters pieces of its hard shell to\n"
    "drive its enemies away.");

const u8 gForretressPokedexTextUnused[] = _("");

const u8 gDunsparcePokedexText[] = _(
    "If spotted, it escapes by burrowing with\n"
    "its tail. It can hover just slightly using\n"
    "its wings.");

const u8 gDunsparcePokedexTextUnused[] = _("");

const u8 gGligarPokedexText[] = _(
    "It usually clings to cliffs. When it spots\n"
    "its prey, it spreads its wings and glides\n"
    "down to attack.");

const u8 gGligarPokedexTextUnused[] = _("");

const u8 gSteelixPokedexText[] = _(
    "It is said that if an ONIX lives for over\n"
    "100 years, its composition changes to\n"
    "become diamond-like.");

const u8 gSteelixPokedexTextUnused[] = _("");

const u8 gSnubbullPokedexText[] = _(
    "It has an active, playful nature. Many\n"
    "women like to frolic with it because of\n"
    "its affectionate ways.");

const u8 gSnubbullPokedexTextUnused[] = _("");

const u8 gGranbullPokedexText[] = _(
    "Because its fangs are too heavy, it\n"
    "always keeps its head tilted down.\n"
    "However, its BITE is powerful.");

const u8 gGranbullPokedexTextUnused[] = _("");

const u8 gQwilfishPokedexText[] = _(
    "The small spikes covering its body\n"
    "developed from scales. They inject a\n"
    "toxin that causes fainting.");

const u8 gQwilfishPokedexTextUnused[] = _("");

const u8 gScizorPokedexText[] = _(
    "Its wings are not used for flying.\n"
    "They are flapped at high speed to adjust\n"
    "its body temperature.");

const u8 gScizorPokedexTextUnused[] = _("");

const u8 gShucklePokedexText[] = _(
    "It stores BERRIES inside its shell.\n"
    "To avoid attacks, it hides beneath rocks\n"
    "and remains completely still.");

const u8 gShucklePokedexTextUnused[] = _("");

const u8 gHeracrossPokedexText[] = _(
    "Usually docile, but if disturbed while\n"
    "sipping honey, it chases off the intruder\n"
    "with its horn.");

const u8 gHeracrossPokedexTextUnused[] = _("");

const u8 gSneaselPokedexText[] = _(
    "Vicious in nature, it drives PIDGEY from\n"
    "their nests and feasts on the eggs that\n"
    "are left behind.");

const u8 gSneaselPokedexTextUnused[] = _("");

const u8 gTeddiursaPokedexText[] = _(
    "Before food becomes scarce in wintertime,\n"
    "its habit is to hoard food in many hidden\n"
    "locations.");

const u8 gTeddiursaPokedexTextUnused[] = _("");

const u8 gUrsaringPokedexText[] = _(
    "With its ability to distinguish any smell,\n"
    "it unfailingly finds all food buried deep\n"
    "underground.");

const u8 gUrsaringPokedexTextUnused[] = _("");

const u8 gSlugmaPokedexText[] = _(
    "A common sight in volcanic areas, it\n"
    "slowly slithers around in a constant\n"
    "search for warm places.");

const u8 gSlugmaPokedexTextUnused[] = _("");

const u8 gMagcargoPokedexText[] = _(
    "Its brittle shell occasionally spouts\n"
    "intense flames that circulate throughout\n"
    "its body.");

const u8 gMagcargoPokedexTextUnused[] = _("");

const u8 gSwinubPokedexText[] = _(
    "If it smells something enticing, it dashes\n"
    "off headlong to find the source of the\n"
    "aroma.");

const u8 gSwinubPokedexTextUnused[] = _("");

const u8 gPiloswinePokedexText[] = _(
    "If it charges at an enemy, the hairs on\n"
    "its back stand up straight. It is very\n"
    "sensitive to sound.");

const u8 gPiloswinePokedexTextUnused[] = _("");

const u8 gCorsolaPokedexText[] = _(
    "In a south sea nation, the people live in\n"
    "communities that are built on groups of\n"
    "these POKéMON.");

const u8 gCorsolaPokedexTextUnused[] = _("");

const u8 gRemoraidPokedexText[] = _(
    "Using its dorsal fin as a suction pad, it\n"
    "clings to a MANTINE's underside to\n"
    "scavenge for leftovers.");

const u8 gRemoraidPokedexTextUnused[] = _("");

const u8 gOctilleryPokedexText[] = _(
    "It instinctively sneaks into rocky holes.\n"
    "If it gets sleepy, it steals the nest of a\n"
    "fellow OCTILLERY.");

const u8 gOctilleryPokedexTextUnused[] = _("");

const u8 gDelibirdPokedexText[] = _(
    "It nests at the edge of sharp cliffs.\n"
    "It spends all day carrying food to its\n"
    "awaiting chicks.");

const u8 gDelibirdPokedexTextUnused[] = _("");

const u8 gMantinePokedexText[] = _(
    "Swimming freely in open seas, it may fly\n"
    "out of the water and over the waves if it\n"
    "builds up enough speed.");

const u8 gMantinePokedexTextUnused[] = _("");

const u8 gSkarmoryPokedexText[] = _(
    "After nesting in bramble bushes, the wings\n"
    "of its chicks grow hard from scratches by\n"
    "thorns.");

const u8 gSkarmoryPokedexTextUnused[] = _("");

const u8 gHoundourPokedexText[] = _(
    "To corner prey, they check each other's\n"
    "location using barks that only they can\n"
    "understand.");

const u8 gHoundourPokedexTextUnused[] = _("");

const u8 gHoundoomPokedexText[] = _(
    "Upon hearing its eerie howls, other\n"
    "POKéMON get the shivers and head straight\n"
    "back to their nests.");

const u8 gHoundoomPokedexTextUnused[] = _("");

const u8 gKingdraPokedexText[] = _(
    "It sleeps deep on the ocean floor to\n"
    "build its energy. It is said to cause\n"
    "tornadoes as it wakes.");

const u8 gKingdraPokedexTextUnused[] = _("");

const u8 gPhanpyPokedexText[] = _(
    "As a sign of affection, it bumps with its\n"
    "snout. However, it is so strong, it may\n"
    "send you flying.");

const u8 gPhanpyPokedexTextUnused[] = _("");

const u8 gDonphanPokedexText[] = _(
    "The longer and bigger its tusks, the\n"
    "higher its rank in its herd. The tusks take\n"
    "a long time to grow.");

const u8 gDonphanPokedexTextUnused[] = _("");

const u8 gPorygon2PokedexText[] = _(
    "Further research enhanced its abilities.\n"
    "Sometimes, it may exhibit motions that\n"
    "were not programmed.");

const u8 gPorygon2PokedexTextUnused[] = _("");

const u8 gStantlerPokedexText[] = _(
    "Those who stare at its antlers will\n"
    "gradually lose control of their senses\n"
    "and be unable to stand.");

const u8 gStantlerPokedexTextUnused[] = _("");

const u8 gSmearglePokedexText[] = _(
    "Once it becomes an adult, it has a\n"
    "tendency to let its comrades plant\n"
    "footprints on its back.");

const u8 gSmearglePokedexTextUnused[] = _("");

const u8 gTyroguePokedexText[] = _(
    "Even though it is small, it can't be\n"
    "ignored because it will slug any handy\n"
    "target without warning.");

const u8 gTyroguePokedexTextUnused[] = _("");

const u8 gHitmontopPokedexText[] = _(
    "It launches kicks while spinning. If it\n"
    "spins at high speed, it may bore its way\n"
    "into the ground.");

const u8 gHitmontopPokedexTextUnused[] = _("");

const u8 gSmoochumPokedexText[] = _(
    "It always rocks its head slowly backwards\n"
    "and forwards as if it is trying to kiss\n"
    "someone.");

const u8 gSmoochumPokedexTextUnused[] = _("");

const u8 gElekidPokedexText[] = _(
    "Even in the most vicious storm, this\n"
    "POKéMON plays happily if thunder rumbles\n"
    "in the sky.");

const u8 gElekidPokedexTextUnused[] = _("");

const u8 gMagbyPokedexText[] = _(
    "It is found in volcanic craters. Its body\n"
    "heat exceeds 1,100 degrees Fahrenheit,\n"
    "so don't underestimate it.");

const u8 gMagbyPokedexTextUnused[] = _("");

const u8 gMiltankPokedexText[] = _(
    "If it has just had a baby, the milk it\n"
    "produces contains much more nutrition than\n"
    "usual.");

const u8 gMiltankPokedexTextUnused[] = _("");

const u8 gBlisseyPokedexText[] = _(
    "It has a very compassionate nature. If it\n"
    "sees a sick POKéMON, it will nurse the\n"
    "sufferer back to health.");

const u8 gBlisseyPokedexTextUnused[] = _("");

const u8 gRaikouPokedexText[] = _(
    "This POKéMON races across the\n"
    "land while barking a cry that sounds\n"
    "like crashing thunder.");

const u8 gRaikouPokedexTextUnused[] = _("");

const u8 gEnteiPokedexText[] = _(
    "A POKéMON that races across the land.\n"
    "It is said that one is born every time a\n"
    "new volcano appears.");

const u8 gEnteiPokedexTextUnused[] = _("");

const u8 gSuicunePokedexText[] = _(
    "This POKéMON races across the land.\n"
    "It is said that north winds will somehow\n"
    "blow whenever it appears.");

const u8 gSuicunePokedexTextUnused[] = _("");

const u8 gLarvitarPokedexText[] = _(
    "It is born deep underground. It can't\n"
    "emerge until it has entirely consumed the\n"
    "soil around it.");

const u8 gLarvitarPokedexTextUnused[] = _("");

const u8 gPupitarPokedexText[] = _(
    "Even sealed in its shell, it can move\n"
    "freely. Hard and fast, it has outstanding\n"
    "destructive power.");

const u8 gPupitarPokedexTextUnused[] = _("");

const u8 gTyranitarPokedexText[] = _(
#if REVISION == 0
    "Its body can't be harmed by any sort of\n"
    "attack, so it is very eager to make\n"
    "challenges against enemies."
#else
"It has an impudent nature. Having great\n"
    "strength, it can even change surrounding\n"
    "landforms."
#endif
);

const u8 gTyranitarPokedexTextUnused[] = _("");

const u8 gLugiaPokedexText[] = _(
    "It is said to be the guardian of the seas.\n"
    "It is rumored to have been seen on the\n"
    "night of a storm.");

const u8 gLugiaPokedexTextUnused[] = _("");

const u8 gHoOhPokedexText[] = _(
    "A legend says that its body glows in\n"
    "seven colors. A rainbow is said to form\n"
    "behind it when it flies.");

const u8 gHoOhPokedexTextUnused[] = _("");

const u8 gCelebiPokedexText[] = _(
    "When CELEBI disappears deep in a forest,\n"
    "it is said to leave behind an egg it\n"
    "brought from the future.");

const u8 gCelebiPokedexTextUnused[] = _("");

const u8 gTreeckoPokedexText[] = _(
    "It quickly scales even vertical walls.\n"
    "It senses humidity with its tail to predict\n"
    "the next day's weather.");

const u8 gTreeckoPokedexTextUnused[] = _("");

const u8 gGrovylePokedexText[] = _(
    "Its strongly developed thigh muscles\n"
    "give it astounding agility and jumping\n"
    "performance.");

const u8 gGrovylePokedexTextUnused[] = _("");

const u8 gSceptilePokedexText[] = _(
    "The leaves on its forelegs are as sharp\n"
    "as swords. It agilely leaps about the\n"
    "branches of trees to strike.");

const u8 gSceptilePokedexTextUnused[] = _("");

const u8 gTorchicPokedexText[] = _(
    "It has a flame sac inside its belly that\n"
    "perpetually burns. It feels warm if it is\n"
    "hugged.");

const u8 gTorchicPokedexTextUnused[] = _("");

const u8 gCombuskenPokedexText[] = _(
    "It boosts its concentration by emitting\n"
    "harsh cries. Its kicks have outstanding\n"
    "destructive power.");

const u8 gCombuskenPokedexTextUnused[] = _("");

const u8 gBlazikenPokedexText[] = _(
    "When facing a tough foe, it looses flames\n"
    "from its wrists. Its powerful legs let it\n"
    "jump clear over buildings.");

const u8 gBlazikenPokedexTextUnused[] = _("");

const u8 gMudkipPokedexText[] = _(
    "Its large tail fin propels it through\n"
    "water with powerful acceleration. It is\n"
    "strong in spite of its size.");

const u8 gMudkipPokedexTextUnused[] = _("");

const u8 gMarshtompPokedexText[] = _(
    "It is at its best when on muddy ground\n"
    "with poor footing. It quickly overwhelms\n"
    "foes struggling in mud.");

const u8 gMarshtompPokedexTextUnused[] = _("");

const u8 gSwampertPokedexText[] = _(
    "Its arms are rock-hard. With one swing,\n"
    "they can batter down its foe. It makes its\n"
    "nest on beautiful beaches.");

const u8 gSwampertPokedexTextUnused[] = _("");

const u8 gPoochyenaPokedexText[] = _(
    "It has a very tenacious nature. Its acute\n"
    "sense of smell lets it chase a chosen\n"
    "prey without ever losing track.");

const u8 gPoochyenaPokedexTextUnused[] = _("");

const u8 gMightyenaPokedexText[] = _(
    "It will always obey the commands of a\n"
    "skilled TRAINER. Its behavior arises from\n"
    "its living in packs in ancient times.");

const u8 gMightyenaPokedexTextUnused[] = _("");

const u8 gZigzagoonPokedexText[] = _(
    "A POKéMON with abundant curiosity.\n"
    "It shows an interest in everything, so it\n"
    "always zigs and zags.");

const u8 gZigzagoonPokedexTextUnused[] = _("");

const u8 gLinoonePokedexText[] = _(
    "When running in a straight line, it can top\n"
    "60 miles per hour. However, it has a\n"
    "tough time with curved roads.");

const u8 gLinoonePokedexTextUnused[] = _("");

const u8 gWurmplePokedexText[] = _(
    "It lives amidst tall grass and in forests.\n"
    "When attacked, it resists by pointing its\n"
    "venomous spikes at the foe.");

const u8 gWurmplePokedexTextUnused[] = _("");

const u8 gSilcoonPokedexText[] = _(
    "It conserves its energy by moving as\n"
    "little as possible. It awaits evolution\n"
    "while drinking only a little rainwater.");

const u8 gSilcoonPokedexTextUnused[] = _("");

const u8 gBeautiflyPokedexText[] = _(
    "Despite its appearance, it has an\n"
    "aggressive nature. It attacks by jabbing\n"
    "with its long, thin mouth.");

const u8 gBeautiflyPokedexTextUnused[] = _("");

const u8 gCascoonPokedexText[] = _(
    "Its body, which is made of soft silk,\n"
    "hardens over time. When cracks appear,\n"
    "evolution is near.");

const u8 gCascoonPokedexTextUnused[] = _("");

const u8 gDustoxPokedexText[] = _(
    "It scatters horribly toxic dust when it\n"
    "senses danger. They tend to gather in the\n"
    "glow of streetlamps at night.");

const u8 gDustoxPokedexTextUnused[] = _("");

const u8 gLotadPokedexText[] = _(
    "It searches about for clean water. If it\n"
    "does not drink water for too long, the\n"
    "leaf on its head wilts.");

const u8 gLotadPokedexTextUnused[] = _("");

const u8 gLombrePokedexText[] = _(
    "It lives at the water's edge where it is\n"
    "sunny. It sleeps on a bed of water grass\n"
    "by day and becomes active at night.");

const u8 gLombrePokedexTextUnused[] = _("");

const u8 gLudicoloPokedexText[] = _(
    "The rhythm of bright, festive music\n"
    "activates LUDICOLO's cells, making it more\n"
    "powerful.");

const u8 gLudicoloPokedexTextUnused[] = _("");

const u8 gSeedotPokedexText[] = _(
    "If it remains still, it becomes impossible\n"
    "to distinguish from real nuts. It delights\n"
    "in surprising foraging PIDGEY.");

const u8 gSeedotPokedexTextUnused[] = _("");

const u8 gNuzleafPokedexText[] = _(
    "They live in holes bored in large trees.\n"
    "The sound of NUZLEAF's grass flute fills\n"
    "listeners with dread.");

const u8 gNuzleafPokedexTextUnused[] = _("");

const u8 gShiftryPokedexText[] = _(
    "A POKéMON that was feared as a forest\n"
    "guardian. It can read the foe's mind and\n"
    "take preemptive action.");

const u8 gShiftryPokedexTextUnused[] = _("");

const u8 gTaillowPokedexText[] = _(
    "It dislikes cold seasons. They migrate to\n"
    "other lands in search of warmth, flying\n"
    "over 180 miles a day.");

const u8 gTaillowPokedexTextUnused[] = _("");

const u8 gSwellowPokedexText[] = _(
    "If its two tail feathers are standing at\n"
    "attention, it is proof of good health.\n"
    "It soars elegantly in the sky.");

const u8 gSwellowPokedexTextUnused[] = _("");

const u8 gWingullPokedexText[] = _(
    "It rides upon ocean winds as if it were\n"
    "a glider. In the winter, it hides food\n"
    "around its nest.");

const u8 gWingullPokedexTextUnused[] = _("");

const u8 gPelipperPokedexText[] = _(
    "It is a flying transporter that carries\n"
    "small POKéMON in its beak. It bobs on the\n"
    "waves to rest its wings.");

const u8 gPelipperPokedexTextUnused[] = _("");

const u8 gRaltsPokedexText[] = _(
    "It is highly attuned to the emotions of\n"
    "people and POKéMON. It hides if it senses\n"
    "hostility.");

const u8 gRaltsPokedexTextUnused[] = _("");

const u8 gKirliaPokedexText[] = _(
    "The cheerful spirit of its TRAINER gives\n"
    "it energy for its psychokinetic power.\n"
    "It spins and dances when happy.");

const u8 gKirliaPokedexTextUnused[] = _("");

const u8 gGardevoirPokedexText[] = _(
    "It has the power to predict the future.\n"
    "Its power peaks when it is protecting its\n"
    "TRAINER.");

const u8 gGardevoirPokedexTextUnused[] = _("");

const u8 gSurskitPokedexText[] = _(
    "They usually live on ponds, but after an\n"
    "evening shower, they may appear on\n"
    "puddles in towns.");

const u8 gSurskitPokedexTextUnused[] = _("");

const u8 gMasquerainPokedexText[] = _(
    "The antennae have distinctive patterns\n"
    "that look like eyes. When it rains, they\n"
    "grow heavy, making flight impossible.");

const u8 gMasquerainPokedexTextUnused[] = _("");

const u8 gShroomishPokedexText[] = _(
    "It prefers damp places. By day it remains\n"
    "still in the forest shade. It releases\n"
    "toxic powder from its head.");

const u8 gShroomishPokedexTextUnused[] = _("");

const u8 gBreloomPokedexText[] = _(
    "The seeds on its tail are made of toxic\n"
    "spores. It knocks out foes with quick,\n"
    "virtually invisible punches.");

const u8 gBreloomPokedexTextUnused[] = _("");

const u8 gSlakothPokedexText[] = _(
    "It sleeps for 20 hours every day. Making\n"
    "drowsy those that see it is one of\n"
    "its abilities.");

const u8 gSlakothPokedexTextUnused[] = _("");

const u8 gVigorothPokedexText[] = _(
    "It is always hungry because it won't stop\n"
    "rampaging. Even while it is eating, it\n"
    "can't keep still.");

const u8 gVigorothPokedexTextUnused[] = _("");

const u8 gSlakingPokedexText[] = _(
    "It is the world's most slothful POKéMON.\n"
    "However, it can exert horrifying power by\n"
    "releasing pent-up energy all at once.");

const u8 gSlakingPokedexTextUnused[] = _("");

const u8 gNincadaPokedexText[] = _(
    "Because it lived almost entirely\n"
    "underground, it is nearly blind.\n"
    "It uses its antennae instead.");

const u8 gNincadaPokedexTextUnused[] = _("");

const u8 gNinjaskPokedexText[] = _(
    "This POKéMON is so quick, it is said to\n"
    "be able to avoid any attack. It loves to\n"
    "feed on tree sap.");

const u8 gNinjaskPokedexTextUnused[] = _("");

const u8 gShedinjaPokedexText[] = _(
    "A most peculiar POKéMON that somehow\n"
    "appears in a POKé BALL when a NINCADA\n"
    "evolves.");

const u8 gShedinjaPokedexTextUnused[] = _("");

const u8 gWhismurPokedexText[] = _(
    "It usually murmurs, but starts crying\n"
    "loudly if it senses danger. It stops when\n"
    "its ear covers are shut.");

const u8 gWhismurPokedexTextUnused[] = _("");

const u8 gLoudredPokedexText[] = _(
    "When it stamps its feet and bellows, it\n"
    "generates ultrasonic waves that can blow\n"
    "apart a house.");

const u8 gLoudredPokedexTextUnused[] = _("");

const u8 gExploudPokedexText[] = _(
    "It emits a variety of sounds from the \n"
    "holes all over its body. Its loud cries\n"
    "can be heard from over six miles away.");

const u8 gExploudPokedexTextUnused[] = _("");

const u8 gMakuhitaPokedexText[] = _(
    "It grows stronger by enduring harsh\n"
    "training. It is a gutsy POKéMON that can\n"
    "withstand any attack.");

const u8 gMakuhitaPokedexTextUnused[] = _("");

const u8 gHariyamaPokedexText[] = _(
    "It stomps on the ground to build power.\n"
    "It can send a 10-ton truck flying with a\n"
    "straight-arm punch.");

const u8 gHariyamaPokedexTextUnused[] = _("");

const u8 gAzurillPokedexText[] = _(
    "It battles by flinging around its tail,\n"
    "which is bigger than its body. The\n"
    "tail is a flotation device in water.");

const u8 gAzurillPokedexTextUnused[] = _("");

const u8 gNosepassPokedexText[] = _(
    "Its magnetic nose consistently faces\n"
    "north. Travelers check NOSEPASS to get\n"
    "their bearings.");

const u8 gNosepassPokedexTextUnused[] = _("");

const u8 gSkittyPokedexText[] = _(
    "It is said to be difficult to earn its\n"
    "trust. However, it is extremely popular\n"
    "for its cute looks and behavior.");

const u8 gSkittyPokedexTextUnused[] = _("");

const u8 gDelcattyPokedexText[] = _(
    "The favorite of trend-conscious\n"
    "female TRAINERS, they are used in\n"
    "competition for their style and fur.");

const u8 gDelcattyPokedexTextUnused[] = _("");

const u8 gSableyePokedexText[] = _(
    "It feeds on gemstone crystals.\n"
    "In darkness, its eyes sparkle with the\n"
    "glitter of jewels.");

const u8 gSableyePokedexTextUnused[] = _("");

const u8 gMawilePokedexText[] = _(
    "It uses its docile-looking face to lull\n"
    "foes into complacency, then bites with its\n"
    "huge, relentless jaws.");

const u8 gMawilePokedexTextUnused[] = _("");

const u8 gAronPokedexText[] = _(
    "It eats iron to build its steel body.\n"
    "It is a pest that descends from mountains\n"
    "to eat bridges and train tracks.");

const u8 gAronPokedexTextUnused[] = _("");

const u8 gLaironPokedexText[] = _(
    "It habitually shows off its strength with\n"
    "the size of sparks it creates by ramming\n"
    "its steel body into boulders.");

const u8 gLaironPokedexTextUnused[] = _("");

const u8 gAggronPokedexText[] = _(
    "It claims a large mountain as its sole\n"
    "territory. It mercilessly thrashes those\n"
    "that violate its space.");

const u8 gAggronPokedexTextUnused[] = _("");

const u8 gMedititePokedexText[] = _(
    "It never skips its daily yoga training.\n"
    "It heightens its inner strength through\n"
    "meditation.");

const u8 gMedititePokedexTextUnused[] = _("");

const u8 gMedichamPokedexText[] = _(
    "It elegantly avoids attacks with dance-\n"
    "like steps, then launches a devastating\n"
    "blow in the same motion.");

const u8 gMedichamPokedexTextUnused[] = _("");

const u8 gElectrikePokedexText[] = _(
    "It stores static electricity in its fur\n"
    "for discharging. It gives off sparks if a\n"
    "storm approaches.");

const u8 gElectrikePokedexTextUnused[] = _("");

const u8 gManectricPokedexText[] = _(
    "It rarely appears before people.\n"
    "It is said to nest where lightning has\n"
    "fallen.");

const u8 gManectricPokedexTextUnused[] = _("");

const u8 gPluslePokedexText[] = _(
    "It cheers on partners while scattering\n"
    "sparks from its body. It climbs telephone\n"
    "poles to absorb electricity.");

const u8 gPluslePokedexTextUnused[] = _("");

const u8 gMinunPokedexText[] = _(
    "Its dislike of water makes it take shelter\n"
    "under the eaves of houses in rain. It uses\n"
    "pom-poms made of sparks for cheering.");

const u8 gMinunPokedexTextUnused[] = _("");

const u8 gVolbeatPokedexText[] = _(
    "It lives around clean ponds. At night,\n"
    "its rear lights up. It converses with\n"
    "others by flashing its light.");

const u8 gVolbeatPokedexTextUnused[] = _("");

const u8 gIllumisePokedexText[] = _(
    "It guides VOLBEAT to draw signs in night\n"
    "skies. There are scientists that study the\n"
    "patterns it creates.");

const u8 gIllumisePokedexTextUnused[] = _("");

const u8 gRoseliaPokedexText[] = _(
    "Its flowers give off a relaxing fragrance.\n"
    "The stronger its aroma, the healthier\n"
    "the ROSELIA is.");

const u8 gRoseliaPokedexTextUnused[] = _("");

const u8 gGulpinPokedexText[] = _(
    "There is nothing its stomach can't digest.\n"
    "While it is digesting, vile, overpowering\n"
    "gases are expelled.");

const u8 gGulpinPokedexTextUnused[] = _("");

const u8 gSwalotPokedexText[] = _(
    "It can swallow a tire whole in one gulp.\n"
    "It secretes a horribly toxic fluid from\n"
    "the pores on its body.");

const u8 gSwalotPokedexTextUnused[] = _("");

const u8 gCarvanhaPokedexText[] = _(
    "It lives in massive rivers that course\n"
    "through jungles. It swarms prey that\n"
    "enter its territory.");

const u8 gCarvanhaPokedexTextUnused[] = _("");

const u8 gSharpedoPokedexText[] = _(
    "The ruffian of the seas, it has fangs that\n"
    "crunch through iron. It swims by jetting\n"
    "water from its rear.");

const u8 gSharpedoPokedexTextUnused[] = _("");

const u8 gWailmerPokedexText[] = _(
    "When it sucks in a large volume of\n"
    "seawater, it becomes like a big, bouncy\n"
    "ball. It eats a ton of food daily.");

const u8 gWailmerPokedexTextUnused[] = _("");

const u8 gWailordPokedexText[] = _(
    "It is among the largest of all POKéMON.\n"
    "It herds prey in a pack then swallows the\n"
    "massed prey in one gulp.");

const u8 gWailordPokedexTextUnused[] = _("");

const u8 gNumelPokedexText[] = _(
    "Magma of almost 2,200 degrees Fahrenheit\n"
    "courses through its body. When it grows\n"
    "cold, the magma hardens and slows it.");

const u8 gNumelPokedexTextUnused[] = _("");

const u8 gCameruptPokedexText[] = _(
    "If angered, the humps on its back erupt\n"
    "in a shower of molten lava. It lives in\n"
    "the craters of volcanoes.");

const u8 gCameruptPokedexTextUnused[] = _("");

const u8 gTorkoalPokedexText[] = _(
    "It burns coal inside its shell. If it is\n"
    "attacked, it belches thick, black smoke\n"
    "and flees.");

const u8 gTorkoalPokedexTextUnused[] = _("");

const u8 gSpoinkPokedexText[] = _(
    "It apparently dies if it stops bouncing\n"
    "about. It carries a pearl from CLAMPERL\n"
    "on its head.");

const u8 gSpoinkPokedexTextUnused[] = _("");

const u8 gGrumpigPokedexText[] = _(
    "It can gain control over foes by doing\n"
    "odd dance steps. The black pearls on its\n"
    "forehead are precious gems.");

const u8 gGrumpigPokedexTextUnused[] = _("");

const u8 gSpindaPokedexText[] = _(
    "No two SPINDA are said to have identical\n"
    "patterns. It confuses foes with its\n"
    "stumbling motions.");

const u8 gSpindaPokedexTextUnused[] = _("");

const u8 gTrapinchPokedexText[] = _(
    "It lives in arid deserts. It makes a\n"
    "sloping pit trap in sand where it\n"
    "patiently awaits prey.");

const u8 gTrapinchPokedexTextUnused[] = _("");

const u8 gVibravaPokedexText[] = _(
    "It generates ultrasonic waves by violently\n"
    "flapping its wings. After making its prey\n"
    "faint, it melts the prey with acid.");

const u8 gVibravaPokedexTextUnused[] = _("");

const u8 gFlygonPokedexText[] = _(
    "It hides itself by kicking up desert sand\n"
    "with its wings. Red covers shield its eyes\n"
    "from sand.");

const u8 gFlygonPokedexTextUnused[] = _("");

const u8 gCacneaPokedexText[] = _(
    "It prefers harsh environments such as\n"
    "deserts. It can survive for 30 days on\n"
    "water stored in its body.");

const u8 gCacneaPokedexTextUnused[] = _("");

const u8 gCacturnePokedexText[] = _(
    "It lives in deserts. It becomes active at\n"
    "night when it hunts for prey exhausted\n"
    "from the desert's heat.");

const u8 gCacturnePokedexTextUnused[] = _("");

const u8 gSwabluPokedexText[] = _(
    "It constantly grooms its cotton-like\n"
    "wings. It takes a shower to clean\n"
    "itself if it becomes dirty.");

const u8 gSwabluPokedexTextUnused[] = _("");

const u8 gAltariaPokedexText[] = _(
    "If you hear a beautiful melody trilling\n"
    "deep among mountains far from people,\n"
    "it is ALTARIA's humming.");

const u8 gAltariaPokedexTextUnused[] = _("");

const u8 gZangoosePokedexText[] = _(
    "If it comes across a SEVIPER, its fur\n"
    "bristles and it assumes its battle pose.\n"
    "Its sharp claws are its best weapon.");

const u8 gZangoosePokedexTextUnused[] = _("");

const u8 gSeviperPokedexText[] = _(
    "It sharpens its swordlike tail on hard\n"
    "rocks. It hides in tall grass and strikes\n"
    "unwary prey with venomous fangs.");

const u8 gSeviperPokedexTextUnused[] = _("");

const u8 gLunatonePokedexText[] = _(
    "Its health ebbs and flows with the lunar\n"
    "cycle. It brims with power when exposed\n"
    "to the light of the full moon.");

const u8 gLunatonePokedexTextUnused[] = _("");

const u8 gSolrockPokedexText[] = _(
    "It absorbs solar energy during the day.\n"
    "Always expressionless, it can sense what\n"
    "its foe is thinking.");

const u8 gSolrockPokedexTextUnused[] = _("");

const u8 gBarboachPokedexText[] = _(
    "It probes muddy riverbeds with its two\n"
    "long whiskers. A slimy film protects its\n"
    "body.");

const u8 gBarboachPokedexTextUnused[] = _("");

const u8 gWhiscashPokedexText[] = _(
    "It makes its nest at the bottom of \n"
    "swamps. It will eat anything - if it is\n"
    "alive, WHISCASH will eat it.");

const u8 gWhiscashPokedexTextUnused[] = _("");

const u8 gCorphishPokedexText[] = _(
    "It came from overseas. It is a very hardy\n"
    "creature that will quickly proliferate,\n"
    "even in polluted streams.");

const u8 gCorphishPokedexTextUnused[] = _("");

const u8 gCrawdauntPokedexText[] = _(
    "A rough customer that wildly flails its\n"
    "giant claws. It is said to be extremely\n"
    "hard to raise.");

const u8 gCrawdauntPokedexTextUnused[] = _("");

const u8 gBaltoyPokedexText[] = _(
    "It was discovered in ancient ruins.\n"
    "While moving, it constantly spins. It\n"
    "stands on one foot even when asleep.");

const u8 gBaltoyPokedexTextUnused[] = _("");

const u8 gClaydolPokedexText[] = _(
    "It appears to have been born from clay\n"
    "dolls made by ancient people. It uses\n"
    "telekinesis to float and move.");

const u8 gClaydolPokedexTextUnused[] = _("");

const u8 gLileepPokedexText[] = _(
    "It became extinct roughly 100 million\n"
    "years ago. It was regenerated from a\n"
    "fossil using advanced techniques.");

const u8 gLileepPokedexTextUnused[] = _("");

const u8 gCradilyPokedexText[] = _(
    "It ensnares prey with its eight tentacles.\n"
    "It then melts the prey with a strong acid\n"
    "before feeding.");

const u8 gCradilyPokedexTextUnused[] = _("");

const u8 gAnorithPokedexText[] = _(
    "It is a kind of POKéMON progenitor.\n"
    "It uses its extending claws to catch prey\n"
    "hiding among rocks on the seafloor.");

const u8 gAnorithPokedexTextUnused[] = _("");

const u8 gArmaldoPokedexText[] = _(
    "Protected by a hard shell, its body is\n"
    "very sturdy. It skewers prey with its\n"
    "claws to feed.");

const u8 gArmaldoPokedexTextUnused[] = _("");

const u8 gFeebasPokedexText[] = _(
    "Ridiculed for its shabby appearance,\n"
    "it is ignored by researchers. It lives in\n"
    "ponds choked with weeds.");

const u8 gFeebasPokedexTextUnused[] = _("");

const u8 gMiloticPokedexText[] = _(
    "MILOTIC is breathtakingly beautiful.\n"
    "Those that see it are said to forget their\n"
    "combative spirits.");

const u8 gMiloticPokedexTextUnused[] = _("");

const u8 gCastformPokedexText[] = _(
    "It has the ability to change its form into\n"
    "the sun, the rain, or a snow cloud, \n"
    "depending on the weather.");

const u8 gCastformPokedexTextUnused[] = _("");

const u8 gKecleonPokedexText[] = _(
    "It changes body color to blend in with\n"
    "its surroundings. It also changes color if\n"
    "it is happy or sad.");

const u8 gKecleonPokedexTextUnused[] = _("");

const u8 gShuppetPokedexText[] = _(
    "It loves to feed on feelings like envy and\n"
    "malice. Its upright horn catches the\n"
    "emotions of people.");

const u8 gShuppetPokedexTextUnused[] = _("");

const u8 gBanettePokedexText[] = _(
    "Strong feelings of hatred turned a puppet\n"
    "into a POKéMON. If it opens its mouth,\n"
    "its cursed energy escapes.");

const u8 gBanettePokedexTextUnused[] = _("");

const u8 gDuskullPokedexText[] = _(
    "Making itself invisible, it silently sneaks\n"
    "up to prey. It has the ability to slip\n"
    "through thick walls.");

const u8 gDuskullPokedexTextUnused[] = _("");

const u8 gDusclopsPokedexText[] = _(
    "Its body is entirely hollow. When it opens\n"
    "its mouth, it sucks everything in as if it\n"
    "were a black hole.");

const u8 gDusclopsPokedexTextUnused[] = _("");

const u8 gTropiusPokedexText[] = _(
    "It lives in tropical jungles. The bunch of\n"
    "fruit around its neck is delicious.\n"
    "The fruit grows twice a year.");

const u8 gTropiusPokedexTextUnused[] = _("");

const u8 gChimechoPokedexText[] = _(
    "It travels by riding on winds. It cleverly\n"
    "uses its long tail to pluck nuts and\n"
    "berries, which it loves to eat.");

const u8 gChimechoPokedexTextUnused[] = _("");

const u8 gAbsolPokedexText[] = _(
    "It appears when it senses an impending\n"
    "natural disaster. As a result, it was\n"
    "mistaken as a doom-bringer.");

const u8 gAbsolPokedexTextUnused[] = _("");

const u8 gWynautPokedexText[] = _(
    "It tends to move in a pack with others.\n"
    "They cluster in a tight group to sleep in\n"
    "a cave.");

const u8 gWynautPokedexTextUnused[] = _("");

const u8 gSnoruntPokedexText[] = _(
    "It is said that a home visited by a\n"
    "SNORUNT will prosper. It can withstand\n"
    "cold of minus 150 degrees Fahrenheit.");

const u8 gSnoruntPokedexTextUnused[] = _("");

const u8 gGlaliePokedexText[] = _(
    "It has a body of ice that won't melt,\n"
    "even with fire. It can instantly freeze\n"
    "moisture in the atmosphere.");

const u8 gGlaliePokedexTextUnused[] = _("");

const u8 gSphealPokedexText[] = _(
    "Its body is covered in fluffy fur. The\n"
    "fur keeps it from feeling cold while\n"
    "it is rolling on ice.");

const u8 gSphealPokedexTextUnused[] = _("");

const u8 gSealeoPokedexText[] = _(
    "It touches new things with its nose to\n"
    "test for smell and feel. It plays by\n"
    "spinning SPHEAL on its nose.");

const u8 gSealeoPokedexTextUnused[] = _("");

const u8 gWalreinPokedexText[] = _(
    "It swims through icy seas while shattering\n"
    "ice floes with its large tusks. It is\n"
    "protected by its thick blubber.");

const u8 gWalreinPokedexTextUnused[] = _("");

const u8 gClamperlPokedexText[] = _(
    "It is protected by a sturdy shell.\n"
    "Once in a lifetime, it makes a magnificent\n"
    "pearl.");

const u8 gClamperlPokedexTextUnused[] = _("");

const u8 gHuntailPokedexText[] = _(
    "It lives deep in the sea where no light\n"
    "ever filters down. It lights up its small\n"
    "fishlike tail to attract prey.");

const u8 gHuntailPokedexTextUnused[] = _("");

const u8 gGorebyssPokedexText[] = _(
    "Its swimming form is exquisitely elegant.\n"
    "With its thin mouth, it feeds on seaweed\n"
    "that grows between rocks.");

const u8 gGorebyssPokedexTextUnused[] = _("");

const u8 gRelicanthPokedexText[] = _(
    "It has remained unchanged for 100\n"
    "million years. It was discovered\n"
    "during a deep-sea exploration.");

const u8 gRelicanthPokedexTextUnused[] = _("");

const u8 gLuvdiscPokedexText[] = _(
    "During the spawning season, countless\n"
    "LUVDISC congregate at coral reefs,\n"
    "turning the waters pink.");

const u8 gLuvdiscPokedexTextUnused[] = _("");

const u8 gBagonPokedexText[] = _(
    "Its steel-hard head can shatter boulders.\n"
    "It longingly hopes for wings to grow so it\n"
    "can fly.");

const u8 gBagonPokedexTextUnused[] = _("");

const u8 gShelgonPokedexText[] = _(
    "Its armored body makes all attacks bounce\n"
    "off. The armor is too tough, however,\n"
    "making it heavy and somewhat sluggish.");

const u8 gShelgonPokedexTextUnused[] = _("");

const u8 gSalamencePokedexText[] = _(
    "It becomes uncontrollable if it is\n"
    "enraged. It destroys everything with\n"
    "shredding claws and fire.");

const u8 gSalamencePokedexTextUnused[] = _("");

const u8 gBeldumPokedexText[] = _(
    "It uses magnetic waves to converse with\n"
    "its kind. All the cells in its body are\n"
    "magnetic.");

const u8 gBeldumPokedexTextUnused[] = _("");

const u8 gMetangPokedexText[] = _(
    "It floats midair using magnetism. Its body\n"
    "is so tough, even a crash with a jet\n"
    "plane won't leave a scratch.");

const u8 gMetangPokedexTextUnused[] = _("");

const u8 gMetagrossPokedexText[] = _(
    "It is formed by two METANG fusing.\n"
    "Its four brains are said to be superior\n"
    "to a supercomputer.");

const u8 gMetagrossPokedexTextUnused[] = _("");

const u8 gRegirockPokedexText[] = _(
    "It is entirely composed of rocks with no\n"
    "sign of a brain or heart. It is a mystery\n"
    "even to modern scientists.");

const u8 gRegirockPokedexTextUnused[] = _("");

const u8 gRegicePokedexText[] = _(
    "Research revealed that its body is made\n"
    "of the same kind of ice that is found at\n"
    "the South Pole.");

const u8 gRegicePokedexTextUnused[] = _("");

const u8 gRegisteelPokedexText[] = _(
    "It is sturdier than any kind of metal.\n"
    "It hardened due to pressure underground\n"
    "over tens of thousands of years.");

const u8 gRegisteelPokedexTextUnused[] = _("");

const u8 gLatiasPokedexText[] = _(
    "It can telepathically communicate with\n"
    "people. It changes its appearance using\n"
    "its down that refracts light.");

const u8 gLatiasPokedexTextUnused[] = _("");

const u8 gLatiosPokedexText[] = _(
    "It has a docile temperament and dislikes\n"
    "fighting. Tucking in its forelegs, it can\n"
    "fly faster than a jet plane.");

const u8 gLatiosPokedexTextUnused[] = _("");

const u8 gKyogrePokedexText[] = _(
    "This POKéMON is said to have\n"
    "expanded the sea by bringing heavy rains.\n"
    "It has the power to control water.");

const u8 gKyogrePokedexTextUnused[] = _("");

const u8 gGroudonPokedexText[] = _(
    "This legendary POKéMON is said to\n"
    "represent the land. It went to sleep after\n"
    "dueling KYOGRE.");

const u8 gGroudonPokedexTextUnused[] = _("");

const u8 gRayquazaPokedexText[] = _(
    "It has lived for hundreds of millions of\n"
    "years in the ozone layer. Its flying form\n"
    "looks like a meteor.");

const u8 gRayquazaPokedexTextUnused[] = _("");

const u8 gJirachiPokedexText[] = _(
    "It is said to make any wish come true.\n"
    "It is awake for only seven days out of\n"
    "a thousand years.");

const u8 gJirachiPokedexTextUnused[] = _("");

const u8 gDeoxysPokedexText[] = _(
    "This DEOXYS has transformed into its\n"
    "aggressive guise. It can fool enemies by\n"
    "altering its appearance.");

const u8 gDeoxysPokedexTextUnused[] = _("");
// ===== END src/data/pokemon/pokedex_text_fr.h =====
#elif defined(LEAFGREEN)
// ===== BEGIN src/data/pokemon/pokedex_text_lg.h =====
const u8 gDummyPokedexText[] = _(
    "This is a newly discovered POKéMON. It is\n"
    "currently under investigation. No detailed\n"
    "information is available at this time.");

const u8 gDummyPokedexTextUnused[] = _("");

const u8 gBulbasaurPokedexText[] = _(
    "A strange seed was planted on its back at\n"
    "birth. The plant sprouts and grows with\n"
    "this POKéMON.");

const u8 gBulbasaurPokedexTextUnused[] = _("");

const u8 gIvysaurPokedexText[] = _(
    "When the bulb on its back grows large, it\n"
    "appears to lose the ability to stand on\n"
    "its hind legs.");

const u8 gIvysaurPokedexTextUnused[] = _("");

const u8 gVenusaurPokedexText[] = _(
    "Its plant blooms when it is absorbing\n"
    "solar energy. It stays on the move to\n"
    "seek sunlight.");

const u8 gVenusaurPokedexTextUnused[] = _(
    " ");

const u8 gCharmanderPokedexText[] = _(
    "It has a preference for hot things.\n"
    "When it rains, steam is said to spout from\n"
    "the tip of its tail.");

const u8 gCharmanderPokedexTextUnused[] = _("");

const u8 gCharmeleonPokedexText[] = _(
    "When it swings its burning tail, it\n"
    "elevates the air temperature to \n"
    "unbearably high levels.");

const u8 gCharmeleonPokedexTextUnused[] = _("");

const u8 gCharizardPokedexText[] = _(
    "It spits fire that is hot enough to melt\n"
    "boulders. It may cause forest fires by\n"
    "blowing flames.");

const u8 gCharizardPokedexTextUnused[] = _("");

const u8 gSquirtlePokedexText[] = _(
    "After birth, its back swells and hardens\n"
    "into a shell. It powerfully sprays foam \n"
    "from its mouth.");

const u8 gSquirtlePokedexTextUnused[] = _("");

const u8 gWartortlePokedexText[] = _(
    "It often hides in water to stalk unwary\n"
    "prey. For fast swimming, it moves its\n"
    "ears to maintain balance.");

const u8 gWartortlePokedexTextUnused[] = _("");

const u8 gBlastoisePokedexText[] = _(
    "The pressurized water jets on this brutal\n"
    "POKéMON's shell are used for high-\n"
    "speed tackles.");

const u8 gBlastoisePokedexTextUnused[] = _("");

const u8 gCaterpiePokedexText[] = _(
    "Its short feet are tipped with suction\n"
    "pads that enable it to tirelessly climb\n"
    "slopes and walls.");

const u8 gCaterpiePokedexTextUnused[] = _("");

const u8 gMetapodPokedexText[] = _(
    "This POKéMON is vulnerable to attack\n"
    "while its shell is soft, exposing its weak\n"
    "and tender body.");

const u8 gMetapodPokedexTextUnused[] = _(
    " ");

const u8 gButterfreePokedexText[] = _(
    "In battle, it flaps its wings at great\n"
    "speed to release highly toxic dust into\n"
    "the air.");

const u8 gButterfreePokedexTextUnused[] = _(
    " ");

const u8 gWeedlePokedexText[] = _(
    "Often found in forests, eating leaves.\n"
    "It has a sharp stinger on its head that\n"
    "injects poison.");

const u8 gWeedlePokedexTextUnused[] = _("");

const u8 gKakunaPokedexText[] = _(
    "Almost incapable of moving, this POKéMON\n"
    "can only harden its shell to protect\n"
    "itself when it is in danger.");

const u8 gKakunaPokedexTextUnused[] = _("");

const u8 gBeedrillPokedexText[] = _(
    "It flies at high speed and attacks using \n"
    "the large venomous stingers on its\n"
    "forelegs and tail.");

const u8 gBeedrillPokedexTextUnused[] = _("");

const u8 gPidgeyPokedexText[] = _(
    "A common sight in forests and woods.\n"
    "It flaps its wings at ground level to kick\n"
    "up blinding sand.");

const u8 gPidgeyPokedexTextUnused[] = _("");

const u8 gPidgeottoPokedexText[] = _(
    "Very protective of its sprawling\n"
    "territorial area, this POKéMON will\n"
    "fiercely peck at any intruder.");

const u8 gPidgeottoPokedexTextUnused[] = _("");

const u8 gPidgeotPokedexText[] = _(
    "When hunting, it skims the surface of\n"
    "water at high speed to pick off unwary\n"
    "prey such as MAGIKARP.");

const u8 gPidgeotPokedexTextUnused[] = _("");

const u8 gRattataPokedexText[] = _(
    "Bites anything when it attacks. Small and\n"
    "very quick, it is a common sight in many\n"
    "places.");

const u8 gRattataPokedexTextUnused[] = _("");

const u8 gRaticatePokedexText[] = _(
    "It uses its whiskers to maintain its\n"
    "balance. It apparently slows down if\n"
    "they are cut off.");

const u8 gRaticatePokedexTextUnused[] = _("");

const u8 gSpearowPokedexText[] = _(
    "Eats bugs in grassy areas. It has to flap\n"
    "its short wings at high speed to stay\n"
    "airborne.");

const u8 gSpearowPokedexTextUnused[] = _("");

const u8 gFearowPokedexText[] = _(
    "With its huge and magnificent wings, it can\n"
    "keep aloft without ever having to land\n"
    "for rest.");

const u8 gFearowPokedexTextUnused[] = _("");

const u8 gEkansPokedexText[] = _(
    "Moving silently and stealthily, it eats\n"
    "the eggs of birds, such as PIDGEY\n"
    "and SPEAROW, whole.");

const u8 gEkansPokedexTextUnused[] = _("");

const u8 gArbokPokedexText[] = _(
    "It is rumored that the ferocious warning\n"
    "markings on its belly differ from area to\n"
    "area.");

const u8 gArbokPokedexTextUnused[] = _("");

const u8 gPikachuPokedexText[] = _(
    "When several of these POKéMON gather,\n"
    "their electricity can build and cause\n"
    "lightning storms.");

const u8 gPikachuPokedexTextUnused[] = _("");

const u8 gRaichuPokedexText[] = _(
    "Its long tail serves as a ground to\n"
    "protect itself from its own high-voltage\n"
    "power.");

const u8 gRaichuPokedexTextUnused[] = _("");

const u8 gSandshrewPokedexText[] = _(
    "Burrows deep underground in arid locations\n"
    "far from water. It only emerges to hunt\n"
    "for prey.");

const u8 gSandshrewPokedexTextUnused[] = _("");

const u8 gSandslashPokedexText[] = _(
    "Curls up into a spiny ball when\n"
    "threatened. It can roll while curled up\n"
    "to attack or escape.");

const u8 gSandslashPokedexTextUnused[] = _("");

const u8 gNidoranFPokedexText[] = _(
    "Although small, its venomous barbs render\n"
    "this POKéMON dangerous. The female has\n"
    "smaller horns.");

const u8 gNidoranFPokedexTextUnused[] = _("");

const u8 gNidorinaPokedexText[] = _(
    "The female's horns develop slowly.\n"
    "Prefers physical attacks such as clawing\n"
    "and biting.");

const u8 gNidorinaPokedexTextUnused[] = _("");

const u8 gNidoqueenPokedexText[] = _(
    "Its hard scales provide strong protection.\n"
    "It uses its hefty bulk to execute\n"
    "powerful moves.");

const u8 gNidoqueenPokedexTextUnused[] = _("");

const u8 gNidoranMPokedexText[] = _(
    "It stiffens its ears to sense danger.\n"
    "The larger its horns, the more \n"
    "powerful its secreted venom.");

const u8 gNidoranMPokedexTextUnused[] = _("");

const u8 gNidorinoPokedexText[] = _(
    "An aggressive POKéMON that is quick to\n"
    "attack. The horn on its head secretes a\n"
    "powerful venom.");

const u8 gNidorinoPokedexTextUnused[] = _("");

const u8 gNidokingPokedexText[] = _(
    "It uses its powerful tail in battle to\n"
    "smash, constrict, then break the prey's\n"
    "bones.");

const u8 gNidokingPokedexTextUnused[] = _("");

const u8 gClefairyPokedexText[] = _(
    "With its magical and cute appeal, it has \n"
    "many admirers. It is rare and found only\n"
    "in certain areas.");

const u8 gClefairyPokedexTextUnused[] = _("");

const u8 gClefablePokedexText[] = _(
    "A timid fairy POKéMON that is rarely seen,\n"
    "it will run and hide the moment it senses\n"
    "people.");

const u8 gClefablePokedexTextUnused[] = _("");

const u8 gVulpixPokedexText[] = _(
    "When it is born, it has just one snow-\n"
    "white tail. The tail splits from its tip as\n"
    "it grows older.");

const u8 gVulpixPokedexTextUnused[] = _("");

const u8 gNinetalesPokedexText[] = _(
    "Very smart and very vengeful. Grabbing\n"
    "one of its many tails could result in a\n"
    "1,000-year curse.");

const u8 gNinetalesPokedexTextUnused[] = _("");

const u8 gJigglypuffPokedexText[] = _(
    "When its huge eyes waver, it sings a\n"
    "mysteriously soothing melody that lulls\n"
    "its enemies to sleep.");

const u8 gJigglypuffPokedexTextUnused[] = _("");

const u8 gWigglytuffPokedexText[] = _(
    "The body is soft and rubbery. When\n"
    "angered, it will suck in air and inflate\n"
    "itself to an enormous size.");

const u8 gWigglytuffPokedexTextUnused[] = _("");

const u8 gZubatPokedexText[] = _(
    "It forms colonies in perpetually dark \n"
    "places and uses ultrasonic waves to  \n"
    "identify and approach targets.");

const u8 gZubatPokedexTextUnused[] = _("");

const u8 gGolbatPokedexText[] = _(
    "Once it bites, it will not stop draining\n"
    "energy from the victim even if it gets too\n"
    "heavy to fly.");

const u8 gGolbatPokedexTextUnused[] = _("");

const u8 gOddishPokedexText[] = _(
    "During the day, it keeps its face buried\n"
    "in the ground. At night, it wanders around\n"
    "sowing its seeds.");

const u8 gOddishPokedexTextUnused[] = _("");

const u8 gGloomPokedexText[] = _(
    "The fluid that oozes from its mouth isn't\n"
    "drool. It is a nectar that is used to\n"
    "attract prey.");

const u8 gGloomPokedexTextUnused[] = _("");

const u8 gVileplumePokedexText[] = _(
    "The larger its petals, the more toxic\n"
    "pollen it contains. Its big head is heavy\n"
    "and hard to hold up.");

const u8 gVileplumePokedexTextUnused[] = _("");

const u8 gParasPokedexText[] = _(
    "Burrows to suck tree roots. The mushrooms\n"
    "on its back grow by drawing nutrients from\n"
    "the bug host.");

const u8 gParasPokedexTextUnused[] = _("");

const u8 gParasectPokedexText[] = _(
    "A host-parasite pair in which the parasite\n"
    "mushroom has taken over the host bug.\n"
    "Prefers damp places. ");

const u8 gParasectPokedexTextUnused[] = _("");

const u8 gVenonatPokedexText[] = _(
    "Lives in the shadows of tall trees where\n"
    "it eats bugs. It is attracted by light\n"
    "at night.");

const u8 gVenonatPokedexTextUnused[] = _("");

const u8 gVenomothPokedexText[] = _(
    "The dustlike scales covering its wings\n"
    "are color-coded to indicate the kinds of\n"
    "poison it has.");

const u8 gVenomothPokedexTextUnused[] = _("");

const u8 gDiglettPokedexText[] = _(
    "Lives about one yard underground where it\n"
    "feeds on plant roots. It sometimes appears\n"
    "aboveground.");

const u8 gDiglettPokedexTextUnused[] = _("");

const u8 gDugtrioPokedexText[] = _(
    "A team of DIGLETT triplets. It triggers\n"
    "huge earthquakes by burrowing 60 miles\n"
    "underground.");

const u8 gDugtrioPokedexTextUnused[] = _("");

const u8 gMeowthPokedexText[] = _(
    "Adores round objects. It wanders the\n"
    "streets on a nightly basis to look for\n"
    "dropped loose change.");

const u8 gMeowthPokedexTextUnused[] = _("");

const u8 gPersianPokedexText[] = _(
    "Although its fur has many admirers, it is\n"
    "tough to raise as a pet because of its\n"
    "fickle meanness.");

const u8 gPersianPokedexTextUnused[] = _("");

const u8 gPsyduckPokedexText[] = _(
    "While lulling its enemies with its vacant\n"
    "look, this wily POKéMON will use\n"
    "psychokinetic powers.");

const u8 gPsyduckPokedexTextUnused[] = _("");

const u8 gGolduckPokedexText[] = _(
    "Often seen swimming elegantly by\n"
    "lakeshores. It is often mistaken for the\n"
    "Japanese monster Kappa.");

const u8 gGolduckPokedexTextUnused[] = _("");

const u8 gMankeyPokedexText[] = _(
    "Extremely quick to anger. It could be\n"
    "docile one moment, then thrashing away \n"
    "the next instant.");

const u8 gMankeyPokedexTextUnused[] = _("");

const u8 gPrimeapePokedexText[] = _(
    "Always furious and tenacious to boot.\n"
    "It will not abandon chasing its quarry\n"
    "until it catches up.");

const u8 gPrimeapePokedexTextUnused[] = _("");

const u8 gGrowlithePokedexText[] = _(
    "It is very protective of its territory.\n"
    "It will bark and bite to repel intruders\n"
    "from its space.");

const u8 gGrowlithePokedexTextUnused[] = _("");

const u8 gArcaninePokedexText[] = _(
    "A POKéMON that has long been admired\n"
    "for its beauty. It runs agilely as if\n"
    "on wings.");

const u8 gArcaninePokedexTextUnused[] = _("");

const u8 gPoliwagPokedexText[] = _(
    "Its newly grown legs prevent it from\n"
    "walking well. It appears to prefer\n"
    "swimming over walking.");

const u8 gPoliwagPokedexTextUnused[] = _("");

const u8 gPoliwhirlPokedexText[] = _(
    "It can live in or out of water. When out\n"
    "of water, it constantly sweats to keep its\n"
    "body slimy.");

const u8 gPoliwhirlPokedexTextUnused[] = _("");

const u8 gPoliwrathPokedexText[] = _(
    "A swimmer adept at both the front crawl\n"
    "and breaststroke. Easily overtakes the\n"
    "best human swimmers.");

const u8 gPoliwrathPokedexTextUnused[] = _("");

const u8 gAbraPokedexText[] = _(
    "Using its ability to read minds, it will\n"
    "sense impending danger and TELEPORT to\n"
    "safety.");

const u8 gAbraPokedexTextUnused[] = _("");

const u8 gKadabraPokedexText[] = _(
    "It emits special alpha waves from its\n"
    "body that induce headaches just by being\n"
    "close.");

const u8 gKadabraPokedexTextUnused[] = _("");

const u8 gAlakazamPokedexText[] = _(
    "Its brain can outperform a supercomputer.\n"
    "Its IQ (intelligence quotient) is said to\n"
    "be around 5,000.");

const u8 gAlakazamPokedexTextUnused[] = _("");

const u8 gMachopPokedexText[] = _(
    "Loves to build its muscles. It trains in\n"
    "all styles of martial arts to become even\n"
    "stronger.");

const u8 gMachopPokedexTextUnused[] = _("");

const u8 gMachokePokedexText[] = _(
    "Its muscular body is so powerful, it must\n"
    "wear a power-save belt to be able to\n"
    "regulate its motions.");

const u8 gMachokePokedexTextUnused[] = _("");

const u8 gMachampPokedexText[] = _(
    "Its superpowerful punches are said to\n"
    "knock the victim flying clear over the\n"
    "horizon.");

const u8 gMachampPokedexTextUnused[] = _("");

const u8 gBellsproutPokedexText[] = _(
    "A carnivorous POKéMON that traps and eats\n"
    "bugs. It appears to use its root feet to\n"
    "replenish moisture.");

const u8 gBellsproutPokedexTextUnused[] = _("");

const u8 gWeepinbellPokedexText[] = _(
    "It spits out POISONPOWDER to immobilize\n"
    "the enemy and then finishes it with a\n"
    "spray of ACID.");

const u8 gWeepinbellPokedexTextUnused[] = _("");

const u8 gVictreebelPokedexText[] = _(
    "Said to live in huge colonies deep in\n"
    "jungles, although no one has ever\n"
    "returned from there.");

const u8 gVictreebelPokedexTextUnused[] = _("");

const u8 gTentacoolPokedexText[] = _(
    "Drifts in shallow seas. Anglers who hook\n"
    "them by accident are often punished by\n"
    "their stingers.");

const u8 gTentacoolPokedexTextUnused[] = _("");

const u8 gTentacruelPokedexText[] = _(
    "The tentacles are normally kept short.\n"
    "On hunts, they are extended to ensnare\n"
    "and immobilize prey.");

const u8 gTentacruelPokedexTextUnused[] = _("");

const u8 gGeodudePokedexText[] = _(
    "Found in fields and mountains. Mistaking\n"
    "them for boulders, people often step or\n"
    "trip on them.");

const u8 gGeodudePokedexTextUnused[] = _("");

const u8 gGravelerPokedexText[] = _(
    "Rolls down slopes to move. It rolls over\n"
    "any obstacle without slowing or changing\n"
    "its direction.");

const u8 gGravelerPokedexTextUnused[] = _("");

const u8 gGolemPokedexText[] = _(
    "Its boulder-like body is extremely hard.\n"
    "It can easily withstand dynamite blasts\n"
    "without taking damage.");

const u8 gGolemPokedexTextUnused[] = _("");

const u8 gPonytaPokedexText[] = _(
    "Its hooves are ten times harder than\n"
    "diamond. It can trample anything\n"
    "completely flat in little time.");

const u8 gPonytaPokedexTextUnused[] = _("");

const u8 gRapidashPokedexText[] = _(
    "Very competitive, this POKéMON will chase\n"
    "anything that moves fast in the hopes of\n"
    "racing it.");

const u8 gRapidashPokedexTextUnused[] = _("");

const u8 gSlowpokePokedexText[] = _(
    "Incredibly slow and dopey. It takes five\n"
    "seconds for it to feel pain when under\n"
    "attack.");

const u8 gSlowpokePokedexTextUnused[] = _("");

const u8 gSlowbroPokedexText[] = _(
    "The SHELLDER that latches onto\n"
    "SLOWPOKE's tail is said to feed on the\n"
    "host's leftover scraps.");

const u8 gSlowbroPokedexTextUnused[] = _("");

const u8 gMagnemitePokedexText[] = _(
    "Uses antigravity to stay suspended.\n"
    "Appears without warning and uses THUNDER\n"
    "WAVE and similar moves.");

const u8 gMagnemitePokedexTextUnused[] = _("");

const u8 gMagnetonPokedexText[] = _(
    "Formed by several MAGNEMITE linked\n"
    "together. They frequently appear when\n"
    "sunspots flare up.");

const u8 gMagnetonPokedexTextUnused[] = _("");

const u8 gFarfetchdPokedexText[] = _(
    "The plant stalk it holds is its weapon.\n"
    "The stalk is used like a sword to cut all\n"
    "sorts of things.");

const u8 gFarfetchdPokedexTextUnused[] = _("");

const u8 gDoduoPokedexText[] = _(
    "A bird that makes up for its poor flying\n"
    "with its fast foot speed. Leaves giant\n"
    "footprints.");

const u8 gDoduoPokedexTextUnused[] = _("");

const u8 gDodrioPokedexText[] = _(
    "Uses its three brains to execute complex\n"
    "plans. While two heads sleep, one head is\n"
    "said to stay awake.");

const u8 gDodrioPokedexTextUnused[] = _("");

const u8 gSeelPokedexText[] = _(
    "The protruding horn on its head is very\n"
    "hard. It is used for bashing through thick\n"
    "icebergs.");

const u8 gSeelPokedexTextUnused[] = _("");

const u8 gDewgongPokedexText[] = _(
    "It stores thermal energy in the body.\n"
    "It swims at a steady eight knots even in\n"
    "intensely cold waters.");

const u8 gDewgongPokedexTextUnused[] = _("");

const u8 gGrimerPokedexText[] = _(
    "Appears in filthy areas. It thrives by\n"
    "sucking up polluted sludge that is pumped\n"
    "out of factories.");

const u8 gGrimerPokedexTextUnused[] = _("");

const u8 gMukPokedexText[] = _(
    "Thickly covered with a filthy, vile\n"
    "sludge. It is so toxic, even its footprints\n"
    "contain poison.");

const u8 gMukPokedexTextUnused[] = _("");

const u8 gShellderPokedexText[] = _(
    "Its hard shell repels any kind of attack.\n"
    "It is vulnerable only when its shell is\n"
    "open.");

const u8 gShellderPokedexTextUnused[] = _("");

const u8 gCloysterPokedexText[] = _(
    "When attacked, it launches its horns in\n"
    "quick volleys. Its innards have never been\n"
    "seen.");

const u8 gCloysterPokedexTextUnused[] = _("");

const u8 gGastlyPokedexText[] = _(
    "Almost invisible, this gaseous POKéMON\n"
    "cloaks the target and puts it to sleep\n"
    "without notice.");

const u8 gGastlyPokedexTextUnused[] = _("");

const u8 gHaunterPokedexText[] = _(
    "Because of its ability to slip through\n"
    "block walls, it is said to be from another\n"
    "dimension.");

const u8 gHaunterPokedexTextUnused[] = _("");

const u8 gGengarPokedexText[] = _(
    "On the night of a full moon, if shadows\n"
    "move on their own and laugh, it must be\n"
    "GENGAR's doing.");

const u8 gGengarPokedexTextUnused[] = _("");

const u8 gOnixPokedexText[] = _(
    "As it grows, the stone portions of its\n"
    "body harden to become similar to\n"
    "black-colored diamonds.");

const u8 gOnixPokedexTextUnused[] = _("");

const u8 gDrowzeePokedexText[] = _(
    "Puts enemies to sleep, then eats their\n"
    "dreams. Occasionally gets sick from eating\n"
    "only bad dreams.");

const u8 gDrowzeePokedexTextUnused[] = _("");

const u8 gHypnoPokedexText[] = _(
    "When it locks eyes with an enemy, it will\n"
    "use a mix of PSI moves such as HYPNOSIS\n"
    "and CONFUSION.");

const u8 gHypnoPokedexTextUnused[] = _("");

const u8 gKrabbyPokedexText[] = _(
    "Its pincers are not only powerful weapons,\n"
    "they are used for balance when walking\n"
    "sideways.");

const u8 gKrabbyPokedexTextUnused[] = _("");

const u8 gKinglerPokedexText[] = _(
    "The large pincer has 10,000-horsepower\n"
    "crushing force. However, its huge size\n"
    "makes it unwieldy to use.");

const u8 gKinglerPokedexTextUnused[] = _("");

const u8 gVoltorbPokedexText[] = _(
    "Usually found in power plants. Easily\n"
    "mistaken for a POKé BALL, it has\n"
    "zapped many people.");

const u8 gVoltorbPokedexTextUnused[] = _("");

const u8 gElectrodePokedexText[] = _(
    "It stores electric energy under very high\n"
    "pressure. It often explodes with little or\n"
    "no provocation.");

const u8 gElectrodePokedexTextUnused[] = _("");

const u8 gExeggcutePokedexText[] = _(
    "It is often mistaken for eggs. When\n"
    "disturbed, they quickly gather and attack\n"
    "in swarms.");

const u8 gExeggcutePokedexTextUnused[] = _("");

const u8 gExeggutorPokedexText[] = _(
    "It is said that on rare occasions, one\n"
    "of its heads will drop off and continue on\n"
    "as an EXEGGCUTE.");

const u8 gExeggutorPokedexTextUnused[] = _("");

const u8 gCubonePokedexText[] = _(
    "Because it never removes its skull helmet,\n"
    "no one has ever seen this POKéMON's real\n"
    "face.");

const u8 gCubonePokedexTextUnused[] = _("");

const u8 gMarowakPokedexText[] = _(
    "The bone it holds is its key weapon.\n"
    "It throws the bone skillfully like a\n"
    "boomerang to KO targets.");

const u8 gMarowakPokedexTextUnused[] = _("");

const u8 gHitmonleePokedexText[] = _(
    "When in a hurry, its legs lengthen\n"
    "progressively. It runs smoothly with\n"
    "extra-long, loping strides.");

const u8 gHitmonleePokedexTextUnused[] = _("");

const u8 gHitmonchanPokedexText[] = _(
    "While apparently doing nothing, it fires\n"
    "punches in lightning-fast volleys that are\n"
    "impossible to see.");

const u8 gHitmonchanPokedexTextUnused[] = _("");

const u8 gLickitungPokedexText[] = _(
    "Its tongue can be extended like a\n"
    "chameleon's. It leaves a tingling\n"
    "sensation when it licks enemies.");

const u8 gLickitungPokedexTextUnused[] = _("");

const u8 gKoffingPokedexText[] = _(
    "Because it stores several kinds of toxic\n"
    "gases in its body, it is prone to\n"
    "exploding without warning.");

const u8 gKoffingPokedexTextUnused[] = _("");

const u8 gWeezingPokedexText[] = _(
    "Where two kinds of poison gases meet, two\n"
    "KOFFING can fuse into a WEEZING over\n"
    "many years.");

const u8 gWeezingPokedexTextUnused[] = _("");

const u8 gRhyhornPokedexText[] = _(
    "Its massive bones are 1,000 times harder\n"
    "than human bones. Its TACKLE can knock a\n"
    "semitrailer flying.");

const u8 gRhyhornPokedexTextUnused[] = _("");

const u8 gRhydonPokedexText[] = _(
    "Protected by an armor-like hide, it is\n"
    "capable of living in molten lava of 3,600\n"
    "degrees Fahrenheit.");

const u8 gRhydonPokedexTextUnused[] = _("");

const u8 gChanseyPokedexText[] = _(
    "A rare and elusive POKéMON that is said\n"
    "to bring happiness to those who manage to\n"
    "catch one.");

const u8 gChanseyPokedexTextUnused[] = _("");

const u8 gTangelaPokedexText[] = _(
    "The whole body is swathed with wide vines\n"
    "that are similar to seaweed. The vines\n"
    "sway as it walks.");

const u8 gTangelaPokedexTextUnused[] = _("");

const u8 gKangaskhanPokedexText[] = _(
    "The infant rarely ventures out of its\n"
    "mother's protective pouch until it is\n"
    "three years old.");

const u8 gKangaskhanPokedexTextUnused[] = _("");

const u8 gHorseaPokedexText[] = _(
    "Known to shoot down flying bugs with\n"
    "precision blasts of ink from the surface\n"
    "of the water.");

const u8 gHorseaPokedexTextUnused[] = _("");

const u8 gSeadraPokedexText[] = _(
    "It is capable of swimming backwards by\n"
    "rapidly flapping its winglike pectoral fins\n"
    "and stout tail.");

const u8 gSeadraPokedexTextUnused[] = _("");

const u8 gGoldeenPokedexText[] = _(
    "Its tail fin billows like an elegant\n"
    "ballroom dress, giving it the nickname of\n"
    "“The Water Queen.”");

const u8 gGoldeenPokedexTextUnused[] = _("");

const u8 gSeakingPokedexText[] = _(
    "In the autumn spawning season, they can\n"
    "be seen swimming powerfully up rivers and\n"
    "creeks.");

const u8 gSeakingPokedexTextUnused[] = _("");

const u8 gStaryuPokedexText[] = _(
    "An enigmatic POKéMON that can effortlessly\n"
    "regenerate any appendage it loses in\n"
    "battle.");

const u8 gStaryuPokedexTextUnused[] = _("");

const u8 gStarmiePokedexText[] = _(
    "Its central core glows with the seven\n"
    "colors of the rainbow. Some people value\n"
    "the core as a gem.");

const u8 gStarmiePokedexTextUnused[] = _("");

const u8 gMrmimePokedexText[] = _(
    "If interrupted while it is miming, it will\n"
    "suddenly DOUBLESLAP the offender with its\n"
    "broad hands.");

const u8 gMrmimePokedexTextUnused[] = _("");

const u8 gScytherPokedexText[] = _(
    "With ninja-like agility and speed, it can\n"
    "create the illusion that there is more\n"
    "than one of itself.");

const u8 gScytherPokedexTextUnused[] = _("");

const u8 gJynxPokedexText[] = _(
    "It seductively wiggles its hips as it\n"
    "walks. It can cause people to dance in\n"
    "unison with it.");

const u8 gJynxPokedexTextUnused[] = _("");

const u8 gElectabuzzPokedexText[] = _(
    "Normally found near power plants, they\n"
    "can wander away and cause major\n"
    "blackouts in cities.");

const u8 gElectabuzzPokedexTextUnused[] = _("");

const u8 gMagmarPokedexText[] = _(
    "Its body always burns with an orange glow\n"
    "that enables it to hide perfectly amidst\n"
    "flames.");

const u8 gMagmarPokedexTextUnused[] = _("");

const u8 gPinsirPokedexText[] = _(
    "If it fails to crush the foe in its\n"
    "pincers, it will swing around and toss\n"
    "the opponent.");

const u8 gPinsirPokedexTextUnused[] = _("");

const u8 gTaurosPokedexText[] = _(
    "When it targets an enemy, it charges\n"
    "furiously while whipping its body with its\n"
    "long tails.");

const u8 gTaurosPokedexTextUnused[] = _("");

const u8 gMagikarpPokedexText[] = _(
    "In the distant past, it was somewhat\n"
    "stronger than the horribly weak\n"
    "descendants that exist today.");

const u8 gMagikarpPokedexTextUnused[] = _("");

const u8 gGyaradosPokedexText[] = _(
    "Rarely seen in the wild. Huge and vicious,\n"
    "it is capable of destroying entire cities\n"
    "in a rage.");

const u8 gGyaradosPokedexTextUnused[] = _("");

const u8 gLaprasPokedexText[] = _(
    "A POKéMON that has been overhunted\n"
    "almost to extinction. It can ferry people\n"
    "on its back.");

const u8 gLaprasPokedexTextUnused[] = _("");

const u8 gDittoPokedexText[] = _(
    "Capable of copying an opponent's genetic\n"
    "code to instantly transform itself into a\n"
    "duplicate of the enemy.");

const u8 gDittoPokedexTextUnused[] = _("");

const u8 gEeveePokedexText[] = _(
    "Its genetic code is irregular. It may\n"
    "mutate if it is exposed to radiation from\n"
    "element STONES.");

const u8 gEeveePokedexTextUnused[] = _("");

const u8 gVaporeonPokedexText[] = _(
    "Lives close to water. Its long tail is\n"
    "ridged with a fin which is often mistaken\n"
    "for a mermaid's.");

const u8 gVaporeonPokedexTextUnused[] = _("");

const u8 gJolteonPokedexText[] = _(
    "It accumulates negative ions in the\n"
    "atmosphere to blast out 10,000-volt\n"
    "lightning bolts.");

const u8 gJolteonPokedexTextUnused[] = _("");

const u8 gFlareonPokedexText[] = _(
    "When storing thermal energy in its body,\n"
    "its temperature can soar to over 1,600\n"
    "degrees Fahrenheit.");

const u8 gFlareonPokedexTextUnused[] = _("");

const u8 gPorygonPokedexText[] = _(
    "A POKéMON that consists entirely of\n"
    "programming code. It is capable of moving\n"
    "freely in cyberspace.");

const u8 gPorygonPokedexTextUnused[] = _("");

const u8 gOmanytePokedexText[] = _(
    "Although long extinct, in rare cases, it\n"
    "can be genetically regenerated from\n"
    "fossils.");

const u8 gOmanytePokedexTextUnused[] = _("");

const u8 gOmastarPokedexText[] = _(
    "Despite having strong fangs and tentacles,\n"
    "it went extinct when its heavy shell made\n"
    "it unable to catch prey.");

const u8 gOmastarPokedexTextUnused[] = _("");

const u8 gKabutoPokedexText[] = _(
    "A POKéMON that was regenerated from a\n"
    "fossil found in what was once the ocean\n"
    "floor long ago.");

const u8 gKabutoPokedexTextUnused[] = _("");

const u8 gKabutopsPokedexText[] = _(
    "Its sleek shape is perfect for swimming.\n"
    "It slashes prey with its claws and drains\n"
    "their fluids.");

const u8 gKabutopsPokedexTextUnused[] = _("");

const u8 gAerodactylPokedexText[] = _(
    "A ferocious, prehistoric POKéMON that\n"
    "goes for the enemy's throat with its\n"
    "serrated, sawlike fangs.");

const u8 gAerodactylPokedexTextUnused[] = _("");

const u8 gSnorlaxPokedexText[] = _(
    "Very lazy. Just eats and sleeps. As its\n"
    "rotund bulk builds, it becomes steadily\n"
    "more slothful.");

const u8 gSnorlaxPokedexTextUnused[] = _("");

const u8 gArticunoPokedexText[] = _(
    "A legendary bird POKéMON that is said to\n"
    "appear to doomed people who are lost in\n"
    "icy mountains.");

const u8 gArticunoPokedexTextUnused[] = _("");

const u8 gZapdosPokedexText[] = _(
    "A legendary bird POKéMON that is said to\n"
    "appear from clouds while dropping\n"
    "enormous lightning bolts.");

const u8 gZapdosPokedexTextUnused[] = _("");

const u8 gMoltresPokedexText[] = _(
    "It is said to be the legendary bird\n"
    "POKéMON of fire. Every flap of its wings\n"
    "creates a dazzling flare of flames.");

const u8 gMoltresPokedexTextUnused[] = _("");

const u8 gDratiniPokedexText[] = _(
    "Long considered a mythical POKéMON until\n"
    "recently, when a small colony was found\n"
    "living underwater.");

const u8 gDratiniPokedexTextUnused[] = _("");

const u8 gDragonairPokedexText[] = _(
    "A mystical POKéMON that exudes a gentle\n"
    "aura. It is said to have the ability to\n"
    "change the weather.");

const u8 gDragonairPokedexTextUnused[] = _("");

const u8 gDragonitePokedexText[] = _(
    "Only a very few people ever see this\n"
    "POKéMON. Its intelligence is said to\n"
    "match that of humans.");

const u8 gDragonitePokedexTextUnused[] = _("");

const u8 gMewtwoPokedexText[] = _(
    "It was created by a scientist after years\n"
    "of horrific gene-splicing and DNA-\n"
    "engineering experiments.");

const u8 gMewtwoPokedexTextUnused[] = _("");

const u8 gMewPokedexText[] = _(
    "So rare that it is still said to be a\n"
    "mirage by many experts. Only a few people\n"
    "have seen it worldwide.");

const u8 gMewPokedexTextUnused[] = _("");

const u8 gChikoritaPokedexText[] = _(
    "A sweet aroma gently wafts from the leaf\n"
    "on its head. It is docile and loves to\n"
    "soak up the sun's rays.");

const u8 gChikoritaPokedexTextUnused[] = _("");

const u8 gBayleefPokedexText[] = _(
    "The scent of spices comes from around\n"
    "its neck. Somehow, sniffing it makes you\n"
    "want to fight.");

const u8 gBayleefPokedexTextUnused[] = _("");

const u8 gMeganiumPokedexText[] = _(
    "The aroma that rises from its petals\n"
    "contains a substance that calms aggressive\n"
    "feelings.");

const u8 gMeganiumPokedexTextUnused[] = _("");

const u8 gCyndaquilPokedexText[] = _(
    "It is timid and always curls itself up in\n"
    "a ball. If attacked, it flares up its back\n"
    "for protection.");

const u8 gCyndaquilPokedexTextUnused[] = _("");

const u8 gQuilavaPokedexText[] = _(
    "Be careful if it turns its back during\n"
    "battle. It means that it will attack with\n"
    "the fire on its back.");

const u8 gQuilavaPokedexTextUnused[] = _("");

const u8 gTyphlosionPokedexText[] = _(
    "If its rage peaks, it becomes so hot that\n"
    "anything that touches it will instantly go\n"
    "up in flames.");

const u8 gTyphlosionPokedexTextUnused[] = _("");

const u8 gTotodilePokedexText[] = _(
    "Its well-developed jaws are powerful and\n"
    "capable of crushing anything. Even its\n"
    "TRAINER must be careful.");

const u8 gTotodilePokedexTextUnused[] = _("");

const u8 gCroconawPokedexText[] = _(
    "If it loses a fang, a new one grows back\n"
    "in its place. There are always 48 fangs\n"
    "lining its mouth.");

const u8 gCroconawPokedexTextUnused[] = _("");

const u8 gFeraligatrPokedexText[] = _(
    "When it bites with its massive and\n"
    "powerful jaws, it shakes its head and\n"
    "savagely tears up its victim.");

const u8 gFeraligatrPokedexTextUnused[] = _("");

const u8 gSentretPokedexText[] = _(
    "A very cautious POKéMON, it raises itself\n"
    "up using its tail to get a better view of\n"
    "its surroundings.");

const u8 gSentretPokedexTextUnused[] = _("");

const u8 gFurretPokedexText[] = _(
    "It makes a nest to suit its long and skinny\n"
    "body. The nest is impossible for other\n"
    "POKéMON to enter.");

const u8 gFurretPokedexTextUnused[] = _("");

const u8 gHoothootPokedexText[] = _(
    "It always stands on one foot. It changes\n"
    "feet so fast, the movement can rarely be\n"
    "seen.");

const u8 gHoothootPokedexTextUnused[] = _("");

const u8 gNoctowlPokedexText[] = _(
    "Its eyes are specially adapted. They\n"
    "concentrate even faint light and enable it\n"
    "to see in the dark.");

const u8 gNoctowlPokedexTextUnused[] = _("");

const u8 gLedybaPokedexText[] = _(
    "It is very timid. It will be afraid to\n"
    "move if it is alone. But it will be active\n"
    "if it is in a group.");

const u8 gLedybaPokedexTextUnused[] = _("");

const u8 gLedianPokedexText[] = _(
    "When the stars flicker in the night sky, it\n"
    "flutters about, scattering a glowing\n"
    "powder.");

const u8 gLedianPokedexTextUnused[] = _("");

const u8 gSpinarakPokedexText[] = _(
    "It lies still in the same pose for days\n"
    "in its web, waiting for its unsuspecting\n"
    "prey to wander close.");

const u8 gSpinarakPokedexTextUnused[] = _("");

const u8 gAriadosPokedexText[] = _(
    "It spins string not only from its rear but\n"
    "also from its mouth. It is hard to tell\n"
    "which end is which.");

const u8 gAriadosPokedexTextUnused[] = _("");

const u8 gCrobatPokedexText[] = _(
    "It flies so silently through the dark on\n"
    "its four wings that it may not be noticed\n"
    "even when nearby.");

const u8 gCrobatPokedexTextUnused[] = _("");

const u8 gChinchouPokedexText[] = _(
    "It shoots positive and negative\n"
    "electricity between the tips of its two\n"
    "antennae and zaps its enemies.");

const u8 gChinchouPokedexTextUnused[] = _("");

const u8 gLanturnPokedexText[] = _(
    "The light it emits is so bright that it can\n"
    "illuminate the sea's surface from a depth\n"
    "of over three miles.");

const u8 gLanturnPokedexTextUnused[] = _("");

const u8 gPichuPokedexText[] = _(
    "It is not yet skilled at storing\n"
    "electricity. It may send out a jolt if\n"
    "amused or startled.");

const u8 gPichuPokedexTextUnused[] = _("");

const u8 gCleffaPokedexText[] = _(
    "Because of its unusual, starlike\n"
    "silhouette, people believe that it came\n"
    "here on a meteor.");

const u8 gCleffaPokedexTextUnused[] = _("");

const u8 gIgglybuffPokedexText[] = _(
    "It has a very soft body. If it starts to\n"
    "roll, it will bounce all over and be\n"
    "impossible to stop.");

const u8 gIgglybuffPokedexTextUnused[] = _("");

const u8 gTogepiPokedexText[] = _(
    "The shell seems to be filled with joy.\n"
    "It is said that it will share good luck\n"
    "when treated kindly.");

const u8 gTogepiPokedexTextUnused[] = _("");

const u8 gTogeticPokedexText[] = _(
    "They say that it will appear before\n"
    "kindhearted, caring people and shower\n"
    "them with happiness.");

const u8 gTogeticPokedexTextUnused[] = _("");

const u8 gNatuPokedexText[] = _(
    "Because its wings aren't yet fully grown,\n"
    "it has to hop to get around. It is always\n"
    "staring at something.");

const u8 gNatuPokedexTextUnused[] = _("");

const u8 gXatuPokedexText[] = _(
    "They say that it stays still and quiet\n"
    "because it is seeing both the past and\n"
    "future at the same time.");

const u8 gXatuPokedexTextUnused[] = _("");

const u8 gMareepPokedexText[] = _(
    "If static electricity builds in its body,\n"
    "its fleece doubles in volume. Touching\n"
    "it will shock you.");

const u8 gMareepPokedexTextUnused[] = _("");

const u8 gFlaaffyPokedexText[] = _(
    "As a result of storing too much\n"
    "electricity, it developed patches where\n"
    "even downy wool won't grow.");

const u8 gFlaaffyPokedexTextUnused[] = _("");

const u8 gAmpharosPokedexText[] = _(
    "The tail's tip shines brightly and can be\n"
    "seen from far away. It acts as a beacon\n"
    "for lost people.");

const u8 gAmpharosPokedexTextUnused[] = _("");

const u8 gBellossomPokedexText[] = _(
    "BELLOSSOM gather at times and appear to\n"
    "dance. They say that the dance is a\n"
    "ritual to summon the sun.");

const u8 gBellossomPokedexTextUnused[] = _("");

const u8 gMarillPokedexText[] = _(
    "The tip of its tail, which contains oil\n"
    "that is lighter than water, lets it swim\n"
    "without drowning.");

const u8 gMarillPokedexTextUnused[] = _("");

const u8 gAzumarillPokedexText[] = _(
    "By keeping still and listening intently, it\n"
    "can even tell what is in wild, fast-moving\n"
    "rivers.");

const u8 gAzumarillPokedexTextUnused[] = _("");

const u8 gSudowoodoPokedexText[] = _(
    "Although it always pretends to be a tree,\n"
    "its composition appears to be closer to a\n"
    "rock than a plant.");

const u8 gSudowoodoPokedexTextUnused[] = _("");

const u8 gPolitoedPokedexText[] = _(
    "If POLIWAG and POLIWHIRL hear its\n"
    "echoing cry, they respond by gathering\n"
    "from far and wide.");

const u8 gPolitoedPokedexTextUnused[] = _("");

const u8 gHoppipPokedexText[] = _(
    "To keep from being blown away by the\n"
    "wind, they gather in clusters. They do\n"
    "enjoy gentle breezes, though.");

const u8 gHoppipPokedexTextUnused[] = _("");

const u8 gSkiploomPokedexText[] = _(
    "The bloom on top of its head opens and\n"
    "closes as the temperature fluctuates up\n"
    "and down.");

const u8 gSkiploomPokedexTextUnused[] = _("");

const u8 gJumpluffPokedexText[] = _(
    "Once it catches the wind, it deftly\n"
    "controls its cotton-puff spores to float,\n"
    "even around the world.");

const u8 gJumpluffPokedexTextUnused[] = _("");

const u8 gAipomPokedexText[] = _(
    "Its tail is so powerful that it can use it\n"
    "to grab a tree branch and hold itself up\n"
    "in the air.");

const u8 gAipomPokedexTextUnused[] = _("");

const u8 gSunkernPokedexText[] = _(
    "It may drop out of the sky suddenly.\n"
    "If attacked by a SPEAROW, it will\n"
    "violently shake its leaves.");

const u8 gSunkernPokedexTextUnused[] = _("");

const u8 gSunfloraPokedexText[] = _(
    "It converts sunlight into energy. In the\n"
    "darkness after sunset, it closes its petals\n"
    "and becomes still.");

const u8 gSunfloraPokedexTextUnused[] = _("");

const u8 gYanmaPokedexText[] = _(
    "If it flaps its wings really fast, it can\n"
    "generate shock waves that will shatter\n"
    "windows in the area.");

const u8 gYanmaPokedexTextUnused[] = _("");

const u8 gWooperPokedexText[] = _(
    "This POKéMON lives in cold water. It will\n"
    "leave the water to search for food when\n"
    "it gets cold outside.");

const u8 gWooperPokedexTextUnused[] = _("");

const u8 gQuagsirePokedexText[] = _(
    "This carefree POKéMON has an easygoing\n"
    "nature. While swimming, it always bumps\n"
    "into boat hulls.");

const u8 gQuagsirePokedexTextUnused[] = _("");

const u8 gEspeonPokedexText[] = _(
    "It uses the fine hair that covers its body\n"
    "to sense air currents and predict its\n"
    "enemy's actions.");

const u8 gEspeonPokedexTextUnused[] = _("");

const u8 gUmbreonPokedexText[] = _(
    "When agitated, this POKéMON protects\n"
    "itself by spraying poisonous sweat from its\n"
    "pores.");

const u8 gUmbreonPokedexTextUnused[] = _("");

const u8 gMurkrowPokedexText[] = _(
    "Feared and loathed by many, it is\n"
    "believed to bring misfortune to all those\n"
    "who see it at night.");

const u8 gMurkrowPokedexTextUnused[] = _("");

const u8 gSlowkingPokedexText[] = _(
    "It has incredible intellect and intuition.\n"
    "Whatever the situation, it remains calm\n"
    "and collected.");

const u8 gSlowkingPokedexTextUnused[] = _("");

const u8 gMisdreavusPokedexText[] = _(
    "It likes playing mischievous tricks such as\n"
    "screaming and wailing to startle people at\n"
    "night. ");

const u8 gMisdreavusPokedexTextUnused[] = _("");

const u8 gUnownPokedexText[] = _(
    "Their shapes look like hieroglyphs on\n"
    "ancient tablets. It is said that the two\n"
    "are somehow related.");

const u8 gUnownPokedexTextUnused[] = _("");

const u8 gWobbuffetPokedexText[] = _(
    "It hates light and shock. If attacked,\n"
    "it inflates its body to pump up its\n"
    "counterstrike.");

const u8 gWobbuffetPokedexTextUnused[] = _("");

const u8 gGirafarigPokedexText[] = _(
    "Its tail has a small brain of its own.\n"
    "Beware! If you get close, it may react\n"
    "to your scent and bite.");

const u8 gGirafarigPokedexTextUnused[] = _("");

const u8 gPinecoPokedexText[] = _(
    "It likes to make its shell thicker by\n"
    "adding layers of tree bark. The extra\n"
    "weight doesn't bother it.");

const u8 gPinecoPokedexTextUnused[] = _("");

const u8 gForretressPokedexText[] = _(
    "Its entire body is shielded by a steel-\n"
    "hard shell. What lurks inside the armor is\n"
    "a total mystery.");

const u8 gForretressPokedexTextUnused[] = _("");

const u8 gDunsparcePokedexText[] = _(
    "When spotted, this POKéMON escapes\n"
    "backward by furiously boring into the\n"
    "ground with its tail.");

const u8 gDunsparcePokedexTextUnused[] = _("");

const u8 gGligarPokedexText[] = _(
    "It flies straight at its target's face,\n"
    "then clamps down on the startled\n"
    "victim to inject poison.");

const u8 gGligarPokedexTextUnused[] = _("");

const u8 gSteelixPokedexText[] = _(
    "Its body has been compressed deep under\n"
    "the ground. As a result, it is even harder\n"
    "than diamond.");

const u8 gSteelixPokedexTextUnused[] = _("");

const u8 gSnubbullPokedexText[] = _(
    "Although it looks frightening, it is\n"
    "actually kind and affectionate. It is very\n"
    "popular among women.");

const u8 gSnubbullPokedexTextUnused[] = _("");

const u8 gGranbullPokedexText[] = _(
    "It is actually timid and easily spooked.\n"
    "If attacked, it flails about to fend off\n"
    "its attacker.");

const u8 gGranbullPokedexTextUnused[] = _("");

const u8 gQwilfishPokedexText[] = _(
    "To fire its poison spikes, it must inflate\n"
    "its body by drinking over 2.6 gallons of \n"
    "water all at once.");

const u8 gQwilfishPokedexTextUnused[] = _("");

const u8 gScizorPokedexText[] = _(
    "It swings its eye-patterned pincers up to\n"
    "scare its foes. This makes it look like it\n"
    "has three heads.");

const u8 gScizorPokedexTextUnused[] = _("");

const u8 gShucklePokedexText[] = _(
    "The BERRIES it stores in its vaselike\n"
    "shell decompose and become a gooey\n"
    "liquid.");

const u8 gShucklePokedexTextUnused[] = _("");

const u8 gHeracrossPokedexText[] = _(
    "This powerful POKéMON thrusts its prized\n"
    "horn under its enemies' bellies, then lifts\n"
    "and throws them.");

const u8 gHeracrossPokedexTextUnused[] = _("");

const u8 gSneaselPokedexText[] = _(
    "Its paws conceal sharp claws.\n"
    "If attacked, it suddenly extends the\n"
    "claws and startles its enemy.");

const u8 gSneaselPokedexTextUnused[] = _("");

const u8 gTeddiursaPokedexText[] = _(
    "If it finds honey, its crescent mark glows.\n"
    "It always licks its paws because they are\n"
    "soaked with honey.");

const u8 gTeddiursaPokedexTextUnused[] = _("");

const u8 gUrsaringPokedexText[] = _(
    "Although it is a good climber, it prefers\n"
    "to snap stout trees with its forelegs and\n"
    "eat fallen BERRIES.");

const u8 gUrsaringPokedexTextUnused[] = _("");

const u8 gSlugmaPokedexText[] = _(
    "It never sleeps. It has to keep moving\n"
    "because if it stopped, its magma body\n"
    "would cool and harden.");

const u8 gSlugmaPokedexTextUnused[] = _("");

const u8 gMagcargoPokedexText[] = _(
    "The shell on its back is just skin that\n"
    "has cooled and hardened. It breaks easily\n"
    "with a slight touch.");

const u8 gMagcargoPokedexTextUnused[] = _("");

const u8 gSwinubPokedexText[] = _(
    "It rubs its snout on the ground to find\n"
    "and dig up food. It sometimes discovers\n"
    "hot springs.");

const u8 gSwinubPokedexTextUnused[] = _("");

const u8 gPiloswinePokedexText[] = _(
    "Because the long hair all over its body\n"
    "obscures its sight, it just keeps charging\n"
    "repeatedly.");

const u8 gPiloswinePokedexTextUnused[] = _("");

const u8 gCorsolaPokedexText[] = _(
    "It continuously sheds and grows. The tip\n"
    "of its head is prized as a treasure for\n"
    "its beauty.");

const u8 gCorsolaPokedexTextUnused[] = _("");

const u8 gRemoraidPokedexText[] = _(
    "It has superb accuracy. The water it\n"
    "shoots out can strike even moving prey\n"
    "from more than 100 yards.");

const u8 gRemoraidPokedexTextUnused[] = _("");

const u8 gOctilleryPokedexText[] = _(
    "It traps enemies with its suction-cupped\n"
    "tentacles, then smashes them with its\n"
    "rock-hard head.");

const u8 gOctilleryPokedexTextUnused[] = _("");

const u8 gDelibirdPokedexText[] = _(
    "It carries food all day long. There are\n"
    "tales about lost people who were saved\n"
    "by the food it had.");

const u8 gDelibirdPokedexTextUnused[] = _("");

const u8 gMantinePokedexText[] = _(
    "As it majestically swims, it doesn't care\n"
    "if REMORAID attach to it to scavenge\n"
    "for its leftovers.");

const u8 gMantinePokedexTextUnused[] = _("");

const u8 gSkarmoryPokedexText[] = _(
    "Its sturdy wings look heavy, but its bones\n"
    "are hollow and light, allowing it to fly\n"
    "freely in the sky.");

const u8 gSkarmoryPokedexTextUnused[] = _("");

const u8 gHoundourPokedexText[] = _(
    "It uses different kinds of cries for\n"
    "communicating with others of its kind and\n"
    "for pursuing prey.");

const u8 gHoundourPokedexTextUnused[] = _("");

const u8 gHoundoomPokedexText[] = _(
    "If you are burned by the flames it shoots\n"
    "from its mouth, the pain will never go\n"
    "away.");

const u8 gHoundoomPokedexTextUnused[] = _("");

const u8 gKingdraPokedexText[] = _(
    "It is said that it usually hides in\n"
    "underwater caves. It can create\n"
    "whirlpools by yawning.");

const u8 gKingdraPokedexTextUnused[] = _("");

const u8 gPhanpyPokedexText[] = _(
    "It swings its long snout around playfully,\n"
    "but because it is so strong, this can be\n"
    "dangerous.");

const u8 gPhanpyPokedexTextUnused[] = _("");

const u8 gDonphanPokedexText[] = _(
    "It has sharp, hard tusks and a rugged\n"
    "hide. Its TACKLE is strong enough to\n"
    "knock down a house.");

const u8 gDonphanPokedexTextUnused[] = _("");

const u8 gPorygon2PokedexText[] = _(
    "This upgraded version of PORYGON is\n"
    "designed for space exploration. However,\n"
    "it can't even fly.");

const u8 gPorygon2PokedexTextUnused[] = _("");

const u8 gStantlerPokedexText[] = _(
    "Its curved antlers subtly change the flow\n"
    "of air to create a strange space where\n"
    "reality is distorted.");

const u8 gStantlerPokedexTextUnused[] = _("");

const u8 gSmearglePokedexText[] = _(
    "A special fluid oozes from the tip of its\n"
    "tail. It paints the fluid everywhere to\n"
    "mark its territory.");

const u8 gSmearglePokedexTextUnused[] = _("");

const u8 gTyroguePokedexText[] = _(
    "It is always bursting with energy. To make\n"
    "itself stronger, it keeps on fighting even\n"
    "if it loses.");

const u8 gTyroguePokedexTextUnused[] = _("");

const u8 gHitmontopPokedexText[] = _(
    "If you become enchanted by its smooth,\n"
    "elegant, dance-like kicks, you may get\n"
    "drilled hard.");

const u8 gHitmontopPokedexTextUnused[] = _("");

const u8 gSmoochumPokedexText[] = _(
    "Its lips are the most sensitive parts on\n"
    "its body. It always uses its lips first to\n"
    "examine things.");

const u8 gSmoochumPokedexTextUnused[] = _("");

const u8 gElekidPokedexText[] = _(
    "It rotates its arms to generate\n"
    "electricity, but it tires easily, so it\n"
    "charges up only a little bit.");

const u8 gElekidPokedexTextUnused[] = _("");

const u8 gMagbyPokedexText[] = _(
    "Each and every time it inhales and\n"
    "exhales, hot embers dribble out of its\n"
    "mouth and nostrils.");

const u8 gMagbyPokedexTextUnused[] = _("");

const u8 gMiltankPokedexText[] = _(
    "Its milk is packed with nutrition, making\n"
    "it the ultimate beverage for the sick or\n"
    "weary.");

const u8 gMiltankPokedexTextUnused[] = _("");

const u8 gBlisseyPokedexText[] = _(
    "Anyone who takes even one bite of\n"
    "BLISSEY's egg becomes unfailingly caring\n"
    "and pleasant to everyone.");

const u8 gBlisseyPokedexTextUnused[] = _("");

const u8 gRaikouPokedexText[] = _(
    "The rain clouds it carries let it fire\n"
    "thunderbolts at will. They say that it\n"
    "descended with lightning.");

const u8 gRaikouPokedexTextUnused[] = _("");

const u8 gEnteiPokedexText[] = _(
    "Volcanoes erupt when it barks. Unable to\n"
    "restrain its extreme power, it races\n"
    "headlong around the land.");

const u8 gEnteiPokedexTextUnused[] = _("");

const u8 gSuicunePokedexText[] = _(
    "Said to be the reincarnation of north\n"
    "winds, it can instantly purify filthy,\n"
    "murky water.");

const u8 gSuicunePokedexTextUnused[] = _("");

const u8 gLarvitarPokedexText[] = _(
    "It feeds on soil. After it has eaten a\n"
    "large mountain, it will fall asleep so it\n"
    "can grow.");

const u8 gLarvitarPokedexTextUnused[] = _("");

const u8 gPupitarPokedexText[] = _(
    "Its shell is as hard as sheet rock, and it\n"
    "is also very strong. Its THRASHING can\n"
    "topple a mountain.");

const u8 gPupitarPokedexTextUnused[] = _("");

const u8 gTyranitarPokedexText[] = _(
    "Its body can't be harmed by any sort of\n"
    "attack, so it is very eager to make\n"
    "challenges against enemies.");

const u8 gTyranitarPokedexTextUnused[] = _("");

const u8 gLugiaPokedexText[] = _(
    "It is said that it quietly spends its time\n"
    "deep at the bottom of the sea because\n"
    "its powers are too strong.");

const u8 gLugiaPokedexTextUnused[] = _("");

const u8 gHoOhPokedexText[] = _(
    "Legends claim this POKéMON flies the\n"
    "world's skies continuously on its\n"
    "magnificent seven-colored wings.");

const u8 gHoOhPokedexTextUnused[] = _("");

const u8 gCelebiPokedexText[] = _(
    "This POKéMON wanders across time.\n"
    "Grass and trees flourish in the forests in\n"
    "which it has appeared.");

const u8 gCelebiPokedexTextUnused[] = _("");

const u8 gTreeckoPokedexText[] = _(
    "It quickly scales even vertical walls.\n"
    "It senses humidity with its tail to predict\n"
    "the next day's weather.");

const u8 gTreeckoPokedexTextUnused[] = _("");

const u8 gGrovylePokedexText[] = _(
    "Its strongly developed thigh muscles\n"
    "give it astounding agility and jumping\n"
    "performance.");

const u8 gGrovylePokedexTextUnused[] = _("");

const u8 gSceptilePokedexText[] = _(
    "The leaves on its forelegs are as sharp\n"
    "as swords. It agilely leaps about the\n"
    "branches of trees to strike.");

const u8 gSceptilePokedexTextUnused[] = _("");

const u8 gTorchicPokedexText[] = _(
    "It has a flame sac inside its belly that\n"
    "perpetually burns. It feels warm if it is\n"
    "hugged.");

const u8 gTorchicPokedexTextUnused[] = _("");

const u8 gCombuskenPokedexText[] = _(
    "It boosts its concentration by emitting\n"
    "harsh cries. Its kicks have outstanding\n"
    "destructive power.");

const u8 gCombuskenPokedexTextUnused[] = _("");

const u8 gBlazikenPokedexText[] = _(
    "When facing a tough foe, it looses flames\n"
    "from its wrists. Its powerful legs let it\n"
    "jump clear over buildings.");

const u8 gBlazikenPokedexTextUnused[] = _("");

const u8 gMudkipPokedexText[] = _(
    "Its large tail fin propels it through\n"
    "water with powerful acceleration. It is\n"
    "strong in spite of its size.");

const u8 gMudkipPokedexTextUnused[] = _("");

const u8 gMarshtompPokedexText[] = _(
    "It is at its best when on muddy ground\n"
    "with poor footing. It quickly overwhelms\n"
    "foes struggling in mud.");

const u8 gMarshtompPokedexTextUnused[] = _("");

const u8 gSwampertPokedexText[] = _(
    "Its arms are rock-hard. With one swing,\n"
    "they can batter down its foe. It makes its\n"
    "nest on beautiful beaches.");

const u8 gSwampertPokedexTextUnused[] = _("");

const u8 gPoochyenaPokedexText[] = _(
    "It has a very tenacious nature. Its acute\n"
    "sense of smell lets it chase a chosen\n"
    "prey without ever losing track.");

const u8 gPoochyenaPokedexTextUnused[] = _("");

const u8 gMightyenaPokedexText[] = _(
    "It will always obey the commands of a\n"
    "skilled TRAINER. Its behavior arises from\n"
    "its living in packs in ancient times.");

const u8 gMightyenaPokedexTextUnused[] = _("");

const u8 gZigzagoonPokedexText[] = _(
    "A POKéMON with abundant curiosity.\n"
    "It shows an interest in everything, so it\n"
    "always zigs and zags.");

const u8 gZigzagoonPokedexTextUnused[] = _("");

const u8 gLinoonePokedexText[] = _(
    "When running in a straight line, it can top\n"
    "60 miles per hour. However, it has a\n"
    "tough time with curved roads.");

const u8 gLinoonePokedexTextUnused[] = _("");

const u8 gWurmplePokedexText[] = _(
    "It lives amidst tall grass and in forests.\n"
    "When attacked, it resists by pointing its\n"
    "venomous spikes at the foe.");

const u8 gWurmplePokedexTextUnused[] = _("");

const u8 gSilcoonPokedexText[] = _(
    "It conserves its energy by moving as\n"
    "little as possible. It awaits evolution\n"
    "while drinking only a little rainwater.");

const u8 gSilcoonPokedexTextUnused[] = _("");

const u8 gBeautiflyPokedexText[] = _(
    "Despite its appearance, it has an\n"
    "aggressive nature. It attacks by jabbing\n"
    "with its long, thin mouth.");

const u8 gBeautiflyPokedexTextUnused[] = _("");

const u8 gCascoonPokedexText[] = _(
    "Its body, which is made of soft silk,\n"
    "hardens over time. When cracks appear,\n"
    "evolution is near.");

const u8 gCascoonPokedexTextUnused[] = _("");

const u8 gDustoxPokedexText[] = _(
    "It scatters horribly toxic dust when it\n"
    "senses danger. They tend to gather in the\n"
    "glow of streetlamps at night.");

const u8 gDustoxPokedexTextUnused[] = _("");

const u8 gLotadPokedexText[] = _(
    "It searches about for clean water. If it\n"
    "does not drink water for too long, the\n"
    "leaf on its head wilts.");

const u8 gLotadPokedexTextUnused[] = _("");

const u8 gLombrePokedexText[] = _(
    "It lives at the water's edge where it is\n"
    "sunny. It sleeps on a bed of water grass\n"
    "by day and becomes active at night.");

const u8 gLombrePokedexTextUnused[] = _("");

const u8 gLudicoloPokedexText[] = _(
    "The rhythm of bright, festive music\n"
    "activates LUDICOLO's cells, making it more\n"
    "powerful.");

const u8 gLudicoloPokedexTextUnused[] = _("");

const u8 gSeedotPokedexText[] = _(
    "If it remains still, it becomes impossible\n"
    "to distinguish from real nuts. It delights\n"
    "in surprising foraging PIDGEY.");

const u8 gSeedotPokedexTextUnused[] = _("");

const u8 gNuzleafPokedexText[] = _(
    "They live in holes bored in large trees.\n"
    "The sound of NUZLEAF's grass flute fills\n"
    "listeners with dread.");

const u8 gNuzleafPokedexTextUnused[] = _("");

const u8 gShiftryPokedexText[] = _(
    "A POKéMON that was feared as a forest\n"
    "guardian. It can read the foe's mind and\n"
    "take preemptive action.");

const u8 gShiftryPokedexTextUnused[] = _("");

const u8 gTaillowPokedexText[] = _(
    "It dislikes cold seasons. They migrate to\n"
    "other lands in search of warmth, flying\n"
    "over 180 miles a day.");

const u8 gTaillowPokedexTextUnused[] = _("");

const u8 gSwellowPokedexText[] = _(
    "If its two tail feathers are standing at\n"
    "attention, it is proof of good health.\n"
    "It soars elegantly in the sky.");

const u8 gSwellowPokedexTextUnused[] = _("");

const u8 gWingullPokedexText[] = _(
    "It rides upon ocean winds as if it were\n"
    "a glider. In the winter, it hides food\n"
    "around its nest.");

const u8 gWingullPokedexTextUnused[] = _("");

const u8 gPelipperPokedexText[] = _(
    "It is a flying transporter that carries\n"
    "small POKéMON in its beak. It bobs on the\n"
    "waves to rest its wings.");

const u8 gPelipperPokedexTextUnused[] = _("");

const u8 gRaltsPokedexText[] = _(
    "It is highly attuned to the emotions of\n"
    "people and POKéMON. It hides if it senses\n"
    "hostility.");

const u8 gRaltsPokedexTextUnused[] = _("");

const u8 gKirliaPokedexText[] = _(
    "The cheerful spirit of its TRAINER gives\n"
    "it energy for its psychokinetic power.\n"
    "It spins and dances when happy.");

const u8 gKirliaPokedexTextUnused[] = _("");

const u8 gGardevoirPokedexText[] = _(
    "It has the power to predict the future.\n"
    "Its power peaks when it is protecting its\n"
    "TRAINER.");

const u8 gGardevoirPokedexTextUnused[] = _("");

const u8 gSurskitPokedexText[] = _(
    "They usually live on ponds, but after an\n"
    "evening shower, they may appear on\n"
    "puddles in towns.");

const u8 gSurskitPokedexTextUnused[] = _("");

const u8 gMasquerainPokedexText[] = _(
    "The antennae have distinctive patterns\n"
    "that look like eyes. When it rains, they\n"
    "grow heavy, making flight impossible.");

const u8 gMasquerainPokedexTextUnused[] = _("");

const u8 gShroomishPokedexText[] = _(
    "It prefers damp places. By day it remains\n"
    "still in the forest shade. It releases\n"
    "toxic powder from its head.");

const u8 gShroomishPokedexTextUnused[] = _("");

const u8 gBreloomPokedexText[] = _(
    "The seeds on its tail are made of toxic\n"
    "spores. It knocks out foes with quick,\n"
    "virtually invisible punches.");

const u8 gBreloomPokedexTextUnused[] = _("");

const u8 gSlakothPokedexText[] = _(
    "It sleeps for 20 hours every day. Making\n"
    "drowsy those that see it is one of\n"
    "its abilities.");

const u8 gSlakothPokedexTextUnused[] = _("");

const u8 gVigorothPokedexText[] = _(
    "It is always hungry because it won't stop\n"
    "rampaging. Even while it is eating, it\n"
    "can't keep still.");

const u8 gVigorothPokedexTextUnused[] = _("");

const u8 gSlakingPokedexText[] = _(
    "It is the world's most slothful POKéMON.\n"
    "However, it can exert horrifying power by\n"
    "releasing pent-up energy all at once.");

const u8 gSlakingPokedexTextUnused[] = _("");

const u8 gNincadaPokedexText[] = _(
    "Because it lived almost entirely\n"
    "underground, it is nearly blind.\n"
    "It uses its antennae instead.");

const u8 gNincadaPokedexTextUnused[] = _("");

const u8 gNinjaskPokedexText[] = _(
    "This POKéMON is so quick, it is said to\n"
    "be able to avoid any attack. It loves to\n"
    "feed on tree sap.");

const u8 gNinjaskPokedexTextUnused[] = _("");

const u8 gShedinjaPokedexText[] = _(
    "A most peculiar POKéMON that somehow\n"
    "appears in a POKé BALL when a NINCADA\n"
    "evolves.");

const u8 gShedinjaPokedexTextUnused[] = _("");

const u8 gWhismurPokedexText[] = _(
    "It usually murmurs, but starts crying\n"
    "loudly if it senses danger. It stops when\n"
    "its ear covers are shut.");

const u8 gWhismurPokedexTextUnused[] = _("");

const u8 gLoudredPokedexText[] = _(
    "When it stamps its feet and bellows, it\n"
    "generates ultrasonic waves that can blow\n"
    "apart a house.");

const u8 gLoudredPokedexTextUnused[] = _("");

const u8 gExploudPokedexText[] = _(
    "It emits a variety of sounds from the \n"
    "holes all over its body. Its loud cries\n"
    "can be heard from over six miles away.");

const u8 gExploudPokedexTextUnused[] = _("");

const u8 gMakuhitaPokedexText[] = _(
    "It grows stronger by enduring harsh\n"
    "training. It is a gutsy POKéMON that can\n"
    "withstand any attack.");

const u8 gMakuhitaPokedexTextUnused[] = _("");

const u8 gHariyamaPokedexText[] = _(
    "It stomps on the ground to build power.\n"
    "It can send a 10-ton truck flying with a\n"
    "straight-arm punch.");

const u8 gHariyamaPokedexTextUnused[] = _("");

const u8 gAzurillPokedexText[] = _(
    "It battles by flinging around its tail,\n"
    "which is bigger than its body. The\n"
    "tail is a flotation device in water.");

const u8 gAzurillPokedexTextUnused[] = _("");

const u8 gNosepassPokedexText[] = _(
    "Its magnetic nose consistently faces\n"
    "north. Travelers check NOSEPASS to get\n"
    "their bearings.");

const u8 gNosepassPokedexTextUnused[] = _("");

const u8 gSkittyPokedexText[] = _(
    "It is said to be difficult to earn its\n"
    "trust. However, it is extremely popular\n"
    "for its cute looks and behavior.");

const u8 gSkittyPokedexTextUnused[] = _("");

const u8 gDelcattyPokedexText[] = _(
    "The favorite of trend-conscious\n"
    "female TRAINERS, they are used in\n"
    "competition for their style and fur.");

const u8 gDelcattyPokedexTextUnused[] = _("");

const u8 gSableyePokedexText[] = _(
    "It feeds on gemstone crystals.\n"
    "In darkness, its eyes sparkle with the\n"
    "glitter of jewels.");

const u8 gSableyePokedexTextUnused[] = _("");

const u8 gMawilePokedexText[] = _(
    "It uses its docile-looking face to lull\n"
    "foes into complacency, then bites with its\n"
    "huge, relentless jaws.");

const u8 gMawilePokedexTextUnused[] = _("");

const u8 gAronPokedexText[] = _(
    "It eats iron to build its steel body.\n"
    "It is a pest that descends from mountains\n"
    "to eat bridges and train tracks.");

const u8 gAronPokedexTextUnused[] = _("");

const u8 gLaironPokedexText[] = _(
    "It habitually shows off its strength with\n"
    "the size of sparks it creates by ramming\n"
    "its steel body into boulders.");

const u8 gLaironPokedexTextUnused[] = _("");

const u8 gAggronPokedexText[] = _(
    "It claims a large mountain as its sole\n"
    "territory. It mercilessly thrashes those\n"
    "that violate its space.");

const u8 gAggronPokedexTextUnused[] = _("");

const u8 gMedititePokedexText[] = _(
    "It never skips its daily yoga training.\n"
    "It heightens its inner strength through\n"
    "meditation.");

const u8 gMedititePokedexTextUnused[] = _("");

const u8 gMedichamPokedexText[] = _(
    "It elegantly avoids attacks with dance-\n"
    "like steps, then launches a devastating\n"
    "blow in the same motion.");

const u8 gMedichamPokedexTextUnused[] = _("");

const u8 gElectrikePokedexText[] = _(
    "It stores static electricity in its fur\n"
    "for discharging. It gives off sparks if a\n"
    "storm approaches.");

const u8 gElectrikePokedexTextUnused[] = _("");

const u8 gManectricPokedexText[] = _(
    "It rarely appears before people.\n"
    "It is said to nest where lightning has\n"
    "fallen.");

const u8 gManectricPokedexTextUnused[] = _("");

const u8 gPluslePokedexText[] = _(
    "It cheers on partners while scattering\n"
    "sparks from its body. It climbs telephone\n"
    "poles to absorb electricity.");

const u8 gPluslePokedexTextUnused[] = _("");

const u8 gMinunPokedexText[] = _(
    "Its dislike of water makes it take shelter\n"
    "under the eaves of houses in rain. It uses\n"
    "pom-poms made of sparks for cheering.");

const u8 gMinunPokedexTextUnused[] = _("");

const u8 gVolbeatPokedexText[] = _(
    "It lives around clean ponds. At night,\n"
    "its rear lights up. It converses with\n"
    "others by flashing its light.");

const u8 gVolbeatPokedexTextUnused[] = _("");

const u8 gIllumisePokedexText[] = _(
    "It guides VOLBEAT to draw signs in night\n"
    "skies. There are scientists that study the\n"
    "patterns it creates.");

const u8 gIllumisePokedexTextUnused[] = _("");

const u8 gRoseliaPokedexText[] = _(
    "Its flowers give off a relaxing fragrance.\n"
    "The stronger its aroma, the healthier\n"
    "the ROSELIA is.");

const u8 gRoseliaPokedexTextUnused[] = _("");

const u8 gGulpinPokedexText[] = _(
    "There is nothing its stomach can't digest.\n"
    "While it is digesting, vile, overpowering\n"
    "gases are expelled.");

const u8 gGulpinPokedexTextUnused[] = _("");

const u8 gSwalotPokedexText[] = _(
    "It can swallow a tire whole in one gulp.\n"
    "It secretes a horribly toxic fluid from\n"
    "the pores on its body.");

const u8 gSwalotPokedexTextUnused[] = _("");

const u8 gCarvanhaPokedexText[] = _(
    "It lives in massive rivers that course\n"
    "through jungles. It swarms prey that\n"
    "enter its territory.");

const u8 gCarvanhaPokedexTextUnused[] = _("");

const u8 gSharpedoPokedexText[] = _(
    "The ruffian of the seas, it has fangs that\n"
    "crunch through iron. It swims by jetting\n"
    "water from its rear.");

const u8 gSharpedoPokedexTextUnused[] = _("");

const u8 gWailmerPokedexText[] = _(
    "When it sucks in a large volume of\n"
    "seawater, it becomes like a big, bouncy\n"
    "ball. It eats a ton of food daily.");

const u8 gWailmerPokedexTextUnused[] = _("");

const u8 gWailordPokedexText[] = _(
    "It is among the largest of all POKéMON.\n"
    "It herds prey in a pack then swallows the\n"
    "massed prey in one gulp.");

const u8 gWailordPokedexTextUnused[] = _("");

const u8 gNumelPokedexText[] = _(
    "Magma of almost 2,200 degrees Fahrenheit\n"
    "courses through its body. When it grows\n"
    "cold, the magma hardens and slows it.");

const u8 gNumelPokedexTextUnused[] = _("");

const u8 gCameruptPokedexText[] = _(
    "If angered, the humps on its back erupt\n"
    "in a shower of molten lava. It lives in\n"
    "the craters of volcanoes.");

const u8 gCameruptPokedexTextUnused[] = _("");

const u8 gTorkoalPokedexText[] = _(
    "It burns coal inside its shell. If it is\n"
    "attacked, it belches thick, black smoke\n"
    "and flees.");

const u8 gTorkoalPokedexTextUnused[] = _("");

const u8 gSpoinkPokedexText[] = _(
    "It apparently dies if it stops bouncing\n"
    "about. It carries a pearl from CLAMPERL\n"
    "on its head.");

const u8 gSpoinkPokedexTextUnused[] = _("");

const u8 gGrumpigPokedexText[] = _(
    "It can gain control over foes by doing\n"
    "odd dance steps. The black pearls on its\n"
    "forehead are precious gems.");

const u8 gGrumpigPokedexTextUnused[] = _("");

const u8 gSpindaPokedexText[] = _(
    "No two SPINDA are said to have identical\n"
    "patterns. It confuses foes with its\n"
    "stumbling motions.");

const u8 gSpindaPokedexTextUnused[] = _("");

const u8 gTrapinchPokedexText[] = _(
    "It lives in arid deserts. It makes a\n"
    "sloping pit trap in sand where it\n"
    "patiently awaits prey.");

const u8 gTrapinchPokedexTextUnused[] = _("");

const u8 gVibravaPokedexText[] = _(
    "It generates ultrasonic waves by violently\n"
    "flapping its wings. After making its prey\n"
    "faint, it melts the prey with acid.");

const u8 gVibravaPokedexTextUnused[] = _("");

const u8 gFlygonPokedexText[] = _(
    "It hides itself by kicking up desert sand\n"
    "with its wings. Red covers shield its eyes\n"
    "from sand.");

const u8 gFlygonPokedexTextUnused[] = _("");

const u8 gCacneaPokedexText[] = _(
    "It prefers harsh environments such as\n"
    "deserts. It can survive for 30 days on\n"
    "water stored in its body.");

const u8 gCacneaPokedexTextUnused[] = _("");

const u8 gCacturnePokedexText[] = _(
    "It lives in deserts. It becomes active at\n"
    "night when it hunts for prey exhausted\n"
    "from the desert's heat.");

const u8 gCacturnePokedexTextUnused[] = _("");

const u8 gSwabluPokedexText[] = _(
    "It constantly grooms its cotton-like\n"
    "wings. It takes a shower to clean\n"
    "itself if it becomes dirty.");

const u8 gSwabluPokedexTextUnused[] = _("");

const u8 gAltariaPokedexText[] = _(
    "If you hear a beautiful melody trilling\n"
    "deep among mountains far from people,\n"
    "it is ALTARIA's humming.");

const u8 gAltariaPokedexTextUnused[] = _("");

const u8 gZangoosePokedexText[] = _(
    "If it comes across a SEVIPER, its fur\n"
    "bristles and it assumes its battle pose.\n"
    "Its sharp claws are its best weapon.");

const u8 gZangoosePokedexTextUnused[] = _("");

const u8 gSeviperPokedexText[] = _(
    "It sharpens its swordlike tail on hard\n"
    "rocks. It hides in tall grass and strikes\n"
    "unwary prey with venomous fangs.");

const u8 gSeviperPokedexTextUnused[] = _("");

const u8 gLunatonePokedexText[] = _(
    "Its health ebbs and flows with the lunar\n"
    "cycle. It brims with power when exposed\n"
    "to the light of the full moon.");

const u8 gLunatonePokedexTextUnused[] = _("");

const u8 gSolrockPokedexText[] = _(
    "It absorbs solar energy during the day.\n"
    "Always expressionless, it can sense what\n"
    "its foe is thinking.");

const u8 gSolrockPokedexTextUnused[] = _("");

const u8 gBarboachPokedexText[] = _(
    "It probes muddy riverbeds with its two\n"
    "long whiskers. A slimy film protects its\n"
    "body.");

const u8 gBarboachPokedexTextUnused[] = _("");

const u8 gWhiscashPokedexText[] = _(
    "It makes its nest at the bottom of \n"
    "swamps. It will eat anything - if it is\n"
    "alive, WHISCASH will eat it.");

const u8 gWhiscashPokedexTextUnused[] = _("");

const u8 gCorphishPokedexText[] = _(
    "It came from overseas. It is a very hardy\n"
    "creature that will quickly proliferate,\n"
    "even in polluted streams.");

const u8 gCorphishPokedexTextUnused[] = _("");

const u8 gCrawdauntPokedexText[] = _(
    "A rough customer that wildly flails its\n"
    "giant claws. It is said to be extremely\n"
    "hard to raise.");

const u8 gCrawdauntPokedexTextUnused[] = _("");

const u8 gBaltoyPokedexText[] = _(
    "It was discovered in ancient ruins.\n"
    "While moving, it constantly spins. It\n"
    "stands on one foot even when asleep.");

const u8 gBaltoyPokedexTextUnused[] = _("");

const u8 gClaydolPokedexText[] = _(
    "It appears to have been born from clay\n"
    "dolls made by ancient people. It uses\n"
    "telekinesis to float and move.");

const u8 gClaydolPokedexTextUnused[] = _("");

const u8 gLileepPokedexText[] = _(
    "It became extinct roughly 100 million\n"
    "years ago. It was regenerated from a\n"
    "fossil using advanced techniques.");

const u8 gLileepPokedexTextUnused[] = _("");

const u8 gCradilyPokedexText[] = _(
    "It ensnares prey with its eight tentacles.\n"
    "It then melts the prey with a strong acid\n"
    "before feeding.");

const u8 gCradilyPokedexTextUnused[] = _("");

const u8 gAnorithPokedexText[] = _(
    "It is a kind of POKéMON progenitor.\n"
    "It uses its extending claws to catch prey\n"
    "hiding among rocks on the seafloor.");

const u8 gAnorithPokedexTextUnused[] = _("");

const u8 gArmaldoPokedexText[] = _(
    "Protected by a hard shell, its body is\n"
    "very sturdy. It skewers prey with its\n"
    "claws to feed.");

const u8 gArmaldoPokedexTextUnused[] = _("");

const u8 gFeebasPokedexText[] = _(
    "Ridiculed for its shabby appearance,\n"
    "it is ignored by researchers. It lives in\n"
    "ponds choked with weeds.");

const u8 gFeebasPokedexTextUnused[] = _("");

const u8 gMiloticPokedexText[] = _(
    "MILOTIC is breathtakingly beautiful.\n"
    "Those that see it are said to forget their\n"
    "combative spirits.");

const u8 gMiloticPokedexTextUnused[] = _("");

const u8 gCastformPokedexText[] = _(
    "It has the ability to change its form into\n"
    "the sun, the rain, or a snow cloud, \n"
    "depending on the weather.");

const u8 gCastformPokedexTextUnused[] = _("");

const u8 gKecleonPokedexText[] = _(
    "It changes body color to blend in with\n"
    "its surroundings. It also changes color if\n"
    "it is happy or sad.");

const u8 gKecleonPokedexTextUnused[] = _("");

const u8 gShuppetPokedexText[] = _(
    "It loves to feed on feelings like envy and\n"
    "malice. Its upright horn catches the\n"
    "emotions of people.");

const u8 gShuppetPokedexTextUnused[] = _("");

const u8 gBanettePokedexText[] = _(
    "Strong feelings of hatred turned a puppet\n"
    "into a POKéMON. If it opens its mouth,\n"
    "its cursed energy escapes.");

const u8 gBanettePokedexTextUnused[] = _("");

const u8 gDuskullPokedexText[] = _(
    "Making itself invisible, it silently sneaks\n"
    "up to prey. It has the ability to slip\n"
    "through thick walls.");

const u8 gDuskullPokedexTextUnused[] = _("");

const u8 gDusclopsPokedexText[] = _(
    "Its body is entirely hollow. When it opens\n"
    "its mouth, it sucks everything in as if it\n"
    "were a black hole.");

const u8 gDusclopsPokedexTextUnused[] = _("");

const u8 gTropiusPokedexText[] = _(
    "It lives in tropical jungles. The bunch of\n"
    "fruit around its neck is delicious.\n"
    "The fruit grows twice a year.");

const u8 gTropiusPokedexTextUnused[] = _("");

const u8 gChimechoPokedexText[] = _(
    "It travels by riding on winds. It cleverly\n"
    "uses its long tail to pluck nuts and\n"
    "berries, which it loves to eat.");

const u8 gChimechoPokedexTextUnused[] = _("");

const u8 gAbsolPokedexText[] = _(
    "It appears when it senses an impending\n"
    "natural disaster. As a result, it was\n"
    "mistaken as a doom-bringer.");

const u8 gAbsolPokedexTextUnused[] = _("");

const u8 gWynautPokedexText[] = _(
    "It tends to move in a pack with others.\n"
    "They cluster in a tight group to sleep in\n"
    "a cave.");

const u8 gWynautPokedexTextUnused[] = _("");

const u8 gSnoruntPokedexText[] = _(
    "It is said that a home visited by a\n"
    "SNORUNT will prosper. It can withstand\n"
    "cold of minus 150 degrees Fahrenheit.");

const u8 gSnoruntPokedexTextUnused[] = _("");

const u8 gGlaliePokedexText[] = _(
    "It has a body of ice that won't melt,\n"
    "even with fire. It can instantly freeze\n"
    "moisture in the atmosphere.");

const u8 gGlaliePokedexTextUnused[] = _("");

const u8 gSphealPokedexText[] = _(
    "Its body is covered in fluffy fur.\n"
    "The fur keeps it from feeling cold while\n"
    "it is rolling on ice.");

const u8 gSphealPokedexTextUnused[] = _("");

const u8 gSealeoPokedexText[] = _(
    "It touches new things with its nose to\n"
    "test for smell and feel. It plays by\n"
    "spinning SPHEAL on its nose.");

const u8 gSealeoPokedexTextUnused[] = _("");

const u8 gWalreinPokedexText[] = _(
    "It swims through icy seas while shattering\n"
    "ice floes with its large tusks. It is\n"
    "protected by its thick blubber.");

const u8 gWalreinPokedexTextUnused[] = _("");

const u8 gClamperlPokedexText[] = _(
    "It is protected by a sturdy shell.\n"
    "Once in a lifetime, it makes a magnificent\n"
    "pearl.");

const u8 gClamperlPokedexTextUnused[] = _("");

const u8 gHuntailPokedexText[] = _(
    "It lives deep in the sea where no light\n"
    "ever filters down. It lights up its small\n"
    "fishlike tail to attract prey.");

const u8 gHuntailPokedexTextUnused[] = _("");

const u8 gGorebyssPokedexText[] = _(
    "Its swimming form is exquisitely elegant.\n"
    "With its thin mouth, it feeds on seaweed\n"
    "that grows between rocks.");

const u8 gGorebyssPokedexTextUnused[] = _("");

const u8 gRelicanthPokedexText[] = _(
    "It has remained unchanged for 100\n"
    "million years. It was discovered\n"
    "during a deep-sea exploration.");

const u8 gRelicanthPokedexTextUnused[] = _("");

const u8 gLuvdiscPokedexText[] = _(
    "During the spawning season, countless\n"
    "LUVDISC congregate at coral reefs,\n"
    "turning the waters pink.");

const u8 gLuvdiscPokedexTextUnused[] = _("");

const u8 gBagonPokedexText[] = _(
    "Its steel-hard head can shatter boulders.\n"
    "It longingly hopes for wings to grow so it\n"
    "can fly.");

const u8 gBagonPokedexTextUnused[] = _("");

const u8 gShelgonPokedexText[] = _(
    "Its armored body makes all attacks bounce\n"
    "off. The armor is too tough, however,\n"
    "making it heavy and somewhat sluggish.");

const u8 gShelgonPokedexTextUnused[] = _("");

const u8 gSalamencePokedexText[] = _(
    "It becomes uncontrollable if it is\n"
    "enraged. It destroys everything with\n"
    "shredding claws and fire.");

const u8 gSalamencePokedexTextUnused[] = _("");

const u8 gBeldumPokedexText[] = _(
    "It uses magnetic waves to converse with\n"
    "its kind. All the cells in its body are\n"
    "magnetic.");

const u8 gBeldumPokedexTextUnused[] = _("");

const u8 gMetangPokedexText[] = _(
    "It floats midair using magnetism. Its body\n"
    "is so tough, even a crash with a jet\n"
    "plane won't leave a scratch.");

const u8 gMetangPokedexTextUnused[] = _("");

const u8 gMetagrossPokedexText[] = _(
    "It is formed by two METANG fusing.\n"
    "Its four brains are said to be superior\n"
    "to a supercomputer.");

const u8 gMetagrossPokedexTextUnused[] = _("");

const u8 gRegirockPokedexText[] = _(
    "It is entirely composed of rocks with no\n"
    "sign of a brain or heart. It is a mystery\n"
    "even to modern scientists.");

const u8 gRegirockPokedexTextUnused[] = _("");

const u8 gRegicePokedexText[] = _(
    "Research revealed that its body is made\n"
    "of the same kind of ice that is found at\n"
    "the South Pole.");

const u8 gRegicePokedexTextUnused[] = _("");

const u8 gRegisteelPokedexText[] = _(
    "It is sturdier than any kind of metal.\n"
    "It hardened due to pressure underground\n"
    "over tens of thousands of years.");

const u8 gRegisteelPokedexTextUnused[] = _("");

const u8 gLatiasPokedexText[] = _(
    "It can telepathically communicate with\n"
    "people. It changes its appearance using\n"
    "its down that refracts light.");

const u8 gLatiasPokedexTextUnused[] = _("");

const u8 gLatiosPokedexText[] = _(
    "It has a docile temperament and dislikes\n"
    "fighting. Tucking in its forelegs, it can\n"
    "fly faster than a jet plane.");

const u8 gLatiosPokedexTextUnused[] = _("");

const u8 gKyogrePokedexText[] = _(
    "This POKéMON is said to have expanded\n"
    "the sea by bringing heavy rains.\n"
    "It has the power to control water.");

const u8 gKyogrePokedexTextUnused[] = _("");

const u8 gGroudonPokedexText[] = _(
    "This legendary POKéMON is said to\n"
    "represent the land. It went to sleep after\n"
    "dueling KYOGRE.");

const u8 gGroudonPokedexTextUnused[] = _("");

const u8 gRayquazaPokedexText[] = _(
    "It has lived for hundreds of millions of\n"
    "years in the ozone layer. Its flying form\n"
    "looks like a meteor.");

const u8 gRayquazaPokedexTextUnused[] = _("");

const u8 gJirachiPokedexText[] = _(
    "It is said to make any wish come true.\n"
    "It is awake for only seven days out of\n"
    "a thousand years.");

const u8 gJirachiPokedexTextUnused[] = _("");

const u8 gDeoxysPokedexText[] = _(
    "When it changes form, an aurora appears.\n"
    "It absorbs attacks by altering its\n"
    "cellular structure.");

const u8 gDeoxysPokedexTextUnused[] = _("");
// ===== END src/data/pokemon/pokedex_text_lg.h =====
#endif
// ===== END src/data/pokemon/pokedex_text.h =====
// ===== BEGIN src/data/pokemon/pokedex_entries.h =====
const struct PokedexEntry gPokedexEntries[] =
{
    [NATIONAL_DEX_NONE] =
    {
        .categoryName = _("UNKNOWN"),
        .height = 0,
        .weight = 0,
        .description = gDummyPokedexText,
        .unusedDescription = gDummyPokedexTextUnused,
        .pokemonScale = 256,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
    },

    [NATIONAL_DEX_BULBASAUR] =
    {
        .categoryName = _("SEED"),
        .height = 7,
        .weight = 69,
        .description = gBulbasaurPokedexText,
        .unusedDescription = gBulbasaurPokedexTextUnused,
        .pokemonScale = 356,
        .pokemonOffset = 16,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_IVYSAUR] =
    {
        .categoryName = _("SEED"),
        .height = 10,
        .weight = 130,
        .description = gIvysaurPokedexText,
        .unusedDescription = gIvysaurPokedexTextUnused,
        .pokemonScale = 332,
        .pokemonOffset = 11,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_VENUSAUR] =
    {
        .categoryName = _("SEED"),
        .height = 20,
        .weight = 1000,
        .description = gVenusaurPokedexText,
        .unusedDescription = gVenusaurPokedexTextUnused,
        .pokemonScale = 256,
        .pokemonOffset = 1,
        .trainerScale = 375,
        .trainerOffset = 6,
    },

    [NATIONAL_DEX_CHARMANDER] =
    {
        .categoryName = _("LIZARD"),
        .height = 6,
        .weight = 85,
        .description = gCharmanderPokedexText,
        .unusedDescription = gCharmanderPokedexTextUnused,
        .pokemonScale = 410,
        .pokemonOffset = 16,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_CHARMELEON] =
    {
        .categoryName = _("FLAME"),
        .height = 11,
        .weight = 190,
        .description = gCharmeleonPokedexText,
        .unusedDescription = gCharmeleonPokedexTextUnused,
        .pokemonScale = 294,
        .pokemonOffset = 8,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_CHARIZARD] =
    {
        .categoryName = _("FLAME"),
        .height = 17,
        .weight = 905,
        .description = gCharizardPokedexText,
        .unusedDescription = gCharizardPokedexTextUnused,
        .pokemonScale = 271,
        .pokemonOffset = 0,
        .trainerScale = 317,
        .trainerOffset = 3,
    },

    [NATIONAL_DEX_SQUIRTLE] =
    {
        .categoryName = _("TINY TURTLE"),
        .height = 5,
        .weight = 90,
        .description = gSquirtlePokedexText,
        .unusedDescription = gSquirtlePokedexTextUnused,
        .pokemonScale = 412,
        .pokemonOffset = 16,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_WARTORTLE] =
    {
        .categoryName = _("TURTLE"),
        .height = 10,
        .weight = 225,
        .description = gWartortlePokedexText,
        .unusedDescription = gWartortlePokedexTextUnused,
        .pokemonScale = 334,
        .pokemonOffset = 9,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_BLASTOISE] =
    {
        .categoryName = _("SHELLFISH"),
        .height = 16,
        .weight = 855,
        .description = gBlastoisePokedexText,
        .unusedDescription = gBlastoisePokedexTextUnused,
        .pokemonScale = 256,
        .pokemonOffset = 1,
        .trainerScale = 329,
        .trainerOffset = 3,
    },

    [NATIONAL_DEX_CATERPIE] =
    {
        .categoryName = _("WORM"),
        .height = 3,
        .weight = 29,
        .description = gCaterpiePokedexText,
        .unusedDescription = gCaterpiePokedexTextUnused,
        .pokemonScale = 549,
        .pokemonOffset = 20,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_METAPOD] =
    {
        .categoryName = _("COCOON"),
        .height = 7,
        .weight = 99,
        .description = gMetapodPokedexText,
        .unusedDescription = gMetapodPokedexTextUnused,
        .pokemonScale = 350,
        .pokemonOffset = 18,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_BUTTERFREE] =
    {
        .categoryName = _("BUTTERFLY"),
        .height = 11,
        .weight = 320,
        .description = gButterfreePokedexText,
        .unusedDescription = gButterfreePokedexTextUnused,
        .pokemonScale = 312,
        .pokemonOffset = 2,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_WEEDLE] =
    {
        .categoryName = _("HAIRY BUG"),
        .height = 3,
        .weight = 32,
        .description = gWeedlePokedexText,
        .unusedDescription = gWeedlePokedexTextUnused,
        .pokemonScale = 455,
        .pokemonOffset = 19,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_KAKUNA] =
    {
        .categoryName = _("COCOON"),
        .height = 6,
        .weight = 100,
        .description = gKakunaPokedexText,
        .unusedDescription = gKakunaPokedexTextUnused,
        .pokemonScale = 424,
        .pokemonOffset = 14,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_BEEDRILL] =
    {
        .categoryName = _("POISON BEE"),
        .height = 10,
        .weight = 295,
        .description = gBeedrillPokedexText,
        .unusedDescription = gBeedrillPokedexTextUnused,
        .pokemonScale = 366,
        .pokemonOffset = 2,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_PIDGEY] =
    {
        .categoryName = _("TINY BIRD"),
        .height = 3,
        .weight = 18,
        .description = gPidgeyPokedexText,
        .unusedDescription = gPidgeyPokedexTextUnused,
        .pokemonScale = 492,
        .pokemonOffset = 18,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_PIDGEOTTO] =
    {
        .categoryName = _("BIRD"),
        .height = 11,
        .weight = 300,
        .description = gPidgeottoPokedexText,
        .unusedDescription = gPidgeottoPokedexTextUnused,
        .pokemonScale = 334,
        .pokemonOffset = 11,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_PIDGEOT] =
    {
        .categoryName = _("BIRD"),
        .height = 15,
        .weight = 395,
        .description = gPidgeotPokedexText,
        .unusedDescription = gPidgeotPokedexTextUnused,
        .pokemonScale = 269,
        .pokemonOffset = -2,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_RATTATA] =
    {
        .categoryName = _("MOUSE"),
        .height = 3,
        .weight = 35,
        .description = gRattataPokedexText,
        .unusedDescription = gRattataPokedexTextUnused,
        .pokemonScale = 481,
        .pokemonOffset = 18,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_RATICATE] =
    {
        .categoryName = _("MOUSE"),
        .height = 7,
        .weight = 185,
        .description = gRaticatePokedexText,
        .unusedDescription = gRaticatePokedexTextUnused,
        .pokemonScale = 401,
        .pokemonOffset = 14,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_SPEAROW] =
    {
        .categoryName = _("TINY BIRD"),
        .height = 3,
        .weight = 20,
        .description = gSpearowPokedexText,
        .unusedDescription = gSpearowPokedexTextUnused,
        .pokemonScale = 571,
        .pokemonOffset = 19,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_FEAROW] =
    {
        .categoryName = _("BEAK"),
        .height = 12,
        .weight = 380,
        .description = gFearowPokedexText,
        .unusedDescription = gFearowPokedexTextUnused,
        .pokemonScale = 282,
        .pokemonOffset = -1,
        .trainerScale = 272,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_EKANS] =
    {
        .categoryName = _("SNAKE"),
        .height = 20,
        .weight = 69,
        .description = gEkansPokedexText,
        .unusedDescription = gEkansPokedexTextUnused,
        .pokemonScale = 298,
        .pokemonOffset = 13,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_ARBOK] =
    {
        .categoryName = _("COBRA"),
        .height = 35,
        .weight = 650,
        .description = gArbokPokedexText,
        .unusedDescription = gArbokPokedexTextUnused,
        .pokemonScale = 256,
        .pokemonOffset = 0,
        .trainerScale = 296,
        .trainerOffset = 1,
    },

    [NATIONAL_DEX_PIKACHU] =
    {
        .categoryName = _("MOUSE"),
        .height = 4,
        .weight = 60,
        .description = gPikachuPokedexText,
        .unusedDescription = gPikachuPokedexTextUnused,
        .pokemonScale = 479,
        .pokemonOffset = 16,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_RAICHU] =
    {
        .categoryName = _("MOUSE"),
        .height = 8,
        .weight = 300,
        .description = gRaichuPokedexText,
        .unusedDescription = gRaichuPokedexTextUnused,
        .pokemonScale = 426,
        .pokemonOffset = 10,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_SANDSHREW] =
    {
        .categoryName = _("MOUSE"),
        .height = 6,
        .weight = 120,
        .description = gSandshrewPokedexText,
        .unusedDescription = gSandshrewPokedexTextUnused,
        .pokemonScale = 370,
        .pokemonOffset = 15,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_SANDSLASH] =
    {
        .categoryName = _("MOUSE"),
        .height = 10,
        .weight = 295,
        .description = gSandslashPokedexText,
        .unusedDescription = gSandslashPokedexTextUnused,
        .pokemonScale = 341,
        .pokemonOffset = 10,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_NIDORAN_F] =
    {
        .categoryName = _("POISON PIN"),
        .height = 4,
        .weight = 70,
        .description = gNidoranFPokedexText,
        .unusedDescription = gNidoranFPokedexTextUnused,
        .pokemonScale = 488,
        .pokemonOffset = 19,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_NIDORINA] =
    {
        .categoryName = _("POISON PIN"),
        .height = 8,
        .weight = 200,
        .description = gNidorinaPokedexText,
        .unusedDescription = gNidorinaPokedexTextUnused,
        .pokemonScale = 381,
        .pokemonOffset = 13,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_NIDOQUEEN] =
    {
        .categoryName = _("DRILL"),
        .height = 13,
        .weight = 600,
        .description = gNidoqueenPokedexText,
        .unusedDescription = gNidoqueenPokedexTextUnused,
        .pokemonScale = 283,
        .pokemonOffset = 2,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_NIDORAN_M] =
    {
        .categoryName = _("POISON PIN"),
        .height = 5,
        .weight = 90,
        .description = gNidoranMPokedexText,
        .unusedDescription = gNidoranMPokedexTextUnused,
        .pokemonScale = 480,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_NIDORINO] =
    {
        .categoryName = _("POISON PIN"),
        .height = 9,
        .weight = 195,
        .description = gNidorinoPokedexText,
        .unusedDescription = gNidorinoPokedexTextUnused,
        .pokemonScale = 408,
        .pokemonOffset = 13,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_NIDOKING] =
    {
        .categoryName = _("DRILL"),
        .height = 14,
        .weight = 620,
        .description = gNidokingPokedexText,
        .unusedDescription = gNidokingPokedexTextUnused,
        .pokemonScale = 304,
        .pokemonOffset = 3,
        .trainerScale = 323,
        .trainerOffset = 2,
    },

    [NATIONAL_DEX_CLEFAIRY] =
    {
        .categoryName = _("FAIRY"),
        .height = 6,
        .weight = 75,
        .description = gClefairyPokedexText,
        .unusedDescription = gClefairyPokedexTextUnused,
        .pokemonScale = 425,
        .pokemonOffset = 18,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_CLEFABLE] =
    {
        .categoryName = _("FAIRY"),
        .height = 13,
        .weight = 400,
        .description = gClefablePokedexText,
        .unusedDescription = gClefablePokedexTextUnused,
        .pokemonScale = 256,
        .pokemonOffset = 3,
        .trainerScale = 272,
        .trainerOffset = -1,
    },

    [NATIONAL_DEX_VULPIX] =
    {
        .categoryName = _("FOX"),
        .height = 6,
        .weight = 99,
        .description = gVulpixPokedexText,
        .unusedDescription = gVulpixPokedexTextUnused,
        .pokemonScale = 497,
        .pokemonOffset = 18,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_NINETALES] =
    {
        .categoryName = _("FOX"),
        .height = 11,
        .weight = 199,
        .description = gNinetalesPokedexText,
        .unusedDescription = gNinetalesPokedexTextUnused,
        .pokemonScale = 339,
        .pokemonOffset = 6,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_JIGGLYPUFF] =
    {
        .categoryName = _("BALLOON"),
        .height = 5,
        .weight = 55,
        .description = gJigglypuffPokedexText,
        .unusedDescription = gJigglypuffPokedexTextUnused,
        .pokemonScale = 419,
        .pokemonOffset = 19,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_WIGGLYTUFF] =
    {
        .categoryName = _("BALLOON"),
        .height = 10,
        .weight = 120,
        .description = gWigglytuffPokedexText,
        .unusedDescription = gWigglytuffPokedexTextUnused,
        .pokemonScale = 328,
        .pokemonOffset = 9,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_ZUBAT] =
    {
        .categoryName = _("BAT"),
        .height = 8,
        .weight = 75,
        .description = gZubatPokedexText,
        .unusedDescription = gZubatPokedexTextUnused,
        .pokemonScale = 355,
        .pokemonOffset = -4,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_GOLBAT] =
    {
        .categoryName = _("BAT"),
        .height = 16,
        .weight = 550,
        .description = gGolbatPokedexText,
        .unusedDescription = gGolbatPokedexTextUnused,
        .pokemonScale = 291,
        .pokemonOffset = 0,
        .trainerScale = 296,
        .trainerOffset = 2,
    },

    [NATIONAL_DEX_ODDISH] =
    {
        .categoryName = _("WEED"),
        .height = 5,
        .weight = 54,
        .description = gOddishPokedexText,
        .unusedDescription = gOddishPokedexTextUnused,
        .pokemonScale = 423,
        .pokemonOffset = 15,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_GLOOM] =
    {
        .categoryName = _("WEED"),
        .height = 8,
        .weight = 86,
        .description = gGloomPokedexText,
        .unusedDescription = gGloomPokedexTextUnused,
        .pokemonScale = 329,
        .pokemonOffset = 10,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_VILEPLUME] =
    {
        .categoryName = _("FLOWER"),
        .height = 12,
        .weight = 186,
        .description = gVileplumePokedexText,
        .unusedDescription = gVileplumePokedexTextUnused,
        .pokemonScale = 256,
        .pokemonOffset = 4,
        .trainerScale = 272,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_PARAS] =
    {
        .categoryName = _("MUSHROOM"),
        .height = 3,
        .weight = 54,
        .description = gParasPokedexText,
        .unusedDescription = gParasPokedexTextUnused,
        .pokemonScale = 546,
        .pokemonOffset = 21,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_PARASECT] =
    {
        .categoryName = _("MUSHROOM"),
        .height = 10,
        .weight = 295,
        .description = gParasectPokedexText,
        .unusedDescription = gParasectPokedexTextUnused,
        .pokemonScale = 307,
        .pokemonOffset = 8,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_VENONAT] =
    {
        .categoryName = _("INSECT"),
        .height = 10,
        .weight = 300,
        .description = gVenonatPokedexText,
        .unusedDescription = gVenonatPokedexTextUnused,
        .pokemonScale = 360,
        .pokemonOffset = 14,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_VENOMOTH] =
    {
        .categoryName = _("POISON MOTH"),
        .height = 15,
        .weight = 125,
        .description = gVenomothPokedexText,
        .unusedDescription = gVenomothPokedexTextUnused,
        .pokemonScale = 256,
        .pokemonOffset = 3,
        .trainerScale = 293,
        .trainerOffset = 1,
    },

    [NATIONAL_DEX_DIGLETT] =
    {
        .categoryName = _("MOLE"),
        .height = 2,
        .weight = 8,
        .description = gDiglettPokedexText,
        .unusedDescription = gDiglettPokedexTextUnused,
        .pokemonScale = 706,
        .pokemonOffset = 22,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_DUGTRIO] =
    {
        .categoryName = _("MOLE"),
        .height = 7,
        .weight = 333,
        .description = gDugtrioPokedexText,
        .unusedDescription = gDugtrioPokedexTextUnused,
        .pokemonScale = 384,
        .pokemonOffset = 14,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_MEOWTH] =
    {
        .categoryName = _("SCRATCH CAT"),
        .height = 4,
        .weight = 42,
        .description = gMeowthPokedexText,
        .unusedDescription = gMeowthPokedexTextUnused,
        .pokemonScale = 480,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_PERSIAN] =
    {
        .categoryName = _("CLASSY CAT"),
        .height = 10,
        .weight = 320,
        .description = gPersianPokedexText,
        .unusedDescription = gPersianPokedexTextUnused,
        .pokemonScale = 320,
        .pokemonOffset = 10,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_PSYDUCK] =
    {
        .categoryName = _("DUCK"),
        .height = 8,
        .weight = 196,
        .description = gPsyduckPokedexText,
        .unusedDescription = gPsyduckPokedexTextUnused,
        .pokemonScale = 347,
        .pokemonOffset = 11,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_GOLDUCK] =
    {
        .categoryName = _("DUCK"),
        .height = 17,
        .weight = 766,
        .description = gGolduckPokedexText,
        .unusedDescription = gGolduckPokedexTextUnused,
        .pokemonScale = 272,
        .pokemonOffset = 4,
        .trainerScale = 287,
        .trainerOffset = 1,
    },

    [NATIONAL_DEX_MANKEY] =
    {
        .categoryName = _("PIG MONKEY"),
        .height = 5,
        .weight = 280,
        .description = gMankeyPokedexText,
        .unusedDescription = gMankeyPokedexTextUnused,
        .pokemonScale = 388,
        .pokemonOffset = 16,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_PRIMEAPE] =
    {
        .categoryName = _("PIG MONKEY"),
        .height = 10,
        .weight = 320,
        .description = gPrimeapePokedexText,
        .unusedDescription = gPrimeapePokedexTextUnused,
        .pokemonScale = 326,
        .pokemonOffset = 8,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_GROWLITHE] =
    {
        .categoryName = _("PUPPY"),
        .height = 7,
        .weight = 190,
        .description = gGrowlithePokedexText,
        .unusedDescription = gGrowlithePokedexTextUnused,
        .pokemonScale = 346,
        .pokemonOffset = 14,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_ARCANINE] =
    {
        .categoryName = _("LEGENDARY"),
        .height = 19,
        .weight = 1550,
        .description = gArcaninePokedexText,
        .unusedDescription = gArcaninePokedexTextUnused,
        .pokemonScale = 256,
        .pokemonOffset = -1,
        .trainerScale = 312,
        .trainerOffset = 2,
    },

    [NATIONAL_DEX_POLIWAG] =
    {
        .categoryName = _("TADPOLE"),
        .height = 6,
        .weight = 124,
        .description = gPoliwagPokedexText,
        .unusedDescription = gPoliwagPokedexTextUnused,
        .pokemonScale = 353,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_POLIWHIRL] =
    {
        .categoryName = _("TADPOLE"),
        .height = 10,
        .weight = 200,
        .description = gPoliwhirlPokedexText,
        .unusedDescription = gPoliwhirlPokedexTextUnused,
        .pokemonScale = 288,
        .pokemonOffset = 10,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_POLIWRATH] =
    {
        .categoryName = _("TADPOLE"),
        .height = 13,
        .weight = 540,
        .description = gPoliwrathPokedexText,
        .unusedDescription = gPoliwrathPokedexTextUnused,
        .pokemonScale = 256,
        .pokemonOffset = 5,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_ABRA] =
    {
        .categoryName = _("PSI"),
        .height = 9,
        .weight = 195,
        .description = gAbraPokedexText,
        .unusedDescription = gAbraPokedexTextUnused,
        .pokemonScale = 374,
        .pokemonOffset = 14,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_KADABRA] =
    {
        .categoryName = _("PSI"),
        .height = 13,
        .weight = 565,
        .description = gKadabraPokedexText,
        .unusedDescription = gKadabraPokedexTextUnused,
        .pokemonScale = 272,
        .pokemonOffset = 2,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_ALAKAZAM] =
    {
        .categoryName = _("PSI"),
        .height = 15,
        .weight = 480,
        .description = gAlakazamPokedexText,
        .unusedDescription = gAlakazamPokedexTextUnused,
        .pokemonScale = 272,
        .pokemonOffset = -1,
        .trainerScale = 271,
        .trainerOffset = -1,
    },

    [NATIONAL_DEX_MACHOP] =
    {
        .categoryName = _("SUPERPOWER"),
        .height = 8,
        .weight = 195,
        .description = gMachopPokedexText,
        .unusedDescription = gMachopPokedexTextUnused,
        .pokemonScale = 320,
        .pokemonOffset = 12,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_MACHOKE] =
    {
        .categoryName = _("SUPERPOWER"),
        .height = 15,
        .weight = 705,
        .description = gMachokePokedexText,
        .unusedDescription = gMachokePokedexTextUnused,
        .pokemonScale = 304,
        .pokemonOffset = 6,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_MACHAMP] =
    {
        .categoryName = _("SUPERPOWER"),
        .height = 16,
        .weight = 1300,
        .description = gMachampPokedexText,
        .unusedDescription = gMachampPokedexTextUnused,
        .pokemonScale = 278,
        .pokemonOffset = 2,
        .trainerScale = 283,
        .trainerOffset = 0,
    },

    [NATIONAL_DEX_BELLSPROUT] =
    {
        .categoryName = _("FLOWER"),
        .height = 7,
        .weight = 40,
        .description = gBellsproutPokedexText,
        .unusedDescription = gBellsproutPokedexTextUnused,
        .pokemonScale = 354,
        .pokemonOffset = 16,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_WEEPINBELL] =
    {
        .categoryName = _("FLYCATCHER"),
        .height = 10,
        .weight = 64,
        .description = gWeepinbellPokedexText,
        .unusedDescription = gWeepinbellPokedexTextUnused,
        .pokemonScale = 256,
        .pokemonOffset = -1,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_VICTREEBEL] =
    {
        .categoryName = _("FLYCATCHER"),
        .height = 17,
        .weight = 155,
        .description = gVictreebelPokedexText,
        .unusedDescription = gVictreebelPokedexTextUnused,
        .pokemonScale = 256,
        .pokemonOffset = 2,
        .trainerScale = 302,
        .trainerOffset = 2,
    },

    [NATIONAL_DEX_TENTACOOL] =
    {
        .categoryName = _("JELLYFISH"),
        .height = 9,
        .weight = 455,
        .description = gTentacoolPokedexText,
        .unusedDescription = gTentacoolPokedexTextUnused,
        .pokemonScale = 256,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_TENTACRUEL] =
    {
        .categoryName = _("JELLYFISH"),
        .height = 16,
        .weight = 550,
        .description = gTentacruelPokedexText,
        .unusedDescription = gTentacruelPokedexTextUnused,
        .pokemonScale = 272,
        .pokemonOffset = -1,
        .trainerScale = 312,
        .trainerOffset = 0,
    },

    [NATIONAL_DEX_GEODUDE] =
    {
        .categoryName = _("ROCK"),
        .height = 4,
        .weight = 200,
        .description = gGeodudePokedexText,
        .unusedDescription = gGeodudePokedexTextUnused,
        .pokemonScale = 330,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_GRAVELER] =
    {
        .categoryName = _("ROCK"),
        .height = 10,
        .weight = 1050,
        .description = gGravelerPokedexText,
        .unusedDescription = gGravelerPokedexTextUnused,
        .pokemonScale = 272,
        .pokemonOffset = 8,
        .trainerScale = 305,
        .trainerOffset = 1,
    },

    [NATIONAL_DEX_GOLEM] =
    {
        .categoryName = _("MEGATON"),
        .height = 14,
        .weight = 3000,
        .description = gGolemPokedexText,
        .unusedDescription = gGolemPokedexTextUnused,
        .pokemonScale = 266,
        .pokemonOffset = 3,
        .trainerScale = 298,
        .trainerOffset = 1,
    },

    [NATIONAL_DEX_PONYTA] =
    {
        .categoryName = _("FIRE HORSE"),
        .height = 10,
        .weight = 300,
        .description = gPonytaPokedexText,
        .unusedDescription = gPonytaPokedexTextUnused,
        .pokemonScale = 288,
        .pokemonOffset = 7,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_RAPIDASH] =
    {
        .categoryName = _("FIRE HORSE"),
        .height = 17,
        .weight = 950,
        .description = gRapidashPokedexText,
        .unusedDescription = gRapidashPokedexTextUnused,
        .pokemonScale = 282,
        .pokemonOffset = -1,
        .trainerScale = 312,
        .trainerOffset = 1,
    },

    [NATIONAL_DEX_SLOWPOKE] =
    {
        .categoryName = _("DOPEY"),
        .height = 12,
        .weight = 360,
        .description = gSlowpokePokedexText,
        .unusedDescription = gSlowpokePokedexTextUnused,
        .pokemonScale = 271,
        .pokemonOffset = 10,
        .trainerScale = 272,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_SLOWBRO] =
    {
        .categoryName = _("HERMIT CRAB"),
        .height = 16,
        .weight = 785,
        .description = gSlowbroPokedexText,
        .unusedDescription = gSlowbroPokedexTextUnused,
        .pokemonScale = 257,
        .pokemonOffset = -2,
        .trainerScale = 312,
        .trainerOffset = 0,
    },

    [NATIONAL_DEX_MAGNEMITE] =
    {
        .categoryName = _("MAGNET"),
        .height = 3,
        .weight = 60,
        .description = gMagnemitePokedexText,
        .unusedDescription = gMagnemitePokedexTextUnused,
        .pokemonScale = 294,
        .pokemonOffset = -8,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_MAGNETON] =
    {
        .categoryName = _("MAGNET"),
        .height = 10,
        .weight = 600,
        .description = gMagnetonPokedexText,
        .unusedDescription = gMagnetonPokedexTextUnused,
        .pokemonScale = 293,
        .pokemonOffset = -4,
        .trainerScale = 273,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_FARFETCHD] =
    {
        .categoryName = _("WILD DUCK"),
        .height = 8,
        .weight = 150,
        .description = gFarfetchdPokedexText,
        .unusedDescription = gFarfetchdPokedexTextUnused,
        .pokemonScale = 317,
        .pokemonOffset = -2,
        .trainerScale = 256,
        .trainerOffset = -3,
    },

    [NATIONAL_DEX_DODUO] =
    {
        .categoryName = _("TWIN BIRD"),
        .height = 14,
        .weight = 392,
        .description = gDoduoPokedexText,
        .unusedDescription = gDoduoPokedexTextUnused,
        .pokemonScale = 256,
        .pokemonOffset = 3,
        .trainerScale = 287,
        .trainerOffset = 0,
    },

    [NATIONAL_DEX_DODRIO] =
    {
        .categoryName = _("TRIPLE BIRD"),
        .height = 18,
        .weight = 852,
        .description = gDodrioPokedexText,
        .unusedDescription = gDodrioPokedexTextUnused,
        .pokemonScale = 272,
        .pokemonOffset = -2,
        .trainerScale = 296,
        .trainerOffset = 1,
    },

    [NATIONAL_DEX_SEEL] =
    {
        .categoryName = _("SEA LION"),
        .height = 11,
        .weight = 900,
        .description = gSeelPokedexText,
        .unusedDescription = gSeelPokedexTextUnused,
        .pokemonScale = 298,
        .pokemonOffset = 8,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_DEWGONG] =
    {
        .categoryName = _("SEA LION"),
        .height = 17,
        .weight = 1200,
        .description = gDewgongPokedexText,
        .unusedDescription = gDewgongPokedexTextUnused,
        .pokemonScale = 288,
        .pokemonOffset = 1,
        .trainerScale = 306,
        .trainerOffset = -1,
    },

    [NATIONAL_DEX_GRIMER] =
    {
        .categoryName = _("SLUDGE"),
        .height = 9,
        .weight = 300,
        .description = gGrimerPokedexText,
        .unusedDescription = gGrimerPokedexTextUnused,
        .pokemonScale = 258,
        .pokemonOffset = 8,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_MUK] =
    {
        .categoryName = _("SLUDGE"),
        .height = 12,
        .weight = 300,
        .description = gMukPokedexText,
        .unusedDescription = gMukPokedexTextUnused,
        .pokemonScale = 288,
        .pokemonOffset = 7,
        .trainerScale = 288,
        .trainerOffset = -1,
    },

    [NATIONAL_DEX_SHELLDER] =
    {
        .categoryName = _("BIVALVE"),
        .height = 3,
        .weight = 40,
        .description = gShellderPokedexText,
        .unusedDescription = gShellderPokedexTextUnused,
        .pokemonScale = 643,
        .pokemonOffset = 21,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_CLOYSTER] =
    {
        .categoryName = _("BIVALVE"),
        .height = 15,
        .weight = 1325,
        .description = gCloysterPokedexText,
        .unusedDescription = gCloysterPokedexTextUnused,
        .pokemonScale = 264,
        .pokemonOffset = 0,
        .trainerScale = 288,
        .trainerOffset = -1,
    },

    [NATIONAL_DEX_GASTLY] =
    {
        .categoryName = _("GAS"),
        .height = 13,
        .weight = 1,
        .description = gGastlyPokedexText,
        .unusedDescription = gGastlyPokedexTextUnused,
        .pokemonScale = 256,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_HAUNTER] =
    {
        .categoryName = _("GAS"),
        .height = 16,
        .weight = 1,
        .description = gHaunterPokedexText,
        .unusedDescription = gHaunterPokedexTextUnused,
        .pokemonScale = 269,
        .pokemonOffset = 2,
        .trainerScale = 308,
        .trainerOffset = 1,
    },

    [NATIONAL_DEX_GENGAR] =
    {
        .categoryName = _("SHADOW"),
        .height = 15,
        .weight = 405,
        .description = gGengarPokedexText,
        .unusedDescription = gGengarPokedexTextUnused,
        .pokemonScale = 256,
        .pokemonOffset = 4,
        .trainerScale = 317,
        .trainerOffset = 1,
    },

    [NATIONAL_DEX_ONIX] =
    {
        .categoryName = _("ROCK SNAKE"),
        .height = 88,
        .weight = 2100,
        .description = gOnixPokedexText,
        .unusedDescription = gOnixPokedexTextUnused,
        .pokemonScale = 257,
        .pokemonOffset = 0,
        .trainerScale = 515,
        .trainerOffset = 12,
    },

    [NATIONAL_DEX_DROWZEE] =
    {
        .categoryName = _("HYPNOSIS"),
        .height = 10,
        .weight = 324,
        .description = gDrowzeePokedexText,
        .unusedDescription = gDrowzeePokedexTextUnused,
        .pokemonScale = 274,
        .pokemonOffset = 7,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_HYPNO] =
    {
        .categoryName = _("HYPNOSIS"),
        .height = 16,
        .weight = 756,
        .description = gHypnoPokedexText,
        .unusedDescription = gHypnoPokedexTextUnused,
        .pokemonScale = 298,
        .pokemonOffset = 3,
        .trainerScale = 310,
        .trainerOffset = 2,
    },

    [NATIONAL_DEX_KRABBY] =
    {
        .categoryName = _("RIVER CRAB"),
        .height = 4,
        .weight = 65,
        .description = gKrabbyPokedexText,
        .unusedDescription = gKrabbyPokedexTextUnused,
        .pokemonScale = 469,
        .pokemonOffset = 18,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_KINGLER] =
    {
        .categoryName = _("PINCER"),
        .height = 13,
        .weight = 600,
        .description = gKinglerPokedexText,
        .unusedDescription = gKinglerPokedexTextUnused,
        .pokemonScale = 287,
        .pokemonOffset = 3,
        .trainerScale = 308,
        .trainerOffset = 1,
    },

    [NATIONAL_DEX_VOLTORB] =
    {
        .categoryName = _("BALL"),
        .height = 5,
        .weight = 104,
        .description = gVoltorbPokedexText,
        .unusedDescription = gVoltorbPokedexTextUnused,
        .pokemonScale = 364,
        .pokemonOffset = -8,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_ELECTRODE] =
    {
        .categoryName = _("BALL"),
        .height = 12,
        .weight = 666,
        .description = gElectrodePokedexText,
        .unusedDescription = gElectrodePokedexTextUnused,
        .pokemonScale = 256,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_EXEGGCUTE] =
    {
        .categoryName = _("EGG"),
        .height = 4,
        .weight = 25,
        .description = gExeggcutePokedexText,
        .unusedDescription = gExeggcutePokedexTextUnused,
        .pokemonScale = 495,
        .pokemonOffset = -4,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_EXEGGUTOR] =
    {
        .categoryName = _("COCONUT"),
        .height = 20,
        .weight = 1200,
        .description = gExeggutorPokedexText,
        .unusedDescription = gExeggutorPokedexTextUnused,
        .pokemonScale = 283,
        .pokemonOffset = 0,
        .trainerScale = 376,
        .trainerOffset = 7,
    },

    [NATIONAL_DEX_CUBONE] =
    {
        .categoryName = _("LONELY"),
        .height = 4,
        .weight = 65,
        .description = gCubonePokedexText,
        .unusedDescription = gCubonePokedexTextUnused,
        .pokemonScale = 545,
        .pokemonOffset = 19,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_MAROWAK] =
    {
        .categoryName = _("BONE KEEPER"),
        .height = 10,
        .weight = 450,
        .description = gMarowakPokedexText,
        .unusedDescription = gMarowakPokedexTextUnused,
        .pokemonScale = 293,
        .pokemonOffset = 12,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_HITMONLEE] =
    {
        .categoryName = _("KICKING"),
        .height = 15,
        .weight = 498,
        .description = gHitmonleePokedexText,
        .unusedDescription = gHitmonleePokedexTextUnused,
        .pokemonScale = 256,
        .pokemonOffset = 0,
        .trainerScale = 273,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_HITMONCHAN] =
    {
        .categoryName = _("PUNCHING"),
        .height = 14,
        .weight = 502,
        .description = gHitmonchanPokedexText,
        .unusedDescription = gHitmonchanPokedexTextUnused,
        .pokemonScale = 256,
        .pokemonOffset = 1,
        .trainerScale = 264,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_LICKITUNG] =
    {
        .categoryName = _("LICKING"),
        .height = 12,
        .weight = 655,
        .description = gLickitungPokedexText,
        .unusedDescription = gLickitungPokedexTextUnused,
        .pokemonScale = 272,
        .pokemonOffset = 3,
        .trainerScale = 272,
        .trainerOffset = -3,
    },

    [NATIONAL_DEX_KOFFING] =
    {
        .categoryName = _("POISON GAS"),
        .height = 6,
        .weight = 10,
        .description = gKoffingPokedexText,
        .unusedDescription = gKoffingPokedexTextUnused,
        .pokemonScale = 369,
        .pokemonOffset = -1,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_WEEZING] =
    {
        .categoryName = _("POISON GAS"),
        .height = 12,
        .weight = 95,
        .description = gWeezingPokedexText,
        .unusedDescription = gWeezingPokedexTextUnused,
        .pokemonScale = 321,
        .pokemonOffset = -1,
        .trainerScale = 276,
        .trainerOffset = -1,
    },

    [NATIONAL_DEX_RHYHORN] =
    {
        .categoryName = _("SPIKES"),
        .height = 10,
        .weight = 1150,
        .description = gRhyhornPokedexText,
        .unusedDescription = gRhyhornPokedexTextUnused,
        .pokemonScale = 291,
        .pokemonOffset = 7,
        .trainerScale = 276,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_RHYDON] =
    {
        .categoryName = _("DRILL"),
        .height = 19,
        .weight = 1200,
        .description = gRhydonPokedexText,
        .unusedDescription = gRhydonPokedexTextUnused,
        .pokemonScale = 272,
        .pokemonOffset = -1,
        .trainerScale = 344,
        .trainerOffset = 3,
    },

    [NATIONAL_DEX_CHANSEY] =
    {
        .categoryName = _("EGG"),
        .height = 11,
        .weight = 346,
        .description = gChanseyPokedexText,
        .unusedDescription = gChanseyPokedexTextUnused,
        .pokemonScale = 257,
        .pokemonOffset = 6,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_TANGELA] =
    {
        .categoryName = _("VINE"),
        .height = 10,
        .weight = 350,
        .description = gTangelaPokedexText,
        .unusedDescription = gTangelaPokedexTextUnused,
        .pokemonScale = 320,
        .pokemonOffset = 9,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_KANGASKHAN] =
    {
        .categoryName = _("PARENT"),
        .height = 22,
        .weight = 800,
        .description = gKangaskhanPokedexText,
        .unusedDescription = gKangaskhanPokedexTextUnused,
        .pokemonScale = 257,
        .pokemonOffset = -3,
        .trainerScale = 349,
        .trainerOffset = 5,
    },

    [NATIONAL_DEX_HORSEA] =
    {
        .categoryName = _("DRAGON"),
        .height = 4,
        .weight = 80,
        .description = gHorseaPokedexText,
        .unusedDescription = gHorseaPokedexTextUnused,
        .pokemonScale = 399,
        .pokemonOffset = -1,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_SEADRA] =
    {
        .categoryName = _("DRAGON"),
        .height = 12,
        .weight = 250,
        .description = gSeadraPokedexText,
        .unusedDescription = gSeadraPokedexTextUnused,
        .pokemonScale = 296,
        .pokemonOffset = 3,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_GOLDEEN] =
    {
        .categoryName = _("GOLDFISH"),
        .height = 6,
        .weight = 150,
        .description = gGoldeenPokedexText,
        .unusedDescription = gGoldeenPokedexTextUnused,
        .pokemonScale = 379,
        .pokemonOffset = 4,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_SEAKING] =
    {
        .categoryName = _("GOLDFISH"),
        .height = 13,
        .weight = 390,
        .description = gSeakingPokedexText,
        .unusedDescription = gSeakingPokedexTextUnused,
        .pokemonScale = 304,
        .pokemonOffset = 1,
        .trainerScale = 288,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_STARYU] =
    {
        .categoryName = _("STAR SHAPE"),
        .height = 8,
        .weight = 345,
        .description = gStaryuPokedexText,
        .unusedDescription = gStaryuPokedexTextUnused,
        .pokemonScale = 326,
        .pokemonOffset = 1,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_STARMIE] =
    {
        .categoryName = _("MYSTERIOUS"),
        .height = 11,
        .weight = 800,
        .description = gStarmiePokedexText,
        .unusedDescription = gStarmiePokedexTextUnused,
        .pokemonScale = 301,
        .pokemonOffset = 3,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_MR_MIME] =
    {
        .categoryName = _("BARRIER"),
        .height = 13,
        .weight = 545,
        .description = gMrmimePokedexText,
        .unusedDescription = gMrmimePokedexTextUnused,
        .pokemonScale = 258,
        .pokemonOffset = 4,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_SCYTHER] =
    {
        .categoryName = _("MANTIS"),
        .height = 15,
        .weight = 560,
        .description = gScytherPokedexText,
        .unusedDescription = gScytherPokedexTextUnused,
        .pokemonScale = 272,
        .pokemonOffset = 0,
        .trainerScale = 293,
        .trainerOffset = 1,
    },

    [NATIONAL_DEX_JYNX] =
    {
        .categoryName = _("HUMAN SHAPE"),
        .height = 14,
        .weight = 406,
        .description = gJynxPokedexText,
        .unusedDescription = gJynxPokedexTextUnused,
        .pokemonScale = 256,
        .pokemonOffset = 3,
        .trainerScale = 300,
        .trainerOffset = 1,
    },

    [NATIONAL_DEX_ELECTABUZZ] =
    {
        .categoryName = _("ELECTRIC"),
        .height = 11,
        .weight = 300,
        .description = gElectabuzzPokedexText,
        .unusedDescription = gElectabuzzPokedexTextUnused,
        .pokemonScale = 330,
        .pokemonOffset = 7,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_MAGMAR] =
    {
        .categoryName = _("SPITFIRE"),
        .height = 13,
        .weight = 445,
        .description = gMagmarPokedexText,
        .unusedDescription = gMagmarPokedexTextUnused,
        .pokemonScale = 293,
        .pokemonOffset = 4,
        .trainerScale = 272,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_PINSIR] =
    {
        .categoryName = _("STAG BEETLE"),
        .height = 15,
        .weight = 550,
        .description = gPinsirPokedexText,
        .unusedDescription = gPinsirPokedexTextUnused,
        .pokemonScale = 256,
        .pokemonOffset = 1,
        .trainerScale = 257,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_TAUROS] =
    {
        .categoryName = _("WILD BULL"),
        .height = 14,
        .weight = 884,
        .description = gTaurosPokedexText,
        .unusedDescription = gTaurosPokedexTextUnused,
        .pokemonScale = 256,
        .pokemonOffset = 2,
        .trainerScale = 312,
        .trainerOffset = 3,
    },

    [NATIONAL_DEX_MAGIKARP] =
    {
        .categoryName = _("FISH"),
        .height = 9,
        .weight = 100,
        .description = gMagikarpPokedexText,
        .unusedDescription = gMagikarpPokedexTextUnused,
        .pokemonScale = 317,
        .pokemonOffset = 4,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_GYARADOS] =
    {
        .categoryName = _("ATROCIOUS"),
        .height = 65,
        .weight = 2350,
        .description = gGyaradosPokedexText,
        .unusedDescription = gGyaradosPokedexTextUnused,
        .pokemonScale = 288,
        .pokemonOffset = -1,
        .trainerScale = 512,
        .trainerOffset = 11,
    },

    [NATIONAL_DEX_LAPRAS] =
    {
        .categoryName = _("TRANSPORT"),
        .height = 25,
        .weight = 2200,
        .description = gLaprasPokedexText,
        .unusedDescription = gLaprasPokedexTextUnused,
        .pokemonScale = 256,
        .pokemonOffset = 0,
        .trainerScale = 425,
        .trainerOffset = 8,
    },

    [NATIONAL_DEX_DITTO] =
    {
        .categoryName = _("TRANSFORM"),
        .height = 3,
        .weight = 40,
        .description = gDittoPokedexText,
        .unusedDescription = gDittoPokedexTextUnused,
        .pokemonScale = 602,
        .pokemonOffset = 21,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_EEVEE] =
    {
        .categoryName = _("EVOLUTION"),
        .height = 3,
        .weight = 65,
        .description = gEeveePokedexText,
        .unusedDescription = gEeveePokedexTextUnused,
        .pokemonScale = 476,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_VAPOREON] =
    {
        .categoryName = _("BUBBLE JET"),
        .height = 10,
        .weight = 290,
        .description = gVaporeonPokedexText,
        .unusedDescription = gVaporeonPokedexTextUnused,
        .pokemonScale = 316,
        .pokemonOffset = 7,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_JOLTEON] =
    {
        .categoryName = _("LIGHTNING"),
        .height = 8,
        .weight = 245,
        .description = gJolteonPokedexText,
        .unusedDescription = gJolteonPokedexTextUnused,
        .pokemonScale = 283,
        .pokemonOffset = 8,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_FLAREON] =
    {
        .categoryName = _("FLAME"),
        .height = 9,
        .weight = 250,
        .description = gFlareonPokedexText,
        .unusedDescription = gFlareonPokedexTextUnused,
        .pokemonScale = 302,
        .pokemonOffset = 11,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_PORYGON] =
    {
        .categoryName = _("VIRTUAL"),
        .height = 8,
        .weight = 365,
        .description = gPorygonPokedexText,
        .unusedDescription = gPorygonPokedexTextUnused,
        .pokemonScale = 328,
        .pokemonOffset = 7,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_OMANYTE] =
    {
        .categoryName = _("SPIRAL"),
        .height = 4,
        .weight = 75,
        .description = gOmanytePokedexText,
        .unusedDescription = gOmanytePokedexTextUnused,
        .pokemonScale = 521,
        .pokemonOffset = 20,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_OMASTAR] =
    {
        .categoryName = _("SPIRAL"),
        .height = 10,
        .weight = 350,
        .description = gOmastarPokedexText,
        .unusedDescription = gOmastarPokedexTextUnused,
        .pokemonScale = 307,
        .pokemonOffset = 5,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_KABUTO] =
    {
        .categoryName = _("SHELLFISH"),
        .height = 5,
        .weight = 115,
        .description = gKabutoPokedexText,
        .unusedDescription = gKabutoPokedexTextUnused,
        .pokemonScale = 438,
        .pokemonOffset = 21,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_KABUTOPS] =
    {
        .categoryName = _("SHELLFISH"),
        .height = 13,
        .weight = 405,
        .description = gKabutopsPokedexText,
        .unusedDescription = gKabutopsPokedexTextUnused,
        .pokemonScale = 271,
        .pokemonOffset = 1,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_AERODACTYL] =
    {
        .categoryName = _("FOSSIL"),
        .height = 18,
        .weight = 590,
        .description = gAerodactylPokedexText,
        .unusedDescription = gAerodactylPokedexTextUnused,
        .pokemonScale = 275,
        .pokemonOffset = -1,
        .trainerScale = 317,
        .trainerOffset = 2,
    },

    [NATIONAL_DEX_SNORLAX] =
    {
        .categoryName = _("SLEEPING"),
        .height = 21,
        .weight = 4600,
        .description = gSnorlaxPokedexText,
        .unusedDescription = gSnorlaxPokedexTextUnused,
        .pokemonScale = 275,
        .pokemonOffset = 1,
        .trainerScale = 408,
        .trainerOffset = 7,
    },

    [NATIONAL_DEX_ARTICUNO] =
    {
        .categoryName = _("FREEZE"),
        .height = 17,
        .weight = 554,
        .description = gArticunoPokedexText,
        .unusedDescription = gArticunoPokedexTextUnused,
        .pokemonScale = 278,
        .pokemonOffset = 0,
        .trainerScale = 308,
        .trainerOffset = 1,
    },

    [NATIONAL_DEX_ZAPDOS] =
    {
        .categoryName = _("ELECTRIC"),
        .height = 16,
        .weight = 526,
        .description = gZapdosPokedexText,
        .unusedDescription = gZapdosPokedexTextUnused,
        .pokemonScale = 275,
        .pokemonOffset = 1,
        .trainerScale = 330,
        .trainerOffset = 3,
    },

    [NATIONAL_DEX_MOLTRES] =
    {
        .categoryName = _("FLAME"),
        .height = 20,
        .weight = 600,
        .description = gMoltresPokedexText,
        .unusedDescription = gMoltresPokedexTextUnused,
        .pokemonScale = 270,
        .pokemonOffset = 1,
        .trainerScale = 379,
        .trainerOffset = 6,
    },

    [NATIONAL_DEX_DRATINI] =
    {
        .categoryName = _("DRAGON"),
        .height = 18,
        .weight = 33,
        .description = gDratiniPokedexText,
        .unusedDescription = gDratiniPokedexTextUnused,
        .pokemonScale = 256,
        .pokemonOffset = 8,
        .trainerScale = 386,
        .trainerOffset = 6,
    },

    [NATIONAL_DEX_DRAGONAIR] =
    {
        .categoryName = _("DRAGON"),
        .height = 40,
        .weight = 165,
        .description = gDragonairPokedexText,
        .unusedDescription = gDragonairPokedexTextUnused,
        .pokemonScale = 274,
        .pokemonOffset = 0,
        .trainerScale = 423,
        .trainerOffset = 6,
    },

    [NATIONAL_DEX_DRAGONITE] =
    {
        .categoryName = _("DRAGON"),
        .height = 22,
        .weight = 2100,
        .description = gDragonitePokedexText,
        .unusedDescription = gDragonitePokedexTextUnused,
        .pokemonScale = 283,
        .pokemonOffset = -1,
        .trainerScale = 342,
        .trainerOffset = 4,
    },

    [NATIONAL_DEX_MEWTWO] =
    {
        .categoryName = _("GENETIC"),
        .height = 20,
        .weight = 1220,
        .description = gMewtwoPokedexText,
        .unusedDescription = gMewtwoPokedexTextUnused,
        .pokemonScale = 276,
        .pokemonOffset = -1,
        .trainerScale = 342,
        .trainerOffset = 5,
    },

    [NATIONAL_DEX_MEW] =
    {
        .categoryName = _("NEW SPECIES"),
        .height = 4,
        .weight = 40,
        .description = gMewPokedexText,
        .unusedDescription = gMewPokedexTextUnused,
        .pokemonScale = 460,
        .pokemonOffset = -2,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_CHIKORITA] =
    {
        .categoryName = _("LEAF"),
        .height = 9,
        .weight = 64,
        .description = gChikoritaPokedexText,
        .unusedDescription = gChikoritaPokedexTextUnused,
        .pokemonScale = 512,
        .pokemonOffset = 18,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_BAYLEEF] =
    {
        .categoryName = _("LEAF"),
        .height = 12,
        .weight = 158,
        .description = gBayleefPokedexText,
        .unusedDescription = gBayleefPokedexTextUnused,
        .pokemonScale = 296,
        .pokemonOffset = 4,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_MEGANIUM] =
    {
        .categoryName = _("HERB"),
        .height = 18,
        .weight = 1005,
        .description = gMeganiumPokedexText,
        .unusedDescription = gMeganiumPokedexTextUnused,
        .pokemonScale = 286,
        .pokemonOffset = 0,
        .trainerScale = 317,
        .trainerOffset = 2,
    },

    [NATIONAL_DEX_CYNDAQUIL] =
    {
        .categoryName = _("FIRE MOUSE"),
        .height = 5,
        .weight = 79,
        .description = gCyndaquilPokedexText,
        .unusedDescription = gCyndaquilPokedexTextUnused,
        .pokemonScale = 539,
        .pokemonOffset = 19,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_QUILAVA] =
    {
        .categoryName = _("VOLCANO"),
        .height = 9,
        .weight = 190,
        .description = gQuilavaPokedexText,
        .unusedDescription = gQuilavaPokedexTextUnused,
        .pokemonScale = 329,
        .pokemonOffset = 10,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_TYPHLOSION] =
    {
        .categoryName = _("VOLCANO"),
        .height = 17,
        .weight = 795,
        .description = gTyphlosionPokedexText,
        .unusedDescription = gTyphlosionPokedexTextUnused,
        .pokemonScale = 284,
        .pokemonOffset = -1,
        .trainerScale = 287,
        .trainerOffset = 0,
    },

    [NATIONAL_DEX_TOTODILE] =
    {
        .categoryName = _("BIG JAW"),
        .height = 6,
        .weight = 95,
        .description = gTotodilePokedexText,
        .unusedDescription = gTotodilePokedexTextUnused,
        .pokemonScale = 487,
        .pokemonOffset = 20,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_CROCONAW] =
    {
        .categoryName = _("BIG JAW"),
        .height = 11,
        .weight = 250,
        .description = gCroconawPokedexText,
        .unusedDescription = gCroconawPokedexTextUnused,
        .pokemonScale = 378,
        .pokemonOffset = 11,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_FERALIGATR] =
    {
        .categoryName = _("BIG JAW"),
        .height = 23,
        .weight = 888,
        .description = gFeraligatrPokedexText,
        .unusedDescription = gFeraligatrPokedexTextUnused,
        .pokemonScale = 282,
        .pokemonOffset = -1,
        .trainerScale = 375,
        .trainerOffset = 6,
    },

    [NATIONAL_DEX_SENTRET] =
    {
        .categoryName = _("SCOUT"),
        .height = 8,
        .weight = 60,
        .description = gSentretPokedexText,
        .unusedDescription = gSentretPokedexTextUnused,
        .pokemonScale = 439,
        .pokemonOffset = 12,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_FURRET] =
    {
        .categoryName = _("LONG BODY"),
        .height = 18,
        .weight = 325,
        .description = gFurretPokedexText,
        .unusedDescription = gFurretPokedexTextUnused,
        .pokemonScale = 346,
        .pokemonOffset = 10,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_HOOTHOOT] =
    {
        .categoryName = _("OWL"),
        .height = 7,
        .weight = 212,
        .description = gHoothootPokedexText,
        .unusedDescription = gHoothootPokedexTextUnused,
        .pokemonScale = 380,
        .pokemonOffset = 15,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_NOCTOWL] =
    {
        .categoryName = _("OWL"),
        .height = 16,
        .weight = 408,
        .description = gNoctowlPokedexText,
        .unusedDescription = gNoctowlPokedexTextUnused,
        .pokemonScale = 278,
        .pokemonOffset = 2,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_LEDYBA] =
    {
        .categoryName = _("FIVE STAR"),
        .height = 10,
        .weight = 108,
        .description = gLedybaPokedexText,
        .unusedDescription = gLedybaPokedexTextUnused,
        .pokemonScale = 256,
        .pokemonOffset = 4,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_LEDIAN] =
    {
        .categoryName = _("FIVE STAR"),
        .height = 14,
        .weight = 356,
        .description = gLedianPokedexText,
        .unusedDescription = gLedianPokedexTextUnused,
        .pokemonScale = 256,
        .pokemonOffset = 1,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_SPINARAK] =
    {
        .categoryName = _("STRING SPIT"),
        .height = 5,
        .weight = 85,
        .description = gSpinarakPokedexText,
        .unusedDescription = gSpinarakPokedexTextUnused,
        .pokemonScale = 414,
        .pokemonOffset = 20,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_ARIADOS] =
    {
        .categoryName = _("LONG LEG"),
        .height = 11,
        .weight = 335,
        .description = gAriadosPokedexText,
        .unusedDescription = gAriadosPokedexTextUnused,
        .pokemonScale = 316,
        .pokemonOffset = 7,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_CROBAT] =
    {
        .categoryName = _("BAT"),
        .height = 18,
        .weight = 750,
        .description = gCrobatPokedexText,
        .unusedDescription = gCrobatPokedexTextUnused,
        .pokemonScale = 279,
        .pokemonOffset = -1,
        .trainerScale = 313,
        .trainerOffset = 2,
    },

    [NATIONAL_DEX_CHINCHOU] =
    {
        .categoryName = _("ANGLER"),
        .height = 5,
        .weight = 120,
        .description = gChinchouPokedexText,
        .unusedDescription = gChinchouPokedexTextUnused,
        .pokemonScale = 424,
        .pokemonOffset = -2,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_LANTURN] =
    {
        .categoryName = _("LIGHT"),
        .height = 12,
        .weight = 225,
        .description = gLanturnPokedexText,
        .unusedDescription = gLanturnPokedexTextUnused,
        .pokemonScale = 269,
        .pokemonOffset = 6,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_PICHU] =
    {
        .categoryName = _("TINY MOUSE"),
        .height = 3,
        .weight = 20,
        .description = gPichuPokedexText,
        .unusedDescription = gPichuPokedexTextUnused,
        .pokemonScale = 508,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_CLEFFA] =
    {
        .categoryName = _("STAR SHAPE"),
        .height = 3,
        .weight = 30,
        .description = gCleffaPokedexText,
        .unusedDescription = gCleffaPokedexTextUnused,
        .pokemonScale = 462,
        .pokemonOffset = 22,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_IGGLYBUFF] =
    {
        .categoryName = _("BALLOON"),
        .height = 3,
        .weight = 10,
        .description = gIgglybuffPokedexText,
        .unusedDescription = gIgglybuffPokedexTextUnused,
        .pokemonScale = 457,
        .pokemonOffset = -1,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_TOGEPI] =
    {
        .categoryName = _("SPIKE BALL"),
        .height = 3,
        .weight = 15,
        .description = gTogepiPokedexText,
        .unusedDescription = gTogepiPokedexTextUnused,
        .pokemonScale = 507,
        .pokemonOffset = 21,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_TOGETIC] =
    {
        .categoryName = _("HAPPINESS"),
        .height = 6,
        .weight = 32,
        .description = gTogeticPokedexText,
        .unusedDescription = gTogeticPokedexTextUnused,
        .pokemonScale = 424,
        .pokemonOffset = 15,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_NATU] =
    {
        .categoryName = _("TINY BIRD"),
        .height = 2,
        .weight = 20,
        .description = gNatuPokedexText,
        .unusedDescription = gNatuPokedexTextUnused,
        .pokemonScale = 610,
        .pokemonOffset = 23,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_XATU] =
    {
        .categoryName = _("MYSTIC"),
        .height = 15,
        .weight = 150,
        .description = gXatuPokedexText,
        .unusedDescription = gXatuPokedexTextUnused,
        .pokemonScale = 258,
        .pokemonOffset = 4,
        .trainerScale = 317,
        .trainerOffset = 3,
    },

    [NATIONAL_DEX_MAREEP] =
    {
        .categoryName = _("WOOL"),
        .height = 6,
        .weight = 78,
        .description = gMareepPokedexText,
        .unusedDescription = gMareepPokedexTextUnused,
        .pokemonScale = 379,
        .pokemonOffset = 18,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_FLAAFFY] =
    {
        .categoryName = _("WOOL"),
        .height = 8,
        .weight = 133,
        .description = gFlaaffyPokedexText,
        .unusedDescription = gFlaaffyPokedexTextUnused,
        .pokemonScale = 372,
        .pokemonOffset = 13,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_AMPHAROS] =
    {
        .categoryName = _("LIGHT"),
        .height = 14,
        .weight = 615,
        .description = gAmpharosPokedexText,
        .unusedDescription = gAmpharosPokedexTextUnused,
        .pokemonScale = 275,
        .pokemonOffset = 2,
        .trainerScale = 283,
        .trainerOffset = -1,
    },

    [NATIONAL_DEX_BELLOSSOM] =
    {
        .categoryName = _("FLOWER"),
        .height = 4,
        .weight = 58,
        .description = gBellossomPokedexText,
        .unusedDescription = gBellossomPokedexTextUnused,
        .pokemonScale = 472,
        .pokemonOffset = 19,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_MARILL] =
    {
        .categoryName = _("AQUA MOUSE"),
        .height = 4,
        .weight = 85,
        .description = gMarillPokedexText,
        .unusedDescription = gMarillPokedexTextUnused,
        .pokemonScale = 476,
        .pokemonOffset = 19,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_AZUMARILL] =
    {
        .categoryName = _("AQUA RABBIT"),
        .height = 8,
        .weight = 285,
        .description = gAzumarillPokedexText,
        .unusedDescription = gAzumarillPokedexTextUnused,
        .pokemonScale = 448,
        .pokemonOffset = 15,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_SUDOWOODO] =
    {
        .categoryName = _("IMITATION"),
        .height = 12,
        .weight = 380,
        .description = gSudowoodoPokedexText,
        .unusedDescription = gSudowoodoPokedexTextUnused,
        .pokemonScale = 305,
        .pokemonOffset = 7,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_POLITOED] =
    {
        .categoryName = _("FROG"),
        .height = 11,
        .weight = 339,
        .description = gPolitoedPokedexText,
        .unusedDescription = gPolitoedPokedexTextUnused,
        .pokemonScale = 289,
        .pokemonOffset = 5,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_HOPPIP] =
    {
        .categoryName = _("COTTONWEED"),
        .height = 4,
        .weight = 5,
        .description = gHoppipPokedexText,
        .unusedDescription = gHoppipPokedexTextUnused,
        .pokemonScale = 562,
        .pokemonOffset = -7,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_SKIPLOOM] =
    {
        .categoryName = _("COTTONWEED"),
        .height = 6,
        .weight = 10,
        .description = gSkiploomPokedexText,
        .unusedDescription = gSkiploomPokedexTextUnused,
        .pokemonScale = 387,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_JUMPLUFF] =
    {
        .categoryName = _("COTTONWEED"),
        .height = 8,
        .weight = 30,
        .description = gJumpluffPokedexText,
        .unusedDescription = gJumpluffPokedexTextUnused,
        .pokemonScale = 418,
        .pokemonOffset = -4,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_AIPOM] =
    {
        .categoryName = _("LONG TAIL"),
        .height = 8,
        .weight = 115,
        .description = gAipomPokedexText,
        .unusedDescription = gAipomPokedexTextUnused,
        .pokemonScale = 363,
        .pokemonOffset = 8,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_SUNKERN] =
    {
        .categoryName = _("SEED"),
        .height = 3,
        .weight = 18,
        .description = gSunkernPokedexText,
        .unusedDescription = gSunkernPokedexTextUnused,
        .pokemonScale = 541,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_SUNFLORA] =
    {
        .categoryName = _("SUN"),
        .height = 8,
        .weight = 85,
        .description = gSunfloraPokedexText,
        .unusedDescription = gSunfloraPokedexTextUnused,
        .pokemonScale = 374,
        .pokemonOffset = 12,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_YANMA] =
    {
        .categoryName = _("CLEAR WING"),
        .height = 12,
        .weight = 380,
        .description = gYanmaPokedexText,
        .unusedDescription = gYanmaPokedexTextUnused,
        .pokemonScale = 274,
        .pokemonOffset = -4,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_WOOPER] =
    {
        .categoryName = _("WATER FISH"),
        .height = 4,
        .weight = 85,
        .description = gWooperPokedexText,
        .unusedDescription = gWooperPokedexTextUnused,
        .pokemonScale = 479,
        .pokemonOffset = 20,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_QUAGSIRE] =
    {
        .categoryName = _("WATER FISH"),
        .height = 14,
        .weight = 750,
        .description = gQuagsirePokedexText,
        .unusedDescription = gQuagsirePokedexTextUnused,
        .pokemonScale = 273,
        .pokemonOffset = 4,
        .trainerScale = 273,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_ESPEON] =
    {
        .categoryName = _("SUN"),
        .height = 9,
        .weight = 265,
        .description = gEspeonPokedexText,
        .unusedDescription = gEspeonPokedexTextUnused,
        .pokemonScale = 363,
        .pokemonOffset = 12,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_UMBREON] =
    {
        .categoryName = _("MOONLIGHT"),
        .height = 10,
        .weight = 270,
        .description = gUmbreonPokedexText,
        .unusedDescription = gUmbreonPokedexTextUnused,
        .pokemonScale = 317,
        .pokemonOffset = 9,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_MURKROW] =
    {
        .categoryName = _("DARKNESS"),
        .height = 5,
        .weight = 21,
        .description = gMurkrowPokedexText,
        .unusedDescription = gMurkrowPokedexTextUnused,
        .pokemonScale = 401,
        .pokemonOffset = -8,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_SLOWKING] =
    {
        .categoryName = _("ROYAL"),
        .height = 20,
        .weight = 795,
        .description = gSlowkingPokedexText,
        .unusedDescription = gSlowkingPokedexTextUnused,
        .pokemonScale = 265,
        .pokemonOffset = -1,
        .trainerScale = 330,
        .trainerOffset = 4,
    },

    [NATIONAL_DEX_MISDREAVUS] =
    {
        .categoryName = _("SCREECH"),
        .height = 7,
        .weight = 10,
        .description = gMisdreavusPokedexText,
        .unusedDescription = gMisdreavusPokedexTextUnused,
        .pokemonScale = 407,
        .pokemonOffset = -8,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_UNOWN] =
    {
        .categoryName = _("SYMBOL"),
        .height = 5,
        .weight = 50,
        .description = gUnownPokedexText,
        .unusedDescription = gUnownPokedexTextUnused,
        .pokemonScale = 411,
        .pokemonOffset = 2,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_WOBBUFFET] =
    {
        .categoryName = _("PATIENT"),
        .height = 13,
        .weight = 285,
        .description = gWobbuffetPokedexText,
        .unusedDescription = gWobbuffetPokedexTextUnused,
        .pokemonScale = 274,
        .pokemonOffset = 4,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_GIRAFARIG] =
    {
        .categoryName = _("LONG NECK"),
        .height = 15,
        .weight = 415,
        .description = gGirafarigPokedexText,
        .unusedDescription = gGirafarigPokedexTextUnused,
        .pokemonScale = 281,
        .pokemonOffset = 2,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_PINECO] =
    {
        .categoryName = _("BAGWORM"),
        .height = 6,
        .weight = 72,
        .description = gPinecoPokedexText,
        .unusedDescription = gPinecoPokedexTextUnused,
        .pokemonScale = 445,
        .pokemonOffset = 2,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_FORRETRESS] =
    {
        .categoryName = _("BAGWORM"),
        .height = 12,
        .weight = 1258,
        .description = gForretressPokedexText,
        .unusedDescription = gForretressPokedexTextUnused,
        .pokemonScale = 293,
        .pokemonOffset = 5,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_DUNSPARCE] =
    {
        .categoryName = _("LAND SNAKE"),
        .height = 15,
        .weight = 140,
        .description = gDunsparcePokedexText,
        .unusedDescription = gDunsparcePokedexTextUnused,
        .pokemonScale = 284,
        .pokemonOffset = 15,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_GLIGAR] =
    {
        .categoryName = _("FLYSCORPION"),
        .height = 11,
        .weight = 648,
        .description = gGligarPokedexText,
        .unusedDescription = gGligarPokedexTextUnused,
        .pokemonScale = 350,
        .pokemonOffset = -1,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_STEELIX] =
    {
        .categoryName = _("IRON SNAKE"),
        .height = 92,
        .weight = 4000,
        .description = gSteelixPokedexText,
        .unusedDescription = gSteelixPokedexTextUnused,
        .pokemonScale = 278,
        .pokemonOffset = -1,
        .trainerScale = 557,
        .trainerOffset = 13,
    },

    [NATIONAL_DEX_SNUBBULL] =
    {
        .categoryName = _("FAIRY"),
        .height = 6,
        .weight = 78,
        .description = gSnubbullPokedexText,
        .unusedDescription = gSnubbullPokedexTextUnused,
        .pokemonScale = 465,
        .pokemonOffset = 18,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_GRANBULL] =
    {
        .categoryName = _("FAIRY"),
        .height = 14,
        .weight = 487,
        .description = gGranbullPokedexText,
        .unusedDescription = gGranbullPokedexTextUnused,
        .pokemonScale = 256,
        .pokemonOffset = 3,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_QWILFISH] =
    {
        .categoryName = _("BALLOON"),
        .height = 5,
        .weight = 39,
        .description = gQwilfishPokedexText,
        .unusedDescription = gQwilfishPokedexTextUnused,
        .pokemonScale = 430,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_SCIZOR] =
    {
        .categoryName = _("PINCER"),
        .height = 18,
        .weight = 1180,
        .description = gScizorPokedexText,
        .unusedDescription = gScizorPokedexTextUnused,
        .pokemonScale = 282,
        .pokemonOffset = 0,
        .trainerScale = 282,
        .trainerOffset = 0,
    },

    [NATIONAL_DEX_SHUCKLE] =
    {
        .categoryName = _("MOLD"),
        .height = 6,
        .weight = 205,
        .description = gShucklePokedexText,
        .unusedDescription = gShucklePokedexTextUnused,
        .pokemonScale = 485,
        .pokemonOffset = 16,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_HERACROSS] =
    {
        .categoryName = _("SINGLE HORN"),
        .height = 15,
        .weight = 540,
        .description = gHeracrossPokedexText,
        .unusedDescription = gHeracrossPokedexTextUnused,
        .pokemonScale = 285,
        .pokemonOffset = 0,
        .trainerScale = 283,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_SNEASEL] =
    {
        .categoryName = _("SHARP CLAW"),
        .height = 9,
        .weight = 280,
        .description = gSneaselPokedexText,
        .unusedDescription = gSneaselPokedexTextUnused,
        .pokemonScale = 413,
        .pokemonOffset = -3,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_TEDDIURSA] =
    {
        .categoryName = _("LITTLE BEAR"),
        .height = 6,
        .weight = 88,
        .description = gTeddiursaPokedexText,
        .unusedDescription = gTeddiursaPokedexTextUnused,
        .pokemonScale = 455,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_URSARING] =
    {
        .categoryName = _("HIBERNATOR"),
        .height = 18,
        .weight = 1258,
        .description = gUrsaringPokedexText,
        .unusedDescription = gUrsaringPokedexTextUnused,
        .pokemonScale = 275,
        .pokemonOffset = 0,
        .trainerScale = 280,
        .trainerOffset = 0,
    },

    [NATIONAL_DEX_SLUGMA] =
    {
        .categoryName = _("LAVA"),
        .height = 7,
        .weight = 350,
        .description = gSlugmaPokedexText,
        .unusedDescription = gSlugmaPokedexTextUnused,
        .pokemonScale = 329,
        .pokemonOffset = 14,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_MAGCARGO] =
    {
        .categoryName = _("LAVA"),
        .height = 8,
        .weight = 550,
        .description = gMagcargoPokedexText,
        .unusedDescription = gMagcargoPokedexTextUnused,
        .pokemonScale = 332,
        .pokemonOffset = 14,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_SWINUB] =
    {
        .categoryName = _("PIG"),
        .height = 4,
        .weight = 65,
        .description = gSwinubPokedexText,
        .unusedDescription = gSwinubPokedexTextUnused,
        .pokemonScale = 324,
        .pokemonOffset = 19,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_PILOSWINE] =
    {
        .categoryName = _("SWINE"),
        .height = 11,
        .weight = 558,
        .description = gPiloswinePokedexText,
        .unusedDescription = gPiloswinePokedexTextUnused,
        .pokemonScale = 306,
        .pokemonOffset = 8,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_CORSOLA] =
    {
        .categoryName = _("CORAL"),
        .height = 6,
        .weight = 50,
        .description = gCorsolaPokedexText,
        .unusedDescription = gCorsolaPokedexTextUnused,
        .pokemonScale = 410,
        .pokemonOffset = 15,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_REMORAID] =
    {
        .categoryName = _("JET"),
        .height = 6,
        .weight = 120,
        .description = gRemoraidPokedexText,
        .unusedDescription = gRemoraidPokedexTextUnused,
        .pokemonScale = 316,
        .pokemonOffset = 4,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_OCTILLERY] =
    {
        .categoryName = _("JET"),
        .height = 9,
        .weight = 285,
        .description = gOctilleryPokedexText,
        .unusedDescription = gOctilleryPokedexTextUnused,
        .pokemonScale = 296,
        .pokemonOffset = 9,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_DELIBIRD] =
    {
        .categoryName = _("DELIVERY"),
        .height = 9,
        .weight = 160,
        .description = gDelibirdPokedexText,
        .unusedDescription = gDelibirdPokedexTextUnused,
        .pokemonScale = 293,
        .pokemonOffset = 8,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_MANTINE] =
    {
        .categoryName = _("KITE"),
        .height = 21,
        .weight = 2200,
        .description = gMantinePokedexText,
        .unusedDescription = gMantinePokedexTextUnused,
        .pokemonScale = 275,
        .pokemonOffset = 0,
        .trainerScale = 360,
        .trainerOffset = 6,
    },

    [NATIONAL_DEX_SKARMORY] =
    {
        .categoryName = _("ARMOR BIRD"),
        .height = 17,
        .weight = 505,
        .description = gSkarmoryPokedexText,
        .unusedDescription = gSkarmoryPokedexTextUnused,
        .pokemonScale = 285,
        .pokemonOffset = 0,
        .trainerScale = 276,
        .trainerOffset = 0,
    },

    [NATIONAL_DEX_HOUNDOUR] =
    {
        .categoryName = _("DARK"),
        .height = 6,
        .weight = 108,
        .description = gHoundourPokedexText,
        .unusedDescription = gHoundourPokedexTextUnused,
        .pokemonScale = 393,
        .pokemonOffset = 15,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_HOUNDOOM] =
    {
        .categoryName = _("DARK"),
        .height = 14,
        .weight = 350,
        .description = gHoundoomPokedexText,
        .unusedDescription = gHoundoomPokedexTextUnused,
        .pokemonScale = 256,
        .pokemonOffset = 2,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_KINGDRA] =
    {
        .categoryName = _("DRAGON"),
        .height = 18,
        .weight = 1520,
        .description = gKingdraPokedexText,
        .unusedDescription = gKingdraPokedexTextUnused,
        .pokemonScale = 257,
        .pokemonOffset = 1,
        .trainerScale = 293,
        .trainerOffset = 1,
    },

    [NATIONAL_DEX_PHANPY] =
    {
        .categoryName = _("LONG NOSE"),
        .height = 5,
        .weight = 335,
        .description = gPhanpyPokedexText,
        .unusedDescription = gPhanpyPokedexTextUnused,
        .pokemonScale = 465,
        .pokemonOffset = 20,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_DONPHAN] =
    {
        .categoryName = _("ARMOR"),
        .height = 11,
        .weight = 1200,
        .description = gDonphanPokedexText,
        .unusedDescription = gDonphanPokedexTextUnused,
        .pokemonScale = 313,
        .pokemonOffset = 9,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_PORYGON2] =
    {
        .categoryName = _("VIRTUAL"),
        .height = 6,
        .weight = 325,
        .description = gPorygon2PokedexText,
        .unusedDescription = gPorygon2PokedexTextUnused,
        .pokemonScale = 320,
        .pokemonOffset = 15,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_STANTLER] =
    {
        .categoryName = _("BIG HORN"),
        .height = 14,
        .weight = 712,
        .description = gStantlerPokedexText,
        .unusedDescription = gStantlerPokedexTextUnused,
        .pokemonScale = 277,
        .pokemonOffset = -1,
        .trainerScale = 277,
        .trainerOffset = 0,
    },

    [NATIONAL_DEX_SMEARGLE] =
    {
        .categoryName = _("PAINTER"),
        .height = 12,
        .weight = 580,
        .description = gSmearglePokedexText,
        .unusedDescription = gSmearglePokedexTextUnused,
        .pokemonScale = 287,
        .pokemonOffset = 5,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_TYROGUE] =
    {
        .categoryName = _("SCUFFLE"),
        .height = 7,
        .weight = 210,
        .description = gTyroguePokedexText,
        .unusedDescription = gTyroguePokedexTextUnused,
        .pokemonScale = 292,
        .pokemonOffset = 8,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_HITMONTOP] =
    {
        .categoryName = _("HANDSTAND"),
        .height = 14,
        .weight = 480,
        .description = gHitmontopPokedexText,
        .unusedDescription = gHitmontopPokedexTextUnused,
        .pokemonScale = 256,
        .pokemonOffset = 2,
        .trainerScale = 257,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_SMOOCHUM] =
    {
        .categoryName = _("KISS"),
        .height = 4,
        .weight = 60,
        .description = gSmoochumPokedexText,
        .unusedDescription = gSmoochumPokedexTextUnused,
        .pokemonScale = 440,
        .pokemonOffset = 19,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_ELEKID] =
    {
        .categoryName = _("ELECTRIC"),
        .height = 6,
        .weight = 235,
        .description = gElekidPokedexText,
        .unusedDescription = gElekidPokedexTextUnused,
        .pokemonScale = 363,
        .pokemonOffset = 13,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_MAGBY] =
    {
        .categoryName = _("LIVE COAL"),
        .height = 7,
        .weight = 214,
        .description = gMagbyPokedexText,
        .unusedDescription = gMagbyPokedexTextUnused,
        .pokemonScale = 284,
        .pokemonOffset = 11,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_MILTANK] =
    {
        .categoryName = _("MILK COW"),
        .height = 12,
        .weight = 755,
        .description = gMiltankPokedexText,
        .unusedDescription = gMiltankPokedexTextUnused,
        .pokemonScale = 280,
        .pokemonOffset = 3,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_BLISSEY] =
    {
        .categoryName = _("HAPPINESS"),
        .height = 15,
        .weight = 468,
        .description = gBlisseyPokedexText,
        .unusedDescription = gBlisseyPokedexTextUnused,
        .pokemonScale = 256,
        .pokemonOffset = 3,
        .trainerScale = 310,
        .trainerOffset = 3,
    },

    [NATIONAL_DEX_RAIKOU] =
    {
        .categoryName = _("THUNDER"),
        .height = 19,
        .weight = 1780,
        .description = gRaikouPokedexText,
        .unusedDescription = gRaikouPokedexTextUnused,
        .pokemonScale = 283,
        .pokemonOffset = 0,
        .trainerScale = 359,
        .trainerOffset = 6,
    },

    [NATIONAL_DEX_ENTEI] =
    {
        .categoryName = _("VOLCANO"),
        .height = 21,
        .weight = 1980,
        .description = gEnteiPokedexText,
        .unusedDescription = gEnteiPokedexTextUnused,
        .pokemonScale = 283,
        .pokemonOffset = 0,
        .trainerScale = 370,
        .trainerOffset = 7,
    },

    [NATIONAL_DEX_SUICUNE] =
    {
        .categoryName = _("AURORA"),
        .height = 20,
        .weight = 1870,
        .description = gSuicunePokedexText,
        .unusedDescription = gSuicunePokedexTextUnused,
        .pokemonScale = 286,
        .pokemonOffset = 0,
        .trainerScale = 371,
        .trainerOffset = 7,
    },

    [NATIONAL_DEX_LARVITAR] =
    {
        .categoryName = _("ROCK SKIN"),
        .height = 6,
        .weight = 720,
        .description = gLarvitarPokedexText,
        .unusedDescription = gLarvitarPokedexTextUnused,
        .pokemonScale = 472,
        .pokemonOffset = 16,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_PUPITAR] =
    {
        .categoryName = _("HARD SHELL"),
        .height = 12,
        .weight = 1520,
        .description = gPupitarPokedexText,
        .unusedDescription = gPupitarPokedexTextUnused,
        .pokemonScale = 292,
        .pokemonOffset = 8,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_TYRANITAR] =
    {
        .categoryName = _("ARMOR"),
        .height = 20,
        .weight = 2020,
        .description = gTyranitarPokedexText,
        .unusedDescription = gTyranitarPokedexTextUnused,
        .pokemonScale = 285,
        .pokemonOffset = 0,
        .trainerScale = 383,
        .trainerOffset = 7,
    },

    [NATIONAL_DEX_LUGIA] =
    {
        .categoryName = _("DIVING"),
        .height = 52,
        .weight = 2160,
        .description = gLugiaPokedexText,
        .unusedDescription = gLugiaPokedexTextUnused,
        .pokemonScale = 283,
        .pokemonOffset = 0,
        .trainerScale = 742,
        .trainerOffset = 18,
    },

    [NATIONAL_DEX_HO_OH] =
    {
        .categoryName = _("RAINBOW"),
        .height = 38,
        .weight = 1990,
        .description = gHoOhPokedexText,
        .unusedDescription = gHoOhPokedexTextUnused,
        .pokemonScale = 283,
        .pokemonOffset = 0,
        .trainerScale = 620,
        .trainerOffset = 16,
    },

    [NATIONAL_DEX_CELEBI] =
    {
        .categoryName = _("TIME TRAVEL"),
        .height = 6,
        .weight = 50,
        .description = gCelebiPokedexText,
        .unusedDescription = gCelebiPokedexTextUnused,
        .pokemonScale = 393,
        .pokemonOffset = -10,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_TREECKO] =
    {
        .categoryName = _("WOOD GECKO"),
        .height = 5,
        .weight = 50,
        .description = gTreeckoPokedexText,
        .unusedDescription = gTreeckoPokedexTextUnused,
        .pokemonScale = 541,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_GROVYLE] =
    {
        .categoryName = _("WOOD GECKO"),
        .height = 9,
        .weight = 216,
        .description = gGrovylePokedexText,
        .unusedDescription = gGrovylePokedexTextUnused,
        .pokemonScale = 360,
        .pokemonOffset = 5,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_SCEPTILE] =
    {
        .categoryName = _("FOREST"),
        .height = 17,
        .weight = 522,
        .description = gSceptilePokedexText,
        .unusedDescription = gSceptilePokedexTextUnused,
        .pokemonScale = 282,
        .pokemonOffset = -1,
        .trainerScale = 313,
        .trainerOffset = 3,
    },

    [NATIONAL_DEX_TORCHIC] =
    {
        .categoryName = _("CHICK"),
        .height = 4,
        .weight = 25,
        .description = gTorchicPokedexText,
        .unusedDescription = gTorchicPokedexTextUnused,
        .pokemonScale = 566,
        .pokemonOffset = 18,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_COMBUSKEN] =
    {
        .categoryName = _("YOUNG FOWL"),
        .height = 9,
        .weight = 195,
        .description = gCombuskenPokedexText,
        .unusedDescription = gCombuskenPokedexTextUnused,
        .pokemonScale = 343,
        .pokemonOffset = 5,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_BLAZIKEN] =
    {
        .categoryName = _("BLAZE"),
        .height = 19,
        .weight = 520,
        .description = gBlazikenPokedexText,
        .unusedDescription = gBlazikenPokedexTextUnused,
        .pokemonScale = 275,
        .pokemonOffset = -1,
        .trainerScale = 314,
        .trainerOffset = 3,
    },

    [NATIONAL_DEX_MUDKIP] =
    {
        .categoryName = _("MUD FISH"),
        .height = 4,
        .weight = 76,
        .description = gMudkipPokedexText,
        .unusedDescription = gMudkipPokedexTextUnused,
        .pokemonScale = 535,
        .pokemonOffset = 19,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_MARSHTOMP] =
    {
        .categoryName = _("MUD FISH"),
        .height = 7,
        .weight = 280,
        .description = gMarshtompPokedexText,
        .unusedDescription = gMarshtompPokedexTextUnused,
        .pokemonScale = 340,
        .pokemonOffset = 7,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_SWAMPERT] =
    {
        .categoryName = _("MUD FISH"),
        .height = 15,
        .weight = 819,
        .description = gSwampertPokedexText,
        .unusedDescription = gSwampertPokedexTextUnused,
        .pokemonScale = 276,
        .pokemonOffset = -1,
        .trainerScale = 282,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_POOCHYENA] =
    {
        .categoryName = _("BITE"),
        .height = 5,
        .weight = 136,
        .description = gPoochyenaPokedexText,
        .unusedDescription = gPoochyenaPokedexTextUnused,
        .pokemonScale = 481,
        .pokemonOffset = 18,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_MIGHTYENA] =
    {
        .categoryName = _("BITE"),
        .height = 10,
        .weight = 370,
        .description = gMightyenaPokedexText,
        .unusedDescription = gMightyenaPokedexTextUnused,
        .pokemonScale = 359,
        .pokemonOffset = 9,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_ZIGZAGOON] =
    {
        .categoryName = _("TINYRACCOON"),
        .height = 4,
        .weight = 175,
        .description = gZigzagoonPokedexText,
        .unusedDescription = gZigzagoonPokedexTextUnused,
        .pokemonScale = 560,
        .pokemonOffset = 21,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_LINOONE] =
    {
        .categoryName = _("RUSHING"),
        .height = 5,
        .weight = 325,
        .description = gLinoonePokedexText,
        .unusedDescription = gLinoonePokedexTextUnused,
        .pokemonScale = 321,
        .pokemonOffset = 5,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_WURMPLE] =
    {
        .categoryName = _("WORM"),
        .height = 3,
        .weight = 36,
        .description = gWurmplePokedexText,
        .unusedDescription = gWurmplePokedexTextUnused,
        .pokemonScale = 711,
        .pokemonOffset = 22,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_SILCOON] =
    {
        .categoryName = _("COCOON"),
        .height = 6,
        .weight = 100,
        .description = gSilcoonPokedexText,
        .unusedDescription = gSilcoonPokedexTextUnused,
        .pokemonScale = 431,
        .pokemonOffset = 19,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_BEAUTIFLY] =
    {
        .categoryName = _("BUTTERFLY"),
        .height = 10,
        .weight = 284,
        .description = gBeautiflyPokedexText,
        .unusedDescription = gBeautiflyPokedexTextUnused,
        .pokemonScale = 298,
        .pokemonOffset = -1,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_CASCOON] =
    {
        .categoryName = _("COCOON"),
        .height = 7,
        .weight = 115,
        .description = gCascoonPokedexText,
        .unusedDescription = gCascoonPokedexTextUnused,
        .pokemonScale = 391,
        .pokemonOffset = 19,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_DUSTOX] =
    {
        .categoryName = _("POISON MOTH"),
        .height = 12,
        .weight = 316,
        .description = gDustoxPokedexText,
        .unusedDescription = gDustoxPokedexTextUnused,
        .pokemonScale = 269,
        .pokemonOffset = 1,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_LOTAD] =
    {
        .categoryName = _("WATER WEED"),
        .height = 5,
        .weight = 26,
        .description = gLotadPokedexText,
        .unusedDescription = gLotadPokedexTextUnused,
        .pokemonScale = 406,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_LOMBRE] =
    {
        .categoryName = _("JOLLY"),
        .height = 12,
        .weight = 325,
        .description = gLombrePokedexText,
        .unusedDescription = gLombrePokedexTextUnused,
        .pokemonScale = 277,
        .pokemonOffset = 7,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_LUDICOLO] =
    {
        .categoryName = _("CAREFREE"),
        .height = 15,
        .weight = 550,
        .description = gLudicoloPokedexText,
        .unusedDescription = gLudicoloPokedexTextUnused,
        .pokemonScale = 283,
        .pokemonOffset = 0,
        .trainerScale = 282,
        .trainerOffset = 0,
    },

    [NATIONAL_DEX_SEEDOT] =
    {
        .categoryName = _("ACORN"),
        .height = 5,
        .weight = 40,
        .description = gSeedotPokedexText,
        .unusedDescription = gSeedotPokedexTextUnused,
        .pokemonScale = 472,
        .pokemonOffset = 20,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_NUZLEAF] =
    {
        .categoryName = _("WILY"),
        .height = 10,
        .weight = 280,
        .description = gNuzleafPokedexText,
        .unusedDescription = gNuzleafPokedexTextUnused,
        .pokemonScale = 299,
        .pokemonOffset = 8,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_SHIFTRY] =
    {
        .categoryName = _("WICKED"),
        .height = 13,
        .weight = 596,
        .description = gShiftryPokedexText,
        .unusedDescription = gShiftryPokedexTextUnused,
        .pokemonScale = 290,
        .pokemonOffset = 2,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_TAILLOW] =
    {
        .categoryName = _("TINYSWALLOW"),
        .height = 3,
        .weight = 23,
        .description = gTaillowPokedexText,
        .unusedDescription = gTaillowPokedexTextUnused,
        .pokemonScale = 465,
        .pokemonOffset = 20,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_SWELLOW] =
    {
        .categoryName = _("SWALLOW"),
        .height = 7,
        .weight = 198,
        .description = gSwellowPokedexText,
        .unusedDescription = gSwellowPokedexTextUnused,
        .pokemonScale = 428,
        .pokemonOffset = 13,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_WINGULL] =
    {
        .categoryName = _("SEAGULL"),
        .height = 6,
        .weight = 95,
        .description = gWingullPokedexText,
        .unusedDescription = gWingullPokedexTextUnused,
        .pokemonScale = 295,
        .pokemonOffset = -2,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_PELIPPER] =
    {
        .categoryName = _("WATER BIRD"),
        .height = 12,
        .weight = 280,
        .description = gPelipperPokedexText,
        .unusedDescription = gPelipperPokedexTextUnused,
        .pokemonScale = 288,
        .pokemonOffset = 1,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_RALTS] =
    {
        .categoryName = _("FEELING"),
        .height = 4,
        .weight = 66,
        .description = gRaltsPokedexText,
        .unusedDescription = gRaltsPokedexTextUnused,
        .pokemonScale = 457,
        .pokemonOffset = 18,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_KIRLIA] =
    {
        .categoryName = _("EMOTION"),
        .height = 8,
        .weight = 202,
        .description = gKirliaPokedexText,
        .unusedDescription = gKirliaPokedexTextUnused,
        .pokemonScale = 354,
        .pokemonOffset = 10,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_GARDEVOIR] =
    {
        .categoryName = _("EMBRACE"),
        .height = 16,
        .weight = 484,
        .description = gGardevoirPokedexText,
        .unusedDescription = gGardevoirPokedexTextUnused,
        .pokemonScale = 277,
        .pokemonOffset = 0,
        .trainerScale = 276,
        .trainerOffset = -1,
    },

    [NATIONAL_DEX_SURSKIT] =
    {
        .categoryName = _("POND SKATER"),
        .height = 5,
        .weight = 17,
        .description = gSurskitPokedexText,
        .unusedDescription = gSurskitPokedexTextUnused,
        .pokemonScale = 375,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_MASQUERAIN] =
    {
        .categoryName = _("EYEBALL"),
        .height = 8,
        .weight = 36,
        .description = gMasquerainPokedexText,
        .unusedDescription = gMasquerainPokedexTextUnused,
        .pokemonScale = 378,
        .pokemonOffset = -1,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_SHROOMISH] =
    {
        .categoryName = _("MUSHROOM"),
        .height = 4,
        .weight = 45,
        .description = gShroomishPokedexText,
        .unusedDescription = gShroomishPokedexTextUnused,
        .pokemonScale = 513,
        .pokemonOffset = 20,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_BRELOOM] =
    {
        .categoryName = _("MUSHROOM"),
        .height = 12,
        .weight = 392,
        .description = gBreloomPokedexText,
        .unusedDescription = gBreloomPokedexTextUnused,
        .pokemonScale = 324,
        .pokemonOffset = 6,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_SLAKOTH] =
    {
        .categoryName = _("SLACKER"),
        .height = 8,
        .weight = 240,
        .description = gSlakothPokedexText,
        .unusedDescription = gSlakothPokedexTextUnused,
        .pokemonScale = 291,
        .pokemonOffset = 16,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_VIGOROTH] =
    {
        .categoryName = _("WILD MONKEY"),
        .height = 14,
        .weight = 465,
        .description = gVigorothPokedexText,
        .unusedDescription = gVigorothPokedexTextUnused,
        .pokemonScale = 301,
        .pokemonOffset = 1,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_SLAKING] =
    {
        .categoryName = _("LAZY"),
        .height = 20,
        .weight = 1305,
        .description = gSlakingPokedexText,
        .unusedDescription = gSlakingPokedexTextUnused,
        .pokemonScale = 277,
        .pokemonOffset = 5,
        .trainerScale = 326,
        .trainerOffset = 3,
    },

    [NATIONAL_DEX_NINCADA] =
    {
        .categoryName = _("TRAINEE"),
        .height = 5,
        .weight = 55,
        .description = gNincadaPokedexText,
        .unusedDescription = gNincadaPokedexTextUnused,
        .pokemonScale = 405,
        .pokemonOffset = 20,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_NINJASK] =
    {
        .categoryName = _("NINJA"),
        .height = 8,
        .weight = 120,
        .description = gNinjaskPokedexText,
        .unusedDescription = gNinjaskPokedexTextUnused,
        .pokemonScale = 383,
        .pokemonOffset = -9,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_SHEDINJA] =
    {
        .categoryName = _("SHED"),
        .height = 8,
        .weight = 12,
        .description = gShedinjaPokedexText,
        .unusedDescription = gShedinjaPokedexTextUnused,
        .pokemonScale = 372,
        .pokemonOffset = -8,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_WHISMUR] =
    {
        .categoryName = _("WHISPER"),
        .height = 6,
        .weight = 163,
        .description = gWhismurPokedexText,
        .unusedDescription = gWhismurPokedexTextUnused,
        .pokemonScale = 373,
        .pokemonOffset = 16,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_LOUDRED] =
    {
        .categoryName = _("BIG VOICE"),
        .height = 10,
        .weight = 405,
        .description = gLoudredPokedexText,
        .unusedDescription = gLoudredPokedexTextUnused,
        .pokemonScale = 356,
        .pokemonOffset = 8,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_EXPLOUD] =
    {
        .categoryName = _("LOUD NOISE"),
        .height = 15,
        .weight = 840,
        .description = gExploudPokedexText,
        .unusedDescription = gExploudPokedexTextUnused,
        .pokemonScale = 284,
        .pokemonOffset = 1,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_MAKUHITA] =
    {
        .categoryName = _("GUTS"),
        .height = 10,
        .weight = 864,
        .description = gMakuhitaPokedexText,
        .unusedDescription = gMakuhitaPokedexTextUnused,
        .pokemonScale = 256,
        .pokemonOffset = 9,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_HARIYAMA] =
    {
        .categoryName = _("ARM THRUST"),
        .height = 23,
        .weight = 2538,
        .description = gHariyamaPokedexText,
        .unusedDescription = gHariyamaPokedexTextUnused,
        .pokemonScale = 268,
        .pokemonOffset = -1,
        .trainerScale = 375,
        .trainerOffset = 6,
    },

    [NATIONAL_DEX_AZURILL] =
    {
        .categoryName = _("POLKA DOT"),
        .height = 2,
        .weight = 20,
        .description = gAzurillPokedexText,
        .unusedDescription = gAzurillPokedexTextUnused,
        .pokemonScale = 603,
        .pokemonOffset = 21,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_NOSEPASS] =
    {
        .categoryName = _("COMPASS"),
        .height = 10,
        .weight = 970,
        .description = gNosepassPokedexText,
        .unusedDescription = gNosepassPokedexTextUnused,
        .pokemonScale = 256,
        .pokemonOffset = 9,
        .trainerScale = 289,
        .trainerOffset = 1,
    },

    [NATIONAL_DEX_SKITTY] =
    {
        .categoryName = _("KITTEN"),
        .height = 6,
        .weight = 110,
        .description = gSkittyPokedexText,
        .unusedDescription = gSkittyPokedexTextUnused,
        .pokemonScale = 492,
        .pokemonOffset = 18,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_DELCATTY] =
    {
        .categoryName = _("PRIM"),
        .height = 11,
        .weight = 326,
        .description = gDelcattyPokedexText,
        .unusedDescription = gDelcattyPokedexTextUnused,
        .pokemonScale = 322,
        .pokemonOffset = 9,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_SABLEYE] =
    {
        .categoryName = _("DARKNESS"),
        .height = 5,
        .weight = 110,
        .description = gSableyePokedexText,
        .unusedDescription = gSableyePokedexTextUnused,
        .pokemonScale = 451,
        .pokemonOffset = 15,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_MAWILE] =
    {
        .categoryName = _("DECEIVER"),
        .height = 6,
        .weight = 115,
        .description = gMawilePokedexText,
        .unusedDescription = gMawilePokedexTextUnused,
        .pokemonScale = 466,
        .pokemonOffset = 15,
        .trainerScale = 256,
        .trainerOffset = -3,
    },

    [NATIONAL_DEX_ARON] =
    {
        .categoryName = _("IRON ARMOR"),
        .height = 4,
        .weight = 600,
        .description = gAronPokedexText,
        .unusedDescription = gAronPokedexTextUnused,
        .pokemonScale = 419,
        .pokemonOffset = 21,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_LAIRON] =
    {
        .categoryName = _("IRON ARMOR"),
        .height = 9,
        .weight = 1200,
        .description = gLaironPokedexText,
        .unusedDescription = gLaironPokedexTextUnused,
        .pokemonScale = 275,
        .pokemonOffset = 11,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_AGGRON] =
    {
        .categoryName = _("IRON ARMOR"),
        .height = 21,
        .weight = 3600,
        .description = gAggronPokedexText,
        .unusedDescription = gAggronPokedexTextUnused,
        .pokemonScale = 274,
        .pokemonOffset = -1,
        .trainerScale = 374,
        .trainerOffset = 7,
    },

    [NATIONAL_DEX_MEDITITE] =
    {
        .categoryName = _("MEDITATE"),
        .height = 6,
        .weight = 112,
        .description = gMedititePokedexText,
        .unusedDescription = gMedititePokedexTextUnused,
        .pokemonScale = 465,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_MEDICHAM] =
    {
        .categoryName = _("MEDITATE"),
        .height = 13,
        .weight = 315,
        .description = gMedichamPokedexText,
        .unusedDescription = gMedichamPokedexTextUnused,
        .pokemonScale = 298,
        .pokemonOffset = 2,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_ELECTRIKE] =
    {
        .categoryName = _("LIGHTNING"),
        .height = 6,
        .weight = 152,
        .description = gElectrikePokedexText,
        .unusedDescription = gElectrikePokedexTextUnused,
        .pokemonScale = 290,
        .pokemonOffset = 16,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_MANECTRIC] =
    {
        .categoryName = _("DISCHARGE"),
        .height = 15,
        .weight = 402,
        .description = gManectricPokedexText,
        .unusedDescription = gManectricPokedexTextUnused,
        .pokemonScale = 256,
        .pokemonOffset = 1,
        .trainerScale = 257,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_PLUSLE] =
    {
        .categoryName = _("CHEERING"),
        .height = 4,
        .weight = 42,
        .description = gPluslePokedexText,
        .unusedDescription = gPluslePokedexTextUnused,
        .pokemonScale = 515,
        .pokemonOffset = -9,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_MINUN] =
    {
        .categoryName = _("CHEERING"),
        .height = 4,
        .weight = 42,
        .description = gMinunPokedexText,
        .unusedDescription = gMinunPokedexTextUnused,
        .pokemonScale = 512,
        .pokemonOffset = -7,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_VOLBEAT] =
    {
        .categoryName = _("FIREFLY"),
        .height = 7,
        .weight = 177,
        .description = gVolbeatPokedexText,
        .unusedDescription = gVolbeatPokedexTextUnused,
        .pokemonScale = 442,
        .pokemonOffset = -4,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_ILLUMISE] =
    {
        .categoryName = _("FIREFLY"),
        .height = 6,
        .weight = 177,
        .description = gIllumisePokedexText,
        .unusedDescription = gIllumisePokedexTextUnused,
        .pokemonScale = 572,
        .pokemonOffset = -4,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_ROSELIA] =
    {
        .categoryName = _("THORN"),
        .height = 3,
        .weight = 20,
        .description = gRoseliaPokedexText,
        .unusedDescription = gRoseliaPokedexTextUnused,
        .pokemonScale = 677,
        .pokemonOffset = 20,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_GULPIN] =
    {
        .categoryName = _("STOMACH"),
        .height = 4,
        .weight = 103,
        .description = gGulpinPokedexText,
        .unusedDescription = gGulpinPokedexTextUnused,
        .pokemonScale = 593,
        .pokemonOffset = 22,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_SWALOT] =
    {
        .categoryName = _("POISON BAG"),
        .height = 17,
        .weight = 800,
        .description = gSwalotPokedexText,
        .unusedDescription = gSwalotPokedexTextUnused,
        .pokemonScale = 256,
        .pokemonOffset = 5,
        .trainerScale = 345,
        .trainerOffset = 4,
    },

    [NATIONAL_DEX_CARVANHA] =
    {
        .categoryName = _("SAVAGE"),
        .height = 8,
        .weight = 208,
        .description = gCarvanhaPokedexText,
        .unusedDescription = gCarvanhaPokedexTextUnused,
        .pokemonScale = 362,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_SHARPEDO] =
    {
        .categoryName = _("BRUTAL"),
        .height = 18,
        .weight = 888,
        .description = gSharpedoPokedexText,
        .unusedDescription = gSharpedoPokedexTextUnused,
        .pokemonScale = 265,
        .pokemonOffset = 0,
        .trainerScale = 342,
        .trainerOffset = 4,
    },

    [NATIONAL_DEX_WAILMER] =
    {
        .categoryName = _("BALL WHALE"),
        .height = 20,
        .weight = 1300,
        .description = gWailmerPokedexText,
        .unusedDescription = gWailmerPokedexTextUnused,
        .pokemonScale = 256,
        .pokemonOffset = 10,
        .trainerScale = 493,
        .trainerOffset = 10,
    },

    [NATIONAL_DEX_WAILORD] =
    {
        .categoryName = _("FLOAT WHALE"),
        .height = 145,
        .weight = 3980,
        .description = gWailordPokedexText,
        .unusedDescription = gWailordPokedexTextUnused,
        .pokemonScale = 276,
        .pokemonOffset = -1,
        .trainerScale = 1428,
        .trainerOffset = 20,
    },

    [NATIONAL_DEX_NUMEL] =
    {
        .categoryName = _("NUMB"),
        .height = 7,
        .weight = 240,
        .description = gNumelPokedexText,
        .unusedDescription = gNumelPokedexTextUnused,
        .pokemonScale = 310,
        .pokemonOffset = 14,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_CAMERUPT] =
    {
        .categoryName = _("ERUPTION"),
        .height = 19,
        .weight = 2200,
        .description = gCameruptPokedexText,
        .unusedDescription = gCameruptPokedexTextUnused,
        .pokemonScale = 256,
        .pokemonOffset = 6,
        .trainerScale = 345,
        .trainerOffset = 4,
    },

    [NATIONAL_DEX_TORKOAL] =
    {
        .categoryName = _("COAL"),
        .height = 5,
        .weight = 804,
        .description = gTorkoalPokedexText,
        .unusedDescription = gTorkoalPokedexTextUnused,
        .pokemonScale = 392,
        .pokemonOffset = 9,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_SPOINK] =
    {
        .categoryName = _("BOUNCE"),
        .height = 7,
        .weight = 306,
        .description = gSpoinkPokedexText,
        .unusedDescription = gSpoinkPokedexTextUnused,
        .pokemonScale = 423,
        .pokemonOffset = 15,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_GRUMPIG] =
    {
        .categoryName = _("MANIPULATE"),
        .height = 9,
        .weight = 715,
        .description = gGrumpigPokedexText,
        .unusedDescription = gGrumpigPokedexTextUnused,
        .pokemonScale = 358,
        .pokemonOffset = 9,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_SPINDA] =
    {
        .categoryName = _("SPOT PANDA"),
        .height = 11,
        .weight = 50,
        .description = gSpindaPokedexText,
        .unusedDescription = gSpindaPokedexTextUnused,
        .pokemonScale = 321,
        .pokemonOffset = 9,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_TRAPINCH] =
    {
        .categoryName = _("ANT PIT"),
        .height = 7,
        .weight = 150,
        .description = gTrapinchPokedexText,
        .unusedDescription = gTrapinchPokedexTextUnused,
        .pokemonScale = 298,
        .pokemonOffset = 15,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_VIBRAVA] =
    {
        .categoryName = _("VIBRATION"),
        .height = 11,
        .weight = 153,
        .description = gVibravaPokedexText,
        .unusedDescription = gVibravaPokedexTextUnused,
        .pokemonScale = 370,
        .pokemonOffset = 15,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_FLYGON] =
    {
        .categoryName = _("MYSTIC"),
        .height = 20,
        .weight = 820,
        .description = gFlygonPokedexText,
        .unusedDescription = gFlygonPokedexTextUnused,
        .pokemonScale = 280,
        .pokemonOffset = 0,
        .trainerScale = 299,
        .trainerOffset = 2,
    },

    [NATIONAL_DEX_CACNEA] =
    {
        .categoryName = _("CACTUS"),
        .height = 4,
        .weight = 513,
        .description = gCacneaPokedexText,
        .unusedDescription = gCacneaPokedexTextUnused,
        .pokemonScale = 455,
        .pokemonOffset = 19,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_CACTURNE] =
    {
        .categoryName = _("SCARECROW"),
        .height = 13,
        .weight = 774,
        .description = gCacturnePokedexText,
        .unusedDescription = gCacturnePokedexTextUnused,
        .pokemonScale = 327,
        .pokemonOffset = 3,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_SWABLU] =
    {
        .categoryName = _("COTTON BIRD"),
        .height = 4,
        .weight = 12,
        .description = gSwabluPokedexText,
        .unusedDescription = gSwabluPokedexTextUnused,
        .pokemonScale = 422,
        .pokemonOffset = -8,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_ALTARIA] =
    {
        .categoryName = _("HUMMING"),
        .height = 11,
        .weight = 206,
        .description = gAltariaPokedexText,
        .unusedDescription = gAltariaPokedexTextUnused,
        .pokemonScale = 327,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_ZANGOOSE] =
    {
        .categoryName = _("CAT FERRET"),
        .height = 13,
        .weight = 403,
        .description = gZangoosePokedexText,
        .unusedDescription = gZangoosePokedexTextUnused,
        .pokemonScale = 256,
        .pokemonOffset = 2,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_SEVIPER] =
    {
        .categoryName = _("FANG SNAKE"),
        .height = 27,
        .weight = 525,
        .description = gSeviperPokedexText,
        .unusedDescription = gSeviperPokedexTextUnused,
        .pokemonScale = 275,
        .pokemonOffset = 6,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_LUNATONE] =
    {
        .categoryName = _("METEORITE"),
        .height = 10,
        .weight = 1680,
        .description = gLunatonePokedexText,
        .unusedDescription = gLunatonePokedexTextUnused,
        .pokemonScale = 300,
        .pokemonOffset = 1,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_SOLROCK] =
    {
        .categoryName = _("METEORITE"),
        .height = 12,
        .weight = 1540,
        .description = gSolrockPokedexText,
        .unusedDescription = gSolrockPokedexTextUnused,
        .pokemonScale = 328,
        .pokemonOffset = -3,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_BARBOACH] =
    {
        .categoryName = _("WHISKERS"),
        .height = 4,
        .weight = 19,
        .description = gBarboachPokedexText,
        .unusedDescription = gBarboachPokedexTextUnused,
        .pokemonScale = 581,
        .pokemonOffset = -2,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_WHISCASH] =
    {
        .categoryName = _("WHISKERS"),
        .height = 9,
        .weight = 236,
        .description = gWhiscashPokedexText,
        .unusedDescription = gWhiscashPokedexTextUnused,
        .pokemonScale = 317,
        .pokemonOffset = 1,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_CORPHISH] =
    {
        .categoryName = _("RUFFIAN"),
        .height = 6,
        .weight = 115,
        .description = gCorphishPokedexText,
        .unusedDescription = gCorphishPokedexTextUnused,
        .pokemonScale = 484,
        .pokemonOffset = 18,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_CRAWDAUNT] =
    {
        .categoryName = _("ROGUE"),
        .height = 11,
        .weight = 328,
        .description = gCrawdauntPokedexText,
        .unusedDescription = gCrawdauntPokedexTextUnused,
        .pokemonScale = 365,
        .pokemonOffset = 7,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_BALTOY] =
    {
        .categoryName = _("CLAY DOLL"),
        .height = 5,
        .weight = 215,
        .description = gBaltoyPokedexText,
        .unusedDescription = gBaltoyPokedexTextUnused,
        .pokemonScale = 384,
        .pokemonOffset = 18,
        .trainerScale = 256,
        .trainerOffset = -3,
    },

    [NATIONAL_DEX_CLAYDOL] =
    {
        .categoryName = _("CLAY DOLL"),
        .height = 15,
        .weight = 1080,
        .description = gClaydolPokedexText,
        .unusedDescription = gClaydolPokedexTextUnused,
        .pokemonScale = 256,
        .pokemonOffset = 3,
        .trainerScale = 280,
        .trainerOffset = 0,
    },

    [NATIONAL_DEX_LILEEP] =
    {
        .categoryName = _("SEA LILY"),
        .height = 10,
        .weight = 238,
        .description = gLileepPokedexText,
        .unusedDescription = gLileepPokedexTextUnused,
        .pokemonScale = 305,
        .pokemonOffset = 8,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_CRADILY] =
    {
        .categoryName = _("BARNACLE"),
        .height = 15,
        .weight = 604,
        .description = gCradilyPokedexText,
        .unusedDescription = gCradilyPokedexTextUnused,
        .pokemonScale = 275,
        .pokemonOffset = -1,
        .trainerScale = 269,
        .trainerOffset = -1,
    },

    [NATIONAL_DEX_ANORITH] =
    {
        .categoryName = _("OLD SHRIMP"),
        .height = 7,
        .weight = 125,
        .description = gAnorithPokedexText,
        .unusedDescription = gAnorithPokedexTextUnused,
        .pokemonScale = 296,
        .pokemonOffset = 4,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_ARMALDO] =
    {
        .categoryName = _("PLATE"),
        .height = 15,
        .weight = 682,
        .description = gArmaldoPokedexText,
        .unusedDescription = gArmaldoPokedexTextUnused,
        .pokemonScale = 312,
        .pokemonOffset = 2,
        .trainerScale = 271,
        .trainerOffset = -1,
    },

    [NATIONAL_DEX_FEEBAS] =
    {
        .categoryName = _("FISH"),
        .height = 6,
        .weight = 74,
        .description = gFeebasPokedexText,
        .unusedDescription = gFeebasPokedexTextUnused,
        .pokemonScale = 423,
        .pokemonOffset = 3,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_MILOTIC] =
    {
        .categoryName = _("TENDER"),
        .height = 62,
        .weight = 1620,
        .description = gMiloticPokedexText,
        .unusedDescription = gMiloticPokedexTextUnused,
        .pokemonScale = 282,
        .pokemonOffset = -1,
        .trainerScale = 382,
        .trainerOffset = 7,
    },

    [NATIONAL_DEX_CASTFORM] =
    {
        .categoryName = _("WEATHER"),
        .height = 3,
        .weight = 8,
        .description = gCastformPokedexText,
        .unusedDescription = gCastformPokedexTextUnused,
        .pokemonScale = 435,
        .pokemonOffset = -5,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_KECLEON] =
    {
        .categoryName = _("COLOR SWAP"),
        .height = 10,
        .weight = 220,
        .description = gKecleonPokedexText,
        .unusedDescription = gKecleonPokedexTextUnused,
        .pokemonScale = 316,
        .pokemonOffset = 8,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_SHUPPET] =
    {
        .categoryName = _("PUPPET"),
        .height = 6,
        .weight = 23,
        .description = gShuppetPokedexText,
        .unusedDescription = gShuppetPokedexTextUnused,
        .pokemonScale = 440,
        .pokemonOffset = -3,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_BANETTE] =
    {
        .categoryName = _("MARIONETTE"),
        .height = 11,
        .weight = 125,
        .description = gBanettePokedexText,
        .unusedDescription = gBanettePokedexTextUnused,
        .pokemonScale = 262,
        .pokemonOffset = 9,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_DUSKULL] =
    {
        .categoryName = _("REQUIEM"),
        .height = 8,
        .weight = 150,
        .description = gDuskullPokedexText,
        .unusedDescription = gDuskullPokedexTextUnused,
        .pokemonScale = 376,
        .pokemonOffset = 13,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_DUSCLOPS] =
    {
        .categoryName = _("BECKON"),
        .height = 16,
        .weight = 306,
        .description = gDusclopsPokedexText,
        .unusedDescription = gDusclopsPokedexTextUnused,
        .pokemonScale = 256,
        .pokemonOffset = 2,
        .trainerScale = 299,
        .trainerOffset = 2,
    },

    [NATIONAL_DEX_TROPIUS] =
    {
        .categoryName = _("FRUIT"),
        .height = 20,
        .weight = 1000,
        .description = gTropiusPokedexText,
        .unusedDescription = gTropiusPokedexTextUnused,
        .pokemonScale = 283,
        .pokemonOffset = -1,
        .trainerScale = 371,
        .trainerOffset = 6,
    },

    [NATIONAL_DEX_CHIMECHO] =
    {
        .categoryName = _("WIND CHIME"),
        .height = 6,
        .weight = 10,
        .description = gChimechoPokedexText,
        .unusedDescription = gChimechoPokedexTextUnused,
        .pokemonScale = 505,
        .pokemonOffset = -4,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_ABSOL] =
    {
        .categoryName = _("DISASTER"),
        .height = 12,
        .weight = 470,
        .description = gAbsolPokedexText,
        .unusedDescription = gAbsolPokedexTextUnused,
        .pokemonScale = 301,
        .pokemonOffset = 1,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_WYNAUT] =
    {
        .categoryName = _("BRIGHT"),
        .height = 6,
        .weight = 140,
        .description = gWynautPokedexText,
        .unusedDescription = gWynautPokedexTextUnused,
        .pokemonScale = 453,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_SNORUNT] =
    {
        .categoryName = _("SNOW HAT"),
        .height = 7,
        .weight = 168,
        .description = gSnoruntPokedexText,
        .unusedDescription = gSnoruntPokedexTextUnused,
        .pokemonScale = 380,
        .pokemonOffset = 14,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_GLALIE] =
    {
        .categoryName = _("FACE"),
        .height = 15,
        .weight = 2565,
        .description = gGlaliePokedexText,
        .unusedDescription = gGlaliePokedexTextUnused,
        .pokemonScale = 256,
        .pokemonOffset = 3,
        .trainerScale = 344,
        .trainerOffset = 2,
    },

    [NATIONAL_DEX_SPHEAL] =
    {
        .categoryName = _("CLAP"),
        .height = 8,
        .weight = 395,
        .description = gSphealPokedexText,
        .unusedDescription = gSphealPokedexTextUnused,
        .pokemonScale = 315,
        .pokemonOffset = 15,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_SEALEO] =
    {
        .categoryName = _("BALL ROLL"),
        .height = 11,
        .weight = 876,
        .description = gSealeoPokedexText,
        .unusedDescription = gSealeoPokedexTextUnused,
        .pokemonScale = 338,
        .pokemonOffset = 12,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_WALREIN] =
    {
        .categoryName = _("ICE BREAK"),
        .height = 14,
        .weight = 1506,
        .description = gWalreinPokedexText,
        .unusedDescription = gWalreinPokedexTextUnused,
        .pokemonScale = 305,
        .pokemonOffset = 2,
        .trainerScale = 277,
        .trainerOffset = 0,
    },

    [NATIONAL_DEX_CLAMPERL] =
    {
        .categoryName = _("BIVALVE"),
        .height = 4,
        .weight = 525,
        .description = gClamperlPokedexText,
        .unusedDescription = gClamperlPokedexTextUnused,
        .pokemonScale = 691,
        .pokemonOffset = 22,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_HUNTAIL] =
    {
        .categoryName = _("DEEP SEA"),
        .height = 17,
        .weight = 270,
        .description = gHuntailPokedexText,
        .unusedDescription = gHuntailPokedexTextUnused,
        .pokemonScale = 307,
        .pokemonOffset = 1,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_GOREBYSS] =
    {
        .categoryName = _("SOUTH SEA"),
        .height = 18,
        .weight = 226,
        .description = gGorebyssPokedexText,
        .unusedDescription = gGorebyssPokedexTextUnused,
        .pokemonScale = 278,
        .pokemonOffset = 5,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_RELICANTH] =
    {
        .categoryName = _("LONGEVITY"),
        .height = 10,
        .weight = 234,
        .description = gRelicanthPokedexText,
        .unusedDescription = gRelicanthPokedexTextUnused,
        .pokemonScale = 316,
        .pokemonOffset = 5,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_LUVDISC] =
    {
        .categoryName = _("RENDEZVOUS"),
        .height = 6,
        .weight = 87,
        .description = gLuvdiscPokedexText,
        .unusedDescription = gLuvdiscPokedexTextUnused,
        .pokemonScale = 371,
        .pokemonOffset = 2,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_BAGON] =
    {
        .categoryName = _("ROCK HEAD"),
        .height = 6,
        .weight = 421,
        .description = gBagonPokedexText,
        .unusedDescription = gBagonPokedexTextUnused,
        .pokemonScale = 448,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_SHELGON] =
    {
        .categoryName = _("ENDURANCE"),
        .height = 11,
        .weight = 1105,
        .description = gShelgonPokedexText,
        .unusedDescription = gShelgonPokedexTextUnused,
        .pokemonScale = 311,
        .pokemonOffset = 10,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_SALAMENCE] =
    {
        .categoryName = _("DRAGON"),
        .height = 15,
        .weight = 1026,
        .description = gSalamencePokedexText,
        .unusedDescription = gSalamencePokedexTextUnused,
        .pokemonScale = 272,
        .pokemonOffset = 2,
        .trainerScale = 307,
        .trainerOffset = 0,
    },

    [NATIONAL_DEX_BELDUM] =
    {
        .categoryName = _("IRON BALL"),
        .height = 6,
        .weight = 952,
        .description = gBeldumPokedexText,
        .unusedDescription = gBeldumPokedexTextUnused,
        .pokemonScale = 414,
        .pokemonOffset = -1,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_METANG] =
    {
        .categoryName = _("IRON CLAW"),
        .height = 12,
        .weight = 2025,
        .description = gMetangPokedexText,
        .unusedDescription = gMetangPokedexTextUnused,
        .pokemonScale = 256,
        .pokemonOffset = 3,
        .trainerScale = 272,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_METAGROSS] =
    {
        .categoryName = _("IRON LEG"),
        .height = 16,
        .weight = 5500,
        .description = gMetagrossPokedexText,
        .unusedDescription = gMetagrossPokedexTextUnused,
        .pokemonScale = 272,
        .pokemonOffset = 3,
        .trainerScale = 461,
        .trainerOffset = 4,
    },

    [NATIONAL_DEX_REGIROCK] =
    {
        .categoryName = _("ROCK PEAK"),
        .height = 17,
        .weight = 2300,
        .description = gRegirockPokedexText,
        .unusedDescription = gRegirockPokedexTextUnused,
        .pokemonScale = 256,
        .pokemonOffset = 1,
        .trainerScale = 309,
        .trainerOffset = 1,
    },

    [NATIONAL_DEX_REGICE] =
    {
        .categoryName = _("ICEBERG"),
        .height = 18,
        .weight = 1750,
        .description = gRegicePokedexText,
        .unusedDescription = gRegicePokedexTextUnused,
        .pokemonScale = 265,
        .pokemonOffset = 0,
        .trainerScale = 317,
        .trainerOffset = 3,
    },

    [NATIONAL_DEX_REGISTEEL] =
    {
        .categoryName = _("IRON"),
        .height = 19,
        .weight = 2050,
        .description = gRegisteelPokedexText,
        .unusedDescription = gRegisteelPokedexTextUnused,
        .pokemonScale = 256,
        .pokemonOffset = 0,
        .trainerScale = 359,
        .trainerOffset = 6,
    },

    [NATIONAL_DEX_LATIAS] =
    {
        .categoryName = _("EON"),
        .height = 14,
        .weight = 400,
        .description = gLatiasPokedexText,
        .unusedDescription = gLatiasPokedexTextUnused,
        .pokemonScale = 291,
        .pokemonOffset = 2,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_LATIOS] =
    {
        .categoryName = _("EON"),
        .height = 20,
        .weight = 600,
        .description = gLatiosPokedexText,
        .unusedDescription = gLatiosPokedexTextUnused,
        .pokemonScale = 273,
        .pokemonOffset = 0,
        .trainerScale = 313,
        .trainerOffset = 3,
    },

    [NATIONAL_DEX_KYOGRE] =
    {
        .categoryName = _("SEA BASIN"),
        .height = 45,
        .weight = 3520,
        .description = gKyogrePokedexText,
        .unusedDescription = gKyogrePokedexTextUnused,
        .pokemonScale = 272,
        .pokemonOffset = 1,
        .trainerScale = 639,
        .trainerOffset = 13,
    },

    [NATIONAL_DEX_GROUDON] =
    {
        .categoryName = _("CONTINENT"),
        .height = 35,
        .weight = 9500,
        .description = gGroudonPokedexText,
        .unusedDescription = gGroudonPokedexTextUnused,
        .pokemonScale = 276,
        .pokemonOffset = 0,
        .trainerScale = 530,
        .trainerOffset = 12,
    },

    [NATIONAL_DEX_RAYQUAZA] =
    {
        .categoryName = _("SKY HIGH"),
        .height = 70,
        .weight = 2065,
        .description = gRayquazaPokedexText,
        .unusedDescription = gRayquazaPokedexTextUnused,
        .pokemonScale = 286,
        .pokemonOffset = -1,
        .trainerScale = 483,
        .trainerOffset = 9,
    },

    [NATIONAL_DEX_JIRACHI] =
    {
        .categoryName = _("WISH"),
        .height = 3,
        .weight = 11,
        .description = gJirachiPokedexText,
        .unusedDescription = gJirachiPokedexTextUnused,
        .pokemonScale = 608,
        .pokemonOffset = -8,
        .trainerScale = 256,
        .trainerOffset = -2,
    },

    [NATIONAL_DEX_DEOXYS] =
    {
        .categoryName = _("DNA"),
        .height = 17,
        .weight = 608,
        .description = gDeoxysPokedexText,
        .unusedDescription = gDeoxysPokedexTextUnused,
        .pokemonScale = 293,
        .pokemonOffset = 0,
        .trainerScale = 337,
        .trainerOffset = 2,
    },
};
// ===== END src/data/pokemon/pokedex_entries.h =====

static const struct BgTemplate sBgTemplates[] = {
    {
        .bg = 0,
        .charBaseIndex = 0,
        .mapBaseIndex = 5,
        .screenSize = 0,
        .paletteMode = 0,
        .priority = 0,
        .baseTile = 0x0000
    },
    {
        .bg = 1,
        .charBaseIndex = 2,
        .mapBaseIndex = 4,
        .screenSize = 0,
        .paletteMode = 0,
        .priority = 1,
        .baseTile = 0x0000
    },
    {
        .bg = 2,
        .charBaseIndex = 2,
        .mapBaseIndex = 6,
        .screenSize = 0,
        .paletteMode = 0,
        .priority = 2,
        .baseTile = 0x0000
    },
    {
        .bg = 3,
        .charBaseIndex = 0,
        .mapBaseIndex = 7,
        .screenSize = 0,
        .paletteMode = 0,
        .priority = 3,
        .baseTile = 0x0000
    },
};

static const struct WindowTemplate sWindowTemplates[] = {
    {
        .bg = 0,
        .tilemapLeft = 0,
        .tilemapTop = 0,
        .width = 30,
        .height = 2,
        .paletteNum = 15,
        .baseBlock = 0x03c4
    },
    {
        .bg = 0,
        .tilemapLeft = 0,
        .tilemapTop = 18,
        .width = 30,
        .height = 2,
        .paletteNum = 15,
        .baseBlock = 0x0388
    },
    {
        .bg = 255,
        .tilemapLeft = 0,
        .tilemapTop = 0,
        .width = 0,
        .height = 0,
        .paletteNum = 0,
        .baseBlock = 0x0000
    },
};

static const struct PokedexScreenData sDexScreenDataInitialState = {
    .modeSelectItemsAbove = 1,
    .modeSelectWindowId = -1,
    .selectionIconWindowId = -1,
    .dexCountsWindowId = -1,
    .pageSpecies = {-1, -1, -1, -1},
    .categoryMonWindowIds = {-1, -1, -1, -1},
    .categoryMonInfoWindowIds = {-1, -1, -1, -1},
    .numericalOrderWindowId = -1,
    .windowIds = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    .scrollArrowsTaskId = -1,
    .categoryPageCursorTaskId = -1,
};


static const struct WindowTemplate sWindowTemplate_ModeSelect = {
    .bg = 1,
    .tilemapLeft = 1,
    .tilemapTop = 2,
    .width = 20,
    .height = 16,
    .paletteNum = 0,
    .baseBlock = 0x0008
};

static const struct WindowTemplate sWindowTemplate_SelectionIcon = {
    .bg = 1,
    .tilemapLeft = 21,
    .tilemapTop = 11,
    .width = 8,
    .height = 6,
    .paletteNum = 1,
    .baseBlock = 0x0148
};

static const struct WindowTemplate sWindowTemplate_DexCounts = {
    .bg = 1,
    .tilemapLeft = 21,
    .tilemapTop = 2,
    .width = 9,
    .height = 9,
    .paletteNum = 0,
    .baseBlock = 0x0178
};

static const struct ListMenuItem sListMenuItems_KantoDexModeSelect[] = {
    {gText_PokemonList,                  LIST_HEADER},
    {gText_NumericalMode,                DEX_MODE(NUMERICAL_KANTO)},
    {gText_PokemonHabitats,              LIST_HEADER},
    {gText_DexCategory_GrasslandPkmn,    DEX_CATEGORY_GRASSLAND},
    {gText_DexCategory_ForestPkmn,       DEX_CATEGORY_FOREST},
    {gText_DexCategory_WatersEdgePkmn,   DEX_CATEGORY_WATERS_EDGE},
    {gText_DexCategory_SeaPkmn,          DEX_CATEGORY_SEA},
    {gText_DexCategory_CavePkmn,         DEX_CATEGORY_CAVE},
    {gText_DexCategory_MountainPkmn,     DEX_CATEGORY_MOUNTAIN},
    {gText_DexCategory_RoughTerrainPkmn, DEX_CATEGORY_ROUGH_TERRAIN},
    {gText_DexCategory_UrbanPkmn,        DEX_CATEGORY_URBAN},
    {gText_DexCategory_RarePkmn,         DEX_CATEGORY_RARE},
    {gText_Search,                       LIST_HEADER},
    {gText_AToZMode,                     DEX_MODE(ATOZ)},
    {gText_TypeMode,                     DEX_MODE(TYPE)},
    {gText_LightestMode,                 DEX_MODE(LIGHTEST)},
    {gText_SmallestMode,                 DEX_MODE(SMALLEST)},
    {gText_PokedexOther,                 LIST_HEADER},
    {gText_ClosePokedex,                 LIST_CANCEL},
};

static const struct ListMenuTemplate sListMenuTemplate_KantoDexModeSelect = {
    .items = sListMenuItems_KantoDexModeSelect,
    .moveCursorFunc = MoveCursorFunc_DexModeSelect,
    .itemPrintFunc = ItemPrintFunc_DexModeSelect,
    .totalItems = NELEMS(sListMenuItems_KantoDexModeSelect),
    .maxShowed = 9,
    .windowId = 0,
    .header_X = 0,
    .item_X = 12,
    .cursor_X = 4,
    .upText_Y = 2,
    .cursorPal = 1,
    .fillValue = 0,
    .cursorShadowPal = 3,
    .lettersSpacing = 1,
    .itemVerticalPadding = 0,
    .scrollMultiple = 0,
    .fontId = FONT_NORMAL,
    .cursorKind = 0,
};

static const struct ListMenuItem sListMenuItems_NatDexModeSelect[] = {
    {gText_PokemonList,                  LIST_HEADER},
    {gText_NumericalModeKanto,           DEX_MODE(NUMERICAL_KANTO)},
    {gText_NumericalModeNational,        DEX_MODE(NUMERICAL_NATIONAL)},
    {gText_PokemonHabitats,              LIST_HEADER},
    {gText_DexCategory_GrasslandPkmn,    DEX_CATEGORY_GRASSLAND},
    {gText_DexCategory_ForestPkmn,       DEX_CATEGORY_FOREST},
    {gText_DexCategory_WatersEdgePkmn,   DEX_CATEGORY_WATERS_EDGE},
    {gText_DexCategory_SeaPkmn,          DEX_CATEGORY_SEA},
    {gText_DexCategory_CavePkmn,         DEX_CATEGORY_CAVE},
    {gText_DexCategory_MountainPkmn,     DEX_CATEGORY_MOUNTAIN},
    {gText_DexCategory_RoughTerrainPkmn, DEX_CATEGORY_ROUGH_TERRAIN},
    {gText_DexCategory_UrbanPkmn,        DEX_CATEGORY_URBAN},
    {gText_DexCategory_RarePkmn,         DEX_CATEGORY_RARE},
    {gText_Search,                       LIST_HEADER},
    {gText_AToZMode,                     DEX_MODE(ATOZ)},
    {gText_TypeMode,                     DEX_MODE(TYPE)},
    {gText_LightestMode,                 DEX_MODE(LIGHTEST)},
    {gText_SmallestMode,                 DEX_MODE(SMALLEST)},
    {gText_PokedexOther,                 LIST_HEADER},
    {gText_ClosePokedex,                 LIST_CANCEL},
};

static const struct ListMenuTemplate sListMenuTemplate_NatDexModeSelect = {
    .items = sListMenuItems_NatDexModeSelect,
    .moveCursorFunc = MoveCursorFunc_DexModeSelect,
    .itemPrintFunc = ItemPrintFunc_DexModeSelect,
    .totalItems = NELEMS(sListMenuItems_NatDexModeSelect),
    .maxShowed = 9,
    .windowId = 0,
    .header_X = 0,
    .item_X = 12,
    .cursor_X = 4,
    .upText_Y = 2,
    .cursorPal = 1,
    .fillValue = 0,
    .cursorShadowPal = 3,
    .lettersSpacing = 1,
    .itemVerticalPadding = 0,
    .scrollMultiple = 0,
    .fontId = FONT_NORMAL,
    .cursorKind = 0,
};

static const struct ScrollArrowsTemplate sScrollArrowsTemplate_KantoDex = {
    .firstArrowType = 2,
    .firstX = 200,
    .firstY = 19,
    .secondArrowType = 3,
    .secondX = 200,
    .secondY = 141,
    .fullyUpThreshold = 0,
    .fullyDownThreshold = 10,
    .tileTag = 2000,
    .palTag = 0xFFFF,
    .palNum = 1
};

static const struct ScrollArrowsTemplate sScrollArrowsTemplate_NatDex = {
    .firstArrowType = 2,
    .firstX = 200,
    .firstY = 19,
    .secondArrowType = 3,
    .secondX = 200,
    .secondY = 141,
    .fullyUpThreshold = 0,
    .fullyDownThreshold = 11,
    .tileTag = 2000,
    .palTag = 0xFFFF,
    .palNum = 1
};


static const struct PokedexScreenWindowGfx sTopMenuSelectionIconGfxPtrs[] = {
    [DEX_CATEGORY_GRASSLAND] = {
        .tiles = sTopMenuIconTiles_Grassland,
        .pal   = sTopMenuIconPals_Grassland
    },
    [DEX_CATEGORY_FOREST] = {
        .tiles = sTopMenuIconTiles_Forest,
        .pal   = sTopMenuIconPals_Forest
    },
    [DEX_CATEGORY_WATERS_EDGE] = {
        .tiles = sTopMenuIconTiles_WatersEdge,
        .pal   = sTopMenuIconPals_WatersEdge
    },
    [DEX_CATEGORY_SEA] = {
        .tiles = sTopMenuIconTiles_Sea,
        .pal   = sTopMenuIconPals_Sea
    },
    [DEX_CATEGORY_CAVE] = {
        .tiles = sTopMenuIconTiles_Cave,
        .pal   = sTopMenuIconPals_Cave
    },
    [DEX_CATEGORY_MOUNTAIN] = {
        .tiles = sTopMenuIconTiles_Mountain,
        .pal   = sTopMenuIconPals_Mountain
    },
    [DEX_CATEGORY_ROUGH_TERRAIN] = {
        .tiles = sTopMenuIconTiles_RoughTerrain,
        .pal   = sTopMenuIconPals_RoughTerrain
    },
    [DEX_CATEGORY_URBAN] = {
        .tiles = sTopMenuIconTiles_Urban,
        .pal   = sTopMenuIconPals_Urban
    },
    [DEX_CATEGORY_RARE] = {
        .tiles = sTopMenuIconTiles_Rare,
        .pal   = sTopMenuIconPals_Rare
    },
    [DEX_MODE(NUMERICAL_KANTO)] = {
        .tiles = sTopMenuIconTiles_Numerical,
        .pal   = sTopMenuIconPals_Numerical
    },
    [DEX_MODE(ATOZ)] = {
        .tiles = gDexScreen_TopMenuIconTiles_AtoZ,
        .pal   = gDexScreen_TopMenuIconPals_AtoZ
    },
    [DEX_MODE(TYPE)] = {
        .tiles = sTopMenuIconTiles_Type,
        .pal   = sTopMenuIconPals_Type
    },
    [DEX_MODE(LIGHTEST)] = {
        .tiles = sTopMenuIconTiles_Lightest,
        .pal   = sTopMenuIconPals_Lightest
    },
    [DEX_MODE(SMALLEST)] = {
        .tiles = sTopMenuIconTiles_Smallest,
        .pal   = sTopMenuIconPals_Smallest
    },
    [DEX_MODE(NUMERICAL_NATIONAL)] = {
        .tiles = sTopMenuIconTiles_Numerical,
        .pal   = sTopMenuIconPals_Numerical
    },
};

static const struct WindowTemplate sWindowTemplate_OrderedListMenu = {
    .bg = 1,
    .tilemapLeft = 2,
    .tilemapTop = 2,
    .width = 23,
    .height = 16,
    .paletteNum = 0,
    .baseBlock = 0x0008
};

static const struct ListMenuTemplate sListMenuTemplate_OrderedListMenu = {
    .items = sListMenuItems_KantoDexModeSelect,
    .moveCursorFunc = ListMenuDefaultCursorMoveFunc,
    .itemPrintFunc = ItemPrintFunc_OrderedListMenu,
    .totalItems = 0,
    .maxShowed = 9,
    .windowId = 0,
    .header_X = 0,
    .item_X = 56,
    .cursor_X = 4,
    .upText_Y = 2,
    .cursorPal = 1,
    .fillValue = 0,
    .cursorShadowPal = 3,
    .lettersSpacing = 1,
    .itemVerticalPadding = 0,
    .scrollMultiple = 1,
    .fontId = FONT_NORMAL,
    .cursorKind = 0,
};

static const struct ListMenuWindowRect sListMenuRects_OrderedList[] = {
    {
        .x = 0,
        .y = 0,
        .width = 5,
        .height = 16,
        .palNum = 0
    }, {
        .x = 5,
        .y = 0,
        .width = 2,
        .height = 16,
        .palNum = 1
    }, {
        .x = 7,
        .y = 0,
        .width = 8,
        .height = 16,
        .palNum = 0
    }, {
        .x = 15,
        .y = 0,
        .width = 8,
        .height = 16,
        .palNum = 2,
    }, {
        .x = 0xFF,
        .y = 0xFF,
        .width = 0xFF,
        .height = 0xFF,
        .palNum = 0xFF
    }
};

static const struct ScrollArrowsTemplate sDexOrderScrollArrowsTemplate = {
    .firstArrowType = 2,
    .firstX = 200,
    .firstY = 19,
    .secondArrowType = 3,
    .secondX = 200,
    .secondY = 141,
    .fullyUpThreshold = 0,
    .fullyDownThreshold = 0,
    .tileTag = 2000,
    .palTag = 0xFFFF,
    .palNum = 1,
};

static const struct WindowTemplate sWindowTemplate_CategoryMonIcon = {
    .bg = 2,
    .tilemapLeft = 0,
    .tilemapTop = 0,
    .width = 8,
    .height = 8,
    .paletteNum = 0,
    .baseBlock = 0x0000
};

static const struct WindowTemplate sWindowTemplate_CategoryMonInfo = {
    .bg = 1,
    .tilemapLeft = 0,
    .tilemapTop = 0,
    .width = 8,
    .height = 5,
    .paletteNum = 0,
    .baseBlock = 0x0000
};

const struct WindowTemplate sWindowTemplate_DexEntry_MonPic = {
    .bg = 1,
    .tilemapLeft = 19,
    .tilemapTop = 3,
    .width = 8,
    .height = 8,
    .paletteNum = 9,
    .baseBlock = 0x01a8
};

const struct WindowTemplate sWindowTemplate_DexEntry_SpeciesStats = {
    .bg = 1,
    .tilemapLeft = 2,
    .tilemapTop = 3,
    .width = 13,
    .height = 8,
    .paletteNum = 0,
    .baseBlock = 0x01e8
};

const struct WindowTemplate sWindowTemplate_DexEntry_FlavorText = {
    .bg = 1,
    .tilemapLeft = 0,
    .tilemapTop = 11,
    .width = 30,
    .height = 7,
    .paletteNum = 0,
    .baseBlock = 0x0250
};

const struct WindowTemplate sWindowTemplate_AreaMap_MonIcon = {
    .bg = 2,
    .tilemapLeft = 1,
    .tilemapTop = 2,
    .width = 4,
    .height = 4,
    .paletteNum = 10,
    .baseBlock = 0x01a8
};

const struct WindowTemplate sWindowTemplate_AreaMap_SpeciesName = {
    .bg = 2,
    .tilemapLeft = 5,
    .tilemapTop = 2,
    .width = 8,
    .height = 3,
    .paletteNum = 0,
    .baseBlock = 0x01b8
};

const struct WindowTemplate sWindowTemplate_AreaMap_Size = {
    .bg = 2,
    .tilemapLeft = 2,
    .tilemapTop = 7,
    .width = 10,
    .height = 2,
    .paletteNum = 0,
    .baseBlock = 0x01d0
};

const struct WindowTemplate sWindowTemplate_AreaMap_Area = {
    .bg = 2,
    .tilemapLeft = 18,
    .tilemapTop = 2,
    .width = 10,
    .height = 2,
    .paletteNum = 0,
    .baseBlock = 0x01e4
};

const struct WindowTemplate sWindowTemplate_AreaMap_MonTypes = {
    .bg = 2,
    .tilemapLeft = 5,
    .tilemapTop = 5,
    .width = 8,
    .height = 2,
    .paletteNum = 11,
    .baseBlock = 0x01f8
};

const struct WindowTemplate sWindowTemplate_AreaMap_Kanto = {
    .bg = 2,
    .tilemapLeft = 17,
    .tilemapTop = 4,
    .width = 12,
    .height = 9,
    .paletteNum = 0,
    .baseBlock = 0x0208
};

static const struct WindowTemplate sWindowTemplate_AreaMap_OneIsland = {
    .bg = 2,
    .tilemapLeft = 13,
    .tilemapTop = 4,
    .width = 4,
    .height = 3,
    .paletteNum = 0,
    .baseBlock = 0x0274
};

static const struct WindowTemplate sWindowTemplate_AreaMap_TwoIsland = {
    .bg = 2,
    .tilemapLeft = 13,
    .tilemapTop = 7,
    .width = 4,
    .height = 3,
    .paletteNum = 0,
    .baseBlock = 0x0280
};

static const struct WindowTemplate sWindowTemplate_AreaMap_ThreeIsland = {
    .bg = 2,
    .tilemapLeft = 13,
    .tilemapTop = 10,
    .width = 4,
    .height = 3,
    .paletteNum = 0,
    .baseBlock = 0x028c
};

static const struct WindowTemplate sWindowTemplate_AreaMap_FourIsland = {
    .bg = 2,
    .tilemapLeft = 13,
    .tilemapTop = 13,
    .width = 4,
    .height = 4,
    .paletteNum = 0,
    .baseBlock = 0x0298
};

static const struct WindowTemplate sWindowTemplate_AreaMap_FiveIsland = {
    .bg = 2,
    .tilemapLeft = 17,
    .tilemapTop = 13,
    .width = 4,
    .height = 4,
    .paletteNum = 0,
    .baseBlock = 0x02a8
};

static const struct WindowTemplate sWindowTemplate_AreaMap_SixIsland = {
    .bg = 2,
    .tilemapLeft = 21,
    .tilemapTop = 13,
    .width = 4,
    .height = 4,
    .paletteNum = 0,
    .baseBlock = 0x02b8
};

static const struct WindowTemplate sWindowTemplate_AreaMap_SevenIsland = {
    .bg = 2,
    .tilemapLeft = 25,
    .tilemapTop = 13,
    .width = 4,
    .height = 4,
    .paletteNum = 0,
    .baseBlock = 0x02c8
};

struct {
    const struct WindowTemplate * window;
    const u32 * tiles;
} const sAreaMapStructs_SeviiIslands[] = {
    {&sWindowTemplate_AreaMap_OneIsland,   sTilemap_AreaMap_OneIsland},
    {&sWindowTemplate_AreaMap_TwoIsland,   sTilemap_AreaMap_TwoIsland},
    {&sWindowTemplate_AreaMap_ThreeIsland, sTilemap_AreaMap_ThreeIsland},
    {&sWindowTemplate_AreaMap_FourIsland,  sTilemap_AreaMap_FourIsland},
    {&sWindowTemplate_AreaMap_FiveIsland,  sTilemap_AreaMap_FiveIsland},
    {&sWindowTemplate_AreaMap_SixIsland,   sTilemap_AreaMap_SixIsland},
    {&sWindowTemplate_AreaMap_SevenIsland, sTilemap_AreaMap_SevenIsland},
};

static const u16 sCategoryPageIconWindowBg[] = INCBIN_U16("assets/graphics.bin", 0x256680, 0x80);

// Circular window x/y; Rectangular window x/y
static const u8 sPageIconCoords_1Mon[1][4] = {
    {11,  3, 11, 11},
};

static const u8 sPageIconCoords_2Mons[2][4] = {
    { 3,  3, 11,  3},
    {18,  9, 10, 11},
};

static const u8 sPageIconCoords_3Mons[3][4] = {
    { 1,  2,  9,  2},
    {11,  9,  3, 11},
    {21,  3, 21, 11}
};

static const u8 sPageIconCoords_4Mons[4][4] = {
    { 0,  2,  6,  3},
    { 7, 10,  0, 12},
    {15, 10, 22, 11},
    {22,  2, 15,  4}
};

const u8 (*const sCategoryPageIconCoords[])[4] = {
    sPageIconCoords_1Mon,
    sPageIconCoords_2Mons,
    sPageIconCoords_3Mons,
    sPageIconCoords_4Mons,
};

static const u8 *const sDexCategoryNamePtrs[] = {
    gText_DexCategory_GrasslandPkmn,
    gText_DexCategory_ForestPkmn,
    gText_DexCategory_WatersEdgePkmn,
    gText_DexCategory_SeaPkmn,
    gText_DexCategory_CavePkmn,
    gText_DexCategory_MountainPkmn,
    gText_DexCategory_RoughTerrainPkmn,
    gText_DexCategory_UrbanPkmn,
    gText_DexCategory_RarePkmn,
};

const u16 sPalette_Silhouette[] = INCBIN_U16("assets/graphics.bin", 0x256700, 0x20);

static const u8 sDexScreenPageTurnColumns[][30] = {
    {30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30},
    { 5, 11, 17, 23, 29, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30},
    { 2,  5,  8, 11, 14, 17, 20, 23, 26, 29, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30},
    { 2,  3,  5,  7,  9, 11, 13, 15, 17, 19, 21, 23, 25, 27, 29, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30},
    { 2,  4,  5,  7,  8, 10, 11, 13, 14, 16, 17, 19, 20, 22, 23, 25, 26, 28, 29, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30},
    { 1,  2,  3,  4,  7,  8,  9, 10, 11, 12, 13, 15, 16, 17, 19, 20, 21, 23, 24, 25, 27, 28, 29, 30, 30, 30, 30, 30, 30, 30},
    { 1,  2,  3,  4,  5,  7,  8,  9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 20, 21, 22, 23, 25, 26, 27, 28, 29, 30, 30, 30, 30},
    { 1,  2,  3,  4,  5,  6,  7,  8,  9, 11, 12, 13, 14, 15, 16, 17, 18, 19, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 30, 30},
    { 1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30},
    { 0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29},
};

static const struct ScrollArrowsTemplate sScrollArrowsTemplate_CategoryMenu = {
    .firstArrowType = 0,
    .firstX = 16,
    .firstY = 80,
    .secondArrowType = 1,
    .secondX = 224,
    .secondY = 80,
    .fullyUpThreshold = 0,
    .fullyDownThreshold = 0,
    .tileTag = 2000,
    .palTag = 0xFFFF,
    .palNum = 1,
};

const struct CursorStruct sCursorStruct_CategoryPage = {
    .left = 0,
    .top = 160,
    .rowWidth = 64,
    .rowHeight = 40,
    .tileTag = 2002,
    .palTag = 0xFFFF,
    .palNum = 4,
};

// ===== BEGIN src/data/pokemon/pokedex_categories.h =====
static const u16 sDexCategory_GrasslandPkmn_Page1[] = {
    SPECIES_RATTATA,
    SPECIES_RATICATE,
    SPECIES_SENTRET,
    SPECIES_FURRET,
};

static const u16 sDexCategory_GrasslandPkmn_Page2[] = {
    SPECIES_ZIGZAGOON,
    SPECIES_LINOONE,
    SPECIES_POOCHYENA,
    SPECIES_MIGHTYENA,
};

static const u16 sDexCategory_GrasslandPkmn_Page3[] = {
    SPECIES_NIDORAN_F,
    SPECIES_NIDORINA,
    SPECIES_NIDOQUEEN,
};

static const u16 sDexCategory_GrasslandPkmn_Page4[] = {
    SPECIES_NIDORAN_M,
    SPECIES_NIDORINO,
    SPECIES_NIDOKING,
};

static const u16 sDexCategory_GrasslandPkmn_Page5[] = {
    SPECIES_DODUO,
    SPECIES_DODRIO,
    SPECIES_TAILLOW,
    SPECIES_SWELLOW,
};

static const u16 sDexCategory_GrasslandPkmn_Page6[] = {
    SPECIES_TANGELA,
    SPECIES_ROSELIA,
    SPECIES_SUNKERN,
    SPECIES_SUNFLORA,
};

static const u16 sDexCategory_GrasslandPkmn_Page7[] = {
    SPECIES_HOPPIP,
    SPECIES_SKIPLOOM,
    SPECIES_JUMPLUFF,
};

static const u16 sDexCategory_GrasslandPkmn_Page8[] = {
    SPECIES_ODDISH,
    SPECIES_GLOOM,
    SPECIES_VILEPLUME,
    SPECIES_BELLOSSOM,
};

static const u16 sDexCategory_GrasslandPkmn_Page9[] = {
    SPECIES_EKANS,
    SPECIES_ARBOK,
};

static const u16 sDexCategory_GrasslandPkmn_Page10[] = {
    SPECIES_IGGLYBUFF,
    SPECIES_JIGGLYPUFF,
    SPECIES_WIGGLYTUFF,
};

static const u16 sDexCategory_GrasslandPkmn_Page11[] = {
    SPECIES_MAREEP,
    SPECIES_FLAAFFY,
    SPECIES_AMPHAROS,
};

static const u16 sDexCategory_GrasslandPkmn_Page12[] = {
    SPECIES_FARFETCHD,
    SPECIES_LICKITUNG,
};

static const u16 sDexCategory_GrasslandPkmn_Page13[] = {
    SPECIES_SCYTHER,
    SPECIES_SCIZOR,
};

static const u16 sDexCategory_GrasslandPkmn_Page14[] = {
    SPECIES_DROWZEE,
    SPECIES_HYPNO,
    SPECIES_GULPIN,
    SPECIES_SWALOT,
};

static const u16 sDexCategory_GrasslandPkmn_Page15[] = {
    SPECIES_KANGASKHAN,
    SPECIES_GIRAFARIG,
};

static const u16 sDexCategory_GrasslandPkmn_Page16[] = {
    SPECIES_TAUROS,
    SPECIES_MILTANK,
};

static const u16 sDexCategory_GrasslandPkmn_Page17[] = {
    SPECIES_VULPIX,
    SPECIES_NINETALES,
    SPECIES_PONYTA,
    SPECIES_RAPIDASH,
};

static const u16 sDexCategory_GrasslandPkmn_Page18[] = {
    SPECIES_ELEKID,
    SPECIES_ELECTABUZZ,
    SPECIES_ELECTRIKE,
    SPECIES_MANECTRIC,
};

static const u16 sDexCategory_GrasslandPkmn_Page19[] = {
    SPECIES_ZANGOOSE,
    SPECIES_SEVIPER,
};

static const u16 sDexCategory_GrasslandPkmn_Page20[] = {
    SPECIES_PLUSLE,
    SPECIES_MINUN,
};

static const u16 sDexCategory_GrasslandPkmn_Page21[] = {
    SPECIES_GROWLITHE,
    SPECIES_ARCANINE,
};

static const u16 sDexCategory_GrasslandPkmn_Page22[] = {
    SPECIES_CASTFORM,
    SPECIES_CHIMECHO,
};

static const u16 sDexCategory_GrasslandPkmn_Page23[] = {
    SPECIES_BULBASAUR,
    SPECIES_IVYSAUR,
    SPECIES_VENUSAUR,
};

static const u16 sDexCategory_GrasslandPkmn_Page24[] = {
    SPECIES_CHIKORITA,
    SPECIES_BAYLEEF,
    SPECIES_MEGANIUM,
};

static const u16 sDexCategory_GrasslandPkmn_Page25[] = {
    SPECIES_CYNDAQUIL,
    SPECIES_QUILAVA,
    SPECIES_TYPHLOSION,
};

static const u16 sDexCategory_GrasslandPkmn_Page26[] = {
    SPECIES_TORCHIC,
    SPECIES_COMBUSKEN,
    SPECIES_BLAZIKEN,
};

static const u16 sDexCategory_GrasslandPkmn_Page27[] = {
    SPECIES_RAIKOU,
    SPECIES_ENTEI,
    SPECIES_SUICUNE,
};

static const u16 sDexCategory_ForestPkmn_Page1[] = {
    SPECIES_CATERPIE,
    SPECIES_METAPOD,
    SPECIES_BUTTERFREE,
};

static const u16 sDexCategory_ForestPkmn_Page2[] = {
    SPECIES_WEEDLE,
    SPECIES_KAKUNA,
    SPECIES_BEEDRILL,
};

static const u16 sDexCategory_ForestPkmn_Page3[] = {
    SPECIES_WURMPLE,
    SPECIES_SILCOON,
    SPECIES_BEAUTIFLY,
};

static const u16 sDexCategory_ForestPkmn_Page4[] = {
    SPECIES_CASCOON,
    SPECIES_DUSTOX,
};

static const u16 sDexCategory_ForestPkmn_Page5[] = {
    SPECIES_PIDGEY,
    SPECIES_PIDGEOTTO,
    SPECIES_PIDGEOT,
};

static const u16 sDexCategory_ForestPkmn_Page6[] = {
    SPECIES_HOOTHOOT,
    SPECIES_NOCTOWL,
    SPECIES_NATU,
    SPECIES_XATU,
};

static const u16 sDexCategory_ForestPkmn_Page7[] = {
    SPECIES_PICHU,
    SPECIES_PIKACHU,
    SPECIES_RAICHU,
};

static const u16 sDexCategory_ForestPkmn_Page8[] = {
    SPECIES_BELLSPROUT,
    SPECIES_WEEPINBELL,
    SPECIES_VICTREEBEL,
};

static const u16 sDexCategory_ForestPkmn_Page9[] = {
    SPECIES_PARAS,
    SPECIES_PARASECT,
    SPECIES_SHROOMISH,
    SPECIES_BRELOOM,
};

static const u16 sDexCategory_ForestPkmn_Page10[] = {
    SPECIES_SEEDOT,
    SPECIES_NUZLEAF,
    SPECIES_SHIFTRY,
};

static const u16 sDexCategory_ForestPkmn_Page11[] = {
    SPECIES_VENONAT,
    SPECIES_VENOMOTH,
    SPECIES_YANMA,
};

static const u16 sDexCategory_ForestPkmn_Page12[] = {
    SPECIES_LEDYBA,
    SPECIES_LEDIAN,
    SPECIES_SPINARAK,
    SPECIES_ARIADOS,
};

static const u16 sDexCategory_ForestPkmn_Page13[] = {
    SPECIES_NINCADA,
    SPECIES_NINJASK,
    SPECIES_SHEDINJA,
};

static const u16 sDexCategory_ForestPkmn_Page14[] = {
    SPECIES_VOLBEAT,
    SPECIES_ILLUMISE,
};

static const u16 sDexCategory_ForestPkmn_Page15[] = {
    SPECIES_PINECO,
    SPECIES_FORRETRESS,
};

static const u16 sDexCategory_ForestPkmn_Page16[] = {
    SPECIES_SLAKOTH,
    SPECIES_VIGOROTH,
    SPECIES_SLAKING,
};

static const u16 sDexCategory_ForestPkmn_Page17[] = {
    SPECIES_SKITTY,
    SPECIES_DELCATTY,
};

static const u16 sDexCategory_ForestPkmn_Page18[] = {
    SPECIES_MURKROW,
    SPECIES_SNEASEL,
};

static const u16 sDexCategory_ForestPkmn_Page19[] = {
    SPECIES_EXEGGCUTE,
    SPECIES_EXEGGUTOR,
    SPECIES_SUDOWOODO,
};

static const u16 sDexCategory_ForestPkmn_Page20[] = {
    SPECIES_AIPOM,
    SPECIES_STANTLER,
    SPECIES_KECLEON,
};

static const u16 sDexCategory_ForestPkmn_Page21[] = {
    SPECIES_PINSIR,
    SPECIES_HERACROSS,
};

static const u16 sDexCategory_ForestPkmn_Page22[] = {
    SPECIES_SWABLU,
    SPECIES_ALTARIA,
    SPECIES_TROPIUS,
};

static const u16 sDexCategory_ForestPkmn_Page23[] = {
    SPECIES_DUSKULL,
    SPECIES_DUSCLOPS,
};

static const u16 sDexCategory_ForestPkmn_Page24[] = {
    SPECIES_TOGEPI,
    SPECIES_TOGETIC,
};

static const u16 sDexCategory_ForestPkmn_Page25[] = {
    SPECIES_TREECKO,
    SPECIES_GROVYLE,
    SPECIES_SCEPTILE,
};

static const u16 sDexCategory_ForestPkmn_Page26[] = {
    SPECIES_CELEBI,
};

static const u16 sDexCategory_WatersEdgePkmn_Page1[] = {
    SPECIES_GOLDEEN,
    SPECIES_SEAKING,
};

static const u16 sDexCategory_WatersEdgePkmn_Page2[] = {
    SPECIES_MAGIKARP,
    SPECIES_GYARADOS,
    SPECIES_KRABBY,
    SPECIES_KINGLER,
};

static const u16 sDexCategory_WatersEdgePkmn_Page3[] = {
    SPECIES_CORPHISH,
    SPECIES_CRAWDAUNT,
    SPECIES_BARBOACH,
    SPECIES_WHISCASH,
};

static const u16 sDexCategory_WatersEdgePkmn_Page4[] = {
    SPECIES_LOTAD,
    SPECIES_LOMBRE,
    SPECIES_LUDICOLO,
};

static const u16 sDexCategory_WatersEdgePkmn_Page5[] = {
    SPECIES_SURSKIT,
    SPECIES_MASQUERAIN,
};

static const u16 sDexCategory_WatersEdgePkmn_Page6[] = {
    SPECIES_PSYDUCK,
    SPECIES_GOLDUCK,
    SPECIES_WOOPER,
    SPECIES_QUAGSIRE,
};

static const u16 sDexCategory_WatersEdgePkmn_Page7[] = {
    SPECIES_POLIWAG,
    SPECIES_POLIWHIRL,
    SPECIES_POLIWRATH,
    SPECIES_POLITOED,
};

static const u16 sDexCategory_WatersEdgePkmn_Page8[] = {
    SPECIES_AZURILL,
    SPECIES_MARILL,
    SPECIES_AZUMARILL,
};

static const u16 sDexCategory_WatersEdgePkmn_Page9[] = {
    SPECIES_SLOWPOKE,
    SPECIES_SLOWBRO,
    SPECIES_SLOWKING,
};

static const u16 sDexCategory_WatersEdgePkmn_Page10[] = {
    SPECIES_FEEBAS,
    SPECIES_MILOTIC,
};

static const u16 sDexCategory_WatersEdgePkmn_Page11[] = {
    SPECIES_ANORITH,
    SPECIES_ARMALDO,
};

static const u16 sDexCategory_WatersEdgePkmn_Page12[] = {
    SPECIES_DRATINI,
    SPECIES_DRAGONAIR,
    SPECIES_DRAGONITE,
};

static const u16 sDexCategory_WatersEdgePkmn_Page13[] = {
    SPECIES_SQUIRTLE,
    SPECIES_WARTORTLE,
    SPECIES_BLASTOISE,
};

static const u16 sDexCategory_WatersEdgePkmn_Page14[] = {
    SPECIES_TOTODILE,
    SPECIES_CROCONAW,
    SPECIES_FERALIGATR,
};

static const u16 sDexCategory_WatersEdgePkmn_Page15[] = {
    SPECIES_MUDKIP,
    SPECIES_MARSHTOMP,
    SPECIES_SWAMPERT,
};

static const u16 sDexCategory_WatersEdgePkmn_Page16[] = {
    SPECIES_LATIAS,
    SPECIES_LATIOS,
};

static const u16 sDexCategory_SeaPkmn_Page1[] = {
    SPECIES_TENTACOOL,
    SPECIES_TENTACRUEL,
};

static const u16 sDexCategory_SeaPkmn_Page2[] = {
    SPECIES_WINGULL,
    SPECIES_PELIPPER,
};

static const u16 sDexCategory_SeaPkmn_Page3[] = {
    SPECIES_STARYU,
    SPECIES_STARMIE,
};

static const u16 sDexCategory_SeaPkmn_Page4[] = {
    SPECIES_CHINCHOU,
    SPECIES_LANTURN,
    SPECIES_REMORAID,
    SPECIES_OCTILLERY,
};

static const u16 sDexCategory_SeaPkmn_Page5[] = {
    SPECIES_SHELLDER,
    SPECIES_CLOYSTER,
};

static const u16 sDexCategory_SeaPkmn_Page6[] = {
    SPECIES_CLAMPERL,
    SPECIES_HUNTAIL,
    SPECIES_GOREBYSS,
};

static const u16 sDexCategory_SeaPkmn_Page7[] = {
    SPECIES_QWILFISH,
    SPECIES_CORSOLA,
    SPECIES_MANTINE,
    SPECIES_LUVDISC,
};

static const u16 sDexCategory_SeaPkmn_Page8[] = {
    SPECIES_SEEL,
    SPECIES_DEWGONG,
};

static const u16 sDexCategory_SeaPkmn_Page9[] = {
    SPECIES_SPHEAL,
    SPECIES_SEALEO,
    SPECIES_WALREIN,
};

static const u16 sDexCategory_SeaPkmn_Page10[] = {
    SPECIES_CARVANHA,
    SPECIES_SHARPEDO,
    SPECIES_WAILMER,
    SPECIES_WAILORD,
};

static const u16 sDexCategory_SeaPkmn_Page11[] = {
    SPECIES_HORSEA,
    SPECIES_SEADRA,
    SPECIES_KINGDRA,
};

static const u16 sDexCategory_SeaPkmn_Page12[] = {
    SPECIES_RELICANTH,
};

static const u16 sDexCategory_SeaPkmn_Page13[] = {
    SPECIES_LAPRAS,
};

static const u16 sDexCategory_SeaPkmn_Page14[] = {
    SPECIES_OMANYTE,
    SPECIES_OMASTAR,
    SPECIES_KABUTO,
    SPECIES_KABUTOPS,
};

static const u16 sDexCategory_SeaPkmn_Page15[] = {
    SPECIES_LILEEP,
    SPECIES_CRADILY,
};

static const u16 sDexCategory_SeaPkmn_Page16[] = {
    SPECIES_KYOGRE,
};

static const u16 sDexCategory_CavePkmn_Page1[] = {
    SPECIES_ZUBAT,
    SPECIES_GOLBAT,
    SPECIES_CROBAT,
};

static const u16 sDexCategory_CavePkmn_Page2[] = {
    SPECIES_DIGLETT,
    SPECIES_DUGTRIO,
    SPECIES_ONIX,
    SPECIES_STEELIX,
};

static const u16 sDexCategory_CavePkmn_Page3[] = {
    SPECIES_SWINUB,
    SPECIES_PILOSWINE,
    SPECIES_SNORUNT,
    SPECIES_GLALIE,
};

static const u16 sDexCategory_CavePkmn_Page4[] = {
    SPECIES_WHISMUR,
    SPECIES_LOUDRED,
    SPECIES_EXPLOUD,
};

static const u16 sDexCategory_CavePkmn_Page5[] = {
    SPECIES_MISDREAVUS,
    SPECIES_DUNSPARCE,
    SPECIES_NOSEPASS,
};

static const u16 sDexCategory_CavePkmn_Page6[] = {
    SPECIES_SABLEYE,
    SPECIES_MAWILE,
};

static const u16 sDexCategory_CavePkmn_Page7[] = {
    SPECIES_GASTLY,
    SPECIES_HAUNTER,
    SPECIES_GENGAR,
};

static const u16 sDexCategory_CavePkmn_Page8[] = {
    SPECIES_WYNAUT,
    SPECIES_WOBBUFFET,
};

static const u16 sDexCategory_CavePkmn_Page9[] = {
    SPECIES_LUNATONE,
    SPECIES_SOLROCK,
};

static const u16 sDexCategory_CavePkmn_Page10[] = {
    SPECIES_REGIROCK,
    SPECIES_REGICE,
    SPECIES_REGISTEEL,
};

static const u16 sDexCategory_MountainPkmn_Page1[] = {
    SPECIES_GEODUDE,
    SPECIES_GRAVELER,
    SPECIES_GOLEM,
};

static const u16 sDexCategory_MountainPkmn_Page2[] = {
    SPECIES_MANKEY,
    SPECIES_PRIMEAPE,
    SPECIES_SPOINK,
    SPECIES_GRUMPIG,
};

static const u16 sDexCategory_MountainPkmn_Page3[] = {
    SPECIES_MACHOP,
    SPECIES_MACHOKE,
    SPECIES_MACHAMP,
};

static const u16 sDexCategory_MountainPkmn_Page4[] = {
    SPECIES_CLEFFA,
    SPECIES_CLEFAIRY,
    SPECIES_CLEFABLE,
};

static const u16 sDexCategory_MountainPkmn_Page5[] = {
    SPECIES_CUBONE,
    SPECIES_MAROWAK,
};

static const u16 sDexCategory_MountainPkmn_Page6[] = {
    SPECIES_SLUGMA,
    SPECIES_MAGCARGO,
    SPECIES_NUMEL,
    SPECIES_CAMERUPT,
};

static const u16 sDexCategory_MountainPkmn_Page7[] = {
    SPECIES_MAKUHITA,
    SPECIES_HARIYAMA,
    SPECIES_MEDITITE,
    SPECIES_MEDICHAM,
};

static const u16 sDexCategory_MountainPkmn_Page8[] = {
    SPECIES_SHUCKLE,
    SPECIES_TEDDIURSA,
    SPECIES_URSARING,
    SPECIES_DELIBIRD,
};

static const u16 sDexCategory_MountainPkmn_Page9[] = {
    SPECIES_GLIGAR,
    SPECIES_SPINDA,
};

static const u16 sDexCategory_MountainPkmn_Page10[] = {
    SPECIES_MAGBY,
    SPECIES_MAGMAR,
    SPECIES_TORKOAL,
};

static const u16 sDexCategory_MountainPkmn_Page11[] = {
    SPECIES_ARON,
    SPECIES_LAIRON,
    SPECIES_AGGRON,
};

static const u16 sDexCategory_MountainPkmn_Page12[] = {
    SPECIES_LARVITAR,
    SPECIES_PUPITAR,
    SPECIES_TYRANITAR,
};

static const u16 sDexCategory_MountainPkmn_Page13[] = {
    SPECIES_SNORLAX,
};

static const u16 sDexCategory_MountainPkmn_Page14[] = {
    SPECIES_ABSOL,
};

static const u16 sDexCategory_MountainPkmn_Page15[] = {
    SPECIES_AERODACTYL,
};

static const u16 sDexCategory_MountainPkmn_Page16[] = {
    SPECIES_CHARMANDER,
    SPECIES_CHARMELEON,
    SPECIES_CHARIZARD,
};

static const u16 sDexCategory_MountainPkmn_Page17[] = {
    SPECIES_JIRACHI,
};

static const u16 sDexCategory_RoughTerrainPkmn_Page1[] = {
    SPECIES_SPEAROW,
    SPECIES_FEAROW,
};

static const u16 sDexCategory_RoughTerrainPkmn_Page2[] = {
    SPECIES_SANDSHREW,
    SPECIES_SANDSLASH,
    SPECIES_RHYHORN,
    SPECIES_RHYDON,
};

static const u16 sDexCategory_RoughTerrainPkmn_Page3[] = {
    SPECIES_MAGNEMITE,
    SPECIES_MAGNETON,
};

static const u16 sDexCategory_RoughTerrainPkmn_Page4[] = {
    SPECIES_HOUNDOUR,
    SPECIES_HOUNDOOM,
    SPECIES_PHANPY,
    SPECIES_DONPHAN,
};

static const u16 sDexCategory_RoughTerrainPkmn_Page5[] = {
    SPECIES_CACNEA,
    SPECIES_CACTURNE,
};

static const u16 sDexCategory_RoughTerrainPkmn_Page6[] = {
    SPECIES_TRAPINCH,
    SPECIES_VIBRAVA,
    SPECIES_FLYGON,
};

static const u16 sDexCategory_RoughTerrainPkmn_Page7[] = {
    SPECIES_SKARMORY,
};

static const u16 sDexCategory_RoughTerrainPkmn_Page8[] = {
    SPECIES_BALTOY,
    SPECIES_CLAYDOL,
};

static const u16 sDexCategory_RoughTerrainPkmn_Page9[] = {
    SPECIES_BAGON,
    SPECIES_SHELGON,
    SPECIES_SALAMENCE,
};

static const u16 sDexCategory_RoughTerrainPkmn_Page10[] = {
    SPECIES_BELDUM,
    SPECIES_METANG,
    SPECIES_METAGROSS,
};

static const u16 sDexCategory_RoughTerrainPkmn_Page11[] = {
    SPECIES_GROUDON,
};

static const u16 sDexCategory_UrbanPkmn_Page1[] = {
    SPECIES_MEOWTH,
    SPECIES_PERSIAN,
    SPECIES_SNUBBULL,
    SPECIES_GRANBULL,
};

static const u16 sDexCategory_UrbanPkmn_Page2[] = {
    SPECIES_GRIMER,
    SPECIES_MUK,
    SPECIES_KOFFING,
    SPECIES_WEEZING,
};

static const u16 sDexCategory_UrbanPkmn_Page3[] = {
    SPECIES_SHUPPET,
    SPECIES_BANETTE,
};

static const u16 sDexCategory_UrbanPkmn_Page4[] = {
    SPECIES_ABRA,
    SPECIES_KADABRA,
    SPECIES_ALAKAZAM,
};

static const u16 sDexCategory_UrbanPkmn_Page5[] = {
    SPECIES_RALTS,
    SPECIES_KIRLIA,
    SPECIES_GARDEVOIR,
};

static const u16 sDexCategory_UrbanPkmn_Page6[] = {
    SPECIES_SMOOCHUM,
    SPECIES_JYNX,
    SPECIES_MR_MIME,
    SPECIES_SMEARGLE,
};

static const u16 sDexCategory_UrbanPkmn_Page7[] = {
    SPECIES_TYROGUE,
    SPECIES_HITMONLEE,
    SPECIES_HITMONCHAN,
    SPECIES_HITMONTOP,
};

static const u16 sDexCategory_UrbanPkmn_Page8[] = {
    SPECIES_CHANSEY,
    SPECIES_BLISSEY,
};

static const u16 sDexCategory_UrbanPkmn_Page9[] = {
    SPECIES_VOLTORB,
    SPECIES_ELECTRODE,
    SPECIES_PORYGON,
    SPECIES_PORYGON2,
};

static const u16 sDexCategory_UrbanPkmn_Page10[] = {
    SPECIES_DITTO,
};

static const u16 sDexCategory_UrbanPkmn_Page11[] = {
    SPECIES_EEVEE,
    SPECIES_VAPOREON,
    SPECIES_JOLTEON,
    SPECIES_FLAREON,
};

static const u16 sDexCategory_UrbanPkmn_Page12[] = {
    SPECIES_ESPEON,
    SPECIES_UMBREON,
};

static const u16 sDexCategory_RarePkmn_Page1[] = {
    SPECIES_UNOWN,
};

static const u16 sDexCategory_RarePkmn_Page2[] = {
    SPECIES_ARTICUNO,
    SPECIES_ZAPDOS,
    SPECIES_MOLTRES,
};

static const u16 sDexCategory_RarePkmn_Page3[] = {
    SPECIES_LUGIA,
};

static const u16 sDexCategory_RarePkmn_Page4[] = {
    SPECIES_HO_OH,
};

static const u16 sDexCategory_RarePkmn_Page5[] = {
    SPECIES_RAYQUAZA,
};

static const u16 sDexCategory_RarePkmn_Page6[] = {
    SPECIES_DEOXYS,
};

static const u16 sDexCategory_RarePkmn_Page7[] = {
    SPECIES_MEWTWO,
};

static const u16 sDexCategory_RarePkmn_Page8[] = {
    SPECIES_MEW,
};

#define DEX_CATEGORY(name){sDexCategory_##name, NELEMS(sDexCategory_##name)}

static const struct PokedexCategoryPage sDexCategory_GrasslandPkmn[] = {
    DEX_CATEGORY(GrasslandPkmn_Page1),
    DEX_CATEGORY(GrasslandPkmn_Page2),
    DEX_CATEGORY(GrasslandPkmn_Page3),
    DEX_CATEGORY(GrasslandPkmn_Page4),
    DEX_CATEGORY(GrasslandPkmn_Page5),
    DEX_CATEGORY(GrasslandPkmn_Page6),
    DEX_CATEGORY(GrasslandPkmn_Page7),
    DEX_CATEGORY(GrasslandPkmn_Page8),
    DEX_CATEGORY(GrasslandPkmn_Page9),
    DEX_CATEGORY(GrasslandPkmn_Page10),
    DEX_CATEGORY(GrasslandPkmn_Page11),
    DEX_CATEGORY(GrasslandPkmn_Page12),
    DEX_CATEGORY(GrasslandPkmn_Page13),
    DEX_CATEGORY(GrasslandPkmn_Page14),
    DEX_CATEGORY(GrasslandPkmn_Page15),
    DEX_CATEGORY(GrasslandPkmn_Page16),
    DEX_CATEGORY(GrasslandPkmn_Page17),
    DEX_CATEGORY(GrasslandPkmn_Page18),
    DEX_CATEGORY(GrasslandPkmn_Page19),
    DEX_CATEGORY(GrasslandPkmn_Page20),
    DEX_CATEGORY(GrasslandPkmn_Page21),
    DEX_CATEGORY(GrasslandPkmn_Page22),
    DEX_CATEGORY(GrasslandPkmn_Page23),
    DEX_CATEGORY(GrasslandPkmn_Page24),
    DEX_CATEGORY(GrasslandPkmn_Page25),
    DEX_CATEGORY(GrasslandPkmn_Page26),
    DEX_CATEGORY(GrasslandPkmn_Page27),
};

static const struct PokedexCategoryPage sDexCategory_ForestPkmn[] = {
    DEX_CATEGORY(ForestPkmn_Page1),
    DEX_CATEGORY(ForestPkmn_Page2),
    DEX_CATEGORY(ForestPkmn_Page3),
    DEX_CATEGORY(ForestPkmn_Page4),
    DEX_CATEGORY(ForestPkmn_Page5),
    DEX_CATEGORY(ForestPkmn_Page6),
    DEX_CATEGORY(ForestPkmn_Page7),
    DEX_CATEGORY(ForestPkmn_Page8),
    DEX_CATEGORY(ForestPkmn_Page9),
    DEX_CATEGORY(ForestPkmn_Page10),
    DEX_CATEGORY(ForestPkmn_Page11),
    DEX_CATEGORY(ForestPkmn_Page12),
    DEX_CATEGORY(ForestPkmn_Page13),
    DEX_CATEGORY(ForestPkmn_Page14),
    DEX_CATEGORY(ForestPkmn_Page15),
    DEX_CATEGORY(ForestPkmn_Page16),
    DEX_CATEGORY(ForestPkmn_Page17),
    DEX_CATEGORY(ForestPkmn_Page18),
    DEX_CATEGORY(ForestPkmn_Page19),
    DEX_CATEGORY(ForestPkmn_Page20),
    DEX_CATEGORY(ForestPkmn_Page21),
    DEX_CATEGORY(ForestPkmn_Page22),
    DEX_CATEGORY(ForestPkmn_Page23),
    DEX_CATEGORY(ForestPkmn_Page24),
    DEX_CATEGORY(ForestPkmn_Page25),
    DEX_CATEGORY(ForestPkmn_Page26),
};

static const struct PokedexCategoryPage sDexCategory_WatersEdgePkmn[] = {
    DEX_CATEGORY(WatersEdgePkmn_Page1),
    DEX_CATEGORY(WatersEdgePkmn_Page2),
    DEX_CATEGORY(WatersEdgePkmn_Page3),
    DEX_CATEGORY(WatersEdgePkmn_Page4),
    DEX_CATEGORY(WatersEdgePkmn_Page5),
    DEX_CATEGORY(WatersEdgePkmn_Page6),
    DEX_CATEGORY(WatersEdgePkmn_Page7),
    DEX_CATEGORY(WatersEdgePkmn_Page8),
    DEX_CATEGORY(WatersEdgePkmn_Page9),
    DEX_CATEGORY(WatersEdgePkmn_Page10),
    DEX_CATEGORY(WatersEdgePkmn_Page11),
    DEX_CATEGORY(WatersEdgePkmn_Page12),
    DEX_CATEGORY(WatersEdgePkmn_Page13),
    DEX_CATEGORY(WatersEdgePkmn_Page14),
    DEX_CATEGORY(WatersEdgePkmn_Page15),
    DEX_CATEGORY(WatersEdgePkmn_Page16),
};

static const struct PokedexCategoryPage sDexCategory_SeaPkmn[] = {
    DEX_CATEGORY(SeaPkmn_Page1),
    DEX_CATEGORY(SeaPkmn_Page2),
    DEX_CATEGORY(SeaPkmn_Page3),
    DEX_CATEGORY(SeaPkmn_Page4),
    DEX_CATEGORY(SeaPkmn_Page5),
    DEX_CATEGORY(SeaPkmn_Page6),
    DEX_CATEGORY(SeaPkmn_Page7),
    DEX_CATEGORY(SeaPkmn_Page8),
    DEX_CATEGORY(SeaPkmn_Page9),
    DEX_CATEGORY(SeaPkmn_Page10),
    DEX_CATEGORY(SeaPkmn_Page11),
    DEX_CATEGORY(SeaPkmn_Page12),
    DEX_CATEGORY(SeaPkmn_Page13),
    DEX_CATEGORY(SeaPkmn_Page14),
    DEX_CATEGORY(SeaPkmn_Page15),
    DEX_CATEGORY(SeaPkmn_Page16),
};

static const struct PokedexCategoryPage sDexCategory_CavePkmn[] = {
    DEX_CATEGORY(CavePkmn_Page1),
    DEX_CATEGORY(CavePkmn_Page2),
    DEX_CATEGORY(CavePkmn_Page3),
    DEX_CATEGORY(CavePkmn_Page4),
    DEX_CATEGORY(CavePkmn_Page5),
    DEX_CATEGORY(CavePkmn_Page6),
    DEX_CATEGORY(CavePkmn_Page7),
    DEX_CATEGORY(CavePkmn_Page8),
    DEX_CATEGORY(CavePkmn_Page9),
    DEX_CATEGORY(CavePkmn_Page10),
};

static const struct PokedexCategoryPage sDexCategory_MountainPkmn[] = {
    DEX_CATEGORY(MountainPkmn_Page1),
    DEX_CATEGORY(MountainPkmn_Page2),
    DEX_CATEGORY(MountainPkmn_Page3),
    DEX_CATEGORY(MountainPkmn_Page4),
    DEX_CATEGORY(MountainPkmn_Page5),
    DEX_CATEGORY(MountainPkmn_Page6),
    DEX_CATEGORY(MountainPkmn_Page7),
    DEX_CATEGORY(MountainPkmn_Page8),
    DEX_CATEGORY(MountainPkmn_Page9),
    DEX_CATEGORY(MountainPkmn_Page10),
    DEX_CATEGORY(MountainPkmn_Page11),
    DEX_CATEGORY(MountainPkmn_Page12),
    DEX_CATEGORY(MountainPkmn_Page13),
    DEX_CATEGORY(MountainPkmn_Page14),
    DEX_CATEGORY(MountainPkmn_Page15),
    DEX_CATEGORY(MountainPkmn_Page16),
    DEX_CATEGORY(MountainPkmn_Page17),
};

static const struct PokedexCategoryPage sDexCategory_RoughTerrainPkmn[] = {
    DEX_CATEGORY(RoughTerrainPkmn_Page1),
    DEX_CATEGORY(RoughTerrainPkmn_Page2),
    DEX_CATEGORY(RoughTerrainPkmn_Page3),
    DEX_CATEGORY(RoughTerrainPkmn_Page4),
    DEX_CATEGORY(RoughTerrainPkmn_Page5),
    DEX_CATEGORY(RoughTerrainPkmn_Page6),
    DEX_CATEGORY(RoughTerrainPkmn_Page7),
    DEX_CATEGORY(RoughTerrainPkmn_Page8),
    DEX_CATEGORY(RoughTerrainPkmn_Page9),
    DEX_CATEGORY(RoughTerrainPkmn_Page10),
    DEX_CATEGORY(RoughTerrainPkmn_Page11),
};

static const struct PokedexCategoryPage sDexCategory_UrbanPkmn[] = {
    DEX_CATEGORY(UrbanPkmn_Page1),
    DEX_CATEGORY(UrbanPkmn_Page2),
    DEX_CATEGORY(UrbanPkmn_Page3),
    DEX_CATEGORY(UrbanPkmn_Page4),
    DEX_CATEGORY(UrbanPkmn_Page5),
    DEX_CATEGORY(UrbanPkmn_Page6),
    DEX_CATEGORY(UrbanPkmn_Page7),
    DEX_CATEGORY(UrbanPkmn_Page8),
    DEX_CATEGORY(UrbanPkmn_Page9),
    DEX_CATEGORY(UrbanPkmn_Page10),
    DEX_CATEGORY(UrbanPkmn_Page11),
    DEX_CATEGORY(UrbanPkmn_Page12),
};

static const struct PokedexCategoryPage sDexCategory_RarePkmn[] = {
    DEX_CATEGORY(RarePkmn_Page1),
    DEX_CATEGORY(RarePkmn_Page2),
    DEX_CATEGORY(RarePkmn_Page3),
    DEX_CATEGORY(RarePkmn_Page4),
    DEX_CATEGORY(RarePkmn_Page5),
    DEX_CATEGORY(RarePkmn_Page6),
    DEX_CATEGORY(RarePkmn_Page7),
    DEX_CATEGORY(RarePkmn_Page8),
};

struct {
    const struct PokedexCategoryPage * page;
    u8 count;
} const gDexCategories[] = {
    DEX_CATEGORY(GrasslandPkmn),
    DEX_CATEGORY(ForestPkmn),
    DEX_CATEGORY(WatersEdgePkmn),
    DEX_CATEGORY(SeaPkmn),
    DEX_CATEGORY(CavePkmn),
    DEX_CATEGORY(MountainPkmn),
    DEX_CATEGORY(RoughTerrainPkmn),
    DEX_CATEGORY(UrbanPkmn),
    DEX_CATEGORY(RarePkmn),
};
// ===== END src/data/pokemon/pokedex_categories.h =====

void VBlankCB(void)
{
    LoadOam();
    ProcessSpriteCopyRequests();
    TransferPlttBuffer();
}

void CB2_PokedexScreen(void)
{
    if (!gPaletteFade.active || IsDma3ManagerBusyWithBgCopy())
    {
        RunTasks();
        RunTextPrinters();
        AnimateSprites();
        BuildOamBuffer();
    }
    else
    {
        UpdatePaletteFade();
    }
}

void DexScreen_LoadResources(void)
{
    bool8 natDex;
    u8 taskId;

    natDex = IsNationalPokedexEnabled();
    m4aSoundVSyncOff();
    SetVBlankCallback(NULL);
    ResetPaletteFade();
    ResetSpriteData();
    ResetTasks();
    ScanlineEffect_Stop();
    ResetBgsAndClearDma3BusyFlags(TRUE);
    InitBgsFromTemplates(0, sBgTemplates, NELEMS(sBgTemplates));
    SetBgTilemapBuffer(3, (u16 *)Alloc(BG_SCREEN_SIZE));
    SetBgTilemapBuffer(2, (u16 *)Alloc(BG_SCREEN_SIZE));
    SetBgTilemapBuffer(1, (u16 *)Alloc(BG_SCREEN_SIZE));
    SetBgTilemapBuffer(0, (u16 *)Alloc(BG_SCREEN_SIZE));
    if (natDex)
        DecompressAndLoadBgGfxUsingHeap(3, (void *)sNatDexTiles, BG_SCREEN_SIZE, 0, 0);
    else
        DecompressAndLoadBgGfxUsingHeap(3, (void *)sKantoDexTiles, BG_SCREEN_SIZE, 0, 0);
    InitWindows(sWindowTemplates);
    DeactivateAllTextPrinters();
    m4aSoundVSyncOn();
    SetVBlankCallback(VBlankCB);
    EnableInterrupts(INTR_FLAG_VBLANK);
    taskId = CreateTask(Task_PokedexScreen, 0);
    sPokedexScreenData = Alloc(sizeof(struct PokedexScreenData));
    *sPokedexScreenData = sDexScreenDataInitialState;
    sPokedexScreenData->taskId = taskId;
    sPokedexScreenData->listItems = Alloc(NATIONAL_DEX_COUNT * sizeof(struct ListMenuItem));
    sPokedexScreenData->numSeenNational = DexScreen_GetDexCount(FLAG_GET_SEEN, 1);
    sPokedexScreenData->numOwnedNational = DexScreen_GetDexCount(FLAG_GET_CAUGHT, 1);
    sPokedexScreenData->numSeenKanto = DexScreen_GetDexCount(FLAG_GET_SEEN, 0);
    sPokedexScreenData->numOwnedKanto = DexScreen_GetDexCount(FLAG_GET_CAUGHT, 0);
    SetBGMVolume_SuppressHelpSystemReduction(0x80);
    ChangeBgX(0, 0, 0);
    ChangeBgY(0, 0, 0);
    ChangeBgX(1, 0, 0);
    ChangeBgY(1, 0, 0);
    ChangeBgX(2, 0, 0);
    ChangeBgY(2, 0, 0);
    ChangeBgX(3, 0, 0);
    ChangeBgY(3, 0, 0);
    gPaletteFade.bufferTransferDisabled = TRUE;
    if (natDex)
        LoadPalette(sNationalDexPalette, BG_PLTT_ID(0), sizeof(sNationalDexPalette));
    else
        LoadPalette(sKantoDexPalette, BG_PLTT_ID(0), sizeof(sKantoDexPalette));
    FillBgTilemapBufferRect(3, 0x001, 0,  0, 32, 32, 0);
    FillBgTilemapBufferRect(2, 0x000, 0,  0, 32, 32, 17);
    FillBgTilemapBufferRect(1, 0x000, 0,  0, 32, 32, 17);
    FillBgTilemapBufferRect(0, 0x003, 0,  0, 32,  2, 15);
    FillBgTilemapBufferRect(0, 0x000, 0,  2, 32, 16, 17);
    FillBgTilemapBufferRect(0, 0x003, 0, 18, 32,  2, 15);
}

void CB2_OpenPokedexFromStartMenu(void)
{
    DexScreen_LoadResources();
    ClearGpuRegBits(REG_OFFSET_DISPCNT, DISPCNT_WIN0_ON | DISPCNT_WIN1_ON);
    SetGpuReg(REG_OFFSET_BLDCNT, 0);
    SetGpuReg(REG_OFFSET_BLDALPHA, 0);
    SetGpuReg(REG_OFFSET_BLDY, 0);
    SetMainCallback2(CB2_PokedexScreen);
    SetHelpContext(HELPCONTEXT_POKEDEX);
}

#define FREE_IF_NOT_NULL(ptr0) ({ void *ptr = (ptr0); if (ptr) Free(ptr); })

bool8 DoClosePokedex(void)
{
    switch (gMain.state)
    {
    case 0:
        BeginNormalPaletteFade(PALETTES_ALL, 0, 0, 16, RGB_BLACK);
        gMain.state++;
        return FALSE;
    case 1:
        if (!gPaletteFade.active)
            gMain.state = 2;
        else
            UpdatePaletteFade();
        return FALSE;
    case 2:
        FREE_IF_NOT_NULL(sPokedexScreenData->listItems);
        FREE_IF_NOT_NULL(sPokedexScreenData);
        FreeAllWindowBuffers();
        FREE_IF_NOT_NULL(GetBgTilemapBuffer(0));
        FREE_IF_NOT_NULL(GetBgTilemapBuffer(1));
        FREE_IF_NOT_NULL(GetBgTilemapBuffer(2));
        FREE_IF_NOT_NULL(GetBgTilemapBuffer(3));
        BGMVolumeMax_EnableHelpSystemReduction();
        break;
    }
    return TRUE;
}

void CB2_ClosePokedex(void)
{
    if (DoClosePokedex())
    {
        SetGpuRegBits(REG_OFFSET_DISPCNT, DISPCNT_WIN0_ON | DISPCNT_WIN1_ON);
        SetMainCallback2(CB2_ReturnToFieldWithOpenMenu);
    }
}

static void Task_PokedexScreen(u8 taskId)
{
    int i;
    switch (sPokedexScreenData->state)
    {
    case 0:
        sPokedexScreenData->unlockedCategories = 0;
        for (i = 0; i < 9; i++)
            sPokedexScreenData->unlockedCategories |= (DexScreen_IsCategoryUnlocked(i) << i);
        sPokedexScreenData->state = 2;
        break;
    case 1:
        RemoveScrollIndicatorArrowPair(sPokedexScreenData->scrollArrowsTaskId);
        DexScreen_RemoveWindow(&sPokedexScreenData->modeSelectWindowId);
        DexScreen_RemoveWindow(&sPokedexScreenData->selectionIconWindowId);
        DexScreen_RemoveWindow(&sPokedexScreenData->dexCountsWindowId);
        SetMainCallback2(CB2_ClosePokedex);
        DestroyTask(taskId);
        break;
    case 2:
        DexScreen_InitGfxForTopMenu();
        sPokedexScreenData->state = 3;
        break;
    case 3:
        CopyBgTilemapBufferToVram(3);
        CopyBgTilemapBufferToVram(2);
        CopyBgTilemapBufferToVram(1);
        CopyBgTilemapBufferToVram(0);
        sPokedexScreenData->state = 4;
        break;
    case 4:
        ShowBg(3);
        ShowBg(2);
        ShowBg(1);
        ShowBg(0);
        if (gPaletteFade.bufferTransferDisabled)
        {
            gPaletteFade.bufferTransferDisabled = FALSE;
            BeginNormalPaletteFade(PALETTES_ALL, 0, 0, 0, RGB_WHITEALPHA);
        }
        else
            BeginNormalPaletteFade(~0x8000, 0, 16, 0, RGB_WHITEALPHA);
        sPokedexScreenData->state = 5;
        break;
    case 5:
        ListMenuGetScrollAndRow(sPokedexScreenData->modeSelectListMenuId, &sPokedexScreenData->modeSelectCursorPosBak, NULL);
        if (IsNationalPokedexEnabled())
            sPokedexScreenData->scrollArrowsTaskId = AddScrollIndicatorArrowPair(&sScrollArrowsTemplate_NatDex, &sPokedexScreenData->modeSelectCursorPosBak);
        else
            sPokedexScreenData->scrollArrowsTaskId = AddScrollIndicatorArrowPair(&sScrollArrowsTemplate_KantoDex, &sPokedexScreenData->modeSelectCursorPosBak);
        sPokedexScreenData->state = 6;
        break;
    case 6:
        sPokedexScreenData->modeSelectInput = ListMenu_ProcessInput(sPokedexScreenData->modeSelectListMenuId);
        ListMenuGetScrollAndRow(sPokedexScreenData->modeSelectListMenuId, &sPokedexScreenData->modeSelectCursorPosBak, NULL);
        if (JOY_NEW(A_BUTTON))
        {
            switch (sPokedexScreenData->modeSelectInput)
            {
            case LIST_CANCEL:
                sPokedexScreenData->state = 1;
                break;
            case DEX_CATEGORY_GRASSLAND:
            case DEX_CATEGORY_FOREST:
            case DEX_CATEGORY_WATERS_EDGE:
            case DEX_CATEGORY_SEA:
            case DEX_CATEGORY_CAVE:
            case DEX_CATEGORY_MOUNTAIN:
            case DEX_CATEGORY_ROUGH_TERRAIN:
            case DEX_CATEGORY_URBAN:
            case DEX_CATEGORY_RARE:
                if (DexScreen_IsCategoryUnlocked(sPokedexScreenData->modeSelectInput))
                {
                    RemoveScrollIndicatorArrowPair(sPokedexScreenData->scrollArrowsTaskId);
                    sPokedexScreenData->category = sPokedexScreenData->modeSelectInput;
                    BeginNormalPaletteFade(~0x8000, 0, 0, 16, RGB_WHITEALPHA);
                    sPokedexScreenData->state = 7;
                }
                break;
            case DEX_MODE(NUMERICAL_KANTO):
            case DEX_MODE(NUMERICAL_NATIONAL):
                RemoveScrollIndicatorArrowPair(sPokedexScreenData->scrollArrowsTaskId);
                sPokedexScreenData->dexOrderId = sPokedexScreenData->modeSelectInput - DEX_CATEGORY_COUNT;
                BeginNormalPaletteFade(~0x8000, 0, 0, 16, RGB_WHITEALPHA);
                sPokedexScreenData->state = 9;
                break;
            case DEX_MODE(ATOZ):
            case DEX_MODE(TYPE):
            case DEX_MODE(LIGHTEST):
            case DEX_MODE(SMALLEST):
                RemoveScrollIndicatorArrowPair(sPokedexScreenData->scrollArrowsTaskId);
                sPokedexScreenData->dexOrderId = sPokedexScreenData->modeSelectInput - DEX_CATEGORY_COUNT;
                sPokedexScreenData->characteristicOrderMenuItemsAbove = sPokedexScreenData->characteristicOrderMenuCursorPos = 0;
                BeginNormalPaletteFade(~0x8000, 0, 0, 16, RGB_WHITEALPHA);
                sPokedexScreenData->state = 8;
                break;
            }
            break;
        }
        if (JOY_NEW(B_BUTTON))
        {
            sPokedexScreenData->state = 1;
        }
        break;
    case 7:
        DestroyListMenuTask(sPokedexScreenData->modeSelectListMenuId, &sPokedexScreenData->modeSelectCursorPos, &sPokedexScreenData->modeSelectItemsAbove);
        FillBgTilemapBufferRect_Palette0(1, 0, 0, 0, 32, 20);
        CopyBgTilemapBufferToVram(1);
        DexScreen_RemoveWindow(&sPokedexScreenData->modeSelectWindowId);
        DexScreen_RemoveWindow(&sPokedexScreenData->selectionIconWindowId);
        DexScreen_RemoveWindow(&sPokedexScreenData->dexCountsWindowId);
        sPokedexScreenData->pageNum = 0;
        sPokedexScreenData->categoryCursorPosInPage = 0;
        sPokedexScreenData->parentOfCategoryMenu = 0;
        gTasks[taskId].func = Task_DexScreen_CategorySubmenu;
        sPokedexScreenData->state = 0;
        break;
    case 8:
        DestroyListMenuTask(sPokedexScreenData->modeSelectListMenuId, &sPokedexScreenData->modeSelectCursorPos, &sPokedexScreenData->modeSelectItemsAbove);
        HideBg(1);
        DexScreen_RemoveWindow(&sPokedexScreenData->modeSelectWindowId);
        DexScreen_RemoveWindow(&sPokedexScreenData->selectionIconWindowId);
        DexScreen_RemoveWindow(&sPokedexScreenData->dexCountsWindowId);
        gTasks[taskId].func = Task_DexScreen_CharacteristicOrder;
        sPokedexScreenData->state = 0;
        break;
    case 9:
        DestroyListMenuTask(sPokedexScreenData->modeSelectListMenuId, &sPokedexScreenData->modeSelectCursorPos, &sPokedexScreenData->modeSelectItemsAbove);
        HideBg(1);
        DexScreen_RemoveWindow(&sPokedexScreenData->modeSelectWindowId);
        DexScreen_RemoveWindow(&sPokedexScreenData->selectionIconWindowId);
        DexScreen_RemoveWindow(&sPokedexScreenData->dexCountsWindowId);
        gTasks[taskId].func = Task_DexScreen_NumericalOrder;
        sPokedexScreenData->state = 0;
        break;
    }
}

static void DexScreen_InitGfxForTopMenu(void)
{
    struct ListMenuTemplate listMenuTemplate;
    FillBgTilemapBufferRect(3, 0x00E, 0, 0, 30, 20, 0);
    FillBgTilemapBufferRect(2, 0x000, 0, 0, 30, 20, 17);
    FillBgTilemapBufferRect(1, 0x000, 0, 0, 30, 20, 17);
    sPokedexScreenData->modeSelectWindowId = AddWindow(&sWindowTemplate_ModeSelect);
    sPokedexScreenData->selectionIconWindowId = AddWindow(&sWindowTemplate_SelectionIcon);
    sPokedexScreenData->dexCountsWindowId = AddWindow(&sWindowTemplate_DexCounts);
    if (IsNationalPokedexEnabled())
    {
        listMenuTemplate = sListMenuTemplate_NatDexModeSelect;
        listMenuTemplate.windowId = sPokedexScreenData->modeSelectWindowId;
        sPokedexScreenData->modeSelectListMenuId = ListMenuInit(&listMenuTemplate, sPokedexScreenData->modeSelectCursorPos, sPokedexScreenData->modeSelectItemsAbove);
        FillWindowPixelBuffer(sPokedexScreenData->dexCountsWindowId, PIXEL_FILL(0));
        DexScreen_AddTextPrinterParameterized(sPokedexScreenData->dexCountsWindowId, FONT_SMALL, gText_Seen, 0, 2, 0);
        DexScreen_AddTextPrinterParameterized(sPokedexScreenData->dexCountsWindowId, FONT_SMALL, gText_Kanto, 8, 13, 0);
        DexScreen_PrintNum3RightAlign(sPokedexScreenData->dexCountsWindowId, 0, sPokedexScreenData->numSeenKanto, 52, 13, 2);
        DexScreen_AddTextPrinterParameterized(sPokedexScreenData->dexCountsWindowId, FONT_SMALL, gText_National, 8, 24, 0);
        DexScreen_PrintNum3RightAlign(sPokedexScreenData->dexCountsWindowId, 0, sPokedexScreenData->numSeenNational, 52, 24, 2);
        DexScreen_AddTextPrinterParameterized(sPokedexScreenData->dexCountsWindowId, FONT_SMALL, gText_Owned, 0, 37, 0);
        DexScreen_AddTextPrinterParameterized(sPokedexScreenData->dexCountsWindowId, FONT_SMALL, gText_Kanto, 8, 48, 0);
        DexScreen_PrintNum3RightAlign(sPokedexScreenData->dexCountsWindowId, 0, sPokedexScreenData->numOwnedKanto, 52, 48, 2);
        DexScreen_AddTextPrinterParameterized(sPokedexScreenData->dexCountsWindowId, FONT_SMALL, gText_National, 8, 59, 0);
        DexScreen_PrintNum3RightAlign(sPokedexScreenData->dexCountsWindowId, 0, sPokedexScreenData->numOwnedNational, 52, 59, 2);
    }
    else
    {
        listMenuTemplate = sListMenuTemplate_KantoDexModeSelect;
        listMenuTemplate.windowId = sPokedexScreenData->modeSelectWindowId;
        sPokedexScreenData->modeSelectListMenuId = ListMenuInit(&listMenuTemplate, sPokedexScreenData->modeSelectCursorPos, sPokedexScreenData->modeSelectItemsAbove);
        FillWindowPixelBuffer(sPokedexScreenData->dexCountsWindowId, PIXEL_FILL(0));
        DexScreen_AddTextPrinterParameterized(sPokedexScreenData->dexCountsWindowId, FONT_NORMAL_COPY_1, gText_Seen, 0, 9, 0);
        DexScreen_PrintNum3RightAlign(sPokedexScreenData->dexCountsWindowId, 1, sPokedexScreenData->numSeenKanto, 32, 21, 2);
        DexScreen_AddTextPrinterParameterized(sPokedexScreenData->dexCountsWindowId, FONT_NORMAL_COPY_1, gText_Owned, 0, 37, 0);
        DexScreen_PrintNum3RightAlign(sPokedexScreenData->dexCountsWindowId, 1, sPokedexScreenData->numOwnedKanto, 32, 49, 2);
    }
    FillWindowPixelBuffer(0, PIXEL_FILL(15));
    DexScreen_PrintStringWithAlignment(gText_PokedexTableOfContents, TEXT_CENTER);
    FillWindowPixelBuffer(1, PIXEL_FILL(15));
    DexScreen_PrintControlInfo(gText_PickOK);
    PutWindowTilemap(0);
    CopyWindowToVram(0, COPYWIN_GFX);
    PutWindowTilemap(1);
    CopyWindowToVram(1, COPYWIN_GFX);
    PutWindowTilemap(sPokedexScreenData->dexCountsWindowId);
    CopyWindowToVram(sPokedexScreenData->dexCountsWindowId, COPYWIN_GFX);
}

static void MoveCursorFunc_DexModeSelect(s32 itemIndex, bool8 onInit, struct ListMenu *list)
{
    if (!onInit)
        PlaySE(SE_SELECT);
    if (itemIndex == LIST_CANCEL)
    {
        CopyToWindowPixelBuffer(sPokedexScreenData->selectionIconWindowId, sTopMenuSelectionIconTiles_Cancel, 0x000, 0x000);
        LoadPalette(sTopMenuSelectionIconPals_Cancel, BG_PLTT_ID(1), PLTT_SIZE_4BPP);
    }
    else
    {
        CopyToWindowPixelBuffer(sPokedexScreenData->selectionIconWindowId, sTopMenuSelectionIconGfxPtrs[itemIndex].tiles, 0x000, 0x000);
        LoadPalette(sTopMenuSelectionIconGfxPtrs[itemIndex].pal, BG_PLTT_ID(1), PLTT_SIZE_4BPP);
    }
    PutWindowTilemap(sPokedexScreenData->selectionIconWindowId);
    CopyWindowToVram(sPokedexScreenData->selectionIconWindowId, COPYWIN_GFX);
}

static void ItemPrintFunc_DexModeSelect(u8 windowId, u32 itemId, u8 y)
{
    if (itemId >= DEX_CATEGORY_COUNT || sPokedexScreenData->unlockedCategories & (1 << itemId))
        ListMenuOverrideSetColors(TEXT_COLOR_WHITE, TEXT_COLOR_TRANSPARENT, TEXT_COLOR_LIGHT_GRAY);
    else
        ListMenuOverrideSetColors(TEXT_DYNAMIC_COLOR_1, TEXT_COLOR_TRANSPARENT, TEXT_DYNAMIC_COLOR_2);
}

static void Task_DexScreen_NumericalOrder(u8 taskId)
{
    switch (sPokedexScreenData->state)
    {
    case 0:
        ListMenuLoadStdPalAt(BG_PLTT_ID(1), 0);
        ListMenuLoadStdPalAt(BG_PLTT_ID(2), 1);
        sPokedexScreenData->orderedDexCount = DexScreen_CountMonsInOrderedList(sPokedexScreenData->dexOrderId);
        sPokedexScreenData->state = 2;
        break;
    case 1:
        DexScreen_DestroyDexOrderListMenu(sPokedexScreenData->dexOrderId);
        HideBg(1);
        DexScreen_RemoveWindow(&sPokedexScreenData->numericalOrderWindowId);
        gTasks[taskId].func = Task_PokedexScreen;
        sPokedexScreenData->state = 0;
        break;
    case 2:
        DexScreen_InitGfxForNumericalOrderList();
        sPokedexScreenData->state = 3;
        break;
    case 3:
        CopyBgTilemapBufferToVram(3);
        CopyBgTilemapBufferToVram(1);
        sPokedexScreenData->state = 4;
        break;
    case 4:
        ShowBg(1);
        BeginNormalPaletteFade(~0x8000, 0, 16, 0, RGB_WHITEALPHA);
        sPokedexScreenData->state = 5;
        break;
    case 5:
        ListMenuGetScrollAndRow(sPokedexScreenData->modeSelectListMenuId, &sPokedexScreenData->modeSelectCursorPosBak, NULL);
        sPokedexScreenData->scrollArrowsTaskId = DexScreen_CreateDexOrderScrollArrows();
        sPokedexScreenData->state = 6;
        break;
    case 6:
        sPokedexScreenData->characteristicMenuInput = ListMenu_ProcessInput(sPokedexScreenData->orderedListMenuTaskId);
        ListMenuGetScrollAndRow(sPokedexScreenData->modeSelectListMenuId, &sPokedexScreenData->modeSelectCursorPosBak, NULL);
        if (JOY_NEW(A_BUTTON))
        {
            if ((sPokedexScreenData->characteristicMenuInput >> 16) & 1)
            {
                sPokedexScreenData->dexSpecies = sPokedexScreenData->characteristicMenuInput;
                RemoveScrollIndicatorArrowPair(sPokedexScreenData->scrollArrowsTaskId);
                BeginNormalPaletteFade(~0x8000, 0, 0, 16, RGB_WHITEALPHA);
                sPokedexScreenData->state = 7;
            }
        }
        else if (JOY_NEW(B_BUTTON))
        {
            RemoveScrollIndicatorArrowPair(sPokedexScreenData->scrollArrowsTaskId);
            BeginNormalPaletteFade(~0x8000, 0, 0, 16, RGB_WHITEALPHA);
            sPokedexScreenData->state = 1;
        }
        break;
    case 7:
        DexScreen_DestroyDexOrderListMenu(sPokedexScreenData->dexOrderId);
        FillBgTilemapBufferRect_Palette0(1, 0x000, 0, 0, 32, 20);
        CopyBgTilemapBufferToVram(1);
        DexScreen_RemoveWindow(&sPokedexScreenData->numericalOrderWindowId);
        gTasks[taskId].func = Task_DexScreen_ShowMonPage;
        sPokedexScreenData->state = 0;
        break;
    }
}

static void DexScreen_InitGfxForNumericalOrderList(void)
{
    struct ListMenuTemplate template;
    FillBgTilemapBufferRect(3, 0x00E, 0, 0, 30, 20, 0);
    FillBgTilemapBufferRect(1, 0x000, 0, 0, 32, 32, 17);
    sPokedexScreenData->numericalOrderWindowId = AddWindow(&sWindowTemplate_OrderedListMenu);
    template = sListMenuTemplate_OrderedListMenu;
    template.items = sPokedexScreenData->listItems;
    template.windowId = sPokedexScreenData->numericalOrderWindowId;
    template.totalItems = sPokedexScreenData->orderedDexCount;
    DexScreen_InitListMenuForOrderedList(&template, sPokedexScreenData->dexOrderId);
    FillWindowPixelBuffer(0, PIXEL_FILL(15));
    DexScreen_PrintStringWithAlignment(gText_PokemonListNoColor, TEXT_CENTER);
    FillWindowPixelBuffer(1, PIXEL_FILL(15));
    DexScreen_PrintControlInfo(gText_PickOKExit);
    CopyWindowToVram(0, COPYWIN_GFX);
    CopyWindowToVram(1, COPYWIN_GFX);
}

static void Task_DexScreen_CharacteristicOrder(u8 taskId)
{
    switch (sPokedexScreenData->state)
    {
    case 0:
        ListMenuLoadStdPalAt(BG_PLTT_ID(1), 0);
        ListMenuLoadStdPalAt(BG_PLTT_ID(2), 1);
        sPokedexScreenData->orderedDexCount = DexScreen_CountMonsInOrderedList(sPokedexScreenData->dexOrderId);
        sPokedexScreenData->state = 2;
        break;
    case 1:
        DexScreen_DestroyDexOrderListMenu(sPokedexScreenData->dexOrderId);
        HideBg(1);
        DexScreen_RemoveWindow(&sPokedexScreenData->numericalOrderWindowId);
        gTasks[taskId].func = Task_PokedexScreen;
        sPokedexScreenData->state = 0;
        break;
    case 2:
        DexScreen_CreateCharacteristicListMenu();
        sPokedexScreenData->state = 3;
        break;
    case 3:
        CopyBgTilemapBufferToVram(3);
        CopyBgTilemapBufferToVram(1);
        sPokedexScreenData->state = 4;
        break;
    case 4:
        ShowBg(1);
        BeginNormalPaletteFade(~0x8000, 0, 16, 0, RGB_WHITEALPHA);
        sPokedexScreenData->state = 5;
        break;
    case 5:
        ListMenuGetScrollAndRow(sPokedexScreenData->modeSelectListMenuId, &sPokedexScreenData->modeSelectCursorPosBak, NULL);
        sPokedexScreenData->scrollArrowsTaskId = DexScreen_CreateDexOrderScrollArrows();
        sPokedexScreenData->state = 6;
        break;
    case 6:
        sPokedexScreenData->characteristicMenuInput = ListMenu_ProcessInput(sPokedexScreenData->orderedListMenuTaskId);
        ListMenuGetScrollAndRow(sPokedexScreenData->modeSelectListMenuId, &sPokedexScreenData->modeSelectCursorPosBak, NULL);
        if (JOY_NEW(A_BUTTON))
        {
            if (((sPokedexScreenData->characteristicMenuInput >> 16) & 1) && !DexScreen_LookUpCategoryBySpecies(sPokedexScreenData->characteristicMenuInput))
            {
                RemoveScrollIndicatorArrowPair(sPokedexScreenData->scrollArrowsTaskId);
                BeginNormalPaletteFade(~0x8000, 0, 0, 16, RGB_WHITEALPHA);
                sPokedexScreenData->state = 7;
            }
        }
        else if (JOY_NEW(B_BUTTON))
        {
            RemoveScrollIndicatorArrowPair(sPokedexScreenData->scrollArrowsTaskId);
            BeginNormalPaletteFade(~0x8000, 0, 0, 16, RGB_WHITEALPHA);
            sPokedexScreenData->state = 1;
        }
        break;
    case 7:
        DexScreen_DestroyDexOrderListMenu(sPokedexScreenData->dexOrderId);
        FillBgTilemapBufferRect_Palette0(1, 0x000, 0, 0, 32, 20);
        CopyBgTilemapBufferToVram(1);
        DexScreen_RemoveWindow(&sPokedexScreenData->numericalOrderWindowId);
        sPokedexScreenData->parentOfCategoryMenu = 1;
        gTasks[taskId].func = Task_DexScreen_CategorySubmenu;
        sPokedexScreenData->state = 0;
        break;
    }
}

static void DexScreen_CreateCharacteristicListMenu(void)
{
    struct ListMenuTemplate template;
    FillBgTilemapBufferRect(3, 0x00E, 0, 0, 30, 20, 0);
    FillBgTilemapBufferRect(1, 0x000, 0, 0, 32, 32, 17);
    sPokedexScreenData->numericalOrderWindowId = AddWindow(&sWindowTemplate_OrderedListMenu);
    template = sListMenuTemplate_OrderedListMenu;
    template.items = sPokedexScreenData->listItems;
    template.windowId = sPokedexScreenData->numericalOrderWindowId;
    template.totalItems = sPokedexScreenData->orderedDexCount;
    DexScreen_InitListMenuForOrderedList(&template, sPokedexScreenData->dexOrderId);
    FillWindowPixelBuffer(0, PIXEL_FILL(15));
    DexScreen_PrintStringWithAlignment(gText_SearchNoColor, TEXT_CENTER);
    FillWindowPixelBuffer(1, PIXEL_FILL(15));
    DexScreen_PrintControlInfo(gText_PickOKExit);
    CopyWindowToVram(0, COPYWIN_GFX);
    CopyWindowToVram(1, COPYWIN_GFX);
}

static u16 DexScreen_CountMonsInOrderedList(u8 orderIdx)
{
    s32 max_n = IsNationalPokedexEnabled() ? NATIONAL_DEX_COUNT : KANTO_DEX_COUNT;
    u16 ndex_num;
    u16 ret = NATIONAL_DEX_NONE;
    s32 i;
    bool8 caught;
    bool8 seen;

    switch (orderIdx)
    {
    default:
    case DEX_ORDER_NUMERICAL_KANTO:
        for (i = 0; i < KANTO_DEX_COUNT; i++)
        {
            ndex_num = i + 1;
            seen = DexScreen_GetSetPokedexFlag(ndex_num, FLAG_GET_SEEN, FALSE);
            caught = DexScreen_GetSetPokedexFlag(ndex_num, FLAG_GET_CAUGHT, FALSE);
            if (seen)
            {
                sPokedexScreenData->listItems[i].label = gSpeciesNames[NationalPokedexNumToSpecies(ndex_num)];
                ret = ndex_num;
            }
            else
            {
                sPokedexScreenData->listItems[i].label = gText_5Dashes;
            }
            sPokedexScreenData->listItems[i].index = (caught << 17) + (seen << 16) + NationalPokedexNumToSpecies(ndex_num);
        }
        break;
    case DEX_ORDER_ATOZ:
        for (i = 0; i < NUM_SPECIES - 1; i++)
        {
            ndex_num = gPokedexOrder_Alphabetical[i];
            if (ndex_num <= max_n)
            {
                seen = DexScreen_GetSetPokedexFlag(ndex_num, FLAG_GET_SEEN, FALSE);
                caught = DexScreen_GetSetPokedexFlag(ndex_num, FLAG_GET_CAUGHT, FALSE);
                if (seen)
                {
                    sPokedexScreenData->listItems[ret].label = gSpeciesNames[NationalPokedexNumToSpecies(ndex_num)];
                    sPokedexScreenData->listItems[ret].index = (caught << 17) + (seen << 16) + NationalPokedexNumToSpecies(ndex_num);
                    ret++;
                }
            }
        }
        break;
    case DEX_ORDER_TYPE:
        for (i = 0; i < NUM_SPECIES - 1; i++)
        {
            ndex_num = SpeciesToNationalPokedexNum(gPokedexOrder_Type[i]);
            if (ndex_num <= max_n)
            {
                seen = DexScreen_GetSetPokedexFlag(ndex_num, FLAG_GET_SEEN, FALSE);
                caught = DexScreen_GetSetPokedexFlag(ndex_num, FLAG_GET_CAUGHT, FALSE);
                if (caught)
                {
                    sPokedexScreenData->listItems[ret].label = gSpeciesNames[NationalPokedexNumToSpecies(ndex_num)];
                    sPokedexScreenData->listItems[ret].index = (caught << 17) + (seen << 16) + NationalPokedexNumToSpecies(ndex_num);
                    ret++;
                }
            }
        }
        break;
    case DEX_ORDER_LIGHTEST:
        for (i = 0; i < NATIONAL_DEX_COUNT; i++)
        {
            ndex_num = gPokedexOrder_Weight[i];
            if (ndex_num <= max_n)
            {
                seen = DexScreen_GetSetPokedexFlag(ndex_num, FLAG_GET_SEEN, FALSE);
                caught = DexScreen_GetSetPokedexFlag(ndex_num, FLAG_GET_CAUGHT, FALSE);
                if (caught)
                {
                    sPokedexScreenData->listItems[ret].label = gSpeciesNames[NationalPokedexNumToSpecies(ndex_num)];
                    sPokedexScreenData->listItems[ret].index = (caught << 17) + (seen << 16) + NationalPokedexNumToSpecies(ndex_num);
                    ret++;
                }
            }
        }
        break;
    case DEX_ORDER_SMALLEST:
        for (i = 0; i < NATIONAL_DEX_COUNT; i++)
        {
            ndex_num = gPokedexOrder_Height[i];
            if (ndex_num <= max_n)
            {
                seen = DexScreen_GetSetPokedexFlag(ndex_num, FLAG_GET_SEEN, FALSE);
                caught = DexScreen_GetSetPokedexFlag(ndex_num, FLAG_GET_CAUGHT, FALSE);
                if (caught)
                {
                    sPokedexScreenData->listItems[ret].label = gSpeciesNames[NationalPokedexNumToSpecies(ndex_num)];
                    sPokedexScreenData->listItems[ret].index = (caught << 17) + (seen << 16) + NationalPokedexNumToSpecies(ndex_num);
                    ret++;
                }
            }
        }
        break;
    case DEX_ORDER_NUMERICAL_NATIONAL:
        for (i = 0; i < NATIONAL_DEX_COUNT; i++)
        {
            ndex_num = i + 1;
            seen = DexScreen_GetSetPokedexFlag(ndex_num, FLAG_GET_SEEN, FALSE);
            caught = DexScreen_GetSetPokedexFlag(ndex_num, FLAG_GET_CAUGHT, FALSE);
            if (seen)
            {
                sPokedexScreenData->listItems[i].label = gSpeciesNames[NationalPokedexNumToSpecies(ndex_num)];
                ret = ndex_num;
            }
            else
            {
                sPokedexScreenData->listItems[i].label = gText_5Dashes;
            }
            sPokedexScreenData->listItems[i].index = (caught << 17) + (seen << 16) + NationalPokedexNumToSpecies(ndex_num);
        }
        break;
    }
    return ret;
}

static void DexScreen_InitListMenuForOrderedList(const struct ListMenuTemplate * template, u8 order)
{
    switch (order)
    {
    default:
    case DEX_ORDER_NUMERICAL_KANTO:
        sPokedexScreenData->orderedListMenuTaskId = ListMenuInitInRect(template, sListMenuRects_OrderedList, sPokedexScreenData->kantoOrderMenuCursorPos, sPokedexScreenData->kantoOrderMenuItemsAbove);
        break;
    case DEX_ORDER_ATOZ:
    case DEX_ORDER_TYPE:
    case DEX_ORDER_LIGHTEST:
    case DEX_ORDER_SMALLEST:
        sPokedexScreenData->orderedListMenuTaskId = ListMenuInitInRect(template, sListMenuRects_OrderedList, sPokedexScreenData->characteristicOrderMenuCursorPos, sPokedexScreenData->characteristicOrderMenuItemsAbove);
        break;
    case DEX_ORDER_NUMERICAL_NATIONAL:
        sPokedexScreenData->orderedListMenuTaskId = ListMenuInitInRect(template, sListMenuRects_OrderedList, sPokedexScreenData->nationalOrderMenuCursorPos, sPokedexScreenData->nationalOrderMenuItemsAbove);
        break;
    }
}

static void DexScreen_DestroyDexOrderListMenu(u8 order)
{
    switch (order)
    {
    default:
    case DEX_ORDER_NUMERICAL_KANTO:
        DestroyListMenuTask(sPokedexScreenData->orderedListMenuTaskId, &sPokedexScreenData->kantoOrderMenuCursorPos, &sPokedexScreenData->kantoOrderMenuItemsAbove);
        break;
    case DEX_ORDER_ATOZ:
    case DEX_ORDER_TYPE:
    case DEX_ORDER_LIGHTEST:
    case DEX_ORDER_SMALLEST:
        DestroyListMenuTask(sPokedexScreenData->orderedListMenuTaskId, &sPokedexScreenData->characteristicOrderMenuCursorPos, &sPokedexScreenData->characteristicOrderMenuItemsAbove);
        break;
    case DEX_ORDER_NUMERICAL_NATIONAL:
        DestroyListMenuTask(sPokedexScreenData->orderedListMenuTaskId, &sPokedexScreenData->nationalOrderMenuCursorPos, &sPokedexScreenData->nationalOrderMenuItemsAbove);
        break;
    }
}

static u8 DexScreen_CreateDexOrderScrollArrows(void)
{
    struct ScrollArrowsTemplate template = sDexOrderScrollArrowsTemplate;
    if (sPokedexScreenData->orderedDexCount > sListMenuTemplate_OrderedListMenu.maxShowed)
        template.fullyDownThreshold = sPokedexScreenData->orderedDexCount - sListMenuTemplate_OrderedListMenu.maxShowed;
    else
        template.fullyDownThreshold = 0;
    return AddScrollIndicatorArrowPair(&template, &sPokedexScreenData->modeSelectCursorPosBak);
}

struct PokedexListItem
{
    u16 species;
    bool8 seen:1;
    bool8 caught:1;
};

static void ItemPrintFunc_OrderedListMenu(u8 windowId, u32 itemId, u8 y)
{
    u16 species = itemId;
    bool8 seen = (itemId >> 16) & 1;  // not used but required to match
    bool8 caught = (itemId >> 17) & 1;
    u8 type1;
    DexScreen_PrintMonDexNo(sPokedexScreenData->numericalOrderWindowId, FONT_SMALL, species, 12, y);
    if (caught)
    {
        BlitMenuInfoIcon(sPokedexScreenData->numericalOrderWindowId, MENU_INFO_ICON_CAUGHT, 0x28, y);
        type1 = gSpeciesInfo[species].types[0];
        BlitMenuInfoIcon(sPokedexScreenData->numericalOrderWindowId, type1 + 1, 0x78, y);
        if (type1 != gSpeciesInfo[species].types[1])
            BlitMenuInfoIcon(sPokedexScreenData->numericalOrderWindowId, gSpeciesInfo[species].types[1] + 1, 0x98, y);
    }
}

static void Task_DexScreen_CategorySubmenu(u8 taskId)
{
    int pageFlipCmd;
    u8 *ptr;
    switch (sPokedexScreenData->state)
    {
    case 0:
        HideBg(3);
        HideBg(2);
        HideBg(1);
        DexScreen_GetPageLimitsForCategory(sPokedexScreenData->category);
        if (sPokedexScreenData->pageNum < sPokedexScreenData->firstPageInCategory)
            sPokedexScreenData->pageNum = sPokedexScreenData->firstPageInCategory;
        sPokedexScreenData->state = 2;
        break;
    case 1:
        DexScreen_DestroyCategoryPageMonIconAndInfoWindows();
        HideBg(2);
        HideBg(1);
        switch (sPokedexScreenData->parentOfCategoryMenu)
        {
        case 0:
        default:
            gTasks[taskId].func = Task_PokedexScreen;
            break;
        case 1:
            gTasks[taskId].func = Task_DexScreen_CharacteristicOrder;
            break;
        }
        sPokedexScreenData->state = 0;
        break;
    case 2:
        DexScreen_CreateCategoryListGfx(FALSE);
        CopyBgTilemapBufferToVram(3);
        CopyBgTilemapBufferToVram(2);
        CopyBgTilemapBufferToVram(1);
        DexScreen_CreateCategoryPageSelectionCursor(0xFF);
        sPokedexScreenData->state = 3;
        break;
    case 3:
        BeginNormalPaletteFade(~0x8000, 0, 16, 0, RGB_WHITEALPHA);
        ShowBg(3);
        ShowBg(2);
        ShowBg(1);
        sPokedexScreenData->state = 4;
        break;
    case 4:
        sPokedexScreenData->scrollArrowsTaskId = DexScreen_CreateCategoryMenuScrollArrows();
        sPokedexScreenData->categoryPageCursorTaskId = ListMenuAddCursorObjectInternal(&sCursorStruct_CategoryPage, 0);
        sPokedexScreenData->state = 5;
        break;
    case 5:
        DexScreen_CreateCategoryPageSelectionCursor(sPokedexScreenData->categoryCursorPosInPage);
        DexScreen_UpdateCategoryPageCursorObject(sPokedexScreenData->categoryPageCursorTaskId, sPokedexScreenData->categoryCursorPosInPage, sPokedexScreenData->numMonsOnPage);
        sPokedexScreenData->modeSelectCursorPosBak = sPokedexScreenData->pageNum;
        pageFlipCmd = 0;
        if (JOY_NEW(A_BUTTON) && DexScreen_GetSetPokedexFlag(sPokedexScreenData->pageSpecies[sPokedexScreenData->categoryCursorPosInPage], FLAG_GET_SEEN, TRUE))
        {
            RemoveScrollIndicatorArrowPair(sPokedexScreenData->scrollArrowsTaskId);
            ListMenuRemoveCursorObject(sPokedexScreenData->categoryPageCursorTaskId, 0);
            sPokedexScreenData->state = 12;
            break;
        }
        if (!JOY_HELD(R_BUTTON) && JOY_REPT(DPAD_LEFT))
        {
            if (sPokedexScreenData->categoryCursorPosInPage != 0)
            {
                sPokedexScreenData->categoryCursorPosInPage--;
                PlaySE(SE_SELECT);
                break;
            }
            else
                pageFlipCmd = 1;
        }
        if (!JOY_HELD(R_BUTTON) && JOY_REPT(DPAD_RIGHT))
        {
            if (sPokedexScreenData->categoryCursorPosInPage < sPokedexScreenData->numMonsOnPage - 1)
            {
                sPokedexScreenData->categoryCursorPosInPage++;
                PlaySE(SE_SELECT);
                break;
            }
            else
                pageFlipCmd = 2;
        }
        if (pageFlipCmd == 0)
            pageFlipCmd = DexScreen_InputHandler_GetShoulderInput();
        switch (pageFlipCmd)
        {
        case 0: // No action
            break;
        case 1: // Left
            while (sPokedexScreenData->pageNum > sPokedexScreenData->firstPageInCategory)
            {
                sPokedexScreenData->pageNum--;
                if (DexScreen_IsPageUnlocked(sPokedexScreenData->category, sPokedexScreenData->pageNum))
                {
                    sPokedexScreenData->state = 8;
                    break;
                }
            }
            if (sPokedexScreenData->state != 8)
                sPokedexScreenData->state = 6;
            break;
        case 2: // Right
            while (sPokedexScreenData->pageNum < sPokedexScreenData->lastPageInCategory - 1)
            {
                sPokedexScreenData->pageNum++;
                if (DexScreen_IsPageUnlocked(sPokedexScreenData->category, sPokedexScreenData->pageNum))
                {
                    sPokedexScreenData->state = 10;
                    break;
                }
            }
            if (sPokedexScreenData->state != 10)
                sPokedexScreenData->state = 6;
            break;
        }
        if (JOY_NEW(B_BUTTON))
        {
            sPokedexScreenData->state = 6;
        }
        break;
    case 6:
    case 7:
        RemoveScrollIndicatorArrowPair(sPokedexScreenData->scrollArrowsTaskId);
        ListMenuRemoveCursorObject(sPokedexScreenData->categoryPageCursorTaskId, 0);
        BeginNormalPaletteFade(~0x8000, 0, 0, 16, RGB_WHITEALPHA);
        sPokedexScreenData->state = 1;
        break;
    case 8:
    case 10:
        DexScreen_DestroyCategoryPageMonIconAndInfoWindows();
        DexScreen_CreateCategoryPageSelectionCursor(0xFF);
        ListMenuUpdateCursorObject(sPokedexScreenData->categoryPageCursorTaskId, 0, 0xA0, 0);
        sPokedexScreenData->categoryPageSelectionCursorTimer = 0;
        sPokedexScreenData->data[0] = 0;
        sPokedexScreenData->state++;
        break;
    case 9:
        if (DexScreen_FlipCategoryPageInDirection(0))
        {
            sPokedexScreenData->categoryCursorPosInPage = sPokedexScreenData->numMonsOnPage - 1;
            sPokedexScreenData->state = 5;
        }
        break;
    case 11:
        if (DexScreen_FlipCategoryPageInDirection(1))
        {
            sPokedexScreenData->categoryCursorPosInPage = 0;
            sPokedexScreenData->state = 5;
        }
        break;
    case 12:
        sPokedexScreenData->dexSpecies = sPokedexScreenData->pageSpecies[sPokedexScreenData->categoryCursorPosInPage];
        PlaySE(SE_SELECT);
        sPokedexScreenData->state = 14;
        break;
    case 13:
        RemoveDexPageWindows();
        sPokedexScreenData->state = 4;
        break;
    case 14:
        DexScreen_DrawMonDexPage(FALSE);
        sPokedexScreenData->state = 15;
        break;
    case 15:
        sPokedexScreenData->data[0] = 0;
        sPokedexScreenData->data[1] = 0;
        sPokedexScreenData->state++;
        // fallthrough
    case 16:
        if (sPokedexScreenData->data[1] < 6)
        {
            if (sPokedexScreenData->data[0])
            {
                DexScreen_DexPageZoomEffectFrame(0, sPokedexScreenData->data[1]);
                CopyBgTilemapBufferToVram(0);
                sPokedexScreenData->data[0] = 4;
                sPokedexScreenData->data[1]++;
            }
            else
            {
                sPokedexScreenData->data[0]--;
            }
        }
        else
        {
            FillBgTilemapBufferRect_Palette0(0, 0x000, 0, 2, 30, 16);
            CopyBgTilemapBufferToVram(3);
            CopyBgTilemapBufferToVram(2);
            CopyBgTilemapBufferToVram(1);
            CopyBgTilemapBufferToVram(0);
            PlayCry_NormalNoDucking(sPokedexScreenData->dexSpecies, 0, CRY_VOLUME_RS, CRY_PRIORITY_NORMAL);
            sPokedexScreenData->data[0] = 0;
            sPokedexScreenData->state = 17;
        }
        break;
    case 17:
        if (JOY_NEW(A_BUTTON))
        {
            RemoveDexPageWindows();
            FillBgTilemapBufferRect_Palette0(1, 0x000, 0, 2, 30, 16);
            CopyBgTilemapBufferToVram(1);
            sPokedexScreenData->state = 21;
        }
        else if (JOY_NEW(B_BUTTON))
        {
            sPokedexScreenData->state = 18;
        }
        else
        {
            DexScreen_InputHandler_StartToCry();
        }
        break;
    case 18:
        DexScreen_CreateCategoryListGfx(FALSE);
        DexScreen_DexPageZoomEffectFrame(0, 6);
        CopyBgTilemapBufferToVram(3);
        CopyBgTilemapBufferToVram(2);
        CopyBgTilemapBufferToVram(1);
        CopyBgTilemapBufferToVram(0);
        sPokedexScreenData->state = 19;
        break;
    case 19:
        sPokedexScreenData->data[0] = 0;
        sPokedexScreenData->data[1] = 6;
        sPokedexScreenData->state++;
        // fallthrough
    case 20:
        if (sPokedexScreenData->data[1])
        {
            if (sPokedexScreenData->data[0])
            {
                sPokedexScreenData->data[1]--;
                FillBgTilemapBufferRect_Palette0(0, 0x000, 0, 2, 30, 16);
                DexScreen_DexPageZoomEffectFrame(0, sPokedexScreenData->data[1]);
                CopyBgTilemapBufferToVram(0);
                sPokedexScreenData->data[0] = 1;
            }
            else
                sPokedexScreenData->data[0]--;
        }
        else
        {
            FillBgTilemapBufferRect_Palette0(0, 0x000, 0, 2, 30, 16);
            CopyBgTilemapBufferToVram(0);
            sPokedexScreenData->state = 13;
        }
        break;
    case 21:
        DexScreen_DrawMonAreaPage();
        sPokedexScreenData->state = 22;
        break;
    case 22:
        CopyBgTilemapBufferToVram(3);
        CopyBgTilemapBufferToVram(2);
        CopyBgTilemapBufferToVram(1);
        CopyBgTilemapBufferToVram(0);
        sPokedexScreenData->state = 23;
        break;
    case 23:
        if (JOY_NEW(A_BUTTON))
        {
            FillBgTilemapBufferRect_Palette0(2, 0x000, 0, 2, 30, 16);
            FillBgTilemapBufferRect_Palette0(1, 0x000, 0, 2, 30, 16);
            FillBgTilemapBufferRect_Palette0(0, 0x000, 0, 2, 30, 16);
            CopyBgTilemapBufferToVram(2);
            CopyBgTilemapBufferToVram(1);
            CopyBgTilemapBufferToVram(0);
            sPokedexScreenData->state = 26;
        }
        else if (JOY_NEW(B_BUTTON))
        {
            FillBgTilemapBufferRect_Palette0(2, 0x000, 0, 2, 30, 16);
            FillBgTilemapBufferRect_Palette0(1, 0x000, 0, 2, 30, 16);
            FillBgTilemapBufferRect_Palette0(0, 0x000, 0, 2, 30, 16);
            CopyBgTilemapBufferToVram(2);
            CopyBgTilemapBufferToVram(1);
            CopyBgTilemapBufferToVram(0);
            sPokedexScreenData->state = 24;
        }
        else
        {
            DexScreen_InputHandler_StartToCry();
        }
        break;
    case 24:
        DexScreen_DestroyAreaScreenResources();
        sPokedexScreenData->state = 25;
        break;
    case 25:
        DexScreen_DrawMonDexPage(FALSE);
        CopyBgTilemapBufferToVram(3);
        CopyBgTilemapBufferToVram(2);
        CopyBgTilemapBufferToVram(1);
        CopyBgTilemapBufferToVram(0);
        sPokedexScreenData->state = 17;
        break;
    case 26:
        DexScreen_DestroyAreaScreenResources();
        sPokedexScreenData->state = 18;
        break;
    }
}

static u8 DexScreen_CreateCategoryMenuScrollArrows(void)
{
    struct ScrollArrowsTemplate template = sScrollArrowsTemplate_CategoryMenu;
    template.fullyUpThreshold = sPokedexScreenData->firstPageInCategory;
    template.fullyDownThreshold = sPokedexScreenData->lastPageInCategory - 1;
    sPokedexScreenData->modeSelectCursorPosBak = sPokedexScreenData->pageNum;
    return AddScrollIndicatorArrowPair(&template, &sPokedexScreenData->modeSelectCursorPosBak);
}

/*
 * Returns 1 to flip pages left, 2 to flip pages right, 0 for no action
 */
static int DexScreen_InputHandler_GetShoulderInput(void)
{
    switch (gSaveBlock2Ptr->optionsButtonMode)
    {
    case OPTIONS_BUTTON_MODE_L_EQUALS_A:
        // Using the JOY_HELD and JOY_NEW macros here does not match!
        if ((gMain.heldKeys & R_BUTTON) && (gMain.newKeys & DPAD_LEFT))
            return 1;
        else if ((gMain.heldKeys & R_BUTTON) && (gMain.newKeys & DPAD_RIGHT))
            return 2;
        else
            return 0;
    case OPTIONS_BUTTON_MODE_LR:
        if (gMain.newKeys & L_BUTTON)
            return 1;
        else if (gMain.newKeys & R_BUTTON)
            return 2;
        else
            return 0;
    case OPTIONS_BUTTON_MODE_HELP:
    default:
        return 0;
    }
}

static void Task_DexScreen_ShowMonPage(u8 taskId)
{
    switch (sPokedexScreenData->state)
    {
    case 0:
        HideBg(3);
        HideBg(2);
        HideBg(1);
        sPokedexScreenData->state = 2;
        break;
    case 1:
        HideBg(2);
        HideBg(1);
        gTasks[taskId].func = Task_DexScreen_NumericalOrder;
        sPokedexScreenData->state = 0;
        break;
    case 2:
        sPokedexScreenData->numMonsOnPage = 1;
        DexScreen_DrawMonDexPage(FALSE);
        sPokedexScreenData->state = 3;
        break;
    case 3:
        CopyBgTilemapBufferToVram(3);
        CopyBgTilemapBufferToVram(2);
        CopyBgTilemapBufferToVram(1);
        CopyBgTilemapBufferToVram(0);
        PlayCry_NormalNoDucking(sPokedexScreenData->dexSpecies, 0, CRY_VOLUME_RS, CRY_PRIORITY_NORMAL);
        sPokedexScreenData->state = 4;
        break;
    case 4:
        BeginNormalPaletteFade(~0x8000, 0, 16, 0, RGB_WHITEALPHA);
        ShowBg(3);
        ShowBg(2);
        ShowBg(1);
        sPokedexScreenData->state = 5;
        break;
    case 5:
        if (JOY_NEW(A_BUTTON))
        {
            RemoveDexPageWindows();
            FillBgTilemapBufferRect_Palette0(1, 0x000, 0, 2, 30, 16);
            CopyBgTilemapBufferToVram(1);
            sPokedexScreenData->state = 7;
        }
        else if (JOY_NEW(B_BUTTON))
        {
            RemoveDexPageWindows();
            BeginNormalPaletteFade(~0x8000, 0, 0, 16, RGB_WHITEALPHA);
            sPokedexScreenData->state = 1;
        }
        else if (JOY_NEW(DPAD_UP) && DexScreen_TryScrollMonsVertical(1))
        {
            RemoveDexPageWindows();
            BeginNormalPaletteFade(~0x8000, 0, 0, 16, RGB_WHITEALPHA);
            sPokedexScreenData->state = 6;
        }
        else if (JOY_NEW(DPAD_DOWN) && DexScreen_TryScrollMonsVertical(0))
        {
            RemoveDexPageWindows();
            BeginNormalPaletteFade(~0x8000, 0, 0, 16, RGB_WHITEALPHA);
            sPokedexScreenData->state = 6;
        }
        else
        {
            DexScreen_InputHandler_StartToCry();
        }
        break;
    case 6:
        HideBg(2);
        HideBg(1);
        sPokedexScreenData->dexSpecies = sPokedexScreenData->characteristicMenuInput;
        sPokedexScreenData->state = 2;
        break;
    case 7:
        DexScreen_DrawMonAreaPage();
        sPokedexScreenData->state = 8;
        break;
    case 8:
        CopyBgTilemapBufferToVram(3);
        CopyBgTilemapBufferToVram(2);
        CopyBgTilemapBufferToVram(1);
        CopyBgTilemapBufferToVram(0);
        sPokedexScreenData->state = 9;
        break;
    case 9:
        if (JOY_NEW(A_BUTTON))
        {
            BeginNormalPaletteFade(~0x8000, 0, 0, 16, RGB_WHITEALPHA);
            sPokedexScreenData->state = 12;
        }
        else if (JOY_NEW(B_BUTTON))
        {
            FillBgTilemapBufferRect_Palette0(2, 0x000, 0, 2, 30, 16);
            FillBgTilemapBufferRect_Palette0(1, 0x000, 0, 2, 30, 16);
            FillBgTilemapBufferRect_Palette0(0, 0x000, 0, 2, 30, 16);
            CopyBgTilemapBufferToVram(2);
            CopyBgTilemapBufferToVram(1);
            CopyBgTilemapBufferToVram(0);
            sPokedexScreenData->state = 10;
        }
        else
        {
            DexScreen_InputHandler_StartToCry();
        }
        break;
    case 10:
        DexScreen_DestroyAreaScreenResources();
        sPokedexScreenData->state = 11;
        break;
    case 11:
        DexScreen_DrawMonDexPage(FALSE);
        CopyBgTilemapBufferToVram(3);
        CopyBgTilemapBufferToVram(2);
        CopyBgTilemapBufferToVram(1);
        CopyBgTilemapBufferToVram(0);
        sPokedexScreenData->state = 5;
        break;
    case 12:
        DexScreen_DestroyAreaScreenResources();
        FillBgTilemapBufferRect_Palette0(0, 0x000, 0, 2, 30, 16);
        CopyBgTilemapBufferToVram(0);
        sPokedexScreenData->state = 1;
        break;
    }
}

static bool32 DexScreen_TryScrollMonsVertical(u8 direction)
{
    int selectedIndex;
    u16 *itemsAbove_p, *cursorPos_p;

    switch (sPokedexScreenData->dexOrderId)
    {
    default:
    case DEX_ORDER_NUMERICAL_KANTO:
        cursorPos_p = &sPokedexScreenData->kantoOrderMenuCursorPos;
        itemsAbove_p = &sPokedexScreenData->kantoOrderMenuItemsAbove;
        break;
    case DEX_ORDER_ATOZ:
    case DEX_ORDER_TYPE:
    case DEX_ORDER_LIGHTEST:
    case DEX_ORDER_SMALLEST:
        cursorPos_p = &sPokedexScreenData->characteristicOrderMenuCursorPos;
        itemsAbove_p = &sPokedexScreenData->characteristicOrderMenuItemsAbove;
        break;
    case DEX_ORDER_NUMERICAL_NATIONAL:
        cursorPos_p = &sPokedexScreenData->nationalOrderMenuCursorPos;
        itemsAbove_p = &sPokedexScreenData->nationalOrderMenuItemsAbove;
        break;
    }

    selectedIndex = *cursorPos_p + *itemsAbove_p;
    if (direction) // Seek up
    {
        if (selectedIndex == 0)
            return FALSE;

        selectedIndex--;
        while (selectedIndex >= 0) //Should be while (--selectedIndex >= 0) without the selectedIndex-- in the body or before the while at all, but this is needed to match.
        {
            if ((sPokedexScreenData->listItems[selectedIndex].index >> 16) & 1)
            {
                break;
            }
            selectedIndex--;
        }

        if (selectedIndex < 0)
        {
            return FALSE;
        }
    }
    else // Seek down
    {
        if (selectedIndex == sPokedexScreenData->orderedDexCount - 1)
        {
            return FALSE;
        }

        selectedIndex++;
        while (selectedIndex < sPokedexScreenData->orderedDexCount) //Should be while (++selectedIndex < sPokedexScreenData->orderedDexCount) without the selectedIndex++ in the body or before the while at all, but this is needed to match.
        {
            if ((sPokedexScreenData->listItems[selectedIndex].index >> 16) & 1)
                break;
            selectedIndex++;
        }
        if (selectedIndex >= sPokedexScreenData->orderedDexCount)
        {
            return FALSE;
        }
    }
    sPokedexScreenData->characteristicMenuInput = sPokedexScreenData->listItems[selectedIndex].index;

    if (sPokedexScreenData->orderedDexCount > 9)
    {
        if (selectedIndex < 4)
        {
            *cursorPos_p = 0;
            *itemsAbove_p = selectedIndex;
        }
        else if (selectedIndex >= (sPokedexScreenData->orderedDexCount - 4))
        {
            *cursorPos_p = (sPokedexScreenData->orderedDexCount - 9);
            *itemsAbove_p = selectedIndex + 9 - (sPokedexScreenData->orderedDexCount);
        }
        else
        {
            *cursorPos_p = selectedIndex - 4;
            *itemsAbove_p = 4;
        }
    }
    else
    {
        *cursorPos_p = 0;
        *itemsAbove_p = selectedIndex;
    }
    return TRUE;
}

static void DexScreen_RemoveWindow(u8 *windowId_p)
{
    if (*windowId_p != 0xFF)
    {
        RemoveWindow(*windowId_p);
        *windowId_p = 0xFF;
    }
}

static void DexScreen_AddTextPrinterParameterized(u8 windowId, u8 fontId, const u8 *str, u8 x, u8 y, u8 colorIdx)
{
    u8 textColor[3];
    switch (colorIdx)
    {
    case 0:
        textColor[0] = 0;
        textColor[1] = 1;
        textColor[2] = 3;
        break;
    case 1:
        textColor[0] = 0;
        textColor[1] = 5;
        textColor[2] = 1;
        break;
    case 2:
        textColor[0] = 0;
        textColor[1] = 15;
        textColor[2] = 14;
        break;
    case 3:
        textColor[0] = 0;
        textColor[1] = 11;
        textColor[2] = 1;
        break;
    case 4:
        textColor[0] = 0;
        textColor[1] = 1;
        textColor[2] = 2;
        break;
    }
    AddTextPrinterParameterized4(windowId, fontId, x, y, fontId == FONT_SMALL ? 0 : 1, 0, textColor, -1, str);
}

static void DexScreen_PrintNum3LeadingZeroes(u8 windowId, u8 fontId, u16 num, u8 x, u8 y, u8 colorIdx)
{
    u8 buff[4];
    buff[0] = (num / 100) + CHAR_0;
    buff[1] = ((num %= 100) / 10) + CHAR_0;
    buff[2] = (num % 10) + CHAR_0;
    buff[3] = EOS;
    DexScreen_AddTextPrinterParameterized(windowId, fontId, buff, x, y, colorIdx);
}

static void DexScreen_PrintNum3RightAlign(u8 windowId, u8 fontId, u16 num, u8 x, u8 y, u8 colorIdx)
{
    u8 buff[4];
    int i;
    buff[0] = (num / 100) + CHAR_0;
    buff[1] = ((num %= 100) / 10) + CHAR_0;
    buff[2] = (num % 10) + CHAR_0;
    buff[3] = EOS;
    for (i = 0; i < 3; i++)
    {
        if (buff[i] != CHAR_0)
            break;
        buff[i] = CHAR_SPACE;
    }
    DexScreen_AddTextPrinterParameterized(windowId, fontId, buff, x, y, colorIdx);
}

static u32 DexScreen_GetDefaultPersonality(int species)
{
    switch (species)
    {
    case SPECIES_SPINDA:
        return gSaveBlock2Ptr->pokedex.spindaPersonality;
    case SPECIES_UNOWN:
        return gSaveBlock2Ptr->pokedex.unownPersonality;
    default:
        return 0;
    }
}

static void DexScreen_LoadMonPicInWindow(u8 windowId, u16 species, u16 paletteOffset)
{
    LoadMonPicInWindow(species, SHINY_ODDS, DexScreen_GetDefaultPersonality(species), TRUE, paletteOffset >> 4, windowId);
}

static void DexScreen_PrintMonDexNo(u8 windowId, u8 fontId, u16 species, u8 x, u8 y)
{
    u16 dexNum = SpeciesToNationalPokedexNum(species);
    DexScreen_AddTextPrinterParameterized(windowId, fontId, gText_PokedexNo, x, y, 0);
    DexScreen_PrintNum3LeadingZeroes(windowId, fontId, dexNum, x + 9, y, 0);
}

s8 DexScreen_GetSetPokedexFlag(u16 nationalDexNo, u8 caseId, bool8 indexIsSpecies)
{
    u8 index;
    u8 bit;
    u8 mask;
    s8 retVal;

    if (indexIsSpecies)
        nationalDexNo = SpeciesToNationalPokedexNum(nationalDexNo);

    nationalDexNo--;
    index = nationalDexNo / 8;
    bit = nationalDexNo % 8;
    mask = 1 << bit;
    retVal = 0;
    switch (caseId)
    {
    case FLAG_GET_SEEN:
        if (gSaveBlock2Ptr->pokedex.seen[index] & mask)
        {
            // Anticheat
            if ((gSaveBlock2Ptr->pokedex.seen[index] & mask) == (gSaveBlock1Ptr->seen1[index] & mask)
                && (gSaveBlock2Ptr->pokedex.seen[index] & mask) == (gSaveBlock1Ptr->seen2[index] & mask))
                retVal = 1;
        }
        break;
    case FLAG_GET_CAUGHT:
        if (gSaveBlock2Ptr->pokedex.owned[index] & mask)
        {
            // Anticheat
            if ((gSaveBlock2Ptr->pokedex.owned[index] & mask) == (gSaveBlock2Ptr->pokedex.seen[index] & mask)
                && (gSaveBlock2Ptr->pokedex.owned[index] & mask) == (gSaveBlock1Ptr->seen1[index] & mask)
                && (gSaveBlock2Ptr->pokedex.owned[index] & mask) == (gSaveBlock1Ptr->seen2[index] & mask))
                retVal = 1;
        }
        break;
    case FLAG_SET_SEEN:
        gSaveBlock2Ptr->pokedex.seen[index] |= mask;
        // Anticheat
        gSaveBlock1Ptr->seen1[index] |= mask;
        gSaveBlock1Ptr->seen2[index] |= mask;
        break;
    case FLAG_SET_CAUGHT:
        gSaveBlock2Ptr->pokedex.owned[index] |= mask;
        break;
    }
    return retVal;
}

static u16 DexScreen_GetDexCount(u8 caseId, bool8 whichDex)
{
    u16 count = 0;
    u16 i;

    switch (whichDex)
    {
    case 0: // Kanto
        for (i = 0; i < KANTO_DEX_COUNT; i++)
        {
            if (DexScreen_GetSetPokedexFlag(i + 1, caseId, FALSE))
                count++;
        }
        break;
    case 1: // National
        for (i = 0; i < NATIONAL_DEX_COUNT; i++)
        {
            if (DexScreen_GetSetPokedexFlag(i + 1, caseId, FALSE))
                count++;

        }
        break;
    }
    return count;
}

static void DexScreen_PrintControlInfo(const u8 *src)
{
    DexScreen_AddTextPrinterParameterized(1, FONT_SMALL, src, 236 - GetStringWidth(FONT_SMALL, src, 0), 2, 4);
}

bool8 DexScreen_DrawMonPicInCategoryPage(u16 species, u8 slot, u8 numSlots)
{
    struct WindowTemplate template;
    numSlots--;
    CopyToBgTilemapBufferRect_ChangePalette(3, sCategoryPageIconWindowBg, sCategoryPageIconCoords[numSlots][slot][0], sCategoryPageIconCoords[numSlots][slot][1], 8, 8, slot + 5);
    if (sPokedexScreenData->categoryMonWindowIds[slot] == 0xFF)
    {
        template = sWindowTemplate_CategoryMonIcon;
        template.tilemapLeft = sCategoryPageIconCoords[numSlots][slot][0];
        template.tilemapTop = sCategoryPageIconCoords[numSlots][slot][1];
        template.paletteNum = slot + 1;
        template.baseBlock = slot * 64 + 8;
        sPokedexScreenData->categoryMonWindowIds[slot] = AddWindow(&template);
        FillWindowPixelBuffer(sPokedexScreenData->categoryMonWindowIds[slot], PIXEL_FILL(0));
        DexScreen_LoadMonPicInWindow(sPokedexScreenData->categoryMonWindowIds[slot], species, slot * 16 + 16);
        PutWindowTilemap(sPokedexScreenData->categoryMonWindowIds[slot]);
        CopyWindowToVram(sPokedexScreenData->categoryMonWindowIds[slot], COPYWIN_GFX);
    }
    else
        PutWindowTilemap(sPokedexScreenData->categoryMonWindowIds[slot]);

    if (sPokedexScreenData->categoryMonInfoWindowIds[slot] == 0xFF)
    {
        if (species != SPECIES_NONE)
        {
            template = sWindowTemplate_CategoryMonInfo;
            template.tilemapLeft = sCategoryPageIconCoords[numSlots][slot][2];
            template.tilemapTop = sCategoryPageIconCoords[numSlots][slot][3];
            template.baseBlock = slot * 40 + 0x108;
            sPokedexScreenData->categoryMonInfoWindowIds[slot] = AddWindow(&template);
            CopyToWindowPixelBuffer(sPokedexScreenData->categoryMonInfoWindowIds[slot], sCategoryMonInfoBgTiles, 0, 0);
            DexScreen_PrintMonDexNo(sPokedexScreenData->categoryMonInfoWindowIds[slot], FONT_SMALL, species, 12, 0);
            DexScreen_AddTextPrinterParameterized(sPokedexScreenData->categoryMonInfoWindowIds[slot], FONT_NORMAL, gSpeciesNames[species], 2, 13, 0);
            if (DexScreen_GetSetPokedexFlag(species, FLAG_GET_CAUGHT, TRUE))
                BlitBitmapRectToWindow(sPokedexScreenData->categoryMonInfoWindowIds[slot], sDexScreen_CaughtIcon, 0, 0, 8, 8, 2, 3, 8, 8);
            PutWindowTilemap(sPokedexScreenData->categoryMonInfoWindowIds[slot]);
            CopyWindowToVram(sPokedexScreenData->categoryMonInfoWindowIds[slot], COPYWIN_GFX);
        }
    }
    else
        PutWindowTilemap(sPokedexScreenData->categoryMonInfoWindowIds[slot]);

    return TRUE;
}

static void DexScreen_DestroyCategoryPageMonIconAndInfoWindows(void)
{
    int i;
    for (i = 0; i < 4; i++)
    {
        DexScreen_RemoveWindow(&sPokedexScreenData->categoryMonWindowIds[i]);
        DexScreen_RemoveWindow(&sPokedexScreenData->categoryMonInfoWindowIds[i]);
    }
}

static void DexScreen_PrintCategoryPageNumbers(u8 windowId, u16 currentPage, u16 totalPages, u16 x, u16 y)
{
    u8 buffer[30];
    u8 *ptr = StringCopy(buffer, gText_Page);
    ptr = ConvertIntToDecimalStringN(ptr, currentPage, STR_CONV_MODE_RIGHT_ALIGN, 2);
    *ptr++ = CHAR_SLASH;
    ptr = ConvertIntToDecimalStringN(ptr, totalPages, STR_CONV_MODE_RIGHT_ALIGN, 2);
    DexScreen_PrintStringWithAlignment(buffer, TEXT_RIGHT);
}

static bool8 DexScreen_CreateCategoryListGfx(bool8 justRegistered)
{
    FillBgTilemapBufferRect_Palette0(3, 2, 0, 0, 30, 20);
    FillBgTilemapBufferRect_Palette0(2, 0, 0, 0, 32, 20);
    FillBgTilemapBufferRect_Palette0(1, 0, 0, 0, 32, 20);
    DexScreen_CreateCategoryPageSpeciesList(sPokedexScreenData->category, sPokedexScreenData->pageNum);
    FillWindowPixelBuffer(0, PIXEL_FILL(15));
    if (justRegistered)
    {
        DexScreen_PrintStringWithAlignment(sDexCategoryNamePtrs[sPokedexScreenData->category], TEXT_CENTER);
    }
    else
    {
        DexScreen_PrintStringWithAlignment(sDexCategoryNamePtrs[sPokedexScreenData->category], TEXT_LEFT);
        DexScreen_PrintCategoryPageNumbers(0, DexScreen_PageNumberToRenderablePages(sPokedexScreenData->pageNum), DexScreen_PageNumberToRenderablePages(sPokedexScreenData->lastPageInCategory - 1), 160, 2);
    }
    CopyWindowToVram(0, COPYWIN_GFX);
    FillWindowPixelBuffer(1, PIXEL_FILL(15));
    if (!justRegistered)
        DexScreen_PrintControlInfo(gText_PickFlipPageCheckCancel);
    CopyWindowToVram(1, COPYWIN_GFX);
    if (sPokedexScreenData->pageSpecies[0] != 0xFFFF)
        DexScreen_DrawMonPicInCategoryPage(sPokedexScreenData->pageSpecies[0], 0, sPokedexScreenData->numMonsOnPage);
    if (sPokedexScreenData->pageSpecies[1] != 0xFFFF)
        DexScreen_DrawMonPicInCategoryPage(sPokedexScreenData->pageSpecies[1], 1, sPokedexScreenData->numMonsOnPage);
    if (sPokedexScreenData->pageSpecies[2] != 0xFFFF)
        DexScreen_DrawMonPicInCategoryPage(sPokedexScreenData->pageSpecies[2], 2, sPokedexScreenData->numMonsOnPage);
    if (sPokedexScreenData->pageSpecies[3] != 0xFFFF)
        DexScreen_DrawMonPicInCategoryPage(sPokedexScreenData->pageSpecies[3], 3, sPokedexScreenData->numMonsOnPage);
    return FALSE;
}

static void DexScreen_CreateCategoryPageSelectionCursor(u8 cursorPos)
{
    int i;
    u32 palIdx;

    if (cursorPos == 0xFF)
    {
        for (i = 0; i < 4; i++)
        {
            LoadPalette(&sDexScreen_CategoryCursorPals[0], PLTT_ID(i) + PLTT_ID(5) + 2 + BG_PLTT_OFFSET, PLTT_SIZEOF(1));
            LoadPalette(&sDexScreen_CategoryCursorPals[1], PLTT_ID(i) + PLTT_ID(5) + 8 + BG_PLTT_OFFSET, PLTT_SIZEOF(1));
        }
        LoadPalette(&sDexScreen_CategoryCursorPals[0], 0x141, PLTT_SIZEOF(1));
        sPokedexScreenData->categoryPageSelectionCursorTimer = 0;
    }
    else
    {
        sPokedexScreenData->categoryPageSelectionCursorTimer++;
        if (sPokedexScreenData->categoryPageSelectionCursorTimer == 16)
            sPokedexScreenData->categoryPageSelectionCursorTimer = 0;
        palIdx = sPokedexScreenData->categoryPageSelectionCursorTimer >> 2;
        for (i = 0; i < 4; i++)
        {
            if (i == cursorPos)
            {
                LoadPalette(&sDexScreen_CategoryCursorPals[2 * palIdx + 2], PLTT_ID(i) + PLTT_ID(5) + 2 + BG_PLTT_OFFSET, PLTT_SIZEOF(1));
                LoadPalette(&sDexScreen_CategoryCursorPals[2 * palIdx + 3], PLTT_ID(i) + PLTT_ID(5) + 8 + BG_PLTT_OFFSET, PLTT_SIZEOF(1));
            }
            else
            {
                LoadPalette(&sDexScreen_CategoryCursorPals[0], PLTT_ID(i) + PLTT_ID(5) + 2 + BG_PLTT_OFFSET, PLTT_SIZEOF(1));
                LoadPalette(&sDexScreen_CategoryCursorPals[1], PLTT_ID(i) + PLTT_ID(5) + 8 + BG_PLTT_OFFSET, PLTT_SIZEOF(1));
            }
        }
        LoadPalette(&sDexScreen_CategoryCursorPals[2 * palIdx + 2], OBJ_PLTT_ID(4) + 1, PLTT_SIZEOF(1));
    }
}

static void DexScreen_UpdateCategoryPageCursorObject(u8 taskId, u8 cursorPos, u8 numMonsInPage)
{
    numMonsInPage--;
    ListMenuUpdateCursorObject(taskId, sCategoryPageIconCoords[numMonsInPage][cursorPos][2] * 8, sCategoryPageIconCoords[numMonsInPage][cursorPos][3] * 8, 0);
}

bool8 DexPage_TileBuffer_CopyCol(const u16 *srcBuf, u8 srcCol, u16 *dstBuf, u8 dstCol)
{
    int i;
    const u16 *src = &srcBuf[srcCol];
    u16 *dst = &dstBuf[dstCol];
    for (i = 0; i < 20; i++)
    {
        *dst = *src;
        dst += 32;
        src += 32;
    }
    return FALSE;
}

bool8 DexPage_TileBuffer_FillCol(u16 tileNo, u16 *tileBuf, u8 x)
{
    int i;
    u16 *dst = &tileBuf[x];
    for (i = 0; i < 20; i++)
    {
        *dst = tileNo;
        dst += 32;
    }
    return FALSE;
}

bool8 DexScreen_TurnCategoryPage_BgEffect(u8 page)
{
    int dstCol;
    int srcCol;
    u16 *bg1buff = GetBgTilemapBuffer(1);
    u16 *bg2buff = GetBgTilemapBuffer(2);
    u16 *bg3buff = GetBgTilemapBuffer(3);
    u16 *bg1mem = sPokedexScreenData->bgBufsMem + 0x800;
    u16 *bg2mem = sPokedexScreenData->bgBufsMem + 0x400;
    u16 *bg3mem = sPokedexScreenData->bgBufsMem + 0x000;
    for (dstCol = 0; dstCol < 30; dstCol++)
    {
        srcCol = sDexScreenPageTurnColumns[page][dstCol];
        if (srcCol == 30)
        {
            DexPage_TileBuffer_FillCol(0x000, bg1buff, dstCol);
            DexPage_TileBuffer_FillCol(0x000, bg2buff, dstCol);
            DexPage_TileBuffer_FillCol(0x00C, bg3buff, dstCol);
        }
        else
        {
            DexPage_TileBuffer_CopyCol(bg1mem, srcCol, bg1buff, dstCol);
            DexPage_TileBuffer_CopyCol(bg2mem, srcCol, bg2buff, dstCol);
            DexPage_TileBuffer_CopyCol(bg3mem, srcCol, bg3buff, dstCol);
        }
    }
    CopyBgTilemapBufferToVram(1);
    CopyBgTilemapBufferToVram(2);
    CopyBgTilemapBufferToVram(3);
    return FALSE;
}

/*
 * Direction = 0: Left; 1: Right
 */
static bool8 DexScreen_FlipCategoryPageInDirection(u8 direction)
{
    u16 color;
    if (IsNationalPokedexEnabled())
        color = sNationalDexPalette[7];
    else
        color = sKantoDexPalette[7];
    switch (sPokedexScreenData->data[0])
    {
    case 0:
        sPokedexScreenData->bgBufsMem = Alloc(3 * BG_SCREEN_SIZE);
        if (direction)
            sPokedexScreenData->data[0] = 6;
        else
            sPokedexScreenData->data[0] = 2;
        break;
    case 1:
        Free(sPokedexScreenData->bgBufsMem);
        return TRUE;
        // Go left
    case 2:
        BeginNormalPaletteFade(0x00007FFF, 0, 0, 16, color);
        sPokedexScreenData->data[0]++;
        break;
    case 3:
        FillBgTilemapBufferRect_Palette0(3, 0x00C, 0, 0, 30, 20);
        FillBgTilemapBufferRect_Palette0(2, 0x000, 0, 0, 32, 20);
        FillBgTilemapBufferRect_Palette0(1, 0x000, 0, 0, 32, 20);
        CopyBgTilemapBufferToVram(1);
        CopyBgTilemapBufferToVram(2);
        CopyBgTilemapBufferToVram(3);
        sPokedexScreenData->data[0]++;
        break;
    case 4:
        BeginNormalPaletteFade(0x00007FFF, 0, 0, 0, color);
        DexScreen_CreateCategoryListGfx(FALSE);
        CpuFastCopy(GetBgTilemapBuffer(3), &sPokedexScreenData->bgBufsMem[0 * BG_SCREEN_SIZE / 2], BG_SCREEN_SIZE);
        CpuFastCopy(GetBgTilemapBuffer(2), &sPokedexScreenData->bgBufsMem[1 * BG_SCREEN_SIZE / 2], BG_SCREEN_SIZE);
        CpuFastCopy(GetBgTilemapBuffer(1), &sPokedexScreenData->bgBufsMem[2 * BG_SCREEN_SIZE / 2], BG_SCREEN_SIZE);
        FillBgTilemapBufferRect_Palette0(3, 0x00C, 0, 0, 30, 20);
        FillBgTilemapBufferRect_Palette0(2, 0x000, 0, 0, 32, 20);
        FillBgTilemapBufferRect_Palette0(1, 0x000, 0, 0, 32, 20);

        sPokedexScreenData->data[1] = 0;
        sPokedexScreenData->data[0]++;
        PlaySE(SE_BALL_TRAY_ENTER);
        break;
    case 5:
        if (sPokedexScreenData->data[1] < 10)
        {
            DexScreen_TurnCategoryPage_BgEffect(sPokedexScreenData->data[1]);
            sPokedexScreenData->data[1]++;
        }
        else
        {
            sPokedexScreenData->data[0] = 1;
        }
        break;
        // Go right
    case 6:
        CpuFastCopy(GetBgTilemapBuffer(3), &sPokedexScreenData->bgBufsMem[0 * BG_SCREEN_SIZE / 2], BG_SCREEN_SIZE);
        CpuFastCopy(GetBgTilemapBuffer(2), &sPokedexScreenData->bgBufsMem[1 * BG_SCREEN_SIZE / 2], BG_SCREEN_SIZE);
        CpuFastCopy(GetBgTilemapBuffer(1), &sPokedexScreenData->bgBufsMem[2 * BG_SCREEN_SIZE / 2], BG_SCREEN_SIZE);

        sPokedexScreenData->data[1] = 9;
        sPokedexScreenData->data[0]++;
        PlaySE(SE_BALL_TRAY_ENTER);
        break;
    case 7:
        if (sPokedexScreenData->data[1] != 0)
        {
            DexScreen_TurnCategoryPage_BgEffect(sPokedexScreenData->data[1]);
            sPokedexScreenData->data[1]--;
        }
        else
        {
#ifdef BUGFIX
            DexScreen_TurnCategoryPage_BgEffect(0);
#else
            DexScreen_TurnCategoryPage_BgEffect(sPokedexScreenData->data[0]);
#endif
            BeginNormalPaletteFade(0x00007FFF, 0, 16, 16, color);
            sPokedexScreenData->data[0]++;
        }
        break;
    case 8:
        gPaletteFade.bufferTransferDisabled = TRUE;
        DexScreen_CreateCategoryListGfx(FALSE);
        CopyBgTilemapBufferToVram(1);
        CopyBgTilemapBufferToVram(2);
        CopyBgTilemapBufferToVram(3);
        sPokedexScreenData->data[0]++;
        break;
    case 9:
        gPaletteFade.bufferTransferDisabled = FALSE;
        BeginNormalPaletteFade(0x00007FFF, 0, 16, 0, color);
        sPokedexScreenData->data[0] = 1;
        break;
    }
    return FALSE;
}

// Scale from 0 to 6
void DexScreen_DexPageZoomEffectFrame(u8 bg, u8 scale)
{
    u8 tileLeft, tileTop, width, height;
    s16 left, top, divY;

    if (!sPokedexScreenData->numMonsOnPage)
    {
        tileLeft = sCategoryPageIconCoords[0][0][2];
        tileTop = sCategoryPageIconCoords[0][0][3];
    }
    else
    {
        tileLeft = sCategoryPageIconCoords[sPokedexScreenData->numMonsOnPage - 1][sPokedexScreenData->categoryCursorPosInPage][2];
        tileTop = sCategoryPageIconCoords[sPokedexScreenData->numMonsOnPage - 1][sPokedexScreenData->categoryCursorPosInPage][3];
    }

    width = 6 + (scale * 4);
    height = 3 + (scale * 2);
    if (width >= 28) // Make sure it's not wider than the screen
        width = 28;
    if (height >= 14) // Make sure it's not taller than the screen
        height = 14;

    left = tileLeft - ((scale * 4) / 2);
    top = tileTop - ((scale * 2) / 2);
    if ((left + width + 2) >= 30) // Don't wrap right...
        left -= ((left + width + 2) - 30);
    else if (left < 0) // ... left ...
        left = 0;
    if ((top + height + 2) >= 18) // ... down ...
        top -= ((top + height + 2) - 18);
    else if (top < 2) // or up.
        top = 2;

    divY = (top + 1) + ((height / 2) + 1); // The horizontal divider

    // Top edge
    FillBgTilemapBufferRect_Palette0(bg, 4, left, top, 1, 1);
    FillBgTilemapBufferRect_Palette0(bg, 5, left + 1, top, width, 1);
    FillBgTilemapBufferRect_Palette0(bg, BG_TILE_H_FLIP(4), left + 1 + width, top, 1, 1);

    // Bottom edge
    FillBgTilemapBufferRect_Palette0(bg, 10, left, top + 1 + height, 1, 1);
    FillBgTilemapBufferRect_Palette0(bg, 11, left + 1, top + 1 + height, width, 1);
    FillBgTilemapBufferRect_Palette0(bg, BG_TILE_H_FLIP(10), left + 1 + width, top + 1 + height, 1, 1);

    // Left edge
    FillBgTilemapBufferRect_Palette0(bg, 6, left, top + 1, 1, divY - top - 1);
    FillBgTilemapBufferRect_Palette0(bg, 7, left, divY, 1, 1);
    FillBgTilemapBufferRect_Palette0(bg, 9, left, divY + 1, 1, top + height - divY);

    // Right edge
    FillBgTilemapBufferRect_Palette0(bg, BG_TILE_H_FLIP(6), left + 1 + width, top + 1, 1, divY - top - 1);
    FillBgTilemapBufferRect_Palette0(bg, BG_TILE_H_FLIP(7), left + 1 + width, divY, 1, 1);
    FillBgTilemapBufferRect_Palette0(bg, BG_TILE_H_FLIP(9), left + 1 + width, divY + 1, 1, top + height - divY);

    // Interior
    FillBgTilemapBufferRect_Palette0(bg, 1, left + 1, top + 1, width, divY - top - 1);
    FillBgTilemapBufferRect_Palette0(bg, 8, left + 1, divY, width, 1);
    FillBgTilemapBufferRect_Palette0(bg, 2, left + 1, divY + 1, width, top + height - divY);
}

void DexScreen_PrintMonCategory(u8 windowId, u16 species, u8 x, u8 y)
{
    u8 * categoryName;
    u8 index, categoryStr[12];

    species = SpeciesToNationalPokedexNum(species);

    categoryName = (u8 *)gPokedexEntries[species].categoryName;
    index = 0;
    if (DexScreen_GetSetPokedexFlag(species, FLAG_GET_CAUGHT, FALSE))
    {
#if REVISION == 0
        while ((categoryName[index] != CHAR_SPACE) && (index < 11))
#else
        while ((categoryName[index] != EOS) && (index < 11))
#endif
        {
            categoryStr[index] = categoryName[index];
            index++;
        }
    }
    else
    {
        while (index < 11)
        {
            categoryStr[index] = CHAR_QUESTION_MARK;
            index++;
        }
    }

    categoryStr[index] = EOS;

    DexScreen_AddTextPrinterParameterized(windowId, FONT_SMALL, categoryStr, x, y, 0);
    x += GetStringWidth(FONT_SMALL, categoryStr, 0);
    DexScreen_AddTextPrinterParameterized(windowId, FONT_SMALL, gText_PokedexPokemon, x, y, 0);
}

void DexScreen_PrintMonHeight(u8 windowId, u16 species, u8 x, u8 y)
{
    u16 height;
    u32 inches, feet;
    const u8 *labelText;
    u8 buffer[32];
    u8 i;

    species = SpeciesToNationalPokedexNum(species);
    height = gPokedexEntries[species].height;
    labelText = gText_HT;

    i = 0;
    buffer[i++] = EXT_CTRL_CODE_BEGIN;
    buffer[i++] = EXT_CTRL_CODE_MIN_LETTER_SPACING;
    buffer[i++] = 5;
    buffer[i++] = CHAR_SPACE;

    if (DexScreen_GetSetPokedexFlag(species, FLAG_GET_CAUGHT, FALSE))
    {
        inches = 10000 * height / 254; // actually tenths of inches here
        if (inches % 10 >= 5)
            inches += 10;
        feet = inches / 120;
        inches = (inches - (feet * 120)) / 10;
        if (feet / 10 == 0)
        {
            buffer[i++] = 0;
            buffer[i++] = feet + CHAR_0;
        }
        else
        {
            buffer[i++] = feet / 10 + CHAR_0;
            buffer[i++] = feet % 10 + CHAR_0;
        }
        buffer[i++] = CHAR_SGL_QUOTE_RIGHT;
        buffer[i++] = inches / 10 + CHAR_0;
        buffer[i++] = inches % 10 + CHAR_0;
        buffer[i++] = CHAR_DBL_QUOTE_RIGHT;
        buffer[i++] = EOS;
    }
    else
    {
        buffer[i++] = CHAR_QUESTION_MARK;
        buffer[i++] = CHAR_QUESTION_MARK;
        buffer[i++] = CHAR_SGL_QUOTE_RIGHT;
        buffer[i++] = CHAR_QUESTION_MARK;
        buffer[i++] = CHAR_QUESTION_MARK;
        buffer[i++] = CHAR_DBL_QUOTE_RIGHT;
    }

    buffer[i++] = EOS;
    DexScreen_AddTextPrinterParameterized(windowId, FONT_SMALL, labelText, x, y, 0);
    x += 30;
    DexScreen_AddTextPrinterParameterized(windowId, FONT_SMALL, buffer, x, y, 0);
}

void DexScreen_PrintMonWeight(u8 windowId, u16 species, u8 x, u8 y)
{
    u16 weight;
    u32 lbs;
    bool8 output;
    const u8 * labelText;
    const u8 * lbsText;
    u8 buffer[32];
    u8 i;
    u32 j;

    species = SpeciesToNationalPokedexNum(species);
    weight = gPokedexEntries[species].weight;
    labelText = gText_WT;
    lbsText = gText_Lbs;

    i = 0;
    buffer[i++] = EXT_CTRL_CODE_BEGIN;
    buffer[i++] = EXT_CTRL_CODE_MIN_LETTER_SPACING;
    buffer[i++] = 5;

    if (DexScreen_GetSetPokedexFlag(species, FLAG_GET_CAUGHT, FALSE))
    {
        lbs = (weight * 100000) / 4536; // Convert to hundredths of lb

        // Round up to the nearest 0.1 lb
        if (lbs % 10 >= 5)
            lbs += 10;

        output = FALSE;

        if ((buffer[i] = (lbs / 100000) + CHAR_0) == CHAR_0 && !output)
        {
            buffer[i++] = CHAR_SPACE;
        }
        else
        {
            output = TRUE;
            i++;
        }

        lbs %= 100000;
        if ((buffer[i] = (lbs / 10000) + CHAR_0) == CHAR_0 && !output)
        {
            buffer[i++] = CHAR_SPACE;
        }
        else
        {
            output = TRUE;
            i++;
        }

        lbs %= 10000;
        if ((buffer[i] = (lbs / 1000) + CHAR_0) == CHAR_0 && !output)
        {
            buffer[i++] = CHAR_SPACE;
        }
        else
        {
            output = TRUE;
            i++;
        }

        lbs %= 1000;
        buffer[i++] = (lbs / 100) + CHAR_0;
        lbs %= 100;
        buffer[i++] = CHAR_PERIOD;
        buffer[i++] = (lbs / 10) + CHAR_0;
    }
    else
    {
        buffer[i++] = CHAR_QUESTION_MARK;
        buffer[i++] = CHAR_QUESTION_MARK;
        buffer[i++] = CHAR_QUESTION_MARK;
        buffer[i++] = CHAR_QUESTION_MARK;
        buffer[i++] = CHAR_PERIOD;
        buffer[i++] = CHAR_QUESTION_MARK;
    }
    buffer[i++] = CHAR_SPACE;
    buffer[i++] = EXT_CTRL_CODE_BEGIN;
    buffer[i++] = EXT_CTRL_CODE_MIN_LETTER_SPACING;
    buffer[i++] = 0;

    for (j = 0; j < 33 - i && lbsText[j] != EOS; j++)
        buffer[i + j] = lbsText[j];

    buffer[i + j] = EOS;
    DexScreen_AddTextPrinterParameterized(windowId, FONT_SMALL, labelText, x, y, 0);
    x += 30;
    DexScreen_AddTextPrinterParameterized(windowId, FONT_SMALL, buffer, x, y, 0);
}

void DexScreen_PrintMonFlavorText(u8 windowId, u16 species, u8 x, u8 y)
{
    struct TextPrinterTemplate printerTemplate;
    u16 length;
    s32 xCenter;

    species = SpeciesToNationalPokedexNum(species);

    if (DexScreen_GetSetPokedexFlag(species, FLAG_GET_CAUGHT, FALSE))
    {
        printerTemplate.currentChar = gPokedexEntries[species].description;
        printerTemplate.windowId = windowId;
        printerTemplate.fontId = FONT_NORMAL;
        printerTemplate.letterSpacing = 1;
        printerTemplate.lineSpacing = 0;
        printerTemplate.unk = 0;
        printerTemplate.fgColor = 1;
        printerTemplate.bgColor = 0;
        printerTemplate.shadowColor = 2;

        length = GetStringWidth(FONT_NORMAL, gPokedexEntries[species].description, 0);
        xCenter = x + (240 - length) / 2;

        if (xCenter > 0)
            x = xCenter;
        else
            x = 0;

        printerTemplate.x = x;
        printerTemplate.y = y;
        printerTemplate.currentX = x;
        printerTemplate.currentY = y;

        AddTextPrinter(&printerTemplate, TEXT_SKIP_DRAW, NULL);
    }
}

void DexScreen_DrawMonFootprint(u8 windowId, u16 species, u8 x, u8 y)
{
    u16 i, j, unused, tileIdx;
    u8 footprintPixel, footprintTile;
    u8 * buffer;
    u8 * footprint;

    if (!(DexScreen_GetSetPokedexFlag(species, FLAG_GET_CAUGHT, TRUE)))
        return;
    footprint = (u8 *)(gMonFootprintTable[species]);
    buffer = gDecompressionBuffer;
    unused = 0;
    tileIdx = 0;

    // Expand 1bpp to 4bpp
    for (i = 0; i < 32; i++)
    {
        footprintPixel = footprint[i];
        for (j = 0; j < 8 / 2; j++)
        {
            footprintTile = 0;
            if (footprintPixel & (1 << (j * 2)))
                footprintTile |= 0x01;
            if (footprintPixel & (2 << (j * 2)))
                footprintTile |= 0x10;
            buffer[tileIdx] = footprintTile;
            tileIdx++;
        }
    }
    BlitBitmapRectToWindow(windowId, buffer, 0, 0, 16, 16, x, y, 16, 16);
}

static u8 DexScreen_DrawMonDexPage(bool8 justRegistered)
{
    DexScreen_DexPageZoomEffectFrame(3, 6);
    FillBgTilemapBufferRect_Palette0(2, 0, 0, 0, 30, 20);
    FillBgTilemapBufferRect_Palette0(1, 0, 0, 0, 30, 20);
    FillBgTilemapBufferRect_Palette0(0, 0, 0, 2, 30, 16);

    sPokedexScreenData->windowIds[0] = AddWindow(&sWindowTemplate_DexEntry_MonPic);
    sPokedexScreenData->windowIds[1] = AddWindow(&sWindowTemplate_DexEntry_SpeciesStats);
    sPokedexScreenData->windowIds[2] = AddWindow(&sWindowTemplate_DexEntry_FlavorText);

    // Mon pic
    FillWindowPixelBuffer(sPokedexScreenData->windowIds[0], PIXEL_FILL(0));
    DexScreen_LoadMonPicInWindow(sPokedexScreenData->windowIds[0], sPokedexScreenData->dexSpecies, 144);
    PutWindowTilemap(sPokedexScreenData->windowIds[0]);
    CopyWindowToVram(sPokedexScreenData->windowIds[0], COPYWIN_GFX);

    // Species stats
    FillWindowPixelBuffer(sPokedexScreenData->windowIds[1], PIXEL_FILL(0));
    DexScreen_PrintMonDexNo(sPokedexScreenData->windowIds[1], FONT_SMALL, sPokedexScreenData->dexSpecies, 0, 8);
    DexScreen_AddTextPrinterParameterized(sPokedexScreenData->windowIds[1], FONT_NORMAL, gSpeciesNames[sPokedexScreenData->dexSpecies], 28, 8, 0);
    DexScreen_PrintMonCategory(sPokedexScreenData->windowIds[1], sPokedexScreenData->dexSpecies, 0, 24);
    DexScreen_PrintMonHeight(sPokedexScreenData->windowIds[1], sPokedexScreenData->dexSpecies, 0, 36);
    DexScreen_PrintMonWeight(sPokedexScreenData->windowIds[1], sPokedexScreenData->dexSpecies, 0, 48);
    DexScreen_DrawMonFootprint(sPokedexScreenData->windowIds[1], sPokedexScreenData->dexSpecies, 88, 40);
    PutWindowTilemap(sPokedexScreenData->windowIds[1]);
    CopyWindowToVram(sPokedexScreenData->windowIds[1], COPYWIN_GFX);

    // Dex entry
    FillWindowPixelBuffer(sPokedexScreenData->windowIds[2], PIXEL_FILL(0));
    DexScreen_PrintMonFlavorText(sPokedexScreenData->windowIds[2], sPokedexScreenData->dexSpecies, 0, 8);
    PutWindowTilemap(sPokedexScreenData->windowIds[2]);
    CopyWindowToVram(sPokedexScreenData->windowIds[2], COPYWIN_GFX);

    // Control info
    FillWindowPixelBuffer(1, PIXEL_FILL(15));
    if (justRegistered == FALSE)
    {
        DexScreen_AddTextPrinterParameterized(1, FONT_SMALL, gText_Cry, 8, 2, 4);
        DexScreen_PrintControlInfo(gText_NextDataCancel);
    }
    else
        // Just registered
        DexScreen_PrintControlInfo(gText_Next);
    PutWindowTilemap(1);
    CopyWindowToVram(1, COPYWIN_GFX);

    return 1;
}

u8 RemoveDexPageWindows(void)
{
    DexScreen_RemoveWindow(&sPokedexScreenData->windowIds[0]);
    DexScreen_RemoveWindow(&sPokedexScreenData->windowIds[1]);
    DexScreen_RemoveWindow(&sPokedexScreenData->windowIds[2]);

    return 0;
}

u8 DexScreen_DrawMonAreaPage(void)
{
    int i;
    u8 width, height;
    bool8 monIsCaught;
    s16 left, top;
    u16 speciesId, species;
    u16 kantoMapVoff;

    species = sPokedexScreenData->dexSpecies;
    speciesId = SpeciesToNationalPokedexNum(species);
    monIsCaught = DexScreen_GetSetPokedexFlag(species, FLAG_GET_CAUGHT, TRUE);
    width = 28;
    height = 14;
    left = 0;
    top = 2;

    FillBgTilemapBufferRect_Palette0(3, 4, left, top, 1, 1);
    FillBgTilemapBufferRect_Palette0(3, BG_TILE_H_FLIP(4), left + 1 + width, top, 1, 1);
    FillBgTilemapBufferRect_Palette0(3, BG_TILE_V_FLIP(4), left, top + 1 + height, 1, 1);
    FillBgTilemapBufferRect_Palette0(3, BG_TILE_H_V_FLIP(4), left + 1 + width, top + 1 + height, 1, 1);
    FillBgTilemapBufferRect_Palette0(3, 5, left + 1, top, width, 1);
    FillBgTilemapBufferRect_Palette0(3, BG_TILE_V_FLIP(5), left + 1, top + 1 + height, width, 1);
    FillBgTilemapBufferRect_Palette0(3, 6, left, top + 1, 1, height);
    FillBgTilemapBufferRect_Palette0(3, BG_TILE_H_FLIP(6), left + 1 + width, top + 1, 1, height);
    FillBgTilemapBufferRect_Palette0(3, 1, left + 1, top + 1, width, height);
    FillBgTilemapBufferRect_Palette0(0, 0, 0, 2, 30, 16);

    width = 10;
    height = 6;
    left = 1;
    top = 9;

    FillBgTilemapBufferRect_Palette0(0, 29, left, top, 1, 1);
    FillBgTilemapBufferRect_Palette0(0, BG_TILE_H_FLIP(29), left + 1 + width, top, 1, 1);
    FillBgTilemapBufferRect_Palette0(0, BG_TILE_V_FLIP(29), left, top + 1 + height, 1, 1);
    FillBgTilemapBufferRect_Palette0(0, BG_TILE_H_V_FLIP(29), left + 1 + width, top + 1 + height, 1, 1);
    FillBgTilemapBufferRect_Palette0(0, 30, left + 1, top, width, 1);
    FillBgTilemapBufferRect_Palette0(0, BG_TILE_V_FLIP(30), left + 1, top + 1 + height, width, 1);
    FillBgTilemapBufferRect_Palette0(0, 31, left, top + 1, 1, height);
    FillBgTilemapBufferRect_Palette0(0, BG_TILE_H_FLIP(31), left + 1 + width, top + 1, 1, height);
    FillBgTilemapBufferRect_Palette0(2, 0, 0, 0, 30, 20);
    FillBgTilemapBufferRect_Palette0(1, 0, 0, 0, 30, 20);

    sPokedexScreenData->unlockedSeviiAreas = GetUnlockedSeviiAreas();
    kantoMapVoff = 4;
    // If any of the postgame islands are unlocked, Kanto map needs to be flush with the
    // top of the screen.
    for (i = 3; i < 7; i++)
        if ((sPokedexScreenData->unlockedSeviiAreas >> i) & 1)
            kantoMapVoff = 0;

    sPokedexScreenData->windowIds[0] = AddWindow(&sWindowTemplate_AreaMap_Kanto);
    CopyToWindowPixelBuffer(sPokedexScreenData->windowIds[0], (void *)sTilemap_AreaMap_Kanto, 0, 0);
    SetWindowAttribute(sPokedexScreenData->windowIds[0], WINDOW_TILEMAP_TOP,
                       GetWindowAttribute(sPokedexScreenData->windowIds[0], WINDOW_TILEMAP_TOP) + kantoMapVoff);
    PutWindowTilemap(sPokedexScreenData->windowIds[0]);
    for (i = 0; i < 7; i++)
        if ((sPokedexScreenData->unlockedSeviiAreas >> i) & 1)
        {
            sPokedexScreenData->windowIds[i + 1] = AddWindow(sAreaMapStructs_SeviiIslands[i].window);
            CopyToWindowPixelBuffer(sPokedexScreenData->windowIds[i + 1], sAreaMapStructs_SeviiIslands[i].tiles, 0, 0);
            SetWindowAttribute(sPokedexScreenData->windowIds[i + 1], WINDOW_TILEMAP_TOP, GetWindowAttribute(sPokedexScreenData->windowIds[i + 1], WINDOW_TILEMAP_TOP) + kantoMapVoff);
            PutWindowTilemap(sPokedexScreenData->windowIds[i + 1]);
            CopyWindowToVram(sPokedexScreenData->windowIds[i + 1], COPYWIN_GFX);
        }
    sPokedexScreenData->windowIds[8] = AddWindow(&sWindowTemplate_AreaMap_SpeciesName);
    sPokedexScreenData->windowIds[9] = AddWindow(&sWindowTemplate_AreaMap_Size);
    sPokedexScreenData->windowIds[10] = AddWindow(&sWindowTemplate_AreaMap_Area);
    sPokedexScreenData->windowIds[11] = AddWindow(&sWindowTemplate_AreaMap_MonIcon);
    sPokedexScreenData->windowIds[12] = AddWindow(&sWindowTemplate_AreaMap_MonTypes);

    // Draw the mon icon
    FillWindowPixelBuffer(sPokedexScreenData->windowIds[11], PIXEL_FILL(0));
    ListMenu_LoadMonIconPalette(BG_PLTT_ID(10), species);
    ListMenu_DrawMonIconGraphics(sPokedexScreenData->windowIds[11], species, DexScreen_GetDefaultPersonality(species), 0, 0);
    PutWindowTilemap(sPokedexScreenData->windowIds[11]);
    CopyWindowToVram(sPokedexScreenData->windowIds[11], COPYWIN_GFX);

    // Print "Size"
    FillWindowPixelBuffer(sPokedexScreenData->windowIds[9], PIXEL_FILL(0));
    {
        s32 strWidth = GetStringWidth(FONT_SMALL, gText_Size, 0);
        DexScreen_AddTextPrinterParameterized(sPokedexScreenData->windowIds[9], FONT_SMALL, gText_Size, (sWindowTemplate_AreaMap_Size.width * 8 - strWidth) / 2, 4, 0);
    }
    PutWindowTilemap(sPokedexScreenData->windowIds[9]);
    CopyWindowToVram(sPokedexScreenData->windowIds[9], COPYWIN_GFX);

    // Print "Area"
    FillWindowPixelBuffer(sPokedexScreenData->windowIds[10], PIXEL_FILL(0));
    {
        s32 strWidth = GetStringWidth(FONT_SMALL, gText_Area, 0);
        DexScreen_AddTextPrinterParameterized(sPokedexScreenData->windowIds[10], FONT_SMALL, gText_Area, (sWindowTemplate_AreaMap_Area.width * 8 - strWidth) / 2, 4, 0);
    }
    SetWindowAttribute(sPokedexScreenData->windowIds[10], WINDOW_TILEMAP_TOP, GetWindowAttribute(sPokedexScreenData->windowIds[10], WINDOW_TILEMAP_TOP) + kantoMapVoff);
    PutWindowTilemap(sPokedexScreenData->windowIds[10]);
    CopyWindowToVram(sPokedexScreenData->windowIds[10], COPYWIN_GFX);

    // Print species name
    FillWindowPixelBuffer(sPokedexScreenData->windowIds[8], PIXEL_FILL(0));
    DexScreen_PrintMonDexNo(sPokedexScreenData->windowIds[8], FONT_SMALL, species, 0, 0);
    DexScreen_AddTextPrinterParameterized(sPokedexScreenData->windowIds[8], FONT_NORMAL, gSpeciesNames[species], 3, 12, 0);
    PutWindowTilemap(sPokedexScreenData->windowIds[8]);
    CopyWindowToVram(sPokedexScreenData->windowIds[8], COPYWIN_GFX);

    // Type icons
    FillWindowPixelBuffer(sPokedexScreenData->windowIds[12], PIXEL_FILL(0));
    ListMenuLoadStdPalAt(BG_PLTT_ID(11), 1);

    if (monIsCaught)
    {
        BlitMenuInfoIcon(sPokedexScreenData->windowIds[12], 1 + gSpeciesInfo[species].types[0], 0, 1);
        if (gSpeciesInfo[species].types[0] != gSpeciesInfo[species].types[1])
            BlitMenuInfoIcon(sPokedexScreenData->windowIds[12], 1 + gSpeciesInfo[species].types[1], 32, 1);
    }
    PutWindowTilemap(sPokedexScreenData->windowIds[12]);
    CopyWindowToVram(sPokedexScreenData->windowIds[12], COPYWIN_GFX);

    // Show size comparison
    ResetAllPicSprites();
    LoadPalette(sPalette_Silhouette, OBJ_PLTT_ID(2), PLTT_SIZE_4BPP);

    if (monIsCaught)
    {
        sPokedexScreenData->windowIds[14] = CreateMonPicSprite_HandleDeoxys(species, SHINY_ODDS, DexScreen_GetDefaultPersonality(species), TRUE, 40, 104, 0, 0xFFFF);
        gSprites[sPokedexScreenData->windowIds[14]].oam.paletteNum = 2;
        gSprites[sPokedexScreenData->windowIds[14]].oam.affineMode = ST_OAM_AFFINE_NORMAL;
        gSprites[sPokedexScreenData->windowIds[14]].oam.matrixNum = 2;
        gSprites[sPokedexScreenData->windowIds[14]].oam.priority = 1;
        gSprites[sPokedexScreenData->windowIds[14]].y2 = gPokedexEntries[speciesId].pokemonOffset;
        SetOamMatrix(2, gPokedexEntries[speciesId].pokemonScale, 0, 0, gPokedexEntries[speciesId].pokemonScale);
        sPokedexScreenData->windowIds[15] = CreateTrainerPicSprite(PlayerGenderToFrontTrainerPicId(gSaveBlock2Ptr->playerGender, TRUE), 1, 80, 104, 0, 0xFFFF);
        gSprites[sPokedexScreenData->windowIds[15]].oam.paletteNum = 2;
        gSprites[sPokedexScreenData->windowIds[15]].oam.affineMode = ST_OAM_AFFINE_NORMAL;
        gSprites[sPokedexScreenData->windowIds[15]].oam.matrixNum = 1;
        gSprites[sPokedexScreenData->windowIds[15]].oam.priority = 1;
        gSprites[sPokedexScreenData->windowIds[15]].y2 = gPokedexEntries[speciesId].trainerOffset;
        SetOamMatrix(1, gPokedexEntries[speciesId].trainerScale, 0, 0, gPokedexEntries[speciesId].trainerScale);
    }
    else
    {
        sPokedexScreenData->windowIds[14] = 0xff;
        sPokedexScreenData->windowIds[15] = 0xff;
    }

    // Create the area markers
    sPokedexScreenData->areaMarkersTaskId = CreatePokedexAreaMarkers(species, TAG_AREA_MARKERS, 3, kantoMapVoff * 8);
    if (GetNumPokedexAreaMarkers(sPokedexScreenData->areaMarkersTaskId) == 0)
    {
        // No markers, display "Area Unknown"
        BlitBitmapRectToWindow(sPokedexScreenData->windowIds[0], (void *)sBlitTiles_WideEllipse, 0, 0, 88, 16, 4, 28, 88, 16);
        {
            s32 strWidth = GetStringWidth(FONT_SMALL, gText_AreaUnknown, 0);
            DexScreen_AddTextPrinterParameterized(sPokedexScreenData->windowIds[0], FONT_SMALL, gText_AreaUnknown, (96 - strWidth) / 2, 29, 0);
        }
    }
    CopyWindowToVram(sPokedexScreenData->windowIds[0], COPYWIN_GFX);

    // Draw the control info
    FillWindowPixelBuffer(1, PIXEL_FILL(15));
    DexScreen_AddTextPrinterParameterized(1, FONT_SMALL, gText_Cry, 8, 2, 4);
    DexScreen_PrintControlInfo(gText_CancelPreviousData);
    PutWindowTilemap(1);
    CopyWindowToVram(1, COPYWIN_GFX);

    return 1;
}


u8 DexScreen_DestroyAreaScreenResources(void)
{
    int i;

    DestroyPokedexAreaMarkers(sPokedexScreenData->areaMarkersTaskId);

    for (i = 0; i < 13; i++)
        DexScreen_RemoveWindow(&sPokedexScreenData->windowIds[i]);
    if (sPokedexScreenData->windowIds[15] != 0xff)
        FreeAndDestroyTrainerPicSprite(sPokedexScreenData->windowIds[15]);
    if (sPokedexScreenData->windowIds[14] != 0xff)
        FreeAndDestroyMonPicSprite(sPokedexScreenData->windowIds[14]);
    return 0;
}

static int DexScreen_CanShowMonInDex(u16 species)
{
    if (IsNationalPokedexEnabled() == TRUE)
        return TRUE;
    if (SpeciesToNationalPokedexNum(species) <= KANTO_DEX_COUNT)
        return TRUE;
    return FALSE;
}

static u8 DexScreen_IsPageUnlocked(u8 categoryNum, u8 pageNum)
{
    int i, count;
    u16 species;

    count = gDexCategories[categoryNum].page[pageNum].count;

    for (i = 0; i < 4; i++)
    {
        if (i < count)
        {
            species = gDexCategories[categoryNum].page[pageNum].species[i];
            if (DexScreen_CanShowMonInDex(species) == TRUE && DexScreen_GetSetPokedexFlag(species, FLAG_GET_SEEN, TRUE))
                return TRUE;
        }
    }
    return FALSE;
}

static bool8 DexScreen_IsCategoryUnlocked(u8 categoryNum)
{
    int i;
    u8 count;

    count = gDexCategories[categoryNum].count;

    for (i = 0; i < count; i++)
        if (DexScreen_IsPageUnlocked(categoryNum, i))
            return 1;

    return 0;
}

void DexScreen_CreateCategoryPageSpeciesList(u8 categoryNum, u8 pageNum)
{
    int i, count;
    u16 species;

    count = gDexCategories[categoryNum].page[pageNum].count;
    sPokedexScreenData->numMonsOnPage = 0;

    for (i = 0; i < 4; i++)
        sPokedexScreenData->pageSpecies[i] = 0xffff;
    for (i = 0; i < count; i++)
    {
        species = gDexCategories[categoryNum].page[pageNum].species[i];
        if (DexScreen_CanShowMonInDex(species) == TRUE && DexScreen_GetSetPokedexFlag(species, FLAG_GET_SEEN, TRUE))
        {
            sPokedexScreenData->pageSpecies[sPokedexScreenData->numMonsOnPage] = gDexCategories[categoryNum].page[pageNum].species[i];
            sPokedexScreenData->numMonsOnPage++;
        }
    }
}

static u8 DexScreen_GetPageLimitsForCategory(u8 category)
{
    int i;
    u8 count, firstPage, lastPage;

    count = gDexCategories[category].count;
    firstPage = 0xff;
    lastPage = 0xff;

    for (i = 0; i < count; i++)
        if (DexScreen_IsPageUnlocked(category, i))
        {
            if (firstPage == 0xff)
                firstPage = i;
            lastPage = i;
        }
    if (lastPage != 0xff)
    {
        sPokedexScreenData->firstPageInCategory = firstPage;
        sPokedexScreenData->lastPageInCategory = lastPage + 1;
        return FALSE;
    }
    else
    {
        sPokedexScreenData->firstPageInCategory = 0;
        sPokedexScreenData->lastPageInCategory = 0;
        return TRUE;
    }
}

static u8 DexScreen_LookUpCategoryBySpecies(u16 species)
{
    int i, j, k, categoryCount, categoryPageCount, posInPage;
    u16 dexSpecies;

    for (i = 0; i < NELEMS(gDexCategories); i++)
    {
        categoryCount = gDexCategories[i].count;
        for (j = 0; j < categoryCount; j++)
        {
            categoryPageCount = gDexCategories[i].page[j].count;
            for (k = 0, posInPage = 0; k < categoryPageCount; k++)
            {
                dexSpecies = gDexCategories[i].page[j].species[k];
                if (species == dexSpecies)
                {
                    sPokedexScreenData->category = i;
                    sPokedexScreenData->pageNum = j;
                    sPokedexScreenData->categoryCursorPosInPage = posInPage;
                    return FALSE;
                }
                if (DexScreen_CanShowMonInDex(dexSpecies) == TRUE && DexScreen_GetSetPokedexFlag(dexSpecies, FLAG_GET_SEEN, TRUE))
                    posInPage++;
            }
        }
    }
    return TRUE;
}

static u8 DexScreen_PageNumberToRenderablePages(u16 page)
{
    int i, count;

    for (i = 0, count = 0; i < page; i++)
        if (DexScreen_IsPageUnlocked(sPokedexScreenData->category, i))
            count++;

    return count + 1;
}

void DexScreen_InputHandler_StartToCry(void)
{
    if (JOY_NEW(START_BUTTON))
        PlayCry_NormalNoDucking(sPokedexScreenData->dexSpecies, 0, CRY_VOLUME_RS, CRY_PRIORITY_NORMAL);
}

u8 DexScreen_RegisterMonToPokedex(u16 species)
{
    DexScreen_GetSetPokedexFlag(species, FLAG_SET_SEEN, TRUE);
    DexScreen_GetSetPokedexFlag(species, FLAG_SET_CAUGHT, TRUE);

    if (!IsNationalPokedexEnabled() && SpeciesToNationalPokedexNum(species) > KANTO_DEX_COUNT)
        return CreateTask(Task_DexScreen_RegisterNonKantoMonBeforeNationalDex, 0);

    DexScreen_LoadResources();
    gTasks[sPokedexScreenData->taskId].func = Task_DexScreen_RegisterMonToPokedex;
    DexScreen_LookUpCategoryBySpecies(species);

    return sPokedexScreenData->taskId;
}

static void Task_DexScreen_RegisterNonKantoMonBeforeNationalDex(u8 taskId)
{
    DestroyTask(taskId);
}

static void Task_DexScreen_RegisterMonToPokedex(u8 taskId)
{
    switch (sPokedexScreenData->state)
    {
    case 0:
        DexScreen_GetPageLimitsForCategory(sPokedexScreenData->category);
        if (sPokedexScreenData->pageNum < sPokedexScreenData->firstPageInCategory)
            sPokedexScreenData->pageNum = sPokedexScreenData->firstPageInCategory;
        sPokedexScreenData->state = 3;
        break;
    case 1:
        RemoveDexPageWindows();
        DexScreen_DestroyCategoryPageMonIconAndInfoWindows();

        gMain.state = 0;
        sPokedexScreenData->state = 2;
        break;
    case 2:
        if (DoClosePokedex())
            DestroyTask(taskId);
        break;
    case 3:
        DexScreen_CreateCategoryListGfx(TRUE);
        PutWindowTilemap(0);
        PutWindowTilemap(1);

        CopyBgTilemapBufferToVram(3);
        CopyBgTilemapBufferToVram(2);
        CopyBgTilemapBufferToVram(1);
        CopyBgTilemapBufferToVram(0);

        DexScreen_CreateCategoryPageSelectionCursor(0xff);

        sPokedexScreenData->state = 4;
        break;
    case 4:
        gPaletteFade.bufferTransferDisabled = 0;
        BeginNormalPaletteFade(PALETTES_ALL, 0, 16, 0, 0xffff);
        ShowBg(3);
        ShowBg(2);
        ShowBg(1);
        ShowBg(0);

        sPokedexScreenData->state = 5;
        break;
    case 5:
        gTasks[taskId].data[0] = 30;
        sPokedexScreenData->categoryPageCursorTaskId = ListMenuAddCursorObjectInternal(&sCursorStruct_CategoryPage, 0);
        sPokedexScreenData->state = 6;
        break;
    case 6:
        DexScreen_CreateCategoryPageSelectionCursor(sPokedexScreenData->categoryCursorPosInPage);
        DexScreen_UpdateCategoryPageCursorObject(sPokedexScreenData->categoryPageCursorTaskId, sPokedexScreenData->categoryCursorPosInPage, sPokedexScreenData->numMonsOnPage);

        if (gTasks[taskId].data[0])
            gTasks[taskId].data[0]--;
        else
        {
            ListMenuRemoveCursorObject(sPokedexScreenData->categoryPageCursorTaskId, 0);
            sPokedexScreenData->state = 7;
        }
        break;
    case 7:
        sPokedexScreenData->dexSpecies = sPokedexScreenData->pageSpecies[sPokedexScreenData->categoryCursorPosInPage];
        sPokedexScreenData->state = 8;
        break;
    case 8:
        DexScreen_DrawMonDexPage(TRUE);
        sPokedexScreenData->state = 9;
        break;
    case 9:
        sPokedexScreenData->data[0] = 0;
        sPokedexScreenData->data[1] = 0;
        sPokedexScreenData->state++;
    case 10:
        if (sPokedexScreenData->data[1] < 6)
        {
            if (sPokedexScreenData->data[0])
            {
                DexScreen_DexPageZoomEffectFrame(0, sPokedexScreenData->data[1]);
                CopyBgTilemapBufferToVram(0);
                sPokedexScreenData->data[0] = 4;
                sPokedexScreenData->data[1]++;
            }
            else
                sPokedexScreenData->data[0]--;
        }
        else
        {
            FillBgTilemapBufferRect_Palette0(0, 0, 0, 2, 30, 16);
            CopyBgTilemapBufferToVram(3);
            CopyBgTilemapBufferToVram(2);
            CopyBgTilemapBufferToVram(1);
            CopyBgTilemapBufferToVram(0);

            PlayCry_NormalNoDucking(sPokedexScreenData->dexSpecies, 0, CRY_VOLUME_RS, CRY_PRIORITY_NORMAL);
            sPokedexScreenData->data[0] = 0;
            sPokedexScreenData->state = 11;
        }
        break;
    case 11:
        if (JOY_NEW(A_BUTTON | B_BUTTON))
            sPokedexScreenData->state = 2;
        break;
    }
}

void DexScreen_PrintStringWithAlignment(const u8 * str, s32 mode)
{
    u32 x;

    switch (mode)
    {
    case TEXT_LEFT:
        x = 8;
        break;
    case TEXT_CENTER:
        x = (u32)(240 - GetStringWidth(FONT_NORMAL, str, 0)) / 2;
        break;
    case TEXT_RIGHT:
    default:
        x = 232 - GetStringWidth(FONT_NORMAL, str, 0);
        break;
    }

    DexScreen_AddTextPrinterParameterized(0, FONT_NORMAL, str, x, 2, 4);
}
