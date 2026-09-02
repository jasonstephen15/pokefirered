#include "global.h"
#include "tilesets.h"
#include "tileset_anims.h"

// ===== BEGIN src/data/tilesets/graphics.h =====
const u32 gTilesetTiles_PalletTown[] = INCBIN_U32("assets/graphics.bin", 0x2AE260, 0x444);

const u16 gTilesetPalettes_PalletTown[][16] =
{
	INCBIN_U16("assets/graphics.bin", 0x2AE6A4, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2AE6C4, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2AE6E4, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2AE704, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2AE724, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2AE744, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2AE764, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2AE784, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2AE7A4, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2AE7C4, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2AE7E4, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2AE804, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2AE824, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2AE844, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2AE864, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2AE884, 0x20),
};

const u32 gTilesetTiles_ViridianCity[] = INCBIN_U32("assets/graphics.bin", 0x2AE8A4, 0x600);

const u16 gTilesetPalettes_ViridianCity[][16] =
{
	INCBIN_U16("assets/graphics.bin", 0x2AEEA4, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2AEEC4, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2AEEE4, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2AEF04, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2AEF24, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2AEF44, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2AEF64, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2AEF84, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2AEFA4, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2AEFC4, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2AEFE4, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2AF004, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2AF024, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2AF044, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2AF064, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2AF084, 0x20),
};

const u32 gTilesetTiles_PewterCity[] = INCBIN_U32("assets/graphics.bin", 0x2AF0A4, 0x8F8);

const u16 gTilesetPalettes_PewterCity[][16] =
{
	INCBIN_U16("assets/graphics.bin", 0x2AF99C, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2AF9BC, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2AF9DC, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2AF9FC, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2AFA1C, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2AFA3C, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2AFA5C, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2AFA7C, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2AFA9C, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2AFABC, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2AFADC, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2AFAFC, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2AFB1C, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2AFB3C, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2AFB5C, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2AFB7C, 0x20),
};

const u32 gTilesetTiles_CeruleanCity[] = INCBIN_U32("assets/graphics.bin", 0x2AFB9C, 0x800);

const u16 gTilesetPalettes_CeruleanCity[][16] =
{
	INCBIN_U16("assets/graphics.bin", 0x2B039C, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2B03BC, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2B03DC, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2B03FC, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2B041C, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2B043C, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2B045C, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2B047C, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2B049C, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2B04BC, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2B04DC, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2B04FC, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2B051C, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2B053C, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2B055C, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2B057C, 0x20),
};

const u32 gTilesetTiles_LavenderTown[] = INCBIN_U32("assets/graphics.bin", 0x2B059C, 0xD80);

const u16 gTilesetPalettes_LavenderTown[][16] =
{
	INCBIN_U16("assets/graphics.bin", 0x2B131C, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2B133C, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2B135C, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2B137C, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2B139C, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2B13BC, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2B13DC, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2B13FC, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2B141C, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2B143C, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2B145C, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2B147C, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2B149C, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2B14BC, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2B14DC, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2B14FC, 0x20),
};

const u32 gTilesetTiles_VermilionCity[] = INCBIN_U32("assets/graphics.bin", 0x2B151C, 0x768);

const u16 gTilesetPalettes_VermilionCity[][16] =
{
	INCBIN_U16("assets/graphics.bin", 0x2B1C84, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2B1CA4, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2B1CC4, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2B1CE4, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2B1D04, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2B1D24, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2B1D44, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2B1D64, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2B1D84, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2B1DA4, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2B1DC4, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2B1DE4, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2B1E04, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2B1E24, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2B1E44, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2B1E64, 0x20),
};

const u32 gTilesetTiles_CeladonCity[] = INCBIN_U32("assets/graphics.bin", 0x2B1E84, 0xCD4);

const u16 gTilesetPalettes_CeladonCity[][16] =
{
	INCBIN_U16("assets/graphics.bin", 0x2B2B58, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2B2B78, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2B2B98, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2B2BB8, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2B2BD8, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2B2BF8, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2B2C18, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2B2C38, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2B2C58, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2B2C78, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2B2C98, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2B2CB8, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2B2CD8, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2B2CF8, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2B2D18, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2B2D38, 0x20),
};

const u32 gTilesetTiles_FuchsiaCity[] = INCBIN_U32("assets/graphics.bin", 0x2B2D58, 0xBE8);

const u16 gTilesetPalettes_FuchsiaCity[][16] =
{
	INCBIN_U16("assets/graphics.bin", 0x2B3940, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2B3960, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2B3980, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2B39A0, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2B39C0, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2B39E0, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2B3A00, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2B3A20, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2B3A40, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2B3A60, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2B3A80, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2B3AA0, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2B3AC0, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2B3AE0, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2B3B00, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2B3B20, 0x20),
};

const u32 gTilesetTiles_CinnabarIsland[] = INCBIN_U32("assets/graphics.bin", 0x2B3B40, 0x6FC);

const u16 gTilesetPalettes_CinnabarIsland[][16] =
{
	INCBIN_U16("assets/graphics.bin", 0x2B423C, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2B425C, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2B427C, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2B429C, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2B42BC, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2B42DC, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2B42FC, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2B431C, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2B433C, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2B435C, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2B437C, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2B439C, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2B43BC, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2B43DC, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2B43FC, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2B441C, 0x20),
};

const u32 gTilesetTiles_IndigoPlateau[] = INCBIN_U32("assets/graphics.bin", 0x2B443C, 0xD78);

const u16 gTilesetPalettes_IndigoPlateau[][16] =
{
	INCBIN_U16("assets/graphics.bin", 0x2B51B4, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2B51D4, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2B51F4, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2B5214, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2B5234, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2B5254, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2B5274, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2B5294, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2B52B4, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2B52D4, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2B52F4, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2B5314, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2B5334, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2B5354, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2B5374, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2B5394, 0x20),
};

const u32 gTilesetTiles_SaffronCity[] = INCBIN_U32("assets/graphics.bin", 0x2B53B4, 0xBC4);

const u16 gTilesetPalettes_SaffronCity[][16] =
{
	INCBIN_U16("assets/graphics.bin", 0x2B5F78, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2B5F98, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2B5FB8, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2B5FD8, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2B5FF8, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2B6018, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2B6038, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2B6058, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2B6078, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2B6098, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2B60B8, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2B60D8, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2B60F8, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2B6118, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2B6138, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2B6158, 0x20),
};

const u32 gTilesetTiles_Building[] = INCBIN_U32("assets/graphics.bin", 0x2B6178, 0x2400);

const u16 gTilesetPalettes_Building[][16] =
{
	INCBIN_U16("assets/graphics.bin", 0x2B8578, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2B8598, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2B85B8, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2B85D8, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2B85F8, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2B8618, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2B8638, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2B8658, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2B8678, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2B8698, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2B86B8, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2B86D8, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2B86F8, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2B8718, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2B8738, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2B8758, 0x20),
};

const u32 gTilesetTiles_Mart[] = INCBIN_U32("assets/graphics.bin", 0x2B8778, 0x1C8);

const u16 gTilesetPalettes_Mart[][16] =
{
	INCBIN_U16("assets/graphics.bin", 0x2B8940, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2B8960, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2B8980, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2B89A0, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2B89C0, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2B89E0, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2B8A00, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2B8A20, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2B8A40, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2B8A60, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2B8A80, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2B8AA0, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2B8AC0, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2B8AE0, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2B8B00, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2B8B20, 0x20),
};

const u32 gTilesetTiles_PokemonCenter[] = INCBIN_U32("assets/graphics.bin", 0x2B8B40, 0x1068);

const u16 gTilesetPalettes_PokemonCenter[][16] =
{
	INCBIN_U16("assets/graphics.bin", 0x2B9BA8, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2B9BC8, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2B9BE8, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2B9C08, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2B9C28, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2B9C48, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2B9C68, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2B9C88, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2B9CA8, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2B9CC8, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2B9CE8, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2B9D08, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2B9D28, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2B9D48, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2B9D68, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2B9D88, 0x20),
};

const u32 gTilesetTiles_Cave[] = INCBIN_U32("assets/graphics.bin", 0x2B9DA8, 0x12E4);

const u16 gTilesetPalettes_Cave[][16] =
{
	INCBIN_U16("assets/graphics.bin", 0x2BB08C, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2BB0AC, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2BB0CC, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2BB0EC, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2BB10C, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2BB12C, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2BB14C, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2BB16C, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2BB18C, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2BB1AC, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2BB1CC, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2BB1EC, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2BB20C, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2BB22C, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2BB24C, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2BB26C, 0x20),
};

const u32 gTilesetTiles_Dummy1[] = INCBIN_U32("assets/graphics.bin", 0x2BB28C, 0x10);

const u16 gTilesetPalettes_Dummy1[][16] =
{
	INCBIN_U16("assets/graphics.bin", 0x2BB29C, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2BB2BC, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2BB2DC, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2BB2FC, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2BB31C, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2BB33C, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2BB35C, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2BB37C, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2BB39C, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2BB3BC, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2BB3DC, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2BB3FC, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2BB41C, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2BB43C, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2BB45C, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2BB47C, 0x20),
};

const u32 gTilesetTiles_Museum[] = INCBIN_U32("assets/graphics.bin", 0x2BB49C, 0x85C);

