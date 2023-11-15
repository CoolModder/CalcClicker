#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <math.h>
#include <tice.h>
#include <time.h>
#include <graphx.h>
#include <keypadc.h>
#include <inttypes.h>
#include <fileioc.h>
#include <debug.h>
#include "gfx/CEClickU.h" 
struct player_t {
	uint64_t points;
	uint64_t cps;
	uint64_t clickvalue;
	uint64_t cps_mult;
	uint64_t cvm;
	uint8_t unlocked;
	uint8_t page;
};

struct counts_t {
	uint64_t addcount, studentcount, subcount, cookiecount, multcount, officecount, divcount, phonecount, expcount, spacecount, calccount, buttoncount;
};

struct prices_t
{
	uint64_t addprice;
	uint64_t studentprice;
	uint64_t subprice;
	uint64_t cookieprice;
	uint64_t multprice;
	uint64_t officeprice;
	uint64_t divprice;
	uint64_t phoneprice;
	uint64_t expprice;
	uint64_t spaceprice;
	uint64_t calcprice;
	uint64_t buttonprice;
};
void printUInt64(uint64_t num) {
	char str[21]; // 64-bit numbers have at most 20 decimal digits
	sprintf(str, "%" PRIu64, num);
	gfx_PrintString(str);
}



void missing_appvars(void) {
	gfx_End();
	os_SetCursorPos(0, 0);
	os_PutStrFull("Err: Missing CE Clicker AppVars");
	while (!os_GetCSC());
	exit(0);
}

