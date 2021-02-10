ALTX:rentbillboard("/rentbb");
CMD:rentbillboard(playerid , params[]) 
{
	if (PlayerInfo[playerid][pInjured] != 0 || GetPVarInt(playerid, "Freeze") || pTemp[playerid][pTaserTime] || pTemp[playerid][pCuffed]) return 1;
	if (!PlayerInfo[playerid][pNumber]) return SendErrorMessage(playerid, "To submit an advertisement you need a phone.");

    new bizid = -1;
    if ((bizid = Advertisement_Nearest(playerid)) == -1) return SendErrorMessage(playerid, "You are not with an advertising agency.");
	if (BizInfo[bizid][bizLocked] == 1)					 return GameTextForPlayer(playerid, "~r~CLOSED!", 2500, 1);

	new str[128], mes[(13+MAX_ZONE_NAME+60)*MAX_BILLBOARDS+27] = "Location\tName\tStatus\n";

	new count;
	for(new i; i < MAX_BILLBOARDS; i++) if (BillboardInfo[i][bbRentBy] == PlayerInfo[playerid][pID]) count++;
	if (count >= 3) return SendErrorMessage(playerid, "You have already rented the maximum number of billboards! /mybb - for management.");

	new location[MAX_ZONE_NAME];
	count = 0;

	for(new i; i < MAX_BILLBOARDS; i++) {
		if (!BillboardInfo[i][bbActive]) continue;
		GetZone(BillboardInfo[i][bbPosX],BillboardInfo[i][bbPosY], location, MAX_ZONE_NAME);

		if (!BillboardInfo[i][bbRentDate]) 	format(str, sizeof(str), "%s\tBillboard #%i\t{16b819}Free{FFFFFF}", location, i+1);
		else								format(str, sizeof(str), "%s\tBillboard #%i\t{FF6347}Rented by %s to %s{FFFFFF}", location, i+1, GetNameFromBD(BillboardInfo[i][bbRentBy]), get_date("%dd.%mm.%yy", BillboardInfo[i][bbRentDate]));

		format(mes, sizeof(mes), "%s\n%s", mes, str);
		count++;
	}

	if (!count) return SendErrorMessage(playerid, "There are no billboards on the server!");

	Dialog_Show(playerid, BillboardList, DIALOG_STYLE_TABLIST_HEADERS, "Billboard rental", mes, "Rent", "Cancel");
	return 1;
}

ALTX:mybillboards("/mybb");
CMD:mybillboards(playerid , params[]) 
{
	if (PlayerInfo[playerid][pInjured] != 0 || GetPVarInt(playerid, "Freeze") || pTemp[playerid][pTaserTime] || pTemp[playerid][pCuffed]) return 1;
	if (!PlayerInfo[playerid][pNumber])				return SendErrorMessage(playerid, "You need a phone number to submit an advertisement.");

    new bizid = -1;
    if ((bizid = Advertisement_Nearest(playerid)) == -1)	return SendErrorMessage(playerid, "You are not with an advertising agency.");
	if (BizInfo[bizid][bizLocked] == 1)						return GameTextForPlayer(playerid, "~r~CLOSED!", 2500, 1);

	new count, str[90], mes[(60+MAX_ZONE_NAME+13)*3+27] = "Location\tName\tStatus\n", location[MAX_ZONE_NAME];
	
	for(new i; i < MAX_BILLBOARDS; i++) {
		if (BillboardInfo[i][bbRentBy] == PlayerInfo[playerid][pID]) 
		{
			GetZone(BillboardInfo[i][bbPosX],BillboardInfo[i][bbPosY], location, MAX_ZONE_NAME);
			format(str, sizeof(str), "%s\tBillboard #%i\tRent to %s{FFFFFF}", location, i+1, get_date("%dd.%mm.%yy", BillboardInfo[i][bbRentDate]));

			format(mes, sizeof(mes), "%s\n%s", mes, str);
			count++;

			if (count == 3) break;
		}
	}

	if (!count) return SendErrorMessage(playerid, "You have no rented billboards!");
	
	Dialog_Show(playerid, MyBillboards, DIALOG_STYLE_TABLIST_HEADERS, "Your billboards", mes, "Remove", "Cancel");
	return 1;
}//