const u16 gTilesetPalettes_Museum[][16] =
{
	INCBIN_U16("assets/graphics.bin", 0x2BBCF8, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2BBD18, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2BBD38, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2BBD58, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2BBD78, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2BBD98, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2BBDB8, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2BBDD8, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2BBDF8, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2BBE18, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2BBE38, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2BBE58, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2BBE78, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2BBE98, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2BBEB8, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2BBED8, 0x20),
};

const u32 gTilesetTiles_CableClub[] = INCBIN_U32("assets/graphics.bin", 0x2BBEF8, 0x4F00);

const u16 gTilesetPalettes_CableClub[][16] =
{
	INCBIN_U16("assets/graphics.bin", 0x2C0DF8, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C0E18, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C0E38, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C0E58, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C0E78, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C0E98, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C0EB8, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C0ED8, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C0EF8, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C0F18, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C0F38, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C0F58, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C0F78, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C0F98, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C0FB8, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C0FD8, 0x20),
};

const u32 gTilesetTiles_BikeShop[] = INCBIN_U32("assets/graphics.bin", 0x2C0FF8, 0x3D8);

const u16 gTilesetPalettes_BikeShop[][16] =
{
	INCBIN_U16("assets/graphics.bin", 0x2C13D0, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C13F0, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C1410, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C1430, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C1450, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C1470, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C1490, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C14B0, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C14D0, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C14F0, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C1510, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C1530, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C1550, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C1570, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C1590, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C15B0, 0x20),
};

const u32 gTilesetTiles_Lab[] = INCBIN_U32("assets/graphics.bin", 0x2C15D0, 0x614);

const u16 gTilesetPalettes_Lab[][16] =
{
	INCBIN_U16("assets/graphics.bin", 0x2C1BE4, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C1C04, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C1C24, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C1C44, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C1C64, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C1C84, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C1CA4, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C1CC4, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C1CE4, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C1D04, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C1D24, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C1D44, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C1D64, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C1D84, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C1DA4, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C1DC4, 0x20),
};

const u32 gTilesetTiles_HoennBuilding[] = INCBIN_U32("assets/graphics.bin", 0x2C1DE4, 0x14A4);

const u16 gTilesetPalettes_HoennBuilding[][16] =
{
	INCBIN_U16("assets/graphics.bin", 0x2C3288, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C32A8, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C32C8, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C32E8, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C3308, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C3328, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C3348, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C3368, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C3388, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C33A8, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C33C8, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C33E8, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C3408, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C3428, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C3448, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C3468, 0x20),
};

const u32 gTilesetTiles_GameCorner[] = INCBIN_U32("assets/graphics.bin", 0x2C3488, 0xA18);

const u16 gTilesetPalettes_GameCorner[][16] =
{
	INCBIN_U16("assets/graphics.bin", 0x2C3EA0, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C3EC0, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C3EE0, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C3F00, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C3F20, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C3F40, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C3F60, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C3F80, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C3FA0, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C3FC0, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C3FE0, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C4000, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C4020, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C4040, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C4060, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C4080, 0x20),
};

const u32 gTilesetTiles_PewterGym[] = INCBIN_U32("assets/graphics.bin", 0x2C40A0, 0x7F4);

const u16 gTilesetPalettes_PewterGym[][16] =
{
	INCBIN_U16("assets/graphics.bin", 0x2C4894, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C48B4, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C48D4, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C48F4, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C4914, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C4934, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C4954, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C4974, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C4994, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C49B4, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C49D4, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C49F4, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C4A14, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C4A34, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C4A54, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C4A74, 0x20),
};

const u32 gTilesetTiles_CeruleanGym[] = INCBIN_U32("assets/graphics.bin", 0x2C4A94, 0x448);

const u16 gTilesetPalettes_CeruleanGym[][16] =
{
	INCBIN_U16("assets/graphics.bin", 0x2C4EDC, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C4EFC, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C4F1C, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C4F3C, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C4F5C, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C4F7C, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C4F9C, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C4FBC, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C4FDC, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C4FFC, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C501C, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C503C, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C505C, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C507C, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C509C, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C50BC, 0x20),
};

const u32 gTilesetTiles_VermilionGym[] = INCBIN_U32("assets/graphics.bin", 0x2C50DC, 0x7C0);

const u16 gTilesetPalettes_VermilionGym[][16] =
{
	INCBIN_U16("assets/graphics.bin", 0x2C589C, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C58BC, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C58DC, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C58FC, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C591C, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C593C, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C595C, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C597C, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C599C, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C59BC, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C59DC, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C59FC, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C5A1C, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C5A3C, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C5A5C, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C5A7C, 0x20),
};

const u32 gTilesetTiles_CeladonGym[] = INCBIN_U32("assets/graphics.bin", 0x2C5A9C, 0x598);

const u16 gTilesetPalettes_CeladonGym[][16] =
{
	INCBIN_U16("assets/graphics.bin", 0x2C6034, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C6054, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C6074, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C6094, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C60B4, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C60D4, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C60F4, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C6114, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C6134, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C6154, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C6174, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C6194, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C61B4, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C61D4, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C61F4, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C6214, 0x20),
};

const u32 gTilesetTiles_FuchsiaGym[] = INCBIN_U32("assets/graphics.bin", 0x2C6234, 0x454);

const u16 gTilesetPalettes_FuchsiaGym[][16] =
{
	INCBIN_U16("assets/graphics.bin", 0x2C6688, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C66A8, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C66C8, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C66E8, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C6708, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C6728, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C6748, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C6768, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C6788, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C67A8, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C67C8, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C67E8, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C6808, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C6828, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C6848, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C6868, 0x20),
};

const u32 gTilesetTiles_SaffronGym[] = INCBIN_U32("assets/graphics.bin", 0x2C6888, 0x3EC);

const u16 gTilesetPalettes_SaffronGym[][16] =
{
	INCBIN_U16("assets/graphics.bin", 0x2C6C74, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C6C94, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C6CB4, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C6CD4, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C6CF4, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C6D14, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C6D34, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C6D54, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C6D74, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C6D94, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C6DB4, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C6DD4, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C6DF4, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C6E14, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C6E34, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C6E54, 0x20),
};

const u32 gTilesetTiles_CinnabarGym[] = INCBIN_U32("assets/graphics.bin", 0x2C6E74, 0x644);

const u16 gTilesetPalettes_CinnabarGym[][16] =
{
	INCBIN_U16("assets/graphics.bin", 0x2C74B8, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C74D8, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C74F8, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C7518, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C7538, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C7558, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C7578, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C7598, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C75B8, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C75D8, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C75F8, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C7618, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C7638, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C7658, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C7678, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C7698, 0x20),
};

const u32 gTilesetTiles_ViridianGym[] = INCBIN_U32("assets/graphics.bin", 0x2C76B8, 0x3F4);

const u16 gTilesetPalettes_ViridianGym[][16] =
{
	INCBIN_U16("assets/graphics.bin", 0x2C7AAC, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C7ACC, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C7AEC, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C7B0C, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C7B2C, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C7B4C, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C7B6C, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C7B8C, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C7BAC, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C7BCC, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C7BEC, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C7C0C, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C7C2C, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C7C4C, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C7C6C, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C7C8C, 0x20),
};

const u32 gTilesetTiles_SSAnne[] = INCBIN_U32("assets/graphics.bin", 0x2C7CAC, 0xDB8);

const u16 gTilesetPalettes_SSAnne[][16] =
{
	INCBIN_U16("assets/graphics.bin", 0x2C8A64, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C8A84, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C8AA4, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C8AC4, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C8AE4, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C8B04, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C8B24, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C8B44, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C8B64, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C8B84, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C8BA4, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C8BC4, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C8BE4, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C8C04, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C8C24, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C8C44, 0x20),
};

const u32 gTilesetTiles_Dummy2[] = INCBIN_U32("assets/graphics.bin", 0x2C8C64, 0x14);

const u16 gTilesetPalettes_Dummy2[][16] =
{
	INCBIN_U16("assets/graphics.bin", 0x2C8C78, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C8C98, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C8CB8, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C8CD8, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C8CF8, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C8D18, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C8D38, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C8D58, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C8D78, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C8D98, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C8DB8, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C8DD8, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C8DF8, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C8E18, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C8E38, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C8E58, 0x20),
};

const u32 gTilesetTiles_ViridianForest[] = INCBIN_U32("assets/graphics.bin", 0x2C8E78, 0x4B0);

const u16 gTilesetPalettes_ViridianForest[][16] =
{
	INCBIN_U16("assets/graphics.bin", 0x2C9328, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C9348, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C9368, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C9388, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C93A8, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C93C8, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C93E8, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C9408, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C9428, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C9448, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C9468, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C9488, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C94A8, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C94C8, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C94E8, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C9508, 0x20),
};

const u32 gTilesetTiles_UnusedGatehouse1[] = INCBIN_U32("assets/graphics.bin", 0x2C9528, 0x61C);

const u16 gTilesetPalettes_UnusedGatehouse1[][16] =
{
	INCBIN_U16("assets/graphics.bin", 0x2C9B44, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C9B64, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C9B84, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C9BA4, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C9BC4, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C9BE4, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C9C04, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C9C24, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C9C44, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C9C64, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C9C84, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C9CA4, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C9CC4, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C9CE4, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C9D04, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2C9D24, 0x20),
};