void Draw(struct player_t* Player, struct counts_t* Counts, struct prices_t* Prices, bool prevkey) {
	gfx_FillScreen(7);
	gfx_SetColor(0);
	gfx_TransparentSprite(background, 0, 0);
	gfx_TransparentSprite(background, 32, 0);
	gfx_TransparentSprite(background, 64, 0);
	gfx_TransparentSprite(background, 96, 0);
	gfx_TransparentSprite(background, 128, 0);
	gfx_TransparentSprite(background, 160, 0);
	gfx_TransparentSprite(background, 192, 0);
	gfx_TransparentSprite(background, 224, 0);
	gfx_TransparentSprite(background, 256, 0);
	gfx_TransparentSprite(background, 288, 0);
	gfx_SetTextXY(10, 10);


	gfx_PrintString("Equations: ");
	printUInt64((*Player).points);
	gfx_SetTextXY(10, 20);
	gfx_PrintString("EPS: ");
	printUInt64((*Player).cps * (*Player).cps_mult);
	if (prevkey)
	{
		gfx_TransparentSprite(calc_small, 24, 68);
	}
	else
	{
		gfx_TransparentSprite(calc_large, 24, 68);
	}
	gfx_SetTextXY(10, 988);
	gfx_PrintString("Enter: Click, Del : Save + Quit, < > : Scroll Shop,");
	gfx_SetTextXY(10, 998);
	gfx_PrintString("2nd: Buy Top, Alpha : Buy Bottom");
	gfx_TransparentSprite(up_box, 136, 74);
	gfx_TransparentSprite(up_box, 136, 140);
	if ((*Player).page > 0)
	{
		gfx_TransparentSprite(arrow_right, 112, 126);
	}
	if ((*Player).page < (*Player).unlocked)
	{
		gfx_TransparentSprite(arrow_left, 296, 126);
	}
	
	if ((*Player).page == 0)
	{
		gfx_TransparentSprite(up_add, 140, 74);
		gfx_SetTextXY(170, 80);
		gfx_PrintString("Addition Sign");
		gfx_SetTextXY(170, 90);
		gfx_PrintString("X ");
		printUInt64((*Counts).addcount);
		gfx_SetTextXY(142, 104);
		gfx_PrintString("+1 EQU Per Click");
		gfx_SetTextXY(142, 114);
		printUInt64((*Prices).addprice);
		gfx_PrintString(" EQU");
		gfx_TransparentSprite(up_stu, 140, 142);
		gfx_SetTextXY(170, 148);
		gfx_PrintString("Bored Student");
		gfx_SetTextXY(170, 158);
		gfx_PrintString("X ");
		printUInt64((*Counts).studentcount);
		gfx_SetTextXY(142, 172);
		gfx_PrintString("+1 EPS");
		gfx_SetTextXY(142, 182);
		printUInt64((*Prices).studentprice);
		gfx_PrintString(" EQU");
	}
	else if ((*Player).page == 1)
	{
		gfx_TransparentSprite(up_sub, 140, 74);
		gfx_SetTextXY(170, 80);
		gfx_PrintString("Subtraction Sign");
		gfx_SetTextXY(170, 90);
		gfx_PrintString("X ");
		printUInt64((*Counts).subcount);
		gfx_SetTextXY(142, 104);
		gfx_PrintString("+3 EQU Per Click");
		gfx_SetTextXY(142, 114);
		printUInt64((*Prices).subprice);
		gfx_PrintString(" EQU");
		gfx_TransparentSprite(up_coo, 140, 142);
		gfx_SetTextXY(170, 148);
		gfx_PrintString("Cookie");
		gfx_SetTextXY(170, 158);
		gfx_PrintString("X ");
		printUInt64((*Counts).cookiecount);
		gfx_SetTextXY(142, 172);
		gfx_PrintString("+4 EPS");
		gfx_SetTextXY(142, 182);
		printUInt64((*Prices).cookieprice);
		gfx_PrintString(" EQU");
	}
	else if ((*Player).page == 2)
	{
		gfx_TransparentSprite(up_mul, 140, 74);
		gfx_SetTextXY(170, 80);
		gfx_PrintString("Multiplying Sign");
		gfx_SetTextXY(170, 90);
		gfx_PrintString("X ");
		printUInt64((*Counts).multcount);
		gfx_SetTextXY(142, 104);
		gfx_PrintString("+10 EQU Per Click");
		gfx_SetTextXY(142, 114);
		printUInt64((*Prices).multprice);
		gfx_PrintString(" EQU");
		gfx_TransparentSprite(up_off, 140, 142);
		gfx_SetTextXY(170, 148);
		gfx_PrintString("Office Worker");
		gfx_SetTextXY(170, 158);
		gfx_PrintString("X ");
		printUInt64((*Counts).officecount);
		gfx_SetTextXY(142, 172);
		gfx_PrintString("+27 EPS");
		gfx_SetTextXY(142, 182);
		printUInt64((*Prices).officeprice);
		gfx_PrintString(" EQU");
	}
	else if ((*Player).page == 3)
	{
		gfx_TransparentSprite(up_div, 140, 74);
		gfx_SetTextXY(170, 80);
		gfx_PrintString("Division Sign");
		gfx_SetTextXY(170, 90);
		gfx_PrintString("X ");
		printUInt64((*Counts).divcount);
		gfx_SetTextXY(142, 104);
		gfx_PrintString("80 EQU Per Click");
		gfx_SetTextXY(142, 114);
		printUInt64((*Prices).divprice);
		gfx_PrintString(" EQU");
		gfx_TransparentSprite(up_pho, 140, 142);
		gfx_SetTextXY(170, 148);
		gfx_PrintString("Phone :0");
		gfx_SetTextXY(170, 158);
		gfx_PrintString("X ");
		printUInt64((*Counts).phonecount);
		gfx_SetTextXY(142, 172);
		gfx_PrintString("+101 EPS");
		gfx_SetTextXY(142, 182);
		printUInt64((*Prices).phoneprice);
		gfx_PrintString(" EQU");
	}
	else if ((*Player).page == 4)
	{
		gfx_TransparentSprite(up_exp, 140, 74);
		gfx_SetTextXY(170, 80);
		gfx_PrintString("Exponent Sign");
		gfx_SetTextXY(170, 90);
		gfx_PrintString("X ");
		printUInt64((*Counts).expcount);
		gfx_SetTextXY(142, 104);
		gfx_PrintString("750 EQU Per Click");
		gfx_SetTextXY(142, 114);
		printUInt64((*Prices).expprice);
		gfx_PrintString(" EQU");
		gfx_TransparentSprite(up_bar, 140, 142);
		gfx_SetTextXY(170, 148);
		gfx_PrintString("Spacebar");
		gfx_SetTextXY(170, 158);
		gfx_PrintString("X ");
		printUInt64((*Counts).spacecount);
		gfx_SetTextXY(142, 172);
		gfx_PrintString("+980 EPS");
		gfx_SetTextXY(142, 182);
		printUInt64((*Prices).spaceprice);
		gfx_PrintString(" EQU");
	}
	else if ((*Player).page == 5)
	{
		gfx_TransparentSprite(up_cal, 140, 74);
		gfx_SetTextXY(170, 80);
		gfx_PrintString("Calculator");
		gfx_SetTextXY(170, 90);
		gfx_PrintString("X ");
		printUInt64((*Counts).calccount);
		gfx_SetTextXY(142, 104);
		gfx_PrintString("2x EQU Per Click");
		gfx_SetTextXY(142, 114);
		printUInt64((*Prices).calcprice);
		gfx_PrintString(" EQU");
		gfx_TransparentSprite(up_but, 140, 142);
		gfx_SetTextXY(170, 148);
		gfx_PrintString("Button");
		gfx_SetTextXY(170, 158);
		gfx_PrintString("X ");
		printUInt64((*Counts).buttoncount);
		gfx_SetTextXY(142, 172);
		gfx_PrintString("2x EPS");
		gfx_SetTextXY(142, 182);
		printUInt64((*Prices).buttonprice);
		gfx_PrintString(" EQU");
	}
	gfx_SetColor(1);
	gfx_Line(0, 215, 319, 215);
	gfx_Line(0, 216, 319, 216);
	gfx_Line(111, 64, 111, 215);
	gfx_Line(112, 64, 112, 215);
	gfx_BlitBuffer();

}
int load(struct player_t* Player, struct counts_t* Counts, struct prices_t* Prices)
{
	uint8_t var = ti_Open("CEClickS", "r");
	if (var == 0)
	{
		return 1;
	}
	if (ti_GetC(var) != 'a')
	{
		return 1;
	}
	if (ti_Read(Player, sizeof(struct player_t), 1, var) != 1)
	{
		return 1;
	}
	if (ti_GetC(var) != 'b')
	{
		return 1;
	}
	if (ti_Read(Counts, sizeof(struct counts_t), 1, var) != 1)
	{
		return 1;
	}
	if (ti_GetC(var) != 'c')
	{
		return 1;
	}
	if (ti_Read(Prices, sizeof(struct prices_t), 1, var) != 1)
	{
		return 1;
	}
	ti_Close(var);

	return 0;

}
int save(struct player_t* Player, struct counts_t* Counts, struct prices_t* Prices)
{
	if ((*Player).clickvalue == 0)
	{
		return 1;
	}
	uint8_t var = ti_Open("CEClickS", "w");
	if (ti_PutC('a', var) == EOF)
	{
		os_PutStrFull("a");
		ti_Close(var);
		return 1;
	}
	if (ti_Write(Player, sizeof(struct player_t), 1, var) != 1)
	{
		os_PutStrFull("Player");
		ti_Close(var);
		return 1;
	}
	if (ti_PutC('b', var) == EOF)
	{
		os_PutStrFull("b");
		ti_Close(var);
		return 1;
	}
	if (ti_Write(Counts, sizeof(struct counts_t), 1, var) != 1)
	{
		os_PutStrFull("Count");
		ti_Close(var);
		return 1;
	}
	if (ti_PutC('c', var) == EOF)
	{
		os_PutStrFull("c");
		ti_Close(var);
		return 1;
	}
	if (ti_Write(Prices, sizeof(struct prices_t), 1, var) != 1)
	{
		os_PutStrFull("Price");
		ti_Close(var);
		return 1;
	}
	ti_SetArchiveStatus(true, var);
	ti_Close(var);
	return 0;
}
/* Main function, called first */
int main(void)
{
	struct player_t Player;
	struct counts_t Counts;
	struct prices_t Prices;
	bool key, prevkey = false;
	if (load(&Player, &Counts, &Prices) == 1)
	{
		Player.points = 0;
		Player.cps = 0;
		Player.clickvalue = 1;
		Player.cps_mult = 1;
		Player.cvm = 1;
		Player.unlocked = 0;
		Player.page = 0;
		Counts.addcount = 0;
		Counts.studentcount = 0;
		Counts.subcount = 0;
		Counts.cookiecount = 0;
		Counts.multcount = 0;
		Counts.officecount = 0;
		Counts.divcount = 0;
		Counts.phonecount = 0;
		Counts.expcount = 0;
		Counts.spacecount = 0;
		Counts.calccount = 0;
		Counts.buttoncount = 0;
		Prices.addprice = 25;
		Prices.studentprice = 15;
		Prices.subprice = 250;
		Prices.cookieprice = 150;
		Prices.multprice = 980;
		Prices.officeprice = 1120;
		Prices.divprice = 7000;
		Prices.phoneprice = 7800;
		Prices.expprice = 80000;
		Prices.spaceprice = 90000;
		Prices.calcprice = 1000000;
		Prices.buttonprice = 1500000;
	}

	uint8_t seconds = rtc_Seconds;
	kb_key_t g1_key = kb_Data[1];
	gfx_Begin();
	gfx_SetTransparentColor(0);
	
	if (CEClickU_init() == 0)
	{
		missing_appvars();
	}
	else
	{
		
		gfx_SetPalette(palette, sizeof_palette, 0);
		gfx_SetDrawBuffer(); // Draw to the buffer to avoid rendering artifacts
		gfx_ZeroScreen();
		do
		{
			kb_Scan();
			key = (kb_Data[6] & kb_Enter);
			g1_key = kb_Data[1];
			if (key && !prevkey) {
				Player.points += Player.clickvalue * Player.cvm;
			}
			if (rtc_Seconds > seconds || rtc_Seconds > seconds)
			{
				Player.points += Player.cps * Player.cps_mult;
			}
			if (kb_Data[7] & kb_Right)
			{
				if (Player.page < Player.unlocked)
				{
					Player.page++;
				}

			}
			if (kb_Data[7] & kb_Left)
			{
				if (Player.page > 0)
				{
					Player.page--;
				}
			}
			if (Player.points >= 100 && Player.unlocked == 0)
			{
				Player.unlocked++;
			}
			if (Player.points >= 800 && Player.unlocked == 1)
			{
				Player.unlocked++;
			}
			if (Player.points >= 6000 && Player.unlocked == 2)
			{
				Player.unlocked++;
			}
			if (Player.points >= 80000 && Player.unlocked == 3)
			{
				Player.unlocked++;
			}
			if (Player.points >= 900000 && Player.unlocked == 4)
			{
				Player.unlocked++;
			}
			if (kb_2nd & g1_key)
			{
				if (Player.page == 0)
				{
					if (Player.points >= Prices.addprice)
					{
						Player.points = Player.points - Prices.addprice;
						Player.clickvalue++;
						Counts.addcount++;
						Prices.addprice *= 1.1;
					}
				}
				else if (Player.page == 1)
				{
					if (Player.points >= Prices.subprice)
					{
						Player.points = Player.points - Prices.subprice;
						Player.clickvalue += 5;
						Counts.subcount++;
						Prices.subprice *= 1.1;
					}
				}
				else if (Player.page == 2)
				{
					if (Player.points >= Prices.multprice)
					{
						Player.points = Player.points - Prices.multprice;
						Player.clickvalue += 10;
						Counts.multcount++;
						Prices.multprice *= 1.1;
					}
				}
				else if (Player.page == 3)
				{
					if (Player.points >= Prices.divprice)
					{
						Player.points = Player.points - Prices.divprice;
						Player.clickvalue += 80;
						Counts.divcount++;
						Prices.divprice *= 1.1;
					}
				}
				else if (Player.page == 4)
				{
					if (Player.points >= Prices.expprice)
					{
						Player.points = Player.points - Prices.expprice;
						Player.clickvalue += 750;
						Counts.expcount++;
						Prices.expprice *= 1.1;
					}
				}
				else if (Player.page == 5)
				{
					if (Player.points >= Prices.calcprice)
					{
						Player.points = Player.points - Prices.calcprice;
						Player.cvm *= 2;
						Counts.calccount++;
						Prices.calcprice *= 2.5;
					}
				}
			}
			if (kb_Alpha & kb_Data[2])
			{
				if (Player.page == 0)
				{
					if (Player.points >= Prices.studentprice)
					{
						Player.points = Player.points - Prices.studentprice;
						Player.cps++;
						Counts.studentcount++;
						Prices.studentprice *= 1.1;
					}
				}
				else if (Player.page == 1)
				{
					if (Player.points >= Prices.cookieprice)
					{
						Player.points = Player.points - Prices.cookieprice;
						Player.cps += 4;
						Counts.cookiecount++;
						Prices.cookieprice *= 1.1;
					} 
				}
				else if (Player.page == 2)
				{
					if (Player.points >= Prices.officeprice)
					{
						Player.points = Player.points - Prices.officeprice;
						Player.cps += 27;
						Counts.officecount++;
						Prices.officeprice *= 1.1;
					}
				}
				else if (Player.page == 3)
				{
					if (Player.points >= Prices.phoneprice)
					{
						Player.points = Player.points - Prices.phoneprice;
						Player.cps += 101;
						Counts.phonecount++;
						Prices.phoneprice *= 1.1;
					}
				}
				else if (Player.page == 4)
				{
					if (Player.points >= Prices.spaceprice)
					{
						Player.points = Player.points - Prices.spaceprice;
						Player.cps += 980;
						Counts.spacecount++;
						Prices.spaceprice *= 1.1;
					}
				}
				else if (Player.page == 5)
				{
					if (Player.points >= Prices.buttonprice)
					{
						Player.points = Player.points - Prices.buttonprice;
						Player.cps_mult *= 2;
						Counts.buttoncount++;
						Prices.buttonprice *= 2.5;
					}
				}
			}
			seconds = rtc_Seconds;
			Draw(&Player, &Counts, &Prices, prevkey);

			prevkey = key;
		} while (!(g1_key & kb_Del));
		gfx_End();
		if (save(&Player, &Counts, &Prices) == 1)
		{
			os_SetCursorPos(0, 0);
			os_PutStrFull("Err: CE Clicker Save Fail!Save Data Is Erased!      Please Report This Error  To Github:                  CoolModder/CalcClicker");
			ti_Delete("CEClickS");
			while (!os_GetCSC());
		}

		exit(0);
	}
}