const u32 gTilesetTiles_RockTunnel[] = INCBIN_U32("assets/graphics.bin", 0x2C9D44, 0x1168);

const u16 gTilesetPalettes_RockTunnel[][16] =
{
	INCBIN_U16("assets/graphics.bin", 0x2CAEAC, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2CAECC, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2CAEEC, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2CAF0C, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2CAF2C, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2CAF4C, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2CAF6C, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2CAF8C, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2CAFAC, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2CAFCC, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2CAFEC, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2CB00C, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2CB02C, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2CB04C, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2CB06C, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2CB08C, 0x20),
};

const u32 gTilesetTiles_DiglettsCave[] = INCBIN_U32("assets/graphics.bin", 0x2CB0AC, 0x1088);

const u16 gTilesetPalettes_DiglettsCave[][16] =
{
	INCBIN_U16("assets/graphics.bin", 0x2CC134, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2CC154, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2CC174, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2CC194, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2CC1B4, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2CC1D4, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2CC1F4, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2CC214, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2CC234, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2CC254, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2CC274, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2CC294, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2CC2B4, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2CC2D4, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2CC2F4, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2CC314, 0x20),
};

const u32 gTilesetTiles_SeafoamIslands[] = INCBIN_U32("assets/graphics.bin", 0x2CC334, 0x1650);

const u16 gTilesetPalettes_SeafoamIslands[][16] =
{
	INCBIN_U16("assets/graphics.bin", 0x2CD984, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2CD9A4, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2CD9C4, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2CD9E4, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2CDA04, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2CDA24, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2CDA44, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2CDA64, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2CDA84, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2CDAA4, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2CDAC4, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2CDAE4, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2CDB04, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2CDB24, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2CDB44, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2CDB64, 0x20),
};

const u32 gTilesetTiles_UnusedGatehouse2[] = INCBIN_U32("assets/graphics.bin", 0x2CDB84, 0x61C);

const u16 gTilesetPalettes_UnusedGatehouse2[][16] =
{
	INCBIN_U16("assets/graphics.bin", 0x2CE1A0, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2CE1C0, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2CE1E0, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2CE200, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2CE220, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2CE240, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2CE260, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2CE280, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2CE2A0, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2CE2C0, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2CE2E0, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2CE300, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2CE320, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2CE340, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2CE360, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2CE380, 0x20),
};

const u32 gTilesetTiles_CeruleanCave[] = INCBIN_U32("assets/graphics.bin", 0x2CE3A0, 0xEE8);

const u16 gTilesetPalettes_CeruleanCave[][16] =
{
	INCBIN_U16("assets/graphics.bin", 0x2CF288, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2CF2A8, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2CF2C8, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2CF2E8, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2CF308, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2CF328, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2CF348, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2CF368, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2CF388, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2CF3A8, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2CF3C8, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2CF3E8, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2CF408, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2CF428, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2CF448, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2CF468, 0x20),
};

const u32 gTilesetTiles_GenericBuilding2[] = INCBIN_U32("assets/graphics.bin", 0x2CF488, 0x6CC);

const u16 gTilesetPalettes_GenericBuilding2[][16] =
{
	INCBIN_U16("assets/graphics.bin", 0x2CFB54, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2CFB74, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2CFB94, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2CFBB4, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2CFBD4, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2CFBF4, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2CFC14, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2CFC34, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2CFC54, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2CFC74, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2CFC94, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2CFCB4, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2CFCD4, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2CFCF4, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2CFD14, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2CFD34, 0x20),
};

const u32 gTilesetTiles_PowerPlant[] = INCBIN_U32("assets/graphics.bin", 0x2CFD54, 0x508);

const u16 gTilesetPalettes_PowerPlant[][16] =
{
	INCBIN_U16("assets/graphics.bin", 0x2D025C, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D027C, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D029C, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D02BC, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D02DC, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D02FC, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D031C, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D033C, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D035C, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D037C, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D039C, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D03BC, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D03DC, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D03FC, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D041C, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D043C, 0x20),
};

const u32 gTilesetTiles_SeaCottage[] = INCBIN_U32("assets/graphics.bin", 0x2D045C, 0x460);

const u16 gTilesetPalettes_SeaCottage[][16] =
{
	INCBIN_U16("assets/graphics.bin", 0x2D08BC, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D08DC, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D08FC, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D091C, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D093C, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D095C, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D097C, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D099C, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D09BC, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D09DC, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D09FC, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D0A1C, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D0A3C, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D0A5C, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D0A7C, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D0A9C, 0x20),
};

// Shared by SilphCo
const u32 gTilesetTiles_Condominiums[] = INCBIN_U32("assets/graphics.bin", 0x2D0ABC, 0x11F8);

// Shared by SilphCo
const u16 gTilesetPalettes_Condominiums[][16] =
{
	INCBIN_U16("assets/graphics.bin", 0x2D1CB4, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D1CD4, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D1CF4, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D1D14, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D1D34, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D1D54, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D1D74, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D1D94, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D1DB4, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D1DD4, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D1DF4, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D1E14, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D1E34, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D1E54, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D1E74, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D1E94, 0x20),
};

const u32 gTilesetTiles_UndergroundPath[] = INCBIN_U32("assets/graphics.bin", 0x2D1EB4, 0x2A4);

const u16 gTilesetPalettes_UndergroundPath[][16] =
{
	INCBIN_U16("assets/graphics.bin", 0x2D2158, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D2178, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D2198, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D21B8, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D21D8, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D21F8, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D2218, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D2238, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D2258, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D2278, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D2298, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D22B8, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D22D8, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D22F8, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D2318, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D2338, 0x20),
};

const u32 gTilesetTiles_PokemonTower[] = INCBIN_U32("assets/graphics.bin", 0x2D2358, 0x688);

const u16 gTilesetPalettes_PokemonTower[][16] =
{
	INCBIN_U16("assets/graphics.bin", 0x2D29E0, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D2A00, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D2A20, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D2A40, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D2A60, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D2A80, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D2AA0, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D2AC0, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D2AE0, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D2B00, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D2B20, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D2B40, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D2B60, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D2B80, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D2BA0, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D2BC0, 0x20),
};

const u32 gTilesetTiles_SafariZoneBuilding[] = INCBIN_U32("assets/graphics.bin", 0x2D2BE0, 0x3F4);

const u16 gTilesetPalettes_SafariZoneBuilding[][16] =
{
	INCBIN_U16("assets/graphics.bin", 0x2D2FD4, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D2FF4, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D3014, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D3034, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D3054, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D3074, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D3094, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D30B4, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D30D4, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D30F4, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D3114, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D3134, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D3154, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D3174, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D3194, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D31B4, 0x20),
};

const u32 gTilesetTiles_PokemonMansion[] = INCBIN_U32("assets/graphics.bin", 0x2D31D4, 0xD00);

const u16 gTilesetPalettes_PokemonMansion[][16] =
{
	INCBIN_U16("assets/graphics.bin", 0x2D3ED4, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D3EF4, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D3F14, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D3F34, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D3F54, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D3F74, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D3F94, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D3FB4, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D3FD4, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D3FF4, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D4014, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D4034, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D4054, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D4074, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D4094, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D40B4, 0x20),
};

const u32 gTilesetTiles_RestaurantHotel[] = INCBIN_U32("assets/graphics.bin", 0x2D40D4, 0x470);

const u16 gTilesetPalettes_RestaurantHotel[][16] =
{
	INCBIN_U16("assets/graphics.bin", 0x2D4544, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D4564, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D4584, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D45A4, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D45C4, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D45E4, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D4604, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D4624, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D4644, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D4664, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D4684, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D46A4, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D46C4, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D46E4, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D4704, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D4724, 0x20),
};

const u32 gTilesetTiles_School[] = INCBIN_U32("assets/graphics.bin", 0x2D4744, 0x2AC);

const u16 gTilesetPalettes_School[][16] =
{
	INCBIN_U16("assets/graphics.bin", 0x2D49F0, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D4A10, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D4A30, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D4A50, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D4A70, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D4A90, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D4AB0, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D4AD0, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D4AF0, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D4B10, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D4B30, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D4B50, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D4B70, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D4B90, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D4BB0, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D4BD0, 0x20),
};

const u32 gTilesetTiles_FanClubDaycare[] = INCBIN_U32("assets/graphics.bin", 0x2D4BF0, 0x438);

const u16 gTilesetPalettes_FanClubDaycare[][16] =
{
	INCBIN_U16("assets/graphics.bin", 0x2D5028, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D5048, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D5068, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D5088, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D50A8, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D50C8, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D50E8, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D5108, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D5128, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D5148, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D5168, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D5188, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D51A8, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D51C8, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D51E8, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D5208, 0x20),
};

const u32 gTilesetTiles_BurgledHouse[] = INCBIN_U32("assets/graphics.bin", 0x2D5228, 0x9C4);

const u16 gTilesetPalettes_BurgledHouse[][16] =
{
	INCBIN_U16("assets/graphics.bin", 0x2D5BEC, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D5C0C, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D5C2C, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D5C4C, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D5C6C, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D5C8C, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D5CAC, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D5CCC, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D5CEC, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D5D0C, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D5D2C, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D5D4C, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D5D6C, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D5D8C, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D5DAC, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D5DCC, 0x20),
};

const u32 gTilesetTiles_Dummy3[] = INCBIN_U32("assets/graphics.bin", 0x2D5DEC, 0x10);

const u16 gTilesetPalettes_Dummy3[][16] =
{
	INCBIN_U16("assets/graphics.bin", 0x2D5DFC, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D5E1C, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D5E3C, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D5E5C, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D5E7C, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D5E9C, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D5EBC, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D5EDC, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D5EFC, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D5F1C, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D5F3C, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D5F5C, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D5F7C, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D5F9C, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D5FBC, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D5FDC, 0x20),
};

const u32 gTilesetTiles_Dummy4[] = INCBIN_U32("assets/graphics.bin", 0x2D5FFC, 0x14);

const u16 gTilesetPalettes_Dummy4[][16] =
{
	INCBIN_U16("assets/graphics.bin", 0x2D6010, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D6030, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D6050, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D6070, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D6090, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D60B0, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D60D0, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D60F0, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D6110, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D6130, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D6150, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D6170, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D6190, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D61B0, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D61D0, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D61F0, 0x20),
};

const u32 gTilesetTiles_MtEmber[] = INCBIN_U32("assets/graphics.bin", 0x2D6210, 0x14A8);

const u16 gTilesetPalettes_MtEmber[][16] =
{
	INCBIN_U16("assets/graphics.bin", 0x2D76B8, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D76D8, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D76F8, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D7718, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D7738, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D7758, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D7778, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D7798, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D77B8, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D77D8, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D77F8, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D7818, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D7838, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D7858, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D7878, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D7898, 0x20),
};

const u32 gTilesetTiles_BerryForest[] = INCBIN_U32("assets/graphics.bin", 0x2D78B8, 0x4BC);

const u16 gTilesetPalettes_BerryForest[][16] =
{
	INCBIN_U16("assets/graphics.bin", 0x2D7D74, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D7D94, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D7DB4, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D7DD4, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D7DF4, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D7E14, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D7E34, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D7E54, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D7E74, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D7E94, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D7EB4, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D7ED4, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D7EF4, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D7F14, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D7F34, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D7F54, 0x20),
};

const u32 gTilesetTiles_NavelRock[] = INCBIN_U32("assets/graphics.bin", 0x2D7F74, 0x132C);

const u16 gTilesetPalettes_NavelRock[][16] =
{
	INCBIN_U16("assets/graphics.bin", 0x2D92A0, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D92C0, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D92E0, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D9300, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D9320, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D9340, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D9360, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D9380, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D93A0, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D93C0, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D93E0, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D9400, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D9420, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D9440, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D9460, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D9480, 0x20),
};

const u32 gTilesetTiles_TanobyRuins[] = INCBIN_U32("assets/graphics.bin", 0x2D94A0, 0x3B4);

const u16 gTilesetPalettes_TanobyRuins[][16] =
{
	INCBIN_U16("assets/graphics.bin", 0x2D9854, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D9874, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D9894, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D98B4, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D98D4, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D98F4, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D9914, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D9934, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D9954, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D9974, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D9994, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D99B4, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D99D4, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D99F4, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D9A14, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2D9A34, 0x20),
};

const u32 gTilesetTiles_SeviiIslands123[] = INCBIN_U32("assets/graphics.bin", 0x2D9A54, 0xF34);

const u16 gTilesetPalettes_SeviiIslands123[][16] =
{
	INCBIN_U16("assets/graphics.bin", 0x2DA988, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2DA9A8, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2DA9C8, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2DA9E8, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2DAA08, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2DAA28, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2DAA48, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2DAA68, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2DAA88, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2DAAA8, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2DAAC8, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2DAAE8, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2DAB08, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2DAB28, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2DAB48, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2DAB68, 0x20),
};

const u32 gTilesetTiles_SeviiIslands45[] = INCBIN_U32("assets/graphics.bin", 0x2DAB88, 0xE60);

const u16 gTilesetPalettes_SeviiIslands45[][16] =
{
	INCBIN_U16("assets/graphics.bin", 0x2DB9E8, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2DBA08, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2DBA28, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2DBA48, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2DBA68, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2DBA88, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2DBAA8, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2DBAC8, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2DBAE8, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2DBB08, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2DBB28, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2DBB48, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2DBB68, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2DBB88, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2DBBA8, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2DBBC8, 0x20),
};

const u32 gTilesetTiles_SeviiIslands67[] = INCBIN_U32("assets/graphics.bin", 0x2DBBE8, 0x1060);

const u16 gTilesetPalettes_SeviiIslands67[][16] =
{
	INCBIN_U16("assets/graphics.bin", 0x2DCC48, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2DCC68, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2DCC88, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2DCCA8, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2DCCC8, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2DCCE8, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2DCD08, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2DCD28, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2DCD48, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2DCD68, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2DCD88, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2DCDA8, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2DCDC8, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2DCDE8, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2DCE08, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2DCE28, 0x20),
};

const u32 gTilesetTiles_TrainerTower[] = INCBIN_U32("assets/graphics.bin", 0x2DCE48, 0xF80);

const u16 gTilesetPalettes_TrainerTower[][16] =
{
	INCBIN_U16("assets/graphics.bin", 0x2DDDC8, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2DDDE8, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2DDE08, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2DDE28, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2DDE48, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2DDE68, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2DDE88, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2DDEA8, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2DDEC8, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2DDEE8, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2DDF08, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2DDF28, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2DDF48, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2DDF68, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2DDF88, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2DDFA8, 0x20),
};

const u32 gTilesetTiles_IslandHarbor[] = INCBIN_U32("assets/graphics.bin", 0x2DDFC8, 0x7B0);

const u16 gTilesetPalettes_IslandHarbor[][16] =
{
	INCBIN_U16("assets/graphics.bin", 0x2DE778, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2DE798, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2DE7B8, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2DE7D8, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2DE7F8, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2DE818, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2DE838, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2DE858, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2DE878, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2DE898, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2DE8B8, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2DE8D8, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2DE8F8, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2DE918, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2DE938, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2DE958, 0x20),
};

const u32 gTilesetTiles_PokemonLeague[] = INCBIN_U32("assets/graphics.bin", 0x2DE978, 0xFBC);

const u16 gTilesetPalettes_PokemonLeague[][16] =
{
	INCBIN_U16("assets/graphics.bin", 0x2DF934, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2DF954, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2DF974, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2DF994, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2DF9B4, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2DF9D4, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2DF9F4, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2DFA14, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2DFA34, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2DFA54, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2DFA74, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2DFA94, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2DFAB4, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2DFAD4, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2DFAF4, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2DFB14, 0x20),
};

const u32 gTilesetTiles_HallOfFame[] = INCBIN_U32("assets/graphics.bin", 0x2DFB34, 0x878);

const u16 gTilesetPalettes_HallOfFame[][16] =
{
	INCBIN_U16("assets/graphics.bin", 0x2E03AC, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2E03CC, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2E03EC, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2E040C, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2E042C, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2E044C, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2E046C, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2E048C, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2E04AC, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2E04CC, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2E04EC, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2E050C, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2E052C, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2E054C, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2E056C, 0x20),
	INCBIN_U16("assets/graphics.bin", 0x2E058C, 0x20),
};
// ===== END src/data/tilesets/graphics.h =====
// ===== BEGIN src/data/tilesets/metatiles.h =====
const u16 gMetatiles_General[] = INCBIN_U16("assets/graphics.bin", 0x2E05AC, 0x2800);
const u32 gMetatileAttributes_General[] = INCBIN_U32("assets/graphics.bin", 0x2E2DAC, 0xA00);

const u16 gMetatiles_PalletTown[] = INCBIN_U16("assets/graphics.bin", 0x2E37AC, 0x590);
const u32 gMetatileAttributes_PalletTown[] = INCBIN_U32("assets/graphics.bin", 0x2E3D3C, 0x164);

const u16 gMetatiles_ViridianCity[] = INCBIN_U16("assets/graphics.bin", 0x2E3EA0, 0x5F0);
const u32 gMetatileAttributes_ViridianCity[] = INCBIN_U32("assets/graphics.bin", 0x2E4490, 0x17C);

const u16 gMetatiles_PewterCity[] = INCBIN_U16("assets/graphics.bin", 0x2E460C, 0x4F0);
const u32 gMetatileAttributes_PewterCity[] = INCBIN_U32("assets/graphics.bin", 0x2E4AFC, 0x13C);

const u16 gMetatiles_CeruleanCity[] = INCBIN_U16("assets/graphics.bin", 0x2E4C38, 0x860);
const u32 gMetatileAttributes_CeruleanCity[] = INCBIN_U32("assets/graphics.bin", 0x2E5498, 0x218);

const u16 gMetatiles_LavenderTown[] = INCBIN_U16("assets/graphics.bin", 0x2E56B0, 0xDA0);
const u32 gMetatileAttributes_LavenderTown[] = INCBIN_U32("assets/graphics.bin", 0x2E6450, 0x368);

const u16 gMetatiles_VermilionCity[] = INCBIN_U16("assets/graphics.bin", 0x2E67B8, 0xA80);
const u32 gMetatileAttributes_VermilionCity[] = INCBIN_U32("assets/graphics.bin", 0x2E7238, 0x2A0);

const u16 gMetatiles_CeladonCity[] = INCBIN_U16("assets/graphics.bin", 0x2E74D8, 0xF00);
const u32 gMetatileAttributes_CeladonCity[] = INCBIN_U32("assets/graphics.bin", 0x2E83D8, 0x3C0);

const u16 gMetatiles_FuchsiaCity[] = INCBIN_U16("assets/graphics.bin", 0x2E8798, 0xC00);
const u32 gMetatileAttributes_FuchsiaCity[] = INCBIN_U32("assets/graphics.bin", 0x2E9398, 0x300);

const u16 gMetatiles_CinnabarIsland[] = INCBIN_U16("assets/graphics.bin", 0x2E9698, 0x400);
const u32 gMetatileAttributes_CinnabarIsland[] = INCBIN_U32("assets/graphics.bin", 0x2E9A98, 0x100);

const u16 gMetatiles_IndigoPlateau[] = INCBIN_U16("assets/graphics.bin", 0x2E9B98, 0xB00);
const u32 gMetatileAttributes_IndigoPlateau[] = INCBIN_U32("assets/graphics.bin", 0x2EA698, 0x2C0);

const u16 gMetatiles_SaffronCity[] = INCBIN_U16("assets/graphics.bin", 0x2EA958, 0xC80);
const u32 gMetatileAttributes_SaffronCity[] = INCBIN_U32("assets/graphics.bin", 0x2EB5D8, 0x320);

const u16 gMetatiles_PewterGym[] = INCBIN_U16("assets/graphics.bin", 0x2EB8F8, 0x650);
const u32 gMetatileAttributes_PewterGym[] = INCBIN_U32("assets/graphics.bin", 0x2EBF48, 0x194);

const u16 gMetatiles_CeruleanGym[] = INCBIN_U16("assets/graphics.bin", 0x2EC0DC, 0x540);
const u32 gMetatileAttributes_CeruleanGym[] = INCBIN_U32("assets/graphics.bin", 0x2EC61C, 0x150);

const u16 gMetatiles_VermilionGym[] = INCBIN_U16("assets/graphics.bin", 0x2EC76C, 0x4B0);
const u32 gMetatileAttributes_VermilionGym[] = INCBIN_U32("assets/graphics.bin", 0x2ECC1C, 0x12C);

const u16 gMetatiles_CeladonGym[] = INCBIN_U16("assets/graphics.bin", 0x2ECD48, 0x400);
const u32 gMetatileAttributes_CeladonGym[] = INCBIN_U32("assets/graphics.bin", 0x2ED148, 0x100);

const u16 gMetatiles_FuchsiaGym[] = INCBIN_U16("assets/graphics.bin", 0x2ED248, 0x220);
const u32 gMetatileAttributes_FuchsiaGym[] = INCBIN_U32("assets/graphics.bin", 0x2ED468, 0x88);

const u16 gMetatiles_SaffronGym[] = INCBIN_U16("assets/graphics.bin", 0x2ED4F0, 0x2E0);
const u32 gMetatileAttributes_SaffronGym[] = INCBIN_U32("assets/graphics.bin", 0x2ED7D0, 0xB8);

const u16 gMetatiles_CinnabarGym[] = INCBIN_U16("assets/graphics.bin", 0x2ED888, 0x600);
const u32 gMetatileAttributes_CinnabarGym[] = INCBIN_U32("assets/graphics.bin", 0x2EDE88, 0x180);

const u16 gMetatiles_ViridianGym[] = INCBIN_U16("assets/graphics.bin", 0x2EE008, 0x540);
const u32 gMetatileAttributes_ViridianGym[] = INCBIN_U32("assets/graphics.bin", 0x2EE548, 0x150);

const u16 gMetatiles_Building[] = INCBIN_U16("assets/graphics.bin", 0x2EE698, 0x2800);
const u32 gMetatileAttributes_Building[] = INCBIN_U32("assets/graphics.bin", 0x2F0E98, 0xA00);

const u16 gMetatiles_Dummy1[] = INCBIN_U16("assets/graphics.bin", 0x2F1898, 0x20);
const u32 gMetatileAttributes_Dummy1[] = INCBIN_U32("assets/graphics.bin", 0x2F18B8, 0x8);

const u16 gMetatiles_HoennBuilding[] = INCBIN_U16("assets/graphics.bin", 0x2F18C0, 0x2000);
const u32 gMetatileAttributes_HoennBuilding[] = INCBIN_U32("assets/graphics.bin", 0x2F38C0, 0x800);

const u16 gMetatiles_BikeShop[] = INCBIN_U16("assets/graphics.bin", 0x2F40C0, 0x2A0);
const u32 gMetatileAttributes_BikeShop[] = INCBIN_U32("assets/graphics.bin", 0x2F4360, 0xA8);

const u16 gMetatiles_Mart[] = INCBIN_U16("assets/graphics.bin", 0x2F4408, 0x430);
const u32 gMetatileAttributes_Mart[] = INCBIN_U32("assets/graphics.bin", 0x2F4838, 0x10C);

const u16 gMetatiles_PokemonCenter[] = INCBIN_U16("assets/graphics.bin", 0x2F4944, 0xFF0);
const u32 gMetatileAttributes_PokemonCenter[] = INCBIN_U32("assets/graphics.bin", 0x2F5934, 0x3FC);

const u16 gMetatiles_GenericBuilding1[] = INCBIN_U16("assets/graphics.bin", 0x2F5D30, 0x180);
const u32 gMetatileAttributes_GenericBuilding1[] = INCBIN_U32("assets/graphics.bin", 0x2F5EB0, 0x60);

const u16 gMetatiles_Cave[] = INCBIN_U16("assets/graphics.bin", 0x2F5F10, 0xA10);
const u32 gMetatileAttributes_Cave[] = INCBIN_U32("assets/graphics.bin", 0x2F6920, 0x284);

const u16 gMetatiles_GameCorner[] = INCBIN_U16("assets/graphics.bin", 0x2F6BA4, 0x980);
const u32 gMetatileAttributes_GameCorner[] = INCBIN_U32("assets/graphics.bin", 0x2F7524, 0x260);

const u16 gMetatiles_Lab[] = INCBIN_U16("assets/graphics.bin", 0x2F7784, 0xAF0);
const u32 gMetatileAttributes_Lab[] = INCBIN_U32("assets/graphics.bin", 0x2F8274, 0x2BC);

const u16 gMetatiles_SSAnne[] = INCBIN_U16("assets/graphics.bin", 0x2F8530, 0x1500);
const u32 gMetatileAttributes_SSAnne[] = INCBIN_U32("assets/graphics.bin", 0x2F9A30, 0x540);

const u16 gMetatiles_Dummy2[] = INCBIN_U16("assets/graphics.bin", 0x2F9F70, 0x20);
const u32 gMetatileAttributes_Dummy2[] = INCBIN_U32("assets/graphics.bin", 0x2F9F90, 0x8);

const u16 gMetatiles_ViridianForest[] = INCBIN_U16("assets/graphics.bin", 0x2F9F98, 0x2B0);
const u32 gMetatileAttributes_ViridianForest[] = INCBIN_U32("assets/graphics.bin", 0x2FA248, 0xAC);

const u16 gMetatiles_UnusedGatehouse1[] = INCBIN_U16("assets/graphics.bin", 0x2FA2F4, 0x720);
const u32 gMetatileAttributes_UnusedGatehouse1[] = INCBIN_U32("assets/graphics.bin", 0x2FAA14, 0x1C8);

const u16 gMetatiles_RockTunnel[] = INCBIN_U16("assets/graphics.bin", 0x2FABDC, 0x980);
const u32 gMetatileAttributes_RockTunnel[] = INCBIN_U32("assets/graphics.bin", 0x2FB55C, 0x260);

const u16 gMetatiles_DiglettsCave[] = INCBIN_U16("assets/graphics.bin", 0x2FB7BC, 0x9D0);
const u32 gMetatileAttributes_DiglettsCave[] = INCBIN_U32("assets/graphics.bin", 0x2FC18C, 0x274);

const u16 gMetatiles_SeafoamIslands[] = INCBIN_U16("assets/graphics.bin", 0x2FC400, 0xF80);
const u32 gMetatileAttributes_SeafoamIslands[] = INCBIN_U32("assets/graphics.bin", 0x2FD380, 0x3E0);

const u16 gMetatiles_UnusedGatehouse2[] = INCBIN_U16("assets/graphics.bin", 0x2FD760, 0x720);
const u32 gMetatileAttributes_UnusedGatehouse2[] = INCBIN_U32("assets/graphics.bin", 0x2FDE80, 0x1C8);

const u16 gMetatiles_CeruleanCave[] = INCBIN_U16("assets/graphics.bin", 0x2FE048, 0x860);
const u32 gMetatileAttributes_CeruleanCave[] = INCBIN_U32("assets/graphics.bin", 0x2FE8A8, 0x218);

const u16 gMetatiles_DepartmentStore[] = INCBIN_U16("assets/graphics.bin", 0x2FEAC0, 0xF60);
const u32 gMetatileAttributes_DepartmentStore[] = INCBIN_U32("assets/graphics.bin", 0x2FFA20, 0x3D8);

const u16 gMetatiles_GenericBuilding2[] = INCBIN_U16("assets/graphics.bin", 0x2FFDF8, 0xB80);
const u32 gMetatileAttributes_GenericBuilding2[] = INCBIN_U32("assets/graphics.bin", 0x300978, 0x2E0);

const u16 gMetatiles_PowerPlant[] = INCBIN_U16("assets/graphics.bin", 0x300C58, 0x990);
const u32 gMetatileAttributes_PowerPlant[] = INCBIN_U32("assets/graphics.bin", 0x3015E8, 0x264);

const u16 gMetatiles_SeaCottage[] = INCBIN_U16("assets/graphics.bin", 0x30184C, 0x3B0);
const u32 gMetatileAttributes_SeaCottage[] = INCBIN_U32("assets/graphics.bin", 0x301BFC, 0xEC);

const u16 gMetatiles_SilphCo[] = INCBIN_U16("assets/graphics.bin", 0x301CE8, 0x17A0);
const u32 gMetatileAttributes_SilphCo[] = INCBIN_U32("assets/graphics.bin", 0x303488, 0x5E8);

const u16 gMetatiles_UndergroundPath[] = INCBIN_U16("assets/graphics.bin", 0x303A70, 0x480);
const u32 gMetatileAttributes_UndergroundPath[] = INCBIN_U32("assets/graphics.bin", 0x303EF0, 0x120);

const u16 gMetatiles_PokemonTower[] = INCBIN_U16("assets/graphics.bin", 0x304010, 0x650);
const u32 gMetatileAttributes_PokemonTower[] = INCBIN_U32("assets/graphics.bin", 0x304660, 0x194);

const u16 gMetatiles_SafariZoneBuilding[] = INCBIN_U16("assets/graphics.bin", 0x3047F4, 0x800);
const u32 gMetatileAttributes_SafariZoneBuilding[] = INCBIN_U32("assets/graphics.bin", 0x304FF4, 0x200);

const u16 gMetatiles_PokemonMansion[] = INCBIN_U16("assets/graphics.bin", 0x3051F4, 0x1020);
const u32 gMetatileAttributes_PokemonMansion[] = INCBIN_U32("assets/graphics.bin", 0x306214, 0x408);

const u16 gMetatiles_Museum[] = INCBIN_U16("assets/graphics.bin", 0x30661C, 0x870);
const u32 gMetatileAttributes_Museum[] = INCBIN_U32("assets/graphics.bin", 0x306E8C, 0x21C);

const u16 gMetatiles_CableClub[] = INCBIN_U16("assets/graphics.bin", 0x3070A8, 0x1000);
const u32 gMetatileAttributes_CableClub[] = INCBIN_U32("assets/graphics.bin", 0x3080A8, 0x400);

const u16 gMetatiles_RestaurantHotel[] = INCBIN_U16("assets/graphics.bin", 0x3084A8, 0x680);
const u32 gMetatileAttributes_RestaurantHotel[] = INCBIN_U32("assets/graphics.bin", 0x308B28, 0x1A0);

const u16 gMetatiles_School[] = INCBIN_U16("assets/graphics.bin", 0x308CC8, 0x2E0);
const u32 gMetatileAttributes_School[] = INCBIN_U32("assets/graphics.bin", 0x308FA8, 0xB8);

const u16 gMetatiles_FanClubDaycare[] = INCBIN_U16("assets/graphics.bin", 0x309060, 0xAA0);
const u32 gMetatileAttributes_FanClubDaycare[] = INCBIN_U32("assets/graphics.bin", 0x309B00, 0x2A8);

const u16 gMetatiles_Condominiums[] = INCBIN_U16("assets/graphics.bin", 0x309DA8, 0xD70);
const u32 gMetatileAttributes_Condominiums[] = INCBIN_U32("assets/graphics.bin", 0x30AB18, 0x35C);

const u16 gMetatiles_BurgledHouse[] = INCBIN_U16("assets/graphics.bin", 0x30AE74, 0x390);
const u32 gMetatileAttributes_BurgledHouse[] = INCBIN_U32("assets/graphics.bin", 0x30B204, 0xE4);

const u16 gMetatiles_Dummy3[] = INCBIN_U16("assets/graphics.bin", 0x30B2E8, 0x20);
const u32 gMetatileAttributes_Dummy3[] = INCBIN_U32("assets/graphics.bin", 0x30B308, 0x8);

const u16 gMetatiles_Dummy4[] = INCBIN_U16("assets/graphics.bin", 0x30B310, 0x20);
const u32 gMetatileAttributes_Dummy4[] = INCBIN_U32("assets/graphics.bin", 0x30B330, 0x8);

const u16 gMetatiles_MtEmber[] = INCBIN_U16("assets/graphics.bin", 0x30B338, 0xE20);
const u32 gMetatileAttributes_MtEmber[] = INCBIN_U32("assets/graphics.bin", 0x30C158, 0x388);

const u16 gMetatiles_BerryForest[] = INCBIN_U16("assets/graphics.bin", 0x30C4E0, 0x2A0);
const u32 gMetatileAttributes_BerryForest[] = INCBIN_U32("assets/graphics.bin", 0x30C780, 0xA8);

const u16 gMetatiles_NavelRock[] = INCBIN_U16("assets/graphics.bin", 0x30C828, 0xDC0);
const u32 gMetatileAttributes_NavelRock[] = INCBIN_U32("assets/graphics.bin", 0x30D5E8, 0x370);

const u16 gMetatiles_TanobyRuins[] = INCBIN_U16("assets/graphics.bin", 0x30D958, 0x5E0);
const u32 gMetatileAttributes_TanobyRuins[] = INCBIN_U32("assets/graphics.bin", 0x30DF38, 0x178);

const u16 gMetatiles_SeviiIslands123[] = INCBIN_U16("assets/graphics.bin", 0x30E0B0, 0x11D0);
const u32 gMetatileAttributes_SeviiIslands123[] = INCBIN_U32("assets/graphics.bin", 0x30F280, 0x474);

const u16 gMetatiles_SeviiIslands45[] = INCBIN_U16("assets/graphics.bin", 0x30F6F4, 0x980);
const u32 gMetatileAttributes_SeviiIslands45[] = INCBIN_U32("assets/graphics.bin", 0x310074, 0x260);

const u16 gMetatiles_SeviiIslands67[] = INCBIN_U16("assets/graphics.bin", 0x3102D4, 0xF00);
const u32 gMetatileAttributes_SeviiIslands67[] = INCBIN_U32("assets/graphics.bin", 0x3111D4, 0x3C0);

const u16 gMetatiles_TrainerTower[] = INCBIN_U16("assets/graphics.bin", 0x311594, 0x1200);
const u32 gMetatileAttributes_TrainerTower[] = INCBIN_U32("assets/graphics.bin", 0x312794, 0x480);

const u16 gMetatiles_IslandHarbor[] = INCBIN_U16("assets/graphics.bin", 0x312C14, 0x4F0);
const u32 gMetatileAttributes_IslandHarbor[] = INCBIN_U32("assets/graphics.bin", 0x313104, 0x13C);

const u16 gMetatiles_PokemonLeague[] = INCBIN_U16("assets/graphics.bin", 0x313240, 0x1800);
const u32 gMetatileAttributes_PokemonLeague[] = INCBIN_U32("assets/graphics.bin", 0x314A40, 0x600);

const u16 gMetatiles_HallOfFame[] = INCBIN_U16("assets/graphics.bin", 0x315040, 0x760);
const u32 gMetatileAttributes_HallOfFame[] = INCBIN_U32("assets/graphics.bin", 0x3157A0, 0x1D8);
// ===== END src/data/tilesets/metatiles.h =====
// ===== BEGIN src/data/tilesets/headers.h =====
const struct Tileset gTileset_General =
{
    .isCompressed = TRUE,
    .isSecondary = FALSE,
    .tiles = gTilesetTiles_General,
    .palettes = gTilesetPalettes_General,
    .metatiles = gMetatiles_General,
    .metatileAttributes = gMetatileAttributes_General,
    .callback = InitTilesetAnim_General,
};

const struct Tileset gTileset_PalletTown =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_PalletTown,
    .palettes = gTilesetPalettes_PalletTown,
    .metatiles = gMetatiles_PalletTown,
    .metatileAttributes = gMetatileAttributes_PalletTown,
    .callback = NULL,
};

const struct Tileset gTileset_ViridianCity =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_ViridianCity,
    .palettes = gTilesetPalettes_ViridianCity,
    .metatiles = gMetatiles_ViridianCity,
    .metatileAttributes = gMetatileAttributes_ViridianCity,
    .callback = NULL,
};

const struct Tileset gTileset_PewterCity =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_PewterCity,
    .palettes = gTilesetPalettes_PewterCity,
    .metatiles = gMetatiles_PewterCity,
    .metatileAttributes = gMetatileAttributes_PewterCity,
    .callback = NULL,
};

const struct Tileset gTileset_CeruleanCity =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_CeruleanCity,
    .palettes = gTilesetPalettes_CeruleanCity,
    .metatiles = gMetatiles_CeruleanCity,
    .metatileAttributes = gMetatileAttributes_CeruleanCity,
    .callback = NULL,
};

const struct Tileset gTileset_LavenderTown =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_LavenderTown,
    .palettes = gTilesetPalettes_LavenderTown,
    .metatiles = gMetatiles_LavenderTown,
    .metatileAttributes = gMetatileAttributes_LavenderTown,
    .callback = NULL,
};

const struct Tileset gTileset_VermilionCity =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_VermilionCity,
    .palettes = gTilesetPalettes_VermilionCity,
    .metatiles = gMetatiles_VermilionCity,
    .metatileAttributes = gMetatileAttributes_VermilionCity,
    .callback = NULL,
};

const struct Tileset gTileset_CeladonCity =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_CeladonCity,
    .palettes = gTilesetPalettes_CeladonCity,
    .metatiles = gMetatiles_CeladonCity,
    .metatileAttributes = gMetatileAttributes_CeladonCity,
    .callback = InitTilesetAnim_CeladonCity,
};

const struct Tileset gTileset_FuchsiaCity =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_FuchsiaCity,
    .palettes = gTilesetPalettes_FuchsiaCity,
    .metatiles = gMetatiles_FuchsiaCity,
    .metatileAttributes = gMetatileAttributes_FuchsiaCity,
    .callback = NULL,
};

const struct Tileset gTileset_CinnabarIsland =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_CinnabarIsland,
    .palettes = gTilesetPalettes_CinnabarIsland,
    .metatiles = gMetatiles_CinnabarIsland,
    .metatileAttributes = gMetatileAttributes_CinnabarIsland,
    .callback = NULL,
};

const struct Tileset gTileset_IndigoPlateau =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_IndigoPlateau,
    .palettes = gTilesetPalettes_IndigoPlateau,
    .metatiles = gMetatiles_IndigoPlateau,
    .metatileAttributes = gMetatileAttributes_IndigoPlateau,
    .callback = NULL,
};

const struct Tileset gTileset_SaffronCity =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_SaffronCity,
    .palettes = gTilesetPalettes_SaffronCity,
    .metatiles = gMetatiles_SaffronCity,
    .metatileAttributes = gMetatileAttributes_SaffronCity,
    .callback = NULL,
};

const struct Tileset gTileset_Building =
{
    .isCompressed = TRUE,
    .isSecondary = FALSE,
    .tiles = gTilesetTiles_Building,
    .palettes = gTilesetPalettes_Building,
    .metatiles = gMetatiles_Building,
    .metatileAttributes = gMetatileAttributes_Building,
    .callback = NULL,
};

const struct Tileset gTileset_Mart =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_Mart,
    .palettes = gTilesetPalettes_Mart,
    .metatiles = gMetatiles_Mart,
    .metatileAttributes = gMetatileAttributes_Mart,
    .callback = NULL,
};

const struct Tileset gTileset_PokemonCenter =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_PokemonCenter,
    .palettes = gTilesetPalettes_PokemonCenter,
    .metatiles = gMetatiles_PokemonCenter,
    .metatileAttributes = gMetatileAttributes_PokemonCenter,
    .callback = NULL,
};

const struct Tileset gTileset_Cave =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_Cave,
    .palettes = gTilesetPalettes_Cave,
    .metatiles = gMetatiles_Cave,
    .metatileAttributes = gMetatileAttributes_Cave,
    .callback = NULL,
};

const struct Tileset gTileset_Dummy1 =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_Dummy1,
    .palettes = gTilesetPalettes_Dummy1,
    .metatiles = gMetatiles_Dummy1,
    .metatileAttributes = gMetatileAttributes_Dummy1,
    .callback = NULL,
};

const struct Tileset gTileset_Museum =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_Museum,
    .palettes = gTilesetPalettes_Museum,
    .metatiles = gMetatiles_Museum,
    .metatileAttributes = gMetatileAttributes_Museum,
    .callback = NULL,
};

const struct Tileset gTileset_CableClub =
{
    .isCompressed = FALSE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_CableClub,
    .palettes = gTilesetPalettes_CableClub,
    .metatiles = gMetatiles_CableClub,
    .metatileAttributes = gMetatileAttributes_CableClub,
    .callback = NULL,
};

const struct Tileset gTileset_BikeShop =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_BikeShop,
    .palettes = gTilesetPalettes_BikeShop,
    .metatiles = gMetatiles_BikeShop,
    .metatileAttributes = gMetatileAttributes_BikeShop,
    .callback = NULL,
};

const struct Tileset gTileset_GenericBuilding1 =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_GenericBuilding1,
    .palettes = gTilesetPalettes_GenericBuilding1,
    .metatiles = gMetatiles_GenericBuilding1,
    .metatileAttributes = gMetatileAttributes_GenericBuilding1,
    .callback = NULL,
};

const struct Tileset gTileset_Lab =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_Lab,
    .palettes = gTilesetPalettes_Lab,
    .metatiles = gMetatiles_Lab,
    .metatileAttributes = gMetatileAttributes_Lab,
    .callback = NULL,
};

const struct Tileset gTileset_FuchsiaGym =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_FuchsiaGym,
    .palettes = gTilesetPalettes_FuchsiaGym,
    .metatiles = gMetatiles_FuchsiaGym,
    .metatileAttributes = gMetatileAttributes_FuchsiaGym,
    .callback = NULL,
};

const struct Tileset gTileset_ViridianGym =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_ViridianGym,
    .palettes = gTilesetPalettes_ViridianGym,
    .metatiles = gMetatiles_ViridianGym,
    .metatileAttributes = gMetatileAttributes_ViridianGym,
    .callback = NULL,
};

const struct Tileset gTileset_HoennBuilding =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_HoennBuilding,
    .palettes = gTilesetPalettes_HoennBuilding,
    .metatiles = gMetatiles_HoennBuilding,
    .metatileAttributes = gMetatileAttributes_HoennBuilding,
    .callback = NULL,
};

const struct Tileset gTileset_GameCorner =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_GameCorner,
    .palettes = gTilesetPalettes_GameCorner,
    .metatiles = gMetatiles_GameCorner,
    .metatileAttributes = gMetatileAttributes_GameCorner,
    .callback = NULL,
};

const struct Tileset gTileset_PewterGym =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_PewterGym,
    .palettes = gTilesetPalettes_PewterGym,
    .metatiles = gMetatiles_PewterGym,
    .metatileAttributes = gMetatileAttributes_PewterGym,
    .callback = NULL,
};

const struct Tileset gTileset_CeruleanGym =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_CeruleanGym,
    .palettes = gTilesetPalettes_CeruleanGym,
    .metatiles = gMetatiles_CeruleanGym,
    .metatileAttributes = gMetatileAttributes_CeruleanGym,
    .callback = NULL,
};

const struct Tileset gTileset_VermilionGym =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_VermilionGym,
    .palettes = gTilesetPalettes_VermilionGym,
    .metatiles = gMetatiles_VermilionGym,
    .metatileAttributes = gMetatileAttributes_VermilionGym,
    .callback = InitTilesetAnim_VermilionGym,
};

const struct Tileset gTileset_CeladonGym =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_CeladonGym,
    .palettes = gTilesetPalettes_CeladonGym,
    .metatiles = gMetatiles_CeladonGym,
    .metatileAttributes = gMetatileAttributes_CeladonGym,
    .callback = InitTilesetAnim_CeladonGym,
};

const struct Tileset gTileset_SaffronGym =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_SaffronGym,
    .palettes = gTilesetPalettes_SaffronGym,
    .metatiles = gMetatiles_SaffronGym,
    .metatileAttributes = gMetatileAttributes_SaffronGym,
    .callback = NULL,
};

const struct Tileset gTileset_CinnabarGym =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_CinnabarGym,
    .palettes = gTilesetPalettes_CinnabarGym,
    .metatiles = gMetatiles_CinnabarGym,
    .metatileAttributes = gMetatileAttributes_CinnabarGym,
    .callback = NULL,
};

const struct Tileset gTileset_SSAnne =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_SSAnne,
    .palettes = gTilesetPalettes_SSAnne,
    .metatiles = gMetatiles_SSAnne,
    .metatileAttributes = gMetatileAttributes_SSAnne,
    .callback = NULL,
};

const struct Tileset gTileset_Dummy2 =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_Dummy2,
    .palettes = gTilesetPalettes_Dummy2,
    .metatiles = gMetatiles_Dummy2,
    .metatileAttributes = gMetatileAttributes_Dummy2,
    .callback = NULL,
};

const struct Tileset gTileset_ViridianForest =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_ViridianForest,
    .palettes = gTilesetPalettes_ViridianForest,
    .metatiles = gMetatiles_ViridianForest,
    .metatileAttributes = gMetatileAttributes_ViridianForest,
    .callback = NULL,
};

const struct Tileset gTileset_UnusedGatehouse1 =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_UnusedGatehouse1,
    .palettes = gTilesetPalettes_UnusedGatehouse1,
    .metatiles = gMetatiles_UnusedGatehouse1,
    .metatileAttributes = gMetatileAttributes_UnusedGatehouse1,
    .callback = NULL,
};

const struct Tileset gTileset_RockTunnel =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_RockTunnel,
    .palettes = gTilesetPalettes_RockTunnel,
    .metatiles = gMetatiles_RockTunnel,
    .metatileAttributes = gMetatileAttributes_RockTunnel,
    .callback = NULL,
};

const struct Tileset gTileset_DiglettsCave =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_DiglettsCave,
    .palettes = gTilesetPalettes_DiglettsCave,
    .metatiles = gMetatiles_DiglettsCave,
    .metatileAttributes = gMetatileAttributes_DiglettsCave,
    .callback = NULL,
};

const struct Tileset gTileset_SeafoamIslands =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_SeafoamIslands,
    .palettes = gTilesetPalettes_SeafoamIslands,
    .metatiles = gMetatiles_SeafoamIslands,
    .metatileAttributes = gMetatileAttributes_SeafoamIslands,
    .callback = NULL,
};

const struct Tileset gTileset_UnusedGatehouse2 =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_UnusedGatehouse2,
    .palettes = gTilesetPalettes_UnusedGatehouse2,
    .metatiles = gMetatiles_UnusedGatehouse2,
    .metatileAttributes = gMetatileAttributes_UnusedGatehouse2,
    .callback = NULL,
};

const struct Tileset gTileset_CeruleanCave =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_CeruleanCave,
    .palettes = gTilesetPalettes_CeruleanCave,
    .metatiles = gMetatiles_CeruleanCave,
    .metatileAttributes = gMetatileAttributes_CeruleanCave,
    .callback = NULL,
};

const struct Tileset gTileset_DepartmentStore =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_DepartmentStore,
    .palettes = gTilesetPalettes_DepartmentStore,
    .metatiles = gMetatiles_DepartmentStore,
    .metatileAttributes = gMetatileAttributes_DepartmentStore,
    .callback = NULL,
};

const struct Tileset gTileset_GenericBuilding2 =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_GenericBuilding2,
    .palettes = gTilesetPalettes_GenericBuilding2,
    .metatiles = gMetatiles_GenericBuilding2,
    .metatileAttributes = gMetatileAttributes_GenericBuilding2,
    .callback = NULL,
};

const struct Tileset gTileset_PowerPlant =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_PowerPlant,
    .palettes = gTilesetPalettes_PowerPlant,
    .metatiles = gMetatiles_PowerPlant,
    .metatileAttributes = gMetatileAttributes_PowerPlant,
    .callback = NULL,
};

const struct Tileset gTileset_SeaCottage =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_SeaCottage,
    .palettes = gTilesetPalettes_SeaCottage,
    .metatiles = gMetatiles_SeaCottage,
    .metatileAttributes = gMetatileAttributes_SeaCottage,
    .callback = NULL,
};

const struct Tileset gTileset_SilphCo =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_Condominiums,
    .palettes = gTilesetPalettes_Condominiums,
    .metatiles = gMetatiles_SilphCo,
    .metatileAttributes = gMetatileAttributes_SilphCo,
    .callback = InitTilesetAnim_SilphCo,
};

const struct Tileset gTileset_UndergroundPath =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_UndergroundPath,
    .palettes = gTilesetPalettes_UndergroundPath,
    .metatiles = gMetatiles_UndergroundPath,
    .metatileAttributes = gMetatileAttributes_UndergroundPath,
    .callback = NULL,
};

const struct Tileset gTileset_PokemonTower =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_PokemonTower,
    .palettes = gTilesetPalettes_PokemonTower,
    .metatiles = gMetatiles_PokemonTower,
    .metatileAttributes = gMetatileAttributes_PokemonTower,
    .callback = NULL,
};

const struct Tileset gTileset_SafariZoneBuilding =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_SafariZoneBuilding,
    .palettes = gTilesetPalettes_SafariZoneBuilding,
    .metatiles = gMetatiles_SafariZoneBuilding,
    .metatileAttributes = gMetatileAttributes_SafariZoneBuilding,
    .callback = NULL,
};

const struct Tileset gTileset_PokemonMansion =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_PokemonMansion,
    .palettes = gTilesetPalettes_PokemonMansion,
    .metatiles = gMetatiles_PokemonMansion,
    .metatileAttributes = gMetatileAttributes_PokemonMansion,
    .callback = NULL,
};

const struct Tileset gTileset_RestaurantHotel =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_RestaurantHotel,
    .palettes = gTilesetPalettes_RestaurantHotel,
    .metatiles = gMetatiles_RestaurantHotel,
    .metatileAttributes = gMetatileAttributes_RestaurantHotel,
    .callback = NULL,
};

const struct Tileset gTileset_School =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_School,
    .palettes = gTilesetPalettes_School,
    .metatiles = gMetatiles_School,
    .metatileAttributes = gMetatileAttributes_School,
    .callback = NULL,
};

const struct Tileset gTileset_FanClubDaycare =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_FanClubDaycare,
    .palettes = gTilesetPalettes_FanClubDaycare,
    .metatiles = gMetatiles_FanClubDaycare,
    .metatileAttributes = gMetatileAttributes_FanClubDaycare,
    .callback = NULL,
};

const struct Tileset gTileset_Condominiums =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_Condominiums,
    .palettes = gTilesetPalettes_Condominiums,
    .metatiles = gMetatiles_Condominiums,
    .metatileAttributes = gMetatileAttributes_Condominiums,
    .callback = NULL,
};

const struct Tileset gTileset_BurgledHouse =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_BurgledHouse,
    .palettes = gTilesetPalettes_BurgledHouse,
    .metatiles = gMetatiles_BurgledHouse,
    .metatileAttributes = gMetatileAttributes_BurgledHouse,
    .callback = NULL,
};

const struct Tileset gTileset_Dummy3 =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_Dummy3,
    .palettes = gTilesetPalettes_Dummy3,
    .metatiles = gMetatiles_Dummy3,
    .metatileAttributes = gMetatileAttributes_Dummy3,
    .callback = NULL,
};

const struct Tileset gTileset_Dummy4 =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_Dummy4,
    .palettes = gTilesetPalettes_Dummy4,
    .metatiles = gMetatiles_Dummy4,
    .metatileAttributes = gMetatileAttributes_Dummy4,
    .callback = NULL,
};

const struct Tileset gTileset_MtEmber =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_MtEmber,
    .palettes = gTilesetPalettes_MtEmber,
    .metatiles = gMetatiles_MtEmber,
    .metatileAttributes = gMetatileAttributes_MtEmber,
    .callback = InitTilesetAnim_MtEmber,
};

const struct Tileset gTileset_BerryForest =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_BerryForest,
    .palettes = gTilesetPalettes_BerryForest,
    .metatiles = gMetatiles_BerryForest,
    .metatileAttributes = gMetatileAttributes_BerryForest,
    .callback = NULL,
};

const struct Tileset gTileset_NavelRock =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_NavelRock,
    .palettes = gTilesetPalettes_NavelRock,
    .metatiles = gMetatiles_NavelRock,
    .metatileAttributes = gMetatileAttributes_NavelRock,
    .callback = NULL,
};

const struct Tileset gTileset_TanobyRuins =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_TanobyRuins,
    .palettes = gTilesetPalettes_TanobyRuins,
    .metatiles = gMetatiles_TanobyRuins,
    .metatileAttributes = gMetatileAttributes_TanobyRuins,
    .callback = NULL,
};

const struct Tileset gTileset_SeviiIslands123 =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_SeviiIslands123,
    .palettes = gTilesetPalettes_SeviiIslands123,
    .metatiles = gMetatiles_SeviiIslands123,
    .metatileAttributes = gMetatileAttributes_SeviiIslands123,
    .callback = NULL,
};

const struct Tileset gTileset_SeviiIslands45 =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_SeviiIslands45,
    .palettes = gTilesetPalettes_SeviiIslands45,
    .metatiles = gMetatiles_SeviiIslands45,
    .metatileAttributes = gMetatileAttributes_SeviiIslands45,
    .callback = NULL,
};

const struct Tileset gTileset_SeviiIslands67 =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_SeviiIslands67,
    .palettes = gTilesetPalettes_SeviiIslands67,
    .metatiles = gMetatiles_SeviiIslands67,
    .metatileAttributes = gMetatileAttributes_SeviiIslands67,
    .callback = NULL,
};

const struct Tileset gTileset_TrainerTower =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_TrainerTower,
    .palettes = gTilesetPalettes_TrainerTower,
    .metatiles = gMetatiles_TrainerTower,
    .metatileAttributes = gMetatileAttributes_TrainerTower,
    .callback = NULL,
};

const struct Tileset gTileset_IslandHarbor =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_IslandHarbor,
    .palettes = gTilesetPalettes_IslandHarbor,
    .metatiles = gMetatiles_IslandHarbor,
    .metatileAttributes = gMetatileAttributes_IslandHarbor,
    .callback = NULL,
};

const struct Tileset gTileset_PokemonLeague =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_PokemonLeague,
    .palettes = gTilesetPalettes_PokemonLeague,
    .metatiles = gMetatiles_PokemonLeague,
    .metatileAttributes = gMetatileAttributes_PokemonLeague,
    .callback = NULL,
};

const struct Tileset gTileset_HallOfFame =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_HallOfFame,
    .palettes = gTilesetPalettes_HallOfFame,
    .metatiles = gMetatiles_HallOfFame,
    .metatileAttributes = gMetatileAttributes_HallOfFame,
    .callback = NULL,
};

// ===== END src/data/tilesets/headers.h =====
